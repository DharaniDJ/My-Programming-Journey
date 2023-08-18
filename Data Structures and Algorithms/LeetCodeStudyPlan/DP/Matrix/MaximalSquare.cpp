
// Problem Link : https://leetcode.com/problems/maximal-square/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Brute Force) : O((m*n)^2) time and O(1) space complexity

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        int mxLen = 0;
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1'){
                    int ln = 1;
                    bool fl = true;
                    while(i+ln<n && j+ln<m && fl){
                        for(int x=i;x<=i+ln;x++){
                            if(matrix[x][j+ln]=='0'){
                                fl = false;
                                break;
                            }
                        }
                        
                        for(int y=j;y<=j+ln;y++){
                            if(matrix[i+ln][y]=='0'){
                                fl = false;
                                break;
                            }
                        }
                        if(fl) ln++;
                    }    
                    mxLen = max(mxLen,ln);
                }
            }
        }
        
        return (mxLen*mxLen);
    }
};

// Approach2(DP) : O(n*m) time and O(n*m) space complexity
// Intuition: consider each element as bottom-right element in a square block
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        vector<vector<int>> dp(n,vector<int>(m,0));
        
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1'){
                    if(i==0 || j==0) dp[i][j]=1;
                    else dp[i][j] = min({dp[i-1][j-1],dp[i-1][j],dp[i][j-1]})+1;
                }
                ans = max(ans,dp[i][j]);
            }
        }
        
        return (ans*ans);
    }
};

// Approach3(DP+Space Optimization) : O(n*m) time and O(m) space complexity
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        
        vector<int> dp(m,0);
        
        int ans = 0;
        int prev = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int temp = dp[j]; // saving the old/prev result for future
                if(matrix[i][j]=='1'){
                    if(j==0) dp[j]=1;
                    else{
                        dp[j] = min({dp[j-1],dp[j],prev})+1;
                    }
                    ans = max(ans,dp[j]);
                }else{
                    dp[j] = 0;
                }
                prev = temp;
            }
            
        }
        
        return (ans*ans);
    }
};