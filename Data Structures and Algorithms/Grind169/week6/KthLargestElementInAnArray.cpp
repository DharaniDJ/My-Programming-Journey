
// Problem Link : https://leetcode.com/problems/kth-largest-element-in-an-array/

// Approach1(sorting) : O(nlogn) time and O(logn) space complexity
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        sort(nums.begin(),nums.end());
        return nums[n-k];
    }
};

// Approach2(MinHeap): O(nlogk) time and O(k) space complexity
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        
        priority_queue<int,vector<int>,greater<int>> q;
        for(int num : nums){
            q.push(num);
            if(q.size()==k+1) q.pop();
        }
        return q.top();
    }
};

// Approach3(quickselect) : O(n)(average), O(n^2)(worst case) time complexity and O(logn) space complexity
class Solution {
public:
    int quickSelect(vector<int> &nums,int start, int end, int k, int n){
        int pivotPos = (start+end)/2;
        int pivot = nums[pivotPos];
        swap(nums[pivotPos],nums[end]);
        
        int l = start;
        for(int i=start;i<=end;i++){
            if(nums[i]<pivot){
                swap(nums[i],nums[l]);
                l++;
            }
        }
        
        swap(nums[l],nums[end]);
        
        if(n-l==k) return nums[l];
        
        else if(n-l>k){
            return quickSelect(nums,l+1,end,k,n);
        }
        
        return quickSelect(nums,start,l-1,k,n);
    }
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        return quickSelect(nums,0,n-1,k,n);
    }
};

// Count sort : O(n+m) time and O(m) space complexity
// where n - len(nums) and m = mx-mn+1
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int mn = INT_MAX;
        int mx = INT_MIN;
        for(int num : nums){
            mn = min(mn,num);
            mx = max(mx,num);
        }
        
        vector<int> cnt(mx-mn+1);
        for(int num:nums){
            cnt[num-mn]++;
        }
        
        int rem = k;
        for(int i=cnt.size()-1;i>=0;i--){
            rem-=cnt[i];
            if(rem<=0) return i+mn;
        }
        
        return -1;
    }
};