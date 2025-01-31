#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Structure to represent a graph edge
struct Edge {
    int destination;
    int weight;
};

// Function to implement Dijkstra's Algorithm with Path Reconstruction
void dijkstra(int V, vector<vector<Edge>>& graph, int source) {
    // Create a priority queue to store vertices that are being processed
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Vector to store the shortest distance from source to each vertex
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // To store the parent of each vertex for path reconstruction
    vector<int> parent(V, -1);

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
                parent[v] = u; // Set u as the parent of v
                pq.push({dist[v], v});
            }
        }
    }

    // Output the shortest distances and reconstructed paths
    cout << "\nVertex\t\tDistance from Source\t\tPath" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << "\t\t";
        
        if (dist[i] == INT_MAX) {
            cout << "No path";
        } else {
            stack<int> path;
            for (int v = i; v != -1; v = parent[v]) {
                path.push(v);
            }
            while (!path.empty()) {
                cout << path.top() << " ";
                path.pop();
            }
        }
        cout << endl;
    }
}

// Function to add edges to the graph
void addEdge(vector<vector<Edge>>& graph, int u, int v, int weight) {
    graph[u].push_back({v, weight});
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<Edge>> graph(V);

    // Input graph edges
    cout << "Enter the edges in the format: u v weight" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        addEdge(graph, u, v, weight);
    }

    int numSources;
    cout << "Enter the number of source vertices: ";
    cin >> numSources;

    // Input multiple source vertices and run Dijkstra for each
    for (int i = 0; i < numSources; ++i) {
        int source;
        cout << "Enter source vertex " << i + 1 << ": ";
        cin >> source;

        cout << "\nRunning Dijkstra for Source Vertex " << source << ":\n";
        dijkstra(V, graph, source);
    }

    return 0;
}