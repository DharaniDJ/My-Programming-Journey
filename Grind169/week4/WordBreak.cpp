
// Problem Link : https://leetcode.com/problems/word-break

// Approach 1 (BFS) : O(n^3 + m*k) time and O(n + m*k) space complexity

// Intuition

// Let's imagine the indices of s as a graph. Each index can be thought of as a node,
// which represents building s up to the index.

// Adding a word to an existing string is like an edge between nodes.
// For a node start, we can move to node end if the substring of s between
// start, end exists in wordDict.

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        
        int n = s.size();
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        queue<int> q;
        vector<bool> vis(n,false);
        
        q.push(0);
        while(!q.empty()){
            int start = q.front();
            q.pop();
            
            if(start == n) return true;
            
            for(int end = start+1; end<=n; end++){
                if(vis[end]) continue;
                
                if(words.count(s.substr(start,end-start))){
                    vis[end]=true;
                    q.push(end);
                }
            }
        }
        return false;
    }
};

// Approach 2 (Top-Down DP) : O(n*m*k) time and O(n) space complexity
// Given n as the length of s, m as the length of wordDict, and k as the average length of the words in wordDict
class Solution {
public:
    vector<int> memo;
    vector<string> wordDict;
    string s;
    
    bool wordBreak(string s, vector<string>& wordDict) {
        memo = vector(s.length(), -1);
        this->wordDict = wordDict;
        this->s = s;
        return dp(s.length() - 1);
    }
    
    // Let's have a function dp that returns a boolean indicating if it is possible to build s up to and including the index i.
    bool dp(int i) {
        if (i < 0) return true;
        
        if (memo[i] != -1) {
            return memo[i] == 1;
        }
        
        for (string word: wordDict) {
            int currSize = word.length();
            // Handle out of bounds case
            if (i - currSize + 1 < 0) {
                continue;
            }

            if (s.substr(i - currSize + 1, currSize) == word && dp(i - currSize)) {
                memo[i] = 1;
                return true;
            }
        }
        
        memo[i] = 0;
        return false;
    }
};

// Approach 3 (Bottom up DP) :  O(n*m*k) time and O(n) space complexity
// dp[i]=any(s[i - word.length + 1, i]==word && dp[i - word.length])

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        vector<bool> dp(n+1,false);
        
        dp[0] = true;
        unordered_map<string,int> mp;
        for(auto it : wordDict){
            mp[it]=1;
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<=i;j++){
                if(mp[s.substr(j,i-j+1)] && dp[j]){
                    dp[i+1]=true;
                    break;
                }
            }
        }
        return dp[n];
    }
};

// Trie Approach : O(n^2 + m*k) time and O(n+m*k) space complexity
class TrieNode{
public:
    bool isWord;
    unordered_map<char,TrieNode*> children;
    TrieNode(){
        isWord=false;
        children = unordered_map<char, TrieNode*>();
    }
    
    void insert(string word){
        TrieNode* cur = this;
        for(auto c : word){
            if(cur->children.find(c)==cur->children.end()){
                cur->children[c] = new TrieNode();
            }
            cur = cur->children[c];
        }
        cur->isWord = true;
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.length();
        TrieNode* root = new TrieNode();
        for(string word :wordDict){
            root->insert(word);
        }
        
        vector<int> dp(n);
        for(int i=0;i<n;i++){
            if(i==0 || dp[i-1]){
                TrieNode* cur = root;
                for(int j=i;j<n;j++){
                    char c = s[j];
                    
                    if(cur->children.find(c)==cur->children.end()){
                        break;
                    }
                    cur = cur->children[c];
                    if(cur->isWord){
                        dp[j]=true;
                    }
                }
            }
        }
        return dp[n-1];
    }
};