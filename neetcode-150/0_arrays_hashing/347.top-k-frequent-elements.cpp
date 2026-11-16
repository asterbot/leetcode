/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freqs; // frequency map
        freqs.reserve(nums.size());
        for (auto &x: nums){ freqs[x]++; }

        int n = nums.size();
        vector<vector<int>> buckets(n);
        for (auto &p: freqs){
            buckets[p.second-1].push_back(p.first);
        }

        vector<int> res;
        res.reserve(k);
        
        int i=n-1;
        while (res.size()<k){
            if (buckets[i].size()!=0){
                for (auto &x: buckets[i]) {
                    if (res.size() < k) res.push_back(x);
                }
            }
            --i;
        }

        return res;
    }
};
// @lc code=end
