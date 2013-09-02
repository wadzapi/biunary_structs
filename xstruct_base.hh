#ifndef XSTRUCT_BASE_H_
#define XSTRUCT_BASE_H_

#include "xstorage.hh"

template <class Tp>
class XStructBase {
    private:
    protected:
        XStorage<Tp>* storage_;
        XNode<Tp>* root_node_;
        XNode<Tp>* spec_node_;
        bool is_built_;
    public:
        XStructBase() : storage_(NULL), root_node_(NULL), spec_node_(NULL), is_built_(false) {}
        XStructBase(XStorage<Tp>* _storage, XNode<Tp>* root_node, XNode<Tp>* spec_node) : storage_(_storage), root_node_(root_node), spec_node_(spec_node), is_built_(false) {}
        virtual ~XStructBase() {}
        void SetRootNode(XNode<Tp>* root_node) {
            if (this->root_node_ != root_node) {
                this->root_node_ = root_node;
                UpdateSpecNode();
            }
        }
        XNode<Tp>* GetRootNode() {
            return this->root_node_;
        }
        void SetSpecNode(XNode<Tp>* spec_node) {
            if (this->spec_node_ != spec_node) {
                this->spec_node_ = spec_node;
            }
        }
        XNode<Tp>* GetSpecNode() {
            return this->spec_node_;
        }
        virtual void UpdateSpecNode() = 0;
};

#endif // XSTRUCT_BASE_H_
