#ifndef SEQUENCE_H_
#define SEQUENCE_H_
#include "data_struct.h"

template <class Tp>
class Sequence {
    private:
        DataStruct struct_;
        tree_node<Tp> curr_node_;

    public:
        Sequence(size_t max_capacity);
        ~Sequence();
        bool Empty();
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        tree_node<Tp>* AddNode(const Tp& val);
        const Tp* Back() const;
        void PushBack(const Tp& val);
        void PushFront(const Tp& val);
        void PopBack();
        void PopFront();
};

#endif
        

template <class Tp>
Sequence::Sequence(size_t max_capacity) {
    struct_.Allocate(max_capacity, max_capacity + 1);
    ///Allocate root logical node
    ///left root subtree - is back, right - front
    root_node_ = struct_.AddLogic();
    struct_.Reserve(root_node_);
    root_node_->left = curr_node_;
    root_node_->right = curr_node_;
    root_node_->value = NULL;
}

template <class Tp>
Sequence::~Sequence() {
}

template <class Tp>
bool Sequence::Empty() {
    if (curr_node_->value = NULL) {
        if (curr_node_->left == curr_node) {
            if (curr_node_->right == curr_node) {
                return true;
            }
        }
    }
    return false;
}

template <class Tp>
Tp* Sequence::Front() {
    return (root_node_->right)->value;
}

template <class Tp>
const Tp* Sequence::Front() const {
    return (root_node_->right)->value;
}

template <class Tp>
Tp* Sequence::Back() {
    return (root_node_->left)->value;
}

template <class Tp>
const Tp* Sequence::Back() const {
    return (root_node_->left)->value;
}

template <class Tp>
tree_node<Tp>* Sequence::AddNode(const Tp& val) {
    tree_node<Tp>* new_node = NULL;
    Tp* new_val = struct_.AddData(val);
    if (new_val == NULL) {
        throw "Physical storage overflow!";
    } else {
        struct.Reserve(new_val);
        new_node = struct_.AddLogic();
        if (new_node == NULL) {
            throw "Logical storage overflow!";
        } else {
            struct_.Reserve(new_node);
            new_node->value = new_val;
            new_node->left = new_node;
            new_node->right = new_node;
        }
    }
    return new_node;
}

template <class Tp>
void Sequence::PushBack(const Tp& val) {
}

template <class Tp>
void Sequence::PushFront(const Tp& val) {
    
}

template <class Tp>
void Sequence::PopBack() {
    
}

template <class Tp>
void Sequence::PopFront() {
}
