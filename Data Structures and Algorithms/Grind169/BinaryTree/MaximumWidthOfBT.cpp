
// Problem Link : https://leetcode.com/problems/maximum-width-of-binary-tree/

// DFS : O(n) time and O(n) space complexity
class Solution {
public:
    void solve(TreeNode* root, long long lvl, unsigned long long vertLvl ,unordered_map<long long,long long> &mp, long long &res){
        if(!root) return;
        if(mp.find(lvl)==mp.end()) mp[lvl]=vertLvl;

        res = max(res, static_cast<long long>(vertLvl-mp[lvl]+1));
        solve(root->left,lvl+1,2*vertLvl,mp,res);
        solve(root->right,lvl+1,2*vertLvl+1,mp,res);

    }

    int widthOfBinaryTree(TreeNode* root) {
        unordered_map<long long,long long> mp;
        long long res = 0;

        solve(root,0,1,mp,res);
        return res;
    }
};

// BFS : O(n) time and O(n) space complexity
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        
        long long res = 1;
        queue<pair<TreeNode*, int>> q;
        q.push({root,1});
        
        while(!q.empty()){
            int sz = q.size();
            long long start = q.front().second;
            long long end = q.back().second;
            
            res = max(res, end-start+1);
            while(sz--){
                auto f = q.front();
                long long idx = f.second - start;
                
                q.pop();
                
                if(f.first->left) q.push({f.first->left, (long long)2*idx});
                if(f.first->right) q.push({f.first->right, (long long)2*idx+1});
            }
        }
        return res;
    }
};