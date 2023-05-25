
// Problem link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

// Recursion - O(n) time and O(n) space complexity
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return root;
        if(p->val > q->val) swap(p,q);
        if(p->val < root->val && q->val > root->val) return root;
        if(q->val < root->val) return lowestCommonAncestor(root->left,p,q);
        else if(p->val > root->val) return lowestCommonAncestor(root->right,p,q);
        return root;
    }
};

// Iterative - O(n) time and O(1) space complexity
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int pVal = p->val;
        int qVal = q->val;
        TreeNode* node = root;
        while(node){
            int parentVal = node->val;
            if(pVal > parentVal && qVal > parentVal) node=node->right;
            else if(pVal < parentVal && qVal < parentVal) node=node->left;
            else return node;
        }
        return NULL;
    }
};
