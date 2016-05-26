#pragma once
#include<vector>
template<class T> 
class linked_list
{
public:
	linked_list(T* obj,int size_objs);

	~linked_list();

	//----- Functions-----//
	T operator[](int index);
	std::vector<int> find(T obj);
	int size();
	void add_node(T obj);
	void delete_node(int index);
	void clear();
private:
	int m_length ;
	struct node
	{
		node * m_next;
		T m_obj;
	};
	node* m_head;
	node* m_tail;
	typename node * node_at(int index);
};
#include"linked_list.cpp"
