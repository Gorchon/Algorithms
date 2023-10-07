#include <iostream> 
#include <string>
#include <vector>
#include <queue>
#include <stack>


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
    int height(Node*);

    public:
        Binary_search_tree():Root(NULL){}; // constructor of the class Binary_search_tree, we do it in order to initialize the values of the class
        ~Binary_search_tree(){
            DeleteBST(Root); // we call the function DeleteBST to delete the tree
            cout  << "\nDestructor: BST deleted\n" << endl; 
        }; 

        
        void Insert(int &value) {Insert(value, Root);} //this is a definition of the function Insert, we do it in order to insert a value in the tree
        void InOrder() {InOrder(Root);} // we pass the root to the function InOrder because we want to print the values of the tree in order
        void PreOrder() {PreOrder(Root);} // we pass the root to the function PreOrder because we want to print the values of the tree in pre order
        void PostOrder() {PostOrder(Root);} // we pass the root to the function PostOrder because we want to print the values of the tree in post order 
        void breadth_first_traversal();//this function is used to print the values of the tree in breadth first traversal

        void substituteToMin(Node*&, Node*&); 
        void DeleteNode(int &value) {DeleteNode(value, Root);} // we pass the value and the root to the function DeleteNode because we want to delete the value
        void DeleteBST(Node*&); // if we let Node*& means
        int getHeight() { return height(Root); }
         
        void ancestor(int &value); // we pass int &value because & 

        int whatLevelamI(int &value); // we wanto to return -1 if the value is not in the tree, 0 if the value is in the root, 1 if the value is in the first level, 2 if the value is in the second level, etc.
        

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

void Binary_search_tree::PreOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        cout << Root->data << " "; // we print the data of the root
        PreOrder(Root->left); // we call the function PreOrder and we pass the left of the root
        PreOrder(Root->right); // we call the function PreOrder and we pass the right of the root
    }
}

void Binary_search_tree::InOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        InOrder(Root->left); // we call the function InOrder and we pass the left of the root
        cout << Root->data << " "; // we print the data of the root
        InOrder(Root->right); // we call the function InOrder and we pass the right of the root
    }
}

void Binary_search_tree::PostOrder(Node* Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else {
        PostOrder(Root->left); // we call the function PostOrder and we pass the left of the root
        PostOrder(Root->right); // we call the function PostOrder and we pass the right of the root
        cout << Root->data << " "; // we print the data of the root
    }
}

void Binary_search_tree::breadth_first_traversal() {
    if (Root == NULL) { // if the root is null then we return
        return;
    } 
    queue<Node*> Q; // we create a queue of nodes
    Q.push(Root); 

    Node *Aux; 
    while(!Q.empty()){
        Q.push(NULL); 

        Aux = Q.front();
        while(Aux != NULL){
            cout << Aux->data << " ";

            if(Aux->left != NULL){
                Q.push(Aux->left); 
            }
            if(Aux->right != NULL){
                Q.push(Aux->right); 
            }
            Q.pop();
            Aux = Q.front();
        }
        Q.pop();
        cout << endl;
    }
}

void Binary_search_tree::substituteToMin(Node*& aptAux, Node*& aptNode) { //apt means pointer to a node
    if (aptAux->left != NULL) { // if the left of the node is not null then we call the function substituteToMin and we pass the left of the node and the node
        substituteToMin(aptAux->left, aptNode);
    } else { // if the left of the node is null then we assign the data of the node to the data of the aptAux
        aptNode->data = aptAux->data;
        aptNode = aptAux;
        aptAux = aptAux->right;
    }

}


