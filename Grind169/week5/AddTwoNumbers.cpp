
// Problem Link : https://leetcode.com/problems/add-two-numbers/

// Direct Implementation : O(n) time and O(1) space complexity
// The digits are stored in reverse order, and each of their nodes contains a single digit.
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1) return l2;
        if(!l2) return l1;

        ListNode *temp = new ListNode();
        auto start = temp;
        int carry = 0;
        while(l1 && l2){
            int val = l1->val + l2->val + carry;
            carry = val/10;
            val = val%10;
            start->next = new ListNode(val);
            start = start->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        while(l1){
            int val = l1->val + carry;
            carry = val/10;
            val = val%10;
            start->next = new ListNode(val);
            start = start->next;
            l1 = l1->next;
        }
        while(l2){
            int val = l2->val + carry;
            carry = val/10;
            val = val%10;
            start->next = new ListNode(val);
            start = start->next;
            l2 = l2->next;
        }

        if(carry){
            start->next = new ListNode(carry);
        }
        return temp->next;
    }
};