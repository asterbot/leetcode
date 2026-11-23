/*
 * @lc app=leetcode id=981 lang=cpp
 *
 * [981] Time Based Key-Value Store
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start


struct TimedValue{
    string value;
    int time;
    
    TimedValue(string value, int time): value{value}, time{time} {}
};

ostream &operator<<(ostream &out, vector<TimedValue> v){
    for (auto &x: v){
        out<<"(v="<<x.value<<", t="<<x.time<<"), ";
    }
    return out;
}


class TimeMap {
    map<string, vector<TimedValue>> internalMap;

public:
    TimeMap() {

    }
    
    void set(string key, string value, int timestamp) {
        if (internalMap.find(key) == internalMap.end()){
            vector<TimedValue> v;
            v.emplace_back(value, timestamp);
            internalMap[key] = v;
        }
        else{
            // already exists
            internalMap[key].emplace_back(value, timestamp);
        }

    }
    
    string get(string key, int timestamp) {
        if (internalMap.find(key)==internalMap.end()) return "";

        vector<TimedValue> &v = internalMap[key];
        int n = v.size();

        if (timestamp < v[0].time) return "";

        // cout<<v<<endl;

        TimedValue optimalValue = v[0];
        int start=0; int end=n-1;
        while (start<=end){
            // cout<<start<<","<<end<<endl;
            int mid = (start+end)/2;
            if (v[mid].time <= timestamp){
                if (v[mid].time > optimalValue.time) optimalValue = v[mid];
                start = mid + 1;
            }
            else end = mid - 1;
        }

        return optimalValue.value;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
// @lc code=end

// t=5
// [0,1,2,3,4,6,8] 