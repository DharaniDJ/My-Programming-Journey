
// Problem Link : https://leetcode.com/problems/alien-dictionary

// Approach1(topo sort)
class Solution {
public:
    string alienOrder(vector<string>& words) {

        // create DataStructures and find all unique characters
        unordered_map<char,vector<char>> adj;
        unordered_map<char,int> cnt; // inward edges count
        for(string word : words){
            for(char ch : word){
                cnt[ch] = 0;
            }
        }

        // find all edges
        int n = words.size();
        for(int i=0;i<(n-1);i++){
            string word1 = words[i];
            string word2 = words[i+1];

            // Check that word2 is not a prefix of word1
            if(word1.length() > word2.length() && word1.rfind(word2, 0) == 0) return "";

            for(int j=0;j<min(word1.size(),word2.size());j++){
                if(word1[j] != word2[j]){
                    adj[word1[j]].push_back(word2[j]);
                    cnt[word2[j]]++;
                    break;
                }
            }
        }

        // bfs
        string ans = "";
        queue<char> q;
        for(auto& [key,val] : cnt){
            if(val==0) q.push(key);
        }

        while(!q.empty()){
            char c = q.front();
            q.pop();
            ans+=c;

            for(auto next : adj[c]){
                cnt[next]--;
                if(cnt[next]==0) q.push(next);
            }
        }

        if(ans.length()<cnt.size()) return "";
        
        return ans;
    }
};