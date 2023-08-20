
// Problem Link : https://leetcode.com/problems/find-median-from-data-stream

// Approach1(BruteForce) :
// time complexity : O(nlogn) + O(1)(amortized for a container with an efficient resizing scheme.)
// space complexity : O(n) for storing in a container
class MedianFinder {
private:
    vector<int> arr;
public:
    MedianFinder() {

    }

    void addNum(int num) {
        arr.push_back(num);
    }

    double findMedian() {
        sort(begin(arr),end(arr));
        int n = arr.size();

        return (n&1 ? (double)arr[n/2] : (arr[n/2]+arr[n/2 - 1])/2.0);
    }
};

// Approach2(Insertion sort):
// time complexity : O(nlogn)(Binary search) + O(n)(inserion)
// space complexity : O(n) for storing in a container

// Keeping our input container always sorted
class MedianFinder {
private:
    vector<int> arr; // resizable array
public:
    MedianFinder() {

    }

    void addNum(int num) {
        if(arr.empty()){
            arr.push_back(num);
        }else{
            // binary search and insertion combined
            arr.insert(lower_bound(arr.begin(),arr.end(),num),num);
        }
    }

    double findMedian() {
        int n = arr.size();
        return (n&1 ? (double)arr[n/2] : (arr[n/2]+arr[n/2 - 1])/2.0);
    }
};

// Approach3(Using heaps):
// addNum : O(logn) time and O(n) space complexity
// findMedian : O(1) time and O(1) space complexity

// A max-heap to store the smaller half of the input numbers
// A min-heap to store the larger half of the input numbers

class MedianFinder {
private:
    priority_queue<int> mxh;
    priority_queue<int,vector<int>, greater<int>> mnh;
public:
    MedianFinder() {

    }

    void addNum(int num) {
        int n = mxh.size();
        int m = mnh.size();

        if(n==0){
            mxh.push(num);
            return;
        }

        int mx = mxh.top();

        if(num>mx){
            mnh.push(num);
            m++; // increase size of min heap
        }else{
            mxh.push(num);
            n++; // increase size of max heap
        }

        if(n>m+1){
            mnh.push(mxh.top());
            mxh.pop();
        }else if(m>n){
            mxh.push(mnh.top());
            mnh.pop();
        }

        return;
    }

    double findMedian() {
        int n = mxh.size();
        int m = mnh.size();

        return n==m ? (mxh.top()+mnh.top())/2.0:(double)mxh.top();
    }
};

// -------------------------- OTHER APPROACHES --------------------------

// Approach4(Multiset and Two Pointers)
// multiset emulates Self-balancing BST behavior
// The only problem remains keeping track of the median elements. That is easily solved with pointers!
// We maintain two pointers: one for the lower median element and the other for the higher median element.
class MedianFinder {
private:
    multiset<int> data;
    multiset<int>::iterator lo_median, hi_median;
public:
    MedianFinder()
        : lo_median(data.end())
        , hi_median(data.end())
    {
    }
    
    void addNum(int num) {
        const size_t n = data.size();
        data.insert(num);
        
        if(n==0){
            // no elements before, one element now
            lo_median = data.begin();
            hi_median = data.begin();
        }else if(n&1){
            // odd size before (i.e. lo == hi), even size now (i.e. hi = lo + 1)
            if(num < *lo_median){
                lo_median--;
            }else{
                hi_median++;
            }
        }else{
            // even size before (i.e. hi = lo + 1), odd size now (i.e. lo == hi)
            if (num > *lo_median && num < *hi_median) {
                lo_median++;                    // num in between lo and hi
                hi_median--;
            }
            else if (num >= *hi_median)         // num inserted after hi
                lo_median++;
            else                                // num <= lo < hi
                lo_median = --hi_median;        // insertion at end of equal range spoils lo
        
        }
    }
    
    double findMedian() {
        return ((double) *lo_median + *hi_median) * 0.5;
    }
};

// Approach5(Using Buckets)
class MedianFinder {

/* The idea of dividing existing numbers into several ranges:

   Say we already have 10k numbers in vector,
   each time adding a number requires sorting all 10k numbers, which is slow.

   To optimize, we can store 10k numbers in several (say 10) vectors,
   and nums in each vector are sorted.

   Then each time we add a number, just need to find one vector with correct range,
   insert the number and sort this vector only. Since its size is relatively small, it's fast.

   When we have a vector's size greater than a threshold, just split it into two halfs.

*/

public:
    vector<vector<int>*> raid; // store all ranges
    int total_size;

    MedianFinder() {
        total_size=0;
        raid.push_back(new vector<int> ());
    }

    void addNum(int num) {
        vector<int>* correctRange=NULL;
        int targetIndex;

        // find the correct range to insert given num
        for (int i=0; i<raid.size(); i++)
            if ( raid.size()==1 ||
                 (i==0 && num<=raid[i]->back()) ||
                 (i==raid.size()-1 && num>=raid[i]->at(0)) ||
                 (raid[i]->at(0)<=num && num<=raid[i]->back()) ||
                 (num > raid[i]->back() && num < raid[i+1]->front()) )
            {
                correctRange = raid[i];
                targetIndex = i;
                break;
            }

        // put num at back of correct range, and sort it to keep increasing sequence
        total_size++;
        correctRange->push_back(num);
        sort(correctRange->begin(), correctRange->end());

        // if current range's size > threshold, split it into two halfs and add them back to this.raid
        const int max_size = 30;
        int len = correctRange->size();
        if (len > max_size) {
            vector<int> *half1 = new vector<int>(correctRange->begin(), correctRange->begin()+len/2);
            vector<int> *half2 = new vector<int>(correctRange->begin()+len/2, correctRange->end());

            delete correctRange;
            raid[targetIndex]=half2;
            raid.insert(raid.begin() + targetIndex, half1);
        }

    }

    // iterate thru all ranges in this.raid to find median value
    double findMedian() {
        if (total_size==0)
            return 0;

        int mid1 = total_size/2;
        int mid2 = mid1 + 1;

        int leftCount=0;
        double first, second;
        for (auto r : raid) {
            if (leftCount<mid1 && mid1<=leftCount+r->size())
                first = r->at(mid1 - leftCount - 1);

            if (leftCount<mid2 && mid2<=leftCount+r->size()) {
                second = r->at(mid2 - leftCount - 1);
                break;
            }
            leftCount += r->size();
        }

        if (total_size % 2)
            return second;
        else
            return (first + second)/2;
    }
};

// Approach6(reservior sampling)
// https://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers/10693752#10693752