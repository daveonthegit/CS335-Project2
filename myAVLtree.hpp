//David Xiao
//Project 2 myAVLTree class header

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

//libraries
#include <vector>
#include <iostream>
//listMedian signature
void treeMedian(const std::vector<int>* instructions);

class myAVLTree{
    public:
        //constructor
        myAVLTree();

        //methods
        int popMedian();

        void insert(const int& median);

        std::vector<int>& getMediansToPrint();

    private:
        std::vector<int> medians_to_print_;
        std::list<int> sorted_medians_;
};

// Definition of an AVL tree node
class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
};
// A utility function to get maximum 
// of two integers  
int max(int a, int b)  
{  
    return (a > b)? a : b;  
}  

// Utility function to get the height of the tree
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

/* Helper function that allocates a new node with the given key and
   nullptr left and right pointers. */
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially added at leaf
    return node;
}

// Utility function to right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    // Return new root
    return x;
}

// Utility function to left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, int key) {
    if (node == nullptr)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node; // Unchanged node pointer
}

// Utility function to print preorder traversal of the tree.
void preOrder(Node* root) {
    if (root != nullptr) {
        std::cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

  
#endif