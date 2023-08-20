

// Problem Link : https://leetcode.com/problems/generate-parentheses/

// Brute Force : O(2^2n) time and O(2^2n) space complexity
// Generate all possible combinations i.e 2^2n unique strings and check if it is a valid parathesis

class Solution {
public:
    bool isValid(string &s){
        int n = s.size();
        if(n%2) return false;

        int cnt = 0;
        for(char c : s){
            if(c=='(') cnt++;
            else cnt--;

            if(cnt<0) return false;
        }
        return cnt==0;
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        queue<string> q;
        q.push("");
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                string s = q.front();
                q.pop();
                if(s.size()==2*n){
                    if(isValid(s)){
                        ans.push_back(s);
                    }
                    continue;
                }
                q.push(s+"(");
                q.push(s+")");
            }
        }
        return ans;
    }
};

// Backtracking : O((4^n)/(n^0.5)) (catalan number) time and O(n) space complexity
class Solution {
public:
    void solve(int n, string s,int openCnt, int closeCnt, vector<string> &ans){

        if(closeCnt>openCnt) return;

        if(openCnt>n) return;

        if((int)s.size()==2*n) {
            ans.push_back(s);
            return;
        }

        solve(n,s+'(',openCnt+1,closeCnt,ans);
        solve(n,s+')',openCnt,closeCnt+1,ans);
        return;
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        int openCnt = 0;
        int closeCnt = 0;
        string s = "";
        solve(n,s,openCnt,closeCnt,ans);
        return ans;
    }
};

// Let F(n) denote the set of all valid strings of length 2n.
// We have just deduced the number of valid strings formed with n pairs of parentheses
// F(n) = F(0)*F(n - 1) + F(1)*F(n - 2) + ... + F(n - 1)*F(0)

// F(n) = '(' + F(0) + ')' + F(n-1)

// Looks familiar?

// Here we can find the connection between this number and the answer. According to the definition, the general formula for Catalan numbers is
// C(n) = C(0) * C(n - 1) + C(1) * C(n - 2) + ... + C(n - 1) * C(0)

// Divide and Conquer :  O((4^n)/(n^0.5)) (catalan number) time and O(n) space complexity
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n==0){
            return {""};
        }

        vector<string> ans;

        for(int i=0;i<n;i++){
            for(string leftString : generateParenthesis(i)){
                for(string rightString : generateParenthesis(n-i-1)){
                    string temp = '(' + leftString + ')' + rightString;
                    ans.push_back(temp);
                }
            }
        }
        return ans;
    }
};