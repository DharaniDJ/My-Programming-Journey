
// Problem Link : https://leetcode.com/problems/word-ladder/

// Appproach1(BFS) : O(n * n * w) time and O(n+e) space
// where n the size of wordList, w the length of the words in wordList and e is number of edges.
class Solution {
private:
    bool isAdj(string &a, string &b){
        int diff = 0;

        for(int i=0;i<a.size();i++){
            if(a[i]!=b[i]) diff++;
            if(diff==2) return false;
        }

        return diff==1;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.insert(wordList.begin(),beginWord);
        int n = wordList.size();

        vector<vector<int>> adj(n,vector<int>(0,0));

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(isAdj(wordList[i],wordList[j])){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        // perform bfs
        vector<bool> vis(n,false);
        queue<int> q;

        q.push(0);
        vis[0]=true;

        int dist = 0;

        while(!q.empty()){
            int sz = q.size();
            dist++;
            while(sz--){
                int node = q.front();
                q.pop();
                if(wordList[node]==endWord) return dist;

                for(auto e : adj[node]){
                    if(vis[e]==false){
                        q.push(e);
                        vis[e]=true;
                    }
                }
            }
        }
        return 0;
    }
};

// Approach2(Optimized BFS) :O(n * w * d) time and O(n+e) space complexity
// where n the size of wordList, w the size of the words, d the maximum degree of the graph and e is the number of edges.

// The above approach can be improved by computing adjacent nodes more efficiently
// Below a hash table is used to compute adjacent nodes.

class Solution {
private:
    bool isAdj(string &a, string &b){
        int diff = 0;

        for(int i=0;i<a.size();i++){
            if(a[i]!=b[i]) diff++;
            if(diff==2) return false;
        }

        return diff==1;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.insert(wordList.begin(),beginWord);

        int n = wordList.size();
        int w = beginWord.size();

        unordered_map<string, int> adjMap;
        for(int i=0;i<n;i++){
            adjMap[wordList[i]]=i;
        }
        vector<unordered_set<int>> adj(n);

        for(int i=0;i<n;i++){
            for(int c=0;c<w;c++){
                string curStr = wordList[i];
                char ch = curStr[c];
                for(int k=0;k<26;k++){
                    curStr[c]=k+'a';
                    if(adjMap.find(curStr)!=adjMap.end()){
                        adj[i].insert(adjMap[curStr]);
                        adj[adjMap[curStr]].insert(i);
                    }
                }
            }
        }

        // perform bfs
        vector<bool> vis(n,false);
        queue<int> q;

        q.push(0);
        vis[0]=true;

        int dist = 0;

        while(!q.empty()){
            int sz = q.size();
            dist++;
            while(sz--){
                int node = q.front();
                q.pop();
                if(wordList[node]==endWord) return dist;

                for(auto e : adj[node]){
                    if(vis[e]==false){
                        q.push(e);
                        vis[e]=true;
                    }
                }
            }
        }
        return 0;
    }
};

// Approach3(Bi-directional BFS)
// The above implementation can be improved by using bidirectional search, though experimentally the improvements
// in efficiency are not significant since for this particular strategy the greatest cost is creating the adjacency list.

class Solution {
private:
    int distA;
    int distB;
    int visitWordNode(vector<unordered_set<int>> & adj, queue<int> & q, vector<bool> & vis, vector<bool> & visRef, int &dist) {
        int sz = q.size();
        
        for(int i=0;i<sz;i++){
            auto node = q.front();
            q.pop();
            for(auto e : adj[node]){
                if(visRef[e]==true){
                    return distA+distB;
                }
                
                if(vis[e]==false){
                    vis[e]=true;
                    q.push(e);
                }
            }
        }
        dist++;
        return -1;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        wordList.insert(wordList.begin(),beginWord);
        
        int n = wordList.size();
        int w = beginWord.size();
        
        unordered_map<string, int> adjMap;
        for(int i=0;i<n;i++){
            adjMap[wordList[i]]=i;
        }
        vector<unordered_set<int>> adj(n);    
        
        int end = -1;
        for(int i=0;i<n;i++){
            if(endWord == wordList[i]) end = i;
            for(int c=0;c<w;c++){
                string curStr = wordList[i];
                char ch = curStr[c];
                for(int k=0;k<26;k++){
                    curStr[c]=k+'a';
                    if(adjMap.find(curStr)!=adjMap.end()){
                        adj[i].insert(adjMap[curStr]);
                        adj[adjMap[curStr]].insert(i);
                    }
                }
            }
        }
        
        if(end==-1) return 0;
        
        // perform bidirectional bfs
        vector<bool> visA(n,false);
        vector<bool> visB(n,false);
        queue<int> qA;
        queue<int> qB;
        
        qA.push(0);
        visA[0]=true;
        qB.push(end);
        visB[end]=true;
        
        distA = 1;
        distB = 1;
        
        int ans = -1;
        
        while(!qA.empty() && !qB.empty()){
            // cout << distA << " " << distB << endl;
            if(qA.size()<=qB.size()){
                ans = visitWordNode(adj,qA,visA,visB,distA);
            }else{
                ans = visitWordNode(adj,qB,visB,visA,distB);
            }
            // cout << ans << endl;
            if(ans>-1) return ans;
        }
                
        // target word cannot be reached
        return 0;
    }
};