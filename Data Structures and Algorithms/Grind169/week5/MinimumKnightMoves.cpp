
// Problem Link : https://leetcode.com/problems/minimum-knight-moves/

// BFS : O((max⁡(∣x∣,∣y∣))^2) time and O((max⁡(∣x∣,∣y∣))^2) space complexity
// Given the coordinate of the target as (x,y), the number of cells covered by the circle that is centered at point (0,0) and reaches the target point is roughly (max⁡(∣x∣,∣y∣))^2
// As for the set, it will contain every elements that we visited, which is (max⁡(∣x∣,∣y∣))^2

class Solution {
public:
    int dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2},
                {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    int minKnightMoves(int a, int b) {
        int ans = 0;

        queue<pair<int,int>> q;

        // - Rather than using the inefficient HashSet, we use the bitmap
        //     otherwise we would run out of time for the test cases.
        // - We create a bitmap that is sufficient to cover all the possible
        //     inputs, according to the description of the problem.
        vector<vector<bool>> vis(607,vector<bool>(607,false));

        q.push({0,0});
        vis[302][302]=true;

        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                auto f = q.front();
                q.pop();
                int x = f.first;
                int y = f.second;
                if(x==a && y==b) return ans;

                for(int i=0;i<8;i++){
                    if(!vis[x+dir[i][0]+302][y+dir[i][1]+302]){
                        vis[x+dir[i][0]+302][y+dir[i][1]+302] = true;
                        q.push({x+dir[i][0],y+dir[i][1]});
                    }
                }
            }
            ans++;
        }
        return -1;
    }
};

// Approach2(Bidirectional BFS)(TLE) : O((max⁡(∣x∣,∣y∣))^2) time and O((max⁡(∣x∣,∣y∣))^2) space complexity
// implementation of bidirectional BFS should be faster than the unidirectional BFS.
// But due to heavy usage of sophisticated data structures, which are inefficient compared to simple arrays.

// Run BFS from both source and target and when you find an intersection,
// just add two distances of intersection point from source and target

class Solution {
public:
    int dir[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2},
                {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    string makeStringFromXY(int x, int y){
        return to_string(x)+","+to_string(y);
    }
    int minKnightMoves(int a, int b) {
        queue<vector<int>> originQueue;
        queue<vector<int>> targetQueue;

        unordered_map<string,int> originDist;
        unordered_map<string,int> targetDist;

        originQueue.push({0,0,0});
        targetQueue.push({a,b,0});

        originDist["0,0"]=0;
        string temp = makeStringFromXY(a,b);
        targetDist[temp]=0;

        vector<int> nextOrigin;
        vector<int> nextTarget;

        string nextOriginXY;
        string nextTargetXY;
        while(1){
            // check if we reach the circle/boundary of target
            auto originf = originQueue.front();
            originQueue.pop();
            string originXY = makeStringFromXY(originf[0],originf[1]);
            if(targetDist.find(originXY)!=targetDist.end()){
                return originf[2]+targetDist[originXY];
            }
            // check if we reach the circle of origin
            auto targetf = targetQueue.front();
            targetQueue.pop();
            string targetXY = makeStringFromXY(targetf[0],targetf[1]);
            if(originDist.find(targetXY)!=originDist.end()){
                return targetf[2]+originDist[targetXY];
            }

            for(int i=0;i<8;i++){
                
                nextOrigin = {originf[0]+dir[i][0],originf[1]+dir[i][1]};
                nextOriginXY = makeStringFromXY(nextOrigin[0],nextOrigin[1]);
                if(originDist.find(nextOriginXY)==originDist.end()){
                    originDist[nextOriginXY]=originf[2]+1;
                    nextOrigin.push_back(originf[2]+1);
                    originQueue.push(nextOrigin);
                }

                nextTarget = {targetf[0]+dir[i][0],targetf[1]+dir[i][1]};
                nextTargetXY = makeStringFromXY(nextTarget[0],nextTarget[1]);
                 if(targetDist.find(nextTargetXY)==targetDist.end()){
                    targetDist[nextTargetXY]=targetf[2]+1;
                    nextTarget.push_back(targetf[2]+1);
                    targetQueue.push(nextTarget);
                }
            }
        }
        return -1;
    }
};

// Approach 3(DFS (Depth-First Search) with Memoization)

// We claim that the target (x,y), its horizontally, vertically, and diagonally symmetric points
// (i.e. (x,−y),(−x,y),(−x,−y)(x, -y)) share the same answer as the target point.

// Due to the symmetry of the board (i.e. from -infinity to +infinity) and the symmetry of the allowed movements,
// we can rest assured that the above claim is correct, without rigid mathematical proof.

// Based on the above insight, we can focus on the first quadrant of the coordinate plane where both xxx and yyy are positive.
// Any target that is outside of the first quadrant, can be shifted to its symmetric point in the first quadrant by taking the absolute value of each coordinate, i.e. (∣x∣,∣y∣).

// For a target that is situated in the first quadrant, though technically we could move in 8 different directions, there are only two directions (i.e. left-down and down-left) that will move us closer to the origin.

// Assume that the function dfs(x, y) returns the minimum steps required to reach the target point (x, y), the idea of DFS can be expressed in the following formula:

// dfs(x,y)=min⁡(dfs(∣x−2∣,∣y−1∣),dfs(∣x−1∣,∣y−2∣))+1

// Indeed, before we reach the immediate neighborhood of the origin, we only need to explore the two left-down directions (with offsets of (−1,−2) and (−2,−1)), since the rest of the directions will deviate further away from the origin.
// The immediate neighborhood of the origin, refers to the points of where the sum of coordinates is less than or equal to 2, i.e. x+y<=2x + y <= 2x+y<=2.
class Solution {
public:
    unordered_map<string,int> memo;

    int dfs(int x,int y){
        string key = to_string(x)+","+to_string(y);
        if(memo.find(key)!=memo.end()) return memo[key];

        if(x+y==0) return 0;
        else if(x+y==2) return 2;
        else{
            int res = min({dfs(abs(x-1),abs(y-2)),dfs(abs(x-2),abs(y-1))})+1;
            memo[key]=res;
            return res;
        }
    }
    int minKnightMoves(int x, int y) {
        return dfs(abs(x),abs(y));
    }
};

// Math : O(1) time and O(1) space complexity
// The crux of the problem is to notice the patterns that emerge when you draw the board.
// The minimum number of moves needed to reach any square
// https://jsfiddle.net/graemian/5qgvr1ba/11/

// 5 4 5 4 5 4 5 6
// 4 3 4 3 4 5 4
// 3 4 3 4 3 4
// 2 3 2 3 4
// 3 2 3 2
// 2 1 4
// 3 2
// 0

#include<cmath>
class Solution {
public:
    int minKnightMoves(int x, int y) {
        // symmetry for axes
        x = abs(x);
        y = abs(y);

        // symmetry for diagonal
        if(x<y){
            int temp = x;
            x=y;
            y=temp;
        }

        if(x==1 && y==0) return 3;
        if(x==2 && y==2) return 4;

        int delta = x-y;
        if (y > delta) {
            return static_cast<int>(delta - 2 * std::floor(static_cast<float>(delta - y) / 3));
        } else {
            return static_cast<int>(delta - 2 * std::floor((delta - y) / 4));
        }

    }
};