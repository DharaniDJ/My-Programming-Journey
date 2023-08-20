
// Problem Link : https://leetcode.com/problems/jump-game/

// Approach1(recursion)(TLE) : (2^n) time and O(n) space complexity
class Solution {
public:

    bool solve(vector<int> &nums, int i, int n){
        if(i>=n) return true;
        if(nums[i]==0) return false;
        int maxLen = nums[i];
        bool fl = false;
        for(int j=1;j<=maxLen;j++){
            fl |= solve(nums,i+j,n);
        }
        return fl;
    }
    bool canJump(vector<int>& nums) {
        return solve(nums,0,nums.size()-1);
    }
};

// Approach2(Top-Down DP) : O(n^2) time and O(2n) space complexity
class Solution {
public:

    bool solve(vector<int> &nums, int i, int n,vector<int> &dp){
        if(i>=n) return true;
        if(dp[i]!=-1){
            return dp[i]==0 ? false : true;
        }

        if(nums[i]==0){
            dp[i]=0;
            return false;
        }

        int finalPos = min(i+nums[i],n);

        for(int j=i+1;j<=finalPos;j++){
            if(dp[j]==1 || solve(nums,j,n,dp)) {
                dp[j]=1;
                return true;
            }else{
                dp[j]=0;
            }
        }
        dp[i]=0;
        return false;;
    }
    bool canJump(vector<int>& nums) {
        vector<int> dp(nums.size(),-1);
        return solve(nums,0,nums.size()-1,dp);
    }
};

// Approach3(Bottom-up DP) : O(n^2) space and O(n) space complexity
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,-1);
        dp[0]=1;

        for(int i=1;i<n;i++){
            bool fl = false;
            for(int j=i-1;j>=0;j--){
                if(dp[j]==0) continue;
                if(j+nums[j]>=i){
                    dp[i]=1;
                    fl = true;
                    break;
                }
            }
            if(!fl) dp[i]=0;
        }
        return dp[n-1];
    }
};

// Greedy Approach : O(n) time and O(1) space complexity

// From a given position, when we try to see if we can jump to a GOOD position,
// we only ever use one - the first one (see the break statement). In other words, the left-most one.
// If we keep track of this left-most GOOD position as a separate variable,
// we can avoid searching for it in the array. Not only that, but we can stop using the array altogether.
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int leftGoodIndex = n-1;
        
        for(int i=n-1;i>=0;i--){
            // we check if there is a potential jump that reaches a GOOD index
            // If we can reach a GOOD index, then our position is itself GOOD.
            // Also, this new GOOD position will be the new leftmost GOOD index.
            if(i+nums[i]>=leftGoodIndex){
                leftGoodIndex = i;
            }
        }
        
        return leftGoodIndex==0;
    }
};