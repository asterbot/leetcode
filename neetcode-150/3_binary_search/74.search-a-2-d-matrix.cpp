/*
 * @lc app=leetcode id=74 lang=cpp
 *
 * [74] Search a 2D Matrix
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
int getElement(vector<vector<int>> & matrix, int i){
    int n = matrix[0].size(); // guaranteed

    int row = i / n;
    int col = i % n;

    return matrix[row][col];
}

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // looks like we just need mappings from [(0,0), (m-1,n-1)] to [0, m*n-1]
        int m = matrix.size();
        int n = matrix[0].size(); // guaranteed

        int start = 0; int end = m * n - 1;
        while (start<=end){
            int i = (start + end) / 2;
            int element = getElement(matrix, i);
            if (element == target) return true;
            else if (target > element) start = i + 1;
            else end = i - 1;
        }

        return false;
    }
};
// @lc code=end

