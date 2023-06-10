#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

// Structure to represent a graph edge
struct Edge
{
    int weight;
    int dest;

    Edge(int w, int d) : weight(w), dest(d) {}
};

// Function to add an edge to the graph
void addEdge(vector<vector<Edge>> &graph, int src, int dest, int weight)
{
    graph[src].push_back(Edge(weight, dest));
    graph[dest].push_back(Edge(weight, src));
}

// Prim's algorithm implementation
void primMST(vector<vector<Edge>> &graph, int V)
{
    // Priority queue to store the edges with their weights
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Create a vector to store the minimum weight for each vertex
    vector<int> minWeight(V, INT_MAX);

    // Create a vector to store the parent of each vertex in the MST
    vector<int> parent(V, -1);

    // Create a vector to track visited vertices
    vector<bool> visited(V, false);

    // Start with vertex 0
    int startVertex = 0;
    pq.push(make_pair(0, startVertex));
    minWeight[startVertex] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        visited[u] = true;

        // Traverse all adjacent vertices of u
        for (const Edge &edge : graph[u])
        {
            int v = edge.dest;
            int weight = edge.weight;

            if (!visited[v] && weight < minWeight[v])
            {
                minWeight[v] = weight;
                parent[v] = u;
                pq.push(make_pair(minWeight[v], v));
            }
        }
    }

    // Print the MST path and shortest distance
    cout << "Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (int i = 1; i < V; i++)
    {
        cout << "Edge: " << parent[i] << " - " << i << ", Weight: " << minWeight[i] << "\n";
        totalWeight += minWeight[i];
    }
    cout << "Total Weight of prim's mst: " << totalWeight << "\n";
}

int main()
{
    int V = 6; // Number of vertices in the graph

    vector<vector<Edge>> graph(V);

    // Add edges to the graph
    addEdge(graph, 0, 1, 6);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 4, 3);
    addEdge(graph, 2, 4, 7);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 5, 2);
    addEdge(graph, 4, 5, 6);

    // Run Prim's algorithm
    primMST(graph, V);

    return 0;
}
