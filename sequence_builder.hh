#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
    public:
        SequenceBuilder();
        SequenceBuilder(DataStruct<Tp>* _struct);
        ~SequenceBuilder(); 
        tree_node<Tp> *AddNode();
        tree_node<Tp> *AddNode(const Tp& value);
        tree_node<Tp> *AddRoot();
        void SetNodeValue(tree_node<Tp> *&node, const Tp& value);
        void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void DisconnectLeft(tree_node<Tp> *node);
        void DisconnectRight(tree_node<Tp> *node);
        void DeleteNode(tree_node<Tp>* node);
        void DeleteRoot(tree_node<Tp>* node);
};

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder() { 
}

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder(DataStruct<Tp>* _struct) : 
    StructBuilderBase<Tp>(_struct, 1) {
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNode() {
    tree_node<Tp>* new_node = this->struct_->AddLogic();
    SetNodeValue(new_node, Tp());
    return new_node;
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNode(const Tp& value) {
    tree_node<Tp>* new_node = this->struct_->AddLogic();
    SetNodeValue(new_node, value);
    return new_node;
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddRoot() {
    tree_node<Tp>* root_node = this->struct_->AddLogic();
    this->struct_->Reserve(root_node);
    return root_node;
}

template <class Tp>
void SequenceBuilder<Tp>::SetNodeValue(tree_node<Tp> *&node, const Tp& value) {
    Tp* new_val = this->struct_->AddData(value);
    this->struct_->SetData(node, new_val);
    this->struct_->Unreserve(new_val);
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

template <class Tp>
void SequenceBuilder<Tp>::DeleteRoot(tree_node<Tp>* node) {
    DeleteNode(node);
    this->struct_->Unreserve(node);
}

#endif //SEQUENCE_BUILDER_H_
