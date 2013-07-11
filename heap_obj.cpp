#include "heap_obj.hh"
#include <cstring>
#include <stdexcept>

template <class Tp>
Heap<Tp>::Heap() : 
    capacity_(0),
    values_(NULL),
    counters_(NULL),
    search_idx_(0),
    search_counter_(0) {
}

template <class Tp>
Heap<Tp>::~Heap() {
    Free();
}

template <class Tp>
size_t Heap<Tp>::Capacity() const {
   return capacity_; 
}

template <class Tp>
&Tp Heap<Tp>::operator[](size_t i) {
    CheckRange();
    return *(values_ + i);
}

template <class Tp>
const &Tp Heap<Tp>::operator[](size_t i) const {
    CheckRange();
    return *(values_ + i);
}

template <class Tp>
void Heap<Tp>::Allocate(size_t capacity) {
    values_ = new Tp[capacity];
    counters_ = new long[capacity];
    capacity_ = capacity;
}

template <class Tp>
void Heap<Tp>::Free() {
    delete[] values_;
    delete[] counters_;
    capacity_ = 0;
}

template <class Tp>
Tp* Heap<Tp>::GetVacant() {
    Tp* vacant = NULL;
    while (search_counter_++ <= capacity_) {
        search_idx_ = (search_idx_ + 1) % capacity_;
        if (counters_[search_idx_] < 1) {
            vacant = (begin_ + search_idx_);
        }
        
    }
    search_counter_ = 0;
    return vacant;
}


template <class Tp>
Heap<Tp>::Reserve(Tp* item) {
    CheckItem(item);
    size_t item_idx = (item - begin_) / sizeof(Tp);
    ++counters_[item_idx];
}

template <class Tp>
Heap<Tp>::Unreserve(Tp* item) {
    CheckItem(item);
    size_t item_idx = (item - begin_) / sizeof(Tp);
    --counters_[item_idx];
}

template <class Tp>
bool Heap<Tp>::Resize(size_t new_size) {
    //save old params
    Tp* old_values = values_;
    long* old_counters = counters_;
    size_t old_capacity = capacity_;
    //alloc new and copy vals
    Alloc(new_size);
    memcpy(values_, old_values, sizeof(Tp) * old_capacity);
    memcpy(counters_, old_counters, sizeof(long) * old_capacity);
    delete[] old_values;
    delete[] old_counters;
}

template <class Tp>
&Tp Heap<Tp>::At(size_t i) {
    CheckRange(i);
    return (*this)[i];
}

template <class Tp>
const &Tp Heap<Tp>::At(size_t i)  const {
    CheckRange(i);
    return (*this)[i];
}

template <class Tp>
void Heap<Tp>::CheckRange(size_t i) {
    if (i >= capacity_) {
        throw std::range_error("heap");
}

template <class Tp>
void Heap<Tp>::CheckItem(Tp* item) {
    if (item < Begin() || item > End()) {
        throw std::range_error("heap");
    }
}

template <class Tp>
Tp* Heap<Tp>::Begin() {
    return begin_;
}

template <class Tp>
const Tp* Heap<Tp>::Begin() const {
    return begin_;
}

template <class Tp>
Tp* Heap<Tp>::End() {
    return (begin_ + capacity_);
}

template <class Tp>
const Tp* Heap<Tp>::End() const {
    return (begin_ + capacity_);
}
