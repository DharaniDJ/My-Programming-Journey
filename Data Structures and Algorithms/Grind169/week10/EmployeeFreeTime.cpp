
// Problem Link : https://leetcode.com/problems/employee-free-time

// Approach1(Sorting) : O(nlogn) time and O(n) space complexity
// where n is total number of intervals present in the schedule
class Solution {
public:
    static bool comp(const Interval &a, const Interval &b){
        return a.start < b.start;
    }

    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {

        vector<Interval> res;
        vector<Interval> ans;

        for(int i=0;i<(int)schedule.size();i++){
            for(int j=0;j<(int)schedule[i].size();j++){
                res.push_back(schedule[i][j]);
            }
        }

        sort(res.begin(),res.end(),comp);

        int start = res[0].start;
        int end = res[0].end;
        for(int i=1;i<(int)res.size();i++){
            if(res[i].start>end){
                ans.push_back(Interval(end,res[i].start));
                start = res[i].start;
                end = res[i].end;
            }else{
                end = max(end,res[i].end);
            }
        }
        return ans;
    }
};

// Approach2(Priority Queue) : O(nlogk) time and O(k) space complexity
// Intuition : find the last end in the sorted schedule and add into the result!
// Key Priority queue to find the min schedule to process with prevEnd
// k elements present at any time in the priority queue

#define tiiii tuple<int,int,int,int>

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        priority_queue<tiiii,vector<tiiii>, greater<tiiii>> pq; // {startTime, endTime, empIdx,idx}

        for(int i=0;i<(int)schedule.size();i++){
            auto [start, end] = schedule[i][0];
            pq.push({start,end,i,0});
        }

        vector<Interval> res;
        int prevEnd = pq.empty() ? -1 : get<0>(pq.top());

        while(!pq.empty()){
            auto [start,end,empIdx,idx] = pq.top();
            pq.pop();

            if(start>prevEnd){
                res.push_back({prevEnd,start});
            }

            prevEnd = max(prevEnd,end);

            if(schedule[empIdx].size()-1 != idx){
                auto [newStart, newEnd] = schedule[empIdx][idx+1];
                pq.push({newStart,newEnd,empIdx,idx+1});
            }
        }

        return res;
    }
};