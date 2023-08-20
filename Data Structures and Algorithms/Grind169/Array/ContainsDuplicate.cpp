
// Problem Link: https://leetcode.com/problems/contains-duplicate/

// Brute Force Approach: O(n^2) time and O(1) space complexity
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(nums[i]==nums[j]) return true;
            }
        }
        return false;
    }
};

// Sorting: O(n*logn) time and O(1) space complexity
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        for(int i=0;i<(n-1);i++){
            if(nums[i]==nums[i+1]) return true;
        }
        return false;
    }
};

// Hast set: O(n) time and O(n) space complexity
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set<int> s;
        for(int i:nums){
            if(s.count(i)) return true;
            s.insert(i);
        }
        return false;
    }
};