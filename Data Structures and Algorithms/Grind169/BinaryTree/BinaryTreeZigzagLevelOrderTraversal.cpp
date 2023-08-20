
// Problem Link : https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

// BFS : O(n) time and O(n) space complexity
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        int sz,lvl=0;
        TreeNode* temp;
        while(!q.empty()){
            sz = q.size();
            for(int i=0;i<sz;i++){
                temp = q.front();
                q.pop();
                ans.push_back(temp->val);
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
            if(!lvl) res.push_back(ans);
            else{
                reverse(ans.begin(),ans.end());
                res.push_back(ans);
            }
            ans.clear();
            lvl = (lvl+1)%2;
        }
        return res;
    }
};

// DFS : O(n) time and O(n) space complexity
class Solution {
public:
    void solve(TreeNode* root, int lvl, map<int,vector<int>> &mp){
        if(!root) return;
        mp[lvl].push_back(root->val);
        solve(root->left,lvl+1,mp);
        solve(root->right,lvl+1,mp);
        return;
    }
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        map<int,vector<int>> mp;
        solve(root,0,mp);
        for(auto it : mp){
            if(it.first%2){
                reverse(it.second.begin(),it.second.end());
            }
            ans.push_back(it.second);
        }
        return ans;
    }
};