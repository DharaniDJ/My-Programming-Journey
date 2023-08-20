
// Problem Link: https://leetcode.com/problems/counting-bits/

// Pop Count or Hamming weight: O(n*logn) time and O(1) space complexity
class Solution {
public:
    int countB(int i){
        int cnt = 0;
        while(i){
            cnt++;
            i=i&(i-1);
        }
        return cnt;
    }
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1;i<=n;i++){
            res[i]=countB(i);
        }
        return res;
    }
};

// Approach 2: DP + Least Significant Bit
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1;i<=n;i++){
            res[i]=res[i>>1]+(i%2);
        }
        return res;
    }
};

// Approach 3: DP + Last Set Bit
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> res(n+1,0);
        for(int i=1;i<=n;i++){
            res[i]=res[i&(i-1)]+1;
        }
        return res;
    }
};