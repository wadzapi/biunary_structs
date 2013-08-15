#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include "memory_heap.hh"
#include "tree_node.hh"

/* Class-container for logical and phisical storage                       */
/* functions to set phisical data, and to link for logical structure data */

template <class Tp>
class DataStorage {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<tree_node<Tp, 2> > logical_data_;
    public:
        DataStorage();
        DataStorage(size_t phys_size, size_t logic_size);
        ~DataStorage();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        tree_node<Tp, 2>* AddLogic();
        void SetData(tree_node<Tp, 2>* node, Tp* value);
        void SetLeft(tree_node<Tp, 2>* source_node, tree_node<Tp, 2>* dest_node);
        void SetRight(tree_node<Tp, 2>* source_node, tree_node<Tp, 2>* dest_node);
        void Reserve(tree_node<Tp, 2>* logical_node);
        void Reserve(Tp* physical_node);
        void Unreserve(Tp* physical_node);
        void Unreserve(tree_node<Tp, 2>* logical_node);
        static Tp* GetData(tree_node<Tp, 2>* node);
        static tree_node<Tp, 2>* GetLeft(tree_node<Tp, 2>* node);
        static tree_node<Tp, 2>* GetRight(tree_node<Tp, 2>* node);
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
tree_node<Tp, 2>* DataStorage<Tp>::AddLogic() {
    tree_node<Tp, 2>* logic = logical_data_.GetVacant();
    SetLeft(logic, logic);
    SetRight(logic, logic);
    logic->value = NULL;
    return logic;
}

template <class Tp>
void DataStorage<Tp>::SetData(tree_node<Tp, 2>* node, Tp* value) {
    Unreserve(node->value);
    node->value = value;
    Reserve(value); 
}

template <class Tp>
void DataStorage<Tp>::SetLeft(tree_node<Tp, 2>* source_node, tree_node<Tp, 2>* dest_node) {
    Unreserve(source_node->links[0]);
    source_node->links[0] = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStorage<Tp>::SetRight(tree_node<Tp, 2>* source_node, tree_node<Tp, 2>* dest_node) {
    Unreserve(source_node->links[1]);
    source_node->links[1] = dest_node;
    Reserve(dest_node);
}

template <class Tp>
void DataStorage<Tp>::Reserve(tree_node<Tp, 2>* logical_node) {
    logical_data_.Reserve(logical_node);
}

template <class Tp>
void DataStorage<Tp>::Reserve(Tp* physical_node) {
    physical_data_.Reserve(physical_node);
}

template <class Tp>
void DataStorage<Tp>::Unreserve(tree_node<Tp, 2>* logical_node) {
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
