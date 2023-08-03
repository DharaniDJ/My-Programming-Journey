
// Problem Link : https://leetcode.com/problems/merge-k-sorted-lists/

// Approach1(Brute Force) : O(nlogn) time and O(n) space complexity
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> res;
        for(auto node : lists){
            while(node){
                res.push_back(node->val);
                node=node->next;
            }
        }

        sort(res.begin(),res.end());

        ListNode* head = new ListNode(-1);
        ListNode* dummy = head;

        for(int node : res){
            dummy->next = new ListNode(node);
            dummy = dummy->next;
        }

        return head->next;
    }
};

// Approach2(Compare one by one) : O(k*n) Almost every selection of node in final linked costs O(k) (k-1 times comparison)time and O(n) complexity
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        int n = lists.size();
        
        ListNode* head = new ListNode(-1);
        ListNode* dummy = head;
        
        while(true){
            int idx = -1;
            int mn = INT_MAX;
            for(int i=0;i<n;i++){
                if(lists[i] && mn > lists[i]->val){
                    mn=lists[i]->val;
                    idx=i;
                }
            }
            if(idx==-1) break;
            dummy->next = new ListNode(mn);
            lists[idx] = lists[idx]->next;
            dummy = dummy->next;
        }
        return head->next;
    }
};

// Appraoch3(using min heap) : O(nlogk) time and O(n) space for creating new LL, O(k) for priority queue
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int,ListNode*>, vector<pair<int,ListNode*>>, greater<pair<int,ListNode*>> > pq;
        for(auto node : lists) if(node) pq.push({node->val,node});

        ListNode* head = new ListNode(-1);
        ListNode* dummy = head;

        while(!pq.empty()){
            auto tp = pq.top();
            pq.pop();
            dummy->next = tp.second;
            dummy = dummy->next;
            auto nxt = tp.second->next;
            if(nxt) pq.push({nxt->val,nxt});
        }
        return head->next;
    }
};

// Approach4(Merge Lists one by one) : O(k*n) time and O(1) space complexity
// for each i, i*(N/k) + (N/k), assuming length of each LinkedLists are same.
class Solution {
public:
    ListNode* merge2Lists(ListNode* list1, ListNode* list2){
        ListNode* head = new ListNode(-1);
        ListNode* dummy = head;
        while(list1 && list2){
            if(list1->val < list2->val){
                dummy->next = list1;
                list1 = list1->next;
            }else{
                dummy->next = list2;
                list2 = list2->next;
            }
            dummy = dummy->next;
        }

        dummy->next = list1 ? list1 : list2;
        dummy = head->next;
        delete head;
        return dummy;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size()==0) return nullptr;
        ListNode* head = lists[0];
        for(int i=1;i<lists.size();i++){
            head = merge2Lists(head,lists[i]);
        }

        return head;
    }
};

// Approach(merge with divide and conquer) : O(nlogk) time and O(1) space complexity
class Solution {
public:
    ListNode* merge2Lists(ListNode* list1, ListNode* list2){
        ListNode* head = new ListNode(-1);
        ListNode* dummy = head;
        while(list1 && list2){
            if(list1->val < list2->val){
                dummy->next = list1;
                list1 = list1->next;
            }else{
                dummy->next = list2;
                list2 = list2->next;
            }
            dummy = dummy->next;
        }

        dummy->next = list1 ? list1 : list2;
        dummy = head->next;
        delete head;
        return dummy;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = lists.size();
        if(n==0) return nullptr;

        int interval = 1;
        while(interval<n){
            for(int i=0;i<(n-interval);i+=(2*interval)){
                lists[i]=merge2Lists(lists[i],lists[i+interval]);
            }
            interval*=2;
        }
        return lists[0];
    }
};