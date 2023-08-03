
// Problem Link: https://leetcode.com/problems/single-number/

// Brute Force : O(n^2) time and O(1) space complexity
// class Solution {
// public:
//     int singleNumber(vector<int>& nums) {
//         int n = nums.size();
//         for(int i=0;i<n;i++){
//             int cnt = 0;
//             for(int j=0;j<n;j++){
//                 if(nums[i]==nums[j]) cnt++;
//                 if(cnt==2) break;
//             }
//             if(cnt==1) return nums[i];
//         }
//         return -1;
//     }
// };

// Hash map : O(n) time and O(n) space complexity
// class Solution {
// public:
//     int singleNumber(vector<int>& nums) {
//         unordered_map<int,int> mp;
//         for(int i:nums) mp[i]++;
//         for(int i:nums){
//             if(mp[i]==1) return i;
//         }
//         return -1;
//     }
// };

// Bit manipulation : O(n) time and O(1) space complexity
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for(int i:nums) ans = ans^i;
        return ans;
    }
};