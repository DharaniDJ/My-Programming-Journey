
// Problem Link: https://leetcode.com/problems/evaluate-reverse-polish-notation/

// In-place Approach : O(n^2) time and O(1) space complexity
class Solution {
public:
    void delete2AtIndex(vector<string> &tokens, int d, int n){
        for(int i=d;i<n-2;i++){
            tokens[i] = tokens[i+2];
        }
    }
    
    bool checkOp(string s){
        return (s=="+" || s=="-" || s=="*" || s=="/");
    }
    
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        string s;
        string res;
        int curPos = 0;
        while(n>1){
            while(!checkOp(tokens[curPos])) curPos++;
            
            int a = stoi(tokens[curPos-1]);
            int b = stoi(tokens[curPos-2]);
            
            int res;
            if(tokens[curPos]=="+"){
                res = b+a;
            }else if(tokens[curPos]=="-"){
                res = b-a;
            }else if(tokens[curPos]=="*"){
                res = b*a;
            }if(tokens[curPos]=="/"){
                res = b/a;
            }
            tokens[curPos]=to_string(res);
            delete2AtIndex(tokens,curPos-2,n);
            curPos--;
            n-=2;
        }
        return stoi(tokens[0]);
    }
};

// Stack Approach : O(n) time and O(n) space complexity
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto it : tokens){
            if(it=="+" or it=="-" or it=="*" or it=="/"){
                int a = st.top();
                st.pop();
                int b = st.top();
                st.pop();
                if(it=="+") st.push(b+a);
                else if(it=="-") st.push(b-a);
                else if(it=="*") st.push(b*a);
                else if(it=="/") st.push(b/a);
            }else{
                st.push(stoi(it));
            }
        }
        return st.top();
    }
};