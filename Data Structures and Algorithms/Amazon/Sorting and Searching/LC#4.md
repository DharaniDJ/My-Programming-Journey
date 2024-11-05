### Problem Statement

We are given two sorted arrays `nums1` and `nums2` with sizes `m` and `n`, respectively. Our goal is to find the median of these two arrays in \(O(\log(m + n))\) time complexity. 

### UMPIRE Breakdown

#### **1. Understand**
- **Clarifications**:
  - We need to find the median of the combined array if `nums1` and `nums2` were merged and sorted.
  - The median of a dataset is the middle value if the total number of elements is odd, or the average of the two middle values if even.
  - Since `nums1` and `nums2` are already sorted, we can avoid merging the arrays directly and use binary search for an efficient solution.

- **Edge Cases**:
  - One of the arrays might be empty.
  - Both arrays might have elements in the same range or have large gaps between their values.
  - Arrays with very different sizes, like `m << n` or `n << m`.

- **Test Cases**:
  - **Example 1**: `nums1 = [1, 3]`, `nums2 = [2]` → Median: `2.0`
  - **Example 2**: `nums1 = [1, 2]`, `nums2 = [3, 4]` → Median: `(2 + 3) / 2 = 2.5`
  - **Example 3**: `nums1 = []`, `nums2 = [1]` → Median: `1.0`
  - **Example 4**: `nums1 = [0, 0]`, `nums2 = [0, 0]` → Median: `0.0`

#### **2. Match**
- **Problem Type**: This is a binary search problem on sorted arrays.
- **Pattern**: We can use binary search on one of the arrays (preferably the smaller one) and partition the arrays to find the correct median.

#### **3. Plan**

**Intuition**:
To find the median efficiently, we’ll take advantage of the sorted properties and use binary search to partition the arrays without merging them:
we need to find a point of partition in both arrays such that the maximum of the smaller half is less than or equal to the minimum of the larger half.

Instead of partitioning over the merged arrays, we can only focus on partitioning the smaller array

1. **Choose the Smaller Array for Binary Search**: To minimize the search range, always perform binary search on the smaller array (`nums1` if `m < n`), as this reduces the number of partition points we need to check.

2. **Partitioning the Arrays**:
   - We aim to split both arrays into left and right halves such that the left half contains smaller or equal elements compared to the right half.
   - For a given partition in `nums1` at index `partition1`, calculate the corresponding partition in `nums2` as `partition2 = (m + n + 1) / 2 - partition1`. This setup ensures that the total elements in the left half equal the total in the right half.

3. **Finding the Correct Partition**:
   - After partitioning, check the largest elements on the left (`maxLeft1` from `nums1` and `maxLeft2` from `nums2`) and the smallest elements on the right (`minRight1` from `nums1` and `minRight2` from `nums2`).
   - If `maxLeft1 <= minRight2` and `maxLeft2 <= minRight1`, we’ve found the correct partition, where all elements in the left half are smaller than those in the right half.

4. **Calculate the Median**:
   - If the total number of elements is even, the median is the average of the two middle elements: `median = (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0`.
   - If the total number is odd, the median is the maximum element in the left half: `median = max(maxLeft1, maxLeft2)`.

5. **Adjust the Binary Search**:
   - If `maxLeft1 > minRight2`, move the partition in `nums1` to the left (i.e., `right = partition1 - 1`).
   - If `maxLeft2 > minRight1`, move the partition in `nums1` to the right (i.e., `left = partition1 + 1`).

This approach enables us to find the median in \(O(\log \min(m, n))\) time by only focusing on partitioning rather than merging the arrays.

#### **4. Implement**

Here's the C++ code implementing this plan:

```cpp
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }

    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;

    while (left <= right) {
        int partitionA = (left + right) / 2;
        int partitionB = (m + n + 1) / 2 - partitionA;

        int maxLeftA = (partitionA == 0) ? INT_MIN : nums1[partitionA - 1];
        int minRightA = (partitionA == m) ? INT_MAX : nums1[partitionA];
        int maxLeftB = (partitionB == 0) ? INT_MIN : nums2[partitionB - 1];
        int minRightB = (partitionB == n) ? INT_MAX : nums2[partitionB];

        if (maxLeftA <= minRightB && maxLeftB <= minRightA) {
            if ((m + n) % 2 == 0) {
                return (max(maxLeftA, maxLeftB) +
                        min(minRightA, minRightB)) /
                        2.0;
            } else {
                return max(maxLeftA, maxLeftB);
            }
        } else if (maxLeftA > minRightB) {
            right = partitionA - 1;
        } else {
            left = partitionA + 1;
        }
    }

    return 0.0;
}
```

#### **5. Review**
- **Example Walkthrough**: For `nums1 = [1, 3]` and `nums2 = [2]`, the function partitions the arrays and correctly identifies the median as `2.0`.
- **Edge Cases**:
  - Single-element arrays, such as `nums1 = []` and `nums2 = [1]`, work correctly and return `1.0`.
  - Handles cases when one array is significantly larger than the other by adjusting partitions correctly.
  
#### **6. Evaluate**
- **Time Complexity**: \(O(\log \min(m, n))\), since we only perform binary search on the smaller array.
- **Space Complexity**: \(O(1)\), requiring only a constant amount of extra space.
- **Strengths**: Efficiently finds the median without merging the arrays.
- **Weaknesses**: None for valid input constraints; the approach meets all requirements.
- **Potential Improvements**: The solution is already optimal for the given problem constraints.

This solution effectively uses binary search to partition two sorted arrays, allowing for efficient median calculation in logarithmic time.