
// Problem Link: https://leetcode.com/problems/maximum-subarray/

// Brute Force: O(n^3) time and O(1) space complexity
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                int sum = 0;
                for(int k=i;k<=j;k++){
                    sum+=nums[k];
                }
                ans=max(ans,sum);
            }
        }
        return ans;
    }
};

// Optimized Brute Force : O(n^2) time and O(1) space complexity
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        for(int i=0;i<n;i++){
            int sum = 0;
            for(int j=i;j<n;j++){
                sum+=nums[j];
                ans=max(ans,sum);
            }
        }
        return ans;
    }
};

// DP, Kadane Algorithm : O(n) time and O(1) space complexity
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        int sum = 0;
        for(int i=0;i<n;i++){
            sum+=nums[i];
            ans=max(ans,sum);
            sum=max(sum,0);
        }
        return ans;
    }
};

// Divide and Conquer : O(n*logn) time and O(logn) space complexity
class Solution {
public:
    int solve(vector<int>& nums, int l, int r){
        if(l>r) return INT_MIN;
        
        int mid = l+(r-l)/2;
        int cur = 0;
        int leftBestSum = 0;
        int rightBestSum = 0;
        for(int i=mid-1;i>=l;i--){
            cur+=nums[i];
            leftBestSum=max(leftBestSum,cur);
        }
        
        cur = 0;
        for(int i=mid+1;i<=r;i++){
            cur+=nums[i];
            rightBestSum=max(rightBestSum,cur);
        }
        
        int temp = leftBestSum+rightBestSum+nums[mid];
        int left = solve(nums,l,mid-1);
        int right = solve(nums,mid+1,r);
        return max({left,right,temp});
    }
    int maxSubArray(vector<int>& nums) {
        return solve(nums,0,nums.size()-1);
    }
};