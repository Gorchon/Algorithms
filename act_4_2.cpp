#include <iostream> 
#include <vector>
#include <list> 
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

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

//A dag has no cycles meaning there is no sequence of nodes such that you can start at one node and visit all the other nodes in the sequence and return to the starting node. Ww say that a graph is acyclic 
Graph::Graph(int vertices, int edges) { //this is the constructor for the graph class. 
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

//The purpose of this function is randomly create an adjacency list of a Connected Directed Acyclic Graph (DAG) with the given number of vertices, it will recibe as input only the number of vertices. 
void Graph::LoadGraph() {   
    srand(time(nullptr)); //srand is used to generate random numbers, works with time(nullptr) to generate a random number every time the program is run.

    for (int i = 0; i < numEdges; i++) { //we use a for loop to generate the edges and vertices for the graph.  
        int src = rand() % numVertices; //we use rand() % numVertices to generate a random number between 0 and the number of vertice to be the source.
        int dest = rand() % numVertices; //we use rand() % numVertices to generate a random number between 0 and the number of vertice to be the destination. 

        if (src != dest && adjMatrix[src][dest] == 0) { //this if statement is used to make sure that the source and destination are not the same and that the edge does not already exist.
            adjMatrix[src][dest] = 1;  //we use adjMatrix[src][dest] = 1 to create the edge between the source and destination.
            adjMatrix[dest][src] = 1; // we need to do it twice because the graph is undirected. 
        }
    }

    for (int i = 0; i < numVertices; i++) { //we use a for loop to create the adjacency list. 
        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j] == 1) { //if the edge exists, we add the destination to the adjacency list.  
                adjList[i].push_back(j);
            }
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

int main() {
    Graph g(5, 10);
    g.LoadGraph();
    g.PrintMatrix();
    g.PrintList();
}