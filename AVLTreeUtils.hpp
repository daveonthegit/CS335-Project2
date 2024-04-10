#ifndef AVLTREEUTILS_HPP
#define AVLTREEUTILS_HPP

#include <iostream>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b);
int height(Node* N);
Node* newNode(int key);
Node* rightRotate(Node* y);
Node* leftRotate(Node* x);
int getBalance(Node* N);
Node* insert(Node* node, int key);
Node* removeNode(Node* root, int key);
void preOrder(Node* root);

#endif