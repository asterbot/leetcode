/*
 * @lc app=leetcode id=167 lang=cpp
 *
 * [167] Two Sum II - Input Array Is Sorted
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size();
        
        vector<int> res(2);
        res[0]=0; res[1]=n-1;

        while (res[0] < res[1]){
            int s = numbers[res[0]] + numbers[res[1]];
            if (s < target) res[0]++;
            else if (s>target) res[1]--;
            else break;
        }

        res[0]++; res[1]++;
        return res;
    }
};
// @lc code=end
