#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// BFS finds a shortest path in an unweighted graph.
void bfs(const vector<vector<int>>& graph,
         int start,
         int destination,
         const vector<string>& buildings)
{
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    vector<int> path;
    for (int current = destination; current != -1; current = parent[current])
        path.push_back(current);

    reverse(path.begin(), path.end());

    cout << "Starting Building: " << buildings[start] << endl;
    cout << "Destination: " << buildings[destination] << endl;
    cout << "Shortest Route (BFS):" << endl;

    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << buildings[path[i]];
        if (i + 1 < path.size())
            cout << " -> ";
    }

    cout << endl;
    cout << "Number of Edges: " << path.size() - 1 << endl;
}

// DFS displays every building reachable from the starting building.
void dfs(const vector<vector<int>>& graph,
         int current,
         vector<bool>& visited,
         const vector<string>& buildings)
{
    visited[current] = true;
    cout << buildings[current] << " ";

    for (int neighbor : graph[current])
    {
        if (!visited[neighbor])
            dfs(graph, neighbor, visited, buildings);
    }
}

int main()
{
    // Building indexes:
    // 0 = Library, 1 = Gym, 2 = Dorm,
    // 3 = Cafe, 4 = LS, 5 = Hall Moody.
    vector<string> buildings =
    {
        "Library",
        "Gym",
        "Dorm",
        "Cafe",
        "LS",
        "Hall Moody"
    };

    // Undirected campus graph represented as an adjacency list.
    vector<vector<int>> graph =
    {
        {1, 4},       // Library: Gym, LS
        {0, 4, 2},     // Gym: Library, LS, Dorm
        {1, 5, 3},     // Dorm: Gym, Hall Moody, Cafe
        {2},           // Cafe: Dorm
        {0, 1, 5},     // LS: Library, Gym, Hall Moody
        {4, 2}         // Hall Moody: LS, Dorm
    };

    bfs(graph, 0, 2, buildings);

    cout << endl;
    cout << "DFS Traversal:" << endl;

    vector<bool> visited(graph.size(), false);
    dfs(graph, 0, visited, buildings);
    cout << endl;

    cout << endl;
    cout << "Why BFS is better for the shortest path:" << endl;
    cout << "BFS explores the graph one level at a time, so the first path it "
            "finds uses the fewest edges. DFS explores one branch deeply and "
            "does not guarantee a shortest path." << endl;

    return 0;
}
