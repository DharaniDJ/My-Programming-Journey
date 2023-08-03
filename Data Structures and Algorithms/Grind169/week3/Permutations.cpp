

// Problem Link : https://leetcode.com/problems/permutations

// Backtracking : O(n*n!) time and O(n) space complexity
// Precise time complexity will be O(n^2 * (e*Γ(n+1,1)−n!))
class Solution {
public:
    void solve(vector<int>& nums, vector<int>& temp, vector<vector<int>>& res){
        if(temp.size()==nums.size()){
            res.push_back(temp);
            return;
        }
        
        for(int num : nums){
            if(find(temp.begin(),temp.end(),num)==temp.end()){
                temp.push_back(num);
                solve(nums,temp,res);
                temp.pop_back();
            }
        }
        return;
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> temp ;
        solve(nums,temp,res);
        return res;
    }
};