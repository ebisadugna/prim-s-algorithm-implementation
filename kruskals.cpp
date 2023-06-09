#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a graph edge
struct Edge
{
    int src, dest, weight;

    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

// Structure to represent a disjoint set
struct DisjointSet
{
    vector<int> parent, rank;

    DisjointSet(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else
        {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Comparison function for sorting edges based on weight
bool compareEdges(const Edge &a, const Edge &b)
{
    return a.weight < b.weight;
}

// Kruskal's algorithm implementation
void kruskalMST(vector<Edge> &edges, int V)
{
    // Sort the edges in ascending order of weight
    sort(edges.begin(), edges.end(), compareEdges);

    vector<Edge> mst; // Minimum spanning tree
    DisjointSet ds(V);

    int totalWeight = 0;

    for (const Edge &edge : edges)
    {
        int src = edge.src;
        int dest = edge.dest;

        int rootSrc = ds.find(src);
        int rootDest = ds.find(dest);

        if (rootSrc != rootDest)
        {
            mst.push_back(edge);
            totalWeight += edge.weight;
            ds.unionSets(rootSrc, rootDest);
        }
    }

    // Print the MST path and total weight
    cout << "Minimum Spanning Tree:\n";
    for (const Edge &edge : mst)
    {
        cout << "Edge: " << edge.src << " - " << edge.dest << ","
             << " Weight: " << edge.weight << "\n";
    }
    cout << "Total Weight of Kruskal's mst: " << totalWeight << "\n";
}

int main()
{
    int V = 6; // Number of vertices in the graph

    vector<Edge> edges;
    edges.push_back(Edge(0, 1, 6));
    edges.push_back(Edge(0, 2, 1));
    edges.push_back(Edge(0, 3, 5));
    edges.push_back(Edge(1, 4, 3));
    edges.push_back(Edge(2, 4, 7));
    edges.push_back(Edge(2, 3, 5));
    edges.push_back(Edge(2, 5, 4));
    edges.push_back(Edge(3, 5, 2));
    edges.push_back(Edge(4, 5, 6));

    // Run Kruskal's algorithm
    kruskalMST(edges, V);

    return 0;
}
