#pragma once
#include "linked_list.h"

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
int * linked_list<T>::find(T obj)
{
	int * indicies;
	int * arrayPropagator = indicies;
	for (int i = 0; i < m_length; i++)
	{
		if (obj == this[i])
		{

		}
	}
	return nullptr;
}

template<class T>
typename linked_list<T>::node * linked_list<T>::node_at(int index)
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

template<class T>
linked_list<T>::~linked_list()
{
	clear();
}
