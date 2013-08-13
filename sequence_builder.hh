#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
        tree_node<Tp> *AddNodeLogic();
    public:
        SequenceBuilder();
        SequenceBuilder(DataStorage<Tp>* _storage);
        ~SequenceBuilder(); 
        tree_node<Tp> *AddNode();
        tree_node<Tp> *AddNode(const Tp& value);
        void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void DisconnectLeft(tree_node<Tp> *node);
        void DisconnectRight(tree_node<Tp> *node);
        void DeleteNode(tree_node<Tp>* node);
};

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder() { 
}

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder(DataStorage<Tp>* _storage) : 
    StructBuilderBase<Tp>(_storage, 1) {
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNodeLogic() {
    tree_node<Tp>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->storage_->SetLeft(node, new_node);
    this->storage_->SetRight(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->storage_->SetRight(node, new_node);
    this->storage_->SetLeft(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectLeft(tree_node<Tp> *node) {
    this->storage_->SetRight(node->left, node->left);
    this->storage_->SetLeft(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectRight(tree_node<Tp> *node) {
    this->storage_->SetLeft(node->right, node->right);
    this->storage_->SetRight(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DeleteNode(tree_node<Tp>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif //SEQUENCE_BUILDER_H_
