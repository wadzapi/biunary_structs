#ifndef STRUCT_BASE_H_
#define STRUCT_BASE_H_

#include "data_struct.hh"

template <class Tp>
class StructBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        tree_node<Tp>* spec_node_;
        tree_node<Tp>* root_node_;
        bool is_built_;
    public:
        StructBase() : struct_(NULL), root_node_(NULL), spec_node_(NULL), is_built_(false) {}
        StructBase(DataStruct<Tp>* _struct, tree_node<Tp>* root_node, tree_node<Tp>* spec_node) : struct_(_struct), spec_node_(spec_node), root_node_(root_node),  is_built_(false) {}
        virtual ~StructBase() {
        }
        void SetRootNode(tree_node<Tp>* root_node) {
            if (this->root_node_ != root_node) {
                this->root_node_ = root_node;
                UpdateSpecNode();
            }
        }
        tree_node<Tp>* GetRootNode() {
            return this->root_node_;
        }
        void SetSpecNode(tree_node<Tp>* spec_node) {
            if (this->spec_node_ != spec_node) {
                this->spec_node_ = spec_node;
            }
        }
        tree_node<Tp>* GetSpecNode() {
            return this->spec_node_;
        }
        virtual void UpdateSpecNode() = 0;
};
#endif //STRUCT_BASE_H_
