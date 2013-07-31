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
        SequenceBuilder(DataStruct<Tp>* _struct);
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
SequenceBuilder<Tp>::SequenceBuilder(DataStruct<Tp>* _struct) : 
    StructBuilderBase<Tp>(_struct, 2) {
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNodeLogic() {
    tree_node<Tp>* new_node = this->struct_->AddLogic();
    return new_node;
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->struct_->SetLeft(node, new_node);
    this->struct_->SetRight(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) {
    this->struct_->SetRight(node, new_node);
    this->struct_->SetLeft(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectLeft(tree_node<Tp> *node) {
    this->struct_->SetRight(node->left, node->left);
    this->struct_->SetLeft(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectRight(tree_node<Tp> *node) {
    this->struct_->SetLeft(node->right, node->right);
    this->struct_->SetRight(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DeleteNode(tree_node<Tp>* node) {
    //delete links
    this->struct_->SetLeft(node, NULL);
    this->struct_->SetRight(node, NULL);
    //delete value
    this->struct_->Unreserve(node->value);
}

#endif //SEQUENCE_BUILDER_H_
