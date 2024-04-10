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
    if (min_tree_ == nullptr) {
        min_tree_ = newNode(median);
        rebalance();
        return;
    }

    if (median <= min_tree_->key) {
        min_tree_ = insert(min_tree_, median);
    } else {
        if (max_tree_ == nullptr)
            max_tree_ = newNode(median);
        else
            max_tree_ = insert(max_tree_, median);
    }

    rebalance();
}

std::vector<int>& myAVLTree::getMediansToPrint() {
    return medians_to_print_;
}

void myAVLTree::rebalance() {
    int balance = height(min_tree_) - height(max_tree_);

    if (balance > 1) {
        max_tree_ = insert(max_tree_, min_tree_->key);
        min_tree_ = removeNode(min_tree_, min_tree_->key);
    } else if (balance < -1) {
        min_tree_ = insert(min_tree_, max_tree_->key);
        max_tree_ = removeNode(max_tree_, max_tree_->key);
    }

    // Update medians_to_print_ based on the current state of the trees
    medians_to_print_.clear();
    if (min_tree_ != nullptr)
        medians_to_print_.push_back(min_tree_->key);
    if (max_tree_ != nullptr)
        medians_to_print_.push_back(max_tree_->key);
    if (min_tree_ != nullptr && max_tree_ != nullptr && min_tree_->key > max_tree_->key)
        std::swap(medians_to_print_[0], medians_to_print_[1]);
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