
// Problem link: https://leetcode.com/problems/invert-binary-tree/

// Recursion - O(n) time and O(n) space complexity
// class Solution {
// public:
//     TreeNode* invertTree(TreeNode* root) {
//         if(!root) return NULL;
//         auto temp = root->left;
//         root->left = invertTree(root->right);
//         root->right = invertTree(temp);
//         return root;
//     }
// };


// Iterative - O(n) time and O(1) space complexity
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return NULL;
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* f = q.front();
            q.pop();
            TreeNode* temp = f->left;
            f->left=f->right;
            f->right=temp;
            if(f->left) q.push(f->left);
            if(f->right) q.push(f->right);
        }
        return root;
    }
};