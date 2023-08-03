
// Problem Link : 

// Approach 1 (DFS) : O(NK*logNK) time and O(NK) space complexity
// For time, in the worst case all the emails will end up 
// belonging to single person

// For space, in the end, "vis" set will contain all of the emails,
// hence it will use O(NK) space. Same goes with call stack for DFS
class Solution {
public:
    unordered_set<string> vis;
    unordered_map<string, vector<string>> mp;
    
    void dfs(string& email, vector<string> &temp ){
        vis.insert(email);
        temp.push_back(email);
        
        for(auto it : mp[email]){
            if(vis.find(it) == vis.end()){
                dfs(it,temp);
            }
        }
    }
    
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        for(auto it : accounts){
            int n = it.size();
            string firstEmail = it[1];
            for(int i=2;i<n;i++){
                string email = it[i];
                mp[firstEmail].push_back(email);
                mp[email].push_back(firstEmail);
            }
        }
        vector<vector<string>> res;
        
        for(auto it : accounts){
            string name = it[0];
            string firstEmail = it[1];
            
            if(vis.count(firstEmail)==0){
                vector<string> temp;
                temp.push_back(name);
                dfs(firstEmail,temp);
                sort(temp.begin()+1,temp.end());
                res.push_back(temp);
            }
        }
        return res;
    }
};

// In the prev approach, the first step is to find which accounts
// have an email in common and merge them.

//  Any problem that involves merging connected components (accounts)
// is a natural fit for the Disjoint Set Union (DSU) data structure.

// Approach 2 (Disjoin Set Union)
class DSU{
public:
    vector<int> parent;
    vector<int> size;
    
    DSU(int sz) : parent(sz),size(sz){
        for(int i=0;i<sz;i++){
            parent[i]=i;
            size[i]=1;
        }
    }
    
    int findParent(int x){
        if(x==parent[x]) return x;
        return parent[x] = findParent(parent[x]);
    }
    
    void unionBySize(int a, int b){
        int x = findParent(a);
        int y = findParent(b);
        
        if(x==y) return;
        
        if(size[x]>=size[y]){
            size[x]+=size[y];
            parent[y]=x;
        }else{
            size[y]+=size[x];
            parent[x]=y;
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int sz = accounts.size();
        DSU dsu(sz);
    
        // Maps email to their component index
        unordered_map<string,int> mp;
        for(int i=0;i<sz;i++){
            int n = accounts[i].size();
    
            for(int j=1;j<n;j++){
                string email = accounts[i][j];
                
                // If this is the first time seeing this email then
                // assign component group as the account index
                if(mp.find(email)==mp.end()) {
                    mp[email] = i;
                }
                else {
                    // If we have seen this email before then union this
                    // group with the previous group of the email
                    dsu.unionBySize(i,mp[email]);
                }
            }
        }
        
        // Store emails corresponding to the component's representative
        unordered_map<int,vector<string>> connectedcomp;
            
        for(auto it : mp){
            string email = it.first;
            int grp = it.second;
            connectedcomp[dsu.findParent(grp)].push_back(email);
        }

        // Sort the components and add the account name
        vector<vector<string>> res;

        for(auto it : connectedcomp){
            int grp = it.first;
            vector<string> temp = {accounts[grp][0]};
            temp.insert(temp.end(), it.second.begin(), it.second.end());
            sort(temp.begin()+1,temp.end());
            res.push_back(temp);
        }

        return res;
    }
};