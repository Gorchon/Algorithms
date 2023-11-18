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

    void initGraph(int vertices) {
        numVertices = vertices;
        adjList.resize(numVertices);
    }

public:
    Graph(int numVertices) {
        initGraph(numVertices);
    }

    void loadGraph(int source, int destination) {
        adjList[source].push_back(destination);
    }

    void printList() {
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

    void loadData() {
        ifstream inputFile("bitacora.txt");
        if (!inputFile) {
            cerr << "Error opening the file " << endl;
        }

        std::set<int> uniqueElements; // To keep track of unique elements (nodes)

        // Declare integer variables to store the individual IP numbers
        int num1, num2, num3, num4;

        // Read and process each line in the file
        string entry;

        while (std::getline(inputFile, entry)) {
            stringstream SS(entry);
            string sa, ch, sb, sc;
            SS >> sa >> ch >> sb >> sc;

            size_t colonPos = sc.find(':');

            if (colonPos != std::string::npos) {
                // Extract the substring before ':' (excluding ':')
                string newString = sc.substr(0, colonPos);

                // Split the newString by dots
                stringstream splitSS(newString);
                char dot;

                if (splitSS >> num1 >> dot >> num2 >> dot >> num3 >> dot >> num4) {
                    // Update uniqueElements with the nodes from allNodes
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

    void printOutDegreesToFile(const std::string& filename) {
        // Open the output file
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
        outputFile.close(); // Close the output file
    }

    void printTop10() {
        vector<pair<int, int>> outDegreeVector; // Vector of all the out degree values (it is a pair to keep track of the index)

        for (int i = 0; i < numVertices; i++) {
            int outDegree = adjList[i].size();

            outDegreeVector.push_back(make_pair(adjList[i].size(), i)); // Pushes all the number of out degrees in the vector
        }

        // Sort the outDegreeVector by out-degrees in descending order
        std::sort(outDegreeVector.begin(), outDegreeVector.end(), std::greater<>()); // Sorts by amount in

        // Displaying the highest 10 values
        for (int i = 9; i >= 0; i--) {
            cout << "Number " << i + 1 << " has: " << outDegreeVector[i].first << " outgoing nodes. This is node: " << outDegreeVector[i].second << endl;
        }
    };

private:
    int newHighest = 0;
    int currentHighest = 0;
};

int main() {
    Graph g(1000); // Create a Graph instance with an initial number of vertices (0)

    // Load the data from the file
    g.loadData();

    // Print out-degrees to a file named "outdegrees.txt"
    g.printOutDegreesToFile("outdegrees.txt");

    // Print the top 10 outdegree values
    g.printTop10();

    // Boot master is probably located on IP address segment 60

    return 0;
}
