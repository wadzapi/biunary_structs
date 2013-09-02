#ifndef XDIRECTOR_H_
#define XDIRECTOR_H_

#include "xstruct_base.hh"

template <class Tp>
class XDirector {
    private:
        XStorage<Tp>* storage_;
    protected:
        void SetStruct(XStorage<Tp> *_storage);
        XNode<Tp>* AddLeft(XBuilder<Tp> *builder, XNode<Tp>* node, const Tp* value = (Tp*)NULL);
        XNode<Tp>* AddRight(XBuilder<Tp> *builder, XNode<Tp>* node, const Tp* value = (Tp*)NULL);
    public:
        XDirector();
        XDirector(XStorage<Tp> *_storage): storage_(_storage) {}
        virtual ~XDirector() {}
        XStructBase<Tp>* Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node);
        void RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Delete(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
};

template <class Tp>
void XDirector<Tp>::SetStruct(XStorage<Tp> *_storage) {
    storage_ = _storage;
}

template <class Tp>
XNode<Tp>* XDirector<Tp>::AddLeft(XBuilder<Tp> *builder, XNode<Tp>* node, const Tp* value = (Tp*)NULL) {
    XNode<Tp>* new_node; 
    if (value == NULL) {
        new_node = builder->AddNode();
    } else {
        new_node = builder->AddNode(*value);
    }
    builder->ConnectLeft(node, new_node);
    return new_node;
}

template <class Tp>
XNode<Tp>* XDirector<Tp>::AddRight(XBuilder<Tp> *builder, XNode<Tp>* node, const Tp* value = (Tp*)NULL) {
    XNode<Tp>* new_node; 
    if (value == NULL) {
        new_node = builder->AddNode();
    } else {
        new_node = builder->AddNode(*value);
    }
    builder->ConnectRight(node, new_node);
    return new_node;
}

template <class Tp>
XDirector<Tp>::XStructDirector() : storage_(NULL) {}

template <class Tp>
XDirector<Tp>::XStructDirector(XStorage<Tp> *_storage): storage_(_storage) {}

template <class Tp>
XDirector<Tp>::~XStructDirector() {};

template <class Tp>
XStructBase<Tp>* XDirector<Tp>::Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL, const Tp* values = NULL) {
}

template <class Tp>
void XDirector<Tp>::ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right){
}

template <class Tp>
void XDirector<Tp>::ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) {
}

template <class Tp>
void XDirector<Tp>::DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) {
}

template <class Tp>
void XDirector<Tp>::DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) {
}

template <class Tp>
void XDirector<Tp>::RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node) {
}

template <class Tp>
void XDirector<Tp>::RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
}

template <class Tp>
void XDirector<Tp>::Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
}

#endif //XDIRECTOR_H_
