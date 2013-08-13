#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_

#include "data_storage.hh"

template <class Tp>
class StructBuilderBase {
    private:
    protected:
        DataStorage<Tp>* storage_;
        size_t num_connections_;
        void SetStruct(DataStorage<Tp> *_storage) { storage_ = _storage; }
        virtual tree_node<Tp> *AddNodeLogic() = 0;
    public:
        StructBuilderBase() : storage_(NULL) {}
        StructBuilderBase(DataStorage<Tp> *_storage, size_t num_connections): storage_(_storage), num_connections_(num_connections) {}
        virtual ~StructBuilderBase() {}
        tree_node<Tp>* AddNode() {
            tree_node<Tp>* new_node = AddNodeLogic();
            AddNodeValue(new_node, Tp());
            return new_node;
        }
        tree_node<Tp>* AddNode(const Tp& value) {
            tree_node<Tp>* new_node = AddNodeLogic();
            AddNodeValue(new_node, value);
            return new_node;
        }
        tree_node<Tp> *AddRoot() {
            tree_node<Tp>* root_node = storage_->AddLogic();
            storage_->Reserve(root_node);
            return root_node;
        }
        void AddNodeValue(tree_node<Tp> *&node, const Tp& value) {
            Tp* new_val = storage_->AddData(value);
            storage_->SetData(node, new_val);
            storage_->Unreserve(new_val);
        }
        virtual void ConnectLeft(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void ConnectRight(tree_node<Tp> *node, tree_node<Tp> *new_node) = 0;
        virtual void DisconnectLeft(tree_node<Tp> *node) = 0;
        virtual void DisconnectRight(tree_node<Tp> *node) = 0;
        virtual void DeleteNode(tree_node<Tp>* node) = 0;
        void DeleteRoot(tree_node<Tp>* node) {
            storage_->SetLeft(node, NULL);
            storage_->SetRight(node, NULL);
            storage_->Unreserve(node);
        }
};

#endif //STRUCT_BUILDER_H_
