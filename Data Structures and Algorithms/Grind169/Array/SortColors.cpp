
// Problem Link: https://leetcode.com/problems/sort-colors/

// Approach1 (Dutch National Flag(DNF) Algo) : O(n) time and O(1) space complexity
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int l = 0;
        int m = 0;
        int r = nums.size()-1;
        
        while(m<=r){
            switch(nums[m]){
                case 0:{
                    swap(nums[l],nums[m]);
                    l++;
                    m++;
                    break;
                }
                case 1:{
                    m++;
                    break;
                }
                case 2:{
                    swap(nums[m],nums[r]);
                    r--;
                    break;
                }
            }
        }
    }
};