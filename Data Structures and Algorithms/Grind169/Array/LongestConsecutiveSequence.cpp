
// Problem Link : https://leetcode.com/problems/longest-consecutive-sequence/

// Brute Force : O(n^3) time and O(1) space complexity
class Solution {
public:
    bool arrayContains(vector<int> &nums, int k){
        for(int num : nums){
            if(num==k) return true;
        }
        return false;
    }
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;

        int ans = 0;
        for(int num : nums){
            int curNum = num;
            int curCnt = 1;

            while(arrayContains(nums,curNum+1)){
                curNum+=1;
                curCnt+=1;
            }

            ans = max(ans,curCnt);
        }

        return ans;
    }
};

// Approach2(Sorting) : O(n*logn) time and O(logn) space complexity
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;

        sort(nums.begin(),nums.end());

        int ans = 1;
        int cur = 1;
        for(int i=1;i<n;i++){
            if(nums[i]==nums[i-1]) continue;

            if(nums[i] == nums[i-1]+1){
                cur++;
            }else{
                ans = max(ans,cur);
                cur = 1;
            }
        }

        ans = max(ans,cur);
        return ans;
    }
};

// HashSet and Improved Sequence Building : O(n) time and O(1) space complexity
// This optimized algorithm contains only two changes from the brute force approach:

// Although the time complexity appears to be quadratic due to the while
// loop nested within the for loop, closer inspection reveals it to be
// linear. Because the while loop is reached only when currentNum marks
// the beginning of a sequence (i.e. currentNum-1 is not present in
// nums), the while loop can only run for n iterations throughout the
// entire runtime of the algorithm.

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;
        unordered_set<int> s;
        for(int num : nums) s.insert(num);
        
        int ans = 1;
        for(int num : nums){
            if(!s.count(num-1)){ // Optimized from the brute force
                int curNum = num;
                int curCnt = 1;
                while(s.count(curNum+1)){
                    curCnt++;
                    curNum+=1;
                }
                ans = max(ans,curCnt);
            }
        }
        return ans;
    }
};