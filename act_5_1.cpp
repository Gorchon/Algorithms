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
    int totalCollisions;

public:
    HashTable(int v) {
        int size = getPrime(v);
        this->capacity = size;
        table = new list<int>[capacity];
        totalCollisions = 0;
    }

    ~HashTable() {
        delete[] table;
        cout << "\nDestructor called" << endl;
    }

    bool checkPrime(int n);
    int getPrime(int n);
    int hashFunction(int key);
    void insertItem(int data);
    void insertItemByOpenAddressing(int data);
    void deleteItem(int key);
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
    double A = 0.6180339887;
    double hashValue = floor(capacity * (key * A - floor(key * A)));
    return static_cast<int>(hashValue) % capacity;
}

void HashTable::insertItemByOpenAddressing(int data) {
    int index = hashFunction(data);

    // Check for collisions using quadratic probing
    int i = 1;
    while (!table[index].empty()) {
        if(totalCollisions == 0){
            totalCollisions++;
        }  
        
        index = (index + i * i) % capacity; 
        i++;
    }

    table[index].push_back(data);
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
    HashTable h2(size);

    for (int i = 0; i < size; i++) {
        h.insertItem(data[i]);
    }
    for (int i = 0; i < size; i++) {
        h2.insertItemByOpenAddressing(data[i]);
    }
    cout << "\nUsing chaining:" << endl;
    h.displayHash();
    cout << "\nOpen Addressing Quadratic problem resoltion:" << endl;
    h2.displayHash();

    cout << "Delete Element" << endl;

    return 0;
}
