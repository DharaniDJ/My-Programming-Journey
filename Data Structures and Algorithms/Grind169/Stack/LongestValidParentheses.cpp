
// Problem Link : https://leetcode.com/problems/longest-valid-parentheses/

// Approach1(Brute Force) : O(n^3) time and O(n) space complexity
class Solution {
public:

    bool checkValidParenthese(string s){
        stack<char> st;
        for(auto c : s){
            if(c=='('){
                st.push(c);
            }else if(!st.empty() && st.top()=='('){
                st.pop();
            }else{
                return false;
            }
        }
        return st.empty();
    }

    int longestValidParentheses(string s) {
        int n = s.size();
        int ans = 0;

        for(int i=0;i<n;i++){
            for(int j=i+2;j<=n;j+=2){
                if(checkValidParenthese(s.substr(i,j-i))){
                    ans = max(ans,j-i);
                }
            }
        }

        return ans;
    }
};

// Optimized Brute Force : O(n^2) time and O(n) space complexity
class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0, count = 0;
        int n = s.length();
        for (int i = 0; i < n; i++) {
            count = 0;
            for (int j = i; j < n; j++) {
                if (s[j] == '(') {
                    count++;
                } else {
                    count--;
                }

                if (count < 0) {
                    break;
                }

                if (count == 0) {
                    if (j - i + 1 > ans) {
                        ans = j - i + 1;
                    }
                }
            }
        }
        return ans;
    }
};

// Approach2(Using DP): O(n) time and O(n) space complexity
// dp[i] - represents the longest valid substring ending at ith index.
// It is obvious that the valid substring must end with ')'
// This further leads to the conclusion that the substrings ending with ‘(’ will always contain '0' at their corresponding
// dp indices. Thus, we update the dp array only when ‘)’ is encountered.

// To fill dp array, we will check
// 1. s[i]=')' and s[i-1]='(' => dp[i] = dp[i-2]+2;
// 2. s[i]=')' and s[i-1]=')' => if s[i-dp[i-1]-1] = '(' then dp[i] = dp[i-1] + dp[i-dp[i-1]-2] + 2

class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        int n = s.length();
        // represents the longest valid substring ending at ith index.
        vector<int> dp(n,0);

        for(int i=1;i<n;i++){
            if(s[i]==')'){
                if(s[i-1]=='('){
                    dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
                }else if(i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '('){
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                ans = max(ans,dp[i]);
            }
        }
        return ans;
    }
};

// Approach3(using stack) : O(n) time and O(n) space complexity
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int ans = 0;

        stack<int> st;
        st.push(-1);

        for(int i=0;i<n;i++){
            if(s[i]=='('){
                st.push(i);
            }else{
                st.pop();
                if(st.empty()){
                    st.push(i);
                }else{
                    ans = max(ans,i-st.top());
                }
            }
        }
        return ans;
    }
};

// Approach4(without extra space) : O(n) time and O(1) space complexity

// Intuition : This solution is inspired by maximum sum of subsequence.
// However, when we scan from left side, we can only find the expression unbalanced when ')' appears too often,
// and '(' should also be checked for balance, so we should scan again from right side.

class Solution {
public:
    int longestValidParentheses(string s) {
        int ans = 0;
        int n = s.length();

        int left = 0, right = 0;

        for(int i=0;i<n;i++){
            if(s[i]=='(') left++;
            else right++;

            if(right==left){
                ans = max(ans, 2*left);
            }else if(right>left){
                left=0;
                right=0;
            }
        }

        left = 0, right = 0;

        for(int i=n-1;i>=0;i--){
            if(s[i]=='(') left++;
            else right++;

            if(right==left){
                ans = max(ans, 2*left);
            }else if(left>right){
                left=0;
                right=0;
            }
        }

        return ans;
    }
};