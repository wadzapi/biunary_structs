#ifndef STRUCT_FACTORY_H_
#define STRUCT_FACTORY_H_

#include "sequence.hh"

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
        Sequence<Tp>* MakeSequence();
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
    Sequence<Tp>* seq = new Sequence<Tp>(struct_);
    return seq;
}

#endif //STRUCT_FACTORY_H_
