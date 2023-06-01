
// Problem Link : https://leetcode.com/problems/insert-interval/

// Linear search : O(n) time and O(n) space complexity
class Solution {
public:
    // Returns true if the intervals a and b have a common element.
    bool isOverlapping(vector<int>& a, vector<int>& b) {
        return min(a[1], b[1]) - max(a[0], b[0]) >= 0;
    }
    
    // Return the interval having all the elements of intervals a and b.
    vector<int> mergeInterval(vector<int>& a, vector<int>& b) {
        return {min(a[0], b[0]), max(a[1], b[1])};
    }
    
    // Insert the interval newInterval, into the list interval keeping the sorting order intact.
    void insertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
        bool isInserted = false;
        for (int i = 0; i < intervals.size(); i++) {
            // find the first interval with a start value greater than the newInterval 
            if (newInterval[0] < intervals[i][0]) {
                intervals.insert(intervals.begin() + i, newInterval);
                isInserted = true;
                break;
            }
        }if(!isInserted){
            intervals.push_back(newInterval);
        }
    }
    
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        insertInterval(intervals,newInterval);
        vector<vector<int>> res;
        for(int i=0;i<intervals.size();i++){
            vector<int> curInterval = {intervals[i][0], intervals[i][1]};
            while(i<intervals.size() && isOverlapping(curInterval,intervals[i])){
                curInterval = mergeInterval(curInterval,intervals[i]);
                i++;
            }
            i--;
            res.push_back(curInterval);
        }
        return res;
    }
};

// Binary Search : O(n) time and O(n) space complexity

// The only difference with this approach would be that 
// instead of using linear search to find the suitable position 
// of newInterval, we can use binary search as the list of 
// intervals is sorted in order of their start time.
void insertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int index = upper_bound(intervals.begin(), intervals.end(), newInterval) - intervals.begin();

    if (index != intervals.size()) {
        intervals.insert(intervals.begin() + index, newInterval);
    } else {
        intervals.push_back(newInterval);
    }
}

// Solution with same time & space complexity but more readabilitySame
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int start = newInterval[0], end = newInterval[1];
        int n = intervals.size();

        if (n == 0) {
            return {newInterval};
        }

        int i = 0;
        while (i < n) {
            while (i < n && intervals[i][1] < start) {
                ans.push_back(intervals[i]);
                ++i;
            }
            while (i < n && start <= intervals[i][1] && end >= intervals[i][0]) {
                start = min(start, intervals[i][0]);
                end = max(end, intervals[i][1]);
                ++i;
            }
            ans.push_back({start, end});
            while (i < n) {
                ans.push_back(intervals[i]);
                ++i;
            }
        }

        return ans;
    }
};