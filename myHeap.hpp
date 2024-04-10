//David Xiao
//Project 2 myHeap class header

#ifndef MYHEAP_HPP
#define MYHEAP_HPP

//libraries
#include <vector>
#include <queue>

//heapMedian signature
void heapMedian(const std::vector<int>* instructions);

class myHeap {
    public:
        //constructor
        myHeap();

        //methods
        int popMedian();

        void insert(const int& median);

        std::vector<int>& getMediansToPrint();

    private:
        std::vector<int> medians_to_print_;
        std::priority_queue<int> max_heap;
        //specifing greater than comparison to make minHeap
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
};


#endif