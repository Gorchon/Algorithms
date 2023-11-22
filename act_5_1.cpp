#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>


using namespace std;

class HashTable{
private:
    int capacity;
    list<int>* table;

public:

    HashTable(int v){
        int size = getPrime(v); // Get the prime number
        this -> capacity = size; 
        table = new list<int>[capacity]; // Create a table of size capacity and initialize all slots with 0 
    }

    ~HashTable(){ // the destructor is called when the object is destroyed, and can't be called explicitly like the constructor . The object is destroyed when the program ends
        delete[] table; // Deallocate the array itself
        cout << "\nDestructor called" << endl;
    }

    bool checkPrime(int n);
    int getPrime(int n);

    void insertItem(int); // Implement item insertion
    void deleteItem(int); // Implement item deletion
    int hashFunction(int); // Implement hash function
    void displayHash(); // Implement hash table display

}; 

bool HashTable::checkPrime(int n) {
    if( n == 0 || n == 1) {
        return false;
    }
    int sqr_root = sqrt(n);
    for(int i = 2; i <= sqr_root; i++) {
        if(n % i == 0) {
            return false;
        }
    }
    return true;
}

int HashTable::getPrime(int n) {
    if(n % 2 == 0) {
        n++;
    }
    while(!checkPrime(n)) { //checkprime is a function that returns true if the number is prime
        n += 2;
    }
    return n;
}

int HashTable::hashFunction(int key) {
    return (key % capacity);
}
void HashTable::insertItem(int data) {
    int index = hashFunction(data);
    table[index].push_back(data);
}

void HashTable::deleteItem(int key) {
    int index = hashFunction(key);
    list<int>::iterator i;
    for(i = table[index].begin(); i != table[index].end(); i++) {
        if(*i == key) { 
            break;
        }
    }
    if(i != table[index].end()) {
        table[index].erase(i);
    }
}

void HashTable::displayHash() { 
    for(int i = 0; i < capacity; i++) {
        cout << "table [" << i << "]";
        for (auto x : table[i]) {
            cout << " --> " << x;
        }
        cout << endl;
    }
}

int main() {
    int data[] = { 231, 321, 212, 321, 433, 262};
    int size = sizeof(data) / sizeof(data[0]); 

    HashTable h(size);

    for(int i = 0; i < size; i++) {
        h.insertItem(data[i]);
    }

    h.displayHash();

    cout << "Delete Element" << endl;
    h.deleteItem(231);
    h.displayHash();

    return 0;
}