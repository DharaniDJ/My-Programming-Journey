
// Problem link: https://leetcode.com/problems/valid-parentheses/

// Approach 1 with vector - O(n) time and O(n) space complexity
class Solution {
public:
    bool isValid(string str) {
        int n = str.size();
        unordered_map<char,char> mp;
        vector<char> st;
        mp['(']=')';
        mp['{']='}';
        mp['[']=']';
        for(char c:str){
            if(mp.count(c)) st.push_back(c);
            else{
                if(st.size()==0) return false;
                else{
                    char tp = st.back();
                    if(mp[tp]==c) st.pop_back();
                    else return false;
                }
            }
        }
        return (st.size()==0);
    }
};


// Approach 2 with stack - O(n) time and O(n) space complexity
class Solution {
public:
    bool isValid(string str) {
        int n = str.size();
        unordered_map<char,char> mp;
        stack<char> st;
        mp['(']=')';
        mp['{']='}';
        mp['[']=']';
        for(char c:str){
            if(mp.count(c)) st.push(c);
            else{
                if(st.empty()) return false;
                else{
                    char tp = st.top();
                    if(mp[tp]==c) st.pop();
                    else return false;
                }
            }
        }
        return st.empty();
    }
};