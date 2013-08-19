#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include "memory_heap.hh"
#include "xstruct_node.hh"

template <class Tp>
class DataStorage {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<XStructNode<Tp> > logical_data_;
    public:
        DataStorage();
        DataStorage(size_t phys_size, size_t logic_size);
        ~DataStorage();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        XStructNode<Tp>* AddLogic(size_t num_links, size_t links_offset);
        XStructNode<Tp>* AddDataLogic(size_t num_links, size_t links_offset, const Tp& val);
        void Reserve(XStructNode<Tp>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(XStructNode<Tp>* logical_node);
        static Tp* GetData(XStructNode<Tp>* node);
        static XStructNode<Tp>* GetLeft(XStructNode<Tp>* node);
        static XStructNode<Tp>* GetRight(XStructNode<Tp>* node);
        void PrintCounters() const;
};

template <class Tp>
DataStorage<Tp>::DataStorage() {
}

template <class Tp>
DataStorage<Tp>::DataStorage(size_t phys_size, size_t logic_size) {
    Allocate(phys_size, logic_size);
}

template <class Tp>
DataStorage<Tp>::~DataStorage() {
}

template <class Tp>
void DataStorage<Tp>::Allocate(size_t phys_size, size_t logic_size) {
    physical_data_.Allocate(phys_size);
    logical_data_.Allocate(logic_size);
}

template <class Tp>
void DataStorage<Tp>::Free() {
    physical_data_.Free();
    logical_data_.Free();
}

template <class Tp>
Tp* DataStorage<Tp>::AddData(const Tp& val) {
    Tp* new_item = physical_data_.GetVacant();
    new (new_item) Tp(val);
    Reserve(new_item);
    return new_item;
}

template <class Tp>
XStructNode<Tp>* DataStorage<Tp>::AddLogic(size_t num_links, size_t links_offset) {
    XStructNode<Tp>* new_logic = logical_data_.GetVacant();
    new (new_logic) XStructNode<Tp>(num_links, links_offset, NULL);
    new_logic->SetStorage(this);
    new_logic->ConnectRight(new_logic);
    return new_logic;
}

template <class Tp>
XStructNode<Tp>* DataStorage<Tp>::AddDataLogic(size_t num_links, size_t links_offset, const Tp& val) {
    XStrucNode<Tp>* data_logic = AddLogic(num_links, links_offset);
    Tp* data_ptr = AddData(val);
    data_logic -> SetData(data_ptr);
}

template <class Tp>
void DataStorage<Tp>::Reserve(XStructNode<Tp>* logical_node) {
    logical_data_.Reserve(logical_node);
}

template <class Tp>
void DataStorage<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void DataStorage<Tp>::Unreserve(XStructNode<Tp>* logical_node) {
    logical_data_.Unreserve(logical_node);
}

template <class Tp>
void DataStorage<Tp>::Unreserve(Tp* physical_node) {
    physical_data_.Unreserve(physical_node);
}

template <class Tp>
void DataStorage<Tp>::PrintCounters() const {
    printf("Logical storage counters\n");
    logical_data_.PrintCounters();
    printf("Physical storage counters\n");
    physical_data_.PrintCounters();
}

#endif // DATA_STORAGE_H_
