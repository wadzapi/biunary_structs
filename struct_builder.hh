#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_
#include "data_struct.hh"

template <class Tp>
class StructBuilderBase {
    private:
    protected:
    public:
        StructBuilderBase() {};
        virtual ~StructBuilderBase() {};
        virtual tree_node<Tp> *AddNode(DataStruct<Tp> *_struct) = 0;
        virtual void ConnectNode(DataStruct<Tp> *_struct, tree_node<Tp> *root_node, tree_node<Tp> *new_node) = 0;
};

template <class Tp>
class StructDirectorBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        void SetStruct(DataStruct<Tp> *_struct) { struct_ = _struct; }
    public:
        StructDirectorBase() : struct_(NULL) {}
        StructDirectorBase(DataStruct<Tp> *_struct): struct_(_struct) {}
        virtual ~StructDirectorBase() {};
        virtual tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes) = 0;
};

#endif //STRUCT_BUILDER_H_
