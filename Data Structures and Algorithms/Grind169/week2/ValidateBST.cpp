

// Problem Link: https://leetcode.com/problems/validate-binary-search-tree/

// Recursion with valid range : O(n) time and O(n) space complexity
class Solution {
public:
    bool solve(TreeNode* root, long long &mn, long long &mx){
        if(!root) return true;
        long long v = root->val;
        if(v<=mn || v>=mx) return false;
        return solve(root->left,mn,v) && solve(root->right,v,mx);
    }
    bool isValidBST(TreeNode* root) {
        long long mn = INT_MIN-1LL;
        long long mx = INT_MAX+1LL;
        return solve(root,mn,mx);
    }
};

// Iterative with valid range: O(n) time and O(n) space complexity
class Solution {
private:
    stack<TreeNode*> st, mn, mx;
public:
    void update(TreeNode* root, TreeNode* low, TreeNode* high){
        st.push(root);
        mn.push(low);
        mx.push(high);
    }
    
    bool isValidBST(TreeNode* root) {
        TreeNode* low = nullptr;
        TreeNode* high = nullptr;
        update(root,low,high);
        while(!st.empty()){
            root = st.top();
            st.pop();
            low = mn.top();
            mn.pop();
            high = mx.top();
            mx.pop();

            if(!root) continue;

            TreeNode* cur = root;
            if(low && cur->val <= low->val) return false;
            if(high && cur->val >= high->val) return false;

            update(cur->left,low,cur);
            update(cur->right,cur,high);
        }
        return true;
    }
};

// Recursive inorder : O(n) time and O(n) space complexity
class Solution {
public:
    bool solve(TreeNode* root, TreeNode* &prev){
        if(!root) return true;
        if(!solve(root->left,prev)) return false;
        if(prev && root->val <= prev->val) return false;
        prev = root;
        return solve(root->right,prev);
    }
    
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = nullptr;
        return solve(root,prev);
    }
};

// Iterative inorder :: O(n) time and O(n) space complexity
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode* prev = NULL;
        while(!st.empty() || root){
            while(root){
                st.push(root);
                root=root->left;
            }
            root = st.top();
            st.pop();
            
            if(prev && root->val <= prev->val) return false;
            prev = root;
            root = root->right;
        }
        return true;
    }
};