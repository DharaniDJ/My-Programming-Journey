
// Problem Link : 

// DFS : O(n+m) time and O(n+m) space complexity
class Solution {
public:
    bool dfs(vector<vector<int>> &g, int node, vector<bool> &vis, vector<bool> &pathVis){
        vis[node]=true;
        pathVis[node]=true;
        for(int i:g[node]){
            if(!vis[i]){
                if(dfs(g,i,vis,pathVis)) return true;
             }else if(pathVis[i]) return true;
        }
        pathVis[node]=false;
        return false;
    }
    
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(n);
        
        for(auto it : prerequisites){
            g[it[1]].push_back(it[0]);
        }
        
        vector<bool>vis(n,false);
        vector<bool>pathVis(n,false);
        for(int i=0;i<n;i++){
             if(!vis[i]){
                 if(dfs(g,i,vis,pathVis)==true) return false;
             }
        }
        return true;
    }
};

// Topo Sort using Kahn's Algo : O(n+m) time and O(n+m) space complexity
class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<int> res;
        vector<int> inorder(n,0);
        vector<vector<int>> g(n);
        
        for(auto it : prerequisites){
            g[it[1]].push_back(it[0]);
            inorder[it[0]]++;
        }
        
        for(int i=0;i<n;i++){
            if(inorder[i]==0) res.push_back(i);
        }
        
        for(int i=0;i<res.size();i++){
            for(auto j:g[res[i]]){
                if(--inorder[j]==0) res.push_back(j);
            }
        }
        return res.size()==n;
    }
};