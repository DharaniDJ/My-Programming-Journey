
// Problem link: https://leetcode.com/problems/balanced-binary-tree/

// Top-down recursion - O(n*logn) time and O(1) space complexity
class Solution {
public:
    int height(TreeNode* root){
        if(!root) return -1;
        return max(height(root->left),height(root->right))+1;
    }
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int lh = height(root->left);
        int rh = height(root->right);
        if(abs(lh-rh)>1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

// Bottom-up recursion - O(n) time and O(n) space complexity
class Solution {
public:
    bool checkBST(TreeNode* root, int &h){
        if(!root){
            h=0;
            return true;
        }
        int lh=0,rh=0;
        bool lt = checkBST(root->left,lh);
        bool rt = checkBST(root->right,rh);

        h = max(lh,rh)+1;

        if(!lt || !rt) return false;
        if(abs(lh-rh)>1) return false;

        return true;
    }

    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int h = 0;
        return checkBST(root,h);
    }
};
