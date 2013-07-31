#ifndef BIUNARY_DIRECTOR_H_
#define BIUNARY_DIRECTOR_H_

#include "struct_builder.hh"

template <class Tp>
class BiunaryDirector : public StructDirectorVase<Tp> {
    private:
    protected:
    public:
        BiunaryDirector();
        BiunaryDirector(DataStruct<Tp>* struct_);
        ~BiunaryDirector();
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes);
        void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node);
        void RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node);
        void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node);
        void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node);
};
      
template <class Tp>
BiunaryDirector::BiunaryDirector() {
}

template <class Tp>
BiunaryDirector::BiunaryDirector(DataStruct<Tp>* struct_) {
}

template <class Tp>
BiunaryDirector::~BiunaryDirector() {
}

template <class Tp>
tree_node<Tp>* BiunaryDirector::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes) {
}

template <class Tp>
tree_node<Tp>* BiunaryDirector::Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) {
}

template <class Tp>
void BiunaryDirector::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
}

template <class Tp>
void BiunaryDirector::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
}

template <class Tp>
void BiunaryDirector::DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
}

template <class Tp>
void BiunaryDirector::DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
}

template <class Tp>
void BiunaryDirector::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) {
}

template <class Tp>
void BiunaryDirector::RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) {
}

template <class Tp>
void BiunaryDirector::Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
}

template <class Tp>
void BiunaryDirector::Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
}

#endif //BIUNARY_DIRECTOR_H_
