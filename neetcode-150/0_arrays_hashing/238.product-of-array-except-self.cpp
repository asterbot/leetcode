/*
 * @lc app=leetcode id=238 lang=cpp
 *
 * [238] Product of Array Except Self
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();

        vector<int32_t> prefixProds(n,1);
        for (int i=1; i<n; ++i){
            prefixProds[i] = nums[i-1] * prefixProds[i-1];
        }

        vector<int32_t> suffixProds(n,1);
        for (int i=n-2; i>=0; --i){
            suffixProds[i] = nums[i+1] * suffixProds[i+1];
        }

        vector<int32_t> answer(n);
        for (int i=0; i<n; ++i) answer[i] = prefixProds[i] * suffixProds[i];
        return answer;
    }
};
// @lc code=end
