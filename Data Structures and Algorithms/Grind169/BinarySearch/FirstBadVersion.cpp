
// Problem Link: https://leetcode.com/problems/first-bad-version/

// Linear Search - O(n) time and O(1) space complexity
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        for(int i=1;i<=n;i++){
            if(isBadVersion(i)) return i;
        }
        return -1;
    }
};


// Binary Search - O(logn) time and O(1) space complexity
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int l=1;
        int r=n;
        int ans = -1;
        while(l<=r){
            int m = l+(r-l)/2;
            if(isBadVersion(m)){
                ans=m;
                r=m-1;
            }else{
                l=m+1;
            }
        }
        return ans;
    }
};