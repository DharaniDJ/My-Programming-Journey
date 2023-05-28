
// Problem Link: https://leetcode.com/problems/symmetric-tree/

// Approach 1 (Recursion) : O(n) time and O(n) space complexity
// class Solution {
// public:
//     bool check(TreeNode* lt, TreeNode* rt){
//         if((lt==NULL) ^ (rt==NULL)) return false;
//         if(!lt && !rt) return true;
//         return (lt->val == rt->val) && check(lt->left,rt->right) && check(lt->right,rt->left);
//     }
//     bool isSymmetric(TreeNode* root) {
//         if(!root) return true;
//         return check(root->left, root->right);
//     }
// };

// Approach 2 (Iterative) : O(n) time and O(n) space complexity
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*> q;
        q.push(root);
        q.push(root);
        while(!q.empty()){
            auto lt = q.front();
            q.pop();
            auto rt = q.front();
            q.pop();
            if((lt==NULL) ^ (rt==NULL)) return false;
            if(!lt && !rt) continue;
            if(lt->val != rt->val) return false;
            q.push(lt->left);
            q.push(rt->right);
            q.push(lt->right);
            q.push(rt->left);
        }
        return true;
    }
};