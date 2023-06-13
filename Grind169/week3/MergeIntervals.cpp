
// Problem Link : https://leetcode.com/problems/merge-intervals

// Approach 1 (connected Comp) (TLE) : O(n^2) time and O(n^2) space complexity
class Solution {
    map<vector<int>, vector<vector<int>> > mp;
    set<vector<int>> vis;
    map<int,vector<vector<int>> > nodes_in_comp;
public:

    bool isoverlap(vector<int> &it1, vector<int> &it2){
        return it1[1]>=it2[0] and it1[0]<=it2[1];
    }

    void generateGraph(vector<vector<int>>& intervals){
        for(auto it1 : intervals){
            for(auto it2 : intervals){
                if(isoverlap(it1,it2)){
                    mp[it1].push_back(it2);
                    mp[it2].push_back(it1);
                }
            }
        }
    }

    vector<int> componentInterval(vector<vector<int>> &nodes){
        int min_start = nodes[0][0];
        int max_end = nodes[0][1];
        for(auto it : nodes){
            min_start = min(min_start,it[0]);
            max_end = max(max_end, it[1]);
        }
        return {min_start,max_end};
    }

    void markComponentDFS(vector<int>& interval, int comp_idx){
        nodes_in_comp[comp_idx].push_back(interval);
        vis.insert(interval);
        for(auto it : mp[interval]){
            if(vis.find(it)==vis.end()){
                markComponentDFS(it,comp_idx);
            }
        }
        return;
    }

    void buildComponents(vector<vector<int>>& intervals){
        int comp_idx = 0;
        for(auto it : intervals){
            if(vis.find(it)==vis.end()){
                markComponentDFS(it,comp_idx);
                comp_idx++;
            }
        }
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        generateGraph(intervals);
        buildComponents(intervals);

        vector<vector<int>> res;

        for(auto it: nodes_in_comp){
            res.push_back(componentInterval(it.second));
        }
        return res;
    }
};

// Approach 2 (sorting) : O(n*logn) time and O(n) or O(logn) space complexity
class Solution {
public:

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(),intervals.end());

        vector<vector<int>> res;
        int start=intervals[0][0];
        int end=intervals[0][1];
        for(int i=1;i<n;i++){
            auto it = intervals[i];
            if(it[0]>end){
                res.push_back({start,end});
                start = it[0];
                end = it[1];
            }else{
                end = max(end,it[1]);
            }
        }
        res.push_back({start,end});
        return res;
    }
};