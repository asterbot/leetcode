/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
bool inRange(int target, int start, int end){
    return target>=start && target<=end;
}

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();

        int start=0; int end=n-1;
        while (start<=end){
            // cout<<start<<","<<end<<endl;
            int mid = (start + end)/2;
            if (nums[mid]==target) return mid;
            else if (mid>start && nums[start] <= nums[mid-1]){
                if (inRange(target, nums[start], nums[mid-1])) end = mid -1;
                else start = mid + 1;
            }
            else if (mid<end && nums[mid+1] <= nums[end]){
                if (inRange(target, nums[mid+1], nums[end])) start = mid + 1;
                else end = mid - 1;
            }
            else if (target>nums[mid]){
                start = mid + 1;
            }
            else{
                end = mid-1;
            }
        }
        return -1;
    }
};
// @lc code=end

