#ifndef STRUCT_BUILDER_H_
#define STRUCT_BUILDER_H_

#include "data_storage.hh"

template <class Tp, size_t NUM_LINKS>
class StructBuilderBase {
    private:
    protected:
        DataStorage<Tp, NUM_LINKS>* storage_;
        size_t num_connections_;
        void SetStorage(DataStorage<Tp, NUM_LINKS> *_storage) { storage_ = _storage; }
    public:
        StructBuilderBase() : storage_(NULL) {}
        StructBuilderBase(DataStorage<Tp, NUM_LINKS> *_storage, size_t num_connections): storage_(_storage), num_connections_(num_connections) {}
        virtual ~StructBuilderBase() {}
        virtual tree_node<Tp, NUM_LINKS> *AddNodeLogic() = 0;
        tree_node<Tp, NUM_LINKS>* AddNode() {
            tree_node<Tp, NUM_LINKS>* new_node = AddNodeLogic();
            AddNodeValue(new_node, Tp());
            return new_node;
        }
        tree_node<Tp, NUM_LINKS>* AddNode(const Tp& value) {
            tree_node<Tp, NUM_LINKS>* new_node = AddNodeLogic();
            AddNodeValue(new_node, value);
            return new_node;
        }
        tree_node<Tp, NUM_LINKS> *AddRoot() {
            tree_node<Tp, NUM_LINKS>* root_node = storage_->AddLogic();
            storage_->Reserve(root_node);
            return root_node;
        }
        void AddNodeValue(tree_node<Tp, NUM_LINKS> *&node, const Tp& value) {
            Tp* new_val = storage_->AddData(value);
            storage_->SetData(node, new_val);
            storage_->Unreserve(new_val);
        }
        virtual void ConnectLeft(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node) = 0;
        virtual void ConnectRight(tree_node<Tp, NUM_LINKS> *node, tree_node<Tp, NUM_LINKS> *new_node) = 0;
        virtual void DisconnectLeft(tree_node<Tp, NUM_LINKS> *node) = 0;
        virtual void DisconnectRight(tree_node<Tp, NUM_LINKS> *node) = 0;
        virtual void DeleteNode(tree_node<Tp, NUM_LINKS>* node) = 0;
        void DeleteRoot(tree_node<Tp, NUM_LINKS>* node) {
            storage_->SetLeft(node, NULL);
            storage_->SetRight(node, NULL);
            storage_->Unreserve(node);
        }
};

#endif //STRUCT_BUILDER_H_
