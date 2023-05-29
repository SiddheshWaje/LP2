#include <bits/stdc++.h>
using namespace std;
// Number of vertices in the graph
#define V 5
//In the below function we check minimal value of adjacent vertex which is in 
//key array but not in MST once we found we updata that vertex in mst
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}
void printMST(int parent[], int graph[V][V])
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}
void primMST(int graph[V][V])
{
    // Array to store constructed MST
    int parent[V];
    // Key values used to pick minimum weight edge in cut
    int key[V];
    // To represent set of vertices included in MST
    bool mstSet[V];
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
    key[0] = 0;
    // First node is always root of MST
    parent[0] = -1;
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    // Print the constructed MST
    printMST(parent, graph);
}
// Driver's code
int main()
{
    int graph[V][V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << "Edge " << i << " - " << j << " : ";
            cin >> graph[i][j];
        }
    }
    // Print the solution
    primMST(graph);
    return 0;
}
// Edge 0 - 0 : 0
// Edge 0 - 1 : 2
// Edge 0 - 2 : 0
// Edge 0 - 3 : 6
// Edge 0 - 4 : 0
// Edge 1 - 0 : 2
// Edge 1 - 1 : 0
// Edge 1 - 2 : 3
// Edge 1 - 3 : 8
// Edge 1 - 4 : 5
// Edge 2 - 0 : 0
// Edge 2 - 1 : 3
// Edge 2 - 2 : 0
// Edge 2 - 3 : 0
// Edge 2 - 4 : 7
// Edge 3 - 0 : 6
// Edge 3 - 1 : 8
// Edge 3 - 2 : 0
// Edge 3 - 3 : 0
// Edge 3 - 4 : 9
// Edge 4 - 0 : 0
// Edge 4 - 1 : 5
// Edge 4 - 2 : 7
// Edge 4 - 3 : 9
// Edge 4 - 4 : 0