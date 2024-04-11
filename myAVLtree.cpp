#include "myAVLtree.hpp"

void treeMedian(const std::vector<int> * instructions)
{
    AvlTree min_tree; // Initialize min_tree as a tree for elements greater than the median
    AvlTree max_tree; // Initialize max_tree as a tree for elements less than the median
    std::vector<int> median; // Vector to store all the popped medians
    int max_tree_size = 0; // Counter for the number of elements in max_tree
    int min_tree_size = 0; // Counter for the number of elements in min_tree

    const auto t1_start = std::chrono::steady_clock::now(); // Start the timer
    
    // Iterate through the vector of instructions
    for (auto it = instructions->begin(); it != instructions->end(); ++it){
        int operation = *it; // Dereference the iterator and store it into operation

        // If max_tree is not empty
        if (!max_tree.isEmpty()){
            // If operation is -1, push the median into the median vector
            if (operation == -1){
                median.push_back(max_tree.findMax());
                max_tree.remove(max_tree.findMax()); // Remove the maximum element from max_tree and decrement its size
                max_tree_size--;
            }
            else{ // If operation is any other value
                // If operation is greater than the maximum element in max_tree, insert it into min_tree
                if ((operation) > max_tree.findMax()) {
                    min_tree.insert(operation); 
                    min_tree_size++; // Increment the size of min_tree
                }
                else{ // If operation is less than or equal to the maximum element in max_tree, insert it into max_tree
                    max_tree.insert(operation); 
                    max_tree_size++; // Increment the size of max_tree
                }
            }
        }
        else{ // If max_tree is empty, this will be the first node inserted
            max_tree.insert(operation); 
            max_tree_size++; // Increment the size of max_tree
        }

        // If the size of min_tree is greater than the size of max_tree
        if (min_tree_size > max_tree_size){
            max_tree.insert(min_tree.findMin()); // Insert the minimum element of min_tree into max_tree and increment its size
            max_tree_size++;
            min_tree.remove(min_tree.findMin()); // Remove the minimum element from min_tree and decrement its size
            min_tree_size--;
        }
        
        // If the sum of the sizes of max_tree and min_tree is even
        if ((max_tree_size + min_tree_size) % 2 == 0){
            // If the size of max_tree is greater than the size of min_tree
            if (max_tree_size > min_tree_size){
                min_tree.insert(max_tree.findMax()); // Insert the maximum element of max_tree into min_tree
                min_tree_size++; // Increment the size of min_tree
                max_tree.remove(max_tree.findMax()); // Remove the maximum element from max_tree and decrement its size
                max_tree_size--;
            }
        }
        else{ // If the sum of the sizes of max_tree and min_tree is odd
            // If the size of max_tree is greater than the size of min_tree plus one
            if (max_tree_size > (min_tree_size + 1)){
                min_tree.insert(max_tree.findMax()); // Insert the maximum element of max_tree into min_tree
                min_tree_size++; // Increment the size of min_tree
                max_tree.remove(max_tree.findMax()); // Remove the maximum element from max_tree and decrement its size
                max_tree_size--;
            }
        }
    }

const auto t1_end = std::chrono::steady_clock::now();
int t1 = std::chrono::duration <double, std::micro> (t1_end - t1_start).count();

        for(auto i : median){
            std::cout << i << " ";
        }
    //std::cout << "\n" << t1 << " microseconds." << std::endl;
}