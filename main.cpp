#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

// Structure to represent a graph edge
struct Edge {
    int destination;
    int weight;
};

// Function to implement Dijkstra's Algorithm
void dijkstra(int V, vector<vector<Edge>>& graph, int source) {
    // Create a priority queue to store vertices that are being processed
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Vector to store the shortest distance from source to each vertex
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    pq.push({0, source}); // Push the source vertex with distance 0

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Loop over all adjacent vertices of u
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // If the distance to v through u is shorter, update it
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Output the shortest distances
    cout << "Vertex\t\tDistance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    }
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> graph(V);

    // Adding edges to the graph
    graph[0].push_back({1, 10});
    graph[0].push_back({2, 5});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({1, 3});
    graph[2].push_back({3, 9});
    graph[2].push_back({4, 2});
    graph[3].push_back({4, 4});
    graph[4].push_back({0, 7});
    graph[4].push_back({3, 6});

    int source = 0; // Starting vertex
    dijkstra(V, graph, source);

    return 0;
}