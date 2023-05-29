#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a disjoint set
struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

// Function to compare edges by weight (used for sorting)
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to find MST using Kruskal's algorithm
vector<Edge> kruskalMST(vector<Edge>& edges, int n) {
    // Sort edges by weight in non-decreasing order
    sort(edges.begin(), edges.end(), compareEdges);

    DisjointSet ds(n);
    vector<Edge> mst;

    for (Edge edge : edges) {
        int src = edge.src;
        int dest = edge.dest;

        int srcParent = ds.find(src);
        int destParent = ds.find(dest);

        // Check if including the current edge forms a cycle
        // If not, include it in the MST and merge the sets
        if (srcParent != destParent) {
            mst.push_back(edge);
            ds.merge(srcParent, destParent);
        }
    }

    return mst;
}

// Driver's code
int main() {
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    vector<Edge> edges(m);
    cout << "Enter the source, destination, and weight of each edge:\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    vector<Edge> mst = kruskalMST(edges, n);

    cout << "Minimum Spanning Tree:\n";
    for (Edge edge : mst) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << "\n";
    }

    return 0;
}

/*
kruskals
Enter the number of vertices: 4
Enter the number of edges: 5
Enter the source, destination, and weight of each edge:
0 1 10
0 2 6
0 3 5
1 3 15
2 3 4

*/