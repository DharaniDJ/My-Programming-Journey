
// Problem Link : https://leetcode.com/problems/insert-delete-getrandom-o1/

// You must implement the functions of the class such that each function works in average O(1) time complexity.
// Approach 1

// Using Hashmap, insert and Delete is done in average constant time, although has problems with getRandom
// The idea of getRandom is to choose a random index and then to retrieve the element with that index.
// There is no indexes in hashmap, and hence to get true random value, one has first to convert hashmap keys in a list,
// that would take linear time. The solution here is to build a list of
// keys aside and to use this list to compute GetRandom in constant time.

// Using ArrayList, insert and getRandom is done in average constant time, though has problems with Delete
// The solution here is always delete the last element:
// swap the element to delete with last element and pop the last element

// For that, one has to compute an index of each element in constant time, and hence
// needs a hashmap which stores element -> its index dictionary

class RandomizedSet {
    unordered_map<int,int> vals;
    vector<int> idxs;
public:
    RandomizedSet() {

    }

    bool insert(int val) {
        if(vals.find(val)!=vals.end()) return false;
        vals[val]=idxs.size();
        idxs.push_back(val);
        return true;
    }

    bool remove(int val) {
        if(vals.find(val)==vals.end()) return false;

        int lst = idxs.back();
        int pos = vals[val];

        // move the last element to the place idx of the element to delete
        vals[lst]=pos;
        idxs[pos]=lst;
        // delete the last element
        vals.erase(val);
        idxs.pop_back();

        return true;
    }

    int getRandom() {
        return idxs[rand() % (idxs.size())];
    }
};