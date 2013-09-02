#ifndef XSTRUCT_H_
#define XSTRUCT_H_

#include "xstruct_base.hh"
#include "xbuilder.hh"
#include "xdirector.hh"

template <class Tp>
class XStruct : public XStructBase<Tp> {
    private:
    protected: 
        XBuilder<Tp>* builder_;
        XDirector<Tp>* director_;
    public:
        XStruct(): builder_(NULL), director_(NULL) {};
        XStruct(XStorage<Tp>* _storage, XNode<Tp>* root_node, XNode<Tp>* spec_node, XBuilder<Tp>* builder, XDirector<Tp>* director) : XStructBase<Tp>(_storage, root_node, spec_node),  builder_(builder), director_(director) {};
        virtual ~XStruct() {
            if (this->is_built_) {
                Delete();
                delete builder_;
                builder_ = NULL;
                delete director_;
                director_ = NULL;
            }
        }
        virtual void Construct(XStorage<Tp>* _storage, XNode<Tp>* root_node = NULL, XNode<Tp>* spec_node = NULL) = 0;
        void Delete() {
            director_->Delete(builder_, this);
        }
};

#endif //XSTRUCT_H_
