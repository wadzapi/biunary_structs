#ifndef HEAP_MEM_H_
#define HEAP_MEM_H_

template <class Tp>
class Heap {
    private:
        size_t capacity_;
        Tp* values_;
        long* counters_;
        size_t search_idx_;
        size_t search_counter_;
        void CheckRange(size_t i);
        void CheckItem(Tp* item);

    public:
        Heap();
        Heap~();
        size_t Capacity() const;
        &Tp operator[](size_t i);
        const &Tp operator[](size_t i) const;
        Allocate(size_t capacity);
        void Free();
        Tp* GetVacant();
        bool Resize();
        &Tp At(size_t i);
        const &Tp At(size_t i) const;
        void Reserve(Tp* item);
        void Unreserve(Tp* item);
        Tp* Begin();
        const Tp* Begin() const;
        Tp* End();
        const Tp* End() const;
};
#endif // HEAP_MEM_H_
