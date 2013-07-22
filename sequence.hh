#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "sequence_builder.hh"
#include "sequence_director.hh"

template <class Tp>
class Sequence {
    private:
        DataStruct<Tp>* struct_;
        SequenceBuilder<Tp>* builder_;
        SequenceDirector<Tp>* director_;
        tree_node<Tp>* root_node_;
        bool is_built_;

    public:
        Sequence();
        Sequence(size_t max_capacity);
        ~Sequence();
        void Construct(size_t max_capacity, bool prebuilt);
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
Sequence<Tp>::Sequence() : is_built_(false) {
}

template <class Tp>
Sequence<Tp>::Sequence(size_t max_capacity) : is_built_(false) {
    Construct(max_capacity, false);
}

template <class Tp>
void Sequence<Tp>::Construct(size_t max_capacity, bool prebuilt) {
    struct_ = new DataStruct<Tp>(max_capacity, max_capacity + 3);
    builder_ = new SequenceBuilder<Tp>();
    director_ = new SequenceDirector<Tp>(struct_);
    if (prebuilt && max_capacity > 0) {
        root_node_ = director_->Construct(builder_, max_capacity);
    } else {
        root_node_ = director_->Construct(builder_, 1);
        struct_->Unreserve((root_node_->left)->value);
        (root_node_->left)->value = NULL;
    }
    is_built_ = true;
}

template <class Tp>
Sequence<Tp>::~Sequence() {
    if (is_built_) {
        delete director_;
        delete builder_;
        delete struct_;
    }
}

template <class Tp>
bool Sequence<Tp>::Empty() {
    if (root_node_->left == root_node_->right) {
        if (root_node_->value == NULL) {
            return true;
        }
    }
    return false;
}

template <class Tp>
Tp* Sequence<Tp>::Front() {
    return (root_node_->right)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Front() const {
    return (root_node_->right)->value;
}

template <class Tp>
Tp* Sequence<Tp>::Back() {
    return (root_node_->left)->value;
}

template <class Tp>
const Tp* Sequence<Tp>::Back() const {
    return (root_node_->left)->value;
}

template <class Tp>
void Sequence<Tp>::PushBack(const Tp& val) {
    tree_node<Tp>* new_node = director_->Construct(builder_, &val, 1);
    director_->Connect(new_node, root_node_);
    root_node_ = new_node;
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    tree_node<Tp>* new_node = director_->Construct(builder_, &val, 1);
    director_->Connect(root_node_, new_node);
    ///struct_->PrintCounters(); //for debug
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    tree_node<Tp>* old_node = root_node_->left;
    struct_->SetLeft(root_node_, old_node->right);
    struct_->SetLeft(root_node_->left, root_node_->left);
    director_->DeleteNode(old_node);
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    tree_node<Tp>* old_node = root_node_->right;
    struct_->SetRight(root_node_, old_node->left);
    struct_->SetRight(root_node_->right, root_node_->right);
    director_->DeleteNode(old_node);
    ///struct_->PrintCounters(); //for debug
}

#endif // SEQUENCE_H_
