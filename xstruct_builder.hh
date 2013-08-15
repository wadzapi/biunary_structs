#ifndef XSTRUCT_BUILDER_H_
#define XSTRUCT_BUILDER_H_

#include "struct_builder.hh"

template <class Tp, size_t NUM_LINKS>
class XStructBuilder : public StructBuilderBase<Tp, NUM_LINKS> {
    private:
    protected:
        tree_node<Tp, 2> *AddNodeLogic();
    public:
        XStructBuilder();
        XStructBuilder(DataStorage<Tp> *_storage, size_t num_connections);
        ~XStructBuilder();
        tree_node<Tp, 2> *AddNode();
        tree_node<Tp, 2> *AddNode(const Tp& value);
        void SetNodeValue(tree_node<Tp, 2> *&node, const Tp& value);
        void ConnectLeft(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node);
        void ConnectRight(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node);
        void DisconnectLeft(tree_node<Tp, 2> *node);
        void DisconnectRight(tree_node<Tp, 2> *node);
        void DeleteNode(tree_node<Tp, 2>* node);
};

template <class Tp, size_t NUM_LINKS>
XStructBuilder<Tp, NUM_LINKS>::XStructBuilder() {
}

template <class Tp, size_t NUM_LINKS>
XStructBuilder<Tp, NUM_LINKS>::XStructBuilder(DataStorage<Tp> *_storage, size_t num_connections) 
    StructBuilderBase(_storage, num_connections) {
}

template <class Tp, size_t NUM_LINKS>
XStructBuilder::~XStructBuilder() {
}

template <class Tp, size_t NUM_LINKS>
tree_node<Tp, 2>* XStructBuilder<Tp, NUM_LINKS>::AddNodeLogic() {
    tree_node<Tp, 2>* new_node = this->storage_->AddLogic();
    this->storage_->Reserve(new_node);
    tree_node<Tp, 2>* left_subnode = this->storage_->AddLogic();
    this->storage_->SetLeft(new_node, left_subnode);
    tree_node<Tp, 2>* right_subnode = this->storage_->AddLogic();
    this->storage_->SetRight(new_node, right_subnode);
    return new_node;
}

template <class Tp, size_t NUM_LINKS>
void XStructBuilder<Tp, NUM_LINKS>::ConnectLeft(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructBuilder::ConnectRight(tree_node<Tp, 2> *node, tree_node<Tp, 2> *new_node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructBuilder::DisconnectLeft(tree_node<Tp, 2> *node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructBuilder::DisconnectRight(tree_node<Tp, 2> *node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructBuilder::DeleteNode(tree_node<Tp, 2>* node) {
}

#endif// XSTRUCT_BUILDER_H_
