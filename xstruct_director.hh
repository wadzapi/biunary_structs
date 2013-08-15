#ifndef XSTRUCT_DIRECTOR_H_
#define XSTRUCT_DIRECTOR_H_

#include "struct.hh"

template <class Tp, size_t NUM_LINKS>
class XStructDirector : public StructDirectorBase<Tp, NUM_LINKS> {
    private:
    protected:
    public:
        XStructDirector();
        XStructDirector(DataStorage<Tp>* storage_);
        ~XStructDirector();
        tree_node<Tp, 2>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp, 2>* spec_node = (tree_node<Tp, 2>*)NULL, tree_node<Tp, 2>* root_node = (tree_node<Tp, 2>*)NULL, const Tp* values = (Tp*)NULL);        
        void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node, tree_node<Tp, 2> *&new_node);
        void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node, tree_node<Tp, 2> *&new_node);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node);
        void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node, tree_node<Tp, 2> *node);
        void RemoveSpecRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node, tree_node<Tp, 2> *node);
        void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node);
        void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node);
};

#include "xstruct.hh"
      
template <class Tp, size_t NUM_LINKS>
XStructDirector<Tp, NUM_LINKS>::XStructDirector() {
}

template <class Tp, size_t NUM_LINKS>
XStructDirector<Tp, NUM_LINKS>::XStructDirector(DataStorage<Tp>* storage_) {
}

template <class Tp, size_t NUM_LINKS>
XStructDirector<Tp, NUM_LINKS>::~XStructDirector() {
}

template <class Tp, size_t NUM_LINKS>
tree_node<Tp, 2>* XStructDirector<Tp, NUM_LINKS>::
Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp, 2>* spec_node, tree_node<Tp, 2>* root_node, const Tp* values) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node, tree_node<Tp, 2> *&new_node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node, tree_node<Tp, 2> *&new_node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *&node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node, tree_node<Tp, 2> *node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::RemoveSpecRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node, tree_node<Tp, 2> *node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::Clear(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node) {
}

template <class Tp, size_t NUM_LINKS>
void XStructDirector<Tp, NUM_LINKS>::Delete(StructBuilderBase<Tp> *builder, tree_node<Tp, 2> *spec_node) {
}

#endif //XSTRUCT_DIRECTOR_H_
