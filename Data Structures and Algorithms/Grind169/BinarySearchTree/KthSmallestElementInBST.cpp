
// Problem Link : https://leetcode.com/problems/kth-smallest-element-in-a-bst

// Recursive Inorder with array : O(n) time and O(n) space complexity
class Solution {
public:
    void solve(TreeNode* root, vector<int> &res){
        if(!root) return;
        solve(root->left,res);
        res.push_back(root->val);
        solve(root->right,res);
    }
    int kthSmallest(TreeNode* root, int &k) {
        vector<int> res;
        solve(root,res);
        return res[k-1];
    }
};

// Recursive Inorder without array : O(n) time and O(n) space complexity
class Solution {
public:
    int kthSmallest(TreeNode* root, int &k) {
        if(root == nullptr) return -1;
        
        int left = kthSmallest(root->left,k);
        if(left!=-1) return left;
        k--;
        if(k==0) return root->val;
        int right = kthSmallest(root->right,k);
        return right;
    }
};

// Iterative inorder : O(n) time and O(n) space complexity
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        
        while(1){
            while(root){
                st.push(root);
                root=root->left;
            }
            root = st.top();
            st.pop();
            k--;
            if(k==0) return root->val;
            root = (root->right);
        }
    }
};

// BST Iterator : O(n) time and O(n) space complexity
class BSTIterator{
    stack<TreeNode*> st;
    bool reverse=false;
public:
    BSTIterator(TreeNode* root, bool isReverse){
        reverse=isReverse;
        pushAll(root);
    }
    int next(){
        TreeNode* el = st.top();
        st.pop();
        if(reverse) pushAll(el->left);
        else pushAll(el->right);
        return el->val;
    }
    bool hasNext(){
        return !st.empty();
    }
private:
    void pushAll(TreeNode* root){
        while(root){
            st.push(root);
            if(reverse) root=root->right;
            else root=root->left;
        }
    }
};
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        BSTIterator l(root,false);
        int ans = -1;
        while(k--){
            ans = l.next();
        }
        return ans;
    }
};