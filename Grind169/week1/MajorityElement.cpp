
// Problem Link: https://leetcode.com/problems/majority-element/

// brute force: O(n^2) time and O(1) space complexity
// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         int n = nums.size();
//         for(int num:nums){
//             int cnt = 0;
//             for(int i:nums){
//                 if(i==num) cnt++;
//             }
//             if(cnt>n/2)return num;
//         }
//         return -1;
//     }
// };

// Frequeny counter: O(n) time and O(n) space complexity
// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         int n = nums.size();
//         unordered_map<int,int> mp;
//         for(int i:nums) mp[i]++;

//         for(auto it:mp){
//             if(it.second > n/2) return it.first;
//         }
//         return -1;
//     }
// };

// sorting: O(n*logn) time and O(1) space complexity
// class Solution {
// public:
//     int majorityElement(vector<int>& nums) {
//         int n = nums.size();
//         sort(nums.begin(),nums.end());
//         return nums[n/2];
//     }
// };

// Bit Manipulation: O(n*logC) time and O(1) space complexity, where C is the max absolute value in the array
// If an element majority_element occurs more than n/2 times,
// then there are at least n/2 elements of identical values with
// num at each bit. That is, we can reconstruct the exact value of
// num by combining the most frequent value (0 or 1) at each bit.

// Boyer-Moore Voting Algorithm
// If we had some way of counting instances of the majority element as +1
// and instances of any other element as −1, summing them would make it
// obvious that the majority element is indeed the majority element.
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        int candidate = -1;
        for(int i:nums){
            if(cnt==0){
                candidate = i;
            }
            if(i==candidate){
                cnt++;
            }else{
                cnt--;
            }
        }
        return candidate;
    }
};
