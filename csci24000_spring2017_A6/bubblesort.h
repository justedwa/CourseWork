//I pledge that I have neither given nor received any help on this assignment.
#include "sort.h"
#ifndef bubblesort_H
#define bubblesort_H
//inherits from sort
class bubblesort : public sort
{
	public:
	bubblesort();
	~bubblesort();
	
	virtual void sortlist(int list[]);
};
#endif