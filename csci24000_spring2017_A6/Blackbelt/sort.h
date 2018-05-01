//I pledge that I have neither given nor received any help on this assignment.
#ifndef Sort_H
#define Sort_H

//parent class of bubblesort and insertsort and quicksort
class sort 
{
	public:
	sort()
	{
		
	}
	~sort()
	{
		
	}
	//making virtual function
	virtual void sortlist(int list[],int begin,int finish) = 0;
};
#endif