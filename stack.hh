#ifndef STACK_H_
#define STACK_H_

#include "sequence.hh"

template <class Tp>
class Stack {
    private:
         
    protected:
        Sequence<Tp> sequence_;
    public:
        Stack();
        Stack(size_t capacity);
        ~Stack();
        bool Empty();
        void Push(const Tp& value);
        void Pop();
        Tp* Top();
        const Tp* Top() const;
};

template <class Tp>
Stack<Tp>::Stack() {
}

template <class Tp>
Stack<Tp>::Stack(size_t capacity) {
    sequence_.Construct(capacity, false);
} 

template <class Tp>
Stack<Tp>::~Stack() {
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

#endif //STACK_H_
