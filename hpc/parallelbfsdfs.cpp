
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
#include <omp.h>
#include <algorithm>
using namespace std;

// Define a graph class for BFS and DFS
class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int v) : V(v), adj(v) {}          //this is a constructor

    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // Function to take graph input from user
    void inputGraph() {
        int edges;
        cout << "Enter the number of edges: ";
        cin >> edges;

        cout << "Enter edges (u v):" << endl;
        for (int i = 0; i < edges; ++i) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }

    // Parallel Breadth-First Search (BFS)
    void parallelBFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cout << u << " ";

#pragma omp parallel for
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // Parallel Depth-First Search (DFS)
    void parallelDFS(int start) {
        vector<bool> visited(V, false);
        stack<int> s;

        visited[start] = true;
        s.push(start);

        while (!s.empty()) {
            int u = s.top();
            s.pop();
            cout << u << " ";

#pragma omp parallel for
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
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    // Create a graph
    Graph g(vertices);
    g.inputGraph();

    // Perform parallel BFS and DFS
    clock_t startParBFS = clock();
    cout << "this is parallel BFS\n";
    g.parallelBFS(0);
    cout << endl;
    clock_t endParBFS = clock();
    double parBFSTime = double(endParBFS - startParBFS) / CLOCKS_PER_SEC;

    clock_t startParDFS = clock();
    cout << "this is parallel DFS\n";
    g.parallelDFS(0);
    clock_t endParDFS = clock();
    double parDFSTime = double(endParDFS - startParDFS) / CLOCKS_PER_SEC;

    // Display parallel results
    cout << "\n\nParallel BFS Time: " << parBFSTime << " seconds\n";
    cout << "Parallel DFS Time: " << parDFSTime << " seconds\n";

    return 0;
}
