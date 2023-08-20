
// Problem Link :  https://leetcode.com/problems/unique-paths-ii/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion): O(2^(m+n)) time and O(m+n) space complexity
class Solution {
public:
    int solve(vector<vector<int>>& grid, int i, int j){
        if(i==grid.size()-1 && j==grid[0].size()-1) return grid[i][j]==0 ? 1 : 0;
        if(i==grid.size() || j==grid[0].size()) return 0;
        if(grid[i][j]==1) return 0;
        
        return solve(grid,i+1,j) + solve(grid,i,j+1);
    }
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        return solve(grid,0,0);
    }
};

// Approach2(Recursion + Memoization) : O(n*m) time and O(n*m) space complexity
class Solution {
public:
    int solve(vector<vector<int>>& grid, int i, int j, vector<vector<int>> &dp){
        if(i==grid.size()-1 && j==grid[0].size()-1) return grid[i][j]==0 ? 1 : 0;
        if(i==grid.size() || j==grid[0].size()) return 0;
        if(grid[i][j]==1) return 0;

        if(dp[i][j]!=-1) return dp[i][j];

        return dp[i][j]=solve(grid,i+1,j,dp) + solve(grid,i,j+1,dp);
    }
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n,vector<int>(m,-1));
        return solve(grid,0,0,dp);
    }
};

// Approach3(DP) : O(n*m) time and O(n*m) space complexity
class Solution {
public:

    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        if(grid[n-1][m-1]==1 || grid[0][0]==1) return 0;
        grid[0][0]=1;

        for(int i=1;i<n;i++){
            grid[i][0]=(grid[i][0]==0 && grid[i-1][0]==1) ? 1 : 0;
        }

        for(int i=1;i<m;i++){
            grid[0][i]=(grid[0][i]==0 && grid[0][i-1]==1) ? 1 : 0;
        }

        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(grid[i][j]==1){
                    grid[i][j]=0;
                    continue;
                }
                grid[i][j] = grid[i-1][j]+grid[i][j-1];
            }
        }

        return grid[n-1][m-1];
    }
};