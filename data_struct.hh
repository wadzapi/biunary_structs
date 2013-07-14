#ifndef DATA_STRUCT_H_
#define DATA_STRUCT_H_

#include "memory_heap.h"
#include "biun.h"

/* Class-container for logical and phisical storage                       */
/* functions to set phisical data, and to link for logical structure data */

template <class Tp>
class DataStruct {
    private:
        MemoryHeap<Tp> physical_data_;
        MemoryHeap<tree_node<Tp> > logical_data_;
    public:
        DataStruct();
        ~DataStruct();
        void Allocate(size_t phys_size, size_t logic_size);
        void Free();
        Tp* AddData(const Tp& val);
        tree_node<Tp>* AddLogic();
        void SetData(tree_node<Tp>* node, Tp* value);
        void SetLeft(tree_node<Tp>* source_node, tree_node<Tp>* dest_node);
        void SetRight(tree_node<Tp>* source_node, tree_node<Tp>* dest_node);
        static Tp* GetData(tree_node<Tp>* node);
        static tree_node<Tp>* GetLeft(tree_node<Tp>* node);
        static tree_node<Tp>* GetRight(tree_node<Tp>* node);
};

template <class Tp>
DataStruct::DataStruct() {
}

template <class Tp>
DataStruct::~DataStruct() {
}

template <class Tp>
void DataStruct::Allocate(size_t phys_size, size_t logic_size) {
}

template <class Tp>
void DataStruct::Free() {
}

template <class Tp>
Tp* DataStruct::AddData(const Tp& val) {
}

template <class Tp>
tree_node<Tp>* DataStruct::AddLogic() {
}

template <class Tp>
void DataStruct::SetData(tree_node<Tp>* node, Tp* value) {
}

template <class Tp>
void DataStruct::SetLeft(tree_node<Tp>* source_node, tree_node<Tp> dest_node) {
}

template <class Tp>
void DataStruct::SetRight(tree_node<Tp>* source_node, tree_node<Tp> dest_node) {
}

#endif DATA_STRUCT_H_
