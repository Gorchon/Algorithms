#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

struct IpNode {
    string ip;
    IpNode* prev;
    IpNode* next;

    IpNode(const string& ipAddress) : ip(ipAddress), prev(nullptr), next(nullptr) {}
};

class IpDoublyLinkedList {
private:
    IpNode* head;
    IpNode* tail;

public:
    IpDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(const string& ipAddress) {
        IpNode* newNode = new IpNode(ipAddress);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void sort() {
        if (!head || !head->next) {
            // Empty list or list with one element, no need to sort
            return;
        }

        bool swapped;
        IpNode* temp;
        do {
            swapped = false;
            IpNode* current = head;

            while (current->next) {
                if (current->ip > current->next->ip) {
                    temp = current->next;
                    current->next = temp->next;
                    if (temp->next) {
                        temp->next->prev = current;
                    } else {
                        tail = current;
                    }
                    temp->prev = current->prev;
                    current->prev = temp;
                    temp->next = current;
                    if (temp->prev) {
                        temp->prev->next = temp;
                    } else {
                        head = temp;
                    }
                    swapped = true;
                } else {
                    current = current->next;
                }
            }
        } while (swapped);
    }

    void display() {
        IpNode* current = head;
        while (current) {
            cout << current->ip << endl;
            current = current->next;
        }
    }

    // function to display the first 10 elements of the list
    void displayFirstTen() {
        IpNode* current = head;
        int count = 0;
        while (current && count < 10) {
            cout << current->ip << endl;
            current = current->next;
            count++;
        }
    }

    // Function to search for IPs in a specified range
    vector<string> searchRange(const string& initialIp, const string& finalIp) {
        vector<string> foundIps;
        IpNode* current = head;

        while (current) {
            if (current->ip >= initialIp && current->ip <= finalIp) {
                foundIps.push_back(current->ip);
            }
            current = current->next;
        }

        return foundIps;
    }

    void deleteList() {
        while (head) {
            IpNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    vector<string> data;

    ifstream inputfile("bitacora.txt");
    if (!inputfile) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    string line;
    while (getline(inputfile, line)) {
        regex ipRegex("\\d+\\.\\d+\\.\\d+\\.\\d+");
        smatch match;
        if (regex_search(line, match, ipRegex)) {
            data.push_back(match[0]);
        }
    }
    inputfile.close();

    IpDoublyLinkedList ipList;
    for (int i = 0; i < data.size(); i++) {
        ipList.append(data[i]);
    }

    ipList.sort();

    string initialIp, finalIp;
    cout << "Enter initial IP: ";
    cin >> initialIp;
    cout << "Enter final IP: ";
    cin >> finalIp;

    vector<string> foundIps = ipList.searchRange(initialIp, finalIp);

    cout << "IP addresses in the specified range:" << endl;
    for (const string& ip : foundIps) {
        cout << ip << endl;
    }

    ipList.deleteList();

    return 0;
}
