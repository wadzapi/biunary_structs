#ifndef XSTRUCT_H_
#define XSTRUCT_H_

#include "struct.hh"

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
class XStruct : public Struct<Tp, NUM_LINKS> {
    private:
    protected:
    public:
        XStruct();
        XStruct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node = NULL, tree_node<Tp, NUM_LINKS>* spec_node = NULL, StructBuilderBase<Tp, NUM_LINKS>* builder = NULL, StructDirectorBase<Tp, NUM_LINKS>* director = NULL);
        ~XStruct();
        void UpdateSpecNode();
        void Construct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node = NULL, tree_node<Tp, NUM_LINKS>* spec_node = NULL);
        bool Empty();
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        const Tp* Back() const;
        void PushBack(const Tp& val);
        void PushFront(const Tp& val);
        void PopBack();
        void PopFront();
};


#include "sequence_director.hh"
#include "sequence_builder.hh"

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::XStruct() {
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::XStruct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node, tree_node<Tp, NUM_LINKS>* spec_node, StructBuilderBase<Tp, NUM_LINKS>* builder, StructDirectorBase<Tp, NUM_LINKS>* director) : Struct<Tp, NUM_LINKS>(_storage, root_node, spec_node, builder, director) {
    Construct(_storage, root_node, spec_node);
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Construct(DataStorage<Tp, NUM_LINKS>* _storage, tree_node<Tp, NUM_LINKS>* root_node, tree_node<Tp, NUM_LINKS>* spec_node) {
    this->storage_ = _storage;
    if (this->director_ == NULL) {
        this->director_ = new XStructDirector<Tp>(_storage);
    }
    if (this->builder_ == NULL) {
        this->builder_ = new XStructBuilder<Tp>(_storage);
    }
    if (spec_node == NULL) {
        spec_node = this->builder_->AddRoot();
        SetSpecNode(spec_node);
    }
    if (root_node == NULL) {
        root_node = this->builder_->AddNodeLogic();
        SetRootNode(root_node);
    }
    this->is_built_ = true;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::~XStruct() {}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
bool XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Empty() {
    if (this->spec_node_->links[0] == this->spec_node_->links[1]) {
        return true;
    }
    return false;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
Tp* XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Front() {
    //return ((this->spec_node_->links[0])->links[1])->value;
    Tp* front_val = (this->root_node_->links[1])->value;
    return front_val;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
const Tp* XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Front() const {
    //return ((this->spec_node_->links[0])->links[1])->value;
    Tp* front_val = (this->root_node_->links[1])->value;
    return front_val;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
Tp* XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Back() {
    Tp* back_val = (this->spec_node_->links[1])->value;
    return back_val;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
const Tp* XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::Back() const {
    Tp* back_val = (this->spec_node_->links[1])->value;
    return back_val;
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::PushBack(const Tp& val) {
    XStruct<Tp, NUM_LINKS, LINKS_OFFSET>* new_node = (XStruct<Tp, NUM_LINKS, LINKS_OFFSET>*)this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectRight(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug 
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::PushFront(const Tp& val) {
    XStruct<Tp, NUM_LINKS, LINKS_OFFSET>* new_node = this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectLeft(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::PopBack() {
    this->director_->RemoveNode(this->builder_, this, this->spec_node_->links[1]);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::PopFront() {
    this->director_->RemoveNode(this->builder_, this, this->root_node_->links[1]);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp, size_t NUM_LINKS, size_t LINKS_OFFSET>
void XStruct<Tp, NUM_LINKS, LINKS_OFFSET>::UpdateSpecNode() {
}

#endif // XSTRUCT_H_
