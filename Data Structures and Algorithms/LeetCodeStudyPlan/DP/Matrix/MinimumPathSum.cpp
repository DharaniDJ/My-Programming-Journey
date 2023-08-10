
// Problem Link : https://leetcode.com/problems/minimum-path-sum/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<vector<int>> &grid, int i,int j){
        int n = grid.size();
        int m = grid[0].size();
        if(i==n-1 && j==m-1) return grid[i][j];


        int l = INT_MAX;
        int r = INT_MAX;

        if(i<n-1) l = solve(grid,i+1,j);
        if(j<m-1) r = solve(grid,i,j+1);

        return min(l,r)+grid[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        return solve(grid,0,0);
    }
};

// Approach2( Recursion+Memoization ) : O(n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<vector<int>> &grid, int i,int j,vector<vector<int>> &dp){
        int n = grid.size();
        int m = grid[0].size();
        if(i==n-1 && j==m-1) return grid[i][j];

        if(dp[i][j]!=-1) return dp[i][j];
        int l = INT_MAX;
        int r = INT_MAX;

        if(i<n-1) l = (dp[i+1][j]!=-1 ? dp[i+1][j] : solve(grid,i+1,j,dp));
        if(j<m-1) r = (dp[i][j+1]!=-1 ? dp[i][j+1] : solve(grid,i,j+1,dp));

        return dp[i][j]=min(l,r)+grid[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n,vector<int>(m,-1));
        return solve(grid,0,0,dp);
    }
};

// Approach3(DP) : O(n) time and O(1) space complexity
class Solution {
public:

    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        // vector<vector<int>> dp(n,vector<int>(m,0));
                
        for(int i=1;i<n;i++) grid[i][0]+=grid[i-1][0];
        for(int j=1;j<m;j++) grid[0][j]+=grid[0][j-1];
        
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                grid[i][j]+=min(grid[i-1][j],grid[i][j-1]);
            }
        }
        
        return grid[n-1][m-1];
    }
};