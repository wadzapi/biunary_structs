#ifndef XBUILDER_H_
#define XBUILDER_H_

#include "xstorage.hh"

template <class Tp>
class XBuilder {
    private:
    protected:
    public:
        XBuilder() {};
        virtual ~XBuilder() {};
        virtual XNode<Tp>* AddSpecNode(XStorage<Tp>* _storage) = 0;
        virtual XNode<Tp>* AddNode(XStorage<Tp>* _storage, const Tp& value = NULL) = 0;
        virtual void ConnectLeft(XNode<Tp>* left_node, XNode<Tp>* right_node) = 0;
        virtual void ConnectRight(XNode<Tp>* left_node, XNode<Tp>* right_node) = 0;
        virtual void DisconnectLeft(XNode<Tp>* node) = 0;
        virtual void DisconnectRight(XNode<Tp>* node) = 0;
        virtual void DeleteNode(XNode<Tp>* node) = 0;
};

#endif // XBUILDER_H_
