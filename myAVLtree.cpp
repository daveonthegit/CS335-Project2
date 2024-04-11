#include "myAVLtree.hpp"

void treeMedian(const std::vector<int> * instructions)
{
    AvlTree large; // a tree for large elements greater than the median(minTree)
    AvlTree small; // a tree for small elements less than the median(maxTree)
    std::vector<int> median; //created a vector to store all the popped medians
    int smallcounter = 0; //counter for maxTree 
    int largecounter = 0; // counter for minTree

    auto start = std::chrono::high_resolution_clock::now();

    for (auto it = instructions->begin(); it != instructions->end(); ++it){//iterate throughout the vector
        int operation = *it;//dereference it and store it into operation
        if (!small.isEmpty()){//if its not empty(!= nullptr)
            if (operation == -1){//push back the median if it is -1
                median.push_back(small.findMax());
                small.remove(small.findMax());//remove the right most node for the small tree and decrement it
                smallcounter--;
            }
            else{//if any other value
                if ((operation) > small.findMax()) //if operation is > right most for small tree then insert it into large tree
                {
                    large.insert(operation); 
                    largecounter++;//increment it by 1 for large
                }
                else{
                    small.insert(operation); // if < right most for small, then insert
                    smallcounter++;
                }
            }
        }
        else{//if it is empty, this will be the first node inserted
            small.insert(operation); 
            smallcounter++;
        }

        if (largecounter > smallcounter){ // if minheap size > maxheap size
                small.insert(large.findMin()); // insert the minheap leftmost node into small and increment small
                smallcounter++;
                large.remove(large.findMin()); // remove the leftmost node for minheap from large(minheap) and decrement
                largecounter--;
            }
        
        if ((smallcounter + largecounter) % 2 == 0){ //if even
            if (smallcounter > largecounter){ // if maxheap size > minheap size
                large.insert(small.findMax()); //insert rightmost of the maxheap(small) into large
                largecounter++;
                small.remove(small.findMax()); // remove rightmost of small from small
                smallcounter--;
            }
        }
        else{//if odd
            if (smallcounter > (largecounter + 1)){//if small is greater than large + 1 because it cannot be greater than large by 1
                large.insert(small.findMax()); //insert rightmost of the maxheap(small) into large
                largecounter++;
                small.remove(small.findMax()); // remove rightmost of small from small
                smallcounter--;
            }
        }
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();
    // Calculate the duration in milliseconds
    std::chrono::duration<double> duration = end - start;
    //std::cout << "\nHeap Completed in: " << duration.count() * 1000 << " milliseconds\n";

}