
// Problem Link : https://leetcode.com/problems/trapping-rain-water/

// Approach1(Brute Force) : O(n^2) time and O(1) space complexity
// For each element in the array, we find the maximum level of water it can trap after the rain,
// which is equal to the minimum of maximum height of bars on both the sides minus its own height.

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;

        for(int i=0;i<n;i++){
            int lf_mx=0,rt_mx=0;
            for(int l=i;l>=0;l--){
                lf_mx = max(lf_mx,height[l]);
            }
            for(int r=i;r<n;r++){
                rt_mx = max(rt_mx,height[r]);
            }
            ans += (min(lf_mx,rt_mx))-height[i];
        }
        return ans;
    }
};

// Approach2(DP) : O(n) time and O(n) space complexity
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int ans = 0;

        vector<int> lf_mx(n),rt_mx(n);

        lf_mx[0]=height[0];
        for(int i=1;i<n;i++){
            lf_mx[i]=max({lf_mx[i-1],height[i]});
        }

        rt_mx[n-1]=height[n-1];
        for(int i=n-2;i>=0;i--){
            rt_mx[i]=max({rt_mx[i+1],height[i]});
        }

        for(int i=0;i<n;i++){
            ans+=(min(lf_mx[i],rt_mx[i])-height[i]);
        }

        return ans;
    }
};

// Approach3(Stack): O(n) time and O(n) space complexity
// Instead of storing the largest bar upto an index as in Approach 2, we can use stack to keep track of the bars
// that are bounded by longer bars and hence, may store water. Using the stack, we can do the calculations in only one iteration.
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n==0) return 0;

        int ans = 0;
        stack<int> st;

        for(int i=0;i<n;i++){
            while(!st.empty() && height[i]>height[st.top()]){
                int top1 = st.top();
                st.pop();
                if(st.empty()) break;

                int dist = i-st.top()-1;
                int height_dif = min(height[st.top()],height[i])-height[top1];
                ans+=(height_dif*dist);
            }
            st.push(i);
        }
        return ans;
    }
};

// Approach4(2 pointer): O(n) time and O(1) space complexity
// As in Approach 2, instead of computing the left and right parts seperately, we may think of some way to do it in one iteration.
// in dynamic programming approach, notice that as long as right_max[i]>left_max[i], the water trapped depends upon the left_max, and similar is the case when left_max[i]>right_max[i]
// So, we can say that if there is a larger bar at one end (say right), we are assured that the water trapped would be dependant on height of bar in current direction (from left to right).
// As soon as we find the bar at other end (right) is smaller, we start iterating in opposite direction (from right to left).
// right_max during the iteration, but now we can do it in one iteration using 2 pointers, switching between the two.

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n==0) return 0;

        int ans = 0;
        int lf_mx = -1, rt_mx = -1;

        int l = 0, r = n-1;
        while(l<=r){
            if(height[l]<height[r]){
                if(height[l]>lf_mx) lf_mx = height[l];
                ans+=(lf_mx-height[l]);
                l++;
            }else{
                if(height[r]>rt_mx) rt_mx=height[r];
                ans+=(rt_mx-height[r]);
                r--;
            }
        }
        return ans;
    }
};