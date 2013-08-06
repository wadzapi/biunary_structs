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
        Queue(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct);
        Queue(DataStruct<Tp>* _struct);
        ~Queue();
        void Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>*& spec_node = NULL, tree_node<Tp>*& root_node = NULL, const Tp* values = NULL); 
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        const Tp* Back() const;
        bool Empty();
        void Push(const Tp& value);
        void Pop();
        void UpdateSpecNode();
};

template <class Tp>
Queue<Tp>::Queue() {
}
        
template <class Tp>
Queue<Tp>::Queue(tree_node<Tp>* spec_node, DataStruct<Tp>* _struct) : sequence_(spec_node, _struct) {
    Construct(_struct, 0 spec_node);
}

template <class Tp>
Queue<Tp>::Queue(DataStruct<Tp>* _struct) : sequence_(_struct) {
    Construct(_struct, 0);
}

template <class Tp>
Queue<Tp>::~Queue() {
}
        
template <class Tp>
void Queue<Tp>::Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>*& spec_node, tree_node<Tp>*& root_node, const Tp* values) {
    this->struct_ = _struct; 
    SetSpecNode(sequence_.GetSpecNode());
    SetRootNode(sequence_.GetRootNode());
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

template <class Tp>
void Queue<Tp>::UpdateSpecNode() {
    this->sequence_->UpdateSpecNode();
}

#endif //QUEUE_H_
