//David Xiao
//Project 2 myList class header

#ifndef MYLIST_HPP
#define MYLIST_HPP

//libraries
#include <vector>
#include <list>

//listMedian signature
void listMedian(const std::vector<int>* instructions);

class myList{
    public:
        //constructor
        myList();

        //methods
        int popMedian();

        void insert(const int& median);

        std::vector<int>& getMediansToPrint();

    private:
        std::vector<int> medians_to_print_;
        std::list<int> sorted_medians_;
};

#endif