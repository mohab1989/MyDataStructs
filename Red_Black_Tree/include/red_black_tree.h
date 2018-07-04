template<class T>
class RedBlackTree
{
public:
    RedBlackTree() = default;
    void Insert(T value);
    int Search(T value);
    void remove (T value);
private:
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
        char color_ ='b';
    };
    TreeNode* root = nullptr;
    void StandradBinarySearchTreeInsert(T &value,TreeNode &current_node);
};

template<class T>
void RedBlackTree<T>::Insert(T value)
{
    if(root == nullptr)
    {
        root = new TreeNode(value);
        return;
    }
    StandradBinarySearchTreeInsert(value);
}


template<class T>
void RedBlackTree<T>::StandradBinarySearchTreeInsert(T &value, TreeNode &current_node)
{
    if(value == current_node.value_)
    {
        return;
    }
    if(value < current_node.value_)
    {
        if(current_node.left_child_ == nullptr)
        {
            current_node.left_child_ = new TreeNode(value);
            return;
        }
        else if(current_node.left_child_->value_ < value )
        {
            StandradBinarySearchTreeInsert(value,current_node);
        }
    }
    else
    {

    }

}

