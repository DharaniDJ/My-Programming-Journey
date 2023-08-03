
// Problem link: https://leetcode.com/problems/implement-queue-using-stacks/

// Approach1: (Two Stacks) Push - O(n) per operation, Pop - O(1) per operation.
// For every push operation, we first transfer all s1 elements to auxiliary stack s2. 
// Then the newly arrived element is pushed on top of s2 and
// all its elements are popped and pushed to s1.

// class MyQueue {
//     stack<int> Tst;
//     stack<int> Mst;
// public:
//     MyQueue() {
//         while(Tst.empty()==false) Tst.pop();
//         while(Mst.empty()==false) Mst.pop();
//     }
//
//     void push(int x) {
//         while(Mst.empty()==false){
//             Tst.push(Mst.top());
//             Mst.pop();
//         }
//         Mst.push(x);
//         while(Tst.empty()==false){
//             Mst.push(Tst.top());
//             Tst.pop();
//         }
//     }
//
//     int pop() {
//         int tp = Mst.top();
//         Mst.pop();
//         return tp;
//     }
//
//     int peek() {
//         int tp = Mst.top();
//         return tp;
//     }
//
//     bool empty() {
//         return Mst.empty();
//     }
// };

// Approach2: (Two Stacks) Push - O(1) per operation, Pop - Amortized O(1) per operation.
class MyQueue {
    stack<int> Tst; // temp stack
    stack<int> Mst; // main stack
public:
    MyQueue() {
        while(Tst.empty()==false) Tst.pop();
        while(Mst.empty()==false) Mst.pop();
    }

    void push(int x) {
        Tst.push(x);
    }

    int pop() {

        if(Mst.empty()==true){
            while(Tst.empty()==false){
                Mst.push(Tst.top());
                Tst.pop();
            }
        }

        int tp = Mst.top();
        Mst.pop();
        return tp;
    }

    int peek() {
        if(Mst.empty()==true){
            while(Tst.empty()==false){
                Mst.push(Tst.top());
                Tst.pop();
            }
        }

        int tp = Mst.top();
        return tp;
    }

    bool empty() {
        return (Mst.empty() && Tst.empty());
    }
};