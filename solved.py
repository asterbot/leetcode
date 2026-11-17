#!/usr/bin/env python3
"""Mark newly solved problems in README.md, then commit and push.

Layout assumed:  <list>/<N_section>/<id>.<slug>.<ext>
  e.g.           neetcode-150/2_stack/20.valid-parentheses.cpp

README layout:   ## <List title>  ->  ### <Section title>  ->  - [x] [Title](path) ([problem](url))

Usage:
  ./solved.py              # update README, commit, push
  ./solved.py --no-push    # update README, commit
  ./solved.py --dry-run    # show what would change, touch nothing
  ./solved.py --sync-only  # just re-link/mark every solution on disk in README
"""

import argparse
import re
import subprocess
import sys
from pathlib import Path
from urllib.parse import quote

ROOT = Path(__file__).resolve().parent
README = ROOT / "README.md"
SOLUTION_EXTS = {".cpp", ".cc", ".c", ".py", ".java", ".js", ".ts", ".go", ".rs", ".kt", ".swift", ".cs", ".rb"}

# Overrides for list folder names that don't title-case nicely.
LIST_TITLES = {"neetcode-150": "NeetCode 150", "blind-75": "Blind 75"}

ITEM_RE = re.compile(r"^(\s*)- \[( |x|X)\] (.*?)\s*$")
# "[Title](path)" optionally followed by " ([problem](url))"
LINK_RE = re.compile(r"^\[([^\]]*)\]\(([^)]*)\)(?:\s*\(\[problem\]\([^)]*\)\))?$")
LEETCODE_URL = "https://leetcode.com/problems/{slug}/"


def norm(s: str) -> str:
    """Normalize a title/slug/heading for fuzzy matching."""
    s = s.lower().replace("&", " and ")
    s = re.sub(r"\band\b", "", s)
    return re.sub(r"[^a-z0-9]", "", s)


def git(*args, capture=True):
    r = subprocess.run(["git", *args], cwd=ROOT, text=True, capture_output=capture)
    if r.returncode != 0:
        sys.exit(f"git {' '.join(args)} failed:\n{r.stderr if capture else ''}")
    return r.stdout if capture else ""


class Problem:
    def __init__(self, rel: Path):
        self.rel = rel  # path relative to repo root
        self.list_dir, self.section_dir = rel.parts[0], rel.parts[1]
        m = re.match(r"^(\d+)\.(.+)$", rel.stem)
        self.number = m.group(1) if m else None
        self.slug = m.group(2) if m else rel.stem
        self.title = self._read_title() or self.slug.replace("-", " ").replace("_", " ").title()

    def _read_title(self):
        # LeetCode extension header: " * [167] Two Sum II - Input Array Is Sorted"
        try:
            head = (ROOT / self.rel).read_text(errors="ignore")[:1000]
        except OSError:
            return None
        m = re.search(r"\[\d+\]\s*(.+)", head)
        return m.group(1).strip() if m else None

    @property
    def keys(self):
        return {norm(self.slug), norm(self.title)}

    @property
    def link(self):
        return quote(self.rel.as_posix())

    @property
    def problem_url(self):
        return LEETCODE_URL.format(slug=self.slug)

    def entry(self, name):
        return f"- [x] [{name}]({self.link}) ([problem]({self.problem_url}))"

    @property
    def list_title(self):
        return LIST_TITLES.get(self.list_dir, self.list_dir.replace("-", " ").replace("_", " ").title())

    @property
    def section_title(self):
        name = re.sub(r"^\d+_", "", self.section_dir)
        return " ".join(w if w.isupper() else w.capitalize() for w in name.split("_"))

    @property
    def section_index(self):
        m = re.match(r"^(\d+)_", self.section_dir)
        return int(m.group(1)) if m else 10**9

    def label(self):
        num = f"{self.number}. " if self.number else ""
        lst = getattr(self, "list_heading", self.list_title)
        sec = getattr(self, "section_heading", self.section_title)
        return f"{num}{self.title} ({lst} / {sec})"


def is_solution(rel: Path) -> bool:
    return (len(rel.parts) == 3 and not rel.parts[0].startswith(".")
            and rel.suffix in SOLUTION_EXTS and (ROOT / rel).is_file())


def changed_solutions():
    """Return (new, modified) solution paths from git status."""
    out = git("status", "--porcelain", "-z", "-uall")
    new, modified = [], []
    entries = out.split("\0")
    i = 0
    while i < len(entries):
        e = entries[i]
        i += 1
        if len(e) < 4:
            continue
        code, path = e[:2], e[3:]
        if code[0] in "RC":  # rename/copy: next entry is the source path
            i += 1
        rel = Path(path)
        if not is_solution(rel):
            continue
        if code == "??" or "A" in code or code[0] in "RC":
            new.append(rel)
        elif "M" in code:
            modified.append(rel)
    return sorted(new), sorted(modified)


def all_solutions():
    return sorted(p.relative_to(ROOT) for p in ROOT.glob("*/*/*") if is_solution(p.relative_to(ROOT)))


# ---------------------------------------------------------------- README model

def find_block(lines, start, end, level, title):
    """Find heading '<level> title' between start and end. Returns (h_idx, block_end) or None."""
    prefix = "#" * level + " "
    for i in range(start, end):
        if lines[i].startswith(prefix) and norm(lines[i][len(prefix):]) == norm(title):
            j = i + 1
            while j < end and not re.match(rf"^#{{1,{level}}} ", lines[j]):
                j += 1
            return i, j
    return None


