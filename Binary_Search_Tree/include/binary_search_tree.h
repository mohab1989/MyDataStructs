#include "binary_search_tree_node.h"
#include <vector>
#include <iostream>
#include <algorithm>

template <class T>
class BinarySearchTree
{
	using NodePtr = std::shared_ptr<BinarySearchTreeNode<T>>;

public:
	BinarySearchTree() = default;
	void Insert(T value);
	std::vector<T> ReturnInOrder() const;
	unsigned int size() const;
	unsigned int depth() const;
	NodePtr Find(const T& value) const;
	int Height(NodePtr node) const;
	bool IsBalanced() const;

private:
	void InsertRecursively(T& value
		, NodePtr node
		, unsigned int& current_depth);

	void InOrder(const NodePtr node
		, std::vector<T>& inorder = nullptr) const;

	NodePtr FindRecursively(const T& value, const NodePtr& node) const;

	bool IsBalancedRecursively(const NodePtr& node) const;

	NodePtr root_ = nullptr;
	unsigned int size_ = 0;
	unsigned int depth_ = 0;
};

template <class T>
unsigned int BinarySearchTree<T>::size() const
{
	return size_;
}

template <class T>
unsigned int BinarySearchTree<T>::depth() const
{
	return depth_;
}

template <class T>
std::vector<T> BinarySearchTree<T>::ReturnInOrder() const
{
	std::vector<T> inOrder;
	InOrder(root_, inOrder);
	return inOrder;
}

template <class T>
void BinarySearchTree<T>::InOrder(
	const NodePtr node
	, std::vector<T>& inOrder) const
{
	if (node == nullptr)
	{
		return;
	}
	InOrder(node->left_child_, inOrder);
	inOrder.push_back(node->GetValue());
	InOrder(node->right_child_, inOrder);
	return;
}

template <class T>
auto BinarySearchTree<T>::Find(const T& value) const->NodePtr
{
	return FindRecursively(value, root_);
}

template <class T>
auto BinarySearchTree<T>::FindRecursively(const T& value, const NodePtr& node) const->NodePtr
{
	if (node == nullptr) return nullptr;
	if (node->GetValue() == value) return node;
	const auto& left_child = FindRecursively(value, node->left_child_);
	if (left_child) return left_child;
	const auto& right_child = FindRecursively(value, node->right_child_);
	if (right_child) return right_child;
	return nullptr;
}

template <class T>
void BinarySearchTree<T>::Insert(T value)
{
	if (root_ == nullptr) {
		root_ = std::make_shared<BinarySearchTreeNode<T>>(value);
		size_ = 1;
		return;
	}
	NodePtr current_node = root_;
	unsigned int current_depth = 0;
	InsertRecursively(value, current_node, current_depth);
}

template <class T>
void BinarySearchTree<T>::InsertRecursively(T& inserted_value
	, NodePtr current_node
	, unsigned int& current_depth)
{
	const auto current_value = current_node->GetValue();
	if (inserted_value == current_value)
	{
		return;
	}
	current_depth++;
	if (inserted_value < current_value)
	{
		auto& left_child = current_node->left_child_;
		if (left_child == nullptr)
		{
			current_node->left_child_ =
				std::make_shared<BinarySearchTreeNode<T>>(inserted_value);
			size_++;
			if (current_depth > depth_)
			{
				depth_++;
			}
			return;
		}
		current_node = left_child;
	}
	else
	{
		auto& right_child = current_node->right_child_;
		if (right_child == nullptr)
		{
			current_node->right_child_ =
				std::make_shared<BinarySearchTreeNode<T>>(inserted_value);
			size_++;
			if (current_depth > depth_)
			{
				depth_++;
			}
			return;
		}
		current_node = right_child;
	}

	InsertRecursively(inserted_value, current_node, current_depth);
}

template <class T>
int BinarySearchTree<T>::Height(NodePtr node) const
{
	if (node == nullptr) return -1;
	return 1 + std::max(Height(node->left_child_), Height(node->right_child_));
}

template <class T>
bool BinarySearchTree<T>::IsBalanced() const
{
	return IsBalancedRecursively(root_);
}

template <class T>
bool BinarySearchTree<T>::IsBalancedRecursively(const NodePtr& node) const
{
	if (node == nullptr) return true;
	return std::abs(Height(node->left_child_) - Height(node->right_child_)) <= 1
		&& IsBalancedRecursively(node->left_child_) && IsBalancedRecursively(node->right_child_);
}
