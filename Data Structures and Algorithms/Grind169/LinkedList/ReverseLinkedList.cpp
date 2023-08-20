
// Problem Link: https://leetcode.com/problems/reverse-linked-list/

// Recursion: O(n) time and O(n) space complexity
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* temp = reverseList(head->next);
        head->next->next = head;
        head->next =NULL;
        return temp;
    }
};

// iteration: O(n) time and O(1) space complexity
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* cur = head;
        ListNode* prev = NULL;
        ListNode* temp;
        while(cur){
            temp = cur->next;
            cur->next=prev;
            prev=cur;
            cur=temp;
        }
        return prev;
    }
};