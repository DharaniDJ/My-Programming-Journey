
// Problem Link : https://leetcode.com/problems/longest-repeating-character-replacement/

// Approach 1(Binary Search + Sliding Window) : O(nlogn) time and O(m)
class Solution {
public:
    bool solve(string &s, int mid, int k){
        int n = s.size();

        int freq[26];
        memset(freq,0,sizeof(freq));

        int max_freq = 0;
        for(int i=0;i<n;i++){
            freq[s[i]-'A']++;

            if(i>=mid){
                freq[s[i-mid]-'A']--;
            }
            max_freq = max(max_freq, freq[s[i]-'A']);

            if(mid - max_freq <= k){
                return true;
            }
        }
        return false;
    }

    int characterReplacement(string s, int k) {
        int n = s.size();

        // binary search over the length of substring
        // lo contains the valid value, and hi contains the
        // invalid value
        int lo = 1, hi = n+1;
        int mid;

        while(lo+1 < hi){
            mid = lo + (hi-lo)/2;

            // can we make a valid substring of length `mid`?
            if(solve(s,mid,k)){
                lo = mid;
            }else{
                hi = mid;
            }
        }

        // length of the longest substring that satisfies
        // the given condition
        return lo;
    }
};

// Sliding Window (Slow) : O(n*m) time and O(m) space complexity
class Solution {
public:
    
    bool isWindowValid(int start, int end, int cnt, int k){
        return end-start+1-cnt <= k;
    }
    
    int characterReplacement(string s, int k) {
        int n = s.size();
        
        int ans = 0;
        // collect all unique letters
        set<char> st;
        for(char c : s) st.insert(c);
        
        for(auto c : st){
            int start = 0;
            int cnt = 0;
            for(int end=0;end<n;end++){
                if(s[end]==c){
                    cnt++;
                }
                
                while(!isWindowValid(start,end,cnt,k)){
                    if(s[start]==c){
                        cnt--;
                    }
                    start++;
                }
                ans = max(ans,(end-start+1));
            }
        }
        return ans;
    }
};

// Sliding Window (Fast) : O(n) time and O(m) space complexity

// once we have found a valid window, we don't need to decrease the size of it. The window keeps moving toward the right. 
// At each step, even if the window becomes invalid, we never decrease its size. We increase the size only when we find a valid window of larger size.
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        int freq[26] = {0};

        int start = 0;
        int ans = 0;
        int max_freq = 0;

        for(int i=0;i<n;i++){
            char c = s[i];
            freq[c-'A']++;
            max_freq = max(max_freq,freq[c-'A']);

            if(i-start+1-max_freq <= k){
                ans = max(ans,(i-start+1));
            }else{
                // move the start pointer towards right if the current
                // window is invalid
                freq[s[start]-'A']--;
                start++;
            }
        }
        return ans;
    }
};