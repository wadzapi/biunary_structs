#ifndef STRUCT_DIRECTOR_H_
#define STRUCT_DIRECTOR_H_

#include "struct_base.hh"

template <class Tp>
class StructDirectorBase {
    private:
    protected:
        DataStorage<Tp>* storage_;
        void SetStruct(DataStorage<Tp> *_storage) { storage_ = _storage; }
        tree_node<Tp>* AddLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* value = (Tp*)NULL) {
            tree_node<Tp>* new_node; 
            if (value == NULL) {
                new_node = builder->AddNode();
            } else {
                new_node = builder->AddNode(*value);
            }
            builder->ConnectLeft(node, new_node);
            return new_node;
        }
        tree_node<Tp>* AddRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* value = (Tp*)NULL) {
            tree_node<Tp>* new_node; 
            if (value == NULL) {
                new_node = builder->AddNode();
            } else {
                new_node = builder->AddNode(*value);
            }
            builder->ConnectRight(node, new_node);
            return new_node;
        }
    public:
        StructDirectorBase() : storage_(NULL) {}
        StructDirectorBase(DataStorage<Tp> *_storage): storage_(_storage) {}
        virtual ~StructDirectorBase() {};
        virtual StructBase<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>* root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL) = 0;
        virtual void ConnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) = 0;
        virtual void ConnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) = 0;
        virtual void DisconnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node) = 0;
        virtual void DisconnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node) = 0;
        virtual void RemoveNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node) = 0;
        virtual void RemoveSpecRootNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) = 0;
        virtual void Clear(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) = 0;
        virtual void Delete(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) = 0;
};

#endif //STRUCT_DIRECTOR_H_
