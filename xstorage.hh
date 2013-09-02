#ifndef XSTORAGE_H_
#define XSTORAGE_H_

#include "memory_heap.hh"
#include "xnode.hh"

template <class Tp>
class XStorage {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<XNode<Tp> > logical_data_;
    public:
        XStorage();
        XStorage(size_t phys_size, size_t logic_size);
        ~XStorage();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        XNode<Tp>* AddLogic(size_t num_links, size_t links_offset);
        XNode<Tp>* AddDataLogic(size_t num_links, size_t links_offset, const Tp& val);
        void Reserve(XNode<Tp>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(XNode<Tp>* logical_node);
        static Tp* GetData(XNode<Tp>* node);
        static XNode<Tp>* GetLeft(XNode<Tp>* node);
        static XNode<Tp>* GetRight(XNode<Tp>* node);
        void PrintCounters() const;
};

template <class Tp>
XStorage<Tp>::XStorage() {
}

template <class Tp>
XStorage<Tp>::XStorage(size_t phys_size, size_t logic_size) {
    Allocate(phys_size, logic_size);
}

template <class Tp>
XStorage<Tp>::~XStorage() {
}

template <class Tp>
void XStorage<Tp>::Allocate(size_t phys_size, size_t logic_size) {
    physical_data_.Allocate(phys_size);
    logical_data_.Allocate(logic_size);
}

template <class Tp>
void XStorage<Tp>::Free() {
    physical_data_.Free();
    logical_data_.Free();
}

template <class Tp>
Tp* XStorage<Tp>::AddData(const Tp& val) {
    Tp* new_item = physical_data_.GetVacant();
    new (new_item) Tp(val);
    Reserve(new_item);
    return new_item;
}

template <class Tp>
XNode<Tp>* XStorage<Tp>::AddLogic(size_t num_links, size_t links_offset) {
    XNode<Tp>* new_logic = logical_data_.GetVacant();
    new (new_logic) XNode<Tp>(num_links, links_offset, NULL);
    new_logic->SetStorage(this);
    new_logic->ConnectRight(new_logic);
    return new_logic;
}

template <class Tp>
XNode<Tp>* XStorage<Tp>::AddDataLogic(size_t num_links, size_t links_offset, const Tp& val) {
    XStrucNode<Tp>* data_logic = AddLogic(num_links, links_offset);
    Tp* data_ptr = AddData(val);
    data_logic -> SetData(data_ptr);
}

template <class Tp>
void XStorage<Tp>::Reserve(XNode<Tp>* logical_node) {
    logical_data_.Reserve(logical_node);
}

template <class Tp>
void XStorage<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void XStorage<Tp>::Unreserve(XNode<Tp>* logical_node) {
    logical_data_.Unreserve(logical_node);
}

template <class Tp>
void XStorage<Tp>::Unreserve(Tp* physical_node) {
    physical_data_.Unreserve(physical_node);
}

template <class Tp>
void XStorage<Tp>::PrintCounters() const {
    printf("Logical storage counters\n");
    logical_data_.PrintCounters();
    printf("Physical storage counters\n");
    physical_data_.PrintCounters();
}

#endif // XSTORAGE_H_
