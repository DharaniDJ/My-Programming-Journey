
// Problem Link : https://leetcode.com/problems/longest-palindromic-substring/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Bruteforce) : O(n^3) time and O(n) space complexity
// Intuition : check every possible substring whether it is a palindrome or not

class Solution {
public:
    bool checkPalindrome(string &s){
        int i = 0;
        int j = s.size()-1;
        while(i<j){
            if(s[i]!=s[j]) return false;
            i++;
            j--;
        }
        return true;
    }

    string longestPalindrome(string s) {

        int n = s.size();

        int mxLen = 0;
        string res;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                string str = s.substr(i,(j-i+1));
                if(checkPalindrome(str)){
                    if(mxLen<(j-i+1)){
                        mxLen = (j-i+1);
                        res = str;
                    }
                }
            }
        }

        return res;
    }
};

// Approach2(expand from center) : O(n^2) time and O(1) space complexity
class Solution {
public:
    
    pair<int,int> expand(string s, int i, int j){
        int n = s.size();
        while(i>=0 && j<n && s[i]==s[j]){
            i--;
            j++;
        }
        return {i+1,(j-i-1)};
    }
    string longestPalindrome(string s) {
        int n = s.size();
        
        int mxLen = 0;
        int idx = 0;
        
        for(int i=0;i<n;i++){
            auto it = expand(s,i,i);
            if(mxLen < it.second){
                mxLen = it.second;
                idx = it.first;
            }
            
            it = expand(s,i-1,i);
            if(mxLen < it.second){
                mxLen = it.second;
                idx = it.first;
            }
        }
        
        return s.substr(idx,mxLen);
    }
};