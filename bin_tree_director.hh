#ifndef SEQUENCE_DIRECTOR_H_
#define SEQUENCE_DIRECTOR_H_

#include "struct.hh"

template <class Tp>
class BinaryTreeDirector : public StructDirectorBase<Tp> {
    private:
    protected:
    public:
        BinaryTreeDirector();
        BinaryTreeDirector(DataStorage<Tp>* _storage);
        ~BinaryTreeDirector();
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

#include "bin_tree.hh"
#include "queue.hh"

template <class Tp>
BinaryTreeDirector<Tp>::BinaryTreeDirector() {
}

template <class Tp>
BinaryTreeDirector<Tp>::BinaryTreeDirector(DataStorage<Tp>* _storage) : StructDirectorBase<Tp>(_storage) {
}

template <class Tp>
BinaryTreeDirector<Tp>::~BinaryTreeDirector() {
}

template <class Tp>
StructBase<Tp>* BinaryTreeDirector<Tp>::Construct(StructBuilderBase<Tp> *builder, size_t num_nodes, tree_node<Tp>* spec_node, tree_node<Tp>* root_node, const Tp* values) {
    BinaryTree<Tp>* bin_tree;
    if (root_node == NULL) {
        root_node = builder->AddNode();
    }
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        Queue<tree_node<Tp>*> connect_queue(this->storage_);
        connect_queue.Push(root_node);
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
    return bin_tree;
}

template <class Tp>
void BinaryTreeDirector<Tp>::ConnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) {
    ConnectRight(builder, new_node, node);
    this->storage_->SetLeft(new_node, node->left);
    RemoveSpecRootNode(builder, new_node, node);
    node = new_node;
}

template <class Tp>
void BinaryTreeDirector<Tp>::ConnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* struct_left, StructBase<Tp>* struct_right) {
    tree_node<Tp>* r_node = (new_node->left)->right;
    tree_node<Tp>* l_node = node->right;
    this->storage_->SetRight(node, new_node->right);
    RemoveSpecRootNode(builder, node, new_node);
    builder->ConnectRight(l_node, r_node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectLeft(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectRight(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp>* node);
    builder->DisconnectRight(node);
}
        
template <class Tp>
void BinaryTreeDirector::DisconnectNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node) {
    DisconnectLeft();
    DisconnectRight();
}

template <class Tp>
void BinaryTreeDirector<Tp>::RemoveNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct, tree_node<Tp> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::RemoveSpecRootNode(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) {
    tree_node<Tp>* old_null = node->left;
    builder->DeleteRoot(node);
    RemoveNode(builder, spec_node, old_null);
}
   
template <class Tp>
void BinaryTreeDirector<Tp>::Clear(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct) {
    tree_node<Tp> old_node;
    while ((spec_node->left)->right != spec_node->right) {
        RemoveNode(builder, spec_node, spec_node->right);
    }
}

template <class Tp>
void BinaryTreeDirector<Tp>::Delete(StructBuilderBase<Tp> *builder, StructBase<Tp>* _struct);
    Clear(builder, spec_node);
    RemoveSpecRootNode(builder, spec_node, spec_node);
}

#endif //SEQUENCE_DIRECTOR_H_
