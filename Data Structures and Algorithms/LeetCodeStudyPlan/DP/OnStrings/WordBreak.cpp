
// Problem Link : https://leetcode.com/problems/word-break/?envType=study-plan-v2&envId=dynamic-programming

// Approach1 (Recursion) : O(n^3) time and O(n) space complexity
class Solution {
public:

    bool solve(string s, int idx, vector<string>& wordDict){
        if(idx==s.size()) return true;

        for(int i = idx;i<s.size();i++){
            string str = s.substr(idx,(i-idx+1));
            if(find(wordDict.begin(),wordDict.end(),str)!=wordDict.end()){
                if(solve(s,i+1,wordDict)) return true;
            }
        }

        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        return solve(s,0,wordDict);
    }
};

// Approach2(Recursion + Memoization) : O(n*m*k) time and O(n) space complexity
// where n=len(s), m=len(wordDict) and k is the average length of the words in wordDict.
class Solution {
public:
    
    bool solve(string s, int idx, vector<string>& wordDict, vector<int>& dp){
        if(idx==s.size()) return true;
        
        if(dp[idx]!=-1) return dp[idx]==0 ? false : true;
        for(int i = idx;i<s.size();i++){
            string str = s.substr(idx,(i-idx+1));
            if(find(wordDict.begin(),wordDict.end(),str)!=wordDict.end()){
                if(solve(s,i+1,wordDict,dp)){
                    dp[idx]=1;
                    return true;
                }
            }
        }
        
        dp[idx]=0;
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<int> dp(n,-1);
        return solve(s,0,wordDict,dp);
    }
};

// Approach3(Bottom Up DP) : O(n*m*k) time and O(n) space complexity
// where n=len(s), m=len(wordDict) and k is the average length of the words in wordDict.
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n,false);
        
        for(int i=0;i<n;i++){
            for(string word : wordDict){
                if(i<word.size()-1) continue;
                
                if(i==word.size()-1 || dp[i-word.size()]){
                    if(s.substr(i-word.size()+1,word.size())==word) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }
        
        return dp[n-1];
    }
};

class TrieNode{
public:
    bool isWord;
    unordered_map<char,TrieNode*> children;
    
    TrieNode(){
        isWord = false;
        children = unordered_map<char,TrieNode*>();
    }
    
    void insert(string word){
        TrieNode* cur = this;
        for(auto c : word){
            if(cur->children.count(c)==0){
                cur->children[c]=new TrieNode();
            }
            cur = cur->children[c];
        }
        
        cur->isWord = true;
    }
};

// Approach(Trie) : O(n^2 + m*k) time and O(n + m*k) space complexity
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        TrieNode* root = new TrieNode();
        
        for(string word : wordDict){
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