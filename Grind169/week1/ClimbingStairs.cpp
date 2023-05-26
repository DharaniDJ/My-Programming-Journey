
// Problem Link: https://leetcode.com/problems/climbing-stairs/

// recursion: O(2^n) time and O(n) space complexity
// class Solution {
// public:
//     int climbStairs(int n) {
//         if(n==1 || n==0) return 1;
//         return climbStairs(n-1)+climbStairs(n-2);
//     }
// };

// recursion + memoization: O(n) time and O(n) space complexity
// class Solution {
// public:
//     int solve(int i,int n,vector<int> &dp){
//         if(i>n) return 0;
//         if(i==n) return 1;
//         if(dp[i]!=-1) return dp[i];
//         int temp = solve(i+1,n,dp)+solve(i+2,n,dp);
//         return dp[i]=temp;
//     }
//     int climbStairs(int n) {
//         vector<int> dp(n+1,-1);
//         return solve(0,n,dp);
//     }
// };

// dynamic programming: O(n) time and O(n) space complexity
// class Solution {
// public:
//     int climbStairs(int n) {
//         int fib[n+1];
//         fib[0]=1;
//         fib[1]=1;
//         for(int i=2;i<=n;i++){
//             fib[i]=fib[i-1]+fib[i-2];
//         }
//         return fib[n];
//     }
// };

// fibonacci number: O(n) time andd O(1) space complexity
class Solution {
public:
    int climbStairs(int n) {
        int a = 1,b=1;
        for(int i=2;i<=n;i++){
            int c = a+b;
            a=b;
            b=c;
        }
        return b;
    }
};