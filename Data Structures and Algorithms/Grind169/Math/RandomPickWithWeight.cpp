
// Problem Link : https://leetcode.com/problems/random-pick-with-weight/

// Intuition :
// To understand the problem better, let us imagine that there is a line in the space, we then project each number into the line according to its value,
// i.e. a large number would occupy a broader range on the line compared to a small number. For example, the range for the number 9 should be exactly nine times as the range for the number 1.

// Now, let us throw a ball randomly onto the line, then it is safe to say there is a good chance that the ball will fall into the range occupied by the number 9.
// In fact, if we repeat this experiment for a large number of times, then statistically speaking, 9 out of 10 times the ball will fall into the range for the number 9.

// Let us rephrase the problem now, given a list of offsets (i.e. prefix sums) and a target offset, our task is to fit
// the target offset into the list so that the ascending order is maintained.

// If one comes across this problem during an interview, one can consider the problem almost resolved,
// once one reduces the original problem down to the problem of inserting an element into a sorted list.


// Approach1(Prefix sum + Linear search)
// Time complexity: O(n) for constructor and O(n) for pickIndex
// Space complexity: O(n) for constructor and O(1) for pickIndex
#include <cstdlib>
class Solution {
public:
    vector<int> prefixSums;
    Solution(vector<int>& w) {
        for(auto weight : w) prefixSums.push_back( weight + (prefixSums.empty()?0:prefixSums.back()) );
    }

    int pickIndex() {
        // generate a random number in the range of [0, 1]
        float randNum = (float) rand() / RAND_MAX;
        float target = randNum * prefixSums.back();

        // run linear search to find the target zone
        for(int i=0;i<prefixSums.size();i++){
            if(prefixSums[i]>target) return i;
        }
        return prefixSums.size()-1;
    }
};

// Approach1(Prefix sum + Binary search)
// Time complexity: O(n) for constructor and O(logn) for pickIndex
// Space complexity: O(n) for constructor and O(1) for pickIndex
// we can apply binary search on the prefixSums array, as we know it is sorted in ascending order
#include <cstdlib>
class Solution {
public:
    vector<int> prefixSums;
    Solution(vector<int>& w) {
        for(auto weight : w) prefixSums.push_back( weight + (prefixSums.empty()?0:prefixSums.back()) );
    }

    int pickIndex() {
        // generate a random number in the range of [0, 1]
        float randNum = (float) rand() / RAND_MAX;
        float target = randNum * prefixSums.back();

        // run Binary search to find the target zone

        return upper_bound(prefixSums.begin(),prefixSums.end(),target) - prefixSums.begin();
    }
};