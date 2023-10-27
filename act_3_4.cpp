#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <map>
#include <regex>

using namespace std;


// Binary Search Tree (BST) node structure
struct PortNode {
    int port;
    int count;
    vector<string> ips;
    vector<string> lines; // Add a vector to store entire lines
    PortNode* left;
    PortNode* right;

    PortNode(int p) : port(p), count(0), left(nullptr), right(nullptr) {}

    void insertIP(const string& ip) {
        ips.push_back(ip);
        count++;
    }

    void insertLine(const string& line) { // Function to insert entire lines
        lines.push_back(line);
    }
};


class Binary_search_tree {
private:
    PortNode* Root;

    // Functions
    void Insert(int, PortNode*&);
    void InOrder(PortNode*, ofstream&);
    void PreOrder(PortNode*, ofstream&);
    void PostOrder(PortNode*, ofstream&);
    int height(PortNode*);

    // Declaration for the DeleteBST function
    void DeleteBST(PortNode*&);

public:
    Binary_search_tree() : Root(nullptr) {};
    ~Binary_search_tree() {
        DeleteBST(Root);
        cout << "\nDestructor: BST deleted\n" << endl;
    }

    void Insert(int port) { 
        Insert(port, Root); //here we call the insert function to insert the port number into the BST, these two functions are in the private section
    }
    int getHeight() {
        return height(Root);
    }

    void ReadBitacoraFile(const string& filename);
    void DisplayTopPorts(const string& outputFile, int topCount);

    // Other member functions
};

void Binary_search_tree::ReadBitacoraFile(const string& filename) {
    ifstream bitacoraFile(filename);
    if (!bitacoraFile.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    regex portPattern(R"(\b(\d{4})\b)");

    while (getline(bitacoraFile, line)) {
        smatch match;
        if (regex_search(line, match, portPattern)) {
            int port = stoi(match[1]);
            Insert(port);

            size_t pos = line.find(":");
            if (pos != string::npos) {
                string ipAddress = line.substr(pos + 1);
                PortNode* node = Root;

                while (node->port != port) {
                    if (port < node->port) {
                        if (node->left == nullptr) {
                            node->left = new PortNode(port);
                        }
                        node = node->left;
                    } else {
                        if (node->right == nullptr) {
                            node->right = new PortNode(port);
                        }
                        node = node->right;
                    }
                }

                node->insertIP(ipAddress);
                node->insertLine(line); // Insert the entire line
            }
        }
    }

    bitacoraFile.close();
}


// Function to display the top ports and their counts to an output file
void Binary_search_tree::DisplayTopPorts(const string& outputFile, int topCount) {
    map<int, PortNode*> portNodes;

    function<void(PortNode*)> traverse = [&](PortNode* node) {
        if (node) {
            portNodes[node->port] = node;
            traverse(node->left);
            traverse(node->right);
        }
    };

    traverse(Root);

    vector<pair<int, PortNode*>> sortedPorts(portNodes.begin(), portNodes.end());

    sort(sortedPorts.begin(), sortedPorts.end(),
         [](const pair<int, PortNode*>& a, const pair<int, PortNode*>& b) {
             return a.second->count > b.second->count;
         });

    ofstream output(outputFile);
    if (output.is_open()) {
        for (int i = 0; i < topCount && i < sortedPorts.size(); i++) {
            int port = sortedPorts[i].first;
            PortNode* portNode = sortedPorts[i].second;

            output << "Port: " << port << " Counter: " << portNode->count << " times\n";

            // Write entire lines and IP addresses for the top port
            for (size_t j = 0; j < portNode->lines.size(); j++) {
                output << "IP --> " << portNode->lines[j] << "\n";
               // output << "   IP: " << portNode->ips[j] << "\n";
            }

            output << "\n";
        }

        output.close();
    } else {
        cout << "Error: Unable to create output file." << endl;
    }
}


// Function to insert a port into the BST
void Binary_search_tree::Insert(int port, PortNode*& node) {
    if (node == nullptr) {
        node = new PortNode(port);
    } else if (port < node->port) {
        Insert(port, node->left);
    } else if (port > node->port) {
        Insert(port, node->right);
    }
}

// Function to delete the BST
void Binary_search_tree::DeleteBST(PortNode*& node) {
    if (node == nullptr) {
        return;
    } else {
        DeleteBST(node->left);
        DeleteBST(node->right);
        delete node;
    }
}

int main() {
    Binary_search_tree BST;

    // Read and parse "bitacora.txt" file
    BST.ReadBitacoraFile("bitacora.txt");

    // Display the top 5 ports and their counts
    BST.DisplayTopPorts("top_ports.txt", 5);

    return 0;
}

