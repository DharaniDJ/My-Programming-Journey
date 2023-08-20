
// Problem Link : https://leetcode.com/problems/group-anagrams

// Categorize with sorted strings : O(nk*logk) time and O(nk) space complexity
// where n is length of strs and k is max length of string in strs

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mp;
        vector<vector<string>> res;
        for(string s : strs){
            string temp = s;
            sort(temp.begin(),temp.end());
            mp[temp].push_back(s);
        }

        for(auto it:mp){
            res.push_back(it.second);
        }
        return res;
    }
};

// Categorize by Count : O(nk) time and O(nk) space complexity
// We can transform each string sinto a character count, count, consisting of 26 non-negative integers
// representing the number of a's, b's, c's, etc. We use these counts as the basis for our hash map.

// The hashable representation of our count will be a string delimited with '#' characters.
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> mp;
        vector<vector<string>> res;

        vector<int> cnt(26,0);
        for(string s : strs){
            fill(cnt.begin(), cnt.end(), 0);
            for(char c : s) cnt[c-'a']++;

            string str = "";
            for(int i=0;i<26;i++){
                str+='#';
                str+=to_string(cnt[i]);
            }
            mp[str].push_back(s);
        }

        for(auto it:mp){
            res.push_back(it.second);
        }
        return res;
    }
};