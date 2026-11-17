#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// BFS to find shortest path
void bfs(const vector<vector<int>>& graph, int start, int destination,
         const vector<string>& buildings)
{
    if (graph.size() != buildings.size() ||
        start < 0 || destination < 0 ||
        start >= static_cast<int>(graph.size()) ||
        destination >= static_cast<int>(graph.size()))
    {
        cerr << "Invalid graph or building index." << endl;
        return;
    }

    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);

    queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (current == destination)
            break;

        for (int neighbor : graph[current])
        {
            if (neighbor >= 0 &&
                neighbor < static_cast<int>(graph.size()) &&
                !visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if (!visited[destination])
    {
        cout << "No route found." << endl;
        return;
    }

    vector<int> path;

    for (int v = destination; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    cout << "Starting Building: " << buildings[start] << endl;
    cout << "Destination: " << buildings[destination] << endl;
    cout << "Shortest Route (BFS):" << endl;

    for (int vertex : path)
        cout << buildings[vertex] << " ";

    cout << endl;
    cout << "Number of Edges: " << path.size() - 1 << endl;
}

// DFS from lecture slides
void dfs(const vector<vector<int>>& graph,
         int v,
         vector<bool>& visited,
         const vector<string>& buildings)
{
    if (v < 0 || v >= static_cast<int>(graph.size()) ||
        graph.size() != buildings.size())
    {
        return;
    }

    visited[v] = true;

    cout << buildings[v] << " ";

    for (int neighbor : graph[v])
    {
        if (neighbor >= 0 &&
            neighbor < static_cast<int>(graph.size()) &&
            !visited[neighbor])
        {
            dfs(graph, neighbor, visited, buildings);
        }
    }
}

int main()
{
    vector<string> buildings =
    {
        "Library",
        "Gym",
        "Dorm",
        "Cafe",
        "LSA",
        "Hall Moody"
    };

    vector<vector<int>> graph =
    {
        {1, 4},      // Library
        {0, 2},      // Gym
        {1, 3, 5},   // Dorm
        {2},         // Cafe
        {0, 5},      // LSA
        {4, 2}       // Hall Moody
    };

    bfs(graph, 0, 2, buildings);

    cout << endl;

    cout << "DFS Traversal:" << endl;

    vector<bool> visited(graph.size(), false);
    dfs(graph, 0, visited, buildings);

    cout << endl;

    return 0;
}
