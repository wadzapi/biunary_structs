#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        SequenceDirector();
        SequenceDirector(DataStruct<Tp>* _struct);
        ~SequenceDirector();
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node = (tree_node<Tp>*)NULL, tree_node<Tp>* root_node = (tree_node<Tp>*)NULL, const Tp* values = (Tp*)NULL);
        void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node, tree_node<Tp> *node);
        void RemoveSpecRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node, tree_node<Tp> *node);
        void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node);
        void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node);
};

template <class Tp>
SequenceDirector<Tp>::SequenceDirector() {
}

template <class Tp>
SequenceDirector<Tp>::SequenceDirector(DataStruct<Tp>* _struct) : StructDirectorBase<Tp>(_struct) {
}

template <class Tp>
SequenceDirector<Tp>::~SequenceDirector() {
}

template <class Tp>
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
    if (root_node == NULL) {
        root_node = this->struct_->AddLogic();
    }
    this->struct_->SetLeft(spec_node, root_node);
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
    this->struct_->SetRight(spec_node, new_node1);
    return root_node;
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp>* spec_node, tree_node<Tp> *node) {
    if (spec_node->right == node) {
        this->struct_->SetRight(spec_node, node->left);
        builder->DisconnectLeft(node);
    } else if (spec_node->left == node) {
        this->struct_->SetLeft(spec_node, node->right);
        builder->DisconnectRight(node);
    } else {
        tree_node<Tp> *l_node = node->left;
        tree_node<Tp> *r_node = node->right;
        builder->DisconnectLeft(node);
        builder->DisconnectRight(node);
        builder->ConnectRight(l_node, r_node);
    }
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveSpecRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node, tree_node<Tp> *node) {
    tree_node<Tp>* old_null = node->left;
    builder->DeleteRoot(node);
    RemoveNode(builder, spec_node, old_null);
}
   
template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    ConnectRight(builder, new_node, node);
    this->struct_->SetLeft(new_node, node->left);
    RemoveSpecRootNode(builder, new_node, node);
    node = new_node;
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    tree_node<Tp>* r_node = (new_node->left)->right;
    tree_node<Tp>* l_node = node->right;
    this->struct_->SetRight(node, new_node->right);
    RemoveSpecRootNode(builder, node, new_node);
    builder->ConnectRight(l_node, r_node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
    builder->DisconnectRight(node);
}

template <class Tp>
void SequenceDirector<Tp>::Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node) {
    tree_node<Tp> old_node;
    while ((spec_node->left)->right != spec_node->right) {
        RemoveNode(builder, spec_node, spec_node->right);
    }
}

template <class Tp>
void SequenceDirector<Tp>::Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *spec_node) {
    Clear(builder, spec_node);
    RemoveSpecRootNode(builder, spec_node, spec_node);
}

#endif //SEQUENCE_DIRECTOR_H_
