
// Problem link: https://leetcode.com/problems/merge-two-sorted-lists/

// Recursion - O(n+m) time and O(n+m) space complexity
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1) return list2;
        if(!list2) return list1;

        if(list1->val > list2->val){
            list2->next = mergeTwoLists(list1,list2->next);
            return list2;
        }else{
            list1->next = mergeTwoLists(list1->next,list2);
            return list1;
        }
    }
};

// Iteration - O(n+m) time and O(1) space complexity
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(!list1) return list2;
        if(!list2) return list1;

        ListNode* head;

        // point list1 and list2 with smallest and largest respectively
        if(list1->val > list2->val){
            head=list2;
            list2=list2->next;
        }else{
            head=list1;
            list1=list1->next;
        }

        ListNode* prev = head;

        while(list1 && list2){
            if(list1->val > list2->val){
                prev->next=list2;
                prev=prev->next;
                list2=list2->next;
            }else{
                prev->next=list1;
                prev=prev->next;
                list1=list1->next;
            }
        }
        if(list1) prev->next=list1;
        if(list2) prev->next=list2;
        return head;
    }
};