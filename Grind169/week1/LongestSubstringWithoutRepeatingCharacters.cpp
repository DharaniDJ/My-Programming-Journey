
// Problem Link : https://leetcode.com/problems/longest-substring-without-repeating-characters/

// Brute force - O(n^3) time and O(1) space complexity
class Solution {
public:
    bool checkRepetitions(string &s, int l, int r){
        unordered_set<char> st;
        for(int i=l;i<=r;i++){
            if(st.count(s[i])) return false;
            st.insert(s[i]);
        }
        return true;
    }
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=i;j<n;j++){
                if(checkRepetitions(s,i,j)){
                    ans = max(ans,(j-i+1));
                }
            }
        }
        return ans;
    }
};

// sliding window - O(2*n) time and O(min(n.m)) space complexity
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> mp;
        int n =s.size();
        int l = 0;
        int r = 0;
        int ans = 0;
        while(r<n){
            mp[s[r]]++;
            while(mp[s[r]]>1){
                mp[s[l++]]--;
            }
            ans=max(ans,(r-l+1));
            r++;
        }
        return ans;
    }
};

// sliding window optimized - O(n) time and O(min(n,m)) space complexity

// The above solution requires at most 2n steps. In fact, it could be optimized to
// require only n steps. we could define a mapping of the characters to its index.
// Then we can skip the characters immediately when we found a repeated character.

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> mp(256,-1);
        int n = s.size();
        int l=0;
        int r=0;
        int ans = 0;
        while(r<n){
            if(mp[s[r]]!=-1){
                l = max(l,mp[s[r]]+1);
            }
            mp[s[r]]=r;
            ans=max(ans,r-l+1);
            r++;
        }
        return ans;
    }
};