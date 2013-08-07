#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include "struct_base.hh"
#include "bin_tree_builder.hh"
#include "bin_tree_director.hh"


template <class Tp>
class BinaryTree :  StructBase<Tp> {
    private:
    protected:
    public:
        BinaryTree();
        BinaryTree(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct);
        BinaryTree(DataStruct<Tp>* _struct);
        ~BinaryTree();
        void Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>*& root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL);
        void UpdateSpecNode();
};

template <class Tp>
BinaryTree<Tp>::BinaryTree() {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct) {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(DataStruct<Tp>* _struct) {
}

template <class Tp>
BinaryTree<Tp>::~BinaryTree() {
}

template <class Tp>
void BinaryTree<Tp>::Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
}

#endif //BIN_TREE_H_
