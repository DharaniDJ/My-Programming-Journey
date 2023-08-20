

// Problem Link : https://leetcode.com/problems/clone-graph/


/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

// HashMap + DFS - O(n) time and O(n) space complexity
class Solution {
public:
    unordered_map<Node*,Node*> mp;
    
    Node* cloneGraph(Node* node) {
        if(node==nullptr) return nullptr;
        
        if(mp.find(node)!=mp.end()) return mp[node];
        
        mp[node] = new Node(node->val);
        
        for(auto it : node->neighbors){
            mp[node]->neighbors.push_back(cloneGraph(it));
        }
        
        return mp[node];
    }
};

// HashMap + BFS - O(n) time and O(n) space complexity
class Solution {
public:    
    Node* cloneGraph(Node* node) {
        if(node==nullptr) return nullptr;
        
        unordered_map<Node*,Node*> mp;
        mp[node] = new Node(node->val);
        queue<Node*> q;
        
        q.push(node);
        
        while(!q.empty()){
            auto f = q.front();
            q.pop();
            for(auto it : f->neighbors){
                if(mp.find(it)==mp.end()){
                    mp[it]=new Node(it->val);
                    q.push(it);
                }
                mp[f]->neighbors.push_back(mp[it]);
            }
        }
        
        return mp[node];
    }
};