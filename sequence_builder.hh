#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
    public:
        tree_node<Tp> *AddNode(DataStruct<Tp> *_struct);
        void ConnectNode(DataStruct<Tp> *_struct, tree_node<Tp>* root_node, tree_node<Tp>* new_node);
        SequenceBuilder();
        ~SequenceBuilder(); 
};

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder() {
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNode(DataStruct<Tp> *_struct) {
    _struct->AddDataLogic();
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectNode(DataStruct<Tp> *_struct, tree_node<Tp>* root_node, tree_node<Tp>* new_node) {
    //connect to other nodes in sequence
    _struct->SetRight(root_node, new_node);
    _struct->SetLeft(new_node, root_node);
    //update root node
    _struct->SetRight(root_node, new_node);
}

#endif //SEQUENCE_BUILDER_H_
