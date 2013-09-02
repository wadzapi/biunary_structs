#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "xbuilder.hh"

template <class Tp>
class SequenceBuilder : public XBuilder<Tp> {
    private:
    protected:
    public:
        SequenceBuilder();
        SequenceBuilder(XStorage<Tp>* _storage);
        ~SequenceBuilder(); 
        XNode<Tp> *AddNodeLogic();
        void ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node);
        void ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node);
        void DisconnectLeft(XNode<Tp> *node);
        void DisconnectRight(XNode<Tp> *node);
        void DeleteNode(XNode<Tp>* node);
};

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder() { 
}

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder(XStorage<Tp>* _storage) : 
    XBuilder<Tp>(_storage, 1) {
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
XNode<Tp>* SequenceBuilder<Tp>::AddNodeLogic() {
    XNode<Tp>* new_node = this->storage_->AddLogic();
    return new_node;
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node) {
    this->storage_->SetLeft(node, new_node);
    this->storage_->SetRight(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node) {
    this->storage_->SetRight(node, new_node);
    this->storage_->SetLeft(new_node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectLeft(XNode<Tp> *node) {
    this->storage_->SetRight(node->links[0], node->links[0]);
    this->storage_->SetLeft(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectRight(XNode<Tp> *node) {
    this->storage_->SetLeft(node->links[1], node->links[1]);
    this->storage_->SetRight(node, node);
}

template <class Tp>
void SequenceBuilder<Tp>::DeleteNode(XNode<Tp>* node) {
    //delete links
    this->storage_->SetLeft(node, NULL);
    this->storage_->SetRight(node, NULL);
    //delete value
    this->storage_->Unreserve(node->value);
}

#endif //SEQUENCE_BUILDER_H_
