//David Xiao
//Project 2 myAVLTree class method implementation
#include "myAVLTree.hpp"
#include <algorithm>

// Constructor initializes the class's data structures
myAVLTree::myAVLTree(){
    // Initialize medians_to_print_ as an empty vector and sorted_medians_ as an empty list
    medians_to_print_ = std::vector<int>();
    sorted_medians_ = std::list<int>();
}

// Accessor for the vector holding medians to print
std::vector<int>& myAVLTree::getMediansToPrint(){
    return medians_to_print_;
}

// Removes and returns the median from the sorted list
int myAVLTree::popMedian(){
    // Calculate the index of the median
    int medianIndex = sorted_medians_.size() / 2;
    int median;

    // Handle even and odd number of elements differently
    if (sorted_medians_.size() % 2 == 0){
        // For even, choose the lower median
        auto it = std::next(sorted_medians_.begin(), medianIndex - 1);
        median = *it;
        // Remove the chosen median from the list
        sorted_medians_.erase(it);
    } else {
        // For odd, the median is at the central index
        auto it = std::next(sorted_medians_.begin(), medianIndex);
        median = *it;
        // Remove the median from the list
        sorted_medians_.erase(it);
    }
    return median;
}

// Inserts a value into the list while maintaining sorted order
void myAVLTree::insert(const int& median){
    // Find the correct position for the new value to keep the list sorted
    auto it = std::lower_bound(sorted_medians_.begin(), sorted_medians_.end(), median);
    // Insert the value at the determined position
    sorted_medians_.insert(it, median);
}

// Function to calculate medians from a sequence of instructions
void treeMedian(const std::vector<int>* instructions){
    myAVLTree aTree;

    // Process each instruction in the vector
    for (const int value : *instructions){
        if (value == -1){
            // If instruction is -1, calculate the median and save it for output
            aTree.getMediansToPrint().push_back(aTree.popMedian());
        } else {
            // Insert the value into the AVL tree
            aTree.insert(value);
        }
    }

    // Print the calculated medians after processing all instructions
    for (const int median : aTree.getMediansToPrint()){
        std::cout << median << " ";
    }
}