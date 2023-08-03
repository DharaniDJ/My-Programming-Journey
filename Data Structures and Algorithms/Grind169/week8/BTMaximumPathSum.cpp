
// Problem Link: 

// Approach1(Postorder DFS) : O(n) time and O(n) space complexity
class Solution {
public:
    int getPathSum(TreeNode* root, int &res){
        if(!root) return 0;

        int l = getPathSum(root->left,res);
        int r = getPathSum(root->right,res);

        int temp = max(max(l,r)+root->val, root->val);
        int ans = max(temp, (l+r+root->val));
        res = max(res,ans);

        return temp;
    }

    int maxPathSum(TreeNode* root) {
        if(!root) return 0;

        int res = INT_MIN;
        getPathSum(root,res);
        return res;
    }
};