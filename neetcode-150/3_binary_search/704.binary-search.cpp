/*
 * @lc app=leetcode id=704 lang=cpp
 *
 * [704] Binary Search
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        int start=0;
        int end=n-1;
        while (start<=end){
            int i = (start+end)/2;
            if (nums[i]==target) return i;
            else if (target > nums[i]) start=i+1;
            else end=i-1;
        }

        return -1;
    }
};
// @lc code=end

