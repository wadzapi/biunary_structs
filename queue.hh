#ifndef QUEUE_H_
#define QUEUE_H_

#include "sequence.hh"

template <class Tp>
class Queue : public StructBase<Tp> {
    private:
        
    protected:
        Sequence<Tp> sequence_;
    public:
        Queue();
        Queue(tree_node<Tp>* root_node, DataStruct<Tp>* _struct);
        Queue(DataStruct<Tp>* _struct);
        ~Queue();
        void Construct(DataStruct<Tp>* _struct, tree_node<Tp>* root_node = NULL);
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        const Tp* Back() const;
        bool Empty();
        void Push(const Tp& value);
        void Pop();
};

template <class Tp>
Queue<Tp>::Queue() {
}
        
template <class Tp>
Queue<Tp>::Queue(tree_node<Tp>* root_node, DataStruct<Tp>* _struct) : sequence_(root_node, _struct) {
    Construct(_struct, root_node);
}

template <class Tp>
Queue<Tp>::Queue(DataStruct<Tp>* _struct) : sequence_(_struct) {
    Construct(_struct);
}

template <class Tp>
Queue<Tp>::~Queue() {
}
        
template <class Tp>
void Queue<Tp>::Construct(DataStruct<Tp>* _struct, tree_node<Tp>* root_node) {
    this->struct_ = _struct; 
    tree_node<Tp>* new_root = sequence_.GetRoot();
    SetRoot(new_root);
}

template <class Tp>
Tp* Queue<Tp>::Front() {
    return sequence_.Front();
}

template <class Tp>
const Tp* Queue<Tp>::Front() const {
    return sequence_.Front();
}

template <class Tp>
Tp* Queue<Tp>::Back() {
    return sequence_.Back();
}

template <class Tp>
const Tp* Queue<Tp>::Back() const {
    return sequence_.Back();
}

template <class Tp>
bool Queue<Tp>::Empty() {
    return sequence_.Empty();
}

template <class Tp>
void Queue<Tp>::Push(const Tp& value) {
    sequence_.PushBack(value);
}

template <class Tp>
void Queue<Tp>::Pop() {
    sequence_.PopFront();
}

#endif //QUEUE_H_
