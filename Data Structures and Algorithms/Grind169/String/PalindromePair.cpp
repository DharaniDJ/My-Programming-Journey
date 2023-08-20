
// Problem Link : https://leetcode.com/problems/palindrome-pairs/

// Appraoch1(Bruteforce) : O(n^2 * k) time and O(n^2 + k) auxilary space and O(n*k + n^2) space
class Solution {
public:
    bool checkPalindrome(string &s){
        int i = 0;
        int j = s.length()-1;

        while(i<j){
            if(s[i]!=s[j]) return false;
            i++;
            j--;
        }
        return true;
    }

    vector<vector<int>> palindromePairs(vector<string>& words) {

        vector<vector<int>> res;

        int n = words.size();
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(i!=j){
                    string word = words[i]+words[j];
                    if(checkPalindrome(word)){
                        res.push_back({i,j});
                    }
                }
            }
        }

        return res;
    }
};

// Approach2(using hashing) : O(n * k^2) time and O((k+n)^2) space complexity
/*
1. Check if the reverse of word is present. If it is, then we have a case 1 pair by appending the reverse onto the end of word.
2. For each suffix of word, check if the suffix is a palindrome. if it is a palindrome, then reverse the remaining prefix and check if it's in the list.
3. For each prefix of word, check if the prefix is a palindrome. if it is a palindrome, then reverse the remaining suffix and check if it's in the list.
*/
class Solution {
private:
    vector<string> allValidPrefixes(string word){
        vector<string> validPrefixes;
        for(int i=0;i<(int)word.size();i++){
            if(isPalindrome(word,i,(int)word.size()-1)){
                validPrefixes.push_back(word.substr(0,i));
            }
        }
        return validPrefixes;
    }
    
    vector<string> allValidSuffixes(string word){
        vector<string> validSuffixes;
        for(int i=0;i<(int)word.size();i++){
            if(isPalindrome(word,0,i)){
                validSuffixes.push_back(word.substr(i+1,(int)word.size()-i-1));
            }
        }
        return validSuffixes;
    }
    
    bool isPalindrome(string word, int l, int r){
        while(l<r){
            if(word[l]!=word[r]) return false;
            l++;
            r--;
        }
        return true;
    }
    
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string, int> wordSet;
        
        // Build a word -> original index mapping for efficient lookup.
        for(int i=0;i<(int)words.size();i++) wordSet[words[i]]=i;
        
        vector<vector<int>> res;
        
        for(int i=0;i<(int)words.size();i++){
            string word = words[i];
            int curWordIdx = i;
            
            string reversedWord = word;
            reverse(reversedWord.begin(),reversedWord.end());
            
            // Build solutions of case #1. This word will be word 1.
            if(wordSet.find(reversedWord)!=wordSet.end() && curWordIdx!=wordSet[reversedWord]){
                res.push_back({curWordIdx, wordSet[reversedWord]});
            }
            
            // Build solutions of case #2. This word will be word 2.
            for(string suffix : allValidSuffixes(word)){
                string reversedSuffix = suffix;
                reverse(reversedSuffix.begin(),reversedSuffix.end());
                
                if(wordSet.find(reversedSuffix)!=wordSet.end()){
                    res.push_back({wordSet[reversedSuffix],curWordIdx});
                }
            }
            
            // Build solutions of case #3. This word will be word 1.
            for(string prefix : allValidPrefixes(word)){
                string reversedPrefix = prefix;
                reverse(reversedPrefix.begin(),reversedPrefix.end());
                
                if(wordSet.find(reversedPrefix)!=wordSet.end()){
                    res.push_back({curWordIdx,wordSet[reversedPrefix]});
                }
            }
        }
        return res;
    }
};

// Approach3(Trie) : O(n * k^2) time and O((k+n)^2) space complexity
class TrieNode{
public:
    int wordEnding = -1; // we'll use -1 to mean there's no word ending here.
    unordered_map<char,TrieNode*> next;
    vector<int> palindromePrefixRemaining;
};

class Solution {
public:

    // Is the given string a palindrome after index i?
    // Tip: Leave this as a method stub in an interview unless you have time
    // or the interviewer tells you to write it. The Trie itself should be
    // the main focus of your time.
    bool hasPalindromeRemaining(string &s, int i) {
        int p1 = i;
        int p2 = s.length() - 1;
        while (p1 < p2) {
            if (s[p1] != s[p2]) return false;
            p1++; p2--;
        }
        return true;
    }
    
    vector<vector<int>> palindromePairs(vector<string>& words) {
        TrieNode* root = new TrieNode();
        
        // build the trie
        for(int id = 0; id<(int)words.size(); id++){
            string word = words[id];
            string reversedWord = words[id];
            reverse(reversedWord.begin(),reversedWord.end());
            
            TrieNode* cur = root;
            
            for(int j=0;j<(int)word.size();j++){
                if(hasPalindromeRemaining(reversedWord,j)){
                    cur->palindromePrefixRemaining.push_back(id);
                }
                
                char c = reversedWord[j];
                
                if(cur->next.find(c)==cur->next.end()){
                    cur->next[c]=new TrieNode();
                }
                
                cur = cur->next[c];
            }
            
            cur->wordEnding = id;
        }
        
        // find pairs
        vector<vector<int>> res;
        for(int id = 0; id<(int)words.size(); id++){
            string word = words[id];
            TrieNode* cur = root;
            
            for(int j=0;j<(int)word.size();j++){
                if(cur->wordEnding != -1 && hasPalindromeRemaining(word,j)){
                    res.push_back({id,cur->wordEnding});
                }
                
                char c = word[j];
                cur = cur->next[c];
                if(!cur) break;
            }
            
            if(!cur) continue;
            
            if(cur->wordEnding != -1 && cur->wordEnding != id){
                res.push_back({id,cur->wordEnding});
            }
            
            for(int other : cur->palindromePrefixRemaining){
                res.push_back({id,other});
            }
        }
        return res;
    }
};