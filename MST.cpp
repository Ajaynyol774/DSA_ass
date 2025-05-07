#include <bits/stdc++.h>
using namespace std;
 
// Define an edge as a pair of integers (u, v) and weight w
typedef pair<int, int> edge;  // (u, v)
 
class Graph {
private:
    vector<pair<int, edge>> G; // List of edges in the graph (weight, (u, v))
    vector<edge> T;           // MST edges for Kruskal's Algorithm
    int *parent;
    int *rank;
    int V; // Number of vertices
 
public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    int find(int i);
    void unionSets(int u, int v);
    void kruskal();
    void printMST_Kruskal();
    void prim(int start);
    void printMST_Prim();
};
 
// Constructor to initialize parent and rank arrays
Graph::Graph(int V) {
    this->V = V;
    parent = new int[V];
    rank = new int[V];
 
    // Initially, each node is its own parent, and the rank is 0
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
 
// Function to add an edge to the graph
void Graph::addEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));  // Push the edge to the edge list
}
 
// Find function for Disjoint Set (with path compression)
int Graph::find(int i) {
    if (i != parent[i]) {
        parent[i] = find(parent[i]);  // Path compression
    }
    return parent[i];
}
 
// Union function for Disjoint Set (with union by rank)
void Graph::unionSets(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
 
    if (root_u != root_v) {
        // Union by rank
        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}
 
// Kruskal's Algorithm to find MST
void Graph::kruskal() {
    sort(G.begin(), G.end()); // Sort edges by weight
 
    for (auto e : G) {
        int u = e.second.first;
        int v = e.second.second;
 
        // Check if including this edge forms a cycle
        if (find(u) != find(v)) {
            T.push_back(e.second);  // Add edge to MST
            unionSets(u, v);        // Union the sets
        }
    }
}
 
// Print the edges in the MST (for Kruskal's)
void Graph::printMST_Kruskal() {
    cout << "Edges in the Minimum Spanning Tree (Kruskal's):" << endl;
    int totalWeight = 0;
    for (auto e : T) {
        cout << e.first << " - " << e.second << endl;
        // Find the corresponding weight in the list
        for (auto g : G) {
            if ((g.second.first == e.first && g.second.second == e.second) ||
                (g.second.first == e.second && g.second.second == e.first)) {
                totalWeight += g.first;  // Add the weight of the edge
                break;
            }
        }
    }
    cout << "Total weight of MST (Kruskal's): " << totalWeight << endl;
}
 
// Prim's Algorithm to find MST starting from a given vertex (start)
void Graph::prim(int start) {
    vector<int> key(V, INT_MAX);  // Stores the minimum edge weight to each vertex
    vector<int> parent(V, -1);    // Stores the parent vertex in the MST
    vector<bool> inMST(V, false); // To track vertices included in the MST
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});  // Start from vertex `start`, key = 0
    key[start] = 0;
 
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
 
        // If vertex u is already in the MST, continue
        if (inMST[u]) continue;
 
        inMST[u] = true;
 
        // Update adjacent vertices
        for (auto e : G) {
            int v = e.second.first == u ? e.second.second : e.second.first;
            int weight = e.first;
 
            // If the vertex v is not in MST and weight of edge (u, v) is smaller than the current key of v
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
 
    // Store the MST edges for Prim's
    T.clear();
    for (int i = 0; i < V; i++) {
        if (parent[i] != -1) {
            T.push_back({parent[i], i});
        }
    }
}
 
// Print the edges in the MST (for Prim's)
void Graph::printMST_Prim() {
    cout << "Edges in the Minimum Spanning Tree (Prim's):" << endl;
    int totalWeight = 0;
    for (auto e : T) {
        cout << e.first << " - " << e.second << endl;
        // Find the corresponding weight in the list
        for (auto g : G) {
            if ((g.second.first == e.first && g.second.second == e.second) ||
                (g.second.first == e.second && g.second.second == e.first)) {
                totalWeight += g.first;  // Add the weight of the edge
                break;
            }
        }
    }
    cout << "Total weight of MST (Prim's): " << totalWeight << endl;
}
 
int main() {
    Graph g(4);  // Create a graph with 4 vertices
 
    // Add edges to the graph
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
 
    // Apply Kruskal's algorithm
    g.kruskal();
    // Print the MST using Kruskal's algorithm
    g.printMST_Kruskal();
 
    // Apply Prim's algorithm starting from vertex 0
    g.prim(0);
    // Print the MST using Prim's algorithm
    g.printMST_Prim();
 
    return 0;
}