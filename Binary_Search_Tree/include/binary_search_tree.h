#include "binary_search_tree_node.h"
#include <vector>
#include <iostream>

template <class T>
class BinarySearchTree
{
    public:
    BinarySearchTree() = default;
    void Insert(T value);
    std::vector<T> ReturnInOrder() const;
    unsigned int size() const;

    private:
    void InsertRecursively(T &value, std::unique_ptr<BinarySearchTreeNode<T>> &node);
    T InOrder(const std::unique_ptr<BinarySearchTreeNode<T>> &node) const;
    std::unique_ptr<BinarySearchTreeNode<T>> root_ = nullptr;
    unsigned int size_ = 0;
};

template <class T>
void BinarySearchTree<T>::Insert(T value) {
    if(root_ == nullptr){
        root_ = std::make_unique<BinarySearchTreeNode<T>>(value);
        size_ = 1;
    }
    //std::unique_ptr<BinarySearchTreeNode<T>> current_node (root_.get());
    InsertRecursively(value,root_);
}

template <class T>
unsigned int BinarySearchTree<T>::size() const {
    return size_;
}

template <class T>
std::vector<T> BinarySearchTree<T>::ReturnInOrder() const{
    std::vector<T> inorder;
    inorder.push_back(InOrder(root_));
    return inorder;

}
template <class T>
T BinarySearchTree<T>::InOrder(
        const std::unique_ptr<BinarySearchTreeNode<T>> &node) const{
    return node->GetValue();
}

template <class T>
void BinarySearchTree<T>::InsertRecursively(T &inserted_value, std::unique_ptr<BinarySearchTreeNode<T>> &current_node){
    T current_value = current_node->GetValue();
    if(inserted_value == current_value)
    {
        return;
    }

    if(inserted_value < current_value)
    {
        auto& left_child = current_node->left_child_;
        if(left_child == nullptr)
        {
            left_child = std::make_unique<BinarySearchTreeNode<T>>(inserted_value);
            return;
        }
        else
        {
            current_node.reset(left_child.get());
        }
    }
    //else
    //{
        //if(current_node->right_child_ == nullptr)
        //{
            //current_node->right_child_ = new TreeNode(value);
            //return;
        //}
        //else
        //{
            //current_node = current_node->right_child_;
        //}
    //}
    //InsertRecursively(inserted_value,std::move(current_node));

}
