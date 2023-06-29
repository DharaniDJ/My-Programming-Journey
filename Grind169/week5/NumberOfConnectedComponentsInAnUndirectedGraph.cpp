
// Problem Link : https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

// DFS : O(v+e) time and O(e+v) space complexity
class Solution {
public:
void dfs(int v, vector<bool>&visited, vector<vector<int>>&adj){
    visited[v]=true;
    for(int i=0; i<adj[v].size(); i++){
        if(visited[adj[v][i]]==false)
            dfs(adj[v][i], visited, adj);
    }

}
    int countComponents(int n, vector<vector<int>>& edges) {
        int ans=0;
        vector<bool>vis(n, false);
        vector<vector<int>>adj(n);
        for(int i=0; i<edges.size(); i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }

        vector<bool> visited(n, false);
        for(int i=0; i<n; i++){
            if(visited[i]==false)
            {
                dfs(i,  visited, adj);
                ans++;
            }
        }

        return ans;
    }
};

// Disjoint Set Union : O(E*α(n)) time and O(V) space complexity
class Solution {
public:

    int findParent(vector<int> &parent,int x){
        if(x==parent[x]) return x;
        return x = findParent(parent,parent[x]);
    }

    int combine(vector<int> &parent, vector<int> &sz, int a, int b){
        int x = findParent(parent,a);
        int y = findParent(parent,b);

        if(a==b) return 0;

        if(sz[a]>=sz[b]){
            sz[a]+=sz[b];
            parent[b]=a;
        }else{
            sz[b]+=sz[a];
            parent[a]=b;
        }
        return 1;
    }
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<int> parent(n), sz(n);

        for(int i=0;i<n;i++){
            parent[i]=i;
            sz[i]=1;
        }

        int components = n;
        for(auto e : edges){
            components-=combine(parent,sz,e[0],e[1]);
        }

        return components;

    }
};