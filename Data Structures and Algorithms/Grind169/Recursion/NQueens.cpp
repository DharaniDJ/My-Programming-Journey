
// Problem Link: https://leetcode.com/problems/n-queens

// Approach1(Backtracking) : O(n!) time and O(n^2) space complexity
class Solution {
public:
    bool issafe(int row, int col, vector<string> &temp, int n){
        int i = row;
        int j = col;

        while(i>=0 && j>=0){
            if(temp[i--][j--]=='Q') return false;
        }

        i = row;
        j = col;
        while(j<n && i>=0){
            if(temp[i--][j++]=='Q') return false;
        }

        i = row;
        while(i>=0){
            if(temp[i--][col]=='Q') return false;
        }

        return true;
    }
    void solve(int row, vector<string> &temp, vector<vector<string>> &res,int n){
        if(row==n){
            res.push_back(temp);
            return;
        }

        for(int col=0;col<n;col++){
            if(issafe(row,col,temp,n)){
                temp[row][col]='Q';
                solve(row+1,temp,res,n);
                temp[row][col]='.';
            }
        }
        return;
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> temp(n,string(n,'.'));
        solve(0,temp,res,n);
        return res;
    }
};

// Another approach : O(n!) time and O(n^2) space complexity
class Solution {
public:

    void solve(int row, vector<bool> &ud, vector<bool> &ld, vector<bool> &col, vector<string> &temp, vector<vector<string>> &res, int n){
        if(row==n){
            res.push_back(temp);
            return;
        }

        for(int i=0;i<n;i++){
            if(!ld[i+row] && !ud[row-i+n-1] && !col[i]){
                temp[row][i]='Q';
                ld[i+row] = true;
                ud[row-i+n-1] = true;
                col[i]=true;
                solve(row+1,ud,ld,col,temp,res,n);
                temp[row][i]='.';
                ld[i+row] = false;
                ud[row-i+n-1] = false;
                col[i]=false;
            }
        }
        return;
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> temp(n,string(n,'.'));
        vector<bool> ud(2*n - 1, false);
        vector<bool> ld(2*n - 1, false);
        vector<bool> col(n,false);
        solve(0,ud,ld,col,temp,res,n);
        return res;
    }
};