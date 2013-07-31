#ifndef BIUNARY_BUILDER_H_
#define BIUNARY_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class BiunaryBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
        tree_node<Tp> *AddNodeLogic();
    public:
        BiunaryBuilder();
        BiunaryBuilder(DataStruct<Tp> *_struct, size_t num_connections);
        ~BiunaryBuilder();
        tree_node<Tp> *AddNode();
        tree_node<Tp> *AddNode(const Tp& value);
        void SetNodeValue(tree_node<Tp> *&node, const Tp& value);
        void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node);
        void DisconnectLeft(tree_node<Tp> *node);
        void DisconnectRight(tree_node<Tp> *node);
        void DeleteNode(tree_node<Tp>* node);
};

template <class Tp>
BiunaryBuilder::BiunaryBuilder() {
}

template <class Tp>
BiunaryBuilder::BiunaryBuilder(DataStruct<Tp> *_struct, size_t num_connections) :
    StructBuilderBase(_struct, num_connections) {
}

template <class Tp>
BiunaryBuilder::~BiunaryBuilder() {
}

template <class Tp>
tree_node<Tp>* BiunaryBuilder<Tp>::AddNodeLogic() {
    tree_node<Tp>* new_node = this->struct_->AddLogic();
    this->struct_->Reserve(new_node);
    tree_node<Tp>* left_subnode = this->struct_->AddLogic();
    this->struct_->SetLeft(new_node, left_subnode);
    tree_node<Tp>* right_subnode = this->struct_->AddLogic();
    this->struct_->SetRight(new_node, right_subnode);
    return new_node;
}

template <class Tp>
void BiunaryBuildr::ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) {
}

template <class Tp>
void BiunaryBuilder::ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) {
}

template <class Tp>
void BiunaryBuilder::DisconnectLeft(tree_node<Tp> *node) {
}

template <class Tp>
void BiunaryBuilder::DisconnectRight(tree_node<Tp> *node) {
}

template <class Tp>
void BiunaryBuilder::DeleteNode(tree_node<Tp>* node) {
}

#endif// BIUNARY_BUILDER_H_
