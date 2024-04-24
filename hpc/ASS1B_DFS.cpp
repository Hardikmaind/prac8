#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;


void printDFS(int n, vector<vector<int>>& edges, int sv, vector<bool>& visited) {
    cout << sv; // printing starting vertex
    cout << "->";
    visited[sv] = true; // making starting vertex as visited

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (i == sv) {
            continue; // if i and starting vertex are same then will skip it and move forward
        }
        if (edges[sv][i] == 1) {
            if (visited[i]) {
                continue;
            }
            printDFS(n, edges, i, visited);
        }
    }
}

int main() {
    int n, e;
    cout << "Enter number of vertices:";
    cin >> n;
    cout << "Enter number of edges:";
    cin >> e;

    cout << "Enter Edges:" << endl;
    vector<vector<int>> edges(n, vector<int>(n, 0)); // vector of vectors initialized with 0

    for (int i = 0; i < e; i++) {
        int f, s; // first index and second index
        cin >> f >> s;
        edges[f][s] = 1; // filling visited edges with 1
        edges[s][f] = 1;
    }
    vector<bool> visited(n, false);

    cout << "The path will be:";
    printDFS(n, edges, 0, visited);
    return 0;
}


// number of vertices:5
// number of edges:7
// Edges:
// 0 1
// 0 2
// 1 2
// 1 3
// 2 3
// 3 4
// 4 0

