
// Problem Link :https://leetcode.com/problems/task-scheduler

// Greedy Approach : O(n) time and O(1) space complexity

// Maximum possible number of idle slots is defined by the
// frequency of the most frequent task: idle_time <= (f_max - 1) * n
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for(char c:tasks) freq[c-'A']++;

        sort(freq.begin(),freq.end());

        int f_mx = freq[25];
        int idle_time = n*(f_mx-1);

        for(int i=24;i>=0 && idle_time>0;i--){
            idle_time-=min(f_mx-1,freq[i]);
        }

        idle_time = max(0,idle_time);

        return idle_time+tasks.size();
    }
};

// Math : O(n) space and O(1) time complexity

// There are two possible situations:

// 1. The most frequent task is not frequent enough to force
// the presence of idle slots (len(tasks)).

// 2. The most frequent task is frequent enough to force some((1+n)*(f_mx-1)+n_mx)

// The answer is the maximum between these two.

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26] = {0};
        for(char c:tasks) freq[c-'A']++;

        int f_mx = 0;
        for(int i=0;i<26;i++) f_mx = max(f_mx,freq[i]);

        int n_mx = 0;
        for(int i=0;i<26;i++){
            if(freq[i]==f_mx) n_mx++;
        }

        return max((int)tasks.size(),((1+n)*(f_mx-1)+n_mx));
    }
};