
// Problem Link : https://leetcode.com/problems/time-based-key-value-store/

// Approach 1(Hashmap + Linear Search) : O(L) time for set() O(L) space for set and O(timestamp*L) time for get();
class TimeMap {
    unordered_map<string,unordered_map<int,string>> mp;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if(!mp.count(key)) return "";
        
        for(int cur = timestamp;cur>=1;cur--){
            if(mp[key].count(cur)) return mp[key][cur];
        }
        return "";
    }
};

// Approach 2(Sorted Map + Binary Search) : O(L* logM) time for set() O(L) space for set and O(L*logM + logM) time for get();

// we will find the upper_bound of the given timestamp, upper_bound function returns
// an iterator pointing to the first element that is greater than the searched value.
// Thus, the left element of the iterator will be equal to or just smaller than the searched value.

// If upper_bound points to the beginning of the map it means no time less than or equal
// to the given timestamp exists in the map thus we return a null string.

class TimeMap {
    unordered_map<string,map<int,string>> mp;
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        mp[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        if(!mp.count(key)) return "";
        
        auto it = mp[key].upper_bound(timestamp);
        
        if (it == mp[key].begin()) {
            return "";
        }
        return prev(it)->second;
    }
};

// Approach 3(Array + Binary Search) : O(L) time for set(), O(L) space for set and O(L*logM) time for get();
// In the problem statement carefully, it is mentioned that "All the timestamps of set are strictly increasing",
// thus even if we use an array to store the timestamps, they will be pushed in sorted order.
class TimeMap {
public:
    unordered_map<string, vector<pair<int, string>>> keyTimeMap;
    TimeMap() {
    }
    
    void set(string key, string value, int timestamp) {
        // Push '(timestamp, value)' pair in 'key' bucket.
        keyTimeMap[key].push_back({ timestamp, value });
    }
    
    string get(string key, int timestamp) {
        // If the 'key' does not exist in map we will return empty string.
        if (keyTimeMap.find(key) == keyTimeMap.end()) {
            return "";
        }
        
        if (timestamp < keyTimeMap[key][0].first) {
            return "";
        }
        
        // Using binary search on the array of pairs.
        int left = 0;
        int right = keyTimeMap[key].size();
        
        while (left < right) {
            int mid = (left + right) / 2;
            if (keyTimeMap[key][mid].first <= timestamp) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        // If iterator points to first element it means, no time <= timestamp exists.
        if (right == 0) {
            return "";
        }
                
        return keyTimeMap[key][right - 1].second;
    }
};