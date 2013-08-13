#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include "struct.hh"

template <class Tp>
class BinaryTree :  Struct<Tp> {
    private:
    protected:
    public:
        BinaryTree();
        BinaryTree(tree_node<Tp>* spec_node, DataStorage<Tp>* _storage);
        BinaryTree(DataStorage<Tp>* _storage);
        ~BinaryTree();
        void Construct(DataStorage<Tp>* _storage, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>*& root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL);
        void UpdateSpecNode();
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
