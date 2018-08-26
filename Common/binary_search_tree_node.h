#include <memory>
#include "node.h"

template <class T>
class BinarySearchTreeNode: public Node<T> {
    public:
        BinarySearchTreeNode();
        BinarySearchTreeNode(T value);
        void SetValue(T value) override;
        T GetValue() const override;
        std::unique_ptr<BinarySearchTreeNode> right_child_ = nullptr;
        std::unique_ptr<BinarySearchTreeNode> left_child_ = nullptr;
};
template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(){
}

template <class T>
BinarySearchTreeNode<T>::BinarySearchTreeNode(T value){
    SetValue(value);
}

template <class T>
T BinarySearchTreeNode<T>::GetValue() const {
    return this->value_;
}


template <class T>
void BinarySearchTreeNode<T>::SetValue(T value){
    this->value_ = value;
}
