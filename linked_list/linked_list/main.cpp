#include<iostream>
#include<stdlib.h>
#include<memory>
#include"linked_list.h"
void main(int argc, char * argv[])
{
	const int size_vals = 10;
	int vals[size_vals]{ 0,1,2,3,4,5,6,7,8,9 };
	linked_list<int> llist(&vals[0],size_vals);
	//llist.reverse_all();
	//llist.recurrsive_reverse_all(llist.head());
	//llist.reverse_after(5);
	//std::vector<int> indicies= llist.find(2);
	//llist.reverseAfter(llist.head(), 1);
	llist.insert(2, 20);
	llist.insert(3, 30);
	llist.insert(11, 110);
	llist.insert(0, 1000);

	llist.console_display();
	llist.clear();
	//linked_list<std::string> stringList();
	//stringList().add_node("Hello");
	//stringList().add_node("World!!");
	//stringList().console_display();
	system("pause");
}