#ifndef STRUCT_BASE_H_
#define STRUCT_BASE_H_

#include "struct_builder.hh"

template <class Tp>
class StructBase {
    private:
    protected:
        DataStruct<Tp>* struct_;
        tree_node<Tp>* root_node_;
        StructBuilderBase<Tp>* builder_;
        StructDirectorBase<Tp>* director_;
        bool is_built_;
    public:
        StructBase() : struct_(NULL), root_node_(NULL), builder_(NULL), director_(NULL), is_built_(false) { }
        StructBase(tree_node<Tp>* root_node, DataStruct<Tp>* _struct) : builder_(NULL), director_(NULL) {
            root_node_ = root_node;
            Construct(_struct);
        }
        StructBase(DataStruct<Tp>* _struct) : root_node_(NULL), builder_(NULL), director_(NULL) {
            Construct(_struct);
            root_node_ = director_->Construct(builder_, 0);
        }
        virtual void Construct(DataStruct<Tp>* _struct) {};
        virtual ~StructBase() {
            if (is_built_) {
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
            Delete();
        }
        void SetRoot(tree_node<Tp>* root_node);
        tree_node<Tp>* GetRoot();
        void Delete() {
            director_->Delete(builder_, root_node_);
        }
};

#endif //STRUCT_BASE_H_
