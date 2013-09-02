#ifndef BINTREE_DIRECTOR_H_
#define BINTREE_DIRECTOR_H_

#include "xstruct.hh"

template <class Tp>
class BinaryTreeDirector : public XDirector<Tp> {
    private:
    protected:
    public:
        BinaryTreeDirector();
        BinaryTreeDirector(XStorage<Tp>* _storage);
        ~BinaryTreeDirector();
        XStructBase<Tp>* Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node = NULL, XNode<Tp>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right);
        void DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
        void DisconnectNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node);
        void RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node);
        void RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
        void Delete(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
};

#include "bin_tree.hh"
#include "queue.hh"

template <class Tp>
BinaryTreeDirector<Tp>::BinaryTreeDirector() {
}

template <class Tp>
BinaryTreeDirector<Tp>::BinaryTreeDirector(XStorage<Tp>* _storage) : XDirector<Tp>(_storage) {
}

template <class Tp>
BinaryTreeDirector<Tp>::~BinaryTreeDirector() {
}

template <class Tp>
XStructBase<Tp>* BinaryTreeDirector<Tp>::Construct(XBuilder<Tp> *builder, size_t num_nodes, XNode<Tp>* spec_node, XNode<Tp>* root_node, const Tp* values) {
    BinaryTree<Tp>* bin_tree;
    if (root_node == NULL) {
        root_node = builder->AddNode();
    }
    ///Construct and connect other nodes
    if (num_nodes > 0) {
        Queue<XNode<Tp>*> connect_queue(this->storage_);
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
void BinaryTreeDirector<Tp>::ConnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) {
    ConnectRight(builder, new_node, node);
    this->storage_->SetLeft(new_node, node->links[0]);
    RemoveSpecRootNode(builder, new_node, node);
    node = new_node;
}

template <class Tp>
void BinaryTreeDirector<Tp>::ConnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* struct_left, XStructBase<Tp>* struct_right) {
    XNode<Tp>* r_node = (new_node->links[0])->links[1];
    XNode<Tp>* l_node = node->links[1];
    this->storage_->SetRight(node, new_node->links[1]);
    RemoveSpecRootNode(builder, node, new_node);
    builder->ConnectRight(l_node, r_node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectLeft(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::DisconnectRight(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp>* node);
    builder->DisconnectRight(node);
}
        
template <class Tp>
void BinaryTreeDirector::DisconnectNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node) {
    DisconnectLeft();
    DisconnectRight();
}

template <class Tp>
void BinaryTreeDirector<Tp>::RemoveNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct, XNode<Tp> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp>
void BinaryTreeDirector<Tp>::RemoveSpecRootNode(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
    XNode<Tp>* old_null = node->links[0];
    builder->DeleteRoot(node);
    RemoveNode(builder, spec_node, old_null);
}
   
template <class Tp>
void BinaryTreeDirector<Tp>::Clear(XBuilder<Tp> *builder, XStructBase<Tp>* _struct) {
    XNode<Tp> old_node;
    while ((spec_node->links[0])->links[1] != spec_node->links[1]) {
        RemoveNode(builder, spec_node, spec_node->links[1]);
    }
}

template <class Tp>
void BinaryTreeDirector<Tp>::Delete(XBuilder<Tp> *builder, XStructBase<Tp>* _struct);
    Clear(builder, spec_node);
    RemoveSpecRootNode(builder, spec_node, spec_node);
}

#endif //BINTREE_DIRECTOR_H_
