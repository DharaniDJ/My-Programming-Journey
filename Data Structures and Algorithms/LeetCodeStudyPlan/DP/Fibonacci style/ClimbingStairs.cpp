
// Problem Link : https://leetcode.com/problems/climbing-stairs/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int climbStairs(int n) {
        if(n==0 || n==1) return 1;
        return climbStairs(n-1)+climbStairs(n-2);
    }
};

// Approach2(Recursion + Memoization) : O(n) time and O(n) space complexity
class Solution {
    int countWays(int n, vector<int> &dp){
        if(n==0 || n==1){
            return dp[n]=1;
        }
        
        if(dp[n]!=-1) return dp[n];
        return dp[n] = countWays(n-1,dp) + countWays(n-2,dp);
    }

public:
    int climbStairs(int n) {
        vector<int> dp(n+1,-1);
        return countWays(n,dp);
    }
};

// Approach3(DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int climbStairs(int n) {
        if(n==0 || n==1) return 1;

        vector<int> dp(n+1);

        dp[0] = 1;
        dp[1] = 1;

        for(int i=2;i<=n;i++){
            dp[i] = dp[i-1]+dp[i-2];
        }

        return dp[n];
    }
};

// Approach4(DP + space optimization) : O(n) time and O(1) space complexity
class Solution {
public:
    int climbStairs(int n) {
        if(n==0 || n==1) return 1;

        int first = 1;
        int second = 1;

        for(int i=2;i<=n;i++){
            int third = first + second;
            first = second;
            second = third;
        }

        return second;
    }
};


// Approach5(Matrix Multiplication) : O(logn) time and O(1) space complexity
class Solution {
public:
    int climbStairs(int n) {
        vector<vector<long>> q = {{1, 1}, {1, 0}};
        vector<vector<long>> res = pow(q, n);
        return res[0][0];
    }

    vector<vector<long>> pow(vector<vector<long>>& a, int n) {
        vector<vector<long>> ret = {{1, 0}, {0, 1}};
        while (n > 0) {
            if ((n & 1) == 1) {
                ret = multiply(ret, a);
            }
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }

    vector<vector<long>> multiply(vector<vector<long>>& a, vector<vector<long>>& b) {
        vector<vector<long>> c(2, vector<long>(2, 0));
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }
};



// Approach6(Fibonacci formula) : O(1) space and O(1) space complexity
class Solution {
public:
    int climbStairs(int n) {
        double sqrt5 = std::sqrt(5);
        double phi = (1 + sqrt5) / 2;
        double psi = (1 - sqrt5) / 2;
        return static_cast<int>((std::pow(phi, n + 1) - std::pow(psi, n + 1)) / sqrt5);
    }
};