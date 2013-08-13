#ifndef STACK_H_
#define STACK_H_

#include "sequence.hh"
#include "sequence_builder.hh"
#include "sequence_director.hh"

template <class Tp>
class Stack {
    private:
         
    protected:
        Sequence<Tp>* sequence_;
        SequenceDirector<Tp>* seq_director_;
        SequenceBuilder<Tp>* seq_builder_;
    public:
        Stack();
        Stack(DataStruct<Tp>* _struct, tree_node<Tp>* root_node = NULL, tree_node<Tp>* spec_node = NULL);
        ~Stack();
        Tp* Top();
        const Tp* Top() const;
        bool Empty();
        void Push(const Tp& value);
        void Pop();
};

template <class Tp>
Stack<Tp>::Stack() {
}

template <class Tp>
Stack<Tp>::Stack(DataStruct<Tp>* _struct, tree_node<Tp>* root_node, tree_node<Tp>* spec_node) {
    this->seq_builder_ = new SequenceBuilder<Tp>(_struct);
    this->seq_director_ = new SequenceDirector<Tp>(_struct);
    this->sequence_ = (Sequence<Tp>*)seq_director_->Construct(seq_builder_, 0, spec_node, root_node);
}

template <class Tp>
Stack<Tp>::~Stack() {
    delete sequence_;
    delete seq_director_;
    delete seq_builder_;
}

template <class Tp>
Tp* Stack<Tp>::Top() {
    return sequence_->Back();
}

template <class Tp>
const Tp* Stack<Tp>::Top() const {
    return sequence_->Back();
}

template <class Tp>
bool Stack<Tp>::Empty() {
    return sequence_->Empty();
}

template <class Tp>
void Stack<Tp>::Push(const Tp& value) {
    sequence_->PushBack(value);
}

template <class Tp>
void Stack<Tp>::Pop() {
    sequence_->PopBack();
}

#endif //STACK_H_
