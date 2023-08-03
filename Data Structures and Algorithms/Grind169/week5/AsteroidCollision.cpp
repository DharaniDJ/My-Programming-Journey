
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

// 2 pointer : O(n) time and O(1) space complexity
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        int j = -1;
        
        for(int i=0;i<n;){
            int a = asteroids[i];

            if(j==-1 || a>0 || asteroids[j]<0){
                j++;
                asteroids[j]=a;
                i++;
            }
            // asteroids[i] is negative but its sum with last asteroid at j is positive so we just ignore the currently read asterod at i.
            else if(asteroids[j]+a>0){
                i++;
            }
            // two equal asteroid in oposite direction collide and nothing is left, so ith one is not kept, and jth one already kept is removed.
            else if(asteroids[j]+a==0){
                j--;
                i++;
            }
            // asteroids[i] is negative and its sum with last asteroid at j is also negative so we are sure the jth astroid we kept needs to be removed but, not sure about if ith one should be kept here, so we continue decrementing j, till we find the correct position to keep the current ith aestroid.
            else if(asteroids[j]+a < 0){
                j--;
            }
        }
        vector<int> res(asteroids.begin(),asteroids.begin()+j+1);
        return res;
    }
};