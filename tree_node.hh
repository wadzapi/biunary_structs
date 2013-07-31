#ifndef TREE_NODE_H_
#define TREE_NODE_H_

template <class Tp>
struct tree_node {
    tree_node* left;
    tree_node* right;
    Tp* value;
};

#endif //TREE_NODE_H_
