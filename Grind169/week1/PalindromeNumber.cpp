
// Problem Link: https://leetcode.com/problems/palindrome-number/

// Approach 1(string comparision): O(n) time and O(n) space complexity
// class Solution {
// public:
//     bool isPalindrome(int x) {
//         string a = to_string(x);
//         string b = a;
//         reverse(a.begin(),a.end());
//         return a==b;
//     }
// };

// Approach 2(reverse number) : O(log n/log 10) time and O(1) space complexity
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0) return false;
        long long y = 0, k = x;
        while(k){
            y = y*10+(k%10);
            k/=10;
        }
        return x==y;
    }
};