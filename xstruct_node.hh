#ifndef XSTRUCT_NODE_H_
#define XSTRUCT_NODE_H_

template <class Tp>
class XStructNode {
    struct XStructNodeData {
        size_t num_links_
        XStructNodeData<Tp>** links_;
        Tp* value_;
        XStructNodeData() : num_links_(0), links_(NULL), value_(NULL) {}
        XStructNodeData(size_t num_links, XStructNodeData<Tp>** links, Tp* value) : num_links_(num_links), links_(links), value_(value) {}
    };
    private:
        XStructNodeData data_;
        size_t links_offset_;
        DataStorage<Tp>* storage_; 
        bool is_built_;
    protected:
    public:
        XStructNode();
        XStructNode(size_t num_links, size_t links_offset, Tp* val_ptr = NULL);
        ~XStructNode();
        void SetStogare(DataStorage<Tp>* storage);
        void Reserve();
        void Unreserve 
        void ConnectLeft(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node);
        void ConnectRight(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node);
        void DisconnectLeft(tree_node<Tp, NUM_LINKS> *node);
        void DisconnectRight(tree_node<Tp, NUM_LINKS> *node);
        void Delete(tree_node<Tp, NUM_LINKS>* node);
};

template <class Tp>
XStructNode<Tp>::XStructNode() : data_(), links_offset(0), storage_(NULL), is_built_(false) {}

template <class Tp>
XStructNode<Tp>::XStructNode(num_links, size_t links_offset, Tp* val_ptr) : data_(num_links, new XStructNodeData*[num_links], val_ptr), storage_(NULL), is_built_(false) {}

template <class Tp>
XStructNode<Tp>::XStructNode(num_links, size_t links_offset) : data_(num_links, new XStructNodeData*[num_links], new Tp()), storage_(NULL), is_built_(true) {}

template <class Tp>
XStructNode<Tp>::~XStructNode() {
    delete[] data_.links_;
    if (is_built_) {
        delete data_.value_;
    }
}

template <class Tp>
void XStructNode<Tp>::SetStogare(DataStorage<Tp>* storage) {
    storage_ = storage;
}

template <class Tp>
void XStructNode<Tp>::Reserve() {
    if (storage_ != NULL) {
        storage_->Reserve(this);
    }
}

template <class Tp>
void XStructNode<Tp>::Unreserve() {
    if (storage_ != NULL) {
        storage_->Unreserve(this);
    }
}

template <class Tp>
void XStructNode<Tp>::ConnectLeft(XStructNode<Tp>* node) {
    size_t offset = node->data_.links_offset_;    
    size_t num_connects = node_->data_.num_links - offset2;
    for (size_t i = num_connects; i <= 0; i--) {
        node->Reserve();
        this->data_.links[i]->Unreserve();
        this->data_.links[i] = node;
    }
}

template <class Tp>
void XStructNode<Tp>::ConnectRight(XStructNode<Tp>* node) {
    size_t offset = this->data_.links_offset_;
    size_t num_connects = this->data_.num_links - this->data_.links_offset_;
    for (size_t i = offset; i < num_connects; i++) {
        node->Reserve();
        this->data_.links[i]->Unreserve();
        this->data_.links[i] = node;
    }
}

template <class Tp>
void XStructNode<Tp>::DisconnectLeft() {
    ConnectLeft(this);
}

template <class Tp>
void XStructNode<Tp>::DisconnectRight() {
    ConnectRight(this);
}

#endif //XSTRUCT_NODE_H_
