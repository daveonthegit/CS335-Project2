//David Xiao
//Project 2 myAVLTree class header

#ifndef MYAVLTREE_HPP
#define MYAVLTREE_HPP

//libraries
#include <vector>
#include <iostream>
#include "AVLTreeUtils.hpp"
//listMedian signature
void treeMedian(const std::vector<int>* instructions);

class myAVLTree{
    public:
        myAVLTree();
        int min_size_;
        int max_size_;
        AvlTree max_tree_;
        AvlTree min_tree_;
        std::vector<int> medians_to_print_;



};

  
#endif