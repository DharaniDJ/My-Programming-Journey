// Diameter of Tree
// Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.

// Example:
// Given a binary tree
//           1
//          / \
//         2   3
//        / \
//       4   5
// Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

int solve(TreeNode* root, int& res){
    if(root==nullptr){
        return 0;
    }

    int l = solve(root->left, res);
    int r = solve(root->right, res);

    int temp = max(l,r)+1;
    int ans = max(temp,1+l+r);
    res = max(res,ans);

    return temp;
}

// int main(){
//     int res = INT_MIN;
//     solve(root,res);
//     cout << res;
// }