#ifndef XSTRUCT_DIRECTOR_H_
#define XSTRUCT_DIRECTOR_H_

#include "struct.hh"

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
class XStructDirector : public StructDirectorBase<Tp, NUM_LINKS> {
    private:
    protected:
    public:
        XStructDirector();
        XStructDirector(DataStorage<Tp, NUM_LINKS>* _storage);
        ~XStructDirector();
        StructBase<Tp, NUM_LINKS>* Construct(StructBuilderBase<Tp, NUM_LINKS> *builder, size_t num_nodes, tree_node<Tp, NUM_LINKS>* spec_node = NULL, tree_node<Tp, NUM_LINKS>* root_node = NULL, const Tp* values = NULL);
        void ConnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right);
        void ConnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right);
        void DisconnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node);
        void DisconnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node);
        void DisconnectNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS> *node);
        void RemoveNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS> *node);
        void RemoveSpecRootNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct);
        void Clear(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct);
        void Delete(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct);
};

#include "sequence.hh"

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::XStructDirector() {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::XStructDirector(DataStorage<Tp, NUM_LINKS>* _storage) : StructDirectorBase<Tp, NUM_LINKS>(_storage) {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::~XStructDirector() {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
StructBase<Tp, NUM_LINKS>* XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::Construct(StructBuilderBase<Tp, NUM_LINKS> *builder, size_t num_nodes, tree_node<Tp, NUM_LINKS>* spec_node, tree_node<Tp, NUM_LINKS>* root_node, const Tp* values) {
    StructBase<Tp, NUM_LINKS>* sequence;
    if (spec_node == NULL) {
        spec_node = builder->AddRoot();
    }
    if (root_node == NULL) {
        root_node = builder->AddNodeLogic();
    }
    this->storage_->SetLeft(spec_node, root_node);
    ///Construct and connect other nodes
    tree_node<Tp, NUM_LINKS>* new_node1 = root_node;
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

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::DisconnectNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS> *node) {
    tree_node<Tp, NUM_LINKS>* spec_node = _struct->GetSpecNode();
    if (spec_node->links[1] == node) {
        this->storage_->SetRight(spec_node, node->links[0]);
        builder->DisconnectLeft(node);
    } else if (spec_node->links[0] == node) {
        this->storage_->SetLeft(spec_node, node->links[1]);
        builder->DisconnectRight(node);
    } else {
        tree_node<Tp, NUM_LINKS> *l_node = node->links[0];
        tree_node<Tp, NUM_LINKS> *r_node = node->links[1];
        builder->DisconnectLeft(node);
        builder->DisconnectRight(node);
        builder->ConnectRight(l_node, r_node);
    }
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::RemoveNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS> *node) {
    DisconnectNode(builder, _struct, node);
    builder->DeleteNode(node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::RemoveSpecRootNode(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) {
    tree_node<Tp, NUM_LINKS>* old_spec = _struct->GetSpecNode();
    tree_node<Tp, NUM_LINKS>* old_root = _struct->GetRootNode();
    builder->DeleteRoot(old_spec);
    RemoveNode(builder, _struct, old_root);
}
   
template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::ConnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right) {
    ConnectRight(builder, struct_right, struct_left);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::ConnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* struct_left, StructBase<Tp, NUM_LINKS>* struct_right) {
    tree_node<Tp, NUM_LINKS>* root_right = struct_right->GetRootNode();
    tree_node<Tp, NUM_LINKS>* spec_left = struct_left->GetSpecNode();
    tree_node<Tp, NUM_LINKS>* spec_right = struct_right->GetSpecNode();
    builder->ConnectRight(spec_left->links[1], root_right);
    this->storage_->SetRight(spec_left, spec_right->links[1]);
    DisconnectNode(builder, struct_left, root_right);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::DisconnectLeft(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node) {
    builder->DisconnectLeft(node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::DisconnectRight(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct, tree_node<Tp, NUM_LINKS>* node) {
    builder->DisconnectRight(node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::Clear(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) {
    tree_node<Tp, NUM_LINKS>* spec_node = _struct->GetSpecNode();
    if (spec_node != NULL) {
        while ((spec_node->links[0])->links[1] != spec_node->links[1]) {
            RemoveNode(builder, _struct, spec_node->links[1]);
        }
    }
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStructDirector<Tp, NUM_LINKS, LINKS_OFFSET>::Delete(StructBuilderBase<Tp, NUM_LINKS> *builder, StructBase<Tp, NUM_LINKS>* _struct) {
    Clear(builder, _struct);
    RemoveSpecRootNode(builder, _struct);
}

#endif //XSTRUCT_DIRECTOR_H_
