/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:

    vector<int> frequencyMap(string &s){
        vector<int> v(26, 0);

        for (auto &c: s) v[c-'a']++;

        return v;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        groups.reserve(strs.size());

        for (auto& s : strs) {
            string key(26, 0);              // counts as chars; fine while each count is under 256
            for (char c : s) key[c - 'a']++;
            groups[std::move(key)].push_back(s);
        }

        vector<vector<string>> res;
        res.reserve(groups.size());
        for (auto& p : groups) res.push_back(std::move(p.second));
        return res;

    }
};
// @lc code=end
