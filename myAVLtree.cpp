//David Xiao
//Project 2 myAVLTree class method implementation
// myAVLTree.cpp
#include <chrono>
#include "myAVLTree.hpp"

// Constructor for myAVLTree class
myAVLTree::myAVLTree() {
    medians_to_print_ = std::vector<int>(); // Initialize vector to store medians
    min_tree_; // Initialize min_tree_ as a tree for all elements greater than the median
    max_tree_; // Initialize max_tree_ as a tree for all elements less than the median
    min_size_=0; // Initialize counter for min_tree_
    max_size_=0; // Initialize counter for max_tree_
}


// Function to calculate medians from a sequence of instructions
void treeMedian(const std::vector<int>* instructions){
    // Instantiate a myAVLTree object to use for calculating medians
    myAVLTree avlTree; 
    
    // Start the timer to measure performance
    auto start = std::chrono::high_resolution_clock::now();

    // Iterate through the vector of instructions
    for (auto it = instructions->begin(); it != instructions->end(); ++it){
        int operation = *it;// Dereference iterator and store it into operation
   // If min_tree_ is not empty
        if (!avlTree.min_tree_.isEmpty()){
                // If operation is -1, pop the median and push it back to the medians vector
            if (operation == -1){
                avlTree.medians_to_print_.push_back(avlTree.min_tree_.findMax());
                avlTree.min_tree_.remove(avlTree.min_tree_.findMax());// Remove the rightmost node for the min_tree_ and decrement its size
                avlTree.min_size_--;
            }
            else{ // If operation is any other value
             // If operation is greater than the rightmost node for min_tree_, insert it into max_tree_
                if ((operation) > avlTree.min_tree_.findMax()) 
                {
                    avlTree.max_tree_.insert(operation); 
                    avlTree.max_size_++; // Increment the size of max_tree_
                }
                else{// If operation is less than or equal to the rightmost node for min_tree_, insert it into min_tree_
                    avlTree.min_tree_.insert(operation); 
                    avlTree.min_size_++; // Increment the size of min_tree_
                }
            }
        }
        else{// If min_tree_ is empty, this will be the first node inserted
            avlTree.min_tree_.insert(operation); 
            avlTree.min_size_++; // Increment the size of min_tree_
        }
        // If the size of max_tree_ is greater than the size of min_tree_
        if (avlTree.max_size_ > avlTree.min_size_){ 
                avlTree.min_tree_.insert(avlTree.max_tree_.findMin()); // Insert the leftmost node of max_tree_ into min_tree_ and increment its size
                avlTree.min_size_++;
                avlTree.max_tree_.remove(avlTree.max_tree_.findMin()); // Remove the leftmost node of max_tree_ and decrement its size
                avlTree.max_size_--;
            }
        
        if ((avlTree.min_size_ + avlTree.max_size_) % 2 == 0){ // If the sum of the sizes of min_tree_ and max_tree_ is even
            if (avlTree.min_size_ > avlTree.max_size_){ 
                // If the size of min_tree_ is greater than the size of max_tree_
                avlTree.max_tree_.insert(avlTree.min_tree_.findMax()); // Insert the rightmost node of min_tree_ into max_tree_
                avlTree.max_size_++; // Increment the size of max_tree_
                avlTree.min_tree_.remove(avlTree.min_tree_.findMax()); // Remove the rightmost node of min_tree_ and decrement its size
                avlTree.min_size_--;
            }
        }
        else{ // If the sum of the sizes of min_tree_ and max_tree_ is odd
            // If the size of min_tree_ is greater than the size of max_tree_ plus one
            if (avlTree.min_size_ > (avlTree.max_size_ + 1)){
                avlTree.max_tree_.insert(avlTree.min_tree_.findMax()); // Insert the rightmost node of min_tree_ into max_tree_
                avlTree.max_size_++; // Increment the size of max_tree_
                avlTree.min_tree_.remove(avlTree.min_tree_.findMax()); // Remove the rightmost node of min_tree_ and decrement its size
                avlTree.min_size_--;
            }
        }
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration in milliseconds
    std::chrono::duration<double> duration = end - start;
    //std::cout << "\nTree Completed in: " << duration.count() * 1000 << " milliseconds\n";

    // Print the medians after processing all instructions
    for (const int median : avlTree.medians_to_print_) {
        std::cout << median << " ";
    }
}   
