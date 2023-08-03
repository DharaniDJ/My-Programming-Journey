
// Problem Link : https://leetcode.com/problems/shortest-path-to-get-food/

// BFS : O(n*m) time and O(n*m) space complexity
class Solution {
    int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
public:
    int bfs(vector<vector<char>> &grid, int i, int j){
        int n = grid.size();
        int m = grid[0].size();

        int ans = 0;
        queue<pair<int,int>> q;
        q.push({i,j});
        grid[i][j]='$';

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto f = q.front();
                q.pop();
                i = f.first;
                j = f.second;

                for(int d=0;d<4;d++){
                    int x = i+dir[d][0];
                    int y = j+dir[d][1];

                    if(x>=n || y>=m || x<0 || y<0 || grid[x][y]=='X' || grid[x][y]=='$') continue;
                    if(grid[x][y]=='#') return ans+1;

                    q.push({x,y});
                    grid[x][y]='$';
                }

            }
            ans++;
        }
        return -1;
    }

    int getFood(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]=='*') return bfs(grid,i,j);
            }
        }
        return -1;
    }
};