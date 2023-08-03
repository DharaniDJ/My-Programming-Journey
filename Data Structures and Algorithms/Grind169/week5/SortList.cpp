
// Problem Link : https://leetcode.com/problems/sort-list/

// Top-Down MergeSort : O(nlogn) time and O(logn)(recursive stack) space complexity
class Solution {
public:
    ListNode* findMid(ListNode* head){
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow,
    }

    ListNode* mergeList(ListNode* head1, ListNode* head2){
        if(!head1) return head2;
        if(!head2) return head1;

        if(head1->val < head2->val){
            head1->next = mergeList(head1->next,head2);
            return head1;
        }else{
            head2->next = mergeList(head1,head2->next);
            return head2;
        }
    }

    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;

        ListNode* mid = findMid(head);
        ListNode* rightNode = mid->next;
        mid->next = NULL;

        ListNode* head1 = sortList(head);
        ListNode* head2 = sortList(rightNode);
        return mergeList(head1,head2);
    }
};

// Bottom-Up MergeSort : O(nlogn) time and O(1) space complexity

// The Bottom Up approach for merge sort starts by splitting the problem into the smallest subproblem and
// iteratively merge the result to solve the original problem.
class Solution {
public:
    ListNode* tail = new ListNode();
    ListNode* nextSubList = new ListNode();

    int getCount(ListNode* head){
        int cnt = 0;
        while(head){
            cnt++;
            head=head->next;
        }
        return cnt;
    }

    ListNode* split(ListNode* start, int sz){
        ListNode* slow = start;
        ListNode* fast = start->next;
        for(int idx = 1;idx<sz && (slow->next || fast->next);idx++){
            if(fast->next){
                fast = (fast->next->next) ? fast->next->next : fast->next;
            }

            if(slow->next) slow = slow->next;
        }

        ListNode* mid = slow->next;
        nextSubList = fast->next;
        slow->next = nullptr;
        fast->next = nullptr;

        // return start of the second node;
        return mid;
    }

    void merge(ListNode* head1, ListNode* head2){
        ListNode dummy(-1);
        ListNode* newTail = &dummy;

        while(head1 && head2){
            if(head1->val < head2->val){
                newTail->next = head1;
                head1=head1->next;
            }else{
                newTail->next = head2;
                head2=head2->next;
            }
            newTail = newTail->next;
        }

        newTail->next = (head1)? head1 : head2;

        while(newTail->next){
            newTail = newTail->next;
        }

        // link the old tail with the head of merged list
        tail->next = dummy.next;

        // update the old tail with the new tail of merged list
        tail = newTail;
    }

    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;

        int n = getCount(head);
        ListNode* start = head;
        ListNode dummy(-1);
        for(int sz=1; sz<n; sz*=2){
            tail = &dummy;
            while(start){
                if(!start->next){
                    tail->next=start;
                    break;
                }

                ListNode* mid = split(start,sz);
                merge(start,mid);
                start = nextSubList;
            }
            start = dummy.next;
        }
        return dummy.next;
    }
};