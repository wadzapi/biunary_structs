#ifndef XSTRUCT_H_
#define XSTRUCT_H_

#include "xstruct_base.hh"
#include "xbuilder.hh"
#include "xdirector.hh"

template <class Tp>
class XStruct : public XStructBase<Tp> {
    private:
        size_t num_elements;
        bool is_built_;
    protected: 
        XBuilder<Tp>* builder_;
        XDirector<Tp>* director_;
    public:
        XStruct(): builder_(NULL), director_(NULL), is_built_(false) {};
        XStruct(XStorage<Tp>* _storage, XBuilder<Tp> _builder, XDirector<Tp> _director) : XStructBase<Tp>(_storage, _builder->AddNode(), _builder->AddSpecNode()), builder_(_builder), director_(_director), is_built_(false) {};
        virtual ~XStruct() {
            Free();
            if (is_built_) {
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
        }
        virtual void Construct() = 0;
        virtual bool IsEmpty() = 0;
        virtual void Free() = 0;
};

#endif //XSTRUCT_H_
