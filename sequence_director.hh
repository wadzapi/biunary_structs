#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct.hh"

template <class Tp>
class SequenceDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        SequenceDirector();
        SequenceDirector(DataStorage<Tp>* _storage);
        ~SequenceDirector();
        StructBase<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node = NULL, tree_node<Tp>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right);
        void ConnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node);
        void DisconnectNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node);
        void RemoveNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node);
        void RemoveSpecRootNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct);
        void Clear(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct);
        void Delete(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct);
};

#include "sequence.hh"

template <class Tp>
SequenceDirector<Tp>::SequenceDirector() {
}

template <class Tp>
SequenceDirector<Tp>::SequenceDirector(DataStorage<Tp>* _storage) : StructDirectorBase<Tp>(_storage) {
}

template <class Tp>
SequenceDirector<Tp>::~SequenceDirector() {
}

template <class Tp>
StructBase<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
    StructBase<Tp>* sequence;
    if (spec_node == NULL) {
        spec_node = builder->AddRoot();
    }
    if (root_node == NULL) {
        root_node = builder->AddNodeLogic();
    }
    this->storage_->SetLeft(spec_node, root_node);
    ///Construct and connect other nodes
    tree_node<Tp>* new_node1 = root_node;
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
void SequenceDirector<Tp>::DisconnectNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node) {
    tree_node<Tp>* spec_node = _struct->GetSpecNode();
    if (spec_node->right == node) {
        this->storage_->SetRight(spec_node, node->left);
        builder->DisconnectLeft(node);
    } else if (spec_node->left == node) {
        this->storage_->SetLeft(spec_node, node->right);
        builder->DisconnectRight(node);
    } else {
        tree_node<Tp> *l_node = node->left;
        tree_node<Tp> *r_node = node->right;
        builder->DisconnectLeft(node);
        builder->DisconnectRight(node);
        builder->ConnectRight(l_node, r_node);
    }
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveSpecRootNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) {
    tree_node<Tp>* old_spec = _struct->GetSpecNode();
    tree_node<Tp>* old_root = _struct->GetRootNode();
    builder->DeleteRoot(old_spec);
    RemoveNode(builder, _struct, old_root);
}
   
template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) {
    ConnectRight(builder, struct_right, struct_left);
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) {
    tree_node<Tp>* root_right = struct_right->GetRootNode();
    tree_node<Tp>* spec_left = struct_left->GetSpecNode();
    tree_node<Tp>* spec_right = struct_right->GetSpecNode();
    builder->ConnectRight(spec_left->right, root_right);
    this->storage_->SetRight(spec_left, spec_right->right);
    DisconnectNode(builder, struct_left, root_right);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node) {
    builder->DisconnectRight(node);
}

template <class Tp>
void SequenceDirector<Tp>::Clear(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) {
    tree_node<Tp>* spec_node = _struct->GetSpecNode();
    if (spec_node != NULL) {
        while ((spec_node->left)->right != spec_node->right) {
            RemoveNode(builder, _struct, spec_node->right);
        }
    }
}

template <class Tp>
void SequenceDirector<Tp>::Delete(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) {
    Clear(builder, _struct);
    RemoveSpecRootNode(builder, _struct);
}

#endif //SEQUENCE_DIRECTOR_H_
