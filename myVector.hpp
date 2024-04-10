//David Xiao
//Project 2 myVector class header

#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

//libraries
#include <vector>

//vectorMedian signature
void vectorMedian(const std::vector<int>* instructions);

class myVector{
    public:
        //constructor
        myVector();

        //methods
        int popMedian();

        void insert(const int& median);

        std::vector<int>& getMediansToPrint();

    private:
        std::vector<int> medians_to_print_;
        std::vector<int> sorted_medians_;
};

#endif