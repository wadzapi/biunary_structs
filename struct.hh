#ifndef STRUCT_H_
#define STRUCT_H_

#include "struct_base.hh"
#include "struct_builder.hh"
#include "struct_director.hh"

template <class Tp, size_t NUM_LINKS>
class Struct : public StructBase<Tp, NUM_LINKS> {
    private:
    protected: 
        StructBuilderBase<Tp, NUM_LINKS>* builder_;
        StructDirectorBase<Tp, NUM_LINKS>* director_;
    public:
        Struct(): builder_(NULL), director_(NULL) {};
        Struct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node, tree_node<Tp, NUM_LINKS>* spec_node, StructBuilderBase<Tp, NUM_LINKS>* builder, StructDirectorBase<Tp, NUM_LINKS>* director) : StructBase<Tp, NUM_LINKS>(_storage, root_node, spec_node),  builder_(builder), director_(director) {};
        virtual ~Struct() {
            if (this->is_built_) {
                Delete();
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
        }
        virtual void Construct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node = NULL, tree_node<Tp, NUM_LINKS>* spec_node = NULL) = 0;
        void Delete() {
            director_->Delete(builder_, this);
        }
};

#endif //STRUCT_H_
