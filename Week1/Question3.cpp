/*
Question 3: Dynamic Network Vulnerability (Tarjan / Bridges)

Given an undirected graph with n nodes,
find all critical connections (bridges).

A connection is critical if removing it disconnects the graph.

Time Complexity Requirement: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

class CriticalConnectionsFinder {

private:

    vector<vector<int>> adjacencyList;
    vector<int> discoveryTime;
    vector<int> lowestReachableTime;
    int currentTime;
    vector<vector<int>> bridgeList;

public:

    vector<vector<int>> findCriticalConnections(
            int totalNodes,
            vector<vector<int>>& connections) {

        // Initialize adjacency list
        adjacencyList.resize(totalNodes);

        for(auto& connection : connections) {

            int sourceNode = connection[0];
            int destinationNode = connection[1];

            adjacencyList[sourceNode].push_back(destinationNode);
            adjacencyList[destinationNode].push_back(sourceNode);
        }

        discoveryTime.assign(totalNodes, 0);
        lowestReachableTime.assign(totalNodes, 0);

        bridgeList.clear();

        currentTime = 0;

        dfs(0, -1);

        return bridgeList;
    }

private:

    void dfs(int currentNode, int parentNode) {

        discoveryTime[currentNode] =
        lowestReachableTime[currentNode] = ++currentTime;

        for(int neighbor : adjacencyList[currentNode]) {

            if(neighbor == parentNode)
                continue;

            if(discoveryTime[neighbor] == 0) {

                dfs(neighbor, currentNode);

                lowestReachableTime[currentNode] =
                    min(lowestReachableTime[currentNode],
                        lowestReachableTime[neighbor]);

                if(lowestReachableTime[neighbor]
                   > discoveryTime[currentNode]) {

                    bridgeList.push_back(
                        {currentNode, neighbor});
                }

            }
            else {

                lowestReachableTime[currentNode] =
                    min(lowestReachableTime[currentNode],
                        discoveryTime[neighbor]);
            }
        }
    }
};

int main() {

    CriticalConnectionsFinder obj;

    int n = 4;

    vector<vector<int>> connections =
    {
        {0,1},
        {1,2},
        {2,0},
        {1,3}
    };

    vector<vector<int>> bridges =
        obj.findCriticalConnections(n, connections);

    for(auto& bridge : bridges) {

        cout << bridge[0] << " - "
             << bridge[1] << endl;
    }
}