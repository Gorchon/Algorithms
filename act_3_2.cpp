#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int value;
    int priority;
};

class PriorQueue { 
private:
    Node* PQ; // Pointer to store values called PQ
    int N, NumNodes; // we create two variables of type int to store the size of the array and the number of nodes in the queue

public:
    PriorQueue(int size) { // Constructor of the class
        N = size; 
        PQ = new Node[N];  // we create a new array of type Node with size N using new because we are using pointers so we need to allocate memory dynamically
        NumNodes = 0; // we initialize the number of nodes to 0 because initially the queue is totally empty 
    }

    ~PriorQueue() { // a destructor is a special member function that is called when the lifetime of an object ends. The purpose of the destructor is to free the resources that the object may have acquired during its lifetime.
        delete[] PQ; // the delete [] means that we are deleting an array of type Node called PQ
    } 

    void heapify(int i); // we declare the heapify function that receives and int that is gonna be the index of the node that we want to heapify, for example if we want to heapify the root we pass 0 as the index and that will be the root
    void insert(int value, int priority); 
    void deleteMax();
    void top();
    bool empty();
    int size();
    void DeleteAll();
};

void PriorQueue::heapify(int i) { //we receive i aa parameter because i is the index of the node that we want to heapify 
    int largest = i;     // Initialize largest as root
    int l = 2 * i + 1;  // left = 2*i + 1 
    int r = 2 * i + 2;

    if (l < NumNodes && PQ[l].priority > PQ[largest].priority)
        largest = l;

    if (r < NumNodes && PQ[r].priority > PQ[largest].priority)
        largest = r;

    if (largest != i) { // If largest is not root we swap the nodes    
        swap(PQ[i], PQ[largest]);
        heapify(largest);
    }
}

void PriorQueue::insert(int value, int priority) {
 // so if numnodes is equal to n, that means that oir priority queue is already full 
if(NumNodes == N){
    std::cout<< "the queue us full man, I cannot instert your element ma friend" << std:: endl; 
    return;
}
PQ[NumNodes].value = value;
PQ[NumNodes].priority = priority;
NumNodes++;
int i = NumNodes-1; 
while (i > 0 && PQ[(i - 1) / 2].priority < PQ[i].priority) {
    swap(PQ[i], PQ[(i-1)/2]);
    i = (i - 1) / 2; 
}
}

void PriorQueue::deleteMax() {
    if (NumNodes == 0) {
        cout << "The queue is empty" << endl;
        return;
    }

    swap(PQ[0], PQ[NumNodes - 1]); // we swap the root with the last node in the queue and then we heapify the root to maintain the heap property
    NumNodes--;  // we decrease the number of nodes because we are deleting the root 
    heapify(0); //
}

void PriorQueue::top() {
    if (NumNodes == 0) {
        cout << "The queue is empty" << endl;
        return;
    }
    else{
    cout << "Top element: " << PQ[0].value << " with priority " << PQ[0].priority << endl;
    }
}

bool PriorQueue::empty() {
   if(NumNodes == 0){
    return true;
   } // if the number of nodes is 0 then the queue is empty
   return false; 
}

int PriorQueue::size() {
    return NumNodes;
}

void PriorQueue::DeleteAll() { // we delete all the nodes in the queue by setting the number of nodes to 0, this effectively deletes all the nodes in the queue because we are not pointing to them anymore
    NumNodes = 0;
}

int main() {
    PriorQueue pq(10);

    pq.insert(10, 3);
    pq.insert(2, 7);
    pq.insert(1, 4);
    pq.insert(5, 1);

    cout << "The size of the queue before delete top is: "<< pq.size() << endl;
    pq.top();
    pq.deleteMax();
    cout << "The size of the queue after delete top is: "<< pq.size() << endl;
    pq.top();

    cout << "The size of the queue before delete all is: "<< pq.size() << endl;
    pq.DeleteAll();
    cout << "The size of the queue after delete all is: "<< pq.size() << endl;

    // if it is we will return 1 if is not we return 0
    cout << "The queue is empty? " << pq.empty() << endl;

    cout << " the time complexity of this is O(log n) because we are using the heapify function that has a time complexity of O(log n) " << endl;

    return 0;
}
