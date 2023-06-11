
// Problem Link : https://leetcode.com/problems/number-of-islands

// Approach 1 (DFS) : O(n*m) time and O(n*m) space complexity
class Solution {
public:
    void dfs(vector<vector<char>>& grid, int i, int j){
        int n = grid.size();
        int m = grid[0].size();

        if(i>=n || i<0 || j>=m || j<0 || grid[i][j]!='1') return;
        grid[i][j]='2';
        dfs(grid,i,j+1);
        dfs(grid,i,j-1);
        dfs(grid,i+1,j);
        dfs(grid,i-1,j);
        return;
    }
    int numIslands(vector<vector<char>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        int cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'){
                    cnt++;
                    dfs(grid,i,j);
                }
            }
        }
        return cnt;
    }
};

// Approach 2 (BFS) : O(n*m) time and O(min(n,m)) space complexity
class Solution {
public:
    bool check(int x, int y, int n, int m, vector<vector<char>>& grid){
        return (x<n && x>=0 && y<m && y>=0 && grid[x][y]=='1');
    }

    void bfs(vector<vector<char>>& grid, int i, int j){
        int n = grid.size();
        int m = grid[0].size();
        
        queue<pair<int,int>> q;
        q.push({i,j});
        grid[i][j]='2';
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            int x = it.first;
            int y = it.second;
            
            if(check(x+1,y,n,m,grid)) {q.push({x+1,y});grid[x+1][y]='2';}
            if(check(x,y+1,n,m,grid)) {q.push({x,y+1});grid[x][y+1]='2';}
            if(check(x-1,y,n,m,grid)) {q.push({x-1,y});grid[x-1][y]='2';}
            if(check(x,y-1,n,m,grid)) {q.push({x,y-1});grid[x][y-1]='2';}
        }
        return;
    }
    
    int numIslands(vector<vector<char>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();
        
        int cnt = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'){
                    bfs(grid,i,j);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

// Union Find Approach :  O(n*m) time and O(n*m) space complexity
class unionFind{
private:
    vector<int> parent;
    vector<int> rank;
    int cnt;
public:
    unionFind(vector<vector<char>> &grid){
        cnt = 0;
        int n = grid.size();
        int m = grid[0].size();
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'){
                    parent.push_back(i*m+j);
                    cnt++;
                }else{
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }
        
    int find(int i){
        if(parent[i]!=i) parent[i]=find(parent[i]);
        return parent[i];
    }

    void Union(int i, int j){
        int x = find(i);
        int y = find(j);
        if(x!=y){
            if(rank[x]>rank[y]){
                parent[y]=x;
            }else if(rank[x]<rank[y]){
                parent[x]=y;
            }else{
                parent[y]=x;
                rank[x]++;
            }
            cnt--;
        }
    }

    int getCount() const {
        return cnt;
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        unionFind uf(grid);
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='1'){
                    grid[i][j]='2';
                    if(i+1<n && grid[i+1][j]=='1') uf.Union(i*m+j,(i+1)*m+j);
                    if(i-1>=0 && grid[i-1][j]=='1') uf.Union(i*m+j,(i-1)*m+j);
                    if(j+1<m && grid[i][j+1]=='1') uf.Union(i*m+j,i*m+(j+1));
                    if(j-1>=0 && grid[i][j-1]=='1') uf.Union(i*m+j,i*m+(j-1));
                }
            }
        }
        return uf.getCount();
    }
};