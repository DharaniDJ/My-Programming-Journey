
// Problem Link : https://leetcode.com/problems/daily-temperatures

// Brute Force: O(n^2) time and O(1) space complexity
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res;
        for(int i=0;i<n;i++){
            int ans = 0;
            int temp = temperatures[i];
            for(int j=i+1;j<n;j++){
                if(temp<temperatures[j]){
                    ans = j-i;
                    break;
                }
            }
            res.push_back(ans);
        }
        return res;
    }
};

// Approach2 (Stack) : O(n) time and O(n) space complexity
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n,0);
        stack<int> st;
        for(int i=n-1;i>=0;i--){
            while(!st.empty() && temperatures[st.top()]<=temperatures[i]){
                 st.pop();
            }
            if(!st.empty()){
                res[i] = (st.top()-i);
            }
            st.push(i);
        }
        return res;
    }
};

// Approach 3 (Space optimization) : O(n) time and O(1) space complexity

// In the first approach, answer exists only to hold the answer. An important thing to notice
// is that answer carries information that we can use to solve the problem. We can save space
// and replace the functionality of the stack by using information from answer.

// Let's use the example test case temperatures = [73, 74, 75, 71, 69, 72, 76, 73]. Iterating backwards, after 5 days we have: answer = [0, 0, 0, 2, 1, 1, 0, 0].

// The next day to calculate is the day at index 2 with temperature 75. How can we use answer to help us do this?
// Well, let's first check the next day - we might be lucky and it could be warmer. The next day (at index 3) has a
// temperature of 71, which is not warmer. However, answer[3] tells us that the day at index 3 will not see a warmer
// temperature for 2 more days.

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n,0);
        
        int hottest = 0;
        for(int i=n-1;i>=0;i--){
            int curTemp = temperatures[i];
            if(curTemp>=hottest){
                hottest=curTemp;
                continue;
            }
            
            int days = 1;
            while(temperatures[i+days]<=curTemp){
                days+=res[i+days];
            }
            res[i]=days;
        }
        return res;
    }
};