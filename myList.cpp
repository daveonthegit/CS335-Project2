// David Xiao
// Project 2: Implementation of myList class methods

// Including necessary libraries
#include <list>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "myList.hpp"

// Function to compute medians from a sequence of instructions
void listMedian(const std::vector<int>* instructions){
    // Initialize myList object for median calculations
    myList temp_list;
    
    // Start timing the execution
    auto start = std::chrono::high_resolution_clock::now();

    // Iterate through each instruction in the vector
    for (const int value : *instructions){
        if (value == -1) {
            // If instruction is -1, extract the median and store for later
            temp_list.getMediansToPrint().push_back(temp_list.popMedian());
        } else {
            // Insert the value into the list in sorted order
            temp_list.insert(value);
        }
    }

    // Stop the timer to measure the total execution time
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate execution duration in milliseconds
    std::chrono::duration<double> duration = end - start;
    std::cout << "\nList Completed in: " << duration.count() * 1000 << " milliseconds\n";

    // Print the calculated medians after processing all instructions
    for (const int median : temp_list.getMediansToPrint()){
        std::cout << median << " ";
    }
}

// Constructor initializes the class's data structures
myList::myList(){
    // Explicitly initialize medians_to_print_ as an empty vector
    // and sorted_medians_ as an empty list
    medians_to_print_ = std::vector<int>();
    sorted_medians_ = std::list<int>();
}

// Getter for the mediansToPrint vector
std::vector<int>& myList::getMediansToPrint(){
    return medians_to_print_;
}

// Extracts and removes the current median from the list
int myList::popMedian(){
    // Determine the median's index based on current list size
    int medianIndex = sorted_medians_.size() / 2;
    int median;

    // Handle the case for even number of elements differently than odd
    if (sorted_medians_.size() % 2 == 0) {
        auto it = sorted_medians_.begin();
        std::advance(it, medianIndex - 1); // Move iterator to the median position
        median = *it; // Retrieve the median value
        sorted_medians_.erase(it); // Remove the median from the list
    } else {
        auto it = sorted_medians_.begin();
        std::advance(it, medianIndex); // For odd, median is directly at medianIndex
        median = *it; // Retrieve the median value
        sorted_medians_.erase(it); // Remove the median from the list
    }
    return median;
}

// Inserts a new value into the list while maintaining sorted order
void myList::insert(const int& value){
    // Use std::lower_bound to find the correct insertion point
    // for the new value to keep the list sorted
    auto it = std::lower_bound(sorted_medians_.begin(), sorted_medians_.end(), value);
    // Insert the new value into the list at the determined position
    sorted_medians_.insert(it, value);
}