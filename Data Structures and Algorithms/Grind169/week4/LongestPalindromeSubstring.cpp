
// Problem Link : https://leetcode.com/problems/longest-palindromic-substring/

// Approach 1(BruteForce) : O(n^3) time and O(n) space complexity
class Solution {
public:
    bool checkPalindrome(string s){
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
        int mx = -1;
        string ans = "";
        int n = s.length();
        for(int i=0;i<n;i++){
            string str = "";
            for(int j=i;j<n;j++){
                str+=s[j];
                if(checkPalindrome(str)){
                    if(mx<(j-i+1)){
                        mx=(j-i+1);
                        ans=str;
                    }
                }
            }
        }
        return ans;
    }
};

// DP : O(n^2) time and O(n^2) space complexity
class Solution {
public:
    string longestPalindrome(string s) {
        vector<int> ans(2,0);
        int n = s.size();
        vector<vector<bool>> dp(n,vector<bool>(n,false));
        for(int i=0;i<n;i++) dp[i][i]=true;
        for(int i=0;i<(n-1);i++){
            if(s[i]==s[i+1]) {
                dp[i][i+1]=true;
                ans[0]=i;
                ans[1]=i+1;
            }
        }
        
        for(int diff=2;diff<n;diff++){
            for(int i=0;i<n-diff;i++){
                int j = i+diff;
                
                if(s[i]==s[j] && dp[i+1][j-1]){
                    dp[i][j]=true;
                    ans[0]=i;
                    ans[1]=j;
                }
            }
        }
        
        int i = ans[0];
        int j = ans[1];
        
        return s.substr(i,(j-i+1));
    }
};

// Approach3 (Expand from center) : O(n^2) time and O(1) space complexity
class Solution {
public:
    // return length
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
        int ans = 0;
        int idx = 0;

        for(int i=0;i<n;i++){
            pair<int,int> temp = expand(s,i,i);
            if(temp.second > ans){
                idx=temp.first;
                ans = temp.second;
            }

            temp = expand(s,i,i+1);
            if(temp.second > ans){
                idx=temp.first;
                ans = temp.second;
            }
        }
        cout << idx << "-" << ans;
        return s.substr(idx,ans);
    }
};

// Approach 4 (Manacher's Algorithm)
// TODO
