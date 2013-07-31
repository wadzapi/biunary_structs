#ifndef BIUNARY_BUILDER_H_
#define BIUNARY_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class BiunaryBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
    public:
        BiunaryBuilder();
        BiunaryBuilder(DataStruct<Tp> *_struct, size_t num_links);
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
BiunaryBuilder::BiunaryBuilder(DataStruct<Tp> *_struct, size_t num_links) :
    StructBuilderBase(_struct, num_links) {
}

template <class Tp>
BiunaryBuilder::~BiunaryBuilder() {
}

template <class Tp>
tree_node<Tp>* BiunaryBuilder::AddNode() {
    tree_node<Tp>* new_node = this->struct_->AddLogic();
    tree_node
}

template <class Tp>
tree_node<Tp>* BiunaryBuilder::AddNode(const Tp& value) {
}

template <class Tp>
void BiunaryBuilder::SetNodeValue(tree_node<Tp> *&node, const Tp& value) {
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
