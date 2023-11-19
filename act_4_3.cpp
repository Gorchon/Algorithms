#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <string>
#include <array>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<list<int>> adjList;
    int numVertices;

    void initGraph(int vertices);

public:
    Graph(int numVertices);

    void loadGraph(int source, int destination);

    void printList();

    void loadData();

    void printOutDegreesToFile(const std::string& filename);

    void printTop10();

    vector<string> BootMaster(const std::string& outputFilename);  // Updated function signature

public:
    int newHighest = 0;  // Made public for access in main
    int currentHighest = 0;
};

// Function implementations...
void Graph::initGraph(int vertices) { // here we are initializing the graph
    numVertices = vertices;
    adjList.resize(numVertices);
}

Graph::Graph(int numVertices) {
    initGraph(numVertices);
}

void Graph::loadGraph(int source, int destination) {
    adjList[source].push_back(destination); // here we are loading the graph with the source and destination
}

void Graph::printList() {  // this function prints the list of the graph
    for (int i = 0; i < numVertices; i++) {
        if (!adjList[i].empty()) {
            cout << "Vertex " << i << ":";
            for (int j : adjList[i]) {
                cout << " -> " << j;
            }
            cout << "\n";
        }
    }
}

void Graph::loadData() {
    ifstream inputFile("bitacora.txt");
    if (!inputFile) {
        cerr << "Error opening the file " << endl;
    }

    std::set<int> uniqueElements;

    int num1, num2, num3, num4;

    string entry;
    while (std::getline(inputFile, entry)) {
        stringstream SS(entry);
        string sa, ch, sb, sc;
        SS >> sa >> ch >> sb >> sc;

        size_t colonPos = sc.find(':');

        if (colonPos != std::string::npos) {
            string newString = sc.substr(0, colonPos);

            stringstream splitSS(newString);
            char dot;

            if (splitSS >> num1 >> dot >> num2 >> dot >> num3 >> dot >> num4) {
                uniqueElements.insert(num1);
                uniqueElements.insert(num2);
                uniqueElements.insert(num3);
                uniqueElements.insert(num4);

                loadGraph(num1, num2);
                loadGraph(num2, num3);
                loadGraph(num3, num4);

            } else {
                std::cout << "Invalid IP format" << std::endl;
            }
        } else {
            std::cout << "Colon not found in: " << sc << std::endl;
        }
    }
}

void Graph::printOutDegreesToFile(const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile) {
        cerr << "Error opening the output file " << filename << endl;
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        int outDegree = adjList[i].size();
        outputFile << "Out-degree of Vertex " << i << ": " << outDegree << "\n";
    }

    cout << "Out-degrees written to file: " << filename << "\n";
    outputFile.close();
}

void Graph::printTop10() {
    vector<pair<int, int>> outDegreeVector;

    for (int i = 0; i < numVertices; i++) {
        int outDegree = adjList[i].size();

        outDegreeVector.push_back(make_pair(adjList[i].size(), i));
    }

    std::sort(outDegreeVector.begin(), outDegreeVector.end(), std::greater<>());

    for (int i = 9; i >= 0; i--) {
        cout << "Number " << i + 1 << " has: " << outDegreeVector[i].first << " outgoing nodes. This is node: " << outDegreeVector[i].second << endl;
    }
}

vector<string> Graph::BootMaster(const std::string& outputFilename) {
    vector<string> linesWithBootMaster;

    for (int i = 0; i < numVertices; i++) {
        int outDegree = adjList[i].size();

        if (outDegree > currentHighest) {
            currentHighest = outDegree;
            newHighest = i;
        }
    }

    ifstream inputFile("bitacora.txt");
    if (!inputFile) {
        cerr << "Error opening the file " << endl;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error opening the output file " << outputFilename << endl;
    }

    string entry;
    while (std::getline(inputFile, entry)) {
        stringstream SS(entry);
        string sa, ch, sb, sc;
        SS >> sa >> ch >> sb >> sc;

        size_t colonPos = sc.find(':');

        if (colonPos != std::string::npos) {
            string newString = sc.substr(0, colonPos);

            stringstream splitSS(newString);
            char dot;

            int num1, num2, num3, num4;
            if (splitSS >> num1 >> dot >> num2 >> dot >> num3 >> dot >> num4) {
                if (num1 == newHighest || num2 == newHighest || num3 == newHighest || num4 == newHighest) {
                    linesWithBootMaster.push_back(entry);
                    outputFile << entry << "\n";
                }
            } else {
                std::cout << "Invalid IP format" << std::endl;
            }
        } else {
            std::cout << "Colon not found in: " << sc << std::endl;
        }
    }

    return linesWithBootMaster;
}

int main() {
    Graph g(1000);

    g.loadData();
    g.printOutDegreesToFile("outdegrees.txt");
    g.printTop10();

    vector<string> bootMasterLines = g.BootMaster("bootmaster_lines.txt");
    cout << "\nLines with BootMaster (Node " << g.newHighest << ") written to bootmaster_lines.txt:\n";
    for (const string& line : bootMasterLines) {
        cout << line << endl;
    }

    return 0;
}
