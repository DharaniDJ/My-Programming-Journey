
// Problem Link : https://leetcode.com/problems/rotate-array/

// Brute Force : O(n*k) time and O(1) space complexity
// shift 1 element each for k times
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k%=n;

        for(int i=0;i<k;i++){
            int lastEle = nums[n-1];
            for(int j=0;j<n;j++){
                int temp = nums[j];
                nums[j]=lastEle;
                lastEle = temp;
            }
        }
        return;
    }
};

// Approach 2(using extra space) : O(n) time and O(n) space complexity
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k%=n;

        vector<int> a(n);
        for(int i=0;i<n;i++){
            a[(i+k)%n]=nums[i];
        }

        for(int i=0;i<n;i++){
            nums[i]=a[i];
        }
    }
};

// Cyclic replacement : O(n) time and O(1) space complexity
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k%=n;
        
        int cnt = 0;
        for(int start=0;cnt<n;start++){
            int cur = start;
            int prev = nums[start];
            do{
                int next = (cur+k)%n;
                int temp =  nums[next];
                nums[next] = prev;
                prev = temp;
                cur = next;
                cnt++;
            }while(cur!=start);
        }
    }
};

// Approach 4 (using reverse) : O(n) time and O(1) space complexity
class Solution {
public:
    void reverse(vector<int> &nums,int l, int r){
        while(l<r){
            swap(nums[l++],nums[r--]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k%=n;

        reverse(nums,0,n-k-1);
        reverse(nums,n-k,n-1);
        reverse(nums,0,n-1);
    }
};