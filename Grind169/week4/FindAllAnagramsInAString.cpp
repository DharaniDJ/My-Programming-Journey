
// Problem Link : https://leetcode.com/problems/find-all-anagrams-in-a-string

// Sliding Window with Array : O(n) time and O(26) which is O(1) space complexity
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<int> res;
        if(m>n) return res;

        vector<int> mp(26,0),mp1(26,0);

        for(char c:p) mp[c-'a']++;

        for(int i=0;i<m;i++) mp1[s[i]-'a']++;
        if(mp==mp1) res.push_back(0);
        for(int i=m;i<n;i++){
            mp1[s[i-m]-'a']--;
            mp1[s[i]-'a']++;
            if(mp==mp1) res.push_back(i-m+1);
        }
        return res;
    }
};