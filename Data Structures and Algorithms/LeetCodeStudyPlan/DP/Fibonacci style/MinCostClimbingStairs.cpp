
// Problem Link : https://leetcode.com/problems/min-cost-climbing-stairs/?envType=study-plan-v2&envId=dynamic-programming

// Approach1(Recursion) : O(2^n) time and O(n) space complexity
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        return solve(cost.size(),cost);
    }

    int solve(int i, vector<int> &cost){
        if(i<=1) return 0;

        int oneStep = cost[i-1]+solve(i-1,cost);
        int twoStep = cost[i-2]+solve(i-2,cost);

        return min(oneStep, twoStep);
    }
};

// Approach2(Recursion + Memoization) : O(n) time and O(n) space complexity
class Solution {
    unordered_map<int,int> mp;
public:
    int minCostClimbingStairs(vector<int>& cost) {
        return solve(cost.size(),cost);
    }

    int solve(int i, vector<int> &cost){
        if(i<=1) return 0;

        if(mp.count(i)) return mp[i];

        int oneStep = cost[i-1]+solve(i-1,cost);
        int twoStep = cost[i-2]+solve(i-2,cost);

        return mp[i] = min(oneStep, twoStep);
    }
};

// Approach3(DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1,0);

        for(int i=2;i<=n;i++){
            dp[i] = min({dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]});
        }

        return dp[n];
    }
};