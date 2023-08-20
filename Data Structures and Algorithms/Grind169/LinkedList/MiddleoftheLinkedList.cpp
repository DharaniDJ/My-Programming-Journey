
// Problem Link: https://leetcode.com/problems/middle-of-the-linked-list/

// Brute force(2 traversals): O(n) time and O(1) space complexity
class Solution {
public:

    int length(ListNode* cur){
        int cnt = 0;
        ListNode* head = cur;
        while(head){
            cnt++;
            head=head->next;
        }
        return cnt;
    }

    ListNode* middleNode(ListNode* head) {
        int l = length(head);
        int k = l/2;
        while(k--){
            head=head->next;
        }
        return head;
    }
};

// Slow and Fast pointer(one time traversal): O(n) time andd O(1) space complexity
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* s = head;
        ListNode* f = head;
        while(f && f->next){
            s=s->next;
            f=f->next->next;
        }
        return s;
    }
};

