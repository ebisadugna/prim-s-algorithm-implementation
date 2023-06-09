#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// Graph class representing an undirected graph
class Graph {
    int numVertices;
    vector<vector<int>> adjList;

public:
    Graph(int V) : numVertices(V), adjList(V) {}

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void dfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> stack;

        stack.push(startVertex);
        visited[startVertex] = true;

        while (!stack.empty()) {
            int currentVertex = stack.top();
            stack.pop();
            cout << currentVertex << " ";

            for (int adjacentVertex : adjList[currentVertex]) {
                if (!visited[adjacentVertex]) {
                    stack.push(adjacentVertex);
                    visited[adjacentVertex] = true;
                }
            }
        }
    }

    void bfs(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> queue;

        queue.push(startVertex);
        visited[startVertex] = true;

        while (!queue.empty()) {
            int currentVertex = queue.front();
            queue.pop();
            cout << currentVertex << " ";

            for (int adjacentVertex : adjList[currentVertex]) {
                if (!visited[adjacentVertex]) {
                    queue.push(adjacentVertex);
                    visited[adjacentVertex] = true;
                }
            }
        }
    }
};

int main() {
    int V = 7;  // Number of vertices

    Graph graph(V);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    int startVertex = 0;

    cout << "DFS traversal starting from vertex " << startVertex << ": ";
    graph.dfs(startVertex);

    cout << "\nBFS traversal starting from vertex " << startVertex << ": ";
    graph.bfs(startVertex);

    return 0;
}
