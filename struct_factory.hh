#ifndef STRUCT_FACTORY_H_
#define STRUCT_FACTORY_H_

#include "sequence.hh"
#include "stack.hh"
#include "queue.hh"

template <class Tp>
class StructFactory {
    private:
        DataStruct<Tp>* struct_;
        bool is_built_;

    public:
        StructFactory();
        StructFactory(size_t phys_capacity, size_t logical_capacity);
        ~StructFactory();
        void Construct(size_t phys_capacity, size_t logical_capacity);
        //Make structure methods
        Sequence<Tp>* MakeSequence();
        Stack<Tp>* MakeStack();
        Queue<Tp>* MakeQueue();
};

template <class Tp>
StructFactory<Tp>::StructFactory() : is_built_(false) {
}

template <class Tp>
StructFactory<Tp>::StructFactory(size_t phys_capacity, size_t logical_capacity) : is_built_(false) {
        Construct(phys_capacity, logical_capacity);
}

template <class Tp>
void StructFactory<Tp>::Construct(size_t phys_capacity, size_t logic_capacity) {
    struct_ = new DataStruct<Tp>(phys_capacity, logic_capacity);
    is_built_ = true;
}

template <class Tp>
StructFactory<Tp>::~StructFactory() {
    if (is_built_) {
        delete struct_;
        struct_ = NULL;
        is_built_ = false;
    }
}

template <class Tp>
Sequence<Tp>* StructFactory<Tp>::MakeSequence() {
    Sequence<Tp>* sequence = new Sequence<Tp>(struct_);
    return sequence;
}

template <class Tp>
Stack<Tp>* StructFactory<Tp>::MakeStack() {
    Stack<Tp>* stack = new Stack<Tp>(struct_);
    return stack;
}

template <class Tp>
Queue<Tp>* StructFactory<Tp>::MakeQueue() {
    Queue<Tp>* queue = new Queue<Tp>(struct_);
    return queue;
}

#endif //STRUCT_FACTORY_H_
