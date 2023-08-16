
// Problem link : https://leetcode.com/problems/triangle/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion + Memoization) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int minPath(vector<vector<int>>& triangle, int i, int j, unordered_map<string,int> &dp){
        string temp = to_string(i)+":"+to_string(j);
        
        if(dp.count(temp)) return dp[temp];
        
        int path = triangle[i][j];
        
        if(i<triangle.size()-1){
            path+=min(minPath(triangle,i+1,j,dp),minPath(triangle,i+1,j+1,dp))
        }
        
        return dp[temp]=path;
    }
    
    int minimumTotal(vector<vector<int>>& triangle) {
        unordered_map<string,int> dp;
        return minPath(triangle,0,0,dp);
    }
};

// Approach2(Bottom-up DP) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        int ans = INT_MAX;
        for(int i=1;i<n;i++){
            for(int j=0;j<=i;j++){
                int temp = INT_MAX;
                if(j>0){
                    temp = triangle[i-1][j-1];
                }
                if(j<i){
                    temp = min(temp,triangle[i-1][j]);
                }

                triangle[i][j] = temp + triangle[i][j];
                if(i==n-1) ans = min(ans, triangle[i][j]);
            }
        }

        for(auto i : triangle[n-1]){
            ans = min(ans, i);
        }

        return ans;
    }
};

// Approach3(Bottom-up Reverse) : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        for(int i=n-2;i>=0;i--){
            for(int j=0;j<=i;j++){
                int temp = min(triangle[i+1][j],triangle[i+1][j+1]);
                triangle[i][j] += temp;
            }
        }

        return triangle[0][0];
    }
};