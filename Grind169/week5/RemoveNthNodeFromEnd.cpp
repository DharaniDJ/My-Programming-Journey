
// Problem Link : https://leetcode.com/problems/remove-nth-node-from-end-of-list/

// Approach 1(Find size): O(n) time and O(1) space complexity
class Solution {
public:
    int getLLSz(ListNode* head){
        int cnt = 0;
        while(head){
            cnt++;
            head=head->next;
        }
        return cnt;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int sz = getLLSz(head);
        if(!head || !head->next) return nullptr;

        if(n==sz) return head->next;
        ListNode* cur = head;
        int pos = sz-n-1;
        while(pos){
            cur=cur->next;
            pos--;
        }
        cur->next = cur->next->next;
        return head;
    }
};

// Approach 2(one pass) : O(n) time and O(1) space complexity
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        ListNode* start = new ListNode();
        start->next = head;
        
        ListNode* cur = start;
        ListNode* tail = start;
        
        for(int i=0;i<n;i++){
            cur=cur->next;
        }
        
        while(cur->next){
            cur=cur->next;
            tail=tail->next;
        }
        
        tail->next=tail->next->next;
        return start->next;
    }
};