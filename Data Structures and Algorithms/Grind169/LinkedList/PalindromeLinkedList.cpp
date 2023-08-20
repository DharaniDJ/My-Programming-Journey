
// Problem Link : https://leetcode.com/problems/palindrome-linked-list/

// Approach 1 (Copy into Array List and then Use Two Pointer Technique) : O(n) time and O(n) space complexity
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> res;
        ListNode* cur = head;
        while(cur){
            res.push_back(cur->val);
            cur=cur->next;
        }
        int i=0, j=res.size()-1;
        while(j>i){
            if(res[i]!=res[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};

// Approach 2 Recursive (Advanced) : O(n) time and O(n) space complexity
class Solution {
private:
    ListNode* frontPointer;
public:
    bool recursiveCheck(ListNode* head){
        if(head){
            if(!recursiveCheck(head->next)) return false;
            if(frontPointer->val != head->val) return false;
            frontPointer=frontPointer->next;
        }
        return true;
    }
    bool isPalindrome(ListNode* head) {
        frontPointer = head;
        return recursiveCheck(head);
    }
};

// Approach 3 (Reverse 2nd half and traverse)
class Solution {
public:
    ListNode* reverse(ListNode* head){
        if(!head || !head->next) return head;
        ListNode* temp = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return temp;
    }
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* slow = head, *fast = head;
        while(fast->next && fast->next->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        slow->next = reverse(slow->next);
        fast = slow->next;
        slow = head;
        while(fast){
            if(slow->val != fast->val) return false;
            slow=slow->next;
            fast=fast->next;
        }
        return true;
    }
};