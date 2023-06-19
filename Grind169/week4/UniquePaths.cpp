
// Problem Link : https://leetcode.com/problems/unique-paths

// Approach 1 (Recursion): O(2^(m+n)) time and O(m+n) space complexity
class Solution {
public:
    
    int uniquePaths(int m, int n) {
        if(m==1 || n==1) return 1;
        return uniquePaths(m-1,n)+uniquePaths(m,n-1);
    }
};

// Approach 2 (DP) : O(n*m) time and O(n*m) space complexity
class Solution {
public:
    
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,1));
        
        for(int i=1;i<m;i++){
            for(int j=1;j<n;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

// Approach 3(Math): O(n*log(m+n)) time and O(1) space complexity
class Solution {
public:
    
    // O(r*logn) time and O(1) space complexity
    long long nCr(int n, int r){
        
        // p holds the value of n*(n-1)*(n-2)...,
        // k holds the value of r*(r-1)...
        long long p = 1, k = 1;
        
        if(n-r < r){
            r = n-r;
        }
        
        if(r!=0){
            while(r){
                p*=n;
                k*=r;
                
                long long m = __gcd(p,k);
                
                // dividing by gcd, to simplify
                // product division by their gcd
                // saves from the overflow
                p/=m;
                k/=m;
                
                n--;
                r--;
                
            }
        }else{
            p=1;
        }
        
        return p;
    }
    
    int uniquePaths(int m, int n) {
        return nCr(m+n-2,n-1);
    }
};