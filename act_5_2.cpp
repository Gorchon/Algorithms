#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>

using namespace std;

class HashTable {
private:
    int capacity;
    list<pair<int, pair<int, vector<string>>> >* table;

public:
    HashTable(int v);
    ~HashTable();

    bool checkPrime(int n);
    int getPrime(int n);

    void insertItem(string entry);
    void displayTopPorts();
    int hashFunction(int key);
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
    return (key % capacity);
}

HashTable::HashTable(int v) {
    int size = getPrime(v);
    this->capacity = size;
    table = new list<pair<int, pair<int, vector<string>>> >[size];
}

HashTable::~HashTable() {
    delete[] table;
}

void HashTable::insertItem(string entry) {
    // Parse the entry and extract the port number
    istringstream iss(entry);
    string month, day, time, ip, port, action;
    iss >> month >> day >> time >> ip >> port >> action;

    int portNumber = stoi(port);

    int index = hashFunction(portNumber);

    // Check if the port is already in the table
    for (auto &item : table[index]) {
        if (item.first == portNumber) {
            // Update the existing entry
            item.second.first++; // Increase the total number of accesses
            item.second.second.push_back(entry); // Add the bitacora entry
            return;
        }
    }

    // If not found, insert a new entry
    vector<string> bitacoraEntries{entry};
    table[index].emplace_back(portNumber, make_pair(1, bitacoraEntries));
}

void HashTable::displayTopPorts() {
    vector<pair<int, int>> portAccesses; // pair of port and total accesses

    // Collect the total accesses for each port
    for (int i = 0; i < capacity; i++) {
        for (auto &item : table[i]) {
            portAccesses.push_back(make_pair(item.first, item.second.first));
        }
    }

    // Sort the ports based on total accesses in descending order
    sort(portAccesses.begin(), portAccesses.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.second > rhs.second;
    });

    // Display the top 5 ports
    cout << "Top 5 Ports with Most Accesses:\n";
    for (int i = 0; i < min(5, static_cast<int>(portAccesses.size())); i++) {
        cout << "Port: " << portAccesses[i].first << " Counter: " << portAccesses[i].second << " times\n";
        cout << "IP --> ";
        for (const auto &entry : table[hashFunction(portAccesses[i].first)]) {
            if (entry.first == portAccesses[i].first) {
                for (const auto &bitacoraEntry : entry.second.second) {
                    cout << bitacoraEntry << '\n';
                }
            }
        }
    }
}

void HashTable::displayHash() {
    for (int i = 0; i < capacity; i++) {
        cout << "table [" << i << "]";
        for (auto &item : table[i]) {
            cout << " --> " << item.first << " (Total Accesses: " << item.second.first << ")";
        }
        cout << endl;
    }
}

int main() {
    ifstream inFile("bitacora.txt");
    if (!inFile) {
        cerr << "Error: Unable to open the file.\n";
        return 1;
    }

    HashTable h(100); // You may need to adjust the size based on your data

    string line;
    while (getline(inFile, line)) {
        h.insertItem(line);
    }

    // Display the entire hash table
    h.displayHash();

    // Display the top 5 ports with the most accesses
    h.displayTopPorts();

    inFile.close();

    return 0;
}
