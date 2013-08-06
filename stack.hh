#ifndef STACK_H_
#define STACK_H_

#include "sequence.hh"

template <class Tp>
class Stack : public StructBase<Tp> {
    private:
         
    protected:
        Sequence<Tp> sequence_;
    public:
        Stack();
        Stack(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct);
        Stack(DataStruct<Tp>* _struct);
        ~Stack();
        void Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>*& spec_node = NULL, tree_node<Tp>*& root_node = NULL, const Tp* values = NULL);
        bool Empty();
        void Push(const Tp& value);
        void Pop();
        Tp* Top();
        const Tp* Top() const;
        void UpdateSpecNode();
};

template <class Tp>
Stack<Tp>::Stack() {
}

template <class Tp>
Stack<Tp>::Stack(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct) : sequence_(spec_node, _struct) {
    Construct(_struct, 0, spec_node);
}

template <class Tp>
Stack<Tp>::Stack(DataStruct<Tp>* _struct) : sequence_(_struct) {
    Construct(_struct, 0);
}

template <class Tp>
Stack<Tp>::~Stack() {
}

template <class Tp>
void Stack<Tp>::Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>*& spec_node, tree_node<Tp>*& root_node, const Tp* values) {
    this->struct_ = _struct; 
    tree_node<Tp>* new_root = sequence_.GetSpecNode();
    SetSpecNode(new_root);
} 

template <class Tp>
bool Stack<Tp>::Empty() {
    return sequence_.Empty();
}

template <class Tp>
void Stack<Tp>::Push(const Tp& value) {
    sequence_.PushBack(value);
}

template <class Tp>
void Stack<Tp>::Pop() {
    sequence_.PopBack();
}

template <class Tp>
Tp* Stack<Tp>::Top() {
    return sequence_.Back();
}

template <class Tp>
const Tp* Stack<Tp>::Top() const {
    return sequence_.Back();
}

template <class Tp>
const Tp* Stack<Tp>::UpdateSpecNode() {
    this->sequence_->UpdateSpecNode();
}

#endif //STACK_H_
