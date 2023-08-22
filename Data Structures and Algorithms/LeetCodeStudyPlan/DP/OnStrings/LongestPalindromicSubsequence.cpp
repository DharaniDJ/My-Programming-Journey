
// Problem Link : https://leetcode.com/problems/longest-palindromic-subsequence/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(string &s, int i, int j){
        if(i==j) return 1;
        if(i>j) return 0;
        
        if(s[i]==s[j]) return solve(s,i+1,j-1)+2;
        
        return max(solve(s,i,j-1),solve(s,i+1,j));
    }
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        
        return solve(s,0,n-1);
    }
};

// Approach2(Recursion+Memoization) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int solve(string &s, int i, int j, vector<vector<int>> &dp){
        if(i==j) return 1;
        if(i>j) return 0;
        
        if(dp[i][j]!=-1) return dp[i][j];
        if(s[i]==s[j]) return dp[i][j]=solve(s,i+1,j-1,dp)+2;
        
        return dp[i][j]=max(solve(s,i,j-1,dp),solve(s,i+1,j,dp));
    }
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n,-1));
        return solve(s,0,n-1,dp);
    }
};

// Approach3(DP) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n,vector<int>(n));
        for(int i=n-1;i>=0;i--){
            dp[i][i]=1;
            for(int j=i+1;j<n;j++){
                if(s[i]==s[j]) dp[i][j] = dp[i+1][j-1]+2;
                else{
                    dp[i][j] = max({dp[i+1][j],dp[i][j-1]});
                }
            }
        }
        
        return dp[0][n-1];
    }
};

// Approach(Space Optimized DP) : O(n^2) time and O(n) space complexity
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<int> prev(n,0);
        for(int i=n-1;i>=0;i--){
            vector<int> cur(n,0);
            cur[i]=1;
            for(int j=i+1;j<n;j++){
                if(s[i]==s[j]) cur[j] = prev[j-1]+2;
                else{
                    cur[j] = max({prev[j],cur[j-1]});
                }
            }
            prev = cur;
        }

        return prev[n-1];
    }
};