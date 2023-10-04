#include <iostream> 
#include <string>
#include <vector>

using namespace std;

// implementig a BST 
// first the node struct for the bst 
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {} // constructor of the struct Node, we do it in order to initialize the values of the struct
};

class Binary_search_tree {
    private: 
    Node *Root; 

    //Functions 
    void Insert(int&, Node*&); // Node*& means that we are passing the pointer by reference, this means that we are passing the address of the pointer and not the value of the pointer
    void InOrder(Node*); // this function is used to print the values of the tree in order
    void PreOrder(Node*); // this function is used to print the values of the tree in pre order
    void PostOrder(Node*); // this function is used to print the values of the tree in post order
    void DeleteNode(int&, Node*&); // we pass two values one is the value of the node that we want to delete and the other is the node that we want to delete for example if we want to delete the root then we pass the value of the root and the root

    public:
        Binary_search_tree():Root(NULL){}; // constructor of the class Binary_search_tree, we do it in order to initialize the values of the class
        ~Binary_search_tree(){
            DeleteBST(Root); // we call the function DeleteBST to delete the tree
            cout  << "\nThe tree has been deleted\n" << endl; 
        }; 

        void DeleteBST(Node*); // this function is used to delete the tree


};