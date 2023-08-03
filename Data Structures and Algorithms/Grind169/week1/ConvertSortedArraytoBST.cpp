
// Problem Link: https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

// Recursion(Preorder traversal): O(n) time and O(log n) space complexity
class Solution {
public:
    TreeNode* constructTree(vector<int> &nums, int l, int r){
        if(l<0 || r>=nums.size()||l>r) return NULL;
        int mid = l+(r-l)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = constructTree(nums,l,mid-1);
        root->right = constructTree(nums,mid+1,r);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return constructTree(nums,0,nums.size()-1);
    }
};