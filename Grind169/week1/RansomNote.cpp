
// Problem Link: https://leetcode.com/problems/ransom-note/

// 2 Hashmap Approach: O(n+m) and O(1) space complexity
//where n and m are lengths of ransomNote and magazine respectively.
// class Solution {
// public:
//     bool canConstruct(string ransomNote, string magazine) {
//         unordered_map<char,int> ranMap, magMap;
//         for(char c:ransomNote) ranMap[c]++;
//         for(char c:magazine) magMap[c]++;

//         for(auto it : ranMap){
//             char c = it.first;
//             int cnt = it.second;
//             if(magMap.find(c)==magMap.end()){
//                 return false;
//             }
//             if(cnt > magMap[c]) return false;
//         }
//         return true;
//     }
// };

// 1 Hashmap or count array: O(n+m) time and O(1) space complexity,
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> cnt(26,0);
        for(char c:magazine) cnt[c-'a']++;
        for(char c:ransomNote){
            if(cnt[c-'a']==0) return false;
            cnt[c-'a']--;
        }
        return true;
    }
};

// Sorting and Stacks - O(m*logm) time and O(m) space complexity
// class Solution {
// public:
//     bool canConstruct(string ransomNote, string magazine) {
//         sort(ransomNote.begin(),ransomNote.end());
//         reverse(ransomNote.begin(),ransomNote.end());
//         sort(magazine.begin(),magazine.end());
//         reverse(magazine.begin(),magazine.end());

//         stack<char> ransomNoteStack,magazineStack;
//         for(char c:ransomNote) ransomNoteStack.push(c);
//         for(char c:magazine) magazineStack.push(c);

//         while(!ransomNoteStack.empty() && !magazineStack.empty()){
//             int s = magazineStack.top();
//             int t = ransomNoteStack.top();
//             if(s==t){
//                 magazineStack.pop();
//                 ransomNoteStack.pop();
//             }else if(s>t){
//                 return false;
//             }else{
//                 magazineStack.pop();
//             }
//         }
//         return ransomNoteStack.empty();
//     }
// };