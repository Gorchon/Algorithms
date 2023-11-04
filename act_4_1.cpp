#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <list>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph {
private:
    int numVertices;
    list<int> *adjList;
    int **adjMatrix;
    bool *visited;

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList = new list<int>[vertices]; // this is the array of lists that will represent the adjacency list of the graph 
        adjMatrix = new int*[vertices];
        visited = new bool[vertices];

        for (int i = 0; i < vertices; i++) { 
            adjMatrix[i] = new int[vertices]; 
            for (int j = 0; j < vertices; j++) { 
                adjMatrix[i][j] = 0; 
            }
        }
    }

    ~Graph() {
        delete[] adjList;
        for (int i = 0; i < numVertices; i++) {  //this loop deletes the rows of the matrix 
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);

        // Update the adjacency matrix to represent the edge between src and dest
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;
    }

    void addEdgeDirected(int src, int dest) {
        adjList[src].push_back(dest); 
        adjMatrix[src][dest] = 1;   
    }

    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << i;
            for (auto node : adjList[i]) {
                cout << " -> " << node;
            }
            cout << endl;
        }
    }

    void printMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void BFS(int startVertex) {
        visited[startVertex] = true;
        list<int> queue;
        queue.push_back(startVertex);

        while (!queue.empty()) {
            int currVertex = queue.front();
            cout << "Visited: " << currVertex << " ";
            queue.pop_front();

            for (auto i : adjList[currVertex]) {
                if (!visited[i]) {
                    visited[i] = true;
                    queue.push_back(i);
                }
            }
        }
    }

    void DFS(int startVertex) {
        visited[startVertex] = true;
        cout << "Visited: " << startVertex << " ";

        for (auto i : adjList[startVertex]) {
            if (!visited[i]) {
                DFS(i);
            }
        }
    }

    void ResetVisited() {
        for (int i = 0; i < numVertices; i++) {
            visited[i] = false;
        }
    }

    // Load the graph with random connections based on the given number of edges
    void LoadGraph(int numEdges) {
        if (numEdges > (numVertices * (numVertices - 1) / 2)) {
            cerr << "Error: Too many edges for the given number of vertices." << endl;
            return;
        }

        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < numEdges; i++) {
            int src, dest;
            do {
                src = rand() % numVertices;
                dest = rand() % numVertices;
            } while (src == dest || adjMatrix[src][dest] == 1);

            addEdge(src, dest);
        }
    }
};



int main() {
    int n, m;
    cout << "Enter the number of vertices (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;

    Graph g(n); // Create a graph with n vertices

    // Load the graph with random connections
    g.LoadGraph(m);

    g.printGraph();
    g.printMatrix();

    cout << "\nBFS: " << endl;
    g.BFS(0);

    cout << "\nDFS: " << endl;
    g.DFS(0);

    return 0;
}
