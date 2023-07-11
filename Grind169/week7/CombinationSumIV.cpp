
// Problem Link : https://leetcode.com/problems/combination-sum-iv

// Approach(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int getSumCombo(vector<int> &nums, int target){
        if(target==0)return 1;
        if(target<0)return 0;

        int ans = 0;
        for(int i=0;i<nums.size();i++){
            ans+=getSumCombo(nums,target-nums[i]);
        }
        return ans;
    }
    int combinationSum4(vector<int>& nums, int target) {
        return getSumCombo(nums,target);
    }
};

// (Approach2)Top Down DP(Recursion + Memoization) : O(n) time and O(n) space complexity
class Solution {
public:
    int getSumCombo(vector<int> &nums, int target, vector<int> &dp){
        if(target==0)return 1;
        if(target<0)return 0;

        if(dp[target]!=-1) return dp[target];

        int ans = 0;
        for(int i=0;i<nums.size();i++){
            ans+=getSumCombo(nums,target-nums[i],dp);
        }
        return dp[target]=ans;
    }
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1,-1);
        return getSumCombo(nums,target,dp);
    }
};

// Approach3(Bottomup DP) : O(n) time and O(n) space complexity

// dp[i] where each element corresponds to the result of function combs(i), i.e. the number of combinations that sum up to the value of i.

// In the previous approach, to obtain the value of combs(target), we start off from the desired target value, and recursively reduce it down to the base case (i.e. target=0).

// In this approach though, we start from the base case (i.e. dp[0]) and then iteratively calcalate all the intermediate results until we reach the target value (i.e. dp[target]).

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        // minor optimization, sort nums
        // sort(begin(nums),end(nums));
        vector<int> dp(target+1,0);
        dp[0]=1;

        for(int comboSum=1;comboSum<=target;comboSum++){
            for(int num : nums){
                if(comboSum>=num){
                    dp[comboSum]+=dp[comboSum-num];
                }
                // minor optimizaton, early stopping
                // else{
                //     break;
                // }
            }
        }

        return dp[target];
    }
};