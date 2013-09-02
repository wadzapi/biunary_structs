#ifndef XBUILDER_H_
#define XBUILDER_H_

#include "xstorage.hh"

template <class Tp>
class XBuilder {
    private:
        XStorage<Tp>* storage_;
    protected:
    public:
        XBuilder();
        XBuilder(XStorage<Tp> *_storage);
        virtual ~XBuilder();
        void SetStorage(XStorage<Tp> *_storage);
        XNode<Tp> *AddNodeLogic();
        XNode<Tp>* AddNode(); 
        XNode<Tp>* AddNode(const Tp& value);
        XNode<Tp> *AddRoot();
        void AddNodeValue(XNode<Tp> *&node, const Tp& value);
        void ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node);
        void ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node);
        void DisconnectLeft(XNode<Tp> *node);
        void DisconnectRight(XNode<Tp> *node);
        void DeleteNode(XNode<Tp>* node);
        void DeleteRoot(XNode<Tp>* node);
};

template <class Tp>
XBuilder<Tp>::XBuilder() : storage_(NULL) {}

template <class Tp>
XBuilder<Tp>::XBuilder(XStorage<Tp> *_storage): storage_(_storage) {}

template <class Tp>
virtual XBuilder<Tp>::~XBuilder() {}

template <class Tp>
void XBuilder<Tp>::SetStorage(XStorage<Tp> *_storage) {
    storage_ = _storage;
}

template <class Tp>
XNode<Tp>* XBuilder<Tp>::AddNodeLogic() {
}

template <class Tp>
XNode<Tp>* XBuilder<Tp>:: AddNode() {
    XNode<Tp>* new_node = AddNodeLogic();
    AddNodeValue(new_node, Tp());
    return new_node;
}

template <class Tp>
XNode<Tp>* XBuilder<Tp>:: AddNode(const Tp& value) {
            XNode<Tp>* new_node = AddNodeLogic();
            AddNodeValue(new_node, value);
            return new_node;
}

template <class Tp>
XNode<Tp>* XBuilder<Tp>::AddRoot() {
            XNode<Tp>* root_node = storage_->AddLogic();
            storage_->Reserve(root_node);
            return root_node;
}

template <class Tp>
void XBuilder<Tp>::AddNodeValue(XNode<Tp> *&node, const Tp& value) {
            Tp* new_val = storage_->AddData(value);
            storage_->SetData(node, new_val);
            storage_->Unreserve(new_val);
}

template <class Tp>
void XBuilder<Tp>::ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node) {
}

template <class Tp>
void XBuilder<Tp>::ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node) {
}

template <class Tp>
void XBuilder<Tp>::DisconnectLeft(XNode<Tp> *node) {
}

template <class Tp>
void XBuilder<Tp>::DisconnectRight(XNode<Tp> *node) {
}

template <class Tp>
void XBuilder<Tp>::DeleteNode(XNode<Tp>* node) {
}

template <class Tp>
void XBuilder<Tp>::DeleteRoot(XNode<Tp>* node) {
    storage_->SetLeft(node, NULL);
    storage_->SetRight(node, NULL);
    storage_->Unreserve(node);
}

#endif // XBUILDER_H_
