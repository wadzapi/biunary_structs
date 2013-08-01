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
        Sequence(tree_node<Tp>* root_node, DataStruct<Tp>* _struct);
        Sequence(DataStruct<Tp>* _struct);
        ~Sequence();
        void Construct(DataStruct<Tp>* _struct);
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
Sequence<Tp>::Sequence(tree_node<Tp>* root_node, DataStruct<Tp>* _struct) : StructBase<Tp>(root_node, _struct) {
}

template <class Tp>
Sequence<Tp>::Sequence(DataStruct<Tp>* _struct) : StructBase<Tp>(_struct) {
}

template <class Tp>
void Sequence<Tp>::Construct(DataStruct<Tp>* _struct) {
    this->builder_ = new SequenceBuilder<Tp>(_struct);
    this->director_ = new SequenceDirector<Tp>(_struct);
    this->struct_ = _struct;
    this->is_built_ = true;
}

template <class Tp>
Sequence<Tp>::~Sequence() {}

template <class Tp>
bool Sequence<Tp>::Empty() {
    if (this->root_node_->left == this->root_node_->right) {
        if ((this->root_node_->left)->value == NULL) {
            return true;
        }
    }
    return false;
}

template <class Tp>
Tp* Sequence<Tp>::Front() {
    return ((this->root_node_->left)->right)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Front() const {
    return ((this->root_node_->left)->right)->value;
}

template <class Tp>
Tp* Sequence<Tp>::Back() {
    return (this->root_node_->right)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Back() const {
    return (this->root_node_->right)->value;
}

template <class Tp>
void Sequence<Tp>::PushBack(const Tp& val) {
    tree_node<Tp>* new_node = this->director->Construct(this->builder_, &val, 1);
    this->director->ConnectRight(this->builder_, this->root_node_, new_node);
    ///for debug 
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    tree_node<Tp>* new_node = this->director->Construct(this->builder_, &val, 1);
    this->director->ConnectLeft(this->builder_, this->root_node_, new_node);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    this->director->RemoveNode(this->builder_, this->root_node_, this->root_node_->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    this->director->RemoveNode(this->builder_, this->root_node_, (this->root_node_->left)->right);
    ///for debug
    this->struct_->PrintCounters(); ///for debug
}

#endif // SEQUENCE_H_
