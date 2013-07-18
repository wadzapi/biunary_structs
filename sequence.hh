#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "sequence_builder.hh"
#include "struct_director.hh"

template <class Tp>
class Sequence {
    private:
        DataStruct<Tp>* struct_;
        SequenceBuilder<Tp>* builder_;
        StructDirector<Tp>* director_;
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
    struct_ = new DataStruct<Tp>(max_capacity, max_capacity + 2);
    builder_ = new SequenceBuilder<Tp>();
    director_ = new StructDirector<Tp>(struct_);
    if (prebuilt) {
        director_->Construct(builder_, max_capacity);
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
    tree_node<Tp>* new_node = director_->Construct(struct_, val, 1);
    director_->ConnectSeq(struct_, root_node_, new_node);
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    tree_node<Tp>* new_node = director_->Construct(struct_, val, 1);
    director_->ConnectSeq(struct_, new_node, root_node_);
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    tree_node<Tp>* old_node = root_node_->left;
    root_node_->left = old_node->right;
    struct_->Unreserve(old_node);
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    tree_node<Tp>* old_node = root_node_->right;
    root_node_->right = old_node->left;
    struct_->Unreserve(old_node);
}

#endif // SEQUENCE_H_
