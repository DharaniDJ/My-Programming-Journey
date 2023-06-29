
// Problem Link : https://leetcode.com/problems/asteroid-collision/

// Using stacks : O(n) time and O(n) space complexityt
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        for(int asteroid : asteroids){
            int fl = 1;

            // there will be a collision only if the stack top is positive and the incoming asteroid is negative
            // the reverse condition does not result in a collision
            while(!st.empty() && (st.top()>0 && asteroid<0)){
                // If the top asteroid in the stack is smaller, then it will explode.
                // Hence pop it from the stack, also continue with the next asteroid in the stack.

                if(abs(st.top())<abs(asteroid)){
                    st.pop();
                    continue;
                }
                // If both asteroids are the same size, then both asteroids will explode.
                // Pop the asteroid from the stack; also, we won't push the current asteroid to the stack.
                else if(abs(st.top()) == abs(asteroid)){
                    st.pop();
                }

                // If we reach here, the current asteroid will be destroyed
                // Hence, we should not add it to the stack
                fl = 0;
                break;
            }

            if(fl) st.push(asteroid);
        }

        // Add the asteroids from the stack to the vector in the reverse order.
        vector<int> res(st.size());
        for (int i = res.size() - 1; i >= 0; i--){
            res[i] = st.top();
            st.pop();
        }

        return res;
    }
};