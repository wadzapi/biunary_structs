#ifndef STRUCT_H_
#define STRUCT_H_

#include "struct_base.hh"
#include "struct_builder.hh"
#include "struct_director.hh"

template <class Tp>
class Struct : public StructBase<Tp> {
    private:
    protected: 
        StructBuilderBase<Tp>* builder_;
        StructDirectorBase<Tp>* director_;
    public:
        Struct(): builder_(NULL), director_(NULL) {};
        Struct(DataStruct<Tp>* _struct, tree_node<Tp>* root_node, tree_node<Tp>* spec_node, StructBuilderBase<Tp>* builder, StructDirectorBase<Tp>* director) : StructBase<Tp>(_struct, root_node, spec_node),  builder_(builder), director_(director) {};
        virtual ~Struct() {
            if (this->is_built_) {
                Delete();
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
        }
        virtual void Construct(DataStruct<Tp>* _struct, tree_node<Tp>* root_node = NULL, tree_node<Tp>* spec_node = NULL) = 0;
        void Delete() {
            director_->Delete(builder_, this);
        }
};

#endif //STRUCT_H_
