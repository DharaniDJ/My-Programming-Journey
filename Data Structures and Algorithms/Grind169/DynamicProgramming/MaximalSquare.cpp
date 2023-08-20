
// Problem Link : https://leetcode.com/problems/maximal-square/

// Approach1(Brute Force)(TLE) : O((n*m)^2) time and O(1) space complexity
// where n = no. of rows and m = no. of cols
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        int max_sq = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1'){
                    int sq = 1;
                    bool fl = true;
                    while(sq+i<n && sq+j<m && fl){
                        for(int k=j;k<=sq+j;k++){
                            if(matrix[sq+i][k]=='0'){
                                fl=false;
                                break;
                            }
                        }

                        for(int k=i;k<=sq+i;k++){
                            if(matrix[k][sq+j]=='0'){
                                fl=false;
                                break;
                            }
                        }

                        if(fl){
                            sq++;
                        }
                    }
                    max_sq = max(max_sq,sq);
                }
            }
        }
        return (max_sq * max_sq);
    }
};


// Approach2(Bottom-Up DP) : O(n*m) time and O(n*m) space complexity
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> dp(n,vector<int>(m,0));
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0 || j==0){
                    if(matrix[i][j]=='1') dp[i][j]=1;
                    else dp[i][j]=0;
                }

                else if(matrix[i][j]=='1'){
                    dp[i][j]=min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]})+1;
                }else{
                    dp[i][j]=0;
                }
                ans=max(ans,dp[i][j]);
            }
        }
        return ans*ans;
    }
};

// Space Optimized DP : O(n*m) time and O(m) space complexity
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<int> dp(m+1,0);
        int prev = 0;
        int ans = 0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int temp = dp[j]; // saving the old/prev result for the next iteration
                if(matrix[i-1][j-1]=='1'){
                    // dp[j-1] is the new value which updated in the prev iteration
                    dp[j] = min({dp[j],dp[j-1],prev})+1;
                    ans = max(ans,dp[j]);
                }else{
                    dp[j]=0;
                }
                prev=temp;
            }
        }
        return ans*ans;
    }
};

-----------------------------------------
| prev                   |    dp[i]     |
-----------------------------------------
| new_dp[i-1]=dp[i-1]    |  new_dp[i]   |
-----------------------------------------