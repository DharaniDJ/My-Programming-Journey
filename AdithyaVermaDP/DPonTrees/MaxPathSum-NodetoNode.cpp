// Given a non-empty binary tree, find the maximum path sum.

// For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

// Example 1:

// Input: [1,2,3]

//        1
//       / \
//      2   3

// Output: 6
// Example 2:

// Input: [-10,9,20,null,null,15,7]

//    -10
//    / \
//   9  20
//     /  \
//    15   7

// Output: 42

int solve(TreeNode* root, int& res){
    if(root==nullptr) return 0;

    int l = solve(root->left,res);
    int r = solve(root->right, res);

    int temp = max(max(l,r)+root->val, root->val);
    int ans = max(temp,max(l+r+root->val));
    res = max(res,ans);

    return temp;
}

// int main(){
//     int res = INT_MIN;
//     solve(root,res);
//     cout << res;
// }