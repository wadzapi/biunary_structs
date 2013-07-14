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
        Tp* AddData();

};

#endif DATA_STRUCT_H_
