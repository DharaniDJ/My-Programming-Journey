
// Problem Link :

// Backtracking : O(n * 3^l) time and O(l) space complexity
// where N is the number of cells in the board and L is the length of the word to be matched.

// For the backtracking function, initially we could have at most 4 directions to explore,
// but further the choices are reduced into 3 (since we won't go back to where we come from).

class Solution {
public:
    bool dfs(vector<vector<char>>& board, int i, int j, string &word, int idx){
        if(word.size()==idx) return true;

        int n = board.size();
        int m = board[0].size();

        if(i>=n || j>=m || i<0 || j<0 || board[i][j]!=word[idx]) return false;

        char tmp = board[i][j];
        board[i][j]='#';

        bool res = dfs(board,i+1,j,word,idx+1) || dfs(board,i,j+1,word,idx+1) || dfs(board,i,j-1,word,idx+1) || dfs(board,i-1,j,word,idx+1);

        board[i][j]=tmp;
        return res;

    }
    bool exist(vector<vector<char>>& board, string word) {

        if(word=="") return false;

        int n = board.size();
        int m = board[0].size();
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dfs(board,i,j,word,0)) return true;
            }
        }

        return false;
    }
};