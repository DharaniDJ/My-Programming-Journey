
// Problem Link : https://leetcode.com/problems/minimum-falling-path-sum/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(n*3^n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<vector<int>>& matrix, int i, int j){
        
        
        // base cases
        if (j < 0 || j == matrix.size()) {
            return INT_MAX;
        }
        // check if we have reached the last row
        if (i == matrix.size() - 1) {
            return matrix[i][j];
        }

        // calculate the minimum falling path sum starting from each possible
        // next step
        int left = solve(matrix, i + 1, j - 1);
        int middle = solve(matrix, i + 1, j);
        int right = solve(matrix, i + 1, j + 1);

        int minSum = min(left, min(middle, right)) + matrix[i][j];

        return minSum;
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int ans = INT_MAX;
        
        int n = matrix.size();
        int m = matrix[0].size();

        
        for(int i=0;i<matrix[0].size();i++){
            ans = min(ans,solve(matrix,0,i));
        }
        
        return ans;
    }
};

// Approach2(Recursion + Memoization) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int solve(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& dp){
        
        
        // base cases
        if (j < 0 || j == matrix.size()) {
            return INT_MAX;
        }
        // check if we have reached the last row
        if (i == matrix.size() - 1) {
            return matrix[i][j];
        }
        // check if the results are calculated before
        if (dp[i][j] != INT_MAX) {
            return dp[i][j];
        }

        // calculate the minimum falling path sum starting from each possible
        // next step
        int left = solve(matrix, i + 1, j - 1, dp);
        int middle = solve(matrix, i + 1, j, dp);
        int right = solve(matrix, i + 1, j + 1, dp);

        int minSum = min(left, min(middle, right)) + matrix[i][j];

        dp[i][j] = minSum;
        return minSum;
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int ans = INT_MAX;
        
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> dp(n,vector<int>(m,INT_MAX));
        
        for(int i=0;i<matrix[0].size();i++){
            ans = min(ans,solve(matrix,0,i,dp));
        }
        
        return ans;
    }
};

// Approach3(DP) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp = matrix;
        
        for(int i=n-2;i>=0;i--){
            for(int j=0;j<m;j++){
                int temp = INT_MAX;
                temp = min(temp,dp[i+1][j]);
                if(j!=0) temp = min(temp,dp[i+1][j-1]);
                if(j!=m-1) temp = min(temp,dp[i+1][j+1]);
                dp[i][j]+=temp;
            }
        }
        
        int ans = INT_MAX;
        for(int i=0;i<m;i++) ans = min(ans,dp[0][i]);
        
        return ans;
    }
};

// Approach4(Space Optimized DP) : O(n^2) time and O(n) space complexity
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        vector<int> prev(m,0);
        
        for(int i=n-1;i>=0;i--){
            vector<int> cur(m,0);
            for(int j=0;j<m;j++){
                cur[j] = prev[j];
                if(j>0) cur[j] = min(cur[j],prev[j-1]);
                if(j!=m-1) cur[j] = min(cur[j],prev[j+1]);
                
                cur[j]+=matrix[i][j];
            }
            prev = cur;
        }
        
        int ans = INT_MAX;
        for(int i=0;i<m;i++) ans = min(ans,prev[i]);
        
        return ans;
    }
};