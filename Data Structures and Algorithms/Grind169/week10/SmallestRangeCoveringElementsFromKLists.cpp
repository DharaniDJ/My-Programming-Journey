
// Problem Link : https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/

// Approach1(Two Pointer Technique) : O(N*K) time and O(K) space complexity
// where K is the no. of lists, and N is the total elements in all the lists
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& arr) {
        int K = arr.size();

        vector<int> ptr(K,0);

        int i, minval, maxval, minrange, minel, maxel, flag, minind;

        minrange = INT_MAX;

        while(1){
            // for maintaining the index of list containing the
            // minimum element
            minind = -1;
            minval = INT_MAX;
            maxval = INT_MIN;
            flag = 0;
            // iterating over all the list
            for (i = 0; i < K; i++) {
                // if every element of list[i] is traversed then
                // break the loop
                if (ptr[i] == arr[i].size()) {
                    flag = 1;
                    break;
                }
                // find minimum value among all the list
                // elements pointing by the ptr[] array
                if (ptr[i] < arr[i].size() && arr[i][ptr[i]] < minval) {
                    minind = i; // update the index of the list
                    minval = arr[i][ptr[i]];
                }
                // find maximum value among all the list
                // elements pointing by the ptr[] array
                if (ptr[i] < arr[i].size() && arr[i][ptr[i]] > maxval) {
                    maxval = arr[i][ptr[i]];
                }
            }

            // if any list exhaust we will not get any better
            // answer, so break the while loop
            if (flag)
                break;

            ptr[minind]++;
            // updating the minrange
            if ((maxval - minval) < minrange) {
                minel = minval;
                maxel = maxval;
                minrange = maxel - minel;
            }
        }

        return {minel,maxel};
    }
};

// Approach2(Sliding window method) : O(N*logN) time and O(N) space complexity
// Firstly we merge k groups to one group, each number recoard it's group
// we can slide window by group when current groups satifies condition and recoard min range.
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int K = nums.size();
        
        vector<pair<int,int>> res; // {element, index of the list}
        
        for(int i=0;i<K;i++){
            for(auto num : nums[i]){
                res.push_back({num,i});
            }
        }
        
        sort(begin(res),end(res));
        
        int i=0, k=0;
        
        vector<int> ans;
        unordered_map<int,int> mp;
        
        for(int j=0;j<(int)res.size();j++){
            if(mp.find(res[j].second)==mp.end()) {
                mp[res[j].second]++;
                k++;
            }else{
                mp[res[j].second]++;
            }
            
            if(k==K){
                while(mp[res[i].second]>1) mp[res[i++].second]--;
                if(ans.empty() || ((ans[1]-ans[0]) > (res[j].first - res[i].first))){
                    ans = vector<int>{res[i].first, res[j].first};
                }
            }
        }
        
        return ans;
    }
};

// Approach3(Priority Queue) : O(N*logK) time and O(K) space complexity
class Solution {
public:
    
    struct comp{
        bool operator()(const vector<int> &a, const vector<int> &b){
            return a[0]>b[0];
        }
    };
    
    vector<int> smallestRange(vector<vector<int>>& arr) {
        
        int K = arr.size();
        // {element, index of the list, index of the next element}
        priority_queue<vector<int>, vector<vector<int>>, comp> mnh;
        
        // Create a min heap with k heap nodes. Every heap node
        // has first element of an list
        int range = INT_MAX;
        int min = INT_MAX, max = INT_MIN;
        int start, end;
        
        for(int i=0;i<K;i++){
            mnh.push({arr[i][0],i,1});
            if(max < arr[i][0]) max = arr[i][0];
        }
        
        while(1){
            auto tp = mnh.top();
            mnh.pop();

            min = tp[0];
            cout << min << ", ";
            
            if(range>(max-min+1)){
                range = max-min+1;
                start = min;
                end = max;
            }
            
            if(tp[2]<arr[tp[1]].size()){
                tp[0] = arr[tp[1]][tp[2]];
                tp[2]+=1;
                if(tp[0] > max) max = tp[0];
                mnh.push(tp);
            }else{
                break;
            }
        }
        
        return {start,end};
    }
};