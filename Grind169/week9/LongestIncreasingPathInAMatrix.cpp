
// Problem Link : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

// Approach1(Native DFS): O(2^(n+m)) time and O(n*m) space complexity
class Solution {
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int n, m;

    int dfs(vector<vector<int>> &matrix, int i, int j){
        int ans = 0;
        for(int k=0;k<4;k++){
            int x = i + dirs[k][0];
            int y = j + dirs[k][1];

            if(x>=0 && x<n && y>=0 && y<m && matrix[x][y]>matrix[i][j]){
                ans = max(ans,dfs(matrix,x,y));
            }
        }
        ans++;
        return ans;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();

        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans,dfs(matrix,i,j));
            }
        }
        return ans;
    }
};

// Approach2(DFS + Memoization) : O(n*m) time and O(n*m) space complexity
class Solution {
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int n, m;

    int dfs(vector<vector<int>> &matrix, int i, int j, vector<vector<int>> &dp){

        if(dp[i][j]!=-1) return dp[i][j];
        int ans = 0;
        for(int k=0;k<4;k++){
            int x = i + dirs[k][0];
            int y = j + dirs[k][1];

            if(x>=0 && x<n && y>=0 && y<m && matrix[x][y]>matrix[i][j]){
                ans = max(ans,dfs(matrix,x,y,dp));
            }
        }
        ans++;
        return dp[i][j]=ans;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();

        vector<vector<int>> dp(n,vector<int>(m,-1));

        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                ans = max(ans,dfs(matrix,i,j,dp));
            }
        }
        return ans;
    }
};

// Approach3(Topological Sorting) : O(n*m) time and O(n*m) space complexity

// Intuition : The result of each cell only related to the result of its neighbors
// For dynamic programming to work, if problem B depends on the result of problem A,
// then we must make sure that problem A is calculated before problem B.
// The terminology of such dependency order is "Topological order" or "Topological sorting":

// There are several ways to perform the topological sorting. Here we employ one of them called "Peeling Onion".
// In out problem, since we want the longest path in the DAG, which equals to the total number of layers of the "onion".
// Thus, we can count the number of layers during "peeling" and return the counts in the end without invoking dynamic programming.
class Solution {
    int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int n, m;

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        n = matrix.size();
        if(n==0) return 0;
        m = matrix[0].size();

        // padding the matrix with zero as boundaries
        // assuming all positive integer, otherwise use INT_MIN as boundaries
        vector<vector<int>> grid(n+2,vector<int>(m+2,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                grid[i][j] = matrix[i-1][j-1];
            }
        }

        vector<vector<int>> outdegree(n+2,vector<int>(m+2,0));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                for(int k=0;k<4;k++){
                    if(grid[i][j]<grid[i+dirs[k][0]][j+dirs[k][1]]){
                        outdegree[i][j]++;
                    }
                }
            }
        }

        // find leaves who have zero out degree as the initial level
        vector<pair<int,int>> leaves;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(outdegree[i][j]==0) leaves.push_back({i,j});
            }
        }

        int height = 0;

        while(leaves.size()!=0){
            height++;
            vector<pair<int,int>> newLeaves;
            for(auto node : leaves){
                int i = node.first;
                int j = node.second;

                for(int k=0;k<4;k++){
                    int x = i+dirs[k][0];
                    int y = j+dirs[k][1];

                    if(grid[i][j]>grid[x][y]){
                        if (--outdegree[x][y] == 0)
                            newLeaves.push_back({x, y});
                    }
                }
            }
            leaves = newLeaves;
        }

        return height;
    }
};