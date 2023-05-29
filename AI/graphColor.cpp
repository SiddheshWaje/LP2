#include <iostream>
#include <vector>
using namespace std;

const int MAX_COLORS = 4; // Maximum number of colors

bool isSafe(int v, const vector<vector<int>>& graph, const vector<int>& colors, int c) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[v][i] && colors[i] == c) {
            return false;
        }
    }
    return true;
}

bool graphColoringUtil(const vector<vector<int>>& graph, vector<int>& colors, int v) {
    if (v == graph.size()) {
        return true; // All vertices are colored
    }

    for (int c = 1; c <= MAX_COLORS; c++) {
        if (isSafe(v, graph, colors, c)) {
            colors[v] = c; // Assign color to vertex v

            if (graphColoringUtil(graph, colors, v + 1)) {
                return true; // Recurse for the next vertex
            }

            colors[v] = 0; // Backtrack: Remove color from vertex v
        }
    }

    return false; // No valid color found
}

bool graphColoring(const vector<vector<int>>& graph, vector<int>& colors) {
    return graphColoringUtil(graph, colors, 0);
}

int main() {
    int numVertices, numEdges;

    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    // Create an adjacency matrix for the graph
    vector<vector<int>> graph(numVertices, vector<int>(numVertices, 0));

    cout << "Enter the edges (vertex1 vertex2):" << endl;
    for (int i = 0; i < numEdges; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        graph[vertex1][vertex2] = 1;
        graph[vertex2][vertex1] = 1;
    }

    vector<int> colors(numVertices, 0); // Initialize colors to 0 (not assigned)

    if (graphColoring(graph, colors)) {
        cout << "Graph coloring possible." << endl;
        cout << "Assigned colors:" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << ": Color " << colors[i] << endl;
        }
    } else {
        cout << "Graph coloring not possible." << endl;
    }

    return 0;
}
// }
// Enter the number of vertices: 5
// Enter the number of edges: 6
// Enter the edges (vertex1 vertex2):
// 0 1
// 0 2
// 1 2
// 1 3
// 2 3
// 3 4