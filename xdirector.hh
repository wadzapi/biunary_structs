#ifndef XDIRECTOR_H_
#define XDIRECTOR_H_

#include "xstruct_base.hh"

template <class Tp>
class XDirector {
    private:
        XStorage<Tp>* storage_;
    protected:
        void SetStorage(XStorage<Tp> *_storage) {
            storage_ = _storage;
        }
    public:
        XDirector() : storage_(NULL) {}
        XDirector(XStorage<Tp> *_storage) : storage_(_storage) {}
        virtual ~XDirector() {}
        virtual XStructBase<Tp>* Construct(XBuilder<Tp> *builder, XStructBase<Tp>* _struct = NULL, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL) = 0;
        virtual void ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) = 0;
        virtual void ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) = 0;
        virtual void DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) = 0;
        virtual void DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) = 0;
};

#endif //XDIRECTOR_H_
