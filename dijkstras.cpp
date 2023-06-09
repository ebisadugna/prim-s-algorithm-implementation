#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

// Vertex structure to represent a vertex in the graph
struct Vertex
{
    int id;
    int distance;
    bool known;
    Vertex *path;
    vector<pair<Vertex *, int>> neighbors; // Adjacent vertices and corresponding edge costs
};

// Comparison function for the priority queue in Dijkstra's algorithm
struct CompareVertex
{
    bool operator()(const Vertex *v1, const Vertex *v2)
    {
        return v1->distance > v2->distance;
    }
};

// Dijkstra's algorithm
void dijkstra(Vertex *start, vector<Vertex *> &vertices)
{
    priority_queue<Vertex *, vector<Vertex *>, CompareVertex> pq;

    // Initialize distances and known flags for all vertices
    for (Vertex *v : vertices)
    {
        v->distance = numeric_limits<int>::max();
        v->known = false;
        v->path = nullptr;
    }

    start->distance = 0;
    pq.push(start);

    while (!pq.empty())
    {
        Vertex *current = pq.top();
        pq.pop();

        if (current->known)
            continue;

        current->known = true;

        // Explore neighbors of the current vertex
        for (auto &neighbor : current->neighbors)
        {
            Vertex *w = neighbor.first;
            int costFromVtoW = neighbor.second;

            if (!w->known && w->distance > current->distance + costFromVtoW)
            {
                w->distance = current->distance + costFromVtoW;
                w->path = current;
                pq.push(w);
            }
        }
    }
}

int main()
{
    // Create vertices and edges in the graph
    vector<Vertex *> vertices;

    Vertex *v1 = new Vertex{1, numeric_limits<int>::max(), false, nullptr, {}};
    Vertex *v2 = new Vertex{2, numeric_limits<int>::max(), false, nullptr, {}};
    Vertex *v3 = new Vertex{3, numeric_limits<int>::max(), false, nullptr, {}};
    Vertex *v4 = new Vertex{4, numeric_limits<int>::max(), false, nullptr, {}};
    Vertex *v5 = new Vertex{5, numeric_limits<int>::max(), false, nullptr, {}};

    v1->neighbors = {{v2, 10}, {v4, 5}};
    v2->neighbors = {{v3, 1}, {v4, 2}};
    v3->neighbors = {{v5, 4}};
    v4->neighbors = {{v2, 3}, {v3, 9}, {v5, 2}};
    v5->neighbors = {{v1, 7}, {v3, 6}};

    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);
    vertices.push_back(v5);

    // Perform Dijkstra's algorithm starting from vertex v1
    dijkstra(v1, vertices);

    // Print the shortest paths and distances from v1 to other vertices
    for (Vertex *v : vertices)
    {
        cout << "Shortest path from v1 to v" << v->id << ": ";
        Vertex *current = v;
        cout << current->id;
        while (current->path != nullptr)
        {
            cout << " <- " << current->path->id;
            current = current->path;
        }
        cout << ", Distance: " << v->distance << endl;
    }

    // Clean up memory
    for (Vertex *v : vertices)
    {
        delete v;
    }

    return 0;
}