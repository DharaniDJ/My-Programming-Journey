
// Problem link: https://leetcode.com/problems/valid-palindrome/

// Approach 1 - O(n) time and O(n) space complexity
class Solution {
public:
    
    bool isPalindrome(string s) {
        string res="";
        for(char c:s){
            if(isalnum(c)){
                res+=tolower(c);
            }
        }
        string temp = res;
        
        reverse(res.begin(),res.end());
        return res==temp;
    }
};


// Two pointers - O(n) time and O(1) space complexity
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.size();
        for (int i = 0, j = n - 1; i < j; i++, j--) {
          while (i < j && !isalnum(s[i])) i++;
          while (i < j && !isalnum(s[j])) j--;

          if (tolower(s[i]) != tolower(s[j])) return false;
        }

        return true;
    }
};