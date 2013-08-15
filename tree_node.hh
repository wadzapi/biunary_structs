#ifndef TREE_NODE_H_
#define TREE_NODE_H_

template <class Tp, size_t NUM_LINKS>
struct tree_node {
    tree_node*[NUM_LINKS];
    Tp* value;
};

#endif //TREE_NODE_H_
