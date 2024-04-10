// David Xiao
// Project 2: Implementation of myHeap class methods

// Including necessary libraries
#include <queue>
#include <algorithm>
#include <iostream>
#include <chrono>
#include "myHeap.hpp"

// Function to calculate medians from a sequence of instructions
void heapMedian(const std::vector<int>* instructions){
    // Instantiate a myHeap object to use for calculating medians
    myHeap temp_heap;
    
    // Start the timer to measure performance
    auto start = std::chrono::high_resolution_clock::now();

    // Process each instruction in the input vector
    for (const int value : *instructions) {
        if (value == -1) {
            // If instruction is -1, pop the median and store it for later printing
            temp_heap.getMediansToPrint().push_back(temp_heap.popMedian());
        } else {
            // Insert the value into the heap
            temp_heap.insert(value);
        }
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration in milliseconds
    std::chrono::duration<double> duration = end - start;
    std::cout << "\nHeap Completed in: " << duration.count() * 1000 << " milliseconds\n";

    // Print the medians after processing all instructions
    for (const int median : temp_heap.getMediansToPrint()) {
        std::cout << median << " ";
    }
}

// Constructor initializes the max_heap and min_heap data structures
myHeap::myHeap(){
    // No explicit action needed here since priority_queues are already initialized upon object creation
}

// Getter method for the mediansToPrint vector
std::vector<int>& myHeap::getMediansToPrint(){
    return medians_to_print_;
}

// Removes and returns the current median from the heaps
int myHeap::popMedian() {
    // The top of max_heap is considered the current median
    int median = max_heap.top();
    max_heap.pop();

    // Rebalance the heaps to maintain the size property
    if (max_heap.size() < min_heap.size()) {
        max_heap.push(min_heap.top());
        min_heap.pop();
    }

    return median;
}

// Inserts a new value into the correct heap to maintain the median property
void myHeap::insert(const int& value) {
    // Insert into max_heap if value is less than or equal to the current median, else into min_heap
    if (max_heap.empty() || value <= max_heap.top()) {
        max_heap.push(value);
    } else {
        min_heap.push(value);
    }

    // Rebalance the heaps to ensure their sizes differ by no more than one
    if (max_heap.size() > min_heap.size() + 1) {
        // Move the top element of max_heap to min_heap to balance the sizes
        min_heap.push(max_heap.top());
        max_heap.pop();
    } else if (min_heap.size() > max_heap.size()) {
        // Move the top element of min_heap to max_heap to balance the sizes
        max_heap.push(min_heap.top());
        min_heap.pop();
    }
}