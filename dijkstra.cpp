// #include <bits/stdc++.h>
// using namespace std;

// class solution {
// public:
//     vector<int> dijkstra(int v, vector<vector<int>> adj[], int s) {
//         vector<bool> explored(v, 0);
//         vector<int> dist(v, INT_MAX);
//         dist[s] = 0;

//         int count = v;
//         while (count--) {
//             int node = -1, value = INT_MAX;
//             for (int i = 0; i < v; i++) {
//                 if (!explored[i] && value > dist[i]) {
//                     node = i;
//                     value = dist[i];
//                 }
//             }

//             if (node == -1) break; 

//             explored[node] = 1;

//             for (int j = 0; j < adj[node].size(); j++) {
//                 int neighbour = adj[node][j][0];
//                 int weight = adj[node][j][1];
//                 if (!explored[neighbour] && dist[node] + weight < dist[neighbour]) {
//                     dist[neighbour] = dist[node] + weight;
//                 }
//             }
//         }

//         return dist;
//     }
// };

// int main() {
//     int v = 5;
//     vector<vector<int>> adj[v];

//     // Sample graph edges (u -> v with weight w)
//     // Graph: 0 -> 1 (2), 0 -> 4 (1), 1 -> 2 (3), 2 -> 3 (6), 4 -> 2 (2), 4 -> 3 (1)
//     adj[0].push_back({1, 2});
//     adj[0].push_back({4, 1});
//     adj[1].push_back({2, 3});
//     adj[2].push_back({3, 6});
//     adj[4].push_back({2, 2});
//     adj[4].push_back({3, 1});

//     solution obj;
//     vector<int> res = obj.dijkstra(v, adj, 0);

//     cout << "Shortest distances from :\n";
//     for (int i = 0; i < v; i++) {
//         cout << "Node " << i << " -> " << res[i] << "\n";
//     }

//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

class solution {
public:
    vector<int> dijkstra(int v, vector<vector<int>> adj[], int s, vector<int> &parent) {
        vector<bool> explored(v, 0);
        vector<int> dist(v, INT_MAX);
        dist[s] = 0;
        parent[s] = -1;

        int count = v;
        while (count--) {
            int node = -1, value = INT_MAX;
            for (int i = 0; i < v; i++) {
                if (!explored[i] && value > dist[i]) {
                    node = i;
                    value = dist[i];
                }
            }

            if (node == -1) break;

            explored[node] = 1;

            for (int j = 0; j < adj[node].size(); j++) {
                int neighbour = adj[node][j][0];
                int weight = adj[node][j][1];
                if (!explored[neighbour] && dist[node] + weight < dist[neighbour]) {
                    dist[neighbour] = dist[node] + weight;
                    parent[neighbour] = node;
                }
            }
        }

        return dist;
    }

    void printPath(int node, vector<int> &parent) {
        if (node == -1) return;
        printPath(parent[node], parent);
        cout << node << " ";
    }
};

int main() {
    int v = 5;
    vector<vector<int>> adj[v];

    // Graph: 0 -> 1 (2), 0 -> 4 (1), 1 -> 2 (3), 2 -> 3 (6), 4 -> 2 (2), 4 -> 3 (1)
    adj[0].push_back({1, 2});
    adj[0].push_back({4, 1});
    adj[1].push_back({2, 3});
    adj[2].push_back({3, 6});
    adj[4].push_back({2, 2});
    adj[4].push_back({3, 1});

    solution obj;
    vector<int> parent(v, -1);
    vector<int> res = obj.dijkstra(v, adj, 0, parent);

    cout << "Shortest distances and paths from node 0:\n";
    for (int i = 0; i < v; i++) {
        cout << "Node " << i << " -> Distance: " << res[i] << ", Path: ";
        obj.printPath(i, parent);
        cout << "\n";
    }

    return 0;
}
