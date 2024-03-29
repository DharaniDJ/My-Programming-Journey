
// Problem Link: https://leetcode.com/problems/reverse-bits/

// http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith64BitsDiv

// Approach 1 (bit by bit) : O(1) time and O(1) space complexity
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        for(int i=31;i>=0;i--){
            if(n&(1<<i)){
                ans |= (1<<(31-i));
            }
        }
        return ans;
    }
};

// Approach 2 (Byte by Byte with Memoization) : O(1) time and O(1) space complexity
class Solution {
public:
    uint32_t reverseByte(uint32_t n, unordered_map<uint32_t,uint32_t> &mp){
        if(mp.find(n)!=mp.end()) return mp[n];
        uint32_t val = (n * 0x0202020202 & 0x010884422010) % 1023;
        mp[n]=val;
        return val;
    }
    uint32_t reverseBits(uint32_t n) {
        uint32_t ans = 0;
        int power = 24;
        unordered_map<uint32_t,uint32_t> mp;
        while(n){
            ans+=reverseByte(n & 0xff,mp) << power;
            power-=8;
            n>>=8;
        }
        return ans;
    }
};

// Mask and Shift (use without loop) : O(1) time and O(1) space complexity
// class Solution {
// public:
//     uint32_t reverseBits(uint32_t n) {
//         n = (n >> 16) | (n << 16);
//         n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
//         n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
//         n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
//         n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
//         return n;
//     }
// };