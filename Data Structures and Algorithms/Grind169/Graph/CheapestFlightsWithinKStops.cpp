
// Problem Link : https://leetcode.com/problems/cheapest-flights-within-k-stops/

// BFS : O(v + e*k) time and O(v + e*k) space complexity
// our problem limits the number of stops to k. As a result, we need not search the paths with lengths greater than k + 1.
// A breadth-first search can be used for this problem because the number of levels to be explored by the algorithm is bounded by k.

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int,int>> adj[n];

        for(auto flight : flights){
            adj[flight[0]].push_back({flight[1],flight[2]});
        }

        vector<int> dist(n,INT_MAX);
        queue<pair<int,int>> q;
        q.push({src,0});

        while(!q.empty() && k>=0){
            int sz = q.size();
            // iterate on current level
            while(sz--){
                auto [node, distance] = q.front();
                q.pop();

                for(auto& [neighbor, price] : adj[node]){
                    if(dist[neighbor]>distance+price){
                        dist[neighbor] = distance+price;
                        q.push({neighbor, dist[neighbor]});
                    }
                }
            }
            k--;
        }
        return dist[dst]==INT_MAX ? -1 : dist[dst] ;
    }
};


// Approach 2(Dijkstra) : O(v + e*k*log(e*k)) time and O(v + e*k) space complexity
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int,int>> adj[n];

        for(auto flight : flights){
            adj[flight[0]].push_back({flight[1],flight[2]});
        }

        // storing the steps required to reach a node from the src node.
        vector<int> dist(n,INT_MAX);

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> q;
        // {dist_from_src, node, num_of_stops_from_src}
        q.push({0,src,0});

        while(!q.empty()){
            auto f = q.top();
            q.pop();

            int d = f[0];
            int node = f[1];
            int steps = f[2];
            // We have already encountered a path with a lower cost and fewer stops,
            // or the number of stops exceeds the limit.
            if (steps > dist[node] || steps > k + 1) continue;
            dist[node]=steps;
            if(node==dst) return d;
            for(auto& [neighbor,price] : adj[node]){
                q.push({d+price,neighbor,steps+1});
            }
        }
        return -1;
    }
};

// Approach3 (Bellman Ford) : O(n*k + e*k)(swap dist arrays(n*k) + iterating all edges(e*k)) time and O(v) space complexity
// Bellman Ford's algorithm is used to find the shortest paths from the source node to all other vertices in a weighted graph.
// It depends on the idea that the shortest path contains at most N - 1 edges (where N is the number of nodes in the graph)
// because the shortest path cannot have a cycle.
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        // Distance from source to all other nodes.
        vector<int> dist(n,INT_MAX);
        dist[src]=0;

        // Run only k+1 times since we want shortest distace in k hops.
        for(int i=0;i<=k;i++){
            // create a copy of dist vector
            vector<int> temp(dist);
            for(auto& flight : flights){
                if(dist[flight[0]]!=INT_MAX){
                    temp[flight[1]] = min(temp[flight[1]], dist[flight[0]]+flight[2]);
                }
            }
            dist = temp;
        }

        return dist[dst]==INT_MAX ? -1 : dist[dst];
    }
};