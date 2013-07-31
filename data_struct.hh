#ifndef DATA_STRUCT_H_
#define DATA_STRUCT_H_

#include "memory_heap.hh"
#include "bin_bin_tree_node.hh"

/* Class-container for logical and phisical storage                       */
/* functions to set phisical data, and to link for logical structure data */

template <class Tp>
class DataStruct {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<bin_tree_node<Tp> > logical_data_;
    public:
        DataStruct();
        DataStruct(size_t phys_size, size_t logic_size);
        ~DataStruct();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        bin_tree_node<Tp>* AddLogic();
        void SetData(bin_tree_node<Tp>* node, Tp* value);
        void SetLeft(bin_tree_node<Tp>* source_node, bin_tree_node<Tp>* dest_node);
        void SetRight(bin_tree_node<Tp>* source_node, bin_tree_node<Tp>* dest_node);
        void Reserve(bin_tree_node<Tp>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(bin_tree_node<Tp>* logical_node);
        static Tp* GetData(bin_tree_node<Tp>* node);
        static bin_tree_node<Tp>* GetLeft(bin_tree_node<Tp>* node);
        static bin_tree_node<Tp>* GetRight(bin_tree_node<Tp>* node);
        void PrintCounters() const;
};

template <class Tp>
DataStruct<Tp>::DataStruct() {
}

template <class Tp>
DataStruct<Tp>::DataStruct(size_t phys_size, size_t logic_size) {
    Allocate(phys_size, logic_size);
}

template <class Tp>
DataStruct<Tp>::~DataStruct() {
}

template <class Tp>
void DataStruct<Tp>::Allocate(size_t phys_size, size_t logic_size) {
    physical_data_.Allocate(phys_size);
    logical_data_.Allocate(logic_size);
}

template <class Tp>
void DataStruct<Tp>::Free() {
    physical_data_.Free();
    logical_data_.Free();
}

template <class Tp>
Tp* DataStruct<Tp>::AddData(const Tp& val) {
    Tp* new_item = physical_data_.GetVacant();
    new (new_item) Tp(val);
    Reserve(new_item);
    return new_item;
}

template <class Tp>
bin_tree_node<Tp>* DataStruct<Tp>::AddLogic() {
    bin_tree_node<Tp>* logic = logical_data_.GetVacant();
    SetLeft(logic, logic);
    SetRight(logic, logic);
    logic->value = NULL;
    return logic;
}

template <class Tp>
void DataStruct<Tp>::SetData(bin_tree_node<Tp>* node, Tp* value) {
    Unreserve(node->value);
    node->value = value;
    Reserve(value); 
}

template <class Tp>
void DataStruct<Tp>::SetLeft(bin_tree_node<Tp>* source_node, bin_tree_node<Tp>* dest_node) {
    Unreserve(source_node->left);
    source_node->left = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStruct<Tp>::SetRight(bin_tree_node<Tp>* source_node, bin_tree_node<Tp>* dest_node) {
    Unreserve(source_node->right);
    source_node->right = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStruct<Tp>::Reserve(bin_tree_node<Tp>* logical_node) {
    logical_data_.Reserve(logical_node);
}

template <class Tp>
void DataStruct<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void DataStruct<Tp>::Unreserve(bin_tree_node<Tp>* logical_node) {
    logical_data_.Unreserve(logical_node);
}

template <class Tp>
void DataStruct<Tp>::Unreserve(Tp* physical_node) {
    physical_data_.Unreserve(physical_node);
}

template <class Tp>
void DataStruct<Tp>::PrintCounters() const {
    printf("Logical storage counters\n");
    logical_data_.PrintCounters();
    printf("Physical storage counters\n");
    physical_data_.PrintCounters();
}

#endif // DATA_STRUCT_H_
