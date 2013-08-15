#ifndef XSTRUCT_BUILDER_H_
#define XSTRUCT_BUILDER_H_

#include "struct_builder.hh"

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
class XStructBuilder : public StructBuilderBase<Tp, NUM_LINKS> {
    private:
    protected:
    public:
        XStructBuilder();
        XStructBuilder(DataStorage<Tp, NUM_LINKS>* _storage);
        ~XStructBuilder(); 
        tree_node<Tp, NUM_LINKS> *AddNodeLogic();
        void ConnectLeft(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node);
        void ConnectRight(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node);
        void DisconnectLeft(tree_node<Tp, NUM_LINKS> *node);
        void DisconnectRight(tree_node<Tp, NUM_LINKS> *node);
        void DeleteNode(tree_node<Tp, NUM_LINKS>* node);
};

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::XStructBuilder() { 
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::XStructBuilder(DataStorage<Tp, NUM_LINKS>* _storage) : 
    StructBuilderBase<Tp, NUM_LINKS>(_storage, 1) {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::~XStructBuilder() {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
tree_node<Tp, NUM_LINKS>* XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::AddNodeLogic() {
    tree_node<Tp, NUM_LINKS>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::ConnectLeft(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node) {
    this->storage_->SetLeft(node, new_node);
    this->storage_->SetRight(new_node, node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::ConnectRight(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node) {
    this->storage_->SetRight(node, new_node);
    this->storage_->SetLeft(new_node, node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::DisconnectLeft(tree_node<Tp, NUM_LINKS> *node) {
    this->storage_->SetRight(node->links[0], node->links[0]);
    this->storage_->SetLeft(node, node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::DisconnectRight(tree_node<Tp, NUM_LINKS> *node) {
    this->storage_->SetLeft(node->links[1], node->links[1]);
    this->storage_->SetRight(node, node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructBuilder<Tp, NUM_LINKS, LINKS_OFFSET>::DeleteNode(tree_node<Tp, NUM_LINKS>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif //XSTRUCT_BUILDER_H_
