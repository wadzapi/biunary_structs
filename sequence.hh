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
        Construct(size_t max_capacity, bool prebuilt);
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
Sequence<Tp>::Construct(size_t max_capacity, bool prebuilt) {
    struct_ = new DataStruct(max_capacity, max_capacity + 1);
    builder_ = new SequenceBuilder(struct_);
    director_ = new StructDirector(struct_);
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
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    
}

template <class Tp>
void Sequence<Tp>::PopFront() {
}

#endif // SEQUENCE_H_
