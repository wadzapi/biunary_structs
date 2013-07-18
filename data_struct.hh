#ifndef DATA_STRUCT_H_
#define DATA_STRUCT_H_

#include "memory_heap.hh"
#include "biun.hh"

/* Class-container for logical and phisical storage                       */
/* functions to set phisical data, and to link for logical structure data */

template <class Tp>
class DataStruct {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<tree_node<Tp> > logical_data_;
    public:
        DataStruct();
        DataStruct(size_t phys_size, size_t logic_size);
        ~DataStruct();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        tree_node<Tp>* AddLogic();
        void SetData(tree_node<Tp>* node, Tp* value);
        void SetLeft(tree_node<Tp>* source_node, tree_node<Tp>* dest_node);
        void SetRight(tree_node<Tp>* source_node, tree_node<Tp>* dest_node);
        void Reserve(tree_node<Tp>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(tree_node<Tp>* logical_node);
        static Tp* GetData(tree_node<Tp>* node);
        static tree_node<Tp>* GetLeft(tree_node<Tp>* node);
        static tree_node<Tp>* GetRight(tree_node<Tp>* node);
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
tree_node<Tp>* DataStruct<Tp>::AddLogic() {
    tree_node<Tp>* logic = logical_data_.GetVacant();
    SetLeft(logic, logic);
    SetRight(logic, logic);
    logic->value = NULL;
    return logic;
}

template <class Tp>
void DataStruct<Tp>::SetData(tree_node<Tp>* node, Tp* value) {
    Unreserve(node->value);
    node->value = value;
    Reserve(value); 
}

template <class Tp>
void DataStruct<Tp>::SetLeft(tree_node<Tp>* source_node, tree_node<Tp>* dest_node) {
    Unreserve(source_node->left);
    source_node->left = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStruct<Tp>::SetRight(tree_node<Tp>* source_node, tree_node<Tp>* dest_node) {
    Unreserve(source_node->right);
    source_node->right = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStruct<Tp>::Reserve(tree_node<Tp>* logical_node) {
    logical_data_.Reserve(logical_node);
    physical_data_.Reserve(logical_node->value);
}

template <class Tp>
void DataStruct<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void DataStruct<Tp>::Unreserve(tree_node<Tp>* logical_node) {
    logical_data_.Unreserve(logical_node);
    physical_data_.Unreserve(logical_node->value);
}

template <class Tp>
void DataStruct<Tp>::Unreserve(Tp* physical_node) {
    physical_data_.Unreserve(physical_node);
}

#endif // DATA_STRUCT_H_
