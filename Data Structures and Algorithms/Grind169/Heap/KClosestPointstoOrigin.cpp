
// Problem Link: https://leetcode.com/problems/k-closest-points-to-origin/

// Brute Force: O(n*logn) time and O(n) space complexity 
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<pair<int,pair<int,int>>> v;
        for(auto x : points){
            int dist = (x[0]*x[0])+(x[1]*x[1]);
             v.push_back({dist,{x[0],x[1]}});
        }
        sort(v.begin(),v.end());
        vector<vector<int>> ans;
        for(int i=0;i<k;i++){
            ans.push_back({v[i].second.first,v[i].second.second});
        }
        return ans;
    }
};

// Max Heap : O(n*logn) time O(k) space
class Solution {
public:
    pair<double,pair<int,int>> transform(vector<int> &arr){
        double temp = sqrt((arr[0]*arr[0])+(arr[1]*arr[1]));
        return {temp,{arr[0],arr[1]}};
    }
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        vector<vector<int>> res;
        priority_queue<pair<double,pair<int,int>>> mxH;
        for(auto it : points){
            mxH.push(transform(it));
            if(mxH.size()>k) mxH.pop();
        }
        while(!mxH.empty()){
            auto it = mxH.top();
            mxH.pop();
            vector<int> temp;
            temp.push_back(it.second.first);
            temp.push_back(it.second.second);
            res.push_back(temp);
        }
        return res;
    }
};

// quick select : (O(N) in average case and O(N2) in the worst case) time and O(n) space complexity
class Solution {
public:
    int eDist(vector<int> &v){
        return v[0]*v[0] + v[1]*v[1];
    }
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int l = 0;
        int r = points.size()-1;
        while(l<r){
            int m = l+(r-l)/2;
            swap(points[m],points[r]);
            int pivot = eDist(points[r]);
            int border = l;
            for(int i=l;i<r;i++){
                if(eDist(points[i])<=pivot){
                    swap(points[i],points[border++]);
                }
            }
            swap(points[border],points[r]);
            if(border > k-1) r= border-1;
            else if(border < k-1) l = border+1;
            else break;
        }
        vector<vector<int>> res;
        for(int i=0;i<k;i++) res.push_back(points[i]);
        return res;
    }
};