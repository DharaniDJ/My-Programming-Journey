
// Problem Link :https://leetcode.com/problems/maximum-frequency-stack

// Approach1(Using map of stacks) : O(1) time and O(n) space complexity
class FreqStack {
    // freqMap is to map element to its frequency
    unordered_map<int,int> freqMap;

    // set map is to map frequency to the
    // element list with this frequency
    unordered_map<int,stack<int>> stackMap;

    // for keeping record of maximum frequency
    int maxFreq = 0;
public:
    FreqStack() {
        maxFreq = 0;
    }

    void push(int val) {

        freqMap[val]++;

        // if freq is greater than maxfreq
        // update max freq
        maxFreq = max(maxFreq, freqMap[val]);

        // Mapping element to  its frequency list
        stackMap[freqMap[val]].push(val);
    }

    int pop() {
        // remove element from setMap
        // from maximum frequency list
        int top = stackMap[maxFreq].top();
        stackMap[maxFreq].pop();
        freqMap[top]--;

        if(stackMap[maxFreq].empty()) maxFreq--;

        return top;
    }
};


// Approach2(using max heap) : O(1) time and O(n) space complexity
class FreqStack {
    // <freq,<idx,val>>
    priority_queue<pair<int,pair<int,int>>> mxh;

    // store the frequency of val
    unordered_map<int,int> freqMap;

    // represents the recent element that is being called
    int idx = 0;
public:
    FreqStack() {
        idx = 0;
    }

    void push(int val) {
        mxh.push({++freqMap[val],{idx++,val}});
    }

    int pop() {
        int tp = mxh.top().second.second;
        freqMap[tp]--;
        mxh.pop();
        return tp;
    }
};
