
// Problem Link : https://leetcode.com/problems/next-permutation/

// Brute Force : O(n!) time and O(n) space complextiy
// we find out every possible permutation of list formed by the elements of the given array and find out the permutation which is
// just larger than the given one.

// C++ Library : O(n) time and O(1) space complexity
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(),nums.end());
    }
};

// Approach 2(single pass) : O(n) time and O(1) space complexity
// for any given sequence that is in descending order, no next larger permutation is possible.

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int start = -1;
        for(int i=n-2;i>=0;i--){
            if(nums[i+1]>nums[i]){
                start = i;
                break;
            }
        }
        if(start==-1){
            reverse(nums.begin(),nums.end());
        }else{
            for(int i=n-1;i>start;i--){
                if(nums[i]>nums[start]){
                    swap(nums[i],nums[start]);
                    break;
                }
            }
            sort(nums.begin()+start+1,nums.end());
        }
    }
};