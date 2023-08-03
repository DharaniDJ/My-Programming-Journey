
// Problem Link : https://leetcode.com/problems/longest-increasing-subsequence/

// DP : O(n^2) space and O(n) time complexity
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp(n,1);
        
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]) dp[i] = max(dp[i],dp[j]+1);
            }
        }
        return *max_element(dp.begin(),dp.end());
    }
};

// DP + Binary search : O(n*logn) time and O(n) space complexity

// dp[i] -> smallest ending element for an increasing subsequence of length i;
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp;
        dp.push_back(nums[0]);
        for(int i=1;i<n;i++){
            if(nums[i]>dp.back()){
                dp.push_back(nums[i]);
            }else{
                int pos = lower_bound(dp.begin(),dp.end(),nums[i])-dp.begin();
                dp[pos] = nums[i];
            }
        }
        return dp.size();
    }
};