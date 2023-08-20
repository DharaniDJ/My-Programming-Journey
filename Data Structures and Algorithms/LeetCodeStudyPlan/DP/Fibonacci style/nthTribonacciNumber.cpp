
// Problem Link : https://leetcode.com/problems/n-th-tribonacci-number/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(3^n) time and O(n) space complexity
class Solution {
public:
    int tribonacci(int n) {
        if(n==0 || n==1) return n;
        if(n==2) return 1;

        return tribonacci(n-1)+tribonacci(n-2)+tribonacci(n-3);
    }
};

// Approach2(Recursion + Memoization) : O(n) time and O(n) space complexity
class Solution {
    unordered_map<int,int> dp = {
        {0,0},
        {1,1},
        {2,1}
    };

    int solve(int n){
        if(dp.count(n)){
            return dp[n];
        }

        int ans = solve(n-1)+solve(n-2)+solve(n-3);
        dp[n]=ans;
        return ans;
    }

public:

    int tribonacci(int n) {
        return solve(n);
    }
};

// Approach3(DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int tribonacci(int n) {
        if(n==0 || n==1) return n;
        if(n==2) return 1;
        vector<int> dp(n+1,0);
        dp[1] = dp[2] = 1;

        for(int i=3;i<=n;i++){
            dp[i] = dp[i-1]+dp[i-2]+dp[i-3];
        }
        return dp[n];
    }
};

// Approach4(DP + space optimization) : O(n) time and O(1) space complexity
class Solution {
public:
    int tribonacci(int n) {
        if(n==0 || n==1) return n;
        if(n==2) return 1;

        int first = 0;
        int second = 1;
        int third = 1;

        for(int i=3;i<=n;i++){
            int temp = first+second+third;
            first = second;
            second = third;
            third = temp;
        }
        return third;
    }
};

// Approach5(Matrix Multiplication) : O(logn) time and O(1) space complexity
/*

| F(n)   |  =  [ | 1 1 1 | ] ^ (n-2)   *  | F(2) |
| F(n-1) |     [ | 1 0 0 | ]              | F(1) |
| F(n-2) |     [ | 0 1 0 | ]              | F(0) |

*/
class Solution {
public:
    int tribonacci(int n) {
        if(n==0 || n==1) return n;
        if(n==2) return 1;

        vector<vector<long>> fib = {{1,1,1},{1,0,0},{0,1,0}};
        fib = pow(fib,n-2);
        vector<vector<long>> ans = {{1},{1},{0}};
        vector<vector<long>> res = multiply(fib,ans);
        return res[0][0];
    }

    vector<vector<long>> pow(vector<vector<long>>& a, int n) {
        vector<vector<long>> temp = a;
        n--;
        while (n > 0) {
            if ((n & 1) == 1) {
                a = multiply(a, temp);
            }
            n >>= 1;
            temp = multiply(temp, temp);
        }
        return a;
    }

    vector<vector<long>> multiply(vector<vector<long>>& a, vector<vector<long>>& b) {
        int r1=a.size(),c1=a[0].size(),r2=b.size(),c2=b[0].size();
        vector<vector<long>> c(r1,vector<long>(c2,0));

        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c2; j++) {
                for(int k=0;k<r2;k++){
                    c[i][j]+=(a[i][k]*b[k][j]);
                }
            }
        }
        return c;
    }
};