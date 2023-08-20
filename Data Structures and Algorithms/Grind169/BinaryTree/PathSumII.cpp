
// Problem Link : https://leetcode.com/problems/path-sum-ii

// Approach1(Recursion)(DFS) : O(n^2) time and O(n) space complexity
// O(n) operation of copying over the temp nodes to a new list to be added to the final res
class Solution {
public:
    void solve(TreeNode* root, int targetSum, vector<int> &temp, vector<vector<int>> &res){
        if(!root) return;

        temp.push_back(root->val);

        if(targetSum==root->val && !root->left && !root->right){
            res.push_back(temp);
        }else{
            solve(root->left,targetSum-(root->val),temp,res);
            solve(root->right,targetSum-(root->val),temp,res);
        }

        temp.pop_back();
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> res;
        vector<int> temp;

        solve(root,targetSum,temp,res);

        return res;
    }
};

// BFS : O(n^2) time and O(n) space complexity
class Solution {
public:
    bool isLeaf(TreeNode* root){
        return !root->left && !root->right;
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        queue<pair<TreeNode*,pair<int,vector<int> > > > q;
        vector<vector<int>> res;

        if(!root) return res;

        q.push({root,{root->val,{root->val}}});

        while(!q.empty()){
            auto f = q.front();
            q.pop();
            TreeNode* cur = f.first;
            int curSum = f.second.first;
            vector<int> curPathNodes = f.second.second;

            if(isLeaf(cur) && curSum==targetSum){
                res.push_back(curPathNodes);
            }

            if(cur->left){
                vector<int> leftPath = curPathNodes;
                leftPath.push_back(cur->left->val);
                q.push({cur->left,{curSum + cur->left->val,leftPath}});
            }

            if(cur->right){
                vector<int> rightPath = curPathNodes;
                rightPath.push_back(cur->right->val);
                q.push({cur->right,{curSum + cur->right->val,rightPath}});
            }
        }
        return res;
    }
};