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
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, const Tp* values = NULL);
        void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node);
        void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node);
        void RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node);
        void Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node);
        void Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node);
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
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, const Tp* values) {
    //allocate root node 
    tree_node<Tp>* root_node = builder->AddRoot();
    ///Add null node
    tree_node<Tp>* new_node1 = this->struct_->AddLogic();
    this->struct_->SetLeft(root_node, new_node1);
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        new_node1 = builder->AddNode(values[0]);
        builder->ConnectRight(root_node->left, new_node1);
        if (values == NULL) {
            for (size_t i = 1; i < num_nodes; i++) {
                new_node1 = AddRight(builder, new_node1);
            }
        } else {
            for (size_t i = 1; i < num_nodes; i++) {
                new_node1 = AddRight(builder, new_node1, (values + i));
            }
        }
    } 
    this->struct_->SetRight(root_node, new_node1);
    return root_node;
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp>* root_node, tree_node<Tp> *node) {
    if (root_node->right == node) {
        this->struct_->SetRight(root_node, node->left);
        builder->DisconnectLeft(node);
    } else if (root_node->left == node) {
        this->struct_->SetLeft(root_node, node->right);
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
void SequenceDirector<Tp>::RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) {
    tree_node<Tp>* old_null = node->left;
    builder->DeleteRoot(node);
    RemoveNode(builder, root_node, old_null);
}
   
template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    ConnectRight(builder, new_node, node);
    this->struct_->SetLeft(new_node, node->left);
    RemoveRootNode(builder, new_node, node);
    node = new_node;
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    tree_node<Tp>* r_node = (new_node->left)->right;
    tree_node<Tp>* l_node = node->right;
    this->struct_->SetRight(node, new_node->right);
    RemoveRootNode(builder, node, new_node);
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
void SequenceDirector<Tp>::Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
    tree_node<Tp> old_node;
    while ((root_node->left)->right != root_node->right) {
        RemoveNode(builder, root_node, root_node->right);
    }
}

template <class Tp>
void SequenceDirector<Tp>::Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
    Clear(builder, root_node);
    RemoveRootNode(builder, root_node, root_node);
}

#endif //SEQUENCE_DIRECTOR_H_
