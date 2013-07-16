#ifndef STACK_H_
#define STACK_H_
#include "data_struct.h"

template <class Tp>
class Stack {
    private:
        DataStruct struct_;
        tree_node<Tp> root_;

    public:
        Stack(size_t max_capacity);
        ~Stack();
        bool Empty();
        Tp* Top();
        const Tp* Top() const;
        void Push(const& Tp);
        void Pop();
        size_t Size() const;
};

#endif
        

template <class Tp>
Stack::Stack(size_t max_capacity) {
    struct_.Allocate(max_capacity, max_capacity);
    ///Allocate root logical node
    root_ = struct_.AddLogic();
    struct_.Reserve(root_);
    root_.left = root_;
    root_.right = root_;
    root_.value = NULL; 
}

template <class Tp>
Stack::~Stack() {
}

template <class Tp>
bool Stack::Empty() {
    return (root_->value = NULL);
}

template <class Tp>
Tp* Stack::Top() {
    
}

template <class Tp>
const Tp* Stack::Top() const {
}

template <class Tp>
void Stack::push(const& Tp) {
}

template <class Tp>
void Stack::pop() {
}
