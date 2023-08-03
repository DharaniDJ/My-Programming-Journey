
// Problem Link : https://leetcode.com/problems/house-robber

// Recursion (TLE): O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<int>& nums, int i){
        int n = nums.size();
        if(i>=n) return 0;

        int notInclude = solve(nums,i+1);
        int include = solve(nums,i+2);
        return max(notInclude,include+nums[i]);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();

        return solve(nums,0);

    }
};

// Recursion with memoization : O(n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<int>& nums, int i,vector<int> &dp){
        int n = nums.size();
        if(i>=n) return 0;

        if(dp[i]!=-1) return dp[i];
        int notInclude = solve(nums,i+1,dp);
        int include = solve(nums,i+2,dp);

        return dp[i]=max(notInclude,include+nums[i]);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,-1);

        return solve(nums,0,dp);
    }
};

// Bottom up DP : O(n) time and O(n) space complexity
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return nums[0];
        if(n==2) return max(nums[0],nums[1]);

        vector<int> dp(n,-1);
        dp[n-1] = nums[n-1];
        dp[n-2] = max(nums[n-2],nums[n-1]);

        for(int i=n-3;i>=0;i--){
            dp[i] = max(nums[i]+dp[i+2], dp[i+1]);
        }

        return dp[0];
    }
};

// Bottom up DP (space optimized) : O(n) time and O(1) space complexity
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n==1) return nums[0];
        if(n==2) return max(nums[0],nums[1]);

        int prev = nums[n-1];
        int cur = max(nums[n-1],nums[n-2]);

        for(int i=n-3;i>=0;i--){
            int temp = max(cur,nums[i]+prev);
            prev = cur;
            cur = temp;
        }

        return cur;
    }
};