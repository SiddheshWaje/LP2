#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void dijkstra(vector<vector<pair<int, int>>>& graph, int start, vector<int>& distance) {
    int n = graph.size();
    distance.resize(n, INF);
    distance[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        // Skip if the node has been processed before with a shorter distance
        if (dist_u > distance[u])
            continue;
            //above condition is met when we are exploring the explored node and weight get added twice 
            // as the node is explored it's distance is present in distance vector

        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            int new_dist = dist_u + weight;

            // Update the distance if a shorter path is found
            if (new_dist < distance[v]) {
                distance[v] = new_dist;
                pq.push({new_dist, v});
            }
        }
    }
}

int main() {
    int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    vector<vector<pair<int, int>>> graph(n);
    cout << "Enter the edges (source, destination, weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    vector<int> distance;
    dijkstra(graph, start, distance);

    cout << "Shortest distances from node " << start << " to all other nodes:" << endl;
    for (int i = 0; i < n; ++i) {
        if (distance[i] == INF)
            cout << "Node " << i << ": Not reachable" << endl;
        else
            cout << "Node " << i << ": " << distance[i] << endl;
    }

    return 0;
}

// Input:
// Number of vertices: 6
// Number of edges: 9

// Edges and their weights:
// Edge 1: 0 1 4
// Edge 2: 0 2 2
// Edge 3: 1 2 1
// Edge 4: 1 3 5
// Edge 5: 2 3 8
// Edge 6: 2 4 10
// Edge 7: 3 4 2
// Edge 8: 3 5 6
// Edge 9: 4 5 3