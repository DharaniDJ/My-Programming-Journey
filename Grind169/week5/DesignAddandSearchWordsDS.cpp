
// Problem Link : https://leetcode.com/problems/design-add-and-search-words-data-structure/

// Approach 1 (Brute Force): O(n*m) time and O(n*m) space complexity
// gives TLE if we use set in place of vector
class WordDictionary {
    unordered_map<int,vector<string>>mp;
public:
    WordDictionary() {

    }
    void addWord(string word) {
        mp[word.size()].push_back(word);
    }

    bool search(string word) {
        for(auto& s:mp[word.size()]){
            bool fl = true;
            for(int i=0;i<s.size();i++){
                if(word[i]=='.') continue;
                if(s[i]!=word[i]){
                    fl=false;
                    break;
                }
            }
            if(fl) return true;
        }
        return false;
    }
};

// Trie Approach
// addWord : O(m) time and O(m) space complexity
// search : O(m) time and O(1)(if no dots in str) or O(m)(for recursion stack) space complexity
class Trie{
public:
    int val;
    bool isEnd;
    vector<Trie*> child;
    
    Trie(int v){
        val=v;
        child = vector<Trie*>(26,nullptr);
        isEnd = false;
    }
};

class WordDictionary {
    unordered_map<int,vector<string>>mp;
    Trie* root;
public:
    WordDictionary() {
        root = new Trie(-1);
    }
    void addWord(string word) {
        Trie* temp = root;
        for(char c:word){
            if(temp->child[c-'a']==nullptr){
                temp->child[c-'a'] = new Trie(c-'a');
            }
            temp = temp->child[c-'a'];
        }
        temp->isEnd = true;
    }
    
    bool search(string word){
        return searchInNode(root,word);
    }
    
    bool searchInNode(Trie* temp,string word) {
        
        for(int i=0;i<word.size();i++){
            char c = word[i];
            if(c=='.'){
                for(auto chldrn : temp->child){
                    if(chldrn!=nullptr && searchInNode(chldrn,word.substr(i+1))) return true;
                }
                return false;
            }else{
                if(temp->child[c-'a']==nullptr){
                    return false;
                }
                temp = temp->child[c-'a'];
            }
        }
        return temp->isEnd;
    }
};