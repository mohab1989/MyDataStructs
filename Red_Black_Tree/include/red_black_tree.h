#include <iostream>
template<class T>
class RedBlackTree
{
public:
    RedBlackTree() = default;
    void Insert(T value);
    int Search(T value);
    void Remove (T value);
    void Show();
private:
    enum Color {RED, BLACK};
    class TreeNode
    {
    public:
        TreeNode(T value, TreeNode *parent=nullptr)
        {
            value_ = value;
            parent_ = parent;
        }
        T value_;
        TreeNode *parent_ = nullptr;
        TreeNode *right_child_ = nullptr;
        TreeNode *left_child_ = nullptr;
        bool color_ = RED;
    };
    TreeNode *root = nullptr;
    void StandradBinarySearchTreeInsert(T &value,TreeNode *current_node);
    void InOrder(TreeNode* node);
};

template<class T>
void RedBlackTree<T>::Show()
{
    InOrder(root);
}

template<class T>
void RedBlackTree<T>::InOrder(TreeNode *node)
{
    if(node == nullptr)
    {
        return;
    }
    InOrder(node->left_child_);
    std::cout << node->value_ << std::endl;
    InOrder(node->right_child_);
}

template<class T>
void RedBlackTree<T>::Insert(T value)
{
    if(root == nullptr)
    {
        root = new TreeNode(value);
        root->color_ = 'B';
        return;
    }
    TreeNode *current_node = root;
    StandradBinarySearchTreeInsert(value,current_node);
}


template<class T>
void RedBlackTree<T>::StandradBinarySearchTreeInsert(T &value, TreeNode *current_node)
{
    if(value == current_node->value_)
    {
        return;
    }
    if(value < current_node->value_)
    {
        if(current_node->left_child_ == nullptr)
        {
            current_node->left_child_ = new TreeNode(value);
            return;
        }
        else
        {
            current_node = current_node->left_child_;
        }
    }
    else
    {
        if(current_node->right_child_ == nullptr)
        {
            current_node->right_child_ = new TreeNode(value);
            return;
        }
        else
        {
            current_node = current_node->right_child_;
        }
    }
    StandradBinarySearchTreeInsert(value,current_node);
}

