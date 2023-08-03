
// Problem Link: https://leetcode.com/problems/squares-of-a-sorted-array/

// Approach 1 (Brute Force) : O(n*logn) time and O(1) space complexity
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            nums[i] = nums[i]*nums[i];
        }
        sort(nums.begin(),nums.end());
        return nums;
    }
};

// Two pointer : O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        
        int i = 0;
        int n = nums.size();
        int j = n-1;
        int k = n-1;
        vector<int> res(n);
        
        while(i<=j){
            if(abs(nums[i]) > abs(nums[j])){
                res[k--]=nums[i]*nums[i];
                i++;
            }else{
                res[k--]=nums[j]*nums[j];
                j--;
            }
        }
        return res;
    }
};