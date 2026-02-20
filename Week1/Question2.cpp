/*
Question 2: Streaming Max Analytics (Monotonic Queue)

Given a stream of latency values and window size k,
calculate maximum latency in each sliding window.

Each incoming data point must be processed in amortized O(1).
*/

#include <bits/stdc++.h>
using namespace std;

class StreamingMax {

public:

    vector<int> findMaxInSlidingWindow(vector<int>& latencyValues, int windowSize) {

        deque<int> indexDeque;

        int totalElements = latencyValues.size();

        vector<int> maximumValues(totalElements - windowSize + 1);

        int resultIndex = 0;

        for(int currentIndex = 0; currentIndex < totalElements; currentIndex++) {

            // Remove indices outside window
            if(!indexDeque.empty()
               && indexDeque.front() <= currentIndex - windowSize) {

                indexDeque.pop_front();
            }

            // Maintain decreasing order
            while(!indexDeque.empty()
                  && latencyValues[indexDeque.back()]
                  <= latencyValues[currentIndex]) {

                indexDeque.pop_back();
            }

            indexDeque.push_back(currentIndex);

            if(currentIndex >= windowSize - 1) {

                maximumValues[resultIndex++] =
                    latencyValues[indexDeque.front()];
            }
        }

        return maximumValues;
    }
};

int main() {

    StreamingMax obj;

    vector<int> latency = {1, 3, -1, -3, 5, 3, 6, 7};

    int k = 3;

    vector<int> result = obj.findMaxInSlidingWindow(latency, k);

    for(int x : result)
        cout << x << " ";

}