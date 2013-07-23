#ifndef QUEUE_H_
#define QUEUE_H_

#include "sequence.hh"

template <class Tp>
class Queue {
    private:
        
    protected:
        Sequence<Tp> sequence_;
    public:
        Queue();
        Queue(size_t capacity);
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
Queue<Tp>::Queue(size_t capacity) {
    sequence_.Construct(capacity, false);
}

template <class Tp>
Queue<Tp>::~Queue() {
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
