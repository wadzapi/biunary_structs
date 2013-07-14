#ifndef BIUN_H_
#define BIUN_H_
/* Basic data structure - classic binary tree */

struct tree_node_base {
    tree_node_base* Left;
    tree_node_base* Right;
};

template <class Value>
struct tree_node : public tree_node_base {
    Value* value_;
};

#endif //BIUN_H_
