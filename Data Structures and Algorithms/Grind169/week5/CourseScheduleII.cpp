
// Problem Link : https://leetcode.com/problems/course-schedule-ii

// Approach 1(DFS)
class Solution {
public:

    bool dfs(vector<vector<int>>& adj, int node, vector<bool> &vis, vector<bool> &pathVis,vector<int> &res){
        vis[node]=true;
        pathVis[node]=true;

        for(int neighbor : adj[node]){
            if(!vis[neighbor]){
                if(dfs(adj,neighbor,vis,pathVis,res)) return true;
            }else if(pathVis[neighbor]) return true;
        }
        pathVis[node]=false;
        res.push_back(node);
        return false;
    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> adj(n);
        for(auto e : prerequisites){
            adj[e[1]].push_back(e[0]);
        }
        vector<int> res;

        vector<bool> vis(n,false);
        vector<bool> pathVis(n,false); 


        for(int i=0;i<n;i++){
            if(!vis[i]){
                dfs(adj,i,vis,pathVis,res);
            }
        }

        if(res.size()!=n) return vector<int>();

        reverse(res.begin(),res.end());
        return res;
    }
};
// Topological Sort : O(v+e) time and O(v+e) space complexity
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<vector<int>> adj(n);

        vector<int> inorder(n);
        vector<int> res;

        for(auto e : prerequisites){
            inorder[e[0]]++;
            adj[e[1]].push_back(e[0]);
        }

        for(int i=0;i<n;i++){
            if(inorder[i]==0) res.push_back(i);
        }

        for(int i=0;i<res.size();i++){
            int x = res[i];
            for(auto j : adj[x]){
                inorder[j]--;
                if(inorder[j]==0) res.push_back(j);
            }
        }

        return res.size()==n ? res : vector<int>();
    }
};