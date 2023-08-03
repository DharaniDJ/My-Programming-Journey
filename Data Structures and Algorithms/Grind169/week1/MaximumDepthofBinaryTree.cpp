
// Problem Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/

// Recursion(DFS): O(n) time and O(n)(if tree is completely unbalanced) or O(logn)(if balanced BT) space complexity
// class Solution {
// public:
//     int maxDepth(TreeNode* root) {
//         if(!root) return 0;
//         return max(maxDepth(root->right),maxDepth(root->left))+1;
//     }
// };

// tail recursion + BFS: O(n) time and O(n)(if tree is completely unbalanced) or O(logn)(if balanced BT) space complexity
// class Solution {
// private:
//     queue<pair<TreeNode*, int>> q;
//     int max_depth=0;

//     int next_maxDepth(){
//         if(q.empty()) return max_depth;

//         auto f = q.front();
//         q.pop();

//         TreeNode* node = f.first;
//         int next_depth = f.second+1;
//         max_depth=max(next_depth,max_depth);

//         if(node->left) q.push({node->left,next_depth});
//         if(node->right) q.push({node->right,next_depth});
//         return next_maxDepth();
//     }
// public:
//     int maxDepth(TreeNode* root) {
//         if(!root) return 0;
//         queue<pair<TreeNode*, int>> empty;
//         swap(q,empty);
//         max_depth=0;

//         q.push({root,0});
//         return next_maxDepth();
//     }
// };

// Iteration + BFS : O(n) time and O(n)(if tree is completely unbalanced) or O(logn)(if balanced BT) space complexity
// class Solution {
// public:
//     int maxDepth(TreeNode* root) {
//         if(!root) return 0;
//         queue<pair<TreeNode*, int>> q;
//         int max_depth=0;

//         q.push({root,0});
//         while(!q.empty()){
//             auto f = q.front();
//             q.pop();
//             auto node = f.first;
//             int lvl = f.second+1;
//             max_depth=max(max_depth,lvl);
//             if(node->left) q.push({node->left,lvl});
//             if(node->right) q.push({node->right,lvl});
//         }
//         return max_depth;
//     }
// };