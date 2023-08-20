
// Problem Link: https://leetcode.com/problems/longest-common-prefix/

// Approach 1 (Horizontal scanning) : O(S) time andd O(1) space complexity , where S is the sum of all characters in all strings
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        string str = strs[0];
        string temp;
        for(int i=1;i<(int)strs.size();i++){
            int l = 0;
            int r = 0;
            temp="";
            while(l<str.length() && r<strs[i].length() && str[l]==strs[i][r]){
                temp+=str[l];
                l++;
                r++;
            }
            str=temp;
        }
        return str;
        
    }
};

// Approach 2 (Vertical scanning): O(S) time andd O(1) space complexity , where S is the sum of all characters in all strings
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        for(int i=0;i<strs[0].size();i++){
            char c = strs[0][i];
            for(int j=1;j<strs.size();j++){
                if(i==strs[j].size() || strs[j][i]!=c){
                    return strs[0].substr(0,i);
                }
            }
        }
        return strs[0];
        
    }
};

// Approach 3 (Trie) : O(S) time andd O(S) space complexity , where S is the sum of all characters in all strings
class TrieNode{
 public:
 char data;
 TrieNode*children[26];
 int numChild;
 bool isTerminal;

 TrieNode(char ch){
    data=ch;
    for(int i=0;i<26;i++)
      children[i]=NULL;

    isTerminal=false;
    numChild=0;
 }
};

class Trie{
    public:
     TrieNode*root;

     Trie(char ch){
        root=new TrieNode(ch);
     }
    
    void insertUtil(TrieNode*root,string word){

        if(word.length()==0){
            root->isTerminal=true;
            return;
        }

        int idx=word[0]-'a';
        TrieNode*child;

        if(root->children[idx]!=NULL){
            child=root->children[idx];
        }

        else{
            child= new TrieNode(word[0]);
            root->children[idx]=child;
            root->numChild++;
        }


        insertUtil(child,word.substr(1));
    }
    void insertWord(string word){
        return insertUtil(root,word);
    }

    void lcp(string word, string &ans){

      for(int i=0;i<word.length();i++) {
          char ch=word[i];
          if(root->numChild==1){
              ans.push_back(ch);
              int idx=ch-'a';
              root=root->children[idx];
          }
          else break;

          if(root->isTerminal) break;
      }
    
    }

};
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        Trie*t= new Trie('\0');

        for(int i=0;i<strs.size();i++){
            if(strs[i]=="") return  "";
            t->insertWord(strs[i]);
        }
        string ans="";
        t->lcp(strs[0],ans);
        return ans;
    }
};