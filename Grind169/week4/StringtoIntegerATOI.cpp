
// Problem Link : https://leetcode.com/problems/string-to-integer-atoi

// Approach 1 (Brute Force) : O(n) time and O(1) space complexity
class Solution {
public:
    int myAtoi(string s) {
        int n = s.length();
        int i=0;
        while(i<n && s[i]==' ') i++;
        bool neg = s[i]=='-';
        bool pos = s[i]=='+';
        
        (neg||pos)?i++:i;
        double num = 0;
        while(i<n && s[i]>='0' && s[i]<='9'){
            num = num*10+(s[i]-'0');
            i++;
        }
        
        num = neg?-num:num;
        
        num = (num>INT_MAX)?INT_MAX:num;
        num = (num<INT_MIN)?INT_MIN:num;
        
        return int(num);
    }
};

// Approach 2: Deterministic Finite Automaton (DFA) : O(n) time and O(1) space complexity

enum State { q0, q1, q2, qd };

class StateMachine {
    // Store current state value.
    State currentState;
    // Store result formed and it's sign.
    int result, sign;
    
    // Transition to state q1.
    void toStateQ1(char& ch) {
        sign = (ch == '-') ? -1 : 1;
        currentState = q1;
    }
    
    // Transition to state q2.
    void toStateQ2(int digit) {
        currentState = q2;
        appendDigit(digit);
    }
    
    // Transition to dead state qd.
    void toStateQd() {
        currentState = qd;
    }
    
    // Append digit to result, if out of range return clamped value.
    void appendDigit(int& digit) {
        if ((result > INT_MAX / 10) || 
            (result == INT_MAX / 10 && digit > INT_MAX % 10)) {
            if (sign == 1) {
                // If sign is 1, clamp result to INT_MAX.
                result = INT_MAX;
            } else {
                // If sign is -1, clamp result to INT_MIN.
                result = INT_MIN;
                sign = 1;
            }
            
            // When the 32-bit int range is exceeded, a dead state is reached.
            toStateQd();
        } else {
            // Append current digit to the result. 
            result = result * 10 + digit;
        }
    }
    
public:
    StateMachine(){
        currentState=q0;
        result = 0;
        sign = 1;
    }
    
    // Change state based on current input character.
    void transition(char& ch) {
        if (currentState == q0) {
            // Beginning state of the string (or some whitespaces are skipped).
            if (ch == ' ') {
                // Current character is a whitespaces.
                // We stay in same state. 
                return;
            } else if (ch == '-' || ch == '+') {
                // Current character is a sign.
                toStateQ1(ch);
            } else if (isdigit(ch)) {
                // Current character is a digit.
                toStateQ2(ch - '0');
            } else {
                // Current character is not a space/sign/digit.
                // Reached a dead state.
                toStateQd();
            }
        } else if (currentState == q1 || currentState == q2) {
            // Previous character was a sign or digit.
            if (isdigit(ch)) {
                // Current character is a digit.
                toStateQ2(ch - '0');
            } else {
                // Current character is not a digit.
                // Reached a dead state.
                toStateQd();
            }
        }
    }
    
    // Return the final result formed with it's sign.
    int getInteger() {
        return sign * result;
    }
    
    // Get current state.
    State getState() {
        return currentState;
    }
};

class Solution {
public:
    int myAtoi(string s) {
        StateMachine Q;
        
        for(auto ch : s){
            Q.transition(ch);
        }
        
        return Q.getInteger();
    }
};