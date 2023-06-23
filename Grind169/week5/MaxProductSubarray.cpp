
// Problem Link : 

// Carry Forward(TLE) : O(n^2) time and O(1) space complexity
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        for(int i=0;i<n;i++){
            int temp = 1;
            for(int j=i;j<n;j++){
                temp*=nums[j];
                ans = max(ans,temp);
            }
        }
        return ans;
    }
};

// Approach 2 (DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        vector<int> l_max(n,INT_MIN);
        vector<int> l_min(n,INT_MAX);
        
        for(int i=0;i<n;i++){
            if(i==0){
                ans = max(ans,nums[i]);
                l_max[0] = max(1,nums[i]);
                l_min[0] = min(1,nums[i]);
                continue;
            }
            
            if(nums[i]<0){
                ans = max(ans,l_min[i-1]*nums[i]);
                l_max[i] = max(l_min[i-1]*nums[i], 1);
                l_min[i] = min(l_max[i-1]*nums[i], 1);
            }else{
                ans = max(ans,l_max[i-1]*nums[i]);
                l_max[i] = max(l_max[i-1]*nums[i], 1);
                l_min[i] = min(l_min[i-1]*nums[i], 1);
            }
        }
        return ans;
    }
};

// DP Space optimized : O(n) time and O(1) space complexity
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        int mx = INT_MIN;
        int mn = INT_MAX;
        for(int i=0;i<n;i++){
            if(i==0){
                ans = max(ans,nums[i]);
                mx = max(nums[i],1);
                mn = min(nums[i],1);
                continue;
            }
            
            if(nums[i]<0){
                ans = max(ans,mn*nums[i]);
                int temp = mx;
                mx = max(mn*nums[i], 1);
                mn = min(temp*nums[i], 1);
            }else{
                ans = max(ans,mx*nums[i]);
                mx = max(mx*nums[i], 1);
                mn = min(mn*nums[i], 1);
            }
        }
        return ans;
    }
};

// Same complexity, but simpler implementation
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return -1;
        int ans=nums[0], mx=nums[0], mn=nums[0];

        for(int i=1;i<n;i++){
            int temp = max({nums[i],mn*nums[i],mx*nums[i]});
            mn = min({nums[i],mn*nums[i],mx*nums[i]});
            mx = temp;

            ans = max(ans,temp);
        }
        return ans;
    }
};