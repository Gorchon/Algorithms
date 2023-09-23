#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Doubly linked list node
struct Node { 
    int data;
    Node* prev;
    Node* next;
    
    Node(int val) : data(val), prev(nullptr), next(nullptr) {} // this is a constructor of the struct Node, we do it in order to initialize the values of the struct
};

class DoubleLinkedList{
private:
    Node* head; 
    Node* tail; 

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {} //we need this constructor to initialize the values of the class, this in order to avoid errors
    // Function to add a new node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode; // we assign the value of newNode to head and tail because it is the first element
        } else { 
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Function to add a new node at the beginning of the list
    void prepend(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Function to delete a node by its value from the list
    void deleteNode(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    head = current->next;
                    if (head)
                        head->prev = nullptr;
                } else if (current == tail) {
                    tail = current->prev;
                    if (tail)
                        tail->next = nullptr;
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    // Function to display the elements of the list
    void display() { //this function works by printing the values of the list this is do it by using the pointer current, current is 
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    void search(int value){
        Node* current = head;
        while (current) {
            if (current->data == value) {
                cout << "The value " << value << " is in the list" << endl;
                cout << "The memory direction is equal to:" <<current<< endl;
                return;
            }
            current = current->next;
        }
        cout << "The value " << value << " is not in the list" << endl;
    }

    Node* sort(){
        Node* current = head , *temp = nullptr;
        while (current != NULL) {
            temp = current->next;
            while (temp != NULL) {
                if (current->data > temp->data) {
                    int aux = current->data;
                    current->data = temp->data;
                    temp->data = aux;
                }
                temp = temp->next; 
            }
            current = current->next;

        }
        return head;
    }

    Node* update(int value, int newValue){
        Node* current = head;
        while (current) {
            if (current->data == value) {
                current->data = newValue;
                cout << "The value " << value << " has been updated to " << newValue << endl;
                //to sort we call the function sort
                sort();
                return head;
            }
            current = current->next;
        }
        cout << "The value " << value << " is not in the list" << endl;
        return head;
    }
  
   //now we create a delete function that deletes the entire list
    void deleteList(){
        Node* current = head;
        while (current) {
            head = current->next;
            delete current;
            current = head;
        }
        cout << "The list has been deleted" << endl;
    }
    Node* getHead() { return head; }
    Node* getTail() { return tail; }

};


int main() {
    system("cls"); //this is to clear the console
    DoubleLinkedList myList;
    int option, value, newValue;
    while(true){
        cout << "1. Append" << endl;
        cout << "2. Prepend" << endl;
        cout << "3. Delete" << endl;
        cout << "4. Display" << endl;
        cout << "5. Search" << endl;
        cout << "6. Update" << endl;
        cout << "7. Delete List" << endl;
        cout << "8. Exit" << endl;
        cout << "Select an option: ";
        cin >> option;
        
        switch (option){ //switch is a conditional structure that works by comparing the value of the variable option with the cases, if the value of option is equal to the case then the code inside the case is executed
            case 1:
                cout << "Enter a value: ";
                cin >> value;
                myList.append(value);
                break;
            case 2:
                cout << "Enter a value: ";
                cin >> value;
                myList.prepend(value);
                break;
            case 3:
                cout << "Enter a value: ";
                cin >> value;
                myList.deleteNode(value);
                break;
            case 4:
                cout << "The list is: ";
                myList.display();

                break;
            case 5:
                cout << "Enter a value: ";
                cin >> value;
                myList.search(value);
                break;
            case 6:
                cout << "Enter a value: ";
                cin >> value;
                cout << "Enter a new value: ";
                cin >> newValue;
                myList.update(value, newValue);
                break;
            case 7:
                myList.deleteList();
                break;
            case 8:
             //change to false 
                return 0;
                
                break;
            default:
                cout << "Invalid option" << endl;
                break;
        }
        
    }

    

    return 0;

}
