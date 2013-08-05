#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct_builder.hh"
#include "stack.hh"

template <class Tp>
class BinaryTreeDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        BinaryTreeDirector();
        BinaryTreeDirector(DataStruct<Tp>* _struct);
        ~BinaryTreeDirector();
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
BinaryTreeDirector<Tp>::BinaryTreeDirector() {
}

template <class Tp>
BinaryTreeDirector<Tp>::BinaryTreeDirector(DataStruct<Tp>* _struct) : StructDirectorBase<Tp>(_struct) {
}

template <class Tp>
BinaryTreeDirector<Tp>::~BinaryTreeDirector() {
}

template <class Tp>
tree_node<Tp>* BinaryTreeDirector<Tp>::AddLeft(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* values = NULL) {

template<class Tp>
tree_node<Tp>* BinaryTreeDirector<Tp>::AddRight(StructBuilderBase<Tp> *builder, tree_node<Tp>* node, const Tp* values = NULL) {

template <class Tp>
tree_node<Tp>* BinaryTreeDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, const Tp* values = NULL) {
    //allocate root node 
    tree_node<Tp>* root_node = builder->AddRoot();
    //add null node
    tree_node<Tp>* new_node1 = builder->AddNode();
    this->struct_->SetLeft(root_node, new_node1);
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        Queue<tree_node<Tp>*> connect_queue(this->struct_);
        connect_queue.Push(new_node1);
        size_t i;
        if (values == NULL) {
            for (i = 0; i < num_nodes - 1; i+=2) { 
                connect_queue.Push(AddLeft(builder, connect_queue->Top()));
                connect_queue.Push(AddRight(builder, connect_queue->Top()));
                connect_queue->Pop();
            }
            if ( i == num_nodes) { //odd
                connect_queue.Push(AddLeft(builder, connect_queue->Top()));
                connect_queue->Pop();
            }
        } else {
            for (i = 0; i < num_nodes - 1; i+=2) { 
                connect_queue.Push(AddLeft(builder, connect_queue->Top(), values[i]));
                connect_queue.Push(AddRight(builder, connect_queue->Top(), values[i+1]));
                connect_queue->Pop();
            }
            if ( i == num_nodes) { //odd
                connect_queue.Push(AddLeft(builder, connect_queue->Top(), values[i-1]));
                connect_queue->Pop();
            }
        }
    }
    return root_node;
}

template <class Tp>
void BinaryTreeDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, tree_node<Tp>* root_node, tree_node<Tp> *node) {
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
void BinaryTreeDirector<Tp>::RemoveRootNode(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node, tree_node<Tp> *node) {
    tree_node<Tp>* old_null = node->left;
    builder->DeleteRoot(node);
    RemoveNode(builder, root_node, old_null);
}
   
template <class Tp>
void BinaryTreeDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    ConnectRight(builder, new_node, node);
    this->struct_->SetLeft(new_node, node->left);
    RemoveRootNode(builder, new_node, node);
    node = new_node;
}

template <class Tp>
void BinaryTreeDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node, tree_node<Tp> *&new_node) {
    tree_node<Tp>* r_node = (new_node->left)->right;
    tree_node<Tp>* l_node = node->right;
    this->struct_->SetRight(node, new_node->right);
    RemoveRootNode(builder, node, new_node);
    builder->ConnectRight(l_node, r_node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectRight(StructBuilderBase<Tp> *builder, tree_node<Tp> *&node) {
    builder->DisconnectRight(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::Clear(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
    tree_node<Tp> old_node;
    while ((root_node->left)->right != root_node->right) {
        RemoveNode(builder, root_node, root_node->right);
    }
}

template <class Tp>
void BinaryTreeDirector<Tp>::Delete(StructBuilderBase<Tp> *builder, tree_node<Tp> *root_node) {
    Clear(builder, root_node);
    RemoveRootNode(builder, root_node, root_node);
}

#endif //SEQUENCE_DIRECTOR_H_
