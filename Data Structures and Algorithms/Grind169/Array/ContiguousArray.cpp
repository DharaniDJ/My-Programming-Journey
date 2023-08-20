
// Problem Link : https://leetcode.com/problems/contiguous-array/

// BruteForce : O(n^3) time and O(1) space complexity
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                int cnt = 0;
                for(int k=i;k<=j;k++){
                    if(nums[k]==0) cnt-=1;
                    else cnt+=1;
                }
                if(cnt==0) ans = max(ans,(j-i+1));
            }
        }
        return ans;
    }
};

// Approach 2(Carry Forward) : O(n^2) time and O(1) space complexity
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for(int i=0;i<n;i++){
            int cnt = 0;
            for(int j=i;j<n;j++){
                if(nums[j]==0) cnt--;
                else cnt++;
                if(cnt==0) ans = max(ans,(j-i+1));
            }
        }
        return ans;
    }
};

// HashMap : O(n) time and O(n) space complexity
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int,int> mp;
        int ans = 0;
        int sum = 0;
        for(int i=0;i<n;i++){
            if(nums[i]==0) sum--;
            else sum++;

            if(sum==0) ans = max(ans,i+1);

            if(mp.find(sum)==mp.end()){
                mp[sum]=i;
            }
            ans = max(ans,i-mp[sum]);
        }
        return ans;
    }
};