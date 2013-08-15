#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
    public:
        SequenceBuilder();
        SequenceBuilder(DataStorage<Tp>* _storage);
        ~SequenceBuilder(); 
        tree_node<Tp, 2> *AddNodeLogic();
        void ConnectLeft(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node);
        void ConnectRight(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node);
        void DisconnectLeft(tree_node<Tp, 2> *node);
        void DisconnectRight(tree_node<Tp, 2> *node);
        void DeleteNode(tree_node<Tp, 2>* node);
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
tree_node<Tp, 2>* SequenceBuilder<Tp>::AddNodeLogic() {
    tree_node<Tp, 2>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectLeft(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node) {
    this->storage_->SetLeft(node, new_node);
    this->storage_->SetRight(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectRight(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node) {
    this->storage_->SetRight(node, new_node);
    this->storage_->SetLeft(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectLeft(tree_node<Tp, 2> *node) {
    this->storage_->SetRight(node->links[0], node->links[0]);
    this->storage_->SetLeft(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectRight(tree_node<Tp, 2> *node) {
    this->storage_->SetLeft(node->links[1], node->links[1]);
    this->storage_->SetRight(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DeleteNode(tree_node<Tp, 2>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif //SEQUENCE_BUILDER_H_
