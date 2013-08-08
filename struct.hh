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
        virtual ~Struct() {
            if (this->is_built_) {
                Delete();
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
        }
        void Delete() {
            director_->Delete(builder_, this);
        }
};

#endif //STRUCT_H_
