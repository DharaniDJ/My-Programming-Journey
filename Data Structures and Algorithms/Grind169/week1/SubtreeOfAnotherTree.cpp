
// Problem Link : https://leetcode.com/problems/subtree-of-another-tree/

// Recursion : O(n*m) time and O(n+m) space complexity
// class Solution {
// public:
//     bool identical(TreeNode* root, TreeNode* subRoot){
//         if((root==NULL) ^ (subRoot==NULL)) return false;
//         if(!root && !subRoot) return true;
//         return (root->val == subRoot->val) && identical(root->left,subRoot->left) && identical(root->right,subRoot->right);
//     }
    
//     bool isSubtree(TreeNode* root, TreeNode* subRoot) {
//         if(root==NULL) return false;
//         if(identical(root,subRoot)) return true;
//         return isSubtree(root->left,subRoot) || isSubtree(root->right,subRoot);
//     }
// };

// Approach2 (string matching) : O(n+m) time and O(n+m) space complexity

// It turns out that if we include # or any other character for the null node
// while serializing, then we can uniquely identify a tree, that too with only
// one traversal (either preorder or postorder). Also add a character (let it be ^, or simply space )
// before adding the node's value

// After serializing both the trees, with the above-mentioned approach, we need
// need to check if the string corresponding to subRoot, named as s in the string
// corresponding to root, named as r. We can use KMP algorithm for pattern matching

class Solution {

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
         // Serialize given Nodes
        string r = "";
        serialize(root, r);
        string s = "";
        serialize(subRoot, s);
                 
         // Check if s is in r
         return kmp(s, r);
     }
    
    // Function to serialize Tree
    void serialize(TreeNode* node, string& treeStr) {
        if (node == nullptr){
            treeStr += "#";
            return;
        }

        treeStr += "^";
        treeStr += to_string(node->val);
        serialize(node->left, treeStr);
        serialize(node->right, treeStr);
    }

    // Knuth-Morris-Pratt algorithm to check if `needle` is in `haystack` or not
    bool kmp(string needle, string haystack) {
        int m = needle.length();
        int n = haystack.length();
        
        if (n < m)
            return false;
        
        // longest proper prefix which is also suffix
        vector<int> lps(m);
        // Length of Longest Border for prefix before it.
        int prev = 0;
        // Iterating from index-1. lps[0] will always be 0
        int i = 1;
        
        while (i < m) {
            if (needle[i] == needle[prev]) {
                // Length of Longest Border Increased
                prev += 1;
                lps[i] = prev;
                i += 1;
            } else {
                // Only empty border exist
                if (prev == 0) {
                    lps[i] = 0;
                    i += 1;
                } else {
                    // Try finding longest border for this i with reduced prev
                    prev = lps[prev-1];
                }
            }
        }
        
        // Pointer for haystack
        int haystackPointer = 0;
        // Pointer for needle.
        // Also indicates number of characters matched in current window.
        int needlePointer = 0;
        
        while (haystackPointer < n) {
            if (haystack[haystackPointer] == needle[needlePointer]) {
                // Matched Increment Both
                needlePointer += 1;
                haystackPointer += 1;
                // All characters matched
                if (needlePointer == m)
                    return true;                
            } else {                
                if (needlePointer == 0) {
                    // Zero Matched
                    haystackPointer += 1;                    
                } else {
                    // Optimally shift left needlePointer. Don't change haystackPointer
                    needlePointer = lps[needlePointer-1];
                }
            }
        }
        
        return false;
    }
};

// Approach3 (Tree Hash) - O(n+m) time and O(n+m) space complexity

// It turns out that tree comparison is expensive. In the very first approach,
// we need to perform the comparison for at most N nodes, and each comparison
// cost O(M). If we can somehow reduce the cost of comparison, then we
// can reduce the overall time complexity

class Solution {
public:
    const int MOD_1 = 1000000007;
    const int MOD_2 = 2147483647;
    
    // Hashing a Node
    pair<unsigned long long, unsigned long long> hashSubtreeAtNode(TreeNode* node, bool needToAdd) {
        if (node == nullptr) return {3, 7};

        auto left = hashSubtreeAtNode(node->left, needToAdd);
        auto right = hashSubtreeAtNode(node->right, needToAdd);

        auto left1 = (left.first << 5) % MOD_1;
        auto right1 = (right.first << 1) % MOD_1;
        auto left2 = (left.second << 7) % MOD_2;
        auto right2 = (right.second << 1) % MOD_2;

        pair hashpair = {(left1 + right1 + node->val) % MOD_1,
                         (left2 + right2 + node->val) % MOD_2};

        if (needToAdd) memo.push_back(hashpair);

        return hashpair;
    }
    
    // Vector to store hashed value of each node.
    vector<pair<unsigned long long, unsigned long long>> memo;
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        hashSubtreeAtNode(root,true);
        auto s = hashSubtreeAtNode(subRoot,false);
        return find(memo.begin(),memo.end(),s)!=memo.end();
    }
};