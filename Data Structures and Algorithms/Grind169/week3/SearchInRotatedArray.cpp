
// Problem Link : https://leetcode.com/problems/search-in-rotated-sorted-array/

// Approach 1 (Linear search) : O(n) time and O(1) space complexity
class Solution {
public:
    int search(vector<int>& nums, int target) {
        for(int i = 0;i<nums.size();i++){
            if(nums[i]==target) return i;
        }
        return -1;
    }
};

// Approach 2 (2 Pass Binary search) : O(logn) time and O(1) space complexity
class Solution {
public:
    int find_rotate_idx(vector<int>& nums, int left, int right){
        if(nums[left] < nums[right]) return 0;
        
        while(left <= right){
            int pivot = left + (right-left)/2;
            if(nums[pivot]>nums[pivot+1]) return pivot+1;
            else{
                if (nums[pivot] < nums[left]){
                    right = pivot-1;
                }else{
                    left = pivot+1;
                }
            }
        }
        return 0;
    }
    
    int search(vector<int>& nums, int left, int right, int target){
        while(left<=right){
            int pivot = left + (right-left)/2;
            if(nums[pivot]==target){
                return pivot;
            }else if(nums[pivot]<target){
                left = pivot+1;
            }else{
                right = pivot-1;
            }
        }
        return -1;
    }
    
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        if(n==1) return nums[0]==target ? 0 : -1;
        
        int idx = find_rotate_idx(nums,0,nums.size()-1);
        if(nums[idx]==target) return idx;
        if(idx==0) return search(nums,0,n-1,target);
        if(target<nums[0]) return search(nums,idx,n-1,target);
        return search(nums,0,idx,target);
    }
};

// Approach 3 (1 Pass Binary Search) : O(logn) time and O(1) space complexity
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int pivot = left+(right - left)/2;
            if(nums[pivot]==target) return pivot;
            else if(nums[pivot]>=nums[left]){
                if(nums[left]<=target && target<nums[pivot]) right = pivot-1;
                else left = pivot+1;
            }else{
                if(nums[pivot]<target && target<=nums[right]) left = pivot+1;
                else right = pivot-1;
            }
        }
        return -1;
    }
};