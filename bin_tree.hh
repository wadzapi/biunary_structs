#ifndef BIN_TREE_H_
#define BIN_TREE_H_
/* Basic data structure - classic binary tree */

template <class Value>
struct tree_node {
    tree_node* left;
    tree_node* right;
    Value* value;
};

#endif //BIN_TREE_H_
