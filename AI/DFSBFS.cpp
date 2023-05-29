#include <bits/stdc++.h>
using namespace std;
void add_edge(vector<vector<int>> &adj_list, int u, int v)
{
    adj_list[u].push_back(v);
    adj_list[v].push_back(u);
}
void bfs(vector<vector<int>> &adj_list, int start_node, int search_node)
{
    vector<bool> visited(adj_list.size(), false);
    queue<int> q;
    unordered_map<int, int> parent;
    visited[start_node] = true;
    parent[start_node] = -1;
    q.push(start_node);
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int neighbor : adj_list[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = node;
                q.push(neighbor);
            }
        }
    }
    if (!visited[search_node])
    {
        cout << "Search node not found" << endl;
        return;
    }
    vector<int> path;
    int node = search_node;
    while (node != -1)
    {
        path.push_back(node);
        node = parent[node];
    }
    cout << "BFS path from start node to search node: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}
void dfs(vector<vector<int>> &adj_list, int start_node, int search_node)
{
    vector<bool> visited(adj_list.size(), false);
    stack<int> s;
    unordered_map<int, int> parent;
    visited[start_node] = true;
    parent[start_node] = -1;
    s.push(start_node);
    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        for (int neighbor : adj_list[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = node;
                s.push(neighbor);
            }
        }
    }
    if (!visited[search_node])
    {
        cout << "Search node not found" << endl;
        return;
    }
    vector<int> path;
    int node = search_node;
    while (node != -1)
    {
        path.push_back(node);
        node = parent[node];
    }
    cout << "DFS path from start node to search node: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i] << " ";
    }
    cout << endl;
}
int main()
{
    vector<vector<int>> adj_list;
    int n;
    cout << "Enter number of nodes in the graph: ";
    cin >> n;
    adj_list.resize(n);
    int m;
    cout << "Enter number of edges in the graph: ";
    cin >> m;
    int u, v;
    for (int i = 0; i < m; i++)
    {
        cout << "Enter the endpoints of edge " << i + 1 << ": ";
        cin >> u >> v;
        add_edge(adj_list, u, v);
    }
    int choice;
    vector<int> dfs_path, bfs_path;
    int start_node = 0;
    int search_node;
    string q;
    bool h = true;
    while (h)
    {
        cout << endl;
        cout << "Enter 0 to perform DFS and 1 to perform BFS: ";
        cin >> choice;
        cout << "Enter the node to search: ";
        cin >> search_node;
        switch (choice)
        {
        case 0:
            cout << "DFS traversal: ";
            dfs(adj_list, start_node, search_node);
            break;
        case 1:
            cout << "BFS traversal: ";
            bfs(adj_list, start_node, search_node);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
        bool found = false;
        for (int i = 0; i < adj_list.size(); i++)
        {
            if (i == search_node)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            cout << "Vertex " << search_node << " found in the graph" << endl;
            cout << endl;
        }
        else
        {
            cout << "Vertex " << search_node << " not found in the graph" << endl;
            cout << endl;
        }
        cout << "Do you want to continue(Y/N):";
        cin >> q;
        if (q == "y" || q == "Y")
        {
            continue;
        }
        else
        {
            h = false;
        }
    }
    return 0;
}
// Enter number of nodes in the graph: 6
// Enter number of edges in the graph: 7
// Enter the endpoints of edge 1: 0 1
// Enter the endpoints of edge 2: 0 2
// Enter the endpoints of edge 3: 1 3
// Enter the endpoints of edge 4: 1 4
// Enter the endpoints of edge 5: 2 4
// Enter the endpoints of edge 6: 3 5
// Enter the endpoints of edge 7: 4 5
// Enter 0 to perform DFS and 1 to perform BFS: 0
// Enter the node to search: 5
