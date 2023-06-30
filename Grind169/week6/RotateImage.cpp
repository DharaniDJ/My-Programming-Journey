
// Problem Link : https://leetcode.com/problems/rotate-image/

// Approach 1(Rotate Groups of Four Cells) : O(n^2) time and O(1) space complexity
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int k = n/2;
        int r = n%2;

        for(int i=0;i<(k+r);i++){
            for(int j=0;j<k;j++){
                int temp = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - j - 1];
                matrix[n - 1 - i][n - j - 1] = matrix[j][n - 1 -i];
                matrix[j][n - 1 - i] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }
    }
};

// Approach2(Transpose + reverse rows) : O(n^2) time and O(1) space complexity
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<i;j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(int i=0;i<n;i++){
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};