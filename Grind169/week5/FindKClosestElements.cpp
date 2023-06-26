
// Problem Link : https://leetcode.com/problems/find-k-closest-elements/

// Sort with custom comparator : O(n*logn + k*logk) time and O(n) space complexity
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<pair<int,int>> p;
        vector<int> res;
        for(int num:arr){
            p.push_back({abs(num-x),num});
        }

        auto cmp = [](pair<int,int> a, pair<int,int> b) {
            if(a.first<b.first){
                return true;
            }else if(a.first==b.first){
                return a.second<b.second;
            }
            return false;
        };

        sort(p.begin(),p.end(),cmp);
        for(int i=0;i<k;i++){
            res.push_back(p[i].second);
        }

        sort(res.begin(),res.end());
        return res;
    }
};

// MaxHeap : O(n*logk) time and O(k) space complexity
class Solution {
public:
    vector<int> findClosestElements(vector<int>& nums, int k, int x) {
        vector<int> res;
        priority_queue<pair<int,int>> mxH;

        for(int num:nums){
            mxH.push({abs(num-x),num});
            if(mxH.size()==k+1) mxH.pop();
        }

        while(!mxH.empty()){
            auto f = mxH.top();
            mxH.pop();
            res.push_back(f.second);
        }

        sort(res.begin(),res.end());
        return res;
    }
};

// Binary search + 2 pointer : O(logn + k) time and O(1) space complexity
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res;
        
        if(arr.size()==k) return arr;
        
        int left = 0;
        int right = arr.size();
        int mid = 0;
        while(left<right){
            mid = left+(right-left)/2;
            if(arr[mid]<x){
                left=mid+1;
            }else{
                right = mid;
            }
        }
        
        // Initialize our sliding window's bounds
        left-=1;
        right = left+1;

        // While the window size is less than k
        while(right-left-1 < k){
            if(left==-1){
                right+=1;
                continue;
            }

            // Expand the window towards the side with the closer number
            if(right==arr.size() || abs(arr[left] - x) <= abs(arr[right] - x)){
                left-=1;
            }else{
                right+=1;
            }
        }

        // Build and return the window
        for(int i=left+1;i<right;i++){
            res.push_back(arr[i]);
        }

        return res;
    }
};