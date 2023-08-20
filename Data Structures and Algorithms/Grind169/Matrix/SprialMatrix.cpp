
// Problem Link : 

// Brute Force : O(n*m) time and O(1) space complexity
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int n = matrix.size();
        int m = matrix[0].size();
        int l=0,r=m-1,u=0,d=n-1;
        int dir = 0;
        
        while(u<=d && l<=r){
                if(dir==0){
                    for(int i=l;i<=r;i++){
                        res.push_back(matrix[u][i]);
                    }
                    u++;
                }
                else if(dir==1){
                    for(int i=u;i<=d;i++){
                        res.push_back(matrix[i][r]);
                    }
                    r--;
                }
                else if(dir==2){
                    for(int i=r;i>=l;i--){
                        res.push_back(matrix[d][i]);
                    }
                    d--;
                }
                else if(dir==3){
                    for(int i=d;i>=u;i--){
                        res.push_back(matrix[i][l]);
                    }
                    l++;
                }
            dir = (dir+1)%4;
        }
        return res;
    }
};

// Brute force method ( different approach ) : O(n*m) time and O(1) space complexity
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int n = matrix.size();
        int m = matrix[0].size();
        int l=0,r=m-1,u=0,d=n-1;
        int dir = 0;
        
        while(res.size()<n*m){
            for(int i=l;i<=r;i++){
                res.push_back(matrix[u][i]);
            }
            
            for(int i=u+1;i<=d;i++){
                res.push_back(matrix[i][r]);
            }

            if(u!=d){
                for(int i=r-1;i>=l;i--){
                    res.push_back(matrix[d][i]);
                }
            }
            
            if(l!=r){
                for(int i=d-1;i>u;i--){
                    res.push_back(matrix[i][l]);
                }
            }
            l++;
            r--;
            u++;
            d--;
        }
        return res;
    }
};

// Using single variable : O(n*m) time and O(1) space complexity
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        vector<int> ans;
        int st = 0;
        int sz = m * n;
        while (ans.size() < sz) {
            for (int i = st; ans.size() < sz && i < m - st; i++) {
                ans.push_back(mat[st][i]);
            }
            for (int i = st + 1; ans.size() < sz && i < n - st; i++) {
                ans.push_back(mat[i][m - st - 1]);
            }
            for (int i = m - 2 - st; ans.size() < sz && i >= st; i--) {
                ans.push_back(mat[n - 1 - st][i]);
            }
            for (int i = n - 2 - st; ans.size() < sz && i >= st + 1; i--) {
                ans.push_back(mat[i][st]);
            }
            st++;
        }
        return ans;
    }
};

// mark visited elements : O(n*m) time and O(1) space complexity
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> res;
        
        // Four directions that we will move: right, down, left, up.
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        // Initial direction: moving right.
        int currentDirection = 0;
        // The number of times we change the direction.
        int changeDirection = 0;
        int row = 0;
        int col = 0;
        
        res.push_back(matrix[row][col]);
        matrix[row][col] = 101;
        
        while(changeDirection<2){
            while (row + directions[currentDirection][0] >= 0 &&
                   row + directions[currentDirection][0] < n &&
                   col + directions[currentDirection][1] >= 0 &&
                   col + directions[currentDirection][1] < m &&
                   matrix[row + directions[currentDirection][0]]
                   [col + directions[currentDirection][1]] != 101){
                changeDirection = 0;
                row = row + directions[currentDirection][0];
                col = col + directions[currentDirection][1];
                res.push_back(matrix[row][col]);
                matrix[row][col] = 101;
            }
            currentDirection = (currentDirection + 1) % 4;
            changeDirection++;

        }
        return res;
    }
};