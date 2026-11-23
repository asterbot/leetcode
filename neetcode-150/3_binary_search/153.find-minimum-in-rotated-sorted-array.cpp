/*
 * @lc app=leetcode id=153 lang=cpp
 *
 * [153] Find Minimum in Rotated Sorted Array
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start

// In nums[start:end], can we prove that nums[mid]>nums[end] <=> the min lies in nums[start:mid-1]
// Elements: a[0]<a[1]<...<a[n-1]
// [a[0], a[1], ..., a[n-1]] --- rotated some times   ---- [a[n-4], ...,  a[n-1], a[0], ...., a[n-5]]
// Let's say S1 = [a[n-4], ...,  a[n-1]] and S2 = [a[0], ..., a[n-5]]
// -> Consider for contradiction, mid in S1 =>  a[n-1] > a[n-5] (not counted!)
// Only way the a[mid]<a[end] is if mid is in S2. So either a[mid] is a[0:n-5]
// Similarly if mid is [a[0], ..., a[n-5]] then the mid is a[start:mid-1]

class Solution {
  public:
    int findMin(vector<int>& nums) {
        int n = nums.size();

        int start=0; int end=n-1;
        while (start < end){
            int mid = (start + end)/2;
            if (nums[mid] < nums[end]) end = mid; 
            else start = mid + 1;
            
        }
        return nums[end];
    }
};
// @lc code=end

// [1,2,3,4,5,6,7]
// [2,3,4,5,6,7,1]
// [3,4,5,6,7,1,2]
// [4,5,6,7,1,2,3]
// [5,6,7,1,2,3,4]
// [6,7,1,2,3,4,5]

