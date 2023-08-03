
// Problem Link : https://leetcode.com/problems/binary-tree-right-side-view/

// Approach 1 (BFS) : O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        int lvl = 0;
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;i++){
                TreeNode* cur = q.front();
                q.pop();

                if(i==(sz-1)) res.push_back(cur->val);

                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            lvl++;
        }
        return res;
    }
};

// Approach 2(DFS) : O(n) time and O(n) space complexity
class Solution {
public:
    void dfs(TreeNode* root, vector<int> &res, int lvl){
        if(!root){
            return;
        }
        if(res.size()==lvl) res.push_back(root->val);
        res[lvl] = root->val;
        dfs(root->left,res,lvl+1);
        dfs(root->right,res,lvl+1);
        return;
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        int lvl = 0;
        dfs(root,res,lvl);
        return res;
    }
};