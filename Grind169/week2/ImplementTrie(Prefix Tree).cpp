
// Problem Link: https://leetcode.com/problems/implement-trie-prefix-tree/

// Trie Approach : 
// Insertion : O(m) time and O(m) space complexity
// Search : O(m) time and O(1) space complexity
// Prefix : O(m) time and O(1) space complexity
class node{

public:
    node* child[26];
    bool isEnd;
    node(){
        isEnd = false;
        for(int i=0;i<26;i++) child[i]=nullptr;
    }
};

class Trie {
private:
    node* root;
public:
    Trie() {
        root = new node();
    }
    
    void insert(string word) {
        node* cur = root;
        for(char c : word){
            if(cur->child[c-'a']==nullptr){
                cur->child[c-'a']=new node();
            }
            cur=cur->child[c-'a'];
        }
        cur->isEnd=true;
    }
    
    bool search(string word) {
        node* cur = root;
        for(char c : word){
            if(cur->child[c-'a']==nullptr){
                return false;
            }
            cur=cur->child[c-'a'];
        }
        return cur->isEnd;
    }
    
    bool startsWith(string prefix) {
        node* cur = root;
        for(char c : prefix){
            if(cur->child[c-'a']==nullptr){
                return false;
            }
            cur=cur->child[c-'a'];
        }
        return true;
    }
};