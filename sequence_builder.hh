#ifndef SEQUENCE_BUILDER_H_
#define SEQUENCE_BUILDER_H_

#include "xbuilder.hh"

template <class Tp>
class SequenceBuilder : public XBuilder<Tp> {
    private:
    protected:
    public:
        SequenceBuilder() {};
        ~SequenceBuilder() {};
        XNode<Tp>* AddSpecNode(XStorage<Tp>* _storage);
        XNode<Tp>* AddNode(XStorage<Tp>* _storage, const Tp& value = NULL);
        void ConnectLeft(XNode<Tp>* left_node, XNode<Tp>* right_node);
        void ConnectRight(XNode<Tp>* left_node, XNode<Tp>* right_node);
        void DisconnectLeft(XNode<Tp>* node);
        void DisconnectRight(XNode<Tp>* node);
        void DeleteNode(XNode<Tp>* node);
};

template <class Tp>
SequenceBuilder<Tp>::SequenceBuilder() { 
}

template <class Tp>
SequenceBuilder<Tp>::~SequenceBuilder() {
}

template <class Tp>
XNode<Tp>* SequenceBuilder<Tp>::AddNode(XStorage<Tp>* _storage, const Tp& value) {
    XNode<Tp>* new_node = _storage->AddDataLogic(2, 1, value);
    return new_node;
}

template <class Tp>
XNode<Tp>* SequenceBuilder<Tp>::AddSpecNode(XStorage<Tp>* _storage) {
    XNode<Tp>* spec_node = _storage->AddLogic(2, 1);
    _storage->Reserve(spec_node);
    return spec_node;
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectLeft(XNode<Tp> *node, XNode<Tp> *new_node) {
    node->ConnectLeft(new_node);
}

template <class Tp>
void SequenceBuilder<Tp>::ConnectRight(XNode<Tp> *node, XNode<Tp> *new_node) {
    node->ConnectRight(new_node);
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectLeft(XNode<Tp> *node) {
    node->DisconnectLeft();
}

template <class Tp>
void SequenceBuilder<Tp>::DisconnectRight(XNode<Tp> *node) {
    node->DisconnectRight();
}

template <class Tp>
void SequenceBuilder<Tp>::DeleteNode(XNode<Tp>* node) {
    delete node;
}

#endif //SEQUENCE_BUILDER_H_
