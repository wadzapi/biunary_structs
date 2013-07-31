#ifndef BIN_TREE_NODE_H_
#define BIN_TREE_NODE_H_

template <class Tp>
struct bin_tree_node {
    tree_node* left;
    tree_node* right;
    Tp* value;
};

#endif //BIN_TREE_NODE_H_
