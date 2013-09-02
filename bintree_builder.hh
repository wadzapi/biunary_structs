#ifndef BINTREE_BUILDER_H_
#define BINTREE_BUILDER_H_

#include "xbuilder.hh"

template <class Tp>
class BinaryTreeBuilder : public XBuilder<Tp> {
    private:
    protected:
        XNode<Tp> *AddNodeLogic();
    public:
        BinaryTreeBuilder();
        BinaryTreeBuilder(XStorage<Tp>* storage);
        ~BinaryTreeBuilder(); 
        void ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node);
        void ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node);
        void DisconnectLeft(XNode<Tp> *node);
        void DisconnectRight(XNode<Tp> *node);
        void DeleteNode(XNode<Tp>* node);
};

template <class Tp>
BinaryTreeBuilder<Tp>::BinaryTreeBuilder() { 
}

template <class Tp>
BinaryTreeBuilder<Tp>::BinaryTreeBuilder(XStorage<Tp>* storage) : 
    XBuilder<Tp>(storage, 2) {
}

template <class Tp>
BinaryTreeBuilder<Tp>::~BinaryTreeBuilder() {
}

template <class Tp>
XNode<Tp>* BinaryTreeBuilder<Tp>::AddNodeLogic() {
    XNode<Tp>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp>
void BinaryTreeBuilder<Tp>::ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node) {
    this->storage_->SetLeft(node, new_node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node) {
    this->storage_->SetRight(node, new_node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DisconnectLeft(XNode<Tp> *node) {
    this->storage_->SetLeft(node, node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DisconnectRight(XNode<Tp> *node) {
    this->storage_->SetRight(node, node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DeleteNode(XNode<Tp>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif // BINTREE_BUILDER_H_
