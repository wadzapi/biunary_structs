#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "struct_base.hh"
#include "sequence_builder.hh"
#include "sequence_director.hh"

template <class Tp>
class Sequence : public StructBase<Tp> {
    private:
    protected:
    public:
        Sequence();
        Sequence(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct, tree_node<Tp>* root_node = NULL);
        Sequence(DataStruct<Tp>* _struct);
        ~Sequence();
        void UpdateSpecNode();
        void Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>* root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL);
        bool Empty();
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        const Tp* Back() const;
        void PushBack(const Tp& val);
        void PushFront(const Tp& val);
        void PopBack();
        void PopFront();
};

template <class Tp>
Sequence<Tp>::Sequence() {
}

template <class Tp>
Sequence<Tp>::Sequence(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct, tree_node<Tp>* root_node) {
    Construct(_struct, 0, spec_node, root_node);
}


template <class Tp>
Sequence<Tp>::Sequence(DataStruct<Tp>* _struct) {
    Construct(_struct, 0);
}

template <class Tp>
void Sequence<Tp>::Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
    this->builder_ = new SequenceBuilder<Tp>(_struct);
    this->director_ = new SequenceDirector<Tp>(_struct);
    this->struct_ = _struct;
    this->is_built_ = true;
    if (spec_node == NULL) {
        spec_node = this->builder_->AddNode();
        SetSpecNode(spec_node);
    }
    this->director_->Construct(this->builder_, num_nodes, spec_node, root_node, values);
    SetRootNode(root_node);
}

template <class Tp>
Sequence<Tp>::~Sequence() {}

template <class Tp>
bool Sequence<Tp>::Empty() {
    if (this->spec_node_->left == this->spec_node_->right) {
        return true;
    }
    return false;
}

template <class Tp>
Tp* Sequence<Tp>::Front() {
    //return ((this->spec_node_->left)->right)->value;
    return (this->root_node_->right)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Front() const {
    //return ((this->spec_node_->left)->right)->value;
    return (this->root_node_->right)->value;
}

template <class Tp>
Tp* Sequence<Tp>::Back() {
    return (this->spec_node_->right)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Back() const {
    return (this->spec_node_->right)->value;
}

template <class Tp>
void Sequence<Tp>::PushBack(const Tp& val) {
    tree_node<Tp>* new_node = this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectRight(this->builder_, this->spec_node_, new_node);
    ///for debug 
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    tree_node<Tp>* new_node = this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectLeft(this->builder_, this->spec_node_, new_node);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    this->director_->RemoveNode(this->builder_, this->spec_node_, this->spec_node_->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    this->director_->RemoveNode(this->builder_, this->spec_node_, this->root_node_->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::UpdateSpecNode() {
}

#endif // SEQUENCE_H_
