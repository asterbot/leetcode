/*
 * @lc app=leetcode id=739 lang=cpp
 *
 * [739] Daily Temperatures
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();

        vector<int> stack;
        stack.reserve(n);

        vector<int> res(n,0);
        for (int i=0; i<n; ++i){
            if (stack.empty()) stack.push_back(i);
            else if(temperatures[i] <= temperatures[stack.back()]) stack.push_back(i);
            else{
                while (!stack.empty() && temperatures[i] > temperatures[stack.back()]){
                    int x = stack.back();
                    stack.pop_back();

                    res[x] = i-x;
                }
                stack.push_back(i);
            }
        }
        
        return res;
    }
};
// @lc code=end

