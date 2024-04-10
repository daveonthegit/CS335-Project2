//David Xiao
//Project 2 myAVLTree class header

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

//libraries
#include <vector>
#include<list>
#include <iostream>
#include "AVLTreeUtils.hpp"
//listMedian signature
void treeMedian(const std::vector<int>* instructions);

class myAVLTree{
    public:
        //constructor
        myAVLTree();

        //methods
        int popMedian();

        void insert(const int& median);

        std::vector<int>& getMediansToPrint();

    private:
        std::vector<int> medians_to_print_;
        Node* max_tree_;
        //specifying greater than comparison to make min_tree_
        Node* min_tree_;
        
        void rebalance();
};

  
#endif