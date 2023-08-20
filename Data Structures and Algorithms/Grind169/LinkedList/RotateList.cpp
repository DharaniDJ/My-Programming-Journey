
// Problem Link : https://leetcode.com/problems/rotate-list/

// Approach 1(Intution) : O(n) time and O(1) space complexity
class Solution {
public:
    int len(ListNode* head){
        int cnt = 0;
        while(head){
            cnt++;
            head=head->next;
        }
        return cnt;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k==0) return head;

        int n = len(head);
        k = k%n;

        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* s = dummy;
        ListNode* f = dummy; 
        for(int i=0;i<k;i++){
            f = f->next;
        }

        while(f->next){
            f=f->next;
            s=s->next;
        }

        f->next = head;
        head = s->next;
        s->next = nullptr;

        return head;
    }
};

// Approach 2(reverse LL) : O(n) time and O(1) space complexity
class Solution {
public:

    ListNode* rev(ListNode* head){
        if(!head) return head;

        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* nxt = head->next;

        while(cur){
            cur->next = prev;
            prev = cur;
            cur = nxt;
            if(nxt) nxt = nxt->next;
        }

        return prev;
    }

    int len(ListNode* head){
        int cnt = 0;
        while(head){
            cnt++;
            head=head->next;
        }
        return cnt;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k==0) return head;

        int n = len(head);
        k = k%n;

        ListNode* dummy = new ListNode(-1);

        dummy->next = head;
        ListNode* f = dummy;
        ListNode* s = dummy;
        ListNode* temp;

        for(int i=0;i<k;i++) f=f->next;
        while(f->next){
            f=f->next;
            s=s->next;
        }

        temp = s->next;
        s->next = nullptr;
        ListNode* head1 = rev(head);
        head->next = rev(temp);
        return rev(head1);

    }
};