#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "xstruct.hh"

template <class Tp>
class SequenceDirector : public XDirector<Tp> {
    private:
    protected:
    public:
        SequenceDirector();
        SequenceDirector(XStorage<Tp>* _storage);
        ~SequenceDirector();
        XStructBase<Tp>* Construct(XBuilder<Tp> *builder, XStructBase<Tp>* _struct = NULL, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL);
        void ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
};

#include "sequence.hh"

template <class Tp>
SequenceDirector<Tp>::SequenceDirector() {
}

template <class Tp>
SequenceDirector<Tp>::SequenceDirector(XStorage<Tp>* _storage) : XDirector<Tp>(_storage) {
}

template <class Tp>
SequenceDirector<Tp>::~SequenceDirector() {
}

template <class Tp>
XStructBase<Tp>* SequenceDirector<Tp>::Construct(XBuilder<Tp>* builder) {
    sequence = new Sequence<Tp>(_storage, builder, this);
    return sequence;
}

template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) {
    ConnectRight(builder, struct_right, struct_left);
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) {
    XNode<Tp>* root_right = struct_right->GetRootNode();
    XNode<Tp>* spec_left = struct_left->GetSpecNode();
    XNode<Tp>* spec_right = struct_right->GetSpecNode();
    builder->ConnectRight(spec_left->links[1], root_right);
    this->storage_->SetRight(spec_left, spec_right->links[1]);
    DisconnectNode(builder, struct_left, root_right);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) {
    builder->DisconnectRight(node);
}

#endif //SEQUENCE_DIRECTOR_H_
