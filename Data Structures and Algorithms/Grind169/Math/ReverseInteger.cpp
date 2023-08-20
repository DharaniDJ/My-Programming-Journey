
// Problem Link : https://leetcode.com/problems/reverse-integer

// Pop and Push Digits & Check before Overflow : O(logx) time and O(1) space complexity
class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        int sign = (x<0) ? 1 : 0;

        x = abs(x);
        while(x){
            int rem = x%10;
            if (ans > INT_MAX/10 || (ans == INT_MAX / 10 && rem > 7)) return 0;
            if (ans < INT_MIN/10 || (ans == INT_MIN / 10 && rem < -8)) return 0;
            ans = ans*10+rem;
            x/=10;
        }

        return sign==1 ? -1*ans : ans;
    }
};