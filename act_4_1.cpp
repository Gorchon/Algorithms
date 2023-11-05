#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph {
private:
    int numVertices;
    int numEdges;
    int** adjMatrix;
    list<int>* adjList;

public:
    Graph(int vertices);
    ~Graph();
    void AddEdge(int src, int dest);
    void LoadGraph();
    void PrintMatrix();
    void PrintList();
    void DFSMatrix(int startVertex);
    void BFSMatrix(int startVertex);
    void DFSList(int startVertex);
    void BFSList(int startVertex);
};


Graph::Graph(int vertices) {
    numVertices = vertices;
    numEdges = 0;

    // Initialize the adjacency matrix
    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Initialize the adjacency list
    adjList = new list<int>[vertices];
}

// Destructor
Graph::~Graph() {
    delete[] adjMatrix;
    delete[] adjList;
}

// Method to add an edge between two vertices
void Graph::AddEdge(int src, int dest) {
    if (src != dest && adjMatrix[src][dest] == 0) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;

        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
        numEdges++;
    }
}

// Method to load a graph with a minimum spanning tree
void Graph::LoadGraph() {
    srand(time(nullptr));

    // Generate a minimum spanning tree
    vector<bool> inMST(numVertices, false);
    vector<int> parent(numVertices, -1);

    inMST[0] = true;  // Start with the first vertex

    while (numEdges < numVertices - 1) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;

        if (inMST[src] && !inMST[dest]) {
            AddEdge(src, dest);
            inMST[dest] = true;
            parent[dest] = src;
        } else if (inMST[dest] && !inMST[src]) {
            AddEdge(dest, src);
            inMST[src] = true;
            parent[src] = dest;
        }
    }
}

// Method to print the adjacency matrix
void Graph::PrintMatrix() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Method to print the adjacency list
void Graph::PrintList() {
    for (int i = 0; i < numVertices; i++) {
        cout << i << " -> ";
        for (auto neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

// Method for depth-first search on the adjacency matrix
void Graph::DFSMatrix(int startVertex) {
    vector<bool> visited(numVertices, false);
    stack<int> s;

    s.push(startVertex);

    while (!s.empty()) {
        int currVertex = s.top();
        s.pop();

        if (!visited[currVertex]) {
            visited[currVertex] = true;
            cout << currVertex << " ";

            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[currVertex][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

// Method for breadth-first search on the adjacency matrix
void Graph::BFSMatrix(int startVertex) {
    vector<bool> visited(numVertices, false);
    queue<int> q;

    q.push(startVertex);

    while (!q.empty()) {
        int currVertex = q.front();
        q.pop();

        if (!visited[currVertex]) {
            visited[currVertex] = true;
            cout << currVertex << " ";

            for (int i = 0; i < numVertices; i++) {
                if (adjMatrix[currVertex][i] == 1 && !visited[i]) {
                    q.push(i);
                }
            }
        }
    }
    cout << endl;
}

// Method for depth-first search on the adjacency list
void Graph::DFSList(int startVertex) {
    vector<bool> visited(numVertices, false);
    stack<int> s;

    s.push(startVertex);

    while (!s.empty()) {
        int currVertex = s.top();
        s.pop();

        if (!visited[currVertex]) {
            visited[currVertex] = true;
            cout << currVertex << " ";

            for (auto i : adjList[currVertex]) {
                if (!visited[i]) {
                    s.push(i);
                }
            }
        }
    }
    cout << endl;
}

// Method for breadth-first search on the adjacency list
void Graph::BFSList(int startVertex) {
    vector<bool> visited(numVertices, false);
    queue<int> q;

    q.push(startVertex);

    while (!q.empty()) {
        int currVertex = q.front();
        q.pop();

        if (!visited[currVertex]) {
            visited[currVertex] = true;
            cout << currVertex << " ";

            for (auto i : adjList[currVertex]) {
                if (!visited[i]) {
                    q.push(i);
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int n, initialNode;
    cout << "Enter the number of vertices (n): ";
    cin >> n;

    Graph g(n);

    g.LoadGraph();

    cout << "Enter the initial node for BFS and DFS: ";
    cin >> initialNode;

    cout << "\nAdjacency Matrix:" << endl;
    g.PrintMatrix();

    cout << "\nDFS Path (Matrix):" << endl;
    g.DFSMatrix(initialNode);

    cout << "\nBFS Path (Matrix):" << endl;
    g.BFSMatrix(initialNode);

    cout << "\nAdjacency List:" << endl;
    g.PrintList();

    cout << "\nDFS Path (List):" << endl;
    g.DFSList(initialNode);

    cout << "\nBFS Path (List):" << endl;
    g.BFSList(initialNode);

    return 0;
}

