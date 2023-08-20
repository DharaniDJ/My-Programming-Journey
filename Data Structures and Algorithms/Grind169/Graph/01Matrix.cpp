
// Problem Link : 

// Brute Force : O((n*m)^2) time and O(1) space complexity
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0)
            return matrix;
        int m = matrix[0].size();
        vector<vector<int>> dist(n, vector<int> (m, INT_MAX));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                } else {
                    for (int k = 0; k < n; k++) {
                        for (int l = 0; l < m; l++) {
                            if (matrix[k][l] == 0) {
                                int dist_01 = abs(k - i) + abs(l - j);
                                dist[i][j] = min(dist[i][j], abs(k - i) + abs(l - j));
                            }
                        }
                    }
                }
            }
        }
        return dist;
    }
};

// Approach2(BFS) : O(n*m) time and O(n*m) space(queue) complexity

// Intuition

// A better brute force:
// Looking over the entire matrix appears wasteful and hence, we can use BFS
// to limit the search to the nearest 0 found for each 1. As soon as a 0 appears
// during the BFS, we know that the 0 is the closest, and hence, we move to the next 1.

// Think again:
// But, in this approach, we will only be able to update the distance of one 1
// using one BFS, which could in fact, result in slightly higher complexity than
// the brute force approach. But hey, this could be optimized if we start the BFS
// from 0s and thereby, updating the distances of all the 1s in the path.

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0)
            return matrix;
        int m = matrix[0].size();
        vector<vector<int>> dist(n, vector<int> (m, INT_MAX));
        queue<pair<int,int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                    q.push({i,j});
                }
            }
        }
        
        int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
        while(!q.empty()){
            auto cur = q.front();
            q.pop();
            for(int i=0;i<4;i++){
                int x = cur.first+dir[i][0];
                int y = cur.second+dir[i][1];
                if(x<n && y<m && x>=0 && y>=0){
                    if(dist[x][y]>dist[cur.first][cur.second]+1){
                        dist[x][y]=dist[cur.first][cur.second]+1;
                        q.push({x,y});
                    }
                }
            }
        }
        return dist;
    }
};

// Approach3 (DP) : O(n*m) time and O(1) space complexity
// Intuition

// The distance of a cell from 0 can be calculated if we know
// the nearest distance for all the neighbors, in which case the
// distance is the minimum distance of any neighbor + 1.
// And, instantly, the words that come to mind are DP!!
// From each 1, the minimum path to 0 could be in any direction.
// So, we need to check all the 4 directions. In one iteration from
// top to bottom, we can check left and top directions, and we need
// another iteration from bottom to top to check for right and bottom directions.


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0)
            return matrix;
        int m = matrix[0].size();
        vector<vector<int>> dist(n, vector<int> (m, INT_MAX - 100000));
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]==0){
                    dist[i][j]=0;
                }else{
                    if (i > 0)
                        dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                    if (j > 0)
                        dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                if(i+1<n) dist[i][j] = min(dist[i][j],dist[i+1][j]+1);
                if(j+1<m) dist[i][j] = min(dist[i][j],dist[i][j+1]+1);
            }
        }
        return dist;
    }
};