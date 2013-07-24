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
        void ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, tree_node<Tp>* new_node);
        void ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, tree_node<Tp>* new_node);
        void DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node);
        void DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node);
        void RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *node);
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
    tree_node<Tp>* root_node = builder->AddRoot(this->struct_);
    ///Add null node
    tree_node<Tp>* new_node1 = builder->AddNode(this->struct_);
    this->struct_->Unreserve(new_node1->value);
    new_node1->value = NULL;
    this->struct_->SetLeft(root_node, new_node1);
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        new_node1 = builder->AddNode(this->struct_);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode(this->struct_);
            builder->ConnectNode(this->struct_, new_node1, new_node2);
            new_node1 = new_node2;
        }
        this->struct_->SetRight(root_node, new_node1);
    } 
    return root_node;
}

template <class Tp>
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = builder->AddRoot(this->struct_);
    if (num_nodes > 0) {
        tree_node<Tp>* new_node1 = builder->AddNode(this->struct_, values[0]);
        this->struct_->SetLeft(root_node, new_node1);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode(this->struct_, values[i]);
            builder->ConnectNode(this->struct_, new_node1, new_node2);
            new_node1 = new_node2;
        }
        this->struct_->SetRight(root_node, new_node1);
    } 
    return root_node;
}

template <class Tp>
void SequenceDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *node) {
    this->struct_->SetRight(node->left, node->right);
    this->struct_->SetLeft(node->right, node->left;
    builder->DeleteNode(node);
}

template <class Tp>
void SequenceDirector<Tp>::RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *node) {
    this->struct_->SetRight(node->left, node->right);
    this->struct_->SetLeft(node->right, node->left;
    builder->DeleteRoot(node);
}
   
template <class Tp>
void SequenceDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, tree_node<Tp>* new_node) {
    ConnectRight(new_node, root_node_);
    RemoveRootNode(root_node_);
    root_node_ = new_node;
}

template <class Tp>
void SequenceDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, tree_node<Tp>* new_node) {
    //connect to the right side of other nodes in sequence
    builder->ConnectRight(node, new_node);
    RemoveRootNode(new_node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void SequenceDirector<Tp>::DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node) {
    builder->DisconnectRight(node);
}

#endif //SEQUENCE_DIRECTOR_H_
