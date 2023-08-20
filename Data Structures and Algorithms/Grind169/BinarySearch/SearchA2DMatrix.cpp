
// Problem Link : https://leetcode.com/problems/search-a-2d-matrix/

// Approach1(Binary search on each row) : O(n*logm) time and O(1) space complexity
class Solution {
public:
    bool findElement(vector<int> & row, int target){
        int m = row.size();
        
        int l = 0;
        int r = m;
        while(l+1 <= r){
            int mid = (l+r)/2;
            if(row[mid]==target) return true;
            else if(row[mid]>target){
                r=mid;
            }else{
                l=mid+1;
            }
        }
        return false;
    }

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        for(int i=0;i<n;i++){
            if(findElement(matrix[i],target)) return true;
        }
        return false;
    }
};


// Approach2 (Pointer technique): O(n+m) time and O(1) space complexity
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int i=n-1,j=0;
        while(i>=0 && j<m){
            if(matrix[i][j]==target) return true;

            if(matrix[i][j]>target){
                i--;
            }else{
                j++;
            }
        }
        return false;
    }
};

// Approach3(Improved BS) : O(logn + logm) time and O(1) space complexity
//  input matrix m x n could be considered as a sorted array of length m x n

class Solution {
public:

    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int l = 0;
        int r = n*m;

        while(l+1<=r){
            int mid = (l+r)/2;
            int i = mid/m;
            int j = mid%m;
            if(matrix[i][j]==target) return true;

            if(matrix[i][j]>target){
                r=mid;
            }else{
                l=mid+1;
            }
        }
        return false;
    }
};