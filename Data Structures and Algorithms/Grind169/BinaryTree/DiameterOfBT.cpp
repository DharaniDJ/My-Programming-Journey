
// Problem Link: https://leetcode.com/problems/diameter-of-binary-tree/

// Approach1 - O(n) time and O(n) space complexity
class Solution {
public:
    int solve(TreeNode* root, int& ans){
        if(!root){
            return 0;
        }
        int lt = solve(root->left,ans);
        int rt = solve(root->right,ans);
        
        ans = max(ans,(lt+rt+1));
        return max(lt,rt)+1;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = -1;
        solve(root,ans);
        return ans-1;
    }
};

// DP on Trees - O(n) time and O(n) space complexity
class Solution {
public:
    int solve(TreeNode* root, int& ans){
        if(!root){
            return 0;
        }
        int lt = solve(root->left,ans);
        int rt = solve(root->right,ans);

        int temp = max(lt,rt)+1;
        ans = max({ans,temp,lt+rt+1});

        return temp;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = -1;
        solve(root,ans);
        return ans-1;
    }
};