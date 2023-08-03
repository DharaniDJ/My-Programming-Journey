
// Problem link: https://leetcode.com/problems/valid-parentheses/

// Brute force - O(n^2) time and O(1) space complexity
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         int n = nums.size();
//         for(int i=0;i<(n-1);i++){
//             for(int j=i+1;j<n;j++){
//                 if(nums[i]+nums[j]-target == 0) return {i,j};
//             }
//         }
//         return {};
//     }
// };


// One-pass Hash Table - O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        int n = nums.size();
        for(int i=0;i<n;i++){
            int k = target-nums[i];
            if(mp.find(k)!=mp.end()){
                return {mp[k],i};
            }
            mp[nums[i]]=i;
        }
        return {};
    }
};