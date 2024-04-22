#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
#include <algorithm>
using namespace std;

// Define a graph class for BFS and DFS
class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v), adj(v) {}

    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Breadth-First Search (BFS)
    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Depth-First Search (DFS)
    void DFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        while (!s.empty()) {
            int u = s.top();
            s.pop();
            cout << u << " ";

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    s.push(v);
                }
            }
        }
    }
};

int main() {
    // Create a graph
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // Perform sequential BFS and DFS
    clock_t startSeqBFS = clock();
    g.BFS(0);
    clock_t endSeqBFS = clock();
    double seqBFSTime = double(endSeqBFS - startSeqBFS) / CLOCKS_PER_SEC;

    clock_t startSeqDFS = clock();
    g.DFS(0);
    clock_t endSeqDFS = clock();
    double seqDFSTime = double(endSeqDFS - startSeqDFS) / CLOCKS_PER_SEC;

    // Display sequential results
    cout << "\nSequential BFS Time: " << seqBFSTime << " seconds\n";
    cout << "Sequential DFS Time: " << seqDFSTime << " seconds\n";

    return 0;
}
