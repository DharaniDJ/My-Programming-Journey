// Maximum path sum from leaf to leaf

// If a binary tree is given, how to find Maximum path sum between two leaves of binary tree.

// All should be numbers
// The maximum sum path may or may not go through root.
// For example, in the following binary tree, the maximum sum is 27(3 + 6 + 9 + 0 – 1 + 10). Expected time complexity is O(n).

//         -15
//         /  \
//        5    6
//       / \  / \
//     -8  1  3  9
//     / \       \
//    2   6       0
//        / \
//       4  -1
//     /
//    10

int solve(TreeNode* root, int& res){
    if(root==nullptr) return 0;

    int l = solve(root->left, res);
    int r = solve(root->right, res);

    int temp = max(l,r)+root->val;

    // if leaf node, only then consider max(temp,root->val)
    if(!root->left && !root->right) temp = max(temp,root->val)
    
    int ans = max(temp,l+r+root->val);
    res = max(res,ans);
    return temp;
}