//I pledge that I have neither given nor received any help on this assignment.
#include "bubblesort.h"

bubblesort::bubblesort()
{
	
}

bubblesort::~bubblesort()
{
	
}
//bubble sort algorithm
void bubblesort::sortlist(int list[],int begin,int finish)
{
	int a;
	int w;
	int temp;
	while(1)
	{
		a = 0;
		for(int w = 0;w<49;w++)
		{
			if(list[w]>list[w+1])
			{
				temp = list[w];
				list[w] = list[w+1];
				list[w+1] = temp;
				a = 1;
			}
		}
		if(a == 0)
		{
			break;
		}
	}
}