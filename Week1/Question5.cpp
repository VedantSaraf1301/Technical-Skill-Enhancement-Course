/*
Question 5: Optimal Resource Allocation (Bitmask DP)

Given N tasks and N workers (N ≤ 20),
assign each worker exactly one task such that total cost is minimized.

Improve brute force O(N!) to O(N * 2^N) using state compression.
*/

#include <bits/stdc++.h>
using namespace std;

class ResourceAllocation {

public:

    int findMinimumCost(vector<vector<int>>& costMatrix) {

        int totalTasks = costMatrix.size();

        int totalStates = 1 << totalTasks;

        vector<int> minimumCostForMask(totalStates, INT_MAX);

        minimumCostForMask[0] = 0;

        for(int taskMask = 0;
            taskMask < totalStates;
            taskMask++) {

            int workerIndex =
                __builtin_popcount(taskMask);

            for(int taskIndex = 0;
                taskIndex < totalTasks;
                taskIndex++) {

                if((taskMask & (1 << taskIndex)) == 0) {

                    int newMask =
                        taskMask | (1 << taskIndex);

                    minimumCostForMask[newMask] =
                        min(minimumCostForMask[newMask],

                            minimumCostForMask[taskMask]
                            + costMatrix[workerIndex][taskIndex]);
                }
            }
        }

        return minimumCostForMask[totalStates - 1];
    }
};

int main() {

    vector<vector<int>> costMatrix =
    {
        {9, 2, 7},
        {6, 4, 3},
        {5, 8, 1}
    };

    ResourceAllocation obj;

    cout << obj.findMinimumCost(costMatrix);

}