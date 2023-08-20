
// Problem Link : https://leetcode.com/problems/decode-ways/

// Approach1 (Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(string &s, int idx){
        if(s.size()==idx) return 1;
        if(s[idx]=='0') return 0;

        if(s.size()-1==idx) return 1;

        int res = solve(s,idx+1);
        if(stoi(s.substr(idx,2))<=26) res+=solve(s,idx+2);

        return res;
    }
    int numDecodings(string s) {
        return solve(s,0);
    }
};

// Approach2(Memoization) : O(n) time and O(n) space complexity
class Solution {
public:
    int solve(string &s, int idx, vector<int>&dp){
        if(dp[idx]!=-1) return dp[idx];
        if(s.size()==idx) return 1;

        if(s[idx]=='0') return 0;

        if(s.size()-1==idx) return 1;

        int res = solve(s,idx+1,dp);
        if(stoi(s.substr(idx,2))<=26) res+=solve(s,idx+2,dp);
        
        return dp[idx]=res;
    }
    int numDecodings(string s) {
        vector<int> dp(s.size()+3,-1);
        return solve(s,0,dp);
    }
};

// Approach3(Iterative) : O(n) time and O(n) space complexity
class Solution {
public:
    int numDecodings(string s) {

        // A cell with index i of the dp array is used to store the number of decode ways for substring of s from index 0 to index i-1.
        vector<int> dp(s.size()+1);

        dp[0]=1;

        dp[1] = (s[0]=='0'? 0 : 1);
        for(int i=2;i<dp.size();i++){
            if(s[i-1]!='0') dp[i]=dp[i-1];

            int two_dig = stoi(s.substr(i-2,2));
            if(two_dig>=10 && two_dig<=26) dp[i]+=dp[i-2];
        }

        return dp[s.size()];
    }
};