#ifndef STRUCT_DIRECTOR_H_
#define STRUCT_DIRECTOR_H_

#include "struct_builder.hh"

template <class Tp>
class StructDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        StructDirector(DataStruct<Tp>* _struct);
        ~StructDirector();
        void Connect(tree_node<Tp>* root_node, tree_node<Tp>* new_node);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes);
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes);
};

template <class Tp>
StructDirector<Tp>::StructDirector(DataStruct<Tp>* _struct) : StructDirectorBase<Tp>(_struct) {
}

template <class Tp>
StructDirector<Tp>::~StructDirector() {
}

template <class Tp>
tree_node<Tp>* StructDirector<Tp>::Construct(StructBuilderBase<Tp>* builder, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = this->struct_->AddLogic();
    tree_node<Tp>* new_node;
    for (size_t i = 0; i < num_nodes; i++) {
        new_node = builder->AddNode(this->struct_);
        builder->ConnectNode(this->struct_, root_node, new_node);
    } 
    return root_node;
}

template <class Tp>
tree_node<Tp>* StructDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, const Tp* values, size_t num_nodes) {
    //allocate root node 
    tree_node<Tp>* root_node = this->struct_->AddLogic();
    tree_node<Tp>* new_node;
    for (size_t i = 0; i < num_nodes; i++) {
        new_node = builder->AddNode(this->struct_, values[i]);
        builder->ConnectNode(this->struct_, root_node, new_node);
    } 
    return root_node;
}
    
template <class Tp>
void StructDirector<Tp>::Connect(tree_node<Tp>* root_node, tree_node<Tp>* new_node) {
    //connect to the right side of other nodes in sequence
    this->struct_->SetRight(root_node->right, new_node->left);
    this->struct_->SetLeft(new_node->left, root_node->right);
    //update root node
    this->struct_->SetRight(root_node, new_node->right);
}
    
#endif //STRUCT_DIRECTOR_H_
