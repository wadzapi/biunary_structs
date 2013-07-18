#ifndef BIUN_H_
#define BIUN_H_
/* Basic data structure - classic binary tree */

template <class Value>
struct tree_node {
    tree_node* left;
    tree_node* right;
    Value* value;
};

#endif //BIUN_H_
