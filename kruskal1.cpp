#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int FindParent(int u, vector<int> &parent) {
        if (u == parent[u]) return u;
        return parent[u] = FindParent(parent[u], parent);
    }

    void UnionByRank(int u, int v, vector<int> &parent, vector<int> &rank) {
        int Pu = FindParent(u, parent);
        int Pv = FindParent(v, parent);

        if (Pu != Pv) {
            if (rank[Pu] > rank[Pv]) {
                parent[Pv] = Pu;
            } else if (rank[Pv] > rank[Pu]) {
                parent[Pu] = Pv;
            } else {
                parent[Pv] = Pu;
                rank[Pu]++;
            }
        }
    }

    int spanningTree(int v, vector<pair<int, int>> adj[]) {
        vector<int> parent(v);
        vector<int> rank(v, 0);
        for (int i = 0; i < v; i++) parent[i] = i;

        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> pq;

        for (int i = 0; i < v; i++) {
            for (auto &edge : adj[i]) {
                pq.push({edge.second, {i, edge.first}});
            }
        }

        int cost = 0, edge = 0;
        vector<pair<int, int>> mstEdges;

        while (!pq.empty() && edge < v - 1) {
            int wt = pq.top().first;
            int u = pq.top().second.first;
            int v = pq.top().second.second;
            pq.pop();

            if (FindParent(u, parent) != FindParent(v, parent)) {
                cost += wt;
                mstEdges.push_back({u, v});
                UnionByRank(u, v, parent, rank);
                edge++;
            }
        }

        cout << "Edges in Minimum Spanning Tree:\n";
        for (auto &e : mstEdges) {
            cout << e.first << " - " << e.second << "\n";
        }

        return cost;
    }
};

int main() {
    int V = 5;
    vector<pair<int, int>> adj[V];

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
    int mstWeight = sol.spanningTree(V, adj);

    cout << "Minimum Spanning Tree Cost: " << mstWeight << endl;

    return 0;
}

