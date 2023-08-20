
// Problem Link : https://leetcode.com/problems/house-robber/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int solve(vector<int> &nums, int idx){
        if(idx>=nums.size()) return 0;
        
        int k1 = solve(nums,idx+1);
        int k2 = solve(nums,idx+2);
        
        return max(k1,nums[idx]+k2);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        return solve(nums,0);
    }
};

// Approach2(Recursion + Memoization) : O(n) time and O(n) space complexity
class Solution {
    unordered_map<int,int> mp;
public:
    int solve(vector<int> &nums, int idx){
        if(idx>=nums.size()) return 0;

        if(mp.count(idx)) return mp[idx];

        int k1 = solve(nums,idx+1);
        int k2 = solve(nums,idx+2);

        return mp[idx]=max(k1,nums[idx]+k2);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        return solve(nums,0);
    }
};

// Approach3(DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if(n==1) return nums[0];
        vector<int> dp(n,0);

        dp[0]=nums[0];
        dp[1]=max(nums[0],nums[1]);

        for(int i=2;i<n;i++){
            dp[i] = max(dp[i-1],dp[i-2]+nums[i]);
        }

        return dp[n-1];
    }
};

// Approach4(DP + space optimization) : O(n) time and O(1) space complexity
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if(n==1) return nums[0];

        int prev = nums[0];
        int cur = max(nums[0],nums[1]);

        for(int i=2;i<n;i++){
            int next = max(cur,prev+nums[i]);
            prev = cur;
            cur = next;
        }

        return cur;
    }
};