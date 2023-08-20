
// Problem Link: https://leetcode.com/problems/move-zeroes/

// Approach 1 (extra array) : O(n) time and O(n) space complexity

// Approach 2 (space optimal) : O(n) time andd O(1) space complexity
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int zero_cnt = 0;
        for(int i=n-1;i>=0;i--){
            if(nums[i]==0){
                zero_cnt++;
                nums.erase(nums.begin()+i);
            }
        }
        while(zero_cnt--){
            nums.push_back(0);
        }
        return;
    }
};

// Approach 3 (optimal with swap) : O(n) time and O(1) space complexity
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        for(int last_non_zero=0, cur=0; cur<n;cur++){
            if(nums[cur]==0){
                continue;
            }else{
                swap(nums[last_non_zero++],nums[cur]);
            }
        }
        return;
    }
};