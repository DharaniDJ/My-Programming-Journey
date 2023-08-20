
// Problem Link : https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree

// Approach1(Implement Parent Pointers and DFS): O(n) time and O(n) space complexity
// You can create a class with left, right and parent pointers

// In Python, we can add attributes (in our case a parent pointer) to an instance of a class at any time,
// even if the attribute is not defined in the class.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode *parent;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
 * };
 */

// class Solution:
//     def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
//         # Recursively add a parent pointer to each node.
//         def add_parent(cur, parent):
//             if cur:
//                 cur.parent = parent
//                 add_parent(cur.left, cur)
//                 add_parent(cur.right, cur)
//         add_parent(root, None)

//         answer = []
//         visited = set()
//         def dfs(cur, distance):
//             if not cur or cur in visited:
//                 return
//             visited.add(cur)
//             if distance == 0:
//                 answer.append(cur.val)
//                 return
//             dfs(cur.parent, distance - 1)
//             dfs(cur.left, distance - 1)
//             dfs(cur.right, distance - 1)

//         dfs(target, k)

//         return answer

// DFS : O(n) time and O(n) space complexity
class Solution {
public:

    void preorder(TreeNode* root, TreeNode* parent, unordered_map<TreeNode*,TreeNode*> &mp ){
        if(!root) return;
        mp[root]=parent;
        preorder(root->left,root,mp);
        preorder(root->right,root,mp);
        return;
    }

    void dfs(TreeNode* node, unordered_map<TreeNode*,TreeNode*> &mp, unordered_set<TreeNode*> &vis, int lvl, vector<int> &res){
        if(vis.count(node)) return;
        if(lvl==0){
            res.push_back(node->val);
            return;
        }

        vis.insert(node);

        if(node->left && vis.count(node->left)==0) dfs(node->left,mp,vis,lvl-1,res);
        if(node->right && vis.count(node->right)==0) dfs(node->right,mp,vis,lvl-1,res);
        if(mp[node] && vis.count(mp[node])==0) dfs(mp[node],mp,vis,lvl-1,res);

    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> res;
        if(!root) return res;

        unordered_map<TreeNode*,TreeNode*> mp;
        preorder(root,NULL,mp);
        unordered_set<TreeNode*> vis;

        dfs(target,mp,vis,k,res);

        return res;
    }
};

// BFS : O(n) time and O(n) space complexity
class Solution {
public:

    void preorder(TreeNode* root, TreeNode* parent, unordered_map<TreeNode*,TreeNode*> &mp ){
        if(!root) return;
        mp[root]=parent;
        preorder(root->left,root,mp);
        preorder(root->right,root,mp);
        return;
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> res;
        if(!root) return res;

        unordered_map<TreeNode*,TreeNode*> mp;
        preorder(root,NULL,mp);
        set<TreeNode*> vis;
        queue<TreeNode*> q;

        q.push(target);
        vis.insert(target);
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                if(k==0){
                    while(!q.empty()){
                        res.push_back(q.front()->val);
                        q.pop();
                    }
                    return res;
                }

                TreeNode* f = q.front();
                q.pop();
                TreeNode* par = mp[f];
                if(f->left && vis.count(f->left)==0) {q.push(f->left);vis.insert(f->left);}
                if(f->right && vis.count(f->right)==0) {q.push(f->right);vis.insert(f->right);}
                if(par && vis.count(par)==0) {q.push(par);vis.insert(par);}
            }
            k--;
        }
        return res;
    }
};