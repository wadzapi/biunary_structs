#ifndef STRUCT_BASE_H_
#define STRUCT_BASE_H_

#include "struct_builder.hh"

template <class Tp>
class StructBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        tree_node<Tp>* spec_node_;
        tree_node<Tp>* root_node_;
        StructBuilderBase<Tp>* builder_;
        StructDirectorBase<Tp>* director_;
        bool is_built_;
    public:
        StructBase() : struct_(NULL), spec_node_(NULL), builder_(NULL), director_(NULL), is_built_(false) { }
        virtual void Construct(DataStruct<Tp>* _struct, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>* root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL) = 0;
        virtual ~StructBase() {
            if (is_built_) {
                Delete();
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
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
        void Delete() {
            director_->Delete(builder_, spec_node_);
        }
        virtual void UpdateSpecNode() = 0;
};

#endif //STRUCT_BASE_H_
