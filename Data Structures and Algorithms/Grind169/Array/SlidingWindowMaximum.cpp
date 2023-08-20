
// Problem Link : https://leetcode.com/problems/sliding-window-maximum/

// Apprach1(Monotonic deque) : O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;

        deque<int> dq;

        for(int i=0;i<(int)nums.size();i++){
            while(!dq.empty() && nums[dq.back()]<nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if((i - dq.front())>=k) dq.pop_front();
            if(i>=k-1){
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};