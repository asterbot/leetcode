/*
 * @lc app=leetcode id=875 lang=cpp
 *
 * [875] Koko Eating Bananas
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start

// If the rate is k, the time to eat piles[i] is ceil(piles[i]/k)
// Also, h>=piles.length so you can spend at least 1 hour on each pile
// which means that if you can eat all the bananas in that hour, you're done
// Now, if k = max(piles), you will always be able to eat all the bananas
// BUT - what is the smallest k? 0, but you might not be able to eat your bananas
// So what's the smallest k in [0, max(piles)] which lets us finish bananas

// Ok new question: for a given k, how many hours do you need?
// I think starting here can help. Since if we know hoursNeeded(k), we can check that h>=hoursNeeded(k)
// moreover we can check that hoursNeeded(k) == h (!) Bound it exactly maybe
// ok so its occurring to me that hoursNeeded(k) being equal to h does not guarantee that its the min sol
// what do we need? hmm

//

long long ceilDiv(long long a, long long b){
    return (a+b-1)/b;
}

int hoursNeeded(int k, vector<int> &piles){
    // emulate the nom nom...
    int res=0;
    for (auto &x: piles){
        res += ceilDiv(x, k);
    }
    return res;
}

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxK = *max_element(piles.begin(), piles.end());

        int minK = maxK;

        int start=1; int end = maxK;
        while (start<end){
            int k = (start + end)/2;
            // cout<<start<<","<<end<<","<<k<<endl;
            int hours = hoursNeeded(k, piles);
            // cout<<"get here"<<endl;
            if (hours <= h) {
                minK = min(k, minK);
                end = k; // i think since we want the smallest k, its favorable to reduce here?
            }
            else start = k+1;
        }

        return minK;
    }
};
// @lc code=end
