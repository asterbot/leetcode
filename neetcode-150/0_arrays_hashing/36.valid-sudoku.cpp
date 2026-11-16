/*
 * @lc app=leetcode id=36 lang=cpp
 *
 * [36] Valid Sudoku
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int N=9;

        // bitmasking time!
        int rows[9] = {0};
        int cols[9] = {0};
        int squares[9] = {0};

        for (int i=0; i<N; ++i){
            for (int j=0; j<N; ++j){
                if (board[i][j]=='.') continue;
                int num = board[i][j] - '0'; // num from 1-9
                num--; // to align with 0-indexing

                int sqIndex = (i/3)*3 + (j/3);

                if (rows[i] & (1<<num)) return false; // exists in row
                if (cols[j] & (1<<num)) return false; // exists in col
                if (squares[sqIndex] & (1<<num)) return false; // exists in square

                rows[i] = rows[i] | (1<<num);
                cols[j] = cols[j] | (1<<num);
                squares[sqIndex] = squares[sqIndex] | (1<<num);
            }
        }
    
        return true;
    }
};
// @lc code=end