def trim_trailing_blank(lines, start, end):
    while end > start and lines[end - 1].strip() == "":
        end -= 1
    return end


def ensure_list(lines, p: Problem):
    found = find_block(lines, 0, len(lines), 2, p.list_title)
    if found:
        p.list_heading = lines[found[0]][3:].strip()
        return found
    while lines and lines[-1].strip() == "":
        lines.pop()
    lines += ["", f"## {p.list_title}", ""]
    return len(lines) - 2, len(lines)


def ensure_section(lines, p: Problem):
    l_start, l_end = ensure_list(lines, p)
    found = find_block(lines, l_start + 1, l_end, 3, p.section_title)
    if found:
        p.section_heading = lines[found[0]][4:].strip()
        return found
    # Insert ordered by the folder's numeric prefix, relative to sibling sections on disk.
    order = {}
    list_path = ROOT / p.list_dir
    for d in list_path.iterdir() if list_path.is_dir() else []:
        if d.is_dir():
            q = Problem.__new__(Problem)
            q.section_dir = d.name
            order[norm(q.section_title)] = q.section_index
    insert_at = l_end
    for i in range(l_start + 1, l_end):
        if lines[i].startswith("### ") and order.get(norm(lines[i][4:]), 10**9) > p.section_index:
            insert_at = i
            break
    if insert_at == l_end:
        insert_at = trim_trailing_blank(lines, l_start + 1, l_end)
        block = ["", f"### {p.section_title}", ""]
    else:
        block = [f"### {p.section_title}", "", ""]
    lines[insert_at:insert_at] = block
    h = insert_at + block.index(f"### {p.section_title}")
    return h, h + 2


def mark(lines, p: Problem):
    """Mark/link problem p in lines. Returns a short description of what changed, or None."""
    s_start, s_end = ensure_section(lines, p)
    entry = p.entry(p.title)
    for i in range(s_start + 1, s_end):
        m = ITEM_RE.match(lines[i])
        if not m:
            continue
        indent, _, text = m.groups()
        lm = LINK_RE.match(text)
        name = lm.group(1) if lm else text
        if norm(name) in p.keys:
            new = indent + p.entry(name)
            if lines[i] == new:
                return None
            lines[i] = new
            return "marked"
    # Not in the checklist yet: append after the section's last non-blank line.
    insert_at = trim_trailing_blank(lines, s_start + 1, s_end)
    if insert_at == s_start + 1:  # empty section -> leave a blank line after heading
        lines.insert(insert_at, "")
        insert_at += 1
    lines.insert(insert_at, entry)
    if insert_at + 1 >= len(lines) or lines[insert_at + 1].strip() != "":
        lines.insert(insert_at + 1, "")
    return "added"


def update_readme(problems, dry_run):
    text = README.read_text() if README.exists() else "# LeetCode\n"
    lines = text.rstrip("\n").split("\n")
    changes = []
    for p in problems:
        what = mark(lines, p)
        if what:
            changes.append((what, p))
    new_text = "\n".join(lines).rstrip("\n") + "\n"
    if new_text != text and not dry_run:
        README.write_text(new_text)
    return changes, new_text != text


# ---------------------------------------------------------------- main

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dry-run", action="store_true", help="print the plan, change nothing")
    ap.add_argument("--no-push", action="store_true", help="commit but don't push")
    ap.add_argument("--sync-only", action="store_true", help="mark/link every solution on disk; no commit")
    args = ap.parse_args()

    if args.sync_only:
        changes, changed = update_readme([Problem(r) for r in all_solutions()], args.dry_run)
        for what, p in changes:
            print(f"{what:7} {p.label()}")
        print("README updated." if changed and not args.dry_run else "No README changes written.")
        return

    new, modified = changed_solutions()
    if not new and not modified:
        sys.exit("No new or modified solutions found in git status.")

    # Mark every solution on disk (cheap + idempotent), so nothing is ever missed.
    problems = {r: Problem(r) for r in all_solutions()}
    update_readme(list(problems.values()), args.dry_run)

    solved = [problems[r] for r in new]
    lines = []
    if solved:
        subject = (f"Solve {solved[0].title}" if len(solved) == 1
                   else f"Solve {len(solved)} problems")
        lines += ["", "Solved:"] + [f"- {p.label()}" for p in solved]
    else:
        subject = f"Update {len(modified)} solution{'s' if len(modified) > 1 else ''}"
    if modified:
        lines += ["", "Updated:"] + [f"- {problems[r].label()}" for r in modified]
    message = subject + "\n" + "\n".join(lines)

    print(message)
    if args.dry_run:
        print("\n(dry run: nothing written, committed or pushed)")
        return

    git("add", "--", "README.md", *[str(r) for r in new + modified])
    git("commit", "-m", message, capture=False)
    if args.no_push:
        return
    branch = git("rev-parse", "--abbrev-ref", "HEAD").strip()
    has_upstream = subprocess.run(["git", "rev-parse", "--abbrev-ref", "@{u}"], cwd=ROOT,
                                  capture_output=True).returncode == 0
    git(*(["push"] if has_upstream else ["push", "-u", "origin", branch]), capture=False)


if __name__ == "__main__":
    main()
