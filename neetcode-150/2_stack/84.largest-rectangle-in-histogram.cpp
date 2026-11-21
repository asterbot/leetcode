/*
 * @lc app=leetcode id=84 lang=cpp
 *
 * [84] Largest Rectangle in Histogram
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
// Idea: We want arrays leftBoundaries[] and rightBoundaries[]
// The idea is that leftBoundaries[i] is the closest element to the left of i such that heights[leftBoundaries[i]] < heights[i]. If nothing exists, its -1
// Similarly rightBoundaries[i] is the closest element to the right of i such that heights[rightBoundaries[i]] < heights[i]. If nothing exists, its n
// Then finally the area that element i can get is (right - left - 1) * heights[i]


ostream &operator<<(ostream &out, vector<int> &v){
    for (auto &x: v) out<<x<<", ";
    return out;
}

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();

        vector<int> leftBoundaries(n,-1);
        vector<int> leftStack; leftStack.reserve(n);
        for (int i=0; i<n; ++i){
            while (!leftStack.empty() && heights[leftStack.back()] >= heights[i]){
                leftStack.pop_back();
            }
            if (!leftStack.empty() && heights[leftStack.back()] < heights[i]) leftBoundaries[i] = leftStack.back();
            leftStack.push_back(i);
        }
        // cout<<leftBoundaries<<endl;

        vector<int> rightBoundaries(n,n);
        vector<int> rightStack; rightStack.reserve(n);
        for (int i=n-1; i>=0; --i){
            while (!rightStack.empty() && heights[rightStack.back()] >= heights[i]){
                rightStack.pop_back();
            }
            if (!rightStack.empty() && heights[rightStack.back()] < heights[i]) rightBoundaries[i] = rightStack.back();
            rightStack.push_back(i);
        }
        // cout<<rightBoundaries<<endl;

        int maxArea=0;
        for (int i=0; i<n; ++i){
            maxArea = max(maxArea, (rightBoundaries[i] - leftBoundaries[i] - 1) * heights[i]);
        }
        return maxArea;
    }
};
// @lc code=end

