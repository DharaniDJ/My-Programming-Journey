
// Problem Link : https://leetcode.com/problems/minimum-window-substring/

// Approach1(Brute Force) : O(n^3) time and O(1) space complexity
class Solution {
public:

    bool check(string s, string &t){
        unordered_map<char,int> arr; // constant space as s and t consist of uppercase and lowercase English letters.

        for(char c:s){
            arr[c]++;
        }

        for(char c:t){
            arr[c]--;
            if(arr[c]<0) return false;
        }
        return true;
    }

    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();

        for(int sz=m;sz<=n;sz++){
            for(int i=0;i<=(n-sz);i++){
                if(check(s.substr(i,sz),t)){
                    return s.substr(i,sz);
                }
            }
        }

        return "";
    }
 };

 // Approach2(Binary Search) : O((n+m)log(n-m)) time and O(1) space complexity
 class Solution {
public:

    int st = -1, en = -1;
    bool check(string &s, string &t, int k){

        if(k==0) return false;
        unordered_map<char,int> freq;
        unordered_map<char,int> f;

        for(auto c:t) f[c]++;
        for(int i=0;i<s.size();i++){
            if(i>=k){
                bool fl = true;
                for(auto it:f){
                    if(it.second>freq[it.first]){
                        fl=false;
                        break;
                    }
                }
                if(fl){
                    st=i-k;
                    en=i;
                    return true;
                }
                freq[s[i-k]]--;
            }
            freq[s[i]]++;
        }

        bool fl = true;
        for(auto it:f){
            if(it.second>freq[it.first]){
                fl=false;
                break;
            }
        }
        if(fl){
            st=s.size()-k;
            en=s.size();
            return true;
        }
        return false;
    }

    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();

        int l = m;
        int r = n;

        string res = "";
        pair<int,int> p;

        while(l <= r){
            int mid = l+(r-l)/2;
            if(check(s,t,mid)){
                p.first=st;
                p.second=en;
                r=mid-1;
            }else{
                l=mid+1;
            }
        }

        if(st==-1) return "";
        res = s.substr(p.first,(p.second-p.first));
        return res;
    }
 };

// Approach3(Sliding window) : O(n+m) time and O(n+m) space complexity
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();

        if(n==0 || m==0) return "";

        unordered_map<char,int> mp_s;
        unordered_map<char,int> mp_t;

        for(auto c:t) mp_t[c]++;
        int required = mp_t.size();
        int formed = 0;

        int l=0, r=0;
        int ans[3] = {-1,0,0}; // {window length, left, right}

        while(r<n){
            mp_s[s[r]]++;

            if(mp_t.find(s[r])!=mp_t.end() && mp_t[s[r]]==mp_s[s[r]]) formed++;

            while(l<=r && required==formed){
                if(ans[0]==-1 || (r-l+1)<ans[0]){
                    ans[0]=(r-l+1);
                    ans[1]=l;
                    ans[2]=r;
                }
                mp_s[s[l]]--;
                if(mp_t.find(s[l])!=mp_t.end() && mp_t[s[l]]>mp_s[s[l]]) formed--;
                l++;
            }
            r++;
        }

        return ans[0]==-1 ? "" : s.substr(ans[1],ans[0]);
    }
};

// Approach4( Optimized Sliding window ) : O(n+m) time and O(n+m) space complexity
// A small improvement to the above approach can reduce the time complexity of the algorithm to O(2∗∣filtered_S∣+∣S∣+∣T∣), where filtered_S is the string formed from S by removing all the elements not present in T.
// We create a list called filtered_S which has all the characters from string S along with their indices in S, but these characters should be present in T.

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.size();
        int m = t.size();

        if(n==0 || m==0) return "";

        unordered_map<char,int> mp_s;
        unordered_map<char,int> mp_t;

        for(auto c:t) mp_t[c]++;
        int required = mp_t.size();

        vector<pair<int,char>> filtered_s;
        // Look for the characters only in the filtered list instead of entire s.
        // This helps to reduce our search.
        // Hence, we follow the sliding window approach on as small list.

        for(int i=0;i<n;i++){
            char c = s[i];
            if(mp_t.find(c)!=mp_t.end()){
                filtered_s.push_back({i,c});
            }
        }

        int formed = 0;

        int l=0, r=0;
        int ans[3] = {-1,0,0}; // {window length, left, right}

        while(r < (int)filtered_s.size()){
            char c = filtered_s[r].second;
            mp_s[c]++;

            if(mp_t.find(c)!=mp_t.end() && mp_t[c]==mp_s[c]) formed++;

            while(l<=r && required==formed){
                int end = filtered_s[r].first;
                int start = filtered_s[l].first;
                if(ans[0]==-1 || (end-start+1)<ans[0]){
                    ans[0]=(end-start+1);
                    ans[1]=start;
                    ans[2]=end;
                }
                c = filtered_s[l].second;
                mp_s[c]--;
                if(mp_t.find(c)!=mp_t.end() && mp_t[c]>mp_s[c]) formed--;
                l++;
            }
            r++;
        }

        return ans[0]==-1 ? "" : s.substr(ans[1],ans[0]);
    }
};