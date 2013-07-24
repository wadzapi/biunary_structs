#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceBuilder : public StructBuilderBase<Tp> {
    private:
    protected:
    public:
        tree_node<Tp> *AddNode(DataStruct<Tp> *_struct);
        tree_node<Tp> *AddNode(DataStruct<Tp> *_struct, const Tp& value);
        tree_node<Tp> *AddRoot(DataStruct<Tp> *_struct);
        void SetNodeValue(DataStruct<Tp> *_struct, tree_node<Tp>* node, const Tp& value);
        void ConnectNode(DataStruct<Tp> *_struct, tree_node<Tp> *node1, tree_node<Tp> *node2);
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
    tree_node<Tp>* new_node = _struct->AddLogic();
    SetNodeValue(_struct, new_node, Tp());
    return new_node;
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddNode(DataStruct<Tp> *_struct, const Tp& value) {
    tree_node<Tp>* new_node = _struct->AddLogic();
    SetNodeValue(_struct, new_node, value);
    return new_node;
}

template <class Tp>
tree_node<Tp>* SequenceBuilder<Tp>::AddRoot(DataStruct<Tp> *_struct) {
    tree_node<Tp>* root_node = _struct->AddLogic();
    _struct->Reserve(root_node);
    return root_node;
}

template <class Tp>
void SequenceBuilder<Tp>::SetNodeValue(DataStruct<Tp> *_struct, tree_node<Tp>* node, const Tp& value) {
    Tp* new_val = _struct->AddData(value);
    _struct->SetData(node, new_val);
    _struct->Unreserve(new_val);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectNode(DataStruct<Tp> *_struct, tree_node<Tp> *node1, tree_node<Tp> *node2) {
    //connect to the right side of other nodes in sequence 
    _struct->SetRight(node1, node2);
    _struct->SetLeft(node2, node1);
}

#endif //SEQUENCE_BUILDER_H_
