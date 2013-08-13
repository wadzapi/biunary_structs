#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include "struct.hh"

template <class Tp>
class BinaryTree : public Struct<Tp> {
    private:
    protected:
    public:
        BinaryTree();
        BinaryTree(tree_node<Tp>* spec_node, DataStorage<Tp>* _storage);
        ~BinaryTree();
        void UpdateSpecNode();
        void Construct(DataStorage<Tp>* _storage, tree_node<Tp>* root_node = NULL, tree_node<Tp>* spec_node = NULL);
};

template <class Tp>
BinaryTree<Tp>::BinaryTree() {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(tree_node<Tp>* spec_node, DataStorage<Tp>* _storage) {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(DataStorage<Tp>* _storage) {
}

template <class Tp>
BinaryTree<Tp>::~BinaryTree() {
}

template <class Tp>
void BinaryTree<Tp>::Construct(DataStorage<Tp>* _storage, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
}

#endif //BIN_TREE_H_
