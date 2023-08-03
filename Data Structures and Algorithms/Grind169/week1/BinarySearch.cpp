
// Problem link: https://leetcode.com/problems/binary-search/

// binary search - O(logn) time and O(1) space complexity
// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         if(nums.size()==0) return -1;
//         int l = 0, r = nums.size()-1;
//         while(l<=r){
//             int mid = l+(r-l)/2;
//             if(target==nums[mid]) return mid;
//             else if(target>nums[mid]) l=mid+1;
//             else r = mid-1;
//         }
//         return -1;
//     }
// };

// upper bound - O(logn) time and O(1) space complexity
// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         if(nums.size()==0) return -1;
//         int l = 0, r = nums.size();
//         while(l<r){
//             int mid = l+(r-l)/2;
//             if(target>=nums[mid]) l=mid+1;
//             else r = mid;
//         }
//         if(l>0 && nums[l-1]==target) return l-1;
//         else return -1;
//     }
// };

// lower bound - O(logn) time and O(1) space complexity
// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         if(nums.size()==0) return -1;
//         int l = 0, r = nums.size();
//         while(l<r){
//             int mid = l+(r-l)/2;
//             if(target<=nums[mid]) r=mid;
//             else l = mid+1;
//         }
//         if(l<nums.size() && nums[l]==target) return l;
//         else return -1;
//     }
// };

// use in-built fn - O(logn) time and O(1) space complexity
class Solution {
public:
    int search(vector<int>& nums, int target) {
        // Find the insertion position `idx`.
        int idx = upper_bound(nums.begin(), nums.end(), target) - nums.begin();

        if (idx > 0 && nums[idx - 1] == target) {
            return idx - 1;
        } else {
            return -1;
        }
    }
};