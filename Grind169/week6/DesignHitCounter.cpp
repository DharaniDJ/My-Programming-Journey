
// Problem Link : https://leetcode.com/problems/design-hit-counter/

// Approach1(queue)
// Time Complexity: O(1) for hit and getHits can take amortized O(1)
// Space Complexity : O(n) for getHits

// However, we must notice that each timestamp is processed only twice
// (first while adding the timestamp in the queue in hit method and second while removing the timestamp from the queue in the getHits method).

// Hence if the total number of timestamps encountered throughout is N, the overall time taken by getHits method is O(N).
// This results in an amortized time complexity of O(1) for a single call to getHits method.
class HitCounter {
    int timeRn;
    queue<int> timeStamp;
public:
    HitCounter() {
        timeRn=0;
    }
    
    void hit(int timestamp) {
        timeStamp.push(timestamp);
        timeRn=timestamp;
    }
    
    int getHits(int timestamp) {
        
        timeRn=timestamp;

        while(!timeStamp.empty()){
            if(timeStamp.front()+300 <= timeRn) timeStamp.pop();
            else{
                break;
            }
        }

        return timeStamp.size();
    }
};

// Approach2(Deque with pairs) :
// Time Complexity: O(1) for hit and getHits can take amortized O(1)
// Space Complexity : O(n) for getHits
// However, in the case of repetitions, the space required for storing those k values O(1).
class HitCounter {
    int total;
    queue<pair<int,int>> timeStamp;
public:
    HitCounter() {
        total=0;
    }
    
    void hit(int timestamp) {
        if(timeStamp.empty() || timeStamp.back().first!=timestamp) timeStamp.push({timestamp,1});
        else{
            timeStamp.back().second++;
        }
        total++;
    }
    
    int getHits(int timestamp) {
        
        while(!timeStamp.empty()){
            int diff = timestamp - timeStamp.front().first;
            if(diff>=300) {
                total-=timeStamp.front().second;
                timeStamp.pop();
            }
            else{
                break;
            }
        }

        return total;
    }
};