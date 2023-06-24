
// Problem Link : https://leetcode.com/problems/graph-valid-tree

// Approach 1(Basic Graph Theory and DFS) : O(v+e) time and O(v+e) for graph and O(n) for dfs space complexity

// Graph g is a tree iff
// a) g is fully connected and
// b) not cycle exists
class Solution {
public:
    bool dfs(vector<vector<int>> &adj, int node, int parent, vector<bool> &vis, vector<int> &res){
        vis[node] = true;
        res.push_back(node);

        for(int neighbor : adj[node]){
            if(neighbor==parent) continue;
            if(vis[neighbor]) return false;
            bool fl = dfs(adj,neighbor,node,vis,res);
            if(!fl) return false;
        }
        return true;
    }
    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>>adj(n);
        for(auto e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> res;
        vector<bool> vis(n,false);

        return dfs(adj,0,-1,vis,res) && res.size()==n;
    }
};

// Approach 2 (Advanced Graph Theory + DFS) : (Before constructing the graph itself, we know e = n-1)O(n) time and O(n) space complexity

// Graph g is a tree iff
// a) g has n-1 edges
//      1) any less, it can't possibly fully connected
//      2) anymore, then it contains cycle
// b) 1 connected component

class Solution {
public:
    void dfs(vector<vector<int>> &adj, int node, unordered_set<int> &vis){
        if(vis.count(node)) return;

        vis.insert(node);
        for(int neighbor : adj[node]){
            dfs(adj,neighbor,vis);
        }
        return;
    }
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size()!=n-1) return false;

        vector<vector<int>>adj(n);
        for(auto e : edges){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        unordered_set<int> vis;

        dfs(adj,0,vis);

        return vis.size()==n;
    }
};

// Approach 3(Advanced Graph Theory + UnionFind) : O(n*α(n)) time and O(n) space complexity
// It turns out that find(...) amortizes to O(α(N)), where α is the Inverse Ackermann Function.

// Graph g is a tree iff
// a) g has n-1 edges
//      1) any less, it can't possibly fully connected
//      2) anymore, then it contains cycle
// b) not cycle exists


// Approach 2 had a lot of overhead in needing to create an adjacency list with the edges before it could even begin the depth-first search.
// This is all treated as a constant, as it ultimately had the same time complexity as the depth-first search itself.

// Approach 3 doesn't need to change the input format, it can just get straight to determining whether or not there is a cycle.
// Additionally the bit that stops it being constant, the α(N), will never have a value larger than 4.
// So in practice, it behaves as a constant too—and a far smaller one at that!

class UnionFind{
private:
    vector<int> parent;
    vector<int> sz;
public:
    UnionFind(int n){
        parent.resize(n);
        sz.resize(n,1);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }

    int findParent(int x){
        if(parent[x]==x) return x;
        return parent[x]=findParent(parent[x]);
    }

    bool doUnion(int x, int y){
        int a = findParent(x);
        int b = findParent(y);

        if(a==b) return false;

        if(sz[a]>sz[b]){
            parent[b]=a;
            sz[a]+=sz[b];
        }else{
            parent[a]=b;
            sz[b]+=sz[a];
        }
        return true;
    }
};
class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if(edges.size()!=n-1) return false;

        UnionFind uf(n);

        for(auto e : edges){
            int a = e[0];
            int b = e[1];
            if(!uf.doUnion(a,b)) return false;
        }
        return true;
    }
};