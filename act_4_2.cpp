#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph {
private:
    int numVertices;
    int** adjMatrix;
    list<int>* adjList;
    bool* visited;

public:
    Graph(int vertices);
    ~Graph();

    void LoadGraph();
    void PrintMatrix();
    void PrintList();
    bool IsBipartite(int startVertex);
    bool IsTree(); 
    //Now we Print the data in topological order.
    void TopologicalSort(); 
};

Graph::Graph(int vertices) {
    numVertices = vertices;

    adjMatrix = new int*[vertices];
    for (int i = 0; i < vertices; i++) {
        adjMatrix[i] = new int[vertices];
        for (int j = 0; j < vertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    adjList = new list<int>[vertices];
    visited = nullptr;  // Initialize visited to nullptr
}

Graph::~Graph() {
    delete[] visited;  // Deallocate memory for 'visited' 
    delete[] adjMatrix;  // Deallocate memory for 'adjMatrix'
    delete[] adjList; // Deallocate memory for 'adjList'
}

void Graph::LoadGraph() {
    srand(time(nullptr)); // this line generates a random number every time the program is run. This is done in order to generate random edges and vertices. 

    visited = new bool[numVertices]; // Allocate memory for the member variable 'visited' 
    visited[0] = true; // we assign the value of true to visited[0] because we start with the vertex 0. 

    int edgesCreated = 0;  // we create a variable called edgesCreated to store the number of edges that have been created. 

    while (edgesCreated < numVertices - 1) {  // we use a while loop to create the edges and vertices. 
        int src = rand() % numVertices; // we use rand() % numVertices to generate a random number between 0 and the number of vertices.
        int dest = rand() % numVertices; 

        if (!visited[dest] && src != dest) { // we use this if statement to make sure that the source and destination are not the same and that the edge does not already exist. I f the connection does not exist then we create it, but if it does then we do not create it.
            visited[dest] = true;
            adjMatrix[src][dest] = 1;
            adjList[src].push_back(dest);
            edgesCreated++;
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
        cout << i << "  ";
        for (auto neighbor : adjList[i]) {
            cout <<  "-> " << neighbor << " ";
        }
        cout << endl;
    }
}

bool Graph::IsBipartite(int startVertex) { // 
    visited = new bool[numVertices]; // we create a vector called visited that will store the vertices that have been visited. of size numVertices.
    fill(visited, visited + numVertices, false);  // we use the fill function to fill the vector with the value of false. 

    vector<bool> color(numVertices); // we create a vector called color that will store the color of each vertex. of size numVertices. 

    visited[startVertex] = true; // we assign the value of true to visited[startVertex] because we start with the vertex 0. 
    color[startVertex] = 0; 

    list<int> queue; // we create a list called queue to store the vertices that have been visited. 
    queue.push_back(startVertex); // we push the startVertex into the queue. 

    while (!queue.empty()) { // while the queue is not empty. 
        int v = queue.front(); // we store the vertex that we are currently visiting.
        queue.pop_front(); // we pop the vertex from the queue in order to visit it. 

        for (auto u : adjList[v]) { // we iterate through the list of the vertex that we are currently visiting.  
            if (!visited[u]) {  // if the vertex has not been visited then we assign the value of true to visited[u] and the value of !color[v] to color[u] and we push the vertex into the queue.
                visited[u] = true; // we assign the value of true to visited[u] because we have visited the vertex. 
                color[u] = !color[v]; // we assign the value of !color[v] to color[u] because we have visited the vertex. 
                queue.push_back(u);
            } else if (color[u] == color[v]) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::IsTree() {
    visited = new bool[numVertices];
    fill(visited, visited + numVertices, false);

    list<int> queue;
    queue.push_back(0);

    int edgeCount = 0;  // Variable to count the number of edges

    while (!queue.empty()) {
        int v = queue.front();
        queue.pop_front();

        if (!visited[v]) {
            visited[v] = true;

            for (auto u : adjList[v]) {
                if (!visited[u]) {
                    queue.push_back(u);
                    edgeCount++;  // Increment edge count for each unvisited neighbor
                }
            }
        } else {
            return false;
        }
    }

    // Check if the number of edges is one less than the number of vertices
    return (edgeCount == numVertices - 1);
}


void Graph::TopologicalSort() {
    vector<int> inDegree(numVertices, 0); // we create a vector called inDegree that will store the inDegree of each vertex.
    for(int i = 0; i < numVertices; i++){ // we iterate through the number of vertices.
        for(auto u: adjList[i]){ // we iterate through the list of each vertex.
            inDegree[u]++; // we increment the inDegree of the vertex.
        }
    }
    list<int> queue; // we create a list called queue to store the vertices that have been visited.
    for(int i = 0; i < numVertices; i++){ // we iterate through the number of vertices.
        if(inDegree[i] == 0){ // if the inDegree of the vertex is 0 then we push the vertex into the queue.
            queue.push_back(i);
        }
    }
    while(!queue.empty()){ // while the queue is not empty.
        int v = queue.front(); // we store the vertex that we are currently visiting.
        queue.pop_front(); // we pop the vertex from the queue in order to visit it.
        cout << v << " "; // we print the vertex that we are currently visiting.
        for(auto u: adjList[v]){ // we iterate through the list of the vertex that we are currently visiting.
            inDegree[u]--; // we decrement the inDegree of the vertex.
            if(inDegree[u] == 0){ // if the inDegree of the vertex is 0 then we push the vertex into the queue.
                queue.push_back(u); 
            }   
        }
    }
    cout << endl;
}




int main() {
    int n;
    cout << "Enter the number of vertices (n): ";
    cin >> n;

    Graph g(n);
    g.LoadGraph();

    cout << endl << "Adjacency Matrix:" << endl;
    g.PrintMatrix();

    cout << endl << "Adjacency List:" << endl;
    g.PrintList();

    g.IsBipartite(0); 
    cout << endl; 
    if (g.IsBipartite(0)) {
        cout << "The graph is bipartite" << endl;
    } else {
        cout << "The graph is not bipartite" << endl;
    }
    cout << endl;
    g.IsTree();
    if (g.IsTree()) {
        cout << "The graph is a tree" << endl;
    } else {
        cout << "The graph is not a tree" << endl;
    }

    cout << endl << "Topological Sort:" << endl;
    g.TopologicalSort();


    return 0;
}
