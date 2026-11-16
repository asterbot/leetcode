/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        std::unordered_set<int> seen;

        for (auto &x: nums){
            if (seen.find(x) != seen.end()) return true; 
            else seen.insert(x);
        }

        return false;
    }
};
// @lc code=end
