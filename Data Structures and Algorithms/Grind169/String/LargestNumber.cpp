
// Problem Link : https://leetcode.com/problems/largest-number

// Approach1(Sorting via Custom Comparator) : O(nlogn) time (sorting) and O(n) space (extra space to store strings) complexity
// Assume that (without loss of generality), for some pair of integers a and
// b, our comparator dictates that a should precede b in sorted
// order. This means that a⌢b> > b⌢a (where ⌢\frown⌢ represents
// concatenation)

class Solution {
public:
    static bool comp(const string a, const string b){
        return a+b>b+a;
    }
    string largestNumber(vector<int>& nums) {
        vector<string> nums_str;
        for(int num : nums){
            nums_str.push_back(to_string(num));
        }
        sort(nums_str.begin(),nums_str.end(),comp);
        
         // If, after being sorted, the largest number is `0`, the entire number
        // is zero.
        if(nums_str[0]=="0") return "0";
        
        string s = "";
        for(string str : nums_str ){
            s+=str;
        }
        return s;
    }
};