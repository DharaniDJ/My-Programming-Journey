
// Problem Link : https://leetcode.com/problems/coin-change

// Recursion : O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<int>& coins, int i, int amount){
        if(i == coins.size()) return INT_MAX-1;
        if(amount == 0) return 0;
        
        int notTaken = solve(coins,i+1,amount);
        int taken = INT_MAX-1;
        if(coins[i]<=amount) taken = solve(coins,i,amount-coins[i])+1;
        
        return min({notTaken,taken});
    }
    int coinChange(vector<int>& coins, int amount) {
        int ans =  solve(coins,0,amount);
        if(ans+1==INT_MAX) return -1;
        return ans;
    }
};

// Top-Down or DP Memoization : O(n*S) time and O(n*S) space complexity
class Solution {
public:
    int solve(vector<int>& coins, int i, int amount,vector<vector<int>> &dp){
        if(i == coins.size()) return INT_MAX-1;
        if(amount == 0) return 0;
        
        if(dp[i][amount]!=-1) return dp[i][amount];
        
        int notTaken = solve(coins,i+1,amount,dp);
        int taken = INT_MAX-1;
        if(coins[i]<=amount) taken = solve(coins,i,amount-coins[i],dp)+1;
        
        return dp[i][amount]=min({notTaken,taken});
    }
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n+1,vector<int>(amount+1,-1));
        int ans =  solve(coins,0,amount,dp);
        if(ans+1==INT_MAX) return -1;
        return ans;
    }
};

// Bottom-up or DP Tabulation : O(n*S) time and O(n*S) space complexity
class Solution {
public:
    int solve(vector<int>& coins, int amount, vector<vector<int>> &dp){
        int n = coins.size();
        
        for(int i=0;i<=n;i++) dp[i][0]=0;
        for(int j=0;j<=amount;j++) dp[0][j]=INT_MAX-1;
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=amount;j++){
                dp[i][j]=dp[i-1][j];
                if(coins[i-1]<=j){
                    dp[i][j]=min({dp[i][j],dp[i][j-coins[i-1]]+1});
                }
            }
        }
        return dp[n][amount]==INT_MAX-1 ? -1 : dp[n][amount];
    }
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n+1,vector<int>(amount+1,-1));
        return solve(coins,amount,dp);
    }
};

// Space Optimization : O(n*S) time and O(S) space complexity
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> prev(amount+1,0), cur(amount+1,0);
        for(int i=0;i<=amount;i++){
            if(i%coins[0]==0) prev[i]=i/coins[0];
            else prev[i]=INT_MAX-1;
        }
        
        for(int i=1;i<n;i++){
            for(int j=0;j<=amount;j++){
                cur[j]=prev[j];
                if(coins[i]<=j) cur[j]=min(cur[j],1+cur[j-coins[i]]);
            }
            prev = cur;
        }
        return prev[amount]==INT_MAX-1 ? -1 : prev[amount];
    }
};