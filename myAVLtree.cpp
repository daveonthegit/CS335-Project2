#include "myAVLtree.hpp"

void treeMedian(const std::vector<int> * instructions)
{
    AvlTree min_tree; // a tree for min_tree elements greater than the median(minTree)
    AvlTree max_tree; // a tree for max_tree elements less than the median(maxTree)
    std::vector<int> median; //created a vector to store all the popped medians
    int max_tree_size = 0; //counter for maxTree 
    int min_tree_size = 0; // counter for minTree

    const auto t1_start = std::chrono::steady_clock::now();

    for (auto it = instructions->begin(); it != instructions->end(); ++it){//iterate throughout the vector
        int operation = *it;//dereference it and store it into operation
        if (!max_tree.isEmpty()){//if its not empty(!= nullptr)
            if (operation == -1){//push back the median if it is -1
                median.push_back(max_tree.findMax());
                max_tree.remove(max_tree.findMax());//remove the right most node for the max_tree tree and decrement it
                max_tree_size--;
            }
            else{//if any other value
                if ((operation) > max_tree.findMax()) //if operation is > right most for max_tree tree then insert it into min_tree tree
                {
                    min_tree.insert(operation); 
                    min_tree_size++;//increment it by 1 for min_tree
                }
                else{
                    max_tree.insert(operation); // if < right most for max_tree, then insert
                    max_tree_size++;
                }
            }
        }
        else{//if it is empty, this will be the first node inserted
            max_tree.insert(operation); 
            max_tree_size++;
        }

        if (min_tree_size > max_tree_size){ // if minheap size > maxheap size
                max_tree.insert(min_tree.findMin()); // insert the minheap leftmost node into max_tree and increment max_tree
                max_tree_size++;
                min_tree.remove(min_tree.findMin()); // remove the leftmost node for minheap from min_tree(minheap) and decrement
                min_tree_size--;
            }
        
        if ((max_tree_size + min_tree_size) % 2 == 0){ //if even
            if (max_tree_size > min_tree_size){ // if maxheap size > minheap size
                min_tree.insert(max_tree.findMax()); //insert rightmost of the maxheap(max_tree) into min_tree
                min_tree_size++;
                max_tree.remove(max_tree.findMax()); // remove rightmost of max_tree from max_tree
                max_tree_size--;
            }
        }
        else{//if odd
            if (max_tree_size > (min_tree_size + 1)){//if max_tree is greater than min_tree + 1 because it cannot be greater than min_tree by 1
                min_tree.insert(max_tree.findMax()); //insert rightmost of the maxheap(max_tree) into min_tree
                min_tree_size++;
                max_tree.remove(max_tree.findMax()); // remove rightmost of max_tree from max_tree
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