//David Xiao
//Project 2 myAVLTree class method implementation
// myAVLTree.cpp
#include "myAVLTree.hpp"

myAVLTree::myAVLTree() {
    medians_to_print_ = std::vector<int>();
    min_tree_ = nullptr;
    max_tree_ = nullptr;
}

int myAVLTree::popMedian() {
    if (min_tree_ == nullptr)
        throw std::runtime_error("Tree is empty");

    int median = min_tree_->key;
    min_tree_ = removeNode(min_tree_, min_tree_->key);
    rebalance();
    return median;
}
void myAVLTree::insert(const int& median) {
    // Insert into the AVL trees
    insert(max_tree_, median);
    insert(min_tree_, median);

    // Rebalance the trees if necessary
    rebalance();
}
// Insert a key into the AVL tree
void myAVLTree::insert(Node*& root, const int& key) {
    if (root == nullptr) {
        root = newNode(key);
        return;
    }

    if (key < root->key)
        insert(root->left, key);
    else if (key > root->key)
        insert(root->right, key);

    root->height = 1 + std::max(height(root->left), height(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key)
        root = rightRotate(root);

    // Right Right Case
    if (balance < -1 && key > root->right->key)
        root = leftRotate(root);

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

std::vector<int>& myAVLTree::getMediansToPrint() {
    return medians_to_print_;
}

// Rebalance the trees if necessary
void myAVLTree::rebalance() {
    // If the difference in heights of max_tree_ and min_tree_ is more than 1,
    // move the necessary elements between the trees to balance them
    while (std::abs(height(max_tree_) - height(min_tree_)) > 1) {
        if (height(max_tree_) > height(min_tree_)) {
            // Move the maximum value from max_tree_ to min_tree_
            int temp = max_tree_->key;
            max_tree_ = removeNode(max_tree_, temp);
            insert(min_tree_, temp);
        } else {
            // Move the minimum value from min_tree_ to max_tree_
            int temp = min_tree_->key;
            min_tree_ = removeNode(min_tree_, temp);
            insert(max_tree_, temp);
        }
    }
}

void treeMedian(const std::vector<int>* instructions) {
    myAVLTree avlTree;

    for (const int value : *instructions) {
        if (value == -1) {
            avlTree.getMediansToPrint().push_back(avlTree.popMedian());
        } else {
            avlTree.insert(value);
        }
    }

    for (const int median : avlTree.getMediansToPrint()) {
        std::cout << median << " ";
    }
}