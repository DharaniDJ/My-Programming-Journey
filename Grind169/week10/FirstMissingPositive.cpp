
// Problem Link : https://leetcode.com/problems/first-missing-positive

// Approach1(Index as a hash key) : O(n) time and O(1) space complexity
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        bool fl = false;        
        for(int i=0;i<n;i++){
            if(nums[i]==1) fl = true;
            else if(nums[i]<=0) nums[i]=1;
            else if(nums[i]>n) nums[i]=1;
        }
        
        for(int i=0;i<n;i++){
            int k = abs(nums[i]);
            int temp = nums[k-1];
            if(k==1 && !fl) continue;
            if(temp>0) nums[k-1]*=-1;
        }
        
        for(int i=0;i<n;i++){
            if(nums[i]>0) return i+1;
        }
        return n+1;
    }
};

// Approach2(Cyclic Sort) : O(n) time and O(1) space complexity
// Reference : https://emre.me/coding-patterns/cyclic-sort/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        bool fl = false;        
        for(int i=0;i<n;i++){
            if(nums[i]==1) fl = true;
            else if(nums[i]<=0) nums[i]=1;
            else if(nums[i]>n) nums[i]=1;
        }
        
        for(int num : nums) cout << num << ", ";
        cout << endl;
        
        int start = 0;
        while(start<n){
            int num = nums[start];
            if(nums[num-1]==num) {start++; continue;}
            if(num<=n && num!=start+1){
                int k = nums[start];
                nums[start] = nums[num-1];
                nums[num-1] = k;
            }else{
                start++;
            }
        }
        
        if(!fl) return 1;
        
        for(int i=0;i<n;i++){
            if(nums[i]!=i+1) return i+1;
        }
        
        return n+1;
    }
};