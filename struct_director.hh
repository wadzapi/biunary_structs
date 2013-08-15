#ifndef STRUCT_DIRECTOR_H_
#define STRUCT_DIRECTOR_H_

#include "struct_base.hh"

template <class Tp, size_t NUM_LINKS>
class StructDirectorBase {
    private:
    protected:
        DataStorage<Tp, NUM_LINKS>* storage_;
        void SetStruct(DataStorage<Tp, NUM_LINKS> *_storage) { storage_ = _storage; }
        tree_node<Tp, NUM_LINKS>* AddLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, tree_node<Tp, NUM_LINKS>* node, const Tp* value = (Tp*)NULL) {
            tree_node<Tp, NUM_LINKS>* new_node; 
            if (value == NULL) {
                new_node = builder->AddNode();
            } else {
                new_node = builder->AddNode(*value);
            }
            builder->ConnectLeft(node, new_node);
            return new_node;
        }
        tree_node<Tp, NUM_LINKS>* AddRight(StructBuilderBase<Tp, NUM_LINKS> *builder, tree_node<Tp, NUM_LINKS>* node, const Tp* value = (Tp*)NULL) {
            tree_node<Tp, NUM_LINKS>* new_node; 
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
        StructDirectorBase(DataStorage<Tp, NUM_LINKS> *_storage): storage_(_storage) {}
        virtual ~StructDirectorBase() {};
        virtual StructBase<Tp, NUM_LINKS>* Construct(StructBuilderBase<Tp, NUM_LINKS> *builder, size_t num_nodes, tree_node<Tp, NUM_LINKS>* spec_node = NULL, tree_node<Tp, NUM_LINKS>* root_node = NULL, const Tp* values = NULL) = 0;
        virtual void ConnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right) = 0;
        virtual void ConnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right) = 0;
        virtual void DisconnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node) = 0;
        virtual void DisconnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node) = 0;
        virtual void RemoveNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS> *node) = 0;
        virtual void RemoveSpecRootNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) = 0;
        virtual void Clear(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) = 0;
        virtual void Delete(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) = 0;
};

#endif //STRUCT_DIRECTOR_H_
