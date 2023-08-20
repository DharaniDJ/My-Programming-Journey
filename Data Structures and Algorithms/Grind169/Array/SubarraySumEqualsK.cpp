
// Problem Link : https://leetcode.com/problems/subarray-sum-equals-k/

// Brute Force : O(n^3) time and O(1) space complexity
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                int sum = 0;
                for(int k=i;k<=j;k++){
                    sum+=nums[k];
                }
                if(sum==k) ans++;
            }
        }
        return ans;
    }
};

// Prefix Sum : O(n^2) time and O(n) space complexity
public class Solution {
    public int subarraySum(int[] nums, int k) {
        int count = 0;
        for (int start = 0; start < nums.length; start++) {
            int sum=0;
            for (int end = start; end < nums.length; end++) {
                sum+=nums[end];
                if (sum == k)
                    count++;
            }
        }
        return count;
    }
}

// Carry Forward : O(n^2) time and O(1) space complexity
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = 0;

        for(int i=0;i<n;i++){
            int sum = 0;
            for(int j=i;j<n;j++){
                sum+=nums[j];
                if(sum==k) ans++;
            }
        }
        return ans;
    }
};

// Hashmap : O(n) time and O(n) space complexity
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();

        unordered_map<int,int> mp;
        int ans = 0;
        int sum = 0;
        for(int i=0;i<n;i++){
            sum+=nums[i];
            if(sum==k) ans++;
            if(mp.find(sum-k)!=mp.end()){
                ans+=mp[sum-k];
            }
            mp[sum]++;
        }
        return ans;
    }
};