/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();

        int i=0; int j=n-1;
        int maxArea = min(height[i], height[j])*(j-i);
        if (height[i] < height[j]) i++; else j--;
        while (i<j){
            int area = min(height[i], height[j])*(j-i);
            if (area > maxArea) maxArea = area;
            
            if (height[i] < height[j]) i++; else j--;
        }
        return maxArea;
    }
};
// @lc code=end
