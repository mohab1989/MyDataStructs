#include<iostream>
#include<stdlib.h>
#include<memory>
#include"linked_list.h"
void main(int argc, char * argv[])
{
	const int size_vals = 10;
	int vals[size_vals]{ 0,1,2,3,4,5,6,7,8,9 };
	linked_list<int> llist(&vals[0],size_vals);
	llist.add_node(10);
	llist.delete_node(3);
	int i = llist[2];
	 i = llist[3];
	 i = llist[4];
	 llist.delete_node(0);
	 i = llist[0];
	 i = llist[1];
	 llist.delete_node(llist.size() - 1);
	 i = llist[llist.size() - 2];
	 i = llist[llist.size() - 1];
	 llist.clear();
	system("pause");
}