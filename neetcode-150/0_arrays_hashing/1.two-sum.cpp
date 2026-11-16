/*
 * @lc app=leetcode id=1 lang=cpp
 *
 * [1] Two Sum
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res(2);

        std::map<int,int> m;
        for (int i=0; i<nums.size(); ++i){
            auto it = m.find(nums[i]);
            if (it == m.end()) m[target-nums[i]] = i; // didn't find
            else{
                // found, answer!
                res[0] = i;
                res[1] = it->second;
                return res;
            }
        }

        return res;
    }
};
// @lc code=end
