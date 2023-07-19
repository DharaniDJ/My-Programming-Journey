
// Problem Link : https://leetcode.com/problems/largest-rectangle-in-histogram/

// Approach1(BruteForce) : O(n^2) time and O(1) space complexity
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;

        for(int i=0;i<n;i++){
            int l=i,r=i;
            for(l=i;l>=0;l--){
                if(heights[i]>heights[l]) break;
            }

            for(r=i;r<n;r++){
                if(heights[i]>heights[r]) break;
            }

            ans = max(ans, heights[i]*(r-l-1));
        }
        return ans;
    }
};

// Simpler BruteForce
// Finding the bar of minimum height lying between them everytime, we can find the bar of minimum height for
// current pair by using the minimum height bar of the previous pair.

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        size_t max_area = 0;
        for (size_t i = 0; i < heights.size(); i++) {
            int min_height = INT_MAX;
            for (size_t j = i; j < heights.size(); j++) {
                min_height = min(min_height, heights[j]);
                max_area = max(max_area, min_height * (j - i + 1));
            }
        }
        return max_area;
    }
};

// Approach2(divide and conquer) : O(nlogn) or O(n^2) time and O(n) space complexity
// This approach relies on the observation that the rectangle with maximum area will be
// the maximum of:
// 1. The widest possible rectangle with height equal to the height of the shortest bar.
// 2. The largest rectangle confined to the left of the shortest bar(subproblem).
// 3. The largest rectangle confined to the right of the shortest bar(subproblem).
class Solution {
public:
    int calculateArea(vector<int> &heights, int start, int end){
        if(start>end) return 0;
        int minIdx = start;
        for(int i=start;i<=end;i++){
            if(heights[minIdx]>heights[i]) minIdx = i;
        }

        return max({heights[minIdx]*(end-start+1), calculateArea(heights,start,minIdx-1), calculateArea(heights,minIdx+1,end)});
    }

    int largestRectangleArea(vector<int>& heights) {
        return calculateArea(heights,0,heights.size()-1);
    }
};


// Approach3(Using stack - 2 pass) : O(n) time and O(n) space complexity
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> l(n,-1),r(n,n);
        stack<int> s;
        int mx = -1;
        for(int i=0;i<n;i++){
            while(!s.empty() && heights[s.top()]>=heights[i]){
                s.pop();
            }
            if(!s.empty()) l[i]=s.top();
            s.push(i);
        }

        while(!s.empty()) s.pop();

        for(int i=n-1;i>=0;i--){
            while(!s.empty() && heights[s.top()]>=heights[i]){
                s.pop();
            }
            if(!s.empty()) r[i]=s.top();
            s.push(i);
            mx = max(mx, (r[i]-l[i]-1)*heights[i]);
        }

        return mx;
    }
};

// Appraoch4(using stack - one pass) : O(n) time and O(n) space complexity
// Every time we pop, we find out the area of rectangle formed using the current element as the height
// of the rectangle and the difference between the the current element's index pointed to in the original array
// and the element stack[top−1]−1 as the width

// i.e. if we pop an element stack[top]stack[top]stack[top] and i is the current index to which we are pointing in the original array,
// the current area of the rectangle will be considered as: (i−stack[top−1]−1)×heights[stack[top]]
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = -1;
        stack<int> st;

        // push -1 onto the stack to mark the end.
        st.push(-1);

        for(int i=0;i<n;i++){

            // keep pushing the current bar's index onto the stack until we get heights[i]<heights[i-1]
            while(st.top()!=-1 && heights[st.top()]>=heights[i]){
                int curH = heights[st.top()];
                st.pop();
                int curW = i-st.top()-1;
                ans = max(ans, curH*curW);
            }

            st.push(i);
        }

        while(st.top()!=-1){
            int curH = heights[st.top()];
            st.pop();
            int curW = n-st.top()-1;
            ans = max(ans, curH*curW);
        }

        return ans;
    }
};