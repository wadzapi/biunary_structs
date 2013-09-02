#ifndef XFACTORY_H_
#define XFACTORY_H_

#include "sequence.hh"
#include "stack.hh"
#include "queue.hh"

template <class Tp>
class XFactory {
    private:
        XStorage<Tp>* storage_;
        bool is_built_;

    public:
        XFactory();
        XFactory(size_t phys_capacity, size_t logical_capacity);
        ~XFactory();
        void Construct(size_t phys_capacity, size_t logical_capacity);
        //Make structure methods
        Sequence<Tp>* MakeSequence();
        Stack<Tp>* MakeStack();
        Queue<Tp>* MakeQueue();
};

template <class Tp>
XFactory<Tp>::XFactory() : is_built_(false) {
}

template <class Tp>
XFactory<Tp>::XFactory(size_t phys_capacity, size_t logical_capacity) : is_built_(false) {
        Construct(phys_capacity, logical_capacity);
}

template <class Tp>
void XFactory<Tp>::Construct(size_t phys_capacity, size_t logic_capacity) {
    storage_ = new XStorage<Tp>(phys_capacity, logic_capacity);
    is_built_ = true;
}

template <class Tp>
XFactory<Tp>::~XFactory() {
    if (is_built_) {
        delete storage_;
        storage_ = NULL;
        is_built_ = false;
    }
}

template <class Tp>
Sequence<Tp>* XFactory<Tp>::MakeSequence() {
    Sequence<Tp>* sequence = new Sequence<Tp>(storage_);
    return sequence;
}

template <class Tp>
Stack<Tp>* XFactory<Tp>::MakeStack() {
    Stack<Tp>* stack = new Stack<Tp>(storage_);
    return stack;
}

template <class Tp>
Queue<Tp>* XFactory<Tp>::MakeQueue() {
    Queue<Tp>* queue = new Queue<Tp>(storage_);
    return queue;
}

#endif // XFACTORY_H_
