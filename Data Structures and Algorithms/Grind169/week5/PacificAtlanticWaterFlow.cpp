
// Problem Link : 

// DFS
class Solution {
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> heights;
    int n, m;
public:

    void dfs(vector<vector<bool>> &ocean, int i, int j){
        // This cell is reachable
        ocean[i][j]=true;

        for(int d=0;d<4;d++){
            int x = i+dir[d][0];
            int y = j+dir[d][1];

            // Check if new cell is within bounds
            if(x>=n || y>=m || x<0 || y<0) continue;
            // Check that the new cell hasn't already been visited
            if(ocean[x][y]) continue;
            // Check that the new cell has a higher or equal height. so that we can sure, it will flow into the ocean 
            if(heights[x][y]<heights[i][j]) continue;
            // If we've gotten this far, that means the new cell is reachable
            dfs(ocean,x,y);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> ans;
        n = heights.size();
        m = heights[0].size();
        this->heights = heights;
        vector<vector<bool>> pacific(n,vector<bool>(m,false));
        vector<vector<bool>> atlantic(n,vector<bool>(m,false));

        for(int i=0;i<n;i++){
            dfs(pacific,i,0);
            dfs(atlantic,i,m-1);
        }

        for(int j=0;j<m;j++){
            dfs(pacific,0,j);
            dfs(atlantic,n-1,j);
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(pacific[i][j] && atlantic[i][j]) ans.push_back({i,j});
            }
        }

        return ans;
    }
};

// BFS
class Solution {
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> heights;
    int n, m;
public:

    void bfs(vector<vector<bool>> &ocean, int i, int j){
        // This cell is reachable
        ocean[i][j]=true;
        queue<pair<int,int>> q;
        q.push({i,j});

        while(!q.empty()){
            auto f = q.front();
            i = f.first;
            j = f.second;
            q.pop();
            for(int d=0;d<4;d++){
                int x = i+dir[d][0];
                int y = j+dir[d][1];

                // Check if new cell is within bounds
                if(x>=n || y>=m || x<0 || y<0) continue;
                // Check that the new cell hasn't already been visited
                if(ocean[x][y]) continue;
                // Check that the new cell has a higher or equal height. so that we can sure, it will flow into the ocean 
                if(heights[x][y]<heights[i][j]) continue;
                // If we've gotten this far, that means the new cell is reachable
                ocean[x][y]=true;
                q.push({x,y});
            }
        }

    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> ans;
        n = heights.size();
        m = heights[0].size();
        this->heights = heights;
        vector<vector<bool>> pacific(n,vector<bool>(m,false));
        vector<vector<bool>> atlantic(n,vector<bool>(m,false));

        for(int i=0;i<n;i++){
            bfs(pacific,i,0);
            bfs(atlantic,i,m-1);
        }

        for(int j=0;j<m;j++){
            bfs(pacific,0,j);
            bfs(atlantic,n-1,j);
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(pacific[i][j] && atlantic[i][j]) ans.push_back({i,j});
            }
        }

        return ans;
    }
};