
// Problem Link : https://leetcode.com/problems/median-of-two-sorted-arrays/

// Approach1(merge sort) : O(n+m) time and O(1) space complexity
class Solution {
    int l = 0, r = 0;
    int n;
    int m;
public:
    int getMin(vector<int> &nums1, vector<int> &nums2){
        if(l<n && r<m){
            return nums1[l] < nums2[r] ? nums1[l++] : nums2[r++];
        }else if(l<n){
            return nums1[l++];
        }else if(r<m){
            return nums2[r++];
        }
        return -1;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size();
        m = nums2.size();

        int k = (n+m)/2;

        if((n+m)%2 == 0){
            for(int i = 0; i < k - 1; i++){
                int _ = getMin(nums1,nums2);
            }
            return (double)(getMin(nums1, nums2) + getMin(nums1, nums2)) / 2;
        }else{
            for(int i = 0; i < k; i++){
                int _ = getMin(nums1,nums2);
            }
            return (double)(getMin(nums1,nums2));
        }

        return -1;
    }
};

// Approach2(BS + Recursion) : O(log(n*m)) time and O(log(n*m)) space complexity
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        int n = A.size();
        int m = B.size();

        int len = n+m;

        if(len%2){
            return solve(A,B,len/2,0,n-1,0,m-1);
        }else{
            return 1.0*(solve(A,B,len/2 -1,0,n-1,0,m-1)+solve(A,B,len/2,0,n-1,0,m-1))/2;
        }
    }

    int solve(vector<int>& A, vector<int>& B, int k, int aStart, int aEnd, int bStart, int bEnd) {
        // If the segment of on array is empty, it means we have passed all
        // its element, just return the corresponding element in the other array.
        if(aStart>aEnd){
            return B[k-aStart];
        }

        if(bStart>bEnd){
            return A[k-bStart];
        }

        // Get the middle indexes and middle values of A and B.
        int aIndex = (aStart + aEnd) / 2, bIndex = (bStart + bEnd) / 2;
        int aValue = A[aIndex], bValue = B[bIndex];

        // If k is in the right half of A + B, remove the smaller left half.
        if (aIndex + bIndex < k) {
            if (aValue > bValue) {
                return solve(A, B, k, aStart, aEnd, bIndex + 1, bEnd);
            } else {
                return solve(A, B, k, aIndex + 1, aEnd, bStart, bEnd);
            }
        }
        // Otherwise, remove the larger right half.
        else {
            if (aValue > bValue) {
                return solve(A, B, k, aStart, aIndex - 1, bStart, bEnd);
            } else {
                return solve(A, B, k, aStart, aEnd, bStart, bIndex - 1);
            }
        }
        return -1;
    }
};

//Approach3(Optimized BS) : O(log(min(n,m))) time and O(1) space complexity
class Solution {
public:
    double solve(vector<int>& nums1, vector<int>& nums2, int n, int m){
        if(n>m) return solve(nums2,nums1,m,n);

        int l = 0, r = n;
        while(l<=r){
            int cut1 = (l+r)>>1;
            int cut2 = (n+m+1)/2 - cut1;

            int l1 = cut1==0 ? INT_MIN : nums1[cut1-1];
            int l2 = cut2==0 ? INT_MIN : nums2[cut2-1];
            int r1 = cut1==n ? INT_MAX : nums1[cut1];
            int r2 = cut2==m ? INT_MAX : nums2[cut2];

            if(r1>=l2 && r2>=l1){
                if((n+m)%2==0){
                    return (max(l1,l2)+min(r1,r2))/2.0;
                }else{
                    return (max(l1,l2));
                }
            }else if(r1<l2){
                l = cut1+1;
            }else{
                r=cut1-1;
            }
        }
        return 0.0;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        return solve(nums1,nums2,nums1.size(),nums2.size());
    }
};