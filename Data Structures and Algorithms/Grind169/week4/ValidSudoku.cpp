
// Problem Link : https://leetcode.com/problems/valid-sudoku

// Brute Force : O(n^3) time and O(1) space complexity
class Solution {
public:
    bool valid(vector<vector<char>>& board, int row, int col, char ch){
        for(int i=0;i<board.size();i++){
            if(board[row][i]==ch) return false;
            if(board[i][col]==ch) return false;
        }

        int l = row - row%3;
        int m = col - col%3;
        for(int i=l;i<l+3;i++){
            for(int j=m;j<m+3;j++){
                if(board[i][j]==ch) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(board[i][j]!='.'){
                    char ch = board[i][j];
                    board[i][j]='.';
                    if(!valid(board,i,j,ch)){
                        return false;
                    }else{
                        board[i][j]=ch;
                    }
                }
            }
        }
        return true;
    }
};

// Hashset : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();
        vector<unordered_set<int>> row(n),col(n),box(n);
        
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]=='.') continue;
                int x = 3*(i/3)+(j/3);
                if(row[i].insert(board[i][j]).second==false) return false;
                if(col[j].insert(board[i][j]).second==false) return false;
                if(box[x].insert(board[i][j]).second==false) return false;
            }
        }
        return true;
    }
};

// Array with fixed length : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int N = 9;

        // Use a vector to record the status
        std::vector<std::vector<int>> rows(N, std::vector<int>(N, 0));
        std::vector<std::vector<int>> cols(N, std::vector<int>(N, 0));
        std::vector<std::vector<int>> boxes(N, std::vector<int>(N, 0));

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                // Check if the position is filled with a number
                if (board[r][c] == '.') {
                    continue;
                }
                int pos = board[r][c] - '1';

                // Check the row
                if (rows[r][pos] == 1) {
                    return false;
                }
                rows[r][pos] = 1;

                // Check the column
                if (cols[c][pos] == 1) {
                    return false;
                }
                cols[c][pos] = 1;

                // Check the box
                int idx = (r / 3) * 3 + c / 3;
                if (boxes[idx][pos] == 1) {
                    return false;
                }
                boxes[idx][pos] = 1;
            }
        }
        return true;
    }
};

// Bitmasking : O(n^2) time and O(n) space complexity
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int N = 9;

        // Use a vector to record the status
        vector<int> rows(N, 0);
        vector<int> cols(N, 0);
        vector<int> boxes(N,0);

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                // Check if the position is filled with a number
                if (board[r][c] == '.') {
                    continue;
                }
                int val = board[r][c] - '1';
                int pos = (1<<val);

                // Check the row
                if (rows[r] & pos) {
                    return false;
                }
                rows[r] |= pos;

                // Check the column
                if (cols[c] & pos) {
                    return false;
                }
                cols[c] |= pos;

                // Check the box
                int idx = (r / 3) * 3 + c / 3;
                if (boxes[idx] & pos) {
                    return false;
                }
                boxes[idx] |= pos;
            }
        }
        return true;
    }
};