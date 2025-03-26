#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int spanningTree(int v, vector<pair<int, int>> adj[]) {
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        vector<bool> isMST(v, false);
        vector<int> parent(v, -1);
        int cost = 0;

        pq.push({0, {0, -1}}); // Start from node 0

        while (!pq.empty()) {
            int wt = pq.top().first;
            int node = pq.top().second.first;
            int par = pq.top().second.second;
            pq.pop();

            if (!isMST[node]) {
                isMST[node] = true;
                cost += wt;
                parent[node] = par;

                for (auto &edge : adj[node]) {
                    int adjNode = edge.first;
                    int edgeWeight = edge.second;
                    if (!isMST[adjNode]) {
                        pq.push({edgeWeight, {adjNode, node}});
                    }
                }
            }
        }

        // Print the edges in the Minimum Spanning Tree
        cout << "Edges in MST:" << endl;
        for (int i = 1; i < v; i++) { // Start from 1 since 0 has no parent
            cout << parent[i] << " - " << i << endl;
        }

        return cost;
    }
};

int main() {
    int V = 5;
    vector<pair<int, int>> adj[V];

    // Example graph (undirected)
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});
    
    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});
    
    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});
    
    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});
    
    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});
    
    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    Solution sol;
    cout << "Minimum Spanning Tree Cost: " << sol.spanningTree(V, adj) << endl;

    return 0;
}
