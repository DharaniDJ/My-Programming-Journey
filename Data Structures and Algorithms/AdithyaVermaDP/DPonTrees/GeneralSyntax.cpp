
// General syntax of DP on Trees

// int funName(inputs){
//     base condition
//     hypothesis (gives answer for left and right node)
//     induction (use left and right answers to induce parent's answer)
// }

// int res = INT_MIN/INT_MAX
// int solve(TreeNode* root, int& res){
//     if(root==nullptr) return 0; // problem dependent and can have multiple base conditions

//     int l = solve(root->left,res);
//     int r = solve(root->right,res);

//     int temp = calculate temp ans
//     int ans = max/min (temp,relation(l,r));
//     res = max/min (res,ans)
//     return temp;
// }

