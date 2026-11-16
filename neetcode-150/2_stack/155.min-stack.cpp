/*
 * @lc app=leetcode id=155 lang=cpp
 *
 * [155] Min Stack
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class MinStack {
    vector<pair<int, int>> elements; // (actual value, min so far)
public:
    MinStack() {
        elements.reserve(30000);
    }
    
    void push(int value) {
        if (elements.size()==0) elements.emplace_back(value, value);
        else elements.emplace_back(value, min(value, elements.back().second));
    }
    
    void pop() {
        elements.pop_back();
    }
    
    int top() {
        return elements.back().first; 
    }
    
    int getMin() {
        return elements.back().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
// @lc code=end

