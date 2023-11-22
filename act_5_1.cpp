#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>

using namespace std;

class HashTable {
private:
    int capacity;
    list<int>* table;
    int totalCollisions; // New variable to keep track of total collisions

public:
    HashTable(int v) {
        int size = getPrime(v);
        this->capacity = size;
        table = new list<int>[capacity];
        totalCollisions = 0; // Initialize totalCollisions to 0
    }

    ~HashTable() {
        delete[] table;
        cout << "\nDestructor called" << endl;
    }

    bool checkPrime(int n);
    int getPrime(int n);
    void insertItem(int);
    void deleteItem(int);
    int hashFunction(int);
    void displayHash();
};

bool HashTable::checkPrime(int n) {
    if (n == 0 || n == 1) {
        return false;
    }
    int sqr_root = sqrt(n);
    for (int i = 2; i <= sqr_root; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int HashTable::getPrime(int n) {
    if (n % 2 == 0) {
        n++;
    }
    while (!checkPrime(n)) {
        n += 2;
    }
    return n;
}

int HashTable::hashFunction(int key) {
    // Implement a better hash function to reduce collisions
    // to make it more efficient and faster to search and with less collisions I used the division method 
     //return (key % capacity);
    //but If I want to make it even better I can use the multiplication method 
    //return floor(capacity * (key * 0.6180339887 - floor(key * 0.6180339887)));
    //but if i want to make it even better I can use the universal hashing method 
    return floor(capacity * (key * 0.6180339887 - floor(key * 0.6180339887))); // 0.6180339887 is the golden ratio 
}

void HashTable::insertItem(int data) {
    int index = hashFunction(data);

    // Check for collisions
    if (!table[index].empty()) {
        cout << "Collision occurred at index " << index << ". ";
        totalCollisions++;
    }

    table[index].push_back(data);
}

void HashTable::deleteItem(int key) {
    int index = hashFunction(key);
    list<int>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            break;
        }
    }
    if (i != table[index].end()) {
        table[index].erase(i);
    }
}

void HashTable::displayHash() {
    for (int i = 0; i < capacity; i++) {
        cout << "table [" << i << "]";
        for (auto x : table[i]) {
            cout << " --> " << x;
        }
        cout << endl;
    }
    cout << "Total Collisions: " << totalCollisions << endl;
}

int main() {
    int data[] = {231, 321, 212, 321, 433, 262, 321, 521};
    int size = sizeof(data) / sizeof(data[0]);

    HashTable h(size);

    for (int i = 0; i < size; i++) {
        h.insertItem(data[i]);
    }

    h.displayHash();

    cout << "Delete Element" << endl;
    h.deleteItem(231);
    h.displayHash();

    return 0;
}
