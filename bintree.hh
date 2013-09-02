#ifndef BINTREE_H_
#define BINTREE_H_

#include "xstruct.hh"

template <class Tp>
class BinaryTree : public XStruct<Tp> {
    private:
    protected:
    public:
        BinaryTree();
        BinaryTree(XNode<Tp>* spec_node, XStorage<Tp>* _storage);
        ~BinaryTree();
        void UpdateSpecNode();
        void Construct(XStorage<Tp>* _storage, XNode<Tp>* root_node = NULL, XNode<Tp>* spec_node = NULL);
};

template <class Tp>
BinaryTree<Tp>::BinaryTree() {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(XNode<Tp>* spec_node, XStorage<Tp>* _storage) {
}

template <class Tp>
BinaryTree<Tp>::BinaryTree(XStorage<Tp>* _storage) {
}

template <class Tp>
BinaryTree<Tp>::~BinaryTree() {
}

template <class Tp>
void BinaryTree<Tp>::Construct(XStorage<Tp>* _storage, size_t num_nodes, XNode<Tp>* spec_node, XNode<Tp>* root_node, const Tp* values) {
}

#endif //BINTREE_H_
