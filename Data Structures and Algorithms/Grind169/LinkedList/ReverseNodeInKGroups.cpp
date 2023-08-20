
// Problem Link : https://leetcode.com/problems/reverse-nodes-in-k-group/

// Approach1(Recursion) : O(n) time and O(n/k) space complexity

class Solution {
    ListNode* reverseLL(ListNode* head, int k){
        ListNode* newHead = nullptr;
        ListNode* ptr = head;
        
        while(k--){
            ListNode* nextNode = ptr->next;
            ptr->next = newHead;
            newHead = ptr;
            ptr = nextNode;
        }
        
        return newHead;
        
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        int cnt = 0;
        ListNode* ptr = head;
        
        while(cnt<k && ptr){
            ptr = ptr->next;
            cnt++;
        }
        
        if(cnt==k){
            ListNode* reversedHead = reverseLL(head,k);
            head->next = reverseKGroup(ptr,k);
            return reversedHead;
        }
        
        return head;
    }
};

// Approach2(Iterative) : O(n) time and O(1) space complexity
class Solution {
    int len(ListNode* head){
        int cnt = 0;
        while(head){
            cnt++;
            head = head->next;
        }
        return cnt;
    }

public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        if(!head || !head->next) return head;
        int n = len(head);
        
        ListNode* dummy = new ListNode(-1);
        
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* cur;
        ListNode* nex;
        while(n >= k){
            cur = pre->next;
            nex = cur->next;
            for(int i=1;i<k;i++){
                cur->next = nex->next;
                nex->next = pre->next;
                pre->next=nex;
                nex=cur->neaxt;
            }
            pre = cur;
            n-=k;
        }
        return dummy->next;
    }
};