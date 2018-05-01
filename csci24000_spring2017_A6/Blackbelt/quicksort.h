//I pledge that I have neither given nor received any help on this assignment.
#include "sort.h"
#ifndef quicksort_H
#define quicksort_H
//inherits from sort
class quicksort : public sort
{
	public:
	quicksort();
	~quicksort();
	
	virtual void sortlist(int list[],int begin,int finish);
};
#endif