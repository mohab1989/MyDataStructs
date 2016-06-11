#pragma once
#include "linked_list.h"

template<class T>
linked_list<T>::linked_list() :m_length(0), m_head(nullptr), m_tail(nullptr) {}


template<class T>
linked_list<T>::linked_list(T* obj,int size_objs):m_length(0),m_head(nullptr),m_tail(nullptr){
	for (int node_num = 0; node_num < size_objs; node_num++)
	{
		add_node(obj[node_num]);
	}
}
template<class T>
T linked_list<T>::operator[](int index)
{
	if (index >= m_length)
	{
		printf("linked list index out of bounds\n");
		fflush(stdout);
		exit(1);
	}
	node * next_node = m_head;
	for (int i = 0; i < index; i++)
	{
		next_node = next_node->m_next;
	}
	return next_node->m_obj;
}

template<class T>
std::vector<int> linked_list<T>::find(T obj)
{
	std::vector<int> indicies;
	node * cur_node = m_head;
	for (int i = 0; i < m_length; i++)
	{
		if (cur_node->m_obj == obj)
		{
			indicies.push_back(i);
		}
		cur_node = cur_node->m_next;
	}
	return indicies;
}

template<class T>
typename linked_list<T>::node * linked_list<T>::node_at(int index)
{
	node * next_node = m_head;
	for (int i = 0; i < index; i++)
	{
		next_node = next_node->m_next;
	}
	return next_node;
}

template<class T>
int linked_list<T>::size()
{
	return m_length;
}

template<class T>
void linked_list<T>::add_node(T obj)
{ 
	if (m_head == nullptr)
	{
		m_head = new node;
		m_head->m_obj = obj;
		m_head->m_next = nullptr;
		m_tail = m_head;
	}
	else
	{
		node * new_node = new node;
		if (m_head->m_next == nullptr)
		{
			m_head->m_next = new_node;
		}
		new_node->m_obj = obj;
		new_node->m_next = nullptr;
		m_tail->m_next = new_node;
		m_tail = new_node;
	}
	m_length++;
}

template<class T>
void linked_list<T>::delete_node(int index)
{
	node * node_to_delete;
	if (index == 0)
	{
		node * new_head = m_head->m_next;
		node_to_delete = m_head;
		m_head = new_head;
	}
	else
	{
		node * previous_node = node_at(index - 1);
		node_to_delete = previous_node->m_next;
		previous_node->m_next = node_to_delete->m_next;
		if (index == m_length - 1)
		{
			m_tail = previous_node;
		}
	}
	delete node_to_delete;
	m_length--;
}

template<class T>
void linked_list<T>::clear()
{
	if (m_length != 0)
	{
		delete_node(0);
		clear();
	}
}

template< class T>
void linked_list<T>::console_display()
{
	node * cur_node = m_head;
	while (cur_node!= nullptr)
	{
		std::cout << cur_node->m_obj<<std::endl;
		cur_node = cur_node->m_next;
	}
}
template<class T>
void linked_list<T>::reverse_after(T obj)
{
	node * prev =nullptr;
	node * cur=nullptr;
	node * next=nullptr;
	node * split=nullptr;
	if (m_head->m_obj == obj)
	{
		cur = m_head;
		split = nullptr;
		m_head = m_tail;
	}
	else
	{
		prev = m_head;
		while (prev != nullptr)
		{
			cur = prev->m_next;
			if (cur->m_obj == obj)
			{
				split = prev;
				break;
			}
			prev = prev->m_next;
		}
	}

	m_tail = cur;
	next = cur->m_next;
	cur->m_next = nullptr;
	while (next !=nullptr)
	{
		prev = cur;
		cur = next;
		next = cur->m_next;
		cur->m_next = prev;
	}
	if(split!=nullptr)
	split->m_next = cur;
}
template<class T>
void linked_list<T>::reverse_all()
{
	node * prev = nullptr;
	node * cur = m_head;
	node * next = nullptr;
	if (m_head == nullptr)
	{
		return;
	}
	m_tail = cur;
	while (cur != nullptr)
	{
		next = cur->m_next;
		cur->m_next = prev;
		prev = cur;
		cur = next;
	}
	m_head = prev;
}
template<class T>
void linked_list<T>::recurrsive_reverse_all(node * cur)
{
	if (cur->m_next == nullptr)
	{
		m_head = cur;
		return;
	}
	recurrsive_reverse_all(cur->m_next);
	cur->m_next->m_next = cur;
	cur->m_next = NULL;
}

template<class T>
void linked_list<T>::reverseAfter(node* head, T obj)
{
	if (head->m_next == nullptr)
	{
		if (m_tail->m_next != nullptr)
		{
			m_tail->m_next = head;
		}
		else
		{
			m_head = head;
		}
		return;
	}
	while (head->m_obj != obj)
	{
		// will stop changing in the previous node of the one we are looking for
		m_tail = head;
		head = head->m_next;
		if ( head == NULL)
		{
			return;
		}
	}
	if (head->m_next == nullptr)
	{
		return;
	}
	reverseAfter(head->m_next, head->m_next->m_obj);
	head->m_next->m_next = head;
	head->m_next = NULL;
	m_tail = head;
}

template <class T>
void linked_list<T>::insert(int index, T obj)
{
	if (index >= m_length)
	{
		return;
	}
	if (index == m_length-1)
	{
		add_node(obj);
		return;
	}
	node * prev = m_head;
	for (int i = 0; i < index-1; i++)
	{
		prev = prev->m_next;
	}
	node * new_node = new node();
	new_node->m_obj = obj;
	if (prev == m_head)
	{
		new_node->m_next = prev;
		m_head = new_node;
	}
	else
	{
		new_node->m_next = prev->m_next;
		prev->m_next = new_node;
	}

	m_length++;
}

template<class T>
linked_list<T>::~linked_list()
{
	clear();
}
