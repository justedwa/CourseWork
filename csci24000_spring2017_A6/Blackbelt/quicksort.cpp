//I pledge that I have neither given nor received any help on this assignment.
#include "quicksort.h"
#include <iostream>
#include <stdio.h>
//constructor/destructor
quicksort::quicksort()
{
	
}
quicksort::~quicksort()
{
	
}
//quick sort algorithm
void quicksort::sortlist(int list[], int begin,int finish)
{
	int q = begin; int v = finish;
	int temp;
	//divides array
	int pivot = list[(begin+finish)/2];
	while(q <= v)
	{
		while(list[q] < pivot)
		{
			q++;
		}
		while(list[v] > pivot)
		{
			v--;
		}
		if(q <= v)
		{
			temp = list[q];
			list[q] = list[v];
			list[v] = temp;
			q++;
			v--;
		}
	};
	//recursion
	if(begin < v)
	{
		sortlist(list,begin,v);
	}
	if(q < finish)
	{
		sortlist(list,q,finish);
	}
	
	
}