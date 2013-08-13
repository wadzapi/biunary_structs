#ifndef BIN_TREE_BUILDER_H_
#define BIN_TREE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class BinaryTreeBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
        tree_node<Tp> *AddNodeLogic();
    public:
        BinaryTreeBuilder();
        BinaryTreeBuilder(DataStorage<Tp>* storage);
        ~BinaryTreeBuilder(); 
        void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void DisconnectLeft(tree_node<Tp> *node);
        void DisconnectRight(tree_node<Tp> *node);
        void DeleteNode(tree_node<Tp>* node);
};

template <class Tp>
BinaryTreeBuilder<Tp>::BinaryTreeBuilder() { 
}

template <class Tp>
BinaryTreeBuilder<Tp>::BinaryTreeBuilder(DataStorage<Tp>* storage) : 
    StructBuilderBase<Tp>(storage, 2) {
}

template <class Tp>
BinaryTreeBuilder<Tp>::~BinaryTreeBuilder() {
}

template <class Tp>
tree_node<Tp>* BinaryTreeBuilder<Tp>::AddNodeLogic() {
    tree_node<Tp>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp>
void BinaryTreeBuilder<Tp>::ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->storage_->SetLeft(node, new_node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->storage_->SetRight(node, new_node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DisconnectLeft(tree_node<Tp> *node) {
    this->storage_->SetLeft(node, node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DisconnectRight(tree_node<Tp> *node) {
    this->storage_->SetRight(node, node);
}

template <class Tp>
void BinaryTreeBuilder<Tp>::DeleteNode(tree_node<Tp>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif //SEQUENCE_BUILDER_H_
