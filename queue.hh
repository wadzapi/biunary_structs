#ifndef QUEUE_H_
#define QUEUE_H_

#include "sequence.hh"
#include "sequence_builder.hh"
#include "sequence_director.hh"

template <class Tp>
class Queue {
    private:
    protected:
        Sequence<Tp>* sequence_; 
        SequenceDirector<Tp>* seq_director_;
        SequenceBuilder<Tp>* seq_builder_;        
    public:
        Queue();
        Queue(DataStorage<Tp>* _storage, tree_node<Tp>* root_node = NULL, tree_node<Tp>* spec_node = NULL);
        ~Queue();
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
Queue<Tp>::Queue(DataStorage<Tp>* _storage, tree_node<Tp>* root_node, tree_node<Tp>* spec_node) { 
    this->seq_builder_ = new SequenceBuilder<Tp>(_storage);
    this->seq_director_ = new SequenceDirector<Tp>(_storage);
    this->sequence_ = (Sequence<Tp>*)seq_director_->Construct(seq_builder_, 0, spec_node, root_node);
}

template <class Tp>
Queue<Tp>::~Queue() {
    delete sequence_;
    delete seq_director_;
    delete seq_builder_;
}
        
template <class Tp>
Tp* Queue<Tp>::Front() {
    return sequence_->Front();
}

template <class Tp>
const Tp* Queue<Tp>::Front() const {
    return sequence_->Front();
}

template <class Tp>
Tp* Queue<Tp>::Back() {
    return sequence_->Back();
}

template <class Tp>
const Tp* Queue<Tp>::Back() const {
    return sequence_->Back();
}

template <class Tp>
bool Queue<Tp>::Empty() {
    return sequence_->Empty();
}

template <class Tp>
void Queue<Tp>::Push(const Tp& value) {
    sequence_->PushBack(value);
}

template <class Tp>
void Queue<Tp>::Pop() {
    sequence_->PopFront();
}

#endif //QUEUE_H_
