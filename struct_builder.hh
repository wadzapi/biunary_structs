#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_
#include "data_struct.hh"

template <class Tp>
class StructBuilderBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        size_t num_connections_;
        void SetStruct(DataStruct<Tp> *_struct) { struct_ = _struct; }
        virtual tree_node<Tp> *AddNodeLogic() = 0;
    public:
        StructBuilderBase() : struct_(NULL) {}
        StructBuilderBase(DataStruct<Tp> *_struct, size_t num_connections): struct_(_struct), num_connections_(num_connections) {}
        virtual ~StructBuilderBase() {}
        tree_node<Tp>* AddNode() {
            tree_node<Tp>* new_node = AddNodeLogic();
            AddNodeValue(new_node, Tp());
            return new_node;
        }
        tree_node<Tp>* AddNode(const Tp& value) {
            tree_node<Tp>* new_node = AddNodeLogic();
            AddNodeValue(new_node, value);
            return new_node;
        }
        tree_node<Tp> *AddRoot() {
            tree_node<Tp>* root_node = struct_->AddLogic();
            struct_->Reserve(root_node);
            return root_node;
        }
        void AddNodeValue(tree_node<Tp> *&node, const Tp& value) {
            Tp* new_val = struct_->AddData(value);
            struct_->SetData(node, new_val);
            struct_->Unreserve(new_val);
        }
        virtual void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void DisconnectLeft(tree_node<Tp> *node) = 0;
        virtual void DisconnectRight(tree_node<Tp> *node) = 0;
        virtual void DeleteNode(tree_node<Tp>* node) = 0;
        void DeleteRoot(tree_node<Tp>* node) {
            struct_->SetLeft(node, NULL);
            struct_->SetRight(node, NULL);
            struct_->Unreserve(node);
        }
};

template <class Tp>
class StructDirectorBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        void SetStruct(DataStruct<Tp> *_struct) { struct_ = _struct; }
        tree_node<Tp>* AddLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* value = NULL) {
            tree_node<Tp>* new_node; 
            if (value == NULL) {
                new_node = builder->AddNode();
            } else {
                new_node = builder->AddNode(*value);
            }
            builder->ConnectLeft(node, new_node);
        }
        tree_node<Tp>* AddRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* value = NULL) {
            tree_node<Tp>* new_node; 
            if (value == NULL) {
                new_node = builder->AddNode();
            } else {
                new_node = builder->AddNode(*value);
            }
            builder->ConnectRight(node, new_node);
        }
    public:
        StructDirectorBase() : struct_(NULL) {}
        StructDirectorBase(DataStruct<Tp> *_struct): struct_(_struct) {}
        virtual ~StructDirectorBase() {};
        virtual tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, const Tp* values = NULL) = 0;
        virtual void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) = 0;
        virtual void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) = 0;
        virtual void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) = 0;
        virtual void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) = 0;
        virtual void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) = 0;
        virtual void RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) = 0;
        virtual void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) = 0;
        virtual void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) = 0;
};

#endif //STRUCT_BUILDER_H_
