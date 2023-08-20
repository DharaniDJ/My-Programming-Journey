
// Problem Link : https://leetcode.com/problems/rotting-oranges

// Approach 1 (BFS) : O(n*m) time and O(n*m) space complexity

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        int totalRottenOranges = 0;
        int finalRottenOranges = 0;
        
        queue<pair<int,int>> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]) totalRottenOranges++;
                if(grid[i][j]==2) {
                    q.push({i,j});
                }
            }
        }
        
        if(!totalRottenOranges) return 0;
        
        int cnt = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto it = q.front();
                int x = it.first;
                int y = it.second;
                q.pop();
                finalRottenOranges++;
                
                if(x+1<n && grid[x+1][y]==1) {q.push({x+1,y}); grid[x+1][y]=2;}
                if(x-1>=0 && grid[x-1][y]==1) {q.push({x-1,y}); grid[x-1][y]=2;}
                if(y+1<m && grid[x][y+1]==1) {q.push({x,y+1}); grid[x][y+1]=2;}
                if(y-1>=0 && grid[x][y-1]==1) {q.push({x,y-1}); grid[x][y-1]=2;}
            }
            cnt++;
        }
        if(finalRottenOranges==totalRottenOranges) return cnt-1;
        else return -1;
    }
};

// Approach 2 (in-place BFS) : O((n*m)^2) time and O(1) space complexity

// The secret in doing BFS traversal without a queue lies in the technique
// called in-place algorithm, which transforms input to solve the problem
// without using auxiliary data structure.


// The idea is that at each round of the BFS, we mark the cells to be visited
// in the input grid with a specific timestamp.

class Solution {
public:
    bool runRottingProcess(int timestamp, vector<vector<int>>& grid){
        int n = grid.size();
        int m = grid[0].size();
        
        vector<pair<int,int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        
        bool fl = false;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==timestamp){
                    for(int k=0;k<4;k++){
                        int x = i+dir[k].first;
                        int y = j+dir[k].second;
                        if(x<n && x>=0 && y<m && y>=0 && grid[x][y]==1){
                            grid[x][y]=timestamp+1;
                            fl=true;
                        }
                    }
                }
            }
        }
        return fl;
    }
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        int timestamp = 2;
        while(runRottingProcess(timestamp,grid)){
            timestamp++;
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1) return -1;
            }
        }
        
        return timestamp-2;
    }
};