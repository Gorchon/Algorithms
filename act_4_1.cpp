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
    Graph(int vertices, int edges);
    ~Graph();

    void LoadGraph();
    void PrintMatrix();
    void PrintList();
    void DFSMatrix(int startVertex);
    void BFSMatrix(int startVertex);
    void DFSList(int startVertex);
    void BFSList(int startVertex);
};

Graph::Graph(int vertices, int edges) {
    numVertices = vertices;
    numEdges = edges;

    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) { 
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    adjList = new list<int>[vertices];    //this is the adjacency list. and represents a list of vertices adjacent to a particular vertex. 
} 

Graph::~Graph() {
    delete[] adjMatrix;
    delete[] adjList;
}

void Graph::LoadGraph() { //this is the method that loads the graph with random edges and vertices.
    srand(time(nullptr)); //srand is used to generate random numbers, works with time(nullptr) to generate a random number every time the program is run.

    for (int i = 0; i < numEdges; i++) { //we use a for loop to generate the edges and vertices for the graph. 
        int src = rand() % numVertices; //we use rand() % numVertices to generate a random number between 0 and the number of vertices. 
        int dest = rand() % numVertices;

        if (src != dest && adjMatrix[src][dest] == 0) { //this if statement is used to make sure that the source and destination are not the same and that the edge does not already exist.
            adjMatrix[src][dest] = 1;  //we use adjMatrix[src][dest] = 1 to create the edge between the source and destination.
            adjMatrix[dest][src] = 1; // we need to do it twice because the graph is undirected. 

            adjList[src].push_back(dest); // in this we push the destination into the source's list. 
            adjList[dest].push_back(src);
        }
    }
}

void Graph::PrintMatrix() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::PrintList() {
    for (int i = 0; i < numVertices; i++) {
        cout << i << " -> ";
        for (auto neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

void Graph::DFSMatrix(int startVertex) {
    vector<bool> visited(numVertices, false); //we use a vector to keep track of the visited vertices. 
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
    int n, m, initialNode;
    cout << "Enter the number of vertices (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;

    Graph g(n, m);

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
