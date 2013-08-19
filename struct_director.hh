#ifndef XSTRUCT_DIRECTOR_H_
#define XSTRUCT_DIRECTOR_H_

#include "struct_base.hh"

template <class Tp>
class XStructDirector {
    private:
        DataStorage<Tp>* storage_;
    protected:
        void SetStruct(DataStorage<Tp> *_storage);
        XStructNode<Tp>* AddLeft(XStructBuilder<Tp> *builder, XStructNode<Tp>* node, const Tp* value = (Tp*)NULL);
        XStructNode<Tp>* AddRight(XStructBuilder<Tp> *builder, XStructNode<Tp>* node, const Tp* value = (Tp*)NULL);
    public:
        XStructDirector();
        XStructDirector(DataStorage<Tp> *_storage): storage_(_storage) {}
        ~XStructDirector() {};
        StructBase<Tp>* Construct(XStructBuilder<Tp> *builder, size_t num_nodes, XStructNode<Tp>* spec_node = NULL, XStructNode<Tp>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(XStructBuilder<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right);
        void ConnectRight(XStructBuilder<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right);
        void DisconnectLeft(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp>* node);
        void DisconnectRight(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp>* node);
        void RemoveNode(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp> *node);
        void RemoveSpecRootNode(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct);
        void Clear(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct);
        void Delete(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct);
};

template <class Tp>
void XStructDirector<Tp>::SetStruct(DataStorage<Tp> *_storage) {
    storage_ = _storage;
}

template <class Tp>
XStructNode<Tp>* XStructDirector<Tp>::AddLeft(XStructBuilder<Tp> *builder, XStructNode<Tp>* node, const Tp* value = (Tp*)NULL) {
    XStructNode<Tp>* new_node; 
    if (value == NULL) {
        new_node = builder->AddNode();
    } else {
        new_node = builder->AddNode(*value);
    }
    builder->ConnectLeft(node, new_node);
    return new_node;
}

template <class Tp>
XStructNode<Tp>* XStructDirector<Tp>::AddRight(XStructBuilder<Tp> *builder, XStructNode<Tp>* node, const Tp* value = (Tp*)NULL) {
    XStructNode<Tp>* new_node; 
    if (value == NULL) {
        new_node = builder->AddNode();
    } else {
        new_node = builder->AddNode(*value);
    }
    builder->ConnectRight(node, new_node);
    return new_node;
}

template <class Tp>
XStructDirector<Tp>::XStructDirector() : storage_(NULL) {}

template <class Tp>
XStructDirector<Tp>::XStructDirector(DataStorage<Tp> *_storage): storage_(_storage) {}

template <class Tp>
XStructDirector<Tp>::~XStructDirector() {};

template <class Tp>
StructBase<Tp>* XStructDirector<Tp>::Construct(XStructBuilder<Tp> *builder, size_t num_nodes, XStructNode<Tp>* spec_node = NULL, XStructNode<Tp>* root_node = NULL, const Tp* values = NULL) {
}

template <class Tp>
void XStructDirector<Tp>::ConnectLeft(XStructBuilder<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right){
}

template <class Tp>
void XStructDirector<Tp>::ConnectRight(XStructBuilder<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) {
}

template <class Tp>
void XStructDirector<Tp>::DisconnectLeft(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp>* node) {
}

template <class Tp>
void XStructDirector<Tp>::DisconnectRight(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp>* node) {
}

template <class Tp>
void XStructDirector<Tp>::RemoveNode(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct, XStructNode<Tp> *node) {
}

template <class Tp>
void XStructDirector<Tp>::RemoveSpecRootNode(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct) {
}

template <class Tp>
void XStructDirector<Tp>::Clear(XStructBuilder<Tp> *builder, StructBase<Tp>* _struct) {
}

#endif //XSTRUCT_DIRECTOR_H_
