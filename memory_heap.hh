#ifndef HEAP_MEM_H_
#define HEAP_MEM_H_
#include <cstddef>

template <class Tp>
class MemoryHeap {
    private:
        size_t capacity_;
        Tp* values_;
        long* counters_;
        size_t search_idx_;
        size_t search_counter_;
        void CheckRange(size_t i);
        void CheckItem(Tp* item);

    public:
        MemoryHeap();
        ~MemoryHeap();
        size_t Capacity() const;
        Tp& operator[](size_t i);
        const Tp& operator[](size_t i) const;
        void Allocate(size_t capacity);
        void Free();
        Tp* GetVacant();
        void Resize(size_t new_size);
        Tp& At(size_t i);
        const Tp& At(size_t i) const;
        void Reserve(Tp* item);
        void Unreserve(Tp* item);
        Tp* Begin();
        const Tp* Begin() const;
        Tp* End();
        const Tp* End() const;
        Tp* AddItem(const Tp& val, bool reserve);
};

#include <cstring>
#include <stdexcept>

template <class Tp>
MemoryHeap<Tp>::MemoryHeap() : 
    capacity_(0),
    values_(NULL),
    counters_(NULL),
    search_idx_(0),
    search_counter_(0) {
}

template <class Tp>
MemoryHeap<Tp>::~MemoryHeap() {
    Free();
}

template <class Tp>
size_t MemoryHeap<Tp>::Capacity() const {
   return capacity_; 
}

template <class Tp>
Tp& MemoryHeap<Tp>::operator[](size_t i) {
    CheckRange();
    return *(values_ + i);
}

template <class Tp>
const Tp& MemoryHeap<Tp>::operator[](size_t i) const {
    CheckRange();
    return *(values_ + i);
}

template <class Tp>
void MemoryHeap<Tp>::Allocate(size_t capacity) {
    values_ = new Tp[capacity];
    counters_ = new long[capacity];
    capacity_ = capacity;
}

template <class Tp>
void MemoryHeap<Tp>::Free() {
    delete[] values_;
    delete[] counters_;
    capacity_ = 0;
}

template <class Tp>
Tp* MemoryHeap<Tp>::GetVacant() {
    Tp* vacant = NULL;
    while (search_counter_++ <= capacity_) {
        search_idx_ = (search_idx_ + 1) % capacity_;
        if (counters_[search_idx_] < 1) {
            vacant = (values_ + search_idx_);
        }
        
    }
    search_counter_ = 0;
    return vacant;
}


template <class Tp>
void MemoryHeap<Tp>::Reserve(Tp* item) {
    CheckItem(item);
    size_t item_idx = (item - values_) / sizeof(Tp);
    ++counters_[item_idx];
}

template <class Tp>
void MemoryHeap<Tp>::Unreserve(Tp* item) {
    CheckItem(item);
    size_t item_idx = (item - values_) / sizeof(Tp);
    --counters_[item_idx];
}

template <class Tp>
void MemoryHeap<Tp>::Resize(size_t new_size) {
    //save old params
    Tp* old_values = values_;
    long* old_counters = counters_;
    size_t old_capacity = capacity_;
    //alloc new and copy vals
    Allocate(new_size);
    memcpy(values_, old_values, sizeof(Tp) * old_capacity);
    memcpy(counters_, old_counters, sizeof(long) * old_capacity);
    delete[] old_values;
    delete[] old_counters;
}

template <class Tp>
Tp& MemoryHeap<Tp>::At(size_t i) {
    CheckRange(i);
    return (*this)[i];
}

template <class Tp>
const Tp& MemoryHeap<Tp>::At(size_t i)  const {
    CheckRange(i);
    return (*this)[i];
}

template <class Tp>
void MemoryHeap<Tp>::CheckRange(size_t i) {
    if (i >= capacity_) {
        throw std::range_error("heap");
    }
}

template <class Tp>
void MemoryHeap<Tp>::CheckItem(Tp* item) {
    if (item < Begin() || item > End()) {
        throw std::range_error("heap");
    }
}

template <class Tp>
Tp* MemoryHeap<Tp>::Begin() {
    return values_;
}

template <class Tp>
const Tp* MemoryHeap<Tp>::Begin() const {
    return values_;
}

template <class Tp>
Tp* MemoryHeap<Tp>::End() {
    return (values_ + capacity_);
}

template <class Tp>
const Tp* MemoryHeap<Tp>::End() const {
    return (values_ + capacity_);
}

template <class Tp>
Tp* MemoryHeap<Tp>::AddItem(const Tp& val, bool reserve) {
    Tp* newItem = GetVacant();
    if (newItem != NULL) {
        //copy object data to physical storage
        //new(newItem) Tp(val);///???
        //memcpy(newItem, val, sizeof(Tp);
        //*newItem = val;
        if (reserve) {
            Reserve(newItem);            
        }
    }
    return newItem;
}

#endif // HEAP_MEM_H_
