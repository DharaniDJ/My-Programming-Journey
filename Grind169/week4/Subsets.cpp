
// Problem Link : https://leetcode.com/problems/subsets/

// Cascading : : O(n * 2^n) time and O(n * 2^n) space for(temp vector) complexity
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return {{}};
        
        vector<vector<int>> res = {{}};
        vector<int> temp;
        int sz;
        for(int num : nums){
            sz = res.size();
            for(int i=0;i<sz;i++){
                temp = res[i];
                temp.push_back(num);
                res.push_back(temp);
            }
        }
        return res;
    }
};

// Recursion (Backtracking) : O(n * 2^n) time and O(n) space complexity
// We are using O(N) space to maintain temp, and are modifying temp in-place with backtracking.
class Solution {
public:
    
    void solve(vector<int> &nums, int i, vector<int> &temp, vector<vector<int>> &res){
        if(i==nums.size()){
            res.push_back(temp);
            return;
        }
        
        solve(nums,i+1,temp,res);
        
        temp.push_back(nums[i]);
        solve(nums,i+1,temp,res);
        temp.pop_back();
        return;
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> temp;
        solve(nums,0,temp,res);
        return res;
    }
};

// Bitmask : O(n * 2^n) time and O(n * 2^n) space for(temp vector) complexity
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        int k = (1<<n);
        for(int i=0;i<k;i++){
            vector<int> temp;
            for(int j=0;j<n;j++){
                if(i & (1<<j)){
                    temp.push_back(nums[j]);
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};