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
    PortNode* left;
    PortNode* right;

    PortNode(int p) : port(p), count(0), left(nullptr), right(nullptr) {}

    void insertIP(const string& ip) {
        ips.push_back(ip);
        count++;
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
        Insert(port, Root);
    }
    int getHeight() {
        return height(Root);
    }

    void ReadBitacoraFile(const string& filename);
    void DisplayTopPorts(const string& outputFile, int topCount);

    // Other member functions
};

// Function to read and parse the "bitacora.txt" file
void Binary_search_tree::ReadBitacoraFile(const string& filename) {
    ifstream bitacoraFile(filename);
    if (!bitacoraFile.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    regex portPattern(R"(\b(\d{4})\b)");  // Updated regular expression for 4-digit port numbers

    while (getline(bitacoraFile, line)) {
        smatch match;
        if (regex_search(line, match, portPattern)) {
            int port = stoi(match[1]);  // Use the first capture group
            Insert(port);  // Insert port number into the BST

            // Extract and insert IP addresses into the appropriate node
            size_t pos = line.find(":");
            if (pos != string::npos) {
                string ipAddress = line.substr(pos + 1);
                PortNode* node = Root;  // Start from the root

                // Find the node with the corresponding port number
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

                // Insert the IP address into the node
                node->insertIP(ipAddress);
            }
        }
    }

    bitacoraFile.close();
}

// Function to display the top ports and their counts to an output file
void Binary_search_tree::DisplayTopPorts(const string& outputFile, int topCount) {
    // Use a map to store the ports and their total access counts
    map<int, PortNode*> portNodes;

    // Helper function to traverse the BST and store port nodes
    function<void(PortNode*)> traverse = [&](PortNode* node) {
        if (node) {
            portNodes[node->port] = node;
            traverse(node->left);
            traverse(node->right);
        }
    };

    traverse(Root);

    // Create a vector of pairs (port, count) for sorting
    vector<pair<int, PortNode*>> sortedPorts(portNodes.begin(), portNodes.end());

    // Sort the ports in descending order of count
    sort(sortedPorts.begin(), sortedPorts.end(),
         [](const pair<int, PortNode*>& a, const pair<int, PortNode*>& b) {
             return a.second->count > b.second->count;
         });

    // Write the top ports and their counts to the output file
    ofstream output(outputFile);
    if (output.is_open()) {
        for (int i = 0; i < topCount && i < sortedPorts.size(); i++) {
            int port = sortedPorts[i].first;
            PortNode* portNode = sortedPorts[i].second;

            output << "Port: " << port << " Counter: " << portNode->count << " times\n";

            // Write IP addresses for the top port
            for (const string& ip : portNode->ips) { 
                output << "   IP: " << ip << "\n"; //here we display the IP 
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