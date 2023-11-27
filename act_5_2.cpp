#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>

using namespace std;

// Function to extract IP address and port from log entry
pair<string, int> extract_ip_port(string entry) {
    istringstream iss(entry);
    string month, day, time, ip, port, action;
    iss >> month >> day >> time >> ip;

    // The port is the last part of the IP address
    size_t colonPos = ip.find_last_of(':');
    port = ip.substr(colonPos + 1);
    ip = ip.substr(0, colonPos);

    int portNumber;
    try {
        portNumber = stoi(port);
    } catch (const std::invalid_argument &e) {
        // Handle the case where stoi fails (e.g., non-numeric port)
        cerr << "Error: Invalid port number in entry: " << entry << endl;
        return make_pair("", -1);  // Return an invalid pair
    }

    return make_pair(ip, portNumber);
}

class HashTable {
private:
    int capacity;
    list<pair<int, pair<int, vector<string>>>> *table;

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
    table = new list<pair<int, pair<int, vector<string>>>>[size];
}

HashTable::~HashTable() {
    delete[] table;
}

void HashTable::insertItem(string entry) {
    // Extract IP address and port using the modified function
    auto ip_port = extract_ip_port(entry);
    if (ip_port.second == -1) {
        // Invalid port, skip the entry
        return;
    }

    string ip = ip_port.first;
    int portNumber = ip_port.second;

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

    HashTable h(10); // You may need to adjust the size based on your data

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
