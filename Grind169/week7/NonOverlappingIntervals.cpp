
// Problem Link : https://leetcode.com/problems/non-overlapping-intervals

// Approach1(Greedy) : O(n*logn) time and O(1) space complexity

// Let's start by considering the intervals according to their end times. Consider the two intervals with the earliest end times.
// Let's say the earlier end time is x and the later one is y. We have x < y.
// If we can only choose to keep one interval, should we choose the one ending at x or ending at y?
// To avoid overlap, We should always greedily choose the interval with an earlier end time x
// We want to maximize the intervals we take (without overlap), so we want to maximize our choices for the next interval.

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        auto comp = [](const vector<int>& a, const vector<int>& b) -> bool{
            if(a[1]<b[1]) return true;
            if(a[1]==b[1] && a[0]<b[0]) return true;
            return false;
        };

        sort(intervals.begin(),intervals.end(),comp);

        int cnt = 1;
        int prev = INT_MIN;

        for(int i=0;i<intervals.size();i++){
            if(prev==INT_MIN){
                prev = intervals[i][1];
                continue;
            }

            if(prev<=intervals[i][0]){
                prev=intervals[i][1];
                cnt++;
            }
        }
        return intervals.size()-cnt;

    }
};