void Binary_search_tree::DeleteNode(int &value, Node*& Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
    } else if (value < Root->data) { // if the value is less than the data of the root then we call the function DeleteNode and we pass the value and the left of the root
        DeleteNode(value, Root->left);
    } else if (value > Root->data) { // if the value is greater than the data of the root then we call the function DeleteNode and we pass the value and the right of the root
        DeleteNode(value, Root->right);
    } else { // if the value is equal to the data of the root then we delete the node
        Node *Aux = Root; // we create a node and we assign the root to the node
        if (Root->left == NULL) { // if the left of the root is null then we assign the right of the root to the root
            Root = Root->right;
        } else if (Root->right == NULL) { // if the right of the root is null then we assign the left of the root to the root
            Root = Root->left;
        } else { // if the left and the right of the root are not null then we call the function substituteToMin and we pass the right of the root and the root
            substituteToMin(Root->right, Aux);
        }
        cout << "The value " << value << " has been deleted" << endl;
        delete Aux; // we delete the node
    }
}


void Binary_search_tree::DeleteBST(Node*& Root) {
    if (Root == NULL) { // if the root is null then we return
        return;
        //we make a post order traversal in order to delete the tree, we could do too a pre order traversal or an in order traversal
    } else {
        DeleteBST(Root->left); // we call the function DeleteBST and we pass the left of the root
        DeleteBST(Root->right); // we call the function DeleteBST and we pass the right of the root
        delete Root; // we delete the root
   }
  
}

int Binary_search_tree::height(Node* Root){
    if(Root == NULL){
        return 0; 
    }else{
        int left_height = height(Root->left); 
        int right_height = height(Root->right); 

        if(left_height > right_height){
            return left_height + 1; 
        }else{
            return right_height + 1; 
        }
    }
}

void Binary_search_tree::ancestor(int &value) {
    if (Root == NULL) {
        return;
    } else {
        stack<Node*> S;
        Node* Aux = Root;
        while (Aux != NULL) {
            S.push(Aux);
            if (value < Aux->data) {
                Aux = Aux->left;
            } else {
                Aux = Aux->right;
            }
        }

        bool found = false;
        cout << "Ancestors of " << value << ": ";
        while (!S.empty()) {
            Aux = S.top();
            if (Aux->data == value) {
                found = true;
            }
            if (found) {
                cout << Aux->data << " ";
            }
            S.pop();
        }
        cout << endl;
    }
}

int Binary_search_tree::whatLevelamI(int &value){
    if(Root == NULL){
        return -1; 
    }else{
        queue<Node*> Q; 
        Q.push(Root); 
        Q.push(NULL); 

        int level = 0; 
        Node* Aux; 
        while(!Q.empty()){
            Aux = Q.front(); 
            Q.pop(); 

            if(Aux == NULL){
                level++; 
                if(!Q.empty()){
                    Q.push(NULL); 
                }
            }else{
                if(Aux->data == value){
                    return level; 
                }
                if(Aux->left != NULL){
                    Q.push(Aux->left); 
                }
                if(Aux->right != NULL){
                    Q.push(Aux->right); 
                }
            }
        }
        return -1; 
    }
};


int main(){
  

    Binary_search_tree BST; // we create a binary search tree

    vector<int> Vector = {47, 60, 22, 12, 6, 13, 41, 20, 52, 16}; 

    for(int i : Vector){
        BST.Insert(i);
    }

    cout << "In order: ";
    BST.InOrder();
    cout << endl;
    cout << "Pre order: ";
    BST.PreOrder();
    cout << endl;
    cout << "Post order: ";
    BST.PostOrder();
    cout << endl;
    cout << "Breadth first traversal: " << endl;
    BST.breadth_first_traversal();
    cout << endl;

    int node = 16;
    BST.DeleteNode(node);
    BST.breadth_first_traversal();
    cout << endl;

    node = 13; 
    BST.DeleteNode(node);
    BST.breadth_first_traversal();
    cout << endl;

    cout << "Height of the tree: " << BST.getHeight() << endl;

    node = 20;
    BST.ancestor(node);
    cout << endl;

    int valueToCheck = 20; // Change this value to one that is still in the tree
    int level = BST.whatLevelamI(valueToCheck);
    if (level == -1) {
        cout << valueToCheck << " not found in the tree." << endl;
    } else {
        cout << valueToCheck << " is at level " << level << endl;
    }

    return 0;

}