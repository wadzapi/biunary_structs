#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include "bin_tree_director.hh"

template <class Tp>
class BinaryTree {
    private:

        bin_tree_node<Tp>* root_node_;
        BinaryTreeBuilder<Tp>* builder_;    
        BinaryTreeDirector<Tp>* director_;
        bool is_built;
    protected:
        
    public:
        BinaryTree();
        BinaryTree(bin_tree_node<Tp>* root_node);
        ~BinaryTree();
};

#endif //BIN_TREE_H_
