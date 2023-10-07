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

        
        void Insert(int &value) {Insert(value, Root);} //this is a definition of the function Insert, we do it in order to insert a value in the tree
        void InOrder() {InOrder(Root);} // we pass the root to the function InOrder because we want to print the values of the tree in order
        void PreOrder() {PreOrder(Root);} // we pass the root to the function PreOrder because we want to print the values of the tree in pre order
        void PostOrder() {PostOrder(Root);} // we pass the root to the function PostOrder because we want to print the values of the tree in post order 
        void breadth_first_traversal();//this function is used to print the values of the tree in breadth first traversal

        void substituteToMin(Node*&, Node*&); 
        void DeleteNode(int &value) {DeleteNode(value, Root);} // we pass the value and the root to the function DeleteNode because we want to delete the value
        void DeleteBST(Node*&); // if we let Node*& means 

};


//now we define Insert 
void Binary_search_tree::Insert(int &value, Node *&Root) {
    if (Root == NULL) { // if the root is null then we create a new node and we assign the value to the data of the node, null because 
        Root = new Node(value);
    } else if (value < Root->data) { // if the value is less than the data of the root then we call the function Insert and we pass the value and the left of the root
        Insert(value, Root->left);
    } else if (value > Root->data) { // if the value is greater than the data of the root then we call the function Insert and we pass the value and the right of the root
        Insert(value, Root->right);
    } else { // if the value is equal to the data of the root then we print that the value is already in the tree
        cout << "The value " << value << " is already in the tree" << endl;
    }
}

void PreOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        cout << Root->data << " "; // we print the data of the root
        PreOrder(Root->left); // we call the function PreOrder and we pass the left of the root
        PreOrder(Root->right); // we call the function PreOrder and we pass the right of the root
    }
}

void InOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        InOrder(Root->left); // we call the function InOrder and we pass the left of the root
        cout << Root->data << " "; // we print the data of the root
        InOrder(Root->right); // we call the function InOrder and we pass the right of the root
    }
}

void PostOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        PostOrder(Root->left); // we call the function PostOrder and we pass the left of the root
        PostOrder(Root->right); // we call the function PostOrder and we pass the right of the root
        cout << Root->data << " "; // we print the data of the root
    }
}



 
int main(){
    return 0; 
}