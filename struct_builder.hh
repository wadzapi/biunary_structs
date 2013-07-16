#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_
#include "data_struct.hh"

template <class Tp>
class StructBuilderBase {
    public:
        StructBuilderBase();
        virtual ~StructBuilderBase();
    private:
        
    protected:
        virtual void AddNode(tree_node<Tp> root_node, DataStruct<Tp>* struct);
        virtual void ConnectNode(tree_node<Tp> root_node, tree_node<Tp> new_node);
};

template <class Tp>
class StructDirectorBase {
    private:
    protected:
        DataStruct<Tp> struct_;
        virtural tree_node<Tp>* ConstructNew(StructBuilder* builder);
        virtural void Construct(StructBuilder* builder, tree_node<Tp> root_node);
    public:
        StructDirectorBase(size_t phys_size, size_t logic_size) {
            struct_.Allocate(phys_size, logic_size);
        }   
        virtual ~StructDirectorBase();
};

#endif //STRUCT_BUILDER_H_
