#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <list>
#include <string>

using namespace std;


struct node {
    int vertex; 
    struct node* next; // this is the pointer to the next node in the list
};

// struct node* createNode(int v){ // this is the function that creates a new node to be added to the list
//     struct node* newNode = new node; 
//     newNode->vertex = v;
//     newNode->next = NULL;
//     return newNode;
// }
class Graph{
    private: 
                int numVertices;
                list<int> *adjLists;
                bool *visited;                  //these three are the attributes of the class 
            public:
                Graph(int vertices){ // constructor
                    numVertices = vertices;
                    adjLists = new list<int>[vertices];
                    visited = new bool[vertices]; 
                }
                ~Graph(){ // destructor-
                    delete[] adjLists;
                }
                void addEdge(int, int);
                void addEdgeDirected(int, int);
                void printGraph();
                void ResetVisited();
                void DFS(int);
                void BFS(int);
        };


void Graph::BFS(int startVertex) {
    visited[startVertex] = true;
    list<int> queue;
    queue.push_back(startVertex);

    while (!queue.empty()) {
        int currVertex = queue.front();
        cout << "Visited: " << currVertex << " ";
        queue.pop_front();

        for (auto i : adjLists[currVertex]) {
            if (!visited[i]) {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}



void Graph::DFS(int vertex){
    this->visited[vertex] = true;  // we mark the vertex as visited
    list<int> adjVertex = this -> adjLists[vertex]; // we create a list of the adjacent vertices of the vertex that we are currently in this -> adjLists[vertex] this means that we are accessing the list of the vertex that we are currently in

    cout << vertex << " "; // we print the vertex that we are currently in 
    for(auto i: adjVertex){ //we iterate through the list of adjacent vertices 
        if(!this->visited[i]){ // if the vertex has not been visited we call the function again with the vertex that we are currently in
            DFS(i);  // this is the recursive call 
        }
    }
}


void Graph::ResetVisited(){
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
    }
}

void Graph::printGraph(){
    for(int i = 0; i < numVertices; i++){
        cout << i ;
        for(auto node: adjLists[i]){
            cout <<  " -> " << node ;
            }
            cout << endl;
            }
}
     
void Graph::addEdge(int src, int dest){
    adjLists[src].push_back(dest);  //so basically what we are doing is pushing to the back or it could be the front of the lis too the vertex that we want to add to the list 
    adjLists[dest].push_back(src);
}

void Graph::addEdgeDirected(int src, int dest){
    adjLists[src].push_back(dest);
}


int main(){
    Graph g(5); // we create a graph with 5 vertices
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,4);
    g.printGraph();

    cout << " \nBFS: " << endl; 
    g.BFS(0);
    return 0;
}
