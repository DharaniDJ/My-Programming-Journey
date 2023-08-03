
// Problem Link : https://leetcode.com/problems/powx-n/

// Approach1(binary exponentiation)(Recursive) : O(logn) time and O(logn) space complexity
class Solution {
public:
    double myPow(double x, long long n) {
        if(x==1) return 1;

        if(n==0) return 1.0;
        if(n==1) return x;

        if(n<0) return 1/myPow(x,abs(n));

        double res = myPow(x,n/2);
        res*=res;
        if(n%2) res*=x;
        return res;
    }
};

// Approach1(binary exponentiation)(Iterative) : O(logn) time and O(1) space complexity
class Solution {
public:
    double myPow(double x, long long n) {

        int k = abs(n);
        double ans = 1.0;

        double pow = x;

        for(int i=0;i<32;i++){
            if(k & (1<<i)){
                ans*=pow;
            }
            pow*=pow;
        }
        return (n>=0)?ans:1/ans;
    }
};;