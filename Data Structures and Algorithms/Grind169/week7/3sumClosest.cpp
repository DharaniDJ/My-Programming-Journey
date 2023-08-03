
// Problem Link : https://leetcode.com/problems/3sum-closest

// 2 pointer techniquie : O(n^2 + logn) time and O(logn) to O(n) space complexity
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(),nums.end());

        int closest_ans = nums[0]+nums[1]+nums[2];
        for(int i=0;i<n;i++){
            if(i==0 || nums[i]!=nums[i-1]){
                int j = i+1;
                int k = n-1;

                while(k>j){
                    int sum = nums[i]+nums[j]+nums[k];
                    if(target == sum) return target;
                    if(target > sum){
                        j++;
                    }else{
                        k--;
                    }

                    if(abs(sum - target) <= abs(closest_ans - target)){
                        closest_ans = sum;
                    }
                }
            }
        }
        return closest_ans;
    }
};

//Binary Search: O(n^2 * logn) time and O(logn) to O(n) space complexity
// In the two pointers approach, we fix one number and use two pointers to enumerate pairs. Here, we fix two numbers, and use a binary search to find the third complement number.
// This is less efficient than the two pointers approach, however, it could be more intuitive to come up with.

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        
        int diff = INT_MAX;
        for(int i=0;i<n && diff!=0;i++){
            if(i==0 || nums[i]!=nums[i-1]){
                for(int j=i+1;j<n-1;j++){
                    int complement = target - nums[i]-nums[j];
                    auto it = upper_bound(nums.begin() + j + 1, nums.end(), complement);
                    int hi = it-nums.begin();
                    int lo = hi-1;
                    if(hi<n && abs(diff) > abs(complement-nums[hi])){
                        diff = complement-nums[hi];
                    }
                    if(lo>j && abs(diff) > abs(complement-nums[lo])){
                        diff = complement-nums[lo];
                    }
                }
            }
        }
        return target-diff;
    }
};