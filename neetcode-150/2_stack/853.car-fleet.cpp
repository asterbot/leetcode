/*
 * @lc app=leetcode id=853 lang=cpp
 *
 * [853] Car Fleet
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
// For car "i" to get to position x, it will get there in time:
// position[i] + t * speed[i] = x => t = (x-position[i])/(speed[i])
int ceilingDiv(int a, int b){
    return (a + b - 1)/b;
}

struct CarInfo{
    int position; // position of car at start (guaranteed unique)
    int speed; // speed of car
    float t; // t-value (to target)

    CarInfo(): position{0}, speed{0}, t{0} {}
    CarInfo(int target, int position, int speed): 
        position{position}, speed{speed}, t{((float)(target-position))/(speed)} 
        {}
};

ostream &operator<<(ostream &out, vector<CarInfo> &v){
    for (auto &p: v) out<<"("<<p.position<<","<<p.speed<<","<<p.t<<"), ";
    return out;
}


class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<CarInfo> cars(n);
        for (int i=0; i<n; ++i){
            cars[i] = CarInfo(target, position[i], speed[i]);
        }
        sort(cars.begin(), cars.end(), [](const CarInfo& a, const CarInfo& b){
            return a.position > b.position; // reverse sort! forward sort would a<b
        });
        // cout<<cars<<endl;

        // Idea: the cars are sorted in descending order
        // -> If the t = (target - position[i]/speed[i]) is in the same descending order, no fleets form
        // otherwise fleets form if position[i]>position[j] and t[i]<t[j]
        vector<float> stack;
        stack.reserve(n);
        for (int i=0; i<n; ++i){
            if (stack.empty()) stack.push_back(cars[i].t);
            if (cars[i].t > stack.back()) stack.push_back(cars[i].t);
            else continue;
        }
        return stack.size();
    }
};
// @lc code=end
