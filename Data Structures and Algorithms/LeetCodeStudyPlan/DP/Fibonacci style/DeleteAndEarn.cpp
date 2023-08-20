
// Problem Link : https://leetcode.com/problems/delete-and-earn/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(TopDown DP) : O(n) time and O(n) space complexity
class Solution {
    unordered_map<int,int> mp;
    unordered_map<int,int> dp;

    int solve(int num){

        if(num==0) return 0;

        if(num==1){
            return mp.count(num) ? mp[num] : 0;
        }

        if(dp.count(num)) return dp[num];

        int points = mp.count(num) ? mp[num] : 0;

        // If we take x, them add the points for num and the next largest number that we can still consider is x-2;
        // If we not take x, then don't add points for num and the next largest number that we can still consider is x-1.
        return dp[num] = max(solve(num-1),solve(num-2)+points);
    }

public:
    int deleteAndEarn(vector<int>& nums) {

        int maxNum = 0;

        for(int num : nums){
            mp[num]+=num;
            maxNum = max(maxNum, num);
        }

        return solve(maxNum);

    }
};

// Approach2(Bottom Up) : O(n) time and O(n) space complexity
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int,int> mp;
        int maxNum = 0;

        for(int num : nums){
            mp[num]+=num;
            maxNum = max(maxNum, num);
        }

        vector<int> dp(maxNum+1);

        dp[0] = 0;
        dp[1] = (mp.count(1)>0) ? mp[1] : 0;

        for(int i=2;i<(int)dp.size();i++){
            int points = (mp.count(i)>0) ? mp[i] : 0;
            dp[i] = max(dp[i-1], dp[i-2]+points);
        }

        return dp.back();
    }
};

// Approach3(Bottom Up + Space Optimization) : O(n) time and O(n) space complexity
class Solution {
public:    
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int,int> mp;
        int maxNum = 0;

        for(int num : nums){
            mp[num]+=num;
            maxNum = max(maxNum, num);
        }
        
        int prev = 0;
        int cur = mp.count(1)>0 ? mp[1] : 0;
        
        for(int i=2;i<=maxNum;i++){
            int points = (mp.count(i)>0) ? mp[i] : 0;
            
            int next = max(cur, prev + points);
            prev = cur;
            cur = next;
        }
        
        return cur;
    }
};

// Approach4(Iterate Over Elements) : O(n) time and O(n) space complexity
// Instead of iterating over all numbers from 0 to max(nums), we can iterate over only the elements that appear in nums.
class Solution {
public:    
    int deleteAndEarn(vector<int>& nums) {
        map<int,int> mp;
        int maxNum = 0;

        for(int num : nums){
            mp[num]+=num;
            maxNum = max(maxNum, num);
        }
        
        vector<int> elem;
        for(auto it : mp) elem.push_back(it.first);
        
        int prev = 0;
        int cur = mp[elem[0]];
        
        for(int i=1;i<(int)elem.size();i++){
            int curEle = elem[i];
            int temp = cur;
            
            if(curEle==elem[i-1]+1){
                // The 2 elements are adjacent, cannot take both - apply normal recurrence
                cur = max(cur,prev+mp[curEle]);
            }else{
                // Otherwise, we don't need to worry about adjacent deletions
                cur+=mp[curEle];
            }
            
            prev = temp;
        }
        
        return cur;
    }
};