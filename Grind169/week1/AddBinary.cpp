
// Problem Link: https://leetcode.com/problems/add-binary/

// bit-by-bit computation - O(max(n,m)) time and O(max(n,m)) space complexity
class Solution {
public:
    string addBinary(string a, string b) {
        int carry = 0;
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
        string ans="";
        int i=0,j=0;
        while(i<a.size() && j<b.size()){
            int val = carry+(a[i++]-'0')+(b[j++]-'0');
            ans+=to_string(val%2);
            carry=val/2;
        }
        while(i<a.size()){
            int val = carry+(a[i++]-'0');
            ans+=to_string(val%2);
            carry=val/2;
        }
        while(j<b.size()){
            int val = carry+(b[j++]-'0');
            ans+=to_string(val%2);
            carry=val/2;
        }
        if(carry) ans+=to_string(carry);
        reverse(ans.begin(),ans.end());
        return ans;
    }
};


