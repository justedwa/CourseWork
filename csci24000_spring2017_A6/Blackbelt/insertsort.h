//I pledge that I have neither given nor received any help on this assignment.
#include "sort.h"
#ifndef insertsort_H
#define insertsort_H
//inherits from sort
class insertsort : public sort
{
	public:
	insertsort();
	~insertsort();
	
	virtual void sortlist(int list[],int begin,int finish);
};
#endif