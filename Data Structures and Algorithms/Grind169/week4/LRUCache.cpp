
// Problem Link : https://leetcode.com/problems/lru-cache/

// Approach1(Double LL) : O(1) for get and put operations, O(capacity) space complexity
class LRUCache {
public:
    class Node{
    public:
        int key;
        int val;
        Node* prev;
        Node* next;

        Node(int key, int val){
            this->key = key;
            this->val = val;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    Node* tail = new Node(-1,-1);
    Node* head = new Node(-1,-1);
    unordered_map<int, Node*> mp;
    int cap;

    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addnode(Node* node){
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void deletenode(Node* node){
        Node* delprev = node->prev;
        Node* delnext = node->next;
        delprev->next = delnext;
        delnext->prev = delprev;
    }

    int get(int k) {
        if(mp.find(k)!=mp.end()){
            Node* node = mp[k];
            int res = node->val;
            mp.erase(k);
            deletenode(node);
            addnode(node);
            mp[k] = head->next;
            return res;
        }
        return -1;
    }

    void put(int k, int v) {
        if(mp.find(k)!=mp.end()){
            Node* node = mp[k];
            mp.erase(k);
            deletenode(node);
        }

        if(mp.size()==cap){
            mp.erase(tail->prev->key);
            deletenode(tail->prev);
        }
        addnode(new Node(k,v));
        mp[k]=head->next;
    }
};

// Approach2(in-built data structure) : O(1) for get and put operations, O(capacity) space complexity
class LRUCache {
public:
    int capacity;
    unordered_map<int, list<pair<int, int>>::iterator> dic;
    list<pair<int, int>> lru;
    
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = dic.find(key);
        
        if (it == dic.end()) {
            return -1;
        }
        
        int value = it->second->second;
        lru.erase(it->second);
        lru.push_front({key, value});
        
        dic.erase(it);
        dic[key] = lru.begin();
        return value;
    }
    
    void put(int key, int value) {
        auto it = dic.find(key);
        
        if (dic.find(key) != dic.end()) {
            lru.erase(it->second);
            dic.erase(it);
        }
        
        lru.push_front({key, value});
        dic[key] = lru.begin();
        
        if (dic.size() > capacity) {
            auto it = dic.find(lru.rbegin()->first);
            dic.erase(it);
            lru.pop_back();
        }
    }

};