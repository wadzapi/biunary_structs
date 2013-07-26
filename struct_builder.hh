#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_
#include "data_struct.hh"

template <class Tp>
class StructBuilderBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        size_t num_links_;
        void SetStruct(DataStruct<Tp> *_struct) { struct_ = _struct; }
    public:
        StructBuilderBase() : struct_(NULL) {}
        StructBuilderBase(DataStruct<Tp> *_struct, size_t num_links): struct_(_struct), num_links_(num_links) {}
        virtual ~StructBuilderBase() {}
        virtual tree_node<Tp> *AddNode() = 0;
        virtual tree_node<Tp> *AddNode(const Tp& value) = 0;
        virtual tree_node<Tp> *AddRoot() = 0;
        virtual void SetNodeValue(tree_node<Tp>* node, const Tp& value) = 0;
        virtual void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void DisconnectLeft(tree_node<Tp> *node) = 0;
        virtual void DisconnectRight(tree_node<Tp> *node) = 0;
        virtual void DeleteNode(tree_node<Tp>* node) = 0;
        virtual void DeleteRoot(tree_node<Tp>* node) = 0;
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
        virtual void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) = 0;
        virtual void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) = 0;
        virtual void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) = 0;
        virtual void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) = 0;
        virtual void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) = 0;
        virtual void RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *node) = 0;
        virtual void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) = 0;
        virtual void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) = 0;
};

#endif //STRUCT_BUILDER_H_
