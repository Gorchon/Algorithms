//A01254831 in this activity I will use the data structure heap in a tree to create a priority queue
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int value;
    int priority; 
};


class PriorQueue { //
private:
    Node* PQ; // we create a pointer of type Node to store the values of the queue 
    int N, NumNodes;  // we create two variables of type int to store the size of the array and the number of nodes in the queue

public:
    void heapify(vector<int> &hT, int i);
};

