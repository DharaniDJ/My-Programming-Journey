
// Problem link: https://leetcode.com/problems/valid-anagram/

// Sort and Compare - O(n*logn) time and O(1) space complexity
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(),s.end());
        sort(t.begin(),t.end());
        return s==t;
    }
};


// Count array - O(n) time and O(n) space complexity
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()) return false;
        vector<int> a(26,0);
        for(char c:s) a[c-'a']++;
        for(char c:t) a[c-'a']--;
        for(int i:a){
            if(i!=0) return false;
        }
        return true;
    }
};