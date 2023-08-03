
// Problem Link: https://leetcode.com/problems/longest-palindrome/

// Greedy Approach : O(n) time and O(1) space complexity
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char,int> mp;
        for(char c:s){
            mp[c]++;
        }
        bool fl = false;
        int cnt = 0;
        for(auto it:mp){
            if((it.second)%2) fl=true;
            cnt+=(it.second/2)*2;
        }
        if(fl) cnt++;
        return cnt;
    }
};