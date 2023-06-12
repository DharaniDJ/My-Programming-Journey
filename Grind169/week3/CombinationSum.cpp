
// Problem Link : https://leetcode.com/problems/combination-sum/


// Recursion : O(N^(T/M + 1)) time and O(T/M) space complexity
// where N be the number of candidates, T be the target value,
// and M be the minimal value among the candidates.


class Solution {
public:
    void solve(int idx, vector<int>& candidates, int target, vector<vector<int>> &res, vector<int>& temp){
        if(idx==candidates.size()){
            if(target==0){
                res.push_back(temp);
            }
            return;
        }
        
        if(target==0){
            res.push_back(temp);
            return;
        }
        
        if(target>=candidates[idx]){
            temp.push_back(candidates[idx]);
            solve(idx,candidates,target-candidates[idx],res,temp);
            temp.pop_back();
        }
        
        solve(idx+1,candidates,target,res,temp);
        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int i=0;
        vector<vector<int>> res;
        vector<int> temp;
        solve(i,candidates,target,res,temp);
        return res;
    }
};