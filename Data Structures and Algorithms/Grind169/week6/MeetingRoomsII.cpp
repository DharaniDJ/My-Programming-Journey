
// Problem Link : https://leetcode.com/problems/meeting-rooms-ii

// Approach1(Min heap) : O(n*logn) time and O(n) space complexity
// So, every time we want to check if any room is free or not, simply check the topmost element of the min heap
// as that would be the room that would get free the earliest out of all the other rooms currently occupied.

class Solution {
public:
    static bool comp1(const vector<int> &a, const vector<int> &b){
        return a[0] < b[0];
    }

    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if(n==0) return 0;

        // min heap to store end time
        priority_queue<int, vector<int>, greater<int>> mnh;

        // sort the intervals by start time
        sort(intervals.begin(), intervals.end(),comp1);

        // add the first meeting
        mnh.push(intervals[0][1]);

        // iterate over the remaining intervals
        for(int i=1;i<n;i++){

            // If the room due to free up the earliest is free, assign that room to this meeting.
            if(intervals[i][0]>=mnh.top()){
                mnh.pop();
            }

            // If a new room is to be assigned, then also we add to the heap,
            // If an old room is allocated, then also we have to add to the heap with updated end time.
            mnh.push(intervals[i][1]);
        }

        // The size of the heap tells us the minimum rooms required for all the meetings.
        return mnh.size();

    }
};

// Approach2(Chronological ordering) : O(n*ogn) time and O(n) space complexity
// Arranging the meetings according to their start times helps us know the natural order of meetings throughout the day.
// However, simply knowing when a meeting starts doesn't tell us much about its duration.

// We also need the meetings sorted by their ending times because an ending event essentially tells us that there must have been
// a corresponding starting event and more importantly, an ending event tell us that a previously occupied room has now become free.

// for this specific algorithm, we need to treat the start and end times individually. This might not make sense right away because a meeting is defined by its start and end times.
// When we encounter an ending event, that means that some meeting that started earlier has ended now. We are not really concerned with which meeting has ended.
// All we need is that some meeting ended thus making a room available.
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<int> start(n), finish(n);

        for(int i=0;i<n;i++){
            start[i]=intervals[i][0];
            finish[i]=intervals[i][1];
        }

        sort(begin(start),end(start));
        sort(begin(finish),end(finish));

        int startPointer = 0, endPointer = 0;

        int usedRooms = 0;
        while(startPointer<n){
            if(start[startPointer]>=finish[endPointer]){
                usedRooms--;
                endPointer++;
            }

            usedRooms++;
            startPointer++;
        }

        return usedRooms;
    }
};

// Approach3(Using Maps) : O(n*logn) time and O(n) space complexity
// Similar to Approach2, but easy implementation
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        int n = intervals.size();

        map<int, int> mp; // key: time; val: +1 if start, -1 if end
        for(int i=0;i<n;i++){
            mp[intervals[i][0]]++;
            mp[intervals[i][1]]--;
        }

        int cnt = 0, ans = 0;
        for(auto it=mp.begin();it!=mp.end();it++){
            cnt+=it->second;
            ans=max(ans,cnt);
        }
        return ans;
    }
};