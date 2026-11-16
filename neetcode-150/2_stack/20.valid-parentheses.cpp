/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;

        for (char &c: s){
            if (c=='(' || c=='{' || c=='[') stack.push_back(c);
            else if ((c==')' && stack.back()!='(') ||
                    (c=='}' && stack.back()!='{') ||
                    (c==']' && stack.back()!='[')) return false;
        }

        return true;
    }
};
// @lc code=end
