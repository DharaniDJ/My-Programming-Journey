
// Problem Link: https://leetcode.com/problems/same-tree/
// Recursion: O(n) time and O(n) space complexity
// class Solution {
// public:
//     bool isSameTree(TreeNode* p, TreeNode* q) {
//         if((p==NULL) ^ (q==NULL)) return false;
//         if(!p && !q) return true;
//         return (p->val==q->val) && isSameTree(p->left,q->left) && isSameTree(p->right,q->right);
//     }
// };

// Iteration: O(n) time and O(n) space complexity
class Solution {
public:
    bool check(TreeNode* p, TreeNode* q){
        if(p==NULL && q==NULL) return true;
        if(p==NULL || q==NULL) return false;
        return (p->val == q->val);
    }
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == NULL && q == NULL) return true;
        if (!check(p, q)) return false;
        
        queue<TreeNode*> dp, dq;
        dp.push(p);
        dq.push(q);
        
        while(!dp.empty()){
            p = dp.front();
            q = dq.front();
            dp.pop();
            dq.pop();
            if(!check(p,q)) return false;
            if(!check(p->left,q->left)) return false;
            if(p->left){
                dp.push(p->left);
                dq.push(q->left);
            }
            if(!check(p->right,q->right)) return false;
            if(p->right){
                dp.push(p->right);
                dq.push(q->right);
            }
        }
        return true;
    }
};