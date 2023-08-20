
// Problem Link : https://leetcode.com/problems/binary-tree-level-order-traversal/

// Recursion - O(n) time and O(n) space complexity
class Solution {
private:
    vector<vector<int>> levels;
public:
    void solve(TreeNode* root, int level){
        if(levels.size()==level){
            levels.push_back(vector<int>());
        }

        levels[level].push_back(root->val);
        if(root->left) solve(root->left,level+1);
        if(root->right) solve(root->right,level+1);
        return;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(!root) return levels;
        solve(root,0);
        return levels;
    }
};

// BFS - O(n) time and O(n) space complexity
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        vector<int> temp;

        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            for(int i=0;i<sz;i++){
                auto node = q.front();
                temp.push_back(node->val);
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            res.push_back(temp);
            temp.clear();
        }
        return res;
    }
};