
// Problem Link : https://leetcode.com/problems/inorder-successor-in-bst/

// Without BST Properties : O(n) time and O(n) space complexity
// In worst case if the tree is left-skewed, we need to traverse all nodes
class Solution {
public:

    TreeNode* inorderSuccessor2(TreeNode* root, TreeNode* p, TreeNode* &prev) {
        if(!root) return NULL;

        TreeNode* leftRes = inorderSuccessor2(root->left,p,prev);

        if(leftRes) return leftRes;

        if(prev==p) return root;

        // Keeping previous up-to-date for further recursions
        prev = root;

        TreeNode* rightRes = inorderSuccessor2(root->right,p,prev);
        return rightRes;
    }

    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {

        // Case 1: We simply need to find the leftmost node in the subtree rooted at p->right.
        if(p->right){
            TreeNode* leftMostNode = p->right;
            while(leftMostNode->left){
                leftMostNode = leftMostNode->left;
            }
            return leftMostNode;
        }

        // Case 2: We need to perform the standard inorder traversal and keep track of the previous node.
        TreeNode* prev = NULL;
        return inorderSuccessor2(root,p,prev);

    }
};

// Using BST Properties: O(n) time and O(1) space complexity
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {

        TreeNode* successor = nullptr;
        while(root){
            if(p->val>=root->val){
                root=root->right;
            }else{
                successor = root;
                root=root->left;
            }
        }
        return successor;
    }
};