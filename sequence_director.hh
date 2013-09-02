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
        XStructBase<Tp>* Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node);
        void RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node);
        void RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Delete(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
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
XStructBase<Tp>* SequenceDirector<Tp>::Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node, XNode<Tp>* root_node, const Tp* values) {
    XStructBase<Tp>* sequence;
    if (spec_node == NULL) {
        spec_node = builder->AddRoot();
    }
    if (root_node == NULL) {
        root_node = builder->AddNodeLogic();
    }
    this->storage_->SetLeft(spec_node, root_node);
    ///Construct and connect other nodes
    XNode<Tp>* new_node1 = root_node;
    if (num_nodes > 0) {
        if (values == NULL) {
            for (size_t i = 0; i < num_nodes; i++) {
                new_node1 = AddRight(builder, new_node1);
            }
        } else {
            for (size_t i = 0; i < num_nodes; i++) {
                new_node1 = AddRight(builder, new_node1, (values + i));
            }
        }
    }
    this->storage_->SetRight(spec_node, new_node1);
    //sequence->UpdateSpecNode();
    sequence = new Sequence<Tp>(this->storage_, root_node, spec_node, builder, this);
    return sequence;
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node) {
    XNode<Tp>* spec_node = _struct->GetSpecNode();
    if (spec_node->links[1] == node) {
        this->storage_->SetRight(spec_node, node->links[0]);
        builder->DisconnectLeft(node);
    } else if (spec_node->links[0] == node) {
        this->storage_->SetLeft(spec_node, node->links[1]);
        builder->DisconnectRight(node);
    } else {
        XNode<Tp> *l_node = node->links[0];
        XNode<Tp> *r_node = node->links[1];
        builder->DisconnectLeft(node);
        builder->DisconnectRight(node);
        builder->ConnectRight(l_node, r_node);
    }
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
    XNode<Tp>* old_spec = _struct->GetSpecNode();
    XNode<Tp>* old_root = _struct->GetRootNode();
    builder->DeleteRoot(old_spec);
    RemoveNode(builder, _struct, old_root);
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

template <class Tp>
void SequenceDirector<Tp>::Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
    XNode<Tp>* spec_node = _struct->GetSpecNode();
    if (spec_node != NULL) {
        while ((spec_node->links[0])->links[1] != spec_node->links[1]) {
            RemoveNode(builder, _struct, spec_node->links[1]);
        }
    }
}

template <class Tp>
void SequenceDirector<Tp>::Delete(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
    Clear(builder, _struct);
    RemoveSpecRootNode(builder, _struct);
}

#endif //SEQUENCE_DIRECTOR_H_
