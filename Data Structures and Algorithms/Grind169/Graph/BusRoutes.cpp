
// Problem Link : https://leetcode.com/problems/bus-routes/

// Approach1 : 
// Intuition : Instead of thinking of the stops as node, think of buses as nodes.
// One difficulty is to efficiently decide whether two buses are connected by an edge. They are connected if they share at least one bus stop.
// Whether two lists share a common value can be done by set intersection (HashSet), or by sorting each list and using a two pointer approach.

// using two pointer
class Solution {
public:
    bool check(vector<int> a, vector<int> b){
        int i=0, j=0;
        while(i<a.size() && j<b.size()){
            if(a[i]==b[j]) return true;
            else if(a[i]<b[j]) i++;
            else j++;
        }
        return false;
    }

    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source == target) return 0;
        int n = routes.size();

        vector<int> adj[n];

        for(int i=0;i<n;i++){
            sort(routes[i].begin(),routes[i].end());
        }

        set<int> seen, targets;
        queue<int> q;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(check(routes[i],routes[j])){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        // Initialize seen, queue, targets.
        // seen represents whether a node has ever been enqueued to queue.
        // queue handles our breadth first search.
        // targets is the set of goal states we have.
        for(int i=0;i<n;i++){
            if(binary_search(routes[i].begin(),routes[i].end(),source)){
                seen.insert(i);
                q.push(i);
            }

            if(binary_search(routes[i].begin(),routes[i].end(),target)){
                targets.insert(i);
            }
        }

        int ans = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto f = q.front();
                q.pop();

                if(targets.count(f)) return ans+1;
                for(int nei : adj[f]){
                    if(seen.count(nei)==0){
                        seen.insert(nei);
                        q.push(nei);
                    }
                }

            }
            ans++;
        }

        return -1;
    }
};

// using sets
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        
        if(source == target) return 0;
        unordered_map<int,vector<int>> adj;
        
        int n = routes.size();
        for(int i=0;i<n;i++){
            for(int j : routes[i]){
                int cur_stop = j;
                int cur_bus = i;
                adj[cur_stop].push_back(cur_bus); // from cur_stop, bus no. i can be boarded
            }
        }
        
        int ans = 0;
        queue<int> q;
        set<int> vis;
        q.push(source);
        vis.insert(source);
        
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int f = q.front();
                q.pop();
                
                if(f==target) return ans;
                
                // iterate over the stops                
                for(int i : adj[f]){
                    // iterate over the buses
                    for(int j : routes[i]){
                        if(vis.count(j)==0){
                            vis.insert(j);
                            q.push(j);
                        }
                    }
                    // clear the route
                    routes[i].clear();
                }
            }
            ans++;
        }
        return -1;
    }
};