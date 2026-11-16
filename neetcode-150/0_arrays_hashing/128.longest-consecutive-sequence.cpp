/*
 * @lc app=leetcode id=128 lang=cpp
 *
 * [128] Longest Consecutive Sequence
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
bool exists(unordered_set<int> &s, int x){
    return s.find(x) != s.end();
}

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();

        unordered_set<int> s;
        s.reserve(n);

        for (auto &x: nums) s.insert(x);

        int maxLength = 0;

        for (auto x: s){
            if (!exists(s,x-1)){
                int length = 1;
                // Explanation for myself: Why is this O(n)?
                // Idea: Let's say the set s is made of k disjoint consecutive subsequences
                // S1, S2, ..., Sk such that S1 U S2 U ... U Sk = s
                // let them have lengths L1, L2, ..., Lk (also L1+L2+...+Lk = len(S) < n)
                // then at the end of the program, this while loop would have gone through S1,S2,...,Sk exactly once
                // Hence O(n)! We just did 2n operations, 2 per item in the set s
                while (exists(s,x+1)){
                    ++length;
                    ++x;
                }
                maxLength = max(maxLength, length);
            }
        }

        return maxLength;
    }
};
// @lc code=end
