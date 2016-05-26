#include<iostream>
#include<stdlib.h>
#include<memory>
#include"linked_list.h"
void main(int argc, char * argv[])
{
	const int size_vals = 10;
	int vals[size_vals]{ 0,1,2,3,4,2,2,7,8,2 };
	linked_list<int> llist(&vals[0],size_vals);
	std::vector<int> indicies= llist.find(2);
	llist.clear();
	system("pause");
}