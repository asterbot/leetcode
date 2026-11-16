#!/usr/bin/env node
// Patches the LeetCode VS Code extension so new C++ problem files get HEADER
// inserted before "// @lc code=start". Safe to run repeatedly.
// Runs automatically on folder open via .vscode/tasks.json.

const fs = require("fs");
const os = require("os");
const path = require("path");

const HEADER = "#include <bits/stdc++.h>\nusing namespace std;\n\n\n";
const TAG = "/* cpp-header-patch */";

const extRoots = [".vscode", ".vscode-insiders", ".vscode-oss", ".vscode-server", ".cursor"]
  .map((d) => path.join(os.homedir(), d, "extensions"));

const ORIGINAL =
  /const codeTemplate = yield this\.executeCommandWithProgressEx\("Fetching problem data\.\.\.", this\.nodeExecutable, cmd\);\s*\n(\s*)yield fse\.writeFile\(filePath, codeTemplate\);/;

let found = 0, patched = 0;

for (const root of extRoots) {
  let entries;
  try { entries = fs.readdirSync(root); } catch { continue; }
  for (const name of entries) {
    if (!/^leetcode\.vscode-leetcode-/.test(name)) continue;
    const file = path.join(root, name, "out", "src", "leetCodeExecutor.js");
    if (!fs.existsSync(file)) continue;
    found++;
    let src = fs.readFileSync(file, "utf8");

    // Already patched: refresh the header in case it changed.
    if (src.includes(TAG)) {
      const updated = src.replace(/const header = .*; \/\* cpp-header-patch \*\//,
        `const header = ${JSON.stringify(HEADER)}; ${TAG}`);
      if (updated !== src) { fs.writeFileSync(file, updated); patched++; console.log(`Updated header: ${file}`); }
      else console.log(`Already patched: ${file}`);
      continue;
    }

    if (!ORIGINAL.test(src)) {
      console.warn(`Unrecognized extension code, skipping: ${file}`);
      continue;
    }
    src = src.replace(ORIGINAL, (_m, indent) =>
      `let codeTemplate = yield this.executeCommandWithProgressEx("Fetching problem data...", this.nodeExecutable, cmd);\n` +
      `${indent}if (language === "cpp") {\n` +
      `${indent}    const header = ${JSON.stringify(HEADER)}; ${TAG}\n` +
      `${indent}    const marker = "// @lc code=start";\n` +
      `${indent}    codeTemplate = codeTemplate.includes(marker) ? codeTemplate.replace(marker, header + marker) : header + codeTemplate;\n` +
      `${indent}}\n` +
      `${indent}yield fse.writeFile(filePath, codeTemplate);`);
    fs.writeFileSync(file, src);
    patched++;
    console.log(`Patched: ${file}`);
  }
}

if (!found) console.log("LeetCode extension not found; nothing to patch.");
if (patched) console.log("\n>>> Run 'Developer: Reload Window' for the change to take effect.");
