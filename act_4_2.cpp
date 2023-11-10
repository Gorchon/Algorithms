#include <iostream> 
#include <vector>
#include <list> 
#include <queue>
#include <stack>
#include <algorithm>
#include <string>

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