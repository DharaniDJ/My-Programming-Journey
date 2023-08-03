
// Problem Link : 

// Approach 1(Reverse the Second Part of the List and Merge Two Sorted Lists): O(n) time and O()
class Solution {
public:

    // Find a Middle Node
    ListNode* getMid(ListNode* head){
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* s = dummy;
        ListNode* f = dummy;

        while(f && f->next){
            s=s->next;
            f=f->next->next;
        }

        return s;
    }

    // Reverse the List(Recursively)
    ListNode* reverseLLRecursive(ListNode* head){
        if(!head || !head->next) return head;

        ListNode* tail = reverseLLRecursive(head->next);
        ListNode* temp = head->next;
        head->next = nullptr;
        temp->next = head;
        return tail;
    }

    // Reverse the List(Iterative)
    ListNode* reverseLLIterative(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* nxt;

        while(head){
            nxt = head->next;
            head->next = prev;
            prev=head;
            head=nxt;
        }
        return prev;
    }

    void reorderList(ListNode* head) {
        if(!head || !head->next) return;

        ListNode* mid = getMid(head);
        ListNode* temp = mid->next;
        mid->next = nullptr;

        // Reverse the Second Part of the List
        // temp = reverseLLRecursive(temp);
        temp = reverseLLIterative(temp);

        ListNode* head1 = head;
        ListNode* head2 = temp;

        ListNode* dummy = new ListNode(-1);
        ListNode* res = dummy;

        // similar to Merge Two Sorted Lists
        while(head1 && head2){
            dummy->next = head1;
            head1=head1->next;
            dummy = dummy->next;
            dummy->next=nullptr;

            dummy->next = head2;
            head2 = head2->next;
            dummy = dummy->next;
            dummy->next = nullptr;
        }
        if(head1){
            head1->next=nullptr;
            dummy->next=head1;
        }

        head=res->next;
    }
};