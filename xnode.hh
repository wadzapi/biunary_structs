#ifndef XNODE_H_
#define XNODE_H_

#include "xdata.hh"

template <class Tp>
class XNode {
    private:
        XData<Tp>* data_;
        size_t links_offset_;
    protected:
    public:
        XNode();
        XNode(XData<Tp>* data, size_t links_offset);
        XNode(size_t num_links, size_t links_offset);
        ~XNode();
        void SetStogare(XStorage<Tp>* storage);
        void SetData(Tp* data_ptr);
        void Reserve();
        void Unreserve 
        void ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node);
        void ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node);
        void DisconnectLeft(XNode<Tp> *node);
        void DisconnectRight(XNode<Tp> *node);
        Tp* GetData();
        XData<Tp>* GetLink(size_t link_idx);
};

template <class Tp>
XNode<Tp>::XNode() : data_(NULL), links_offset_(0) {}

template <class Tp>
XNode<Tp>::XNode(XStorage<Tp>* _storage, size_t num_links, size_t links_offset, const ) :
    data_(NULL),
    links_offset_(links_offset)
{
    data_ = _storage->addLogic();
}

template <class Tp>
XNode<Tp>::XNode(num_links, size_t links_offset, Tp* val_ptr) : data_(new XData<Tp>(num_links, new XStructNodeData*[num_links], val_ptr)), storage_(NULL), is_built_(true) {}
XNode<Tp>::XNode(XData<Tp>* data, size_t links_offset) :
{
    this->data_ = 
}

template <class Tp>
XNode<Tp>::XNode(num_links, size_t links_offset) : data_(new XData<Tp>(num_links, new XStructNodeData*[num_links], new Tp())), storage_(NULL), is_built_(true) {}

template <class Tp>
XNode<Tp>::~XNode() {
    DisconnectLeft();
    DisconnectRight();
    if (is_built_) {
       // delete data;
    }
}

template <class Tp>
void XNode<Tp>::SetStogare(XStorage<Tp>* storage) {
    storage_ = storage;
}

template <class Tp>
void XNode<Tp>::Reserve() {
    if (storage_ != NULL) {
        storage_->Reserve(this->data_);
    }
}

template <class Tp>
void XNode<Tp>::Unreserve() {
    if (storage_ != NULL) {
        storage_->Unreserve(this->data_);
    }
}

template <class Tp>
void XNode<Tp>::ConnectLeft(XNode<Tp>* node) {
    node->ConnectRight(this);
}

template <class Tp>
void XNode<Tp>::ConnectRight(XNode<Tp>* node) {
    size_t offset = this->data_->links_offset_;
    size_t num_connects = this->data_->num_links - this->data_->links_offset_;
    for (size_t i = offset; i < num_connects; i++) {
        //connect node1 to node2
        node->Reserve();
        this->data_->links[i] = node;
        this->data_->Unreserve(this->data_->links[i]);
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

template <class Tp>
Tp* XNode<Tp>::GetData() {
    return data_->value_;
}

template <class Tp>
XData<Tp>* XNode<Tp>::GetLink(size_t link_idx) {
    return data_->(links_ + link_idx);
}

template <class Tp>
size_t XNode<Tp>::GetNumLinks() {
    return this->data_->num_links_;
}

template <class Tp>
size_t XNode<Tp>::GetLinksOffset() {
    return this->links_offset_;
}



#endif //XSTRUCT_NODE_H_
