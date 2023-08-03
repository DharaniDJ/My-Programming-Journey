
// Problem link: https://leetcode.com/problems/linked-list-cycle/

// Hash set - O(n) time and O(n) space complexity
// class Solution {
// public:
//     bool hasCycle(ListNode *head) {
//         unordered_set<ListNode*> st;
//         while(head){
//             if(st.find(head)!=st.end()) return true;
//             st.insert(head);
//             head=head->next;
//         }
//         return head!=NULL;
//     }
// };


// Floyd's Cycle Finding Algorithm(slow & fast pointer) - O(n) time and O(1) space complexity
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode* slow = head, *fast = head;
        do{
            if(slow->next) slow = slow->next;
            else return false;
            if(fast->next && fast->next->next) fast = fast->next->next;
            else return false;
        }while(slow!=fast);
        return true;
    }
};