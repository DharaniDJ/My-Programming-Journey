
// Problem link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

// Brute Force - O(n^2) time and O(1) space complexity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int ans = 0;
        for(int i=0;i<(n-1);i++){
            for(int j=i+1;j<n;j++){
                ans = max(ans, prices[j]-prices[i]);
            }
        }
        return ans;
    }
};

// Modification of Kadane algorithm - O(n) time and O(n) space complexity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> temp;
        int n = prices.size();
        for(int i=0;i<(n-1);i++){
            temp.push_back(prices[i+1]-prices[i]);
        }
        int mx = 0;
        int sum = 0;
        for(int i:temp){
            sum+=i;
            sum=max(sum,0);
            mx=max(mx,sum);
        }
        return mx;
    }
};

// Iteration - O(n) time and O(1) space complexity
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int ans = -1;
        int mn = prices[0];
        for(int i=0;i<n;i++){
            ans=max(ans,(prices[i]-mn));
            mn=min(mn,prices[i]);
        }
        return ans;
    }
};

