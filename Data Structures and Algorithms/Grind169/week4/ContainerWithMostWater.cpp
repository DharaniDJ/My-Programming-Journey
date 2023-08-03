
// Problem Link : https://leetcode.com/problems/container-with-most-water/

// Approach 1(Brute Force)(TLE) : O(n^2) time and O(1) space complexity
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int mn = min(height[i],height[j]);
                ans = max(ans, (j-i)*mn);
            }
        }
        return ans;
    }
};

// Two Pointer : O(n) time and O(1) space complexity
// At every step, we calculate the area formed between the two pointers, update the
// maxArea and move the pointer pointing to the shorter line towards the other end by one.

// But a critical question is: why are we doing this? Here is an explanation by considering
// two possible scenarios when (height[i] < height[j]) and (height[i] > height[j]).

// Case 1: if (height[i] < height[j])
// When height[i] < height[j], we don’t need to calculate the area for all pairs between
// (i, j - 1), (i, j - 2),…because these areas are smaller than the area at (i, j).
// Let's understand it better by comparing the area for (i, j) and (i, j - 1).

// A = Area for pair (i, j) = (j - i) * min (height[i], height[j]) = (j - i) * height[i]
// A’ = Area for pair (i, j - 1) = (j - 1 - i) * min (height[i], height[j - 1])

//     if(height[i] < height[j - 1])
//     => A’ = (j - 1 - i) * min (height[i], height[j - 1]) = (j - 1 - i) * height[i]
//     => A' = (j - 1 - i) * height[i] < (j - i) * height[i] (As we know, A = (j - i) * height[i])
//     => A' < A

//     if(height[i] > height[j - 1])
//     => A’ = (j - 1 - i) * min (height[i], height[j - 1]) = (j - 1 - i) * height[j-1]
//     => A' = (j - 1 - i) * height[j-1] < (j - i) * height[i] (As we know, A = (j - i) * height[i])
//     => A' < A

// In simple words: we don’t need to consider the area between the pairs
// (i, j - 1), (i, j - 2), (i, j - 3), etc., and move the pointer i to one right in search of a larger area.

// Case 2: if (height[i] > height[j])
// When height[i] > height[j], we don’t need to calculate all (i + 1, j), (i + 2, j),…
// because these areas are smaller than our area at (i, j). ***So we move the pointer j to one left in search of a larger area***.
// We can use an idea similar to the above approach for the proof. (Think!)


class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int ans = 0;
        int i = 0, j = n-1;
        while(j>=i){
            ans = max(ans, (j-i)*min(height[i],height[j]));
            if(height[i]>height[j]){
                j--;
            }else{
                i++;
            }
        }
        return ans;
    }
};