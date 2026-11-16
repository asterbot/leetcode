/*
 * @lc app=leetcode id=150 lang=cpp
 *
 * [150] Evaluate Reverse Polish Notation
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
ostream &operator<<(ostream &out, vector<int> v){
    for (auto &x: v) out<<x<<',';
    return out;
}

int performOp(int x, int y, string op){
    if (op=="+") return x+y;
    else if (op=="-") return x-y;
    else if (op=="*") return x*y;
    else return x/y;
}

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        vector<int> stack;
        for (auto &s: tokens){
            try{
                int x = stoi(s);
                stack.push_back(x);
            }
            catch(...){
                // look i was feeling like imeplemnting the int detection thing
                int res = performOp(stack[stack.size()-2], stack[stack.size()-1], s);
                for (int i=0; i<2; ++i) stack.pop_back();
                stack.push_back(res);
            }
        }
        return stack[0];
    }

};
// @lc code=end

