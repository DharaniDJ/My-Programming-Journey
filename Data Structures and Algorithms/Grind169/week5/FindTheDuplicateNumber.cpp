
// Problem Link : https://leetcode.com/problems/find-the-duplicate-number/

// Approach 1 (Brute Force) : O(n^2) time and O(1) complexity
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<n;i++){
            int cnt = 0;
            for(int j=0;j<n;j++){
                if(nums[j]==nums[i]) cnt++;
                if(cnt==2) return nums[i];
            }
        }
        return -1;
    }
};

// Approach 2 (sorting) : O(nlogn) time and O(logn) space complexity
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        
        for(int i=0;i<n-1;i++){
            if(nums[i]==nums[i+1]) return nums[i];
        }
        return -1;
    }
};

// Approach 3 (count array) : O(n) time and O(n) space complexity
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int cnt[n];
        memset(cnt,0,sizeof(cnt));

        for(int i=0;i<n;i++){
            if(cnt[nums[i]-1]==1) return nums[i];
            cnt[nums[i]-1]++;
        }

        return -1;
    }
};

// Negative marking : O(n) time and O(1) space complexity
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        for(int i=0;i<n;i++){
            int k = abs(nums[i]);
            if(nums[k-1]<0) return k;
            nums[k-1]*= -1;
        }

        return -1;
    }
};

// Array as Map (Recursive): O(n) time and O(n) space complexity
class Solution {
public:
    int store(vector<int>& nums, int cur) {
        if (cur == nums[cur])
            return cur;
        int nxt = nums[cur];
        nums[cur] = cur;
        return store(nums, nxt);
    }

    int findDuplicate(vector<int>& nums) {
        return store(nums, 0);
    }
};

// Array as Map (Iterative): O(n) time and O(1) space complexity
// The key idea is to always map the number at index 0 to its equivalent index.
// we will bring the number from the next index to index and continue from there
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();

        while(nums[0]!=nums[nums[0]]){
            swap(nums[0],nums[nums[0]]);
        }

        return nums[0];
    }
};

// Sum of Bits : O(nlogn) time and O(1) space complexity

//  To understand this, let's take a step back and reconsider the example array [3,1,3,2,4]
// However, for this example ignore the binary representation of each number.
// Pretend base_count is an array where base_count[num] contains the frequency of number num.
// so for the range [1,4], base_count is [1,1,1,1] and nums_count is count of each number [1,1,2,1].
// Then the differnce is [1,1,2,1] - [1,1,1,1] = [0,0,1,0]. The 3rd index is the only index to have
// a positive count and thus 3 is the duplicate number.

class Solution {
public:
    int calMaxBits(int num){
        int bits = 0;
        while(num){
            num/=2;
            bits++;
        }
        return bits;
    }

    int findDuplicate(vector<int>& nums) {
        int duplicate = 0;
        int n = nums.size()-1;
        int max_num = *max_element(nums.begin(),nums.end());
        int max_bit = calMaxBits(max_num);

        for(int bit = 0; bit<max_bit;bit++){
            int mask =(1<<bit);
            int base_cnt = 0, nums_cnt = 0;

            for(int i=0;i<=n;i++){
                if(i&mask) base_cnt++;
                if(nums[i]&mask) nums_cnt++;
            }

            if(nums_cnt>base_cnt) duplicate |= mask;
        }
        return duplicate;
    }
};

// Floyd's Tortoise and Hare (Cycle Detection) : O(n) time and O(1) time complexity

// For Example, consider nums = [2,6,4,1,3,1,5]
// If one starts from x = nums[0], such a sequence will produce a linked list with a cycle.

// start from 2
// nums[2]=4
// nums[4]=3
// nums[3]=1<----------
// nums[1]=6           |
// nums[6]=5           | (Cycle!)
// nums[5]=1<----------

//                    6
//                  / |
// 2 -> 4 -> 3 -> 1   |
//                  \ |
//                    5

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[0];
        do{
            slow = nums[slow];
            fast = nums[nums[fast]];
        }while(slow!=fast);
        
        slow = nums[0];
        while(slow!=fast){
            slow = nums[slow];
            fast = nums[fast];
        }
        
        return slow;
    }
};