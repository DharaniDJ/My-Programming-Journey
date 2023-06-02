
// Problem Link : https://leetcode.com/problems/product-of-array-except-self/

// Prefix and Suffix product list: O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n,1);
        vector<int> suf(n,1);
        for(int i=1;i<n;i++){
            pre[i]=pre[i-1]*nums[i-1];
        }
        for(int i=n-2;i>=0;i--){
            suf[i]=suf[i+1]*nums[i+1];
        }
        for(int i=0;i<n;i++){
            pre[i]*=suf[i];
        }
        return pre;
    }
};

// O(1) space approach

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,1);
        
        for(int i=1;i<n;i++) res[i]=res[i-1]*nums[i-1];
        int temp = 1;
        for(int i=n-1;i>=0;i--){
            res[i] = res[i]*temp;
            temp = temp*nums[i];
        }
        return res;
    }
};