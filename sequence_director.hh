#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct_builder.hh"

template <class Tp>
class SequenceDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        SequenceDirector(DataStruct<Tp>* _struct);
        ~SequenceDirector();
        void Connect(tree_node<Tp>* root_node, tree_node<Tp>* new_node);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes);
        void DeleteNode(tree_node<Tp>* node);
};

template <class Tp>
SequenceDirector<Tp>::SequenceDirector(DataStruct<Tp>* _struct) : StructDirectorBase<Tp>(_struct) {
}

template <class Tp>
SequenceDirector<Tp>::~SequenceDirector() {
}

template <class Tp>
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp>* builder, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = this->struct_->AddRoot();
    if (num_nodes > 0) {
        tree_node<Tp>* new_node1 = builder->AddNode(this->struct_);
        this->struct_->SetLeft(root_node, new_node1);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode(this->struct_);
            builder->ConnectNode(this->struct_, new_node1, new_node2);
            new_node1 = new_node2;
        }
    } 
    return root_node;
}

template <class Tp>
tree_node<Tp>* SequenceDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = this->struct_->AddRoot();
    if (num_nodes > 0) {
        tree_node<Tp>* new_node1 = builder->AddNode(this->struct_, values[0]);
        this->struct_->SetLeft(root_node, new_node1);
        tree_node<Tp>* new_node2;
        for (size_t i = 1; i < num_nodes; i++) {
            new_node2 = builder->AddNode(this->struct_, values[i]);
            builder->ConnectNode(this->struct_, new_node1, new_node2);
            new_node1 = new_node2;
        }
    } 
    return root_node;
}
    
template <class Tp>
void SequenceDirector<Tp>::Connect(tree_node<Tp>* root_node, tree_node<Tp>* new_node) {
    //connect to the right side of other nodes in sequence
    this->struct_->SetRight(root_node->right, new_node->left);
    this->struct_->SetLeft(new_node->left, root_node->right);
    //update root node
    this->struct_->SetRight(root_node, new_node->right);
    //delete temporary root
    DeleteNode(new_node); 
}

template <class Tp>
void SequenceDirector<Tp>::DeleteNode(tree_node<Tp>* node) {
    this->struct_->SetLeft(node, node);
    this->struct_->SetRight(node, node);
    this->struct_->Unreserve(node);
}

#endif //SEQUENCE_DIRECTOR_H_
