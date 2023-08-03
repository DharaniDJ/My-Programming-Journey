
// Problem Link : https://leetcode.com/problems/maximum-profit-in-job-scheduling/

// Approach1(Top-Down DP + BS) : O(n*logn) time and O(n) space complexity
// Let's start at time zero, before the startTime of any job, at this point we can choose any job to schedule first.
// Once the first job has ended, we can iterate over all of the jobs and only consider scheduling those that start after the current time.
// we sort our jobs according to start time, then we can apply binary search to find the next job. After sorting jobs according to startTime,
// to find the index of the first non-conflicting job, binary search for the endTime of the current job in the list of start times for all jobs.

class Solution {
    int dp[50001];
public:

    int findMaxProfit(int idx, vector<int> &startTime, int n, vector<vector<int>> &jobs){
        if(idx==n) return 0;

        if(dp[idx]!=-1) return dp[idx];

        int nextIdx = lower_bound(startTime.begin(),startTime.end(),jobs[idx][1])-startTime.begin();
        // find the maximum profit of our two options: skipping or scheduling the current job
        int maxProfit = max(findMaxProfit(idx+1,startTime,n,jobs),
                        jobs[idx][2] + findMaxProfit(nextIdx,startTime,n,jobs));

        return dp[idx] = maxProfit;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;

        memset(dp,-1,sizeof(dp));

        int n = startTime.size();
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }

        sort(jobs.begin(),jobs.end());

        for(int i=0;i<n;i++) startTime[i]=jobs[i][0];

        return findMaxProfit(0,startTime,n,jobs);
    }
};

// Approach2(Bottom up DP + BS) : O(n*logn) time and O(n) space complexity
class Solution {
    int dp[50001];
public:
    int findMaxProfit(vector<int>& startTime, vector<vector<int>>& jobs){
        int n = startTime.size();
        for(int i=n-1;i>=0;i--){
            int curProfit = 0;
            int nextIdx = lower_bound(startTime.begin(),startTime.end(),jobs[i][1])-startTime.begin();

            // if there is a non-conflicting job possible add it's profit
            // else just consider the curent job profit
            if(nextIdx!=n){
                curProfit = dp[nextIdx]+jobs[i][2];
            }else{
                curProfit = jobs[i][2];
            }

            if(i==n-1){
                dp[i]=curProfit;
            }else{
                dp[i] = max(dp[i+1],curProfit);
            }
        }
        return dp[0];
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        // memset(dp,-1,sizeof(dp));

        vector<vector<int>> jobs;
        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }

        sort(jobs.begin(),jobs.end());

        for(int i=0;i<n;i++){
            startTime[i]=jobs[i][0];
        }

        return findMaxProfit(startTime, jobs);
    }
};

// Approach3(Sorting + Priority Queue) : O(n*logn) time and O(n) space complexity
// Considering the problem this way, it becomes similar to Longest Increasing Subsequence with the goal of maximizing the profit instead of length.
// As such, we can approach this problem in a similar way, by first sorting the jobs according to their start time and then for each job,
// choose the most profitable chain of jobs to add the current job to.

// we iterate over all of the previous job chains to find the most profitable chain that ends at or before the current job starts.
// This results in O(N2) time complexity. Can we do better?


// When we pop a job chain from the heap we don't push it back into the heap, although this job chain can still be combined with other jobs in the future.
// To handle this case we introduce a variable maxProfit whenever we pop a job chain from heap we compare its profit with the maxProfit and update it accordingly.
// The reason is that the jobs are sorted and hence if we pop out a chain from the heap for the ith job then it implies that this chain can be combined with any
// other job that comes after index i. Therefore we only need to store the chain's profit.

// Formally at the time of ith iteration, the value of maxProfit will be the maximum profit of a set of job chains to which the ith job can be appended.

class Solution {
public:
    int findMaxProfit(vector<vector<int>> &jobs){
        int n = jobs.size(), maxProfit = 0;
        // min heap having {endTime, profit}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        // iterate over all the jobs from left to right
        for(int i=0;i<n;i++){
            int start = jobs[i][0], end = jobs[i][1], profit = jobs[i][2];

            // check among all chains that are not conflicting
            while(!pq.empty() && start>=pq.top()[0]){
                maxProfit = max(maxProfit, pq.top()[1]);
                pq.pop();
            }

            // represents the chain created by adding the current job to the most profitable job chain.
            pq.push({end,profit + maxProfit});
        }

        // update the value of maxProfit by comparing with
        // profit of jobs that exits in the heap
        while (pq.empty() == 0) {
            maxProfit = max(maxProfit, pq.top()[1]);
            pq.pop();
        }

        return maxProfit;
    }
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>> jobs;
        int n = startTime.size();

        for(int i=0;i<n;i++){
            jobs.push_back({startTime[i],endTime[i],profit[i]});
        }

        sort(jobs.begin(),jobs.end());

        return findMaxProfit(jobs);

    }
};