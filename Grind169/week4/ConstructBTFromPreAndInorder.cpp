
// Problem Link : https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

// Recursion : O(n) time and O(n) space complexity
class Solution {
public:
    TreeNode* solve(vector<int>& preorder, int preS, int preE, vector<int>& inorder, int inS, int inE, unordered_map<int,int> &mp){
        if(preS>preE || inS>inE) return NULL;
        
        TreeNode* root = new TreeNode(preorder[preS]);
        int idx = mp[root->val];
        int ln = idx-inS;
        root->left = solve(preorder,preS+1,preS+ln,inorder,inS,idx-1,mp);
        root->right = solve(preorder,preS+ln+1,preE,inorder,idx+1,inE,mp);
        
        return root;
        
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int,int> mp;
        for(int i=0;i<inorder.size();i++) mp[inorder[i]]=i; // store element and index in the map
        
        return solve(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1,mp);
    }
};