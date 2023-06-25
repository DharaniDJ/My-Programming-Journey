
// Problem Link : https://leetcode.com/problems/decode-string

// Recursion : O(n*maxK) time and O(m+n) space complexity
// where n = length of given string s and maxK = max possible value of K
// where m is the number of letters(a-z) and n is the number of digits(0-9) in string s
class Solution {
public:
    string decodeString(string s) {
        int idx = 0;
        return decodeString(s,idx);
    }

    string decodeString(const string& s, int& idx){
        string res;
        while(idx < s.length() && s[idx]!=']'){
            if(!isdigit(s[idx])){
                res+=s[idx++];
            }else{
                int k=0;
                while(idx<s.length() && isdigit(s[idx])){
                    k=k*10+(s[idx++]-'0');
                }
                idx++;
                string decodedString = decodeString(s,idx);
                idx++;
                while(k--){
                    res+=decodedString;
                }
            }
        }
        return res;
    }
};

// Using Stack (Iterative): O(n*maxK) time and O(m+n) space complexity
// where n = length of given string s and maxK = max possible value of K
// where m is the number of letters(a-z) and n is the number of digits(0-9) in string s
class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        stack<int> stCnt;

        string res ="";

        int n = s.size();
        string str = "";
        int k = 0;
        for(int i=0;i<n;i++){
            if(isdigit(s[i])){
                k = k*10+(s[i]-'0');
            }else if(s[i]=='['){
                stCnt.push(k);
                k=0;
                st.push(str);
                str="";
            }else if(s[i]==']'){
                string temp = st.top();
                st.pop();
                int cnt = stCnt.top();
                stCnt.pop();
                while(cnt--){
                    temp=temp+str;
                }
                str=temp;
            }else{
                str+=s[i];
            }
        }

        return str;
    }
};