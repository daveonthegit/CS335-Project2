// David Xiao
// Project 2: Implementation of myVector class methods

// Including required libraries
#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "myVector.hpp"

// Function to calculate medians from a sequence of instructions
void vectorMedian(const std::vector<int>* instructions){
    myVector temp_vector;

    // Begin timing the execution
    auto start = std::chrono::high_resolution_clock::now();

    // Process each instruction in the vector
    for (const int value : *instructions){
        if (value == -1){
            // If instruction is -1, calculate the median and save it for output
            temp_vector.getMediansToPrint().push_back(temp_vector.popMedian());
        } else {
            // Insert the value into the vector in sorted order
            temp_vector.insert(value);
        }
    }

    // Stop timing and calculate the total duration
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "\nVector Completed in: " << duration.count() * 1000 << " milliseconds\n";

    // Output the calculated medians after processing all instructions
    for (const int median : temp_vector.getMediansToPrint()){
        std::cout << median << " ";
    }
}

// Constructor initializes the class's data structures
myVector::myVector(){
    // Initializes medians_to_print_ and sorted_medians_ as empty vectors
    medians_to_print_ = std::vector<int>();
    sorted_medians_ = std::vector<int>();
}

// Accessor for the vector holding medians to print
std::vector<int>& myVector::getMediansToPrint(){
    return medians_to_print_;
}

// Removes and returns the median from the sorted vector
int myVector::popMedian(){
    // Calculate the index of the median
    int median_index = sorted_medians_.size() / 2;
    int median;

    // Handle even and odd number of elements differently
    if (sorted_medians_.size() % 2 == 0){
        // For even, choose the lower median
        median = sorted_medians_[median_index - 1];
        // Remove the chosen median from the vector
        sorted_medians_.erase(sorted_medians_.begin() + (median_index - 1));
    } else {
        // For odd, the median is at the central index
        median = sorted_medians_[median_index];
        // Remove the median from the vector
        sorted_medians_.erase(sorted_medians_.begin() + median_index);
    }
    return median;
}

// Inserts a value into the vector while maintaining sorted order
void myVector::insert(const int& value){
    // Find the correct position for the new value to keep the vector sorted
    auto insertion_point = std::lower_bound(sorted_medians_.begin(), sorted_medians_.end(), value);
    // Insert the value at the determined position
    sorted_medians_.insert(insertion_point, value);
}