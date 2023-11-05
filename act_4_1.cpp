#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph {
private: //these things are defined in private because they are not supposed to be accessed by the user 
    int numVertices;
    int numEdges;
    int** adjMatrix;
    list<int>* adjList; 

public:
    Graph(int vertices, int edges) { 
        numVertices = vertices; 
        numEdges = edges; 

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

    ~Graph() {
        delete[] adjMatrix;
        delete[] adjList;
    }

    void LoadGraph() {
        srand(time(nullptr));

        // Randomly fill the graph with m connections
        for (int i = 0; i < numEdges; i++) {
            int src = rand() % numVertices;
            int dest = rand() % numVertices;

            if (src != dest && adjMatrix[src][dest] == 0) {
                adjMatrix[src][dest] = 1;
                adjMatrix[dest][src] = 1;

                adjList[src].push_back(dest);
                adjList[dest].push_back(src);
            }
        }
    }

    void PrintMatrix() { 
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl; 
        }
    }

    void PrintList() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " -> ";
            for (auto neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void DFS(int startVertex) {  
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

    void BFS(int startVertex) {
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
};

int main() {
    int n, m, initialNode;
    cout << "Enter the number of vertices (n): ";
    cin >> n;
    cout << "Enter the number of edges (m): ";
    cin >> m;

    Graph g(n, m);

    g.LoadGraph();

    cout << "Enter the initial node for DFS and BFS: ";
    cin >> initialNode;

    cout << "\nAdjacency Matrix:" << endl;
    g.PrintMatrix();

    cout << "\nAdjacency List:" << endl;
    g.PrintList();

    cout << "\nDFS Path:" << endl;
    g.DFS(initialNode);

    cout << "\nBFS Path:" << endl;
    g.BFS(initialNode);

    return 0;
}
