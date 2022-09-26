#ifndef TRIE_DEFINED
#define TRIE_DEFINED
#include <vector>
#include <unordered_map>

namespace datastructures {

	template <class T> class Trie
	{
	public:
		Trie();
		struct TrieNode {
			std::unordered_map<T, TrieNode*> children;
			bool is_leaf = false;
		};
		void Insert(std::vector<T> inserted_elements);
		bool Search(std::vector<T> inserted_elements);

		void Clear();
		~Trie();
	private:
		void ClearFromNode(TrieNode** node_ptr);
		TrieNode* root_ptr_;
	};

	template <typename T>
	Trie<T>::Trie() {
		root_ptr_ = new TrieNode();
	};

	template<typename T>
	void Trie<T>::Insert(std::vector<T> inserted_elements) {
		TrieNode** current_node_ptr_ref = &root_ptr_;
		for (int element_id = 0; element_id < inserted_elements.size(); ++element_id) {
			current_node_ptr_ref = &(*current_node_ptr_ref)->children[inserted_elements[element_id]];
			*current_node_ptr_ref = *current_node_ptr_ref == nullptr ? new TrieNode() : *current_node_ptr_ref;
		}
		(*current_node_ptr_ref)->is_leaf = true;
	};

	template<typename T>
	bool Trie<T>::Search(std::vector<T> elements) {
		TrieNode** current_node_ptr_ref = &root_ptr_;
		for (int element_id = 0; element_id < elements.size(); ++element_id) {
			current_node_ptr_ref = &(*current_node_ptr_ref)->children[elements[element_id]];
			if (*current_node_ptr_ref == nullptr) {
				return false;
			}
		}
		if ((*current_node_ptr_ref)->is_leaf == true) {
			return true;
		}
		return false;
	}

	template<typename T>
	void Trie<T>::Clear() {
		ClearFromNode(&root_ptr_);
	}

	template<typename T>
	void Trie<T>::ClearFromNode(TrieNode** current_node_ptr_ref) {
		for (auto child : (*current_node_ptr_ref)->children) {
			ClearFromNode(&child.second);
		}
		(*current_node_ptr_ref)->children.clear();
		delete* current_node_ptr_ref;
	}
	template <typename T>
	Trie<T>::~Trie()
	{
		Clear();
	};
#endif // !TRIE_DEFINED
}