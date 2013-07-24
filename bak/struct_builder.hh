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
        virtual tree_node<Tp> *AddNode(DataStruct<Tp> *_struct, const Tp& value) = 0;
        virtual tree_node<Tp> *AddRoot(DataStruct<Tp> *_struct) = 0;
        virtual void SetNodeValue(DataStruct<Tp> *_struct, tree_node<Tp>* node, const Tp& value) = 0;
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
        virtual tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) = 0;
        virtual void Connect(tree_node<Tp>* root_node, tree_node<Tp>* new_node) = 0;
        virtual void DeleteNode(tree_node<Tp>* node) = 0;
};

#endif //STRUCT_BUILDER_H_
