
// Problem Link : https://leetcode.com/problems/set-matrix-zeroes/

// Additional Memory Approach : O(n*m) time and O(n+m) space complexity
// If any cell of the matrix has a zero we can record its row and column number.
// All the cells of this recorded row and column can be marked zero in the next iteration.
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> row(n,0);
        vector<int> col(m,0);

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]==0){
                    row[i]=1;
                    col[j]=1;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(row[i]==1 || col[j]==1){
                    matrix[i][j]=0;
                }
            }
        }

    }
};

// Space optimized Approach : O(n*m) time and O(1) space complexity
// Rather than using additional variables to keep track of rows and columns to be reset, we use the matrix itself as the indicators.
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        int col0=0;
        for(int i=0;i<n;i++){
            if(matrix[i][0]==0) col0=1;
            for(int j=1;j<m;j++){
                if(matrix[i][j]==0){
                    matrix[i][0]=0;
                    matrix[0][j]=0;
                }
            }
        }

        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(matrix[i][0]==0 || matrix[0][j]==0) matrix[i][j]=0;
            }
        }

        if(matrix[0][0]==0){
            for(int j=1;j<m;j++) matrix[0][j]=0;
        }

        if(col0){
            for(int i=0;i<n;i++) matrix[i][0]=0;
        }
    }
};
