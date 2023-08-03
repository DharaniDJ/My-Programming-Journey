
// Problem Link : https://leetcode.com/problems/basic-calculator-ii/

// Approach1(Using Stack) : O(n) time and O(n) space complexity
class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        if(n == 0 ) return 0;
        stack<int> st;

        int currentNumber = 0;
        char operation = '+';
        for(int i=0;i<n;i++){
            char curChar = s[i];
            if(isdigit(curChar)){
                currentNumber = currentNumber*10 + (curChar-'0');
            }
            if(!isdigit(curChar) && !iswspace(curChar) || i==n-1){
                // Addition (+) or Subtraction (-): We must evaluate the expression later based on the next operation.
                // So, we must store the currentNumber to be used later.
                if(operation=='-'){
                    st.push(-currentNumber);
                }else if(operation=='+'){
                    st.push(currentNumber);

                // Multiplication (*) or Division (/): Pop the top values from the stack and evaluate the current expression.
                }else if(operation=='*'){
                    int prevNumber = st.top();
                    st.pop();
                    st.push(prevNumber*currentNumber);
                }else if(operation=='/'){
                    int prevNumber = st.top();
                    st.pop();
                    st.push(prevNumber/currentNumber);
                }
                operation=curChar;
                currentNumber = 0;
            }
        }

        int res = 0;
        while(!st.empty()){
            res+=st.top();
            st.pop();
        }

        return res;
    }
};

// Approach2(space optimized) : O(n) time and O(1) space
// In the previous approach, we used a stack to track the values of the evaluated expressions. In the end, we pop all the values from the stack and add to the result. 
// Instead of that, we could add the values to the result beforehand and keep track of the last calculated number

// op1      +       op2     -       op3     *       op4
//lastN  operation curN   curChar
//                 lastN operation curChar(curN)
//                 lastN operation curN   curChar
//                                 lastN operation curChar(curN)


// when curChar points to '-', operation is '+', lastNumber = op1. Since operation == '+' add lastNumber to result and update lastNumber with +/-(currentNumber)


class Solution {
public:
    int calculate(string s) {
        int n = s.size();
        if(n == 0 ) return 0;

        int currentNumber = 0, lastNumber = 0;
        int res = 0;

        char operation = '+';
        for(int i=0;i<n;i++){
            char curChar = s[i];

            if(isdigit(curChar)){
                currentNumber = (currentNumber * 10) + (curChar-'0');
            }

            if(!isdigit(curChar) && !iswspace(curChar) || i==n-1){
                if(operation=='+' || operation=='-'){
                    res += lastNumber;
                    lastNumber = (operation=='+') ? currentNumber : -currentNumber;
                }else if(operation=='*'){
                    lastNumber = lastNumber*currentNumber;
                }else if(operation=='/'){
                    lastNumber = lastNumber/currentNumber;
                }
                operation=curChar;
                currentNumber = 0;
            }
        }

        res += lastNumber;
        return res;
    }
};