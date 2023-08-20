
// Problem Link : https://leetcode.com/problems/odd-even-linked-list/

// Appraoch 1(dummy nodes) : O(n) time and O(1) space complexity
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head || !head->next || !head->next->next) return head;
        
        ListNode* oddNode = new ListNode(-1);
        ListNode* evenNode = new ListNode(-1);
        
        ListNode* cur = head;
        ListNode* oddPtr = oddNode;
        ListNode* evenPtr = evenNode;
        
        int idx = 1;
        while(cur){
            if(idx){
                oddPtr->next = cur;
                cur=cur->next;
                oddPtr = oddPtr->next;
                oddPtr->next = nullptr;
            }else{
                evenPtr->next = cur;
                cur=cur->next;
                evenPtr=evenPtr->next;
                evenPtr->next=nullptr;
            }
            idx = 1-idx;
        }
        
        oddPtr->next = evenNode->next;
        delete oddNode;
        delete evenNode;
        return head;
    }
};

// Without Dummy Node : O(n) time and O(1) space complexity
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {

        if(!head || !head->next || !head->next->next) return head;

        ListNode* oddPtr = head;
        ListNode* evenPtr = head->next;
        ListNode* evenNodeStart = evenPtr;

        while(oddPtr->next && evenPtr->next){
            oddPtr->next = evenPtr->next;
            evenPtr->next = evenPtr->next->next;
            oddPtr = oddPtr->next;
            evenPtr = evenPtr->next;
        }

        oddPtr->next = evenNodeStart;
        return head;
    }
};