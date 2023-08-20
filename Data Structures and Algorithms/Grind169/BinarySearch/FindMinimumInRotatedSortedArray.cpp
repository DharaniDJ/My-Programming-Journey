
// Problem Link : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array

// Approach1(Binary search) : O(logn) time and O(1) space complexity
class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if(nums[0]<nums[n-1]) return nums[0];

        int l = 0;
        int r = n-1;
        while(l+1<r){
            int mid = l+(r-l)/2;
            cout << nums[mid] << ',';
            if(nums[mid]>nums[l] && nums[mid]>nums[r]){
                l = mid;
            }else if(nums[mid]<nums[l] && nums[mid]<nums[r]){
                r = mid;
            }
        }
        return nums[r];
    }
};

