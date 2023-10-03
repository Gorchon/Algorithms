#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


using namespace std;

struct LogEntry {
    string line;
    string ip;

    LogEntry(const string& logLine) : line(logLine) {
        regex ipRegex("\\b\\d+\\.\\d+\\.\\d+\\.\\d+\\b");
        smatch match;
        if (regex_search(logLine, match, ipRegex)) {
            ip = match[0];
        } else {
            ip = "";
        }
    }
};

struct IpNode {
    LogEntry logEntry;
    IpNode* prev;
    IpNode* next;

    IpNode(const LogEntry& entry) : logEntry(entry), prev(nullptr), next(nullptr) {}
};

class IpDoublyLinkedList {
private:
    IpNode* head;
    IpNode* tail;

public:
    IpDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(const LogEntry& entry) {
        IpNode* newNode = new IpNode(entry);
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
            return;
        }

        bool swapped;
        IpNode* temp;
        do {
            swapped = false;
            IpNode* current = head;

            while (current->next) {
                if (current->logEntry.ip > current->next->logEntry.ip) {
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

    vector<LogEntry> searchRange(const string& initialIp, const string& finalIp) {
        vector<LogEntry> foundEntries;
        IpNode* current = head;

        while (current) {
            string ip = current->logEntry.ip;
            if (ip >= initialIp && ip <= finalIp) {
                foundEntries.push_back(current->logEntry);
            }
            current = current->next;
        }

        return foundEntries;
    }

    void deleteList() {
        while (head) {
            IpNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

bool compareEntries(const LogEntry& entry1, const LogEntry& entry2) {
    return entry1.ip < entry2.ip;
}

int main() {
    vector<LogEntry> logEntries;

    ifstream inputfile("bitacora.txt");
    if (!inputfile) {
        cerr << "Error al abrir el archivo" << endl;
        return 1;
    }

    string line;
    while (getline(inputfile, line)) {
        logEntries.emplace_back(line);
    }
    inputfile.close();

    IpDoublyLinkedList ipList;
    for (const LogEntry& entry : logEntries) {
        ipList.append(entry);
    }

    ipList.sort();

    string initialIp, finalIp;
    cout << "Enter initial IP: ";
    cin >> initialIp;
    cout << "Enter final IP: ";
    cin >> finalIp;

    vector<LogEntry> foundEntries = ipList.searchRange(initialIp, finalIp);

    ofstream outputFile("sorted_ips.txt");
    if (!outputFile) {
        cerr << "Error al abrir el archivo de salida" << endl;
        return 1;
    }

    for (const LogEntry& entry : foundEntries) {
        outputFile << entry.line << endl;
    }

    outputFile.close();

    cout << "Sorted log entries by IP addresses written to sorted_ips.txt." << endl;

    ipList.deleteList();

    return 0;
}
