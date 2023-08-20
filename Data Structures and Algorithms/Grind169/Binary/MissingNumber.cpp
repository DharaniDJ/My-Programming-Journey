
// Problem Link: https://leetcode.com/problems/missing-number/

// Brute Force : O(n^2) time and O(1) space complexity
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<=n;i++){
            bool fl = false;
            for(int x:nums){
                if(x==i){
                    fl=true;
                    break;
                }
            }
            if(!fl) return i;
        }
        return -1;
    }
};

// Sorting: O(n*logn) time and O(1) space complexity
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        for(int i=0;i<n;i++){
            if(i!=nums[i]) return i;
        }
        return n;
    }
};

// Hashset : O(n) time and O(1) space complexity
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> s;
        for(int i:nums) s.insert(i);
        for(int i=0;i<=n;i++){
            if(s.count(i)==0) return i;
        }
        return -1;
    }
};

// Bit Manipulation : O(n) time and O(1) space complexity
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for(int i=0;i<=n;i++){
            if(i!=n){
                ans^=nums[i];
            }
            ans^=i;
        }
        return ans;
    }
};

// Guass Formula (sum of n natural no.) : O(n) time and O(1) space complexity
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(int i:nums) sum+=i;
        return (n*(n+1)/2)-sum;
    }
};