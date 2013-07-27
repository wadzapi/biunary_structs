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
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes);
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
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp>* builder, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = builder->AddRoot();
    ///Add null node
    tree_node<Tp>* new_node1 = builder->AddNode();
    this->struct_->Unreserve(new_node1->value);
    new_node1->value = NULL;
    this->struct_->SetLeft(root_node, new_node1);
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        new_node1 = builder->AddNode();
        builder->ConnectRight(root_node->left, new_node1);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode();
            builder->ConnectRight(new_node1, new_node2);
            new_node1 = new_node2;
        }
        this->struct_->SetRight(root_node, new_node1);
    } 
    return root_node;
}

template <class Tp>
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = builder->AddRoot();
    ///Add null node
    tree_node<Tp>* new_node1 = builder->AddNode();
    this->struct_->Unreserve(new_node1->value);
    new_node1->value = NULL;
    this->struct_->SetLeft(root_node, new_node1);
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        new_node1 = builder->AddNode(values[0]);
        builder->ConnectRight(root_node->left, new_node1);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode(values[i]);
            builder->ConnectRight(new_node1, new_node2);
            new_node1 = new_node2;
        }
        this->struct_->SetRight(root_node, new_node1);
    } 
    return root_node;
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp>* root_node, tree_node<Tp> *node) {
    if (root_node->right == node) {
        this->struct_->SetRight(root_node, node->left);
    } else if (root_node->left == node) {
        this->struct_->SetLeft(root_node, node->right);
    } else {
        builder->ConnectRight(node->left, node->right);
    }
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) {
    RemoveNode(builder, root_node, node->left);
    builder->DeleteRoot(node);
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
    //connect to the right side of other nodes in sequence
    builder->ConnectRight(node->right, (new_node->left)->right);
    this->struct_->SetRight(node, new_node->right); 
    RemoveRootNode(builder, node, new_node);
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
