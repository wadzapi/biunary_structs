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
        tree_node<Tp>* Construct(StructBuilderBase<Tp> *builder, size_t num_nodes);
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
    tree_node<Tp>* root_node = this->struct_->addLogic();
    tree_node<Tp>* new_node;
    for (size_t i = 0; i < num_nodes; i++) {
        new_node = builder->AddNode(this->struct_);
        builder->ConnectNode(root_node, new_node);
    } 
    return root_node;
}

#endif //STRUCT_DIRECTOR_H_
