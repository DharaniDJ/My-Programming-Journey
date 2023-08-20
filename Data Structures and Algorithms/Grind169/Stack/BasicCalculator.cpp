
// Problem Link : https://leetcode.com/problems/basic-calculator/

// Approach1(Recursion) : O(n) time and O(n) space complexity
class Solution {
public:
    int solve(string &s, int &idx){
        long res = 0;
        long num = 0;
        long sign = 1;
        while(idx<(int)s.size() && s[idx]!=')'){
            if(isdigit(s[idx])) num = num*10 + s[idx] - '0';
            else{
                res+=(num*sign);
                num=0;
                if(s[idx]=='(') res = res+sign*solve(s,++idx);
                else if(!isspace(s[idx])) sign = s[idx]=='+'?1:-1;
            }
            idx++;
        }
        return res+sign*num;
    }

    int calculate(string s) {
        int idx = 0;
        return solve(s,idx);
    }
};

// Approach2(Using stack) : O(n) time and O(n) space complexity
class Solution {
public:
    int calculate(string s) {
        stack<int> stack;
        int operand = 0;
        int result = 0; // For the on-going result
        int sign = 1;  // 1 means positive, -1 means negative

        for (int i = 0; i < s.length(); i++) {
            char ch = s[i];
            if (isdigit(ch)) {
                // Forming operand, since it could be more than one digit
                operand = 10 * operand + (ch - '0');
            } else if (ch == '+') {
                // Evaluate the expression to the left,
                // with result, sign, operand
                result += sign * operand;
                // Save the recently encountered '+' sign
                sign = 1;
                // Reset operand
                operand = 0;
            } else if (ch == '-') {
                result += sign * operand;
                sign = -1;
                operand = 0;
            } else if (ch == '(') {
                // Push the result and sign onto the stack, for later
                // We push the result first, then sign
                stack.push(result);
                stack.push(sign);
                // Reset operand and result, as if new evaluation begins for the new sub-expression
                sign = 1;
                result = 0;
            } else if (ch == ')') {
                // Evaluate the expression to the left
                // with result, sign, and operand
                result += sign * operand;
                // ')' marks the end of an expression within a set of parentheses
                // Its result is multiplied with the sign on top of the stack
                // as stack.pop() is the sign before the parentheses
                result *= stack.top();
                stack.pop();
                // Then add to the next operand on top.
                // as stack.pop() is the result calculated before this parentheses
                // (operand on stack) + (sign on stack * (result from parentheses))
                result += stack.top();
                stack.pop();
                // Reset the operand
                operand = 0;
            }
        }
        return result + (sign * operand);
    }
};