#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "struct.hh"

template <class Tp>
class Sequence : public Struct<Tp> {
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


#include "sequence_director.hh"
#include "sequence_builder.hh"

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
    if (spec_node == NULL) {
        spec_node = this->builder_->AddRoot();
    }
    SetSpecNode(spec_node);
    if (root_node == NULL) {
        root_node = this->builder_->AddRoot();
    }
    SetRootNode(root_node);
    this->is_built_ = true;
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
    Tp* front_val = (this->root_node_->right)->value;
    return front_val;
}

template <class Tp>
const Tp* Sequence<Tp>::Front() const {
    //return ((this->spec_node_->left)->right)->value;
    Tp* front_val = (this->root_node_->right)->value;
    return front_val;
}

template <class Tp>
Tp* Sequence<Tp>::Back() {
    Tp* back_val = (this->spec_node_->right)->value;
    return back_val;
}

template <class Tp>
const Tp* Sequence<Tp>::Back() const {
    Tp* back_val = (this->spec_node_->right)->value;
    return back_val;
}

template <class Tp>
void Sequence<Tp>::PushBack(const Tp& val) {
    Sequence<Tp>* new_node = (Sequence<Tp>*)this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectRight(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug 
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    Sequence<Tp>* new_node = this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectLeft(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    this->director_->RemoveNode(this->builder_, this, this->spec_node_->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    this->director_->RemoveNode(this->builder_, this, this->root_node_->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::UpdateSpecNode() {
}

#endif // SEQUENCE_H_
