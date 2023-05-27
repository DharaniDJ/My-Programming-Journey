
// Problem Link: https://leetcode.com/problems/roman-to-integer/

// Approach 1 (Right to left pass): O(n) time and O(1) space complexity
// class Solution {
// public:
//     int romanToInt(string s) {
//         int n = s.size();
//         unordered_map<char,int> mp;
//         mp['I']=1;
//         mp['V']=5;
//         mp['X']=10;
//         mp['L']=50;
//         mp['C']=100;
//         mp['D']=500;
//         mp['M']=1000;
        
//         int ans=0;
//         for(int i=0;i<n;i++){
//             int cur = mp[s[i]];
//             int next = 0;
//             if(i<(n-1)){
//                 next = mp[s[i+1]];
//             }
            
//             if(next>cur){
//                 ans+=(next-cur);
//                 i++;
//             }else{
//                 ans+=cur;
//             }
//         }
//         return ans;
//     }
// };

// Approach 2 (Right to left pass): O(n) time and O(1) space complexity
class Solution {
public:
    int romanToInt(string s) {
        int n = s.size();
        unordered_map<char,int> mp;
        mp['I']=1;
        mp['V']=5;
        mp['X']=10;
        mp['L']=50;
        mp['C']=100;
        mp['D']=500;
        mp['M']=1000;
        
        int ans=0,num=0,prev=0;
        for(int i=n-1;i>=0;i--){
            int num = mp[s[i]];
            if(num>=prev){
                ans+=num;
            }else{
                ans-=num;
            }
            prev=num;
        }
        return ans;
    }
};