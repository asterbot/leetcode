/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 */

#include <bits/stdc++.h>
using namespace std;


// @lc code=start
bool alnum(char &c){
    return (c>='a' && c<='z') 
            || (c>='A' && c<='Z') 
            || (c>='0' && c<='9');
}

char lowerCase(char &c){
    if (c>='A' && c<='Z') return c + ('a' - 'A');
    return c;
}

class Solution {
public:
    bool isPalindrome(string s) {
        string simple; 
        for (auto &c: s){
            if (alnum(c)) simple+=lowerCase(c);
        }
        
        int n = simple.length();
        int p1 = 0;
        int p2 = n-1;
        while (p1 < p2){
            if (simple[p1] != simple[p2]) return false;
            p1++;
            p2--;
        }

        return true;
    }
};
// @lc code=end
