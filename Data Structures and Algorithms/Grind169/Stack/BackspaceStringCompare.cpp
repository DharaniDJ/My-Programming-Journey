
// Problem Link: https://leetcode.com/problems/backspace-string-compare/

// Approach 1 (stack): O(n+m) time and O(n+m) space complexity
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        stack<char> a,b;
        for(char c:s){
            if(c!='#') a.push(c);
            else if(a.empty()==false) a.pop();
        }
        
        for(char c:t){
            if(c!='#') b.push(c);
            else if(b.empty()==false) b.pop();
        }
        if(a.size()!=b.size()) return false;
        while(!a.empty()){
            char atop = a.top();
            char btop = b.top();
            if(atop!=btop) return false;
            a.pop();
            b.pop();
        }
        return true;
    }
};

// Two pointer: O(n+m) time and O(1) space complexity
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int i = s.size()-1, j = t.size()-1;
        
        int skipS = 0, skipT = 0;
        while(i>=0 || j>=0){
            while(i>=0){
                if(s[i]=='#') {skipS++; i--;}
                else if(skipS > 0){skipS--; i--;}
                else break;
            }
            
            while(j>=0){
                if(t[j]=='#') {skipT++; j--;}
                else if(skipT > 0){skipT--; j--;}
                else break;
            }
            
            // If expecting to compare char vs nothing
            if(i>=0 && j>=0 && s[i]!=t[j]) return false;
            
            if ((i >= 0) != (j >= 0))
                return false;
            i--;
            j--;
        }
        return true;
    }
};