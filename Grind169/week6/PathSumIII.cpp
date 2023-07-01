
// Problem Link : https://leetcode.com/problems/path-sum-iii

// Prefix Sum : O(n) time and O(n) space complexity
// for 1D arrays (sum the current value with all the previous integers)
// for 2D arrays (sum of the current value with the integers above or on the left)
// for the binary trees (sum the values of the current node and all parent nodes)

class Solution {
    int count=0;
    unordered_map<long long,long long> mp;
    int k;
public:
    void preorder(TreeNode* root, long long curSum){
        if(!root) return;

        // current prefix sum
        curSum+=root->val;

        // here is the sum we're looking for
        if(curSum==k) count++;

        // number of times the curr_sum − k has occured already,
        // determines the number of times a path with sum k
        // has occured upto the current node
        if(mp.find(curSum-k)!=mp.end()) count+=mp[curSum-k];

        // add the current sum into hashmap
        // to use it during the child nodes processing
        mp[curSum]++;

        // process left and right child
        preorder(root->left,curSum);
        preorder(root->right,curSum);

        // remove the current sum from the hashmap
        // in order not to use it during
        // the parallel subtree processing
        mp[curSum]--;
        return;
    }
    int pathSum(TreeNode* root, int targetSum) {
        k = targetSum;
        preorder(root,0L);
        return count;
    }
};