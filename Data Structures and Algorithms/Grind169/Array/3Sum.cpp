
// Problem Link: https://leetcode.com/problems/3sum/

// 2 pointer : O(n^2) time and O(logn) or O(n) space complexity
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n =nums.size();
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());

        if(n<3) return res;

        for(int i=0;i<(n-2);i++){
            if(i==0 || (i>0 && nums[i]!=nums[i-1])){
                int j = i+1;
                int k = n-1;
                int sum = 0-nums[i];
                while(j<k){
                    if(nums[j]+nums[k]==sum){
                        res.push_back({nums[i],nums[j],nums[k]});
                        while(j<k && nums[j]==nums[j+1]) j++;
                        while(j<k && nums[k]==nums[k-1]) k--;
                        j++;
                        k--;
                    }else if(nums[j]+nums[k]<sum){
                        j++;
                    }else{
                        k--;
                    }
                }
            }
        }
        return res;
    }
};

// Hashset : O(n^2) time and O(n) space complexity
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(begin(nums), end(nums));
        vector<vector<int>> res;
        for (int i = 0; i < nums.size(); ++i)
            if (i == 0 || nums[i - 1] != nums[i]) {
                unordered_set<int> seen;
                for (int j = i + 1; j < nums.size(); ++j) {
                    int complement = -nums[i] - nums[j];
                    if (seen.count(complement)) {
                        res.push_back({nums[i], complement, nums[j]});
                        while (j + 1 < nums.size() && nums[j] == nums[j + 1]) {
                            ++j;
                        }
                    }
                    seen.insert(nums[j]);
                }
            }
        return res;
    }
};

// no-sort : O(n^2) time and O(n) space complexity.
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {

        // we loop thru the nums, and for each iteration num1,
        // we have another loop
        //walk thru the right of num2. we store num2 in a map and
        // meantime check if -num1-num2 in map already.

        set<vector<int>> res;
        unordered_set<int> dups;
        unordered_map<int,int> seen;

        int n = nums.size();

        for(int i=0;i<n;i++){
            // we skip if we already seen num1 before
            if(dups.insert(nums[i]).second){
                for(int j=i+1;j<n;j++){
                    int compliment = -nums[i]-nums[j];
                    auto it = seen.find(compliment);
                    // note that here we need to make sure for each num1,
                    // we should have its own dict, otherwise we would reuse
                    // the num and have wrong triplets.
                    // to do that we save the index i as value of num2,
                    // so that we know num1,num2 and compliment have different index
                    if(it!=seen.end() && it->second==i){
                        vector<int> triplet = {nums[i],nums[j],compliment};
                        sort(begin(triplet), end(triplet));
                        res.insert(triplet);
                    }
                    seen[nums[j]]=i;
                }
            }
        }
        return vector<vector<int>>(begin(res), end(res));
    }
};