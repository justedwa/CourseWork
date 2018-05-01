//I pledge that I have neither given nor received any help on this assignment.
#include "insertsort.h"
//constructor/destructor
insertsort::insertsort()
{
	
}
insertsort::~insertsort()
{
	
}
//insert sort algorithm
void insertsort::sortlist(int list[])
{
	int temp;
	int o,u;
	
	for(o=0;o<50;o++)
	{
		temp = list[o];
		u = o-1;
		while(temp < list[u])
		{
			list[u+1] = list[u];
			u--;
		}
		list[u+1] = temp;
	}
	
	
}