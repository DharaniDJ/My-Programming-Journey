
// Problem Link : https://leetcode.com/problems/top-k-frequent-words

// Brute Force : O(nlogn) time and O(n) space complexity
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string,int> mp;
        for(string s : words){
            mp[s]++;
        }
        
        vector<pair<int,string>> ans;
        for(auto it : mp){
            ans.push_back({-it.second,it.first});
        }
        
        sort(ans.begin(),ans.end());
        
        vector<string> res;
        for(int i=0;i<k;i++){
            auto it = ans[i];
            res.push_back(it.second);
        }
        return res;
    }
};

// Max Heap : O(N*logk) time and O(n)(map), O(k)(maxheap) space complexity
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string,int> mp;
        for(string s : words) mp[s]++;

        // max_heap
        priority_queue< pair<int,string> > mxH;

        for(auto it : mp){
            mxH.push({-1*it.second, it.first});
            if(mxH.size()==k+1) mxH.pop();
        }

        vector<string> res;
        while(!mxH.empty()){
            res.push_back(mxH.top().second);
            mxH.pop();
        }
        reverse(res.begin(),res.end());
        return res;
    }
};

// Bucket sorting + trie : O(n) time and O(n) space complexity
class Solution {
public:
    int k;
    class TrieNode{
        public:
        TrieNode* child[26];
        bool isEnd;
        TrieNode(){
            for(int i=0;i<26;i++) child[i]=nullptr;
            isEnd = false;
        }
    };
    
    void addWord(TrieNode* root, string word){
        TrieNode* cur = root;
        for(char c : word){
            if(cur->child[c-'a']==nullptr) cur->child[c-'a']=new TrieNode();
            cur = cur->child[c-'a'];
        }
        cur->isEnd = true;
    }
    
    void getWord(TrieNode* root, string prefix, vector<string> &res){
        if(k==0) return;
        if(root->isEnd){
            k--;
            res.push_back(prefix);
        }
        
        for(int i=0;i<26;i++){
            if(root->child[i]!=nullptr) getWord(root->child[i], prefix + (char)('a' + i), res);
        }
        
    }
    
    vector<string> topKFrequent(vector<string>& words, int k) {
        int n = words.size();
        this->k = k;
        
        unordered_map<string,int> mp;
        for(string s : words) mp[s]++;
        
        vector<string> res;
        vector<TrieNode> bucket(n+1,TrieNode());
        for(auto& it : mp){
            addWord(&bucket[it.second], it.first);
        }
                
        for(int i=n;i>=0;i--){
            getWord(&bucket[i],"",res);
        }
        
        return res;
    }
};