#ifndef XSTRUCT_NODE_H_
#define XSTRUCT_NODE_H_

#include "xdata.hh"

template <class Tp>
class XNode {
    private:
        XData<Tp> data_;
        size_t links_offset_;
        XStorage<Tp>* storage_; 
        bool is_built_;
    protected:
    public:
        XNode();
        XNode(size_t num_links, size_t links_offset, Tp* val_ptr = NULL);
        ~XNode();
        void SetStogare(XStorage<Tp>* storage);
        void SetData(Tp* data_ptr);
        void Reserve();
        void Unreserve 
        void ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node);
        void ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node);
        void DisconnectLeft(XNode<Tp> *node);
        void DisconnectRight(XNode<Tp> *node);
};

template <class Tp>
XNode<Tp>::XNode() : data_(), links_offset(0), storage_(NULL), is_built_(false) {}

template <class Tp>
XNode<Tp>::XNode(num_links, size_t links_offset, Tp* val_ptr) : data_(num_links, new XStructNodeData*[num_links], val_ptr), storage_(NULL), is_built_(false) {}

template <class Tp>
XNode<Tp>::XNode(num_links, size_t links_offset) : data_(num_links, new XStructNodeData*[num_links], new Tp()), storage_(NULL), is_built_(true) {}

template <class Tp>
XNode<Tp>::~XNode() {
    delete[] data_.links_;
    if (is_built_) {
        //delete data_.value_;
    }
}

template <class Tp>
void XNode<Tp>::SetStogare(XStorage<Tp>* storage) {
    storage_ = storage;
}

template <class Tp>
void XNode<Tp>::SetData(Tp* data_ptr) {
    this->storage_->Unreserve(this->data_.value_);
    this->data_.value_ = data_ptr;
    this->storage_->Reserve(data_ptr);
}

template <class Tp>
void XNode<Tp>::Reserve() {
    if (storage_ != NULL) {
        storage_->Reserve(this);
    }
}

template <class Tp>
void XNode<Tp>::Unreserve() {
    if (storage_ != NULL) {
        storage_->Unreserve(this);
    }
}

template <class Tp>
void XNode<Tp>::ConnectLeft(XNode<Tp>* node) {
    size_t offset = node->data_.links_offset_;    
    size_t num_connects = node_->data_.num_links - offset2;
    for (size_t i = num_connects; i <= 0; i--) {
        node->Reserve();
        this->data_.links[i]->Unreserve();
        this->data_.links[i] = node;
    }
}

template <class Tp>
void XNode<Tp>::ConnectRight(XNode<Tp>* node) {
    size_t offset = this->data_.links_offset_;
    size_t num_connects = this->data_.num_links - this->data_.links_offset_;
    for (size_t i = offset; i < num_connects; i++) {
        node->Reserve();
        this->data_.links[i]->Unreserve();
        this->data_.links[i] = node;
    }
}

template <class Tp>
void XNode<Tp>::DisconnectLeft() {
    ConnectLeft(this);
}

template <class Tp>
void XNode<Tp>::DisconnectRight() {
    ConnectRight(this);
}

#endif //XSTRUCT_NODE_H_
