
// Problem Link : https://leetcode.com/problems/unique-paths/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^(n+m)) time and O(m*n) space complexity
class Solution {
public:
    int uniquePaths(int m, int n) {
        if(m==0 | n==0) return 0;
        if(m==1 && n==1) return 1;
        
        return uniquePaths(m-1,n)+uniquePaths(m,n-1);
    }
};

// Approach2(Recursion + Memoization) : O(m*n) time and O(m*n) space complexity
class Solution {
public:
    int solve(int m, int n,vector<vector<int>> &dp){
        if(m==0 | n==0) return 0;
        if(m==1 && n==1) return 1;
        
        if(dp[m][n]!=-1) return dp[m][n];
        
        return dp[m][n] = solve(m-1,n,dp)+solve(m,n-1,dp);
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1,vector<int>(n+1,-1));
        return solve(m,n,dp);
    }
};

// Approach3(DP) : O(m*n) time and O(m*n) space complexity
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,0));
        
        for(int i=0;i<m;i++) dp[i][0]=1;
        for(int j=0;j<n;j++) dp[0][j]=1;
        
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j] = dp[i-1][j]+dp[i][j-1];
            }
        }
        
        return dp[m-1][n-1];
    }
};

// Approach4(Maths) : O(1) time and O(1) space complexity
class Solution {
public:
    
    long long ncr(int n, int r){
        if(r==0 || r==n) return 1;
        
        if(n-r < r) r = n-r;
        
        long long numerator = 1, denominator = 1;
        
        while(r){
            numerator*=n;
            denominator*=r;
            
            long long m = __gcd(numerator, denominator);
            
            numerator/=m;
            denominator/=m;
            
            n--;
            r--;
        }
        
        return numerator;
    }
        
    int uniquePaths(int m, int n) {
        return ncr( m+n-2 , m-1 );
    }
};