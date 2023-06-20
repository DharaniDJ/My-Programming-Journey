
// Problem Link : https://leetcode.com/problems/letter-combinations-of-a-phone-number/

// Recursion : O(n*4^n) time and O(n) space complexity
// Note that 4 in this expression is referring to the maximum value length in the hash map, and not to the length of the input.

class Solution {
public:
    void solve(string &digits, int idx, unordered_map<char,vector<char>> &mp, string &temp, vector<string> &res){
        if(idx==digits.size()){
            res.push_back(temp);
            return;
        }

        char ch = digits[idx];
        for(auto c : mp[ch]){
            temp.push_back(c);
            solve(digits,idx+1,mp,temp,res);
            temp.pop_back();
        }
        return;
    }

    vector<string> letterCombinations(string digits) {
        vector<string> res;
        int n = digits.size();
        if(n==0) return res;
        unordered_map<char,vector<char>> mp;
        mp['2']={'a','b','c'};
        mp['3']={'d','e','f'};
        mp['4']={'g','h','i'};
        mp['5']={'j','k','l'};
        mp['6']={'m','n','o'};
        mp['7']={'p','q','r','s'};
        mp['8']={'t','u','v'};
        mp['9']={'w','x','y','z'};

        string temp = "";

        solve(digits,0,mp,temp,res);
        return res;
    }
};