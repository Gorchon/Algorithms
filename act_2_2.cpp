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
    PriorQueue(int size) { //this is a constructor of the class PriorQueue, we do it in order to initialize the values of the class
        N = size; // we assign the value of size to N because it is the size of the array
        PQ = new Node[size]; // we create a new array of type Node with the size of N to store the values of the queue
        NumNodes = -1; // we assign the value of -1 to NumNodes because it is the number of nodes in the queue and we start with -1 because the first element is in the position 0 and -1 is 
    }

    ~PriorQueue() {
        delete[] PQ;
    }

   void Enqueue(int value, int priority) {
    if (NumNodes == N - 1) { 
        cout << "The queue is full" << "The element " << value << " cannot be added" << endl;
        return;
    }
    // Increase the size before inserting the new element
    NumNodes ++;

    // Insert the new element with its priority 
    PQ[NumNodes].priority = priority; 
    PQ[NumNodes].value = value;
}

void Update(int value, int newPriority, int newValue) {
    if (NumNodes == -1) {
        cout << "The queue is empty" << endl;
        return;
    }

    bool found = false; // Use a flag to track whether the element was found

    for (int i = 0; i <= NumNodes; i++) {
        if (PQ[i].value == value) {
            PQ[i].priority = newPriority;
            PQ[i].value = newValue;
            found = true; // Element found, set the flag to true
        }
    }

    if (found == false) {
        cout << "The element " << value << " is not in the queue so it cannot be updated" << endl;
    }
}


 

    int Peek() {
        if (NumNodes == -1) {
            cout << "The queue is empty" << endl;
            return -1; // Return some suitable default value or handle the empty queue case as needed.
            }
            int highestPriority = PQ[0].priority; // PQ is the array of type Node, we create a variable of type int to store the value of the priority of the element in the position 0
            int highestPriorityIndex = 0;

    for (int i = 0; i <= NumNodes; i++) {
        if (PQ[i].priority > highestPriority) { //PQ is
            highestPriority = PQ[i].priority;
            highestPriorityIndex = i; // this is the index of the element with the highest priority and is updated every time we find an element with a higher priority

        }
    } 
    //now we return the index 
    return highestPriorityIndex; 
     
    }



    void Display() {
        if (NumNodes == -1) {
            cout << "The queue is empty" << endl;
            return;
        }
        cout << "Elements in the queue: "<< endl;
        for(int i = 0; i < N; i++){
            cout << "Value " << PQ[i].value << " ";
            cout << "Priority of: " << PQ[i].priority << " and the index is: " << i << endl;

        }

    }
    void Display_by_index(int idx) {
        cout << "Index with priority: " << idx << " with a value: " << PQ[idx].value << " and a priority of:" << PQ[idx].priority<< endl;
    }
    void Dequeue() {
    if (NumNodes == -1) {
        cout << "The queue is empty" << endl;
        return;
    }

    // Find the index of the element with the highest priority
    int highestPriorityIndex = Peek();

    // Shift all elements after the highest priority element one position to the left
    for (int i = highestPriorityIndex; i < NumNodes; i++) {
        PQ[i] = PQ[i + 1]; // basically we are moving the element with the highest priority to the end of the queue, and then we decrease the number of nodes in the queue
    }

    // Decrease the number of nodes in the queue
    NumNodes--; // if i do not do this the element will be there but it will not be displayed because the number of nodes is the one that is displayed in the display function
   N--;
}

};

int main() {
    // Usage example
    PriorQueue pq(5);
   
    pq.Enqueue(5, 7);
    pq.Enqueue(8, 1);
    pq.Enqueue(3, 3);
    pq.Enqueue(1, 1);
    pq.Enqueue(2, 2);
    pq.Display();
    cout << "" << endl;
    cout << "here we peek" << endl;
    pq.Display_by_index(pq.Peek());
     cout << "" << endl;

    cout << "Enter the element to update" << endl;
    int value;
    cin >> value;
    cout << "Enter the new priority and the new value" << endl; 
    int newPriority, newValue;
    cin >> newPriority >> newValue;
    pq.Update(value, newPriority, newValue);
    pq.Display();

    cout << "" << endl; 
    cout << "here we dequeue two elements" << endl;
    pq.Dequeue();
    pq.Dequeue(); 
    pq.Display();

    return 0;
}
