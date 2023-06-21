
// Problem Link : https://leetcode.com/problems/minimum-height-trees/

// Approach 1(BruteForce)(TLE) : O(n^2) time and O(n) space complexity
class Solution {
public:
    int height(int node, unordered_map<int,vector<int>> &mp,int parent){
        
        int mn = 0;
        for(auto it : mp[node]){
            if(it!=parent) mn = max(mn,height(it,mp,node)+1);
        }
        
        return mn;
    }
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        unordered_map<int,vector<int>> mp;
        for(auto it : edges){
            mp[it[0]].push_back(it[1]);
            mp[it[1]].push_back(it[0]);
        }
        vector<int> res;
        int ans = INT_MAX;
        for(int i=0;i<n;i++){
            int ht = height(i,mp,-1);
            if(ans>ht){
                ans=ht;
                res.clear();
                res.push_back(i);
            }else if(ans==ht){
                res.push_back(i);
            }
        }
        return res;
    }
};

// Topological Sort : O(|V|) time and O(|V|) space complexity(to construct graph and store leaves in vector)

// we can rephrase the problem as finding out the nodes that are overall close
// to all other nodes, especially the leaf nodes.

// Before we proceed, here we make one assertion which is essential to the algorithm.
// For the tree-alike graph, the number of centroids is no more than 2.

// we could prove by contradiction. Suppose that we have 3 centroids in the graph,
// if we remove all the non-centroid nodes in the graph, then the 3 centroids nodes must form a triangle shape
// Because these centroids are equally important to each other, and they should equally close to each other as well.
// If any of the edges that is missing from the triangle, then the 3 centroids would be reduced down to a single centroid.

// However, the triangle shape forms a cycle which is contradicted to the condition that there is no cycle in our tree-alike graph.
// Similarly, for any of the cases that have more than 2 centroids, they must form a cycle among the centroids, which is contradicted to our condition.

// Therefore, there cannot be more than 2 centroids in a tree-alike graph.

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        
        if(n<2){
            vector<int> res;
            for(int i=0;i<n;i++) res.push_back(i);
            return res;
        }
        
        vector<int> adj[n];
        for(int i=0;i<n;i++){
            adj[i] = {};
        }
        
        for(auto e : edges){
            int start = e[0];
            int end = e[1];
            adj[start].push_back(end);
            adj[end].push_back(start);
        }
        
        vector<int> leaves;
        for(int i=0;i<n;i++) if(adj[i].size()==1) leaves.push_back(i);
        
        int remNodes = n;
        while(remNodes>2){
            remNodes-=leaves.size();
            
            vector<int> newLeaves;
            
            for(int leaf : leaves){
                int neighbor = adj[leaf][0];
                auto it = find(adj[neighbor].begin(),adj[neighbor].end(),leaf);
                adj[neighbor].erase(it);
                if(adj[neighbor].size()==1) newLeaves.push_back(neighbor);
            }
            
            leaves=newLeaves;
        }
        return leaves;
    }
};