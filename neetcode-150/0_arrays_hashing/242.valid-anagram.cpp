/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        
        int freqs[26] = {0}; // indexes: a=0, z=25
        for (auto &c: s) freqs[c-'a']+=1;
        for (auto &c: t) freqs[c-'a']-=1;

        for (auto &x: freqs) if (x!=0) return false;

        return true;
    }
};
// @lc code=end
