
// Problem Link: https://leetcode.com/problems/meeting-rooms/

// Brute Force: O(n^2) time and O(1) space complexity
class Solution {
public:
    bool overlap(vector<int> &interval1, vector<int> &interval2){
        return interval2[0] >=interval1[0] && interval2[0]<interval1[1]
            || interval1[0] >=interval2[0] && interval1[0]<interval2[1];
    }
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n==0) return true;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(overlap(intervals[i],intervals[j])) return false;
            }
        }
        return true;
    }
};

// sorting: O(n*logn) time and O(1) space complexity
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if(intervals.empty()){
            return true;
        }
        sort(intervals.begin(), intervals.end());
        for(int i=0;i<intervals.size()-1;i++){
            if(intervals[i+1][0] < intervals[i][1])
                return false;
        }
        return true;
    }
};