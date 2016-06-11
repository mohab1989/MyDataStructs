#pragma once
#include<vector>
template<class T> 
class linked_list
{
private:
	int m_length;
	struct node
	{
		node * m_next;
		T m_obj;
	};
	node* m_head;
	node* m_tail;
	typename node * node_at(int index);

public:
	linked_list(T* obj,int size_objs);
	linked_list();
	~linked_list();

	//----- Functions-----//
	T operator[](int index);
	std::vector<int> find(T obj);
	int size();
	void add_node(T obj);
	void delete_node(int index);
	void clear();
	void console_display();
	void reverse_after(T obj);
	void reverse_all();
	void recurrsive_reverse_all(node * cur);
	void reverseAfter(node* head ,T obj);
	void insert(int index , T obj);

	node * head()
	{
		return m_head;
	}
	node * tail()
	{
		return m_tail;
	};
};
#include"linked_list.cpp"
