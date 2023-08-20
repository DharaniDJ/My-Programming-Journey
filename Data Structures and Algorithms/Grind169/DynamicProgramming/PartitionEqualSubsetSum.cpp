
// Problem Link : https://leetcode.com/problems/partition-equal-subset-sum/

// Approach 1 (recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    
    bool solve(vector<int>& nums, int idx, int k,int temp){
        if(idx==nums.size()){
            return k==temp;
        }
        
        if(temp>k) return false;
        
        bool taken = solve(nums,idx+1,k,temp+nums[idx]);
        bool notTaken = solve(nums,idx+1,k,temp);
        
        return (taken || notTaken);
    }
    
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int num:nums) sum+=num;
        if(sum%2) return false;
        int temp = 0;
        return solve(nums,0,sum/2,temp);
    }
};

// Approach 2 (Top Down DP- Memoization) : O(m*n) time and O(m*n) space complexity
class Solution{
    private: 
    bool solve(int idx,int target, vector<int>&arr, int n, int sum, vector<vector<int>> &dp){
        if(idx>=n) return false ;
        if(sum>target) return false;
        if(sum==target) return true;
        
        if(dp[idx][sum]!=-1) return dp[idx][sum];
        bool take=solve(idx+1,target,arr,n,sum+arr[idx],dp);
        bool nottake=solve(idx+1,target,arr,n,sum,dp);
        return dp[idx][sum]=(take || nottake);
    }
    public:
    bool canPartition(vector<int>& arr) {
        int sum=0;
        int n=arr.size();
        for(int i=0;i<n;i++){
            sum+=arr[i];
        }
        if(sum%2!=0) return false;
        int target=sum/2;
        vector<vector<int>> dp(n+1,vector<int>(target+1 , -1));
        return solve(0,target,arr,n,0,dp);
    }
};

// Approach 3 (Bottom up DP) : O(m*n) time and O(m*n) space complexity
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int num:nums) sum+=num;
        
        if(sum%2) return false;
        int k = sum/2;
        vector<vector<bool>> dp(n+1,vector<bool>(k+1,false));
        
        for(int i=0;i<=n;i++){
            dp[i][0]=true;
        }
        
        for(int j=1;j<=k;j++){
            dp[0][j]=false;
        }
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                dp[i][j]=dp[i-1][j];
                if(j>=nums[i-1]){
                    dp[i][j] = dp[i][j] || dp[i-1][j-nums[i-1]]; 
                }
            }
        }
        return dp[n][k];
    }
};

// Approach 4(Optimized DP - 1D array) : O(m*n) time and O(m) space complexity
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int num:nums) sum+=num;
        
        if(sum%2) return false;
        int k = sum/2;
        
        vector<bool> prev(k+1,false);
        vector<bool> cur(k+1,false);
        
        prev[0]=true;
        cur[0]=true;
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=k;j++){
                bool notTaken = prev[j];
                bool taken = false;
                if(j>=nums[i-1]) taken = prev[j-nums[i-1]];
                cur[j] = (notTaken || taken);
            }
            prev = cur;
        }
        return prev[k];
    }
};