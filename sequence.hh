#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "xstruct.hh"

template <class Tp>
class Sequence : public XStruct<Tp> {
    private:
    protected:
    public:
        Sequence();
        Sequence(XStorage<Tp>* _storage, XBuilder<Tp>* builder, XDirector<Tp>* director);
        Sequence(XStorage<Tp>* _storage);
        ~Sequence();
        void Construct();
        bool IsEmpty();
        Tp* Front();
        const Tp* Front() const;
        Tp* Back();
        const Tp* Back() const;
        void PushBack(const Tp& val);
        void PushFront(const Tp& val);
        void PopBack();
        void PopFront();
        void Free();
};


#include "sequence_director.hh"
#include "sequence_builder.hh"

template <class Tp>
Sequence<Tp>::Sequence() {
}

template <class Tp>
Sequence<Tp>::Sequence(XStorage<Tp>* _storage, XBuilder<Tp>* builder, XDirector<Tp>* director) : XStruct<Tp>(_storage, builder, director) {
    Construct();
    is_built_ = false;
}

template <class Tp>
Sequence<Tp>::Sequence(XStorage<Tp>* _storage) : XStruct<Tp>(_storage, new SequenceBuilder(), new SequenceDirector(_storage)) {
    Construct();
    is_built_ = true;
}

template <class Tp>
void Sequence<Tp>::Construct() {
    builder->ConnectLeft(spec_node, root_node);
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
void Sequence<Tp>::Free() {
    
}

#endif // SEQUENCE_H_
