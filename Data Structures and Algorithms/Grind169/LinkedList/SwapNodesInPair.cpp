
// Problem Link : https://leetcode.com/problems/swap-nodes-in-pairs/

// Approach 1(Recursion) : O(n) time and O(n) space complexity
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;

        ListNode* t = swapPairs(head->next->next);

        ListNode* temp = head;
        head = head->next;
        temp->next=t;
        head->next = temp;

        return head;
    }
};

// Appraoch 2(Iterative) : O(n) time and O(1) space complexity

// We break the linked list into pairs by jumping in steps of two.
// The only difference is, unlike recursion, we swap the nodes on the go.
// After swapping a pair of nodes, say A and B, we need to link the node B to the node that was right before A.
// To establish this linkage we save the previous node of node A in prevNode.

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

        if(!head || !head->next) return head;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* prevNode = dummy;

        while(head && head->next){
            ListNode* firstNode = head;
            ListNode* secondNode = head->next;

            // swapping
            prevNode->next = secondNode;
            firstNode->next = secondNode->next;
            secondNode->next = firstNode;

            prevNode = firstNode;
            head = prevNode->next;
        }

        return dummy->next;
    }
};