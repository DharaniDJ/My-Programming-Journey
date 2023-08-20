
// Problem Link: https://leetcode.com/problems/number-of-1-bits/

// Loop and count : O(1) time andd O(1) space complexity
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        for(int i=0;i<=31;i++){
            if(n&(1<<i)) cnt++;
        }
        return cnt;
    }
};

// Bit manipulation: O(1) time andd O(1) space complexity
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n){
            cnt++;
            n=n&(n-1);
        }
        return cnt;
    }
};