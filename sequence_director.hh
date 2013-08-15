#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct.hh"

template <class Tp>
class SequenceDirector : public StructDirectorBase<Tp, 2> {
    private:
    protected:
    public:
        SequenceDirector();
        SequenceDirector(DataStorage<Tp, 2>* _storage);
        ~SequenceDirector();
        StructBase<Tp, 2>* Construct(StructBuilderBase<Tp, 2> *builder, size_t num_nodes, tree_node<Tp, 2>* spec_node = NULL, tree_node<Tp, 2>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* struct_left, StructBase<Tp, 2>* struct_right);
        void ConnectRight(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* struct_left, StructBase<Tp, 2>* struct_right);
        void DisconnectLeft(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2>* node);
        void DisconnectRight(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2>* node);
        void DisconnectNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2> *node);
        void RemoveNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2> *node);
        void RemoveSpecRootNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct);
        void Clear(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct);
        void Delete(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct);
};

#include "sequence.hh"

template <class Tp>
SequenceDirector<Tp>::SequenceDirector() {
}

template <class Tp>
SequenceDirector<Tp>::SequenceDirector(DataStorage<Tp, 2>* _storage) : StructDirectorBase<Tp, 2>(_storage) {
}

template <class Tp>
SequenceDirector<Tp>::~SequenceDirector() {
}

template <class Tp>
StructBase<Tp, 2>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp, 2> *builder, size_t num_nodes, tree_node<Tp, 2>* spec_node, tree_node<Tp, 2>* root_node, const Tp* values) {
    StructBase<Tp, 2>* sequence;
    if (spec_node == NULL) {
        spec_node = builder->AddRoot();
    }
    if (root_node == NULL) {
        root_node = builder->AddNodeLogic();
    }
    this->storage_->SetLeft(spec_node, root_node);
    ///Construct and connect other nodes
    tree_node<Tp, 2>* new_node1 = root_node;
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
void SequenceDirector<Tp>::DisconnectNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2> *node) {
    tree_node<Tp, 2>* spec_node = _struct->GetSpecNode();
    if (spec_node->links[1] == node) {
        this->storage_->SetRight(spec_node, node->links[0]);
        builder->DisconnectLeft(node);
    } else if (spec_node->links[0] == node) {
        this->storage_->SetLeft(spec_node, node->links[1]);
        builder->DisconnectRight(node);
    } else {
        tree_node<Tp, 2> *l_node = node->links[0];
        tree_node<Tp, 2> *r_node = node->links[1];
        builder->DisconnectLeft(node);
        builder->DisconnectRight(node);
        builder->ConnectRight(l_node, r_node);
    }
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveSpecRootNode(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct) {
    tree_node<Tp, 2>* old_spec = _struct->GetSpecNode();
    tree_node<Tp, 2>* old_root = _struct->GetRootNode();
    builder->DeleteRoot(old_spec);
    RemoveNode(builder, _struct, old_root);
}
   
template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* struct_left, StructBase<Tp, 2>* struct_right) {
    ConnectRight(builder, struct_right, struct_left);
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* struct_left, StructBase<Tp, 2>* struct_right) {
    tree_node<Tp, 2>* root_right = struct_right->GetRootNode();
    tree_node<Tp, 2>* spec_left = struct_left->GetSpecNode();
    tree_node<Tp, 2>* spec_right = struct_right->GetSpecNode();
    builder->ConnectRight(spec_left->links[1], root_right);
    this->storage_->SetRight(spec_left, spec_right->links[1]);
    DisconnectNode(builder, struct_left, root_right);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectRight(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct, tree_node<Tp, 2>* node) {
    builder->DisconnectRight(node);
}

template <class Tp>
void SequenceDirector<Tp>::Clear(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct) {
    tree_node<Tp, 2>* spec_node = _struct->GetSpecNode();
    if (spec_node != NULL) {
        while ((spec_node->links[0])->links[1] != spec_node->links[1]) {
            RemoveNode(builder, _struct, spec_node->links[1]);
        }
    }
}

template <class Tp>
void SequenceDirector<Tp>::Delete(StructBuilderBase<Tp, 2> *builder, StructBase<Tp, 2>* _struct) {
    Clear(builder, _struct);
    RemoveSpecRootNode(builder, _struct);
}

#endif //SEQUENCE_DIRECTOR_H_
