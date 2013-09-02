#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "xstruct.hh"

template <class Tp>
class Sequence : public XStruct<Tp> {
    private:
    protected:
    public:
        Sequence();
        Sequence(XStorage<Tp>* _storage, XNode<Tp>* root_node = NULL, XNode<Tp>* spec_node = NULL, XBuilder<Tp>* builder = NULL, XDirector<Tp>* director = NULL);
        ~Sequence();
        void UpdateSpecNode();
        void Construct(XStorage<Tp>* _storage, XNode<Tp>* root_node = NULL, XNode<Tp>* spec_node = NULL);
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

template <class Tp>
Sequence<Tp>::Sequence() {
}

template <class Tp>
Sequence<Tp>::Sequence(XStorage<Tp>* _storage, XNode<Tp>* root_node, XNode<Tp>* spec_node, XBuilder<Tp>* builder, XDirector<Tp>* director) : XStruct<Tp>(_storage, root_node, spec_node, builder, director) {
    Construct(_storage, root_node, spec_node);
}

template <class Tp>
void Sequence<Tp>::Construct(XStorage<Tp>* _storage, XNode<Tp>* root_node, XNode<Tp>* spec_node) {
    this->storage_ = _storage;
    if (this->director_ == NULL) {
        this->director_ = new SequenceDirector<Tp>(_storage);
    }
    if (this->builder_ == NULL) {
        this->builder_ = new SequenceBuilder<Tp>(_storage);
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

template <class Tp>
Sequence<Tp>::~Sequence() {}

template <class Tp>
bool Sequence<Tp>::Empty() {
    if (this->spec_node_->links[0] == this->spec_node_->links[1]) {
        return true;
    }
    return false;
}

template <class Tp>
Tp* Sequence<Tp>::Front() {
    //return ((this->spec_node_->links[0])->links[1])->value;
    Tp* front_val = (this->root_node_->links[1])->value;
    return front_val;
}

template <class Tp>
const Tp* Sequence<Tp>::Front() const {
    //return ((this->spec_node_->links[0])->links[1])->value;
    Tp* front_val = (this->root_node_->links[1])->value;
    return front_val;
}

template <class Tp>
Tp* Sequence<Tp>::Back() {
    Tp* back_val = (this->spec_node_->links[1])->value;
    return back_val;
}

template <class Tp>
const Tp* Sequence<Tp>::Back() const {
    Tp* back_val = (this->spec_node_->links[1])->value;
    return back_val;
}

template <class Tp>
void Sequence<Tp>::PushBack(const Tp& val) {
    Sequence<Tp>* new_node = (Sequence<Tp>*)this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectRight(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug 
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PushFront(const Tp& val) {
    Sequence<Tp>* new_node = this->director_->Construct(this->builder_, 1, NULL, NULL, &val);
    this->director_->ConnectLeft(this->builder_, this, new_node);
    this->director_->RemoveSpecRootNode(this->builder_, new_node);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopBack() {
    this->director_->RemoveNode(this->builder_, this, this->spec_node_->links[1]);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::PopFront() {
    this->director_->RemoveNode(this->builder_, this, this->root_node_->links[1]);
    ///for debug
    this->storage_->PrintCounters(); ///for debug
}

template <class Tp>
void Sequence<Tp>::UpdateSpecNode() {
}

#endif // SEQUENCE_H_
