
// Problem Link : https://leetcode.com/problems/gas-station

// Approach 1(Brute force) : O(n^2) time and O(1) space complexity
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        for(int i=0;i<n;i++){
            int j = i;
            int cap = gas[j];
            bool fl = true;
            do{
                cap-=cost[j];
                if(cap<0){
                    fl=false;
                    break;
                }
                j=(j+1)%n;
                cap+=gas[j];
            }while(i!=j);
            if(fl) return i;
        }
        return -1;
    }
};

// Approach 2 : O(n) time and O(1) space complexity
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int cur_gain=0, total_gain=0, ans=0;
        int n = gas.size();

        for(int i=0;i<n;i++){
            cur_gain += gas[i]-cost[i];
            total_gain += gas[i]-cost[i];

            // skip this "valley"
            // try completing the circular route starting from the next gas station with a non-negative net gain of gas.
            // we treat the previous part as a single segment, which we failed to pass through with 0 initial gas. Let's temporarily leave it behind and start over from the next station with 0 initial gas.

            // To pass these segments, we must hold enough extra gas before entering them.

            if(cur_gain<0){
                ans = i+1;
                cur_gain=0;
            }
        }
        return total_gain<0 ? -1 : ans;
    }
};