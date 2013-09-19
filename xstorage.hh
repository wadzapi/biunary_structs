#ifndef XSTORAGE_H_
#define XSTORAGE_H_

#include "memory_heap.hh"
#include "xdata.hh"

template <class Tp>
class XStorage {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<XData<Tp> > logical_data_;
    public:
        XStorage();
        XStorage(size_t phys_size, size_t logic_size);
        ~XStorage();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        XData<Tp>* AddLogic(size_t num_links, size_t links_offset);
        void SetDataLogic(XData<Tp>* data_logic, const Tp& val);
        XData<Tp>* AddDataLogic(size_t num_links, size_t links_offset, const Tp& val);
        void Reserve(XData<Tp>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(XData<Tp>* logical_node);
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
    return new_item;
}

template <class Tp>
XData<Tp>* XStorage<Tp>::AddLogic(size_t num_links, size_t links_offset) {
    XData<Tp>* new_logic = logical_data_.GetVacant();
    new (new_logic) XData<Tp>(num_links, links_offset, NULL);
    new_logic->SetStorage(this);
    new_logic->ConnectRight(new_logic);
    return new_logic;
}

template <class Tp>
void XStorage<Tp>::SetData(XData<Tp>* data_logic, const Tp& val) {
    Tp* data_ptr = AddData(val);
    data_logic->storage_->Unreserve(data_logic->data); 
    data_logic->value = val;
    Reserve(data_ptr);
}

template <class Tp>
XData<Tp>* XStorage<Tp>::AddDataLogic(size_t num_links, size_t links_offset, const Tp& val) {
    XData<Tp>* data_logic = AddLogic(num_links, links_offset);
    SetDataLogic(data_logic, val);
    return data_logic;
}

template <class Tp>
void XStorage<Tp>::Reserve(XData<Tp>* logical_node) {
    logical_data_.Reserve(logical_node);
}

template <class Tp>
void XStorage<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void XStorage<Tp>::Unreserve(XData<Tp>* logical_node) {
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
