/*
 * @lc app=leetcode id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
ostream& operator<<(ostream &out, vector<int> &v){
    for (auto &x: v) out<<x<<",";
    return out;
}

class Solution {
public:
    int trap(vector<int>& height) {
        // let's try to create beforeMax and afterMax
        // beforeMax[i] = max(height[0:i-1])
        // afterMax[i] = max(height[i+1:n-1])
        // beforeMax[0] = beforeMax[n-1] = -1
        int n = height.size();

        vector<int> beforeMax(n,0);
        int peak = height[0];
        for (int i=1; i<n-1; ++i){
            beforeMax[i] = peak;
            if (height[i] > peak) peak = height[i];
        }

        vector<int> afterMax(n,0);
        peak = height[n-1];
        for (int i=n-2; i>0; --i){
            afterMax[i] = peak;
            if (height[i] > peak) peak = height[i];
        }

        // cout<<beforeMax<<endl;
        // cout<<afterMax<<endl;

        int res = 0;
        for (int i=0; i<n-1; ++i){
            res += max(0, min(beforeMax[i], afterMax[i]) - height[i]);
        }

        return res;
    }
};
// @lc code=end

