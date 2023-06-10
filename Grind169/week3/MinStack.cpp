
// Problem Link : https://leetcode.com/problems/min-stack/

// Approach 1 (Stack of pair) : O(1) time for all operations and O(n) space complexity
class MinStack {
stack<pair<int,int>> st;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        if(st.empty()){
            st.push({val,val});
        }else{
            int mn = val<st.top().second ? val : st.top().second;
            st.push({val,mn});
        }
        return;
    }
    
    void pop() {
        st.pop();
        return;
    }
    
    int top() {
        auto it = st.top();
        return it.first;
    }
    
    int getMin() {
        auto it = st.top();
        return it.second;
    }
};

// Approach 2 (2 stacks) : O(1) time for all operations and O(n) space complexity
class MinStack {
    stack<int> st;
    stack<int> mnSt;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);
        if(mnSt.empty() || mnSt.top()>=val) mnSt.push(val);
    }
    
    void pop() {
        int val = st.top();
        st.pop();
        if(mnSt.top()==val) mnSt.pop();
        return;
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return mnSt.top();
    }
};
// Approach 2 (improved 2 stacks) : O(1) time for all operations and O(n) space complexity
class MinStack {
    stack<int> st;
    stack<pair<int,int>> mnSt;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        st.push(val);
        
        if(mnSt.empty() || mnSt.top().first>val){
            mnSt.push({val,1});
        }else if(mnSt.top().first==val){
            auto top = mnSt.top();
            mnSt.pop();
            top.second++;
            mnSt.push(top);
        }
    }
    
    void pop() {
        int val = st.top();
        st.pop();
        if(mnSt.top().first==val){
            auto top = mnSt.top();
            mnSt.pop();
            top.second--;
            if(top.second) mnSt.push(top);
        }
        return;
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return mnSt.top().first;
    }
};

// Approach 3 (LinkedList) : O(1) time for all operations and O(n) space complexity
class node{
public:
    int val;
    int mn;
    node* next;
    node(int val, int mn, node* next){
        this->val=val;
        this->mn=mn;
        this->next = next;
    }
};

class MinStack {
    node* head;
public:
    MinStack() {
        head=NULL;
    }
    
    void push(int val) {
        if(!head){
            head=new node(val,val,NULL);
        }else{
            head = new node(val,min(val,head->mn),head);
        }
    }
    
    void pop() {
        head = head->next;
        return;
    }
    
    int top() {
        int val = head->val;
        return val;
    }
    
    int getMin() {
        int mn = head->mn;
        return mn;
    }
};

// Approach 4 (1 stack and 1 min variable) : O(1) time for all operations and O(n) space complexity
#define ll long long
class MinStack {
private:
    stack<ll> s;
    ll mn;
    
public:
    MinStack() {
        while(!s.empty()) s.pop();
        mn=INT_MAX;
    }
    
    void push(ll val) {
        if (s.empty()) {
          mn = val;
          s.push(val);
        } else {
          if (val < mn) {
            s.push(2 *val*1LL - mn);
            mn = val;
          } else {
            s.push(val);
          }
        }
     }
    
    void pop() {
        if(!s.empty()){
            if(s.top()<mn){
                ll val = 2*mn-s.top();
                mn = val;
                s.pop();
            }else{
                s.pop();
            }
        }
    }
    
    int top() {
        if(!s.empty()){
            if(s.top()<mn){
                return mn;
            }else{
                return s.top();
            }
        }
        return -1;
    }
    
    int getMin() {
        return mn;
    }
};
