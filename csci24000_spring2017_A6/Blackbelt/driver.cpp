//I pledge that I have neither given nor received any help on this assignment.
#include "bubblesort.h"
#include "insertsort.h"
#include "sort.h"
#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream> 
#include <string> 
#include <sstream>
#include <ctime>
#include <string.h>

int main(void)
{
	srand(time(NULL));
	sort *bubble;
	sort *insert;
	sort *quick;
	int y;
	int list[50];
	int rand1;
	//creates strings to store user input
	std::string in;
	std::string x;
	while(1)
	{
		//menu 1
		
		int i = 0;
		std::cout<<"1.)Load List"<<std::endl;
		std::cout<<"2.)Exit"<<std::endl;
		std::cout<<"Please enter your selection:";
		std::cin>>x;
		std::cout<<"\n";
		//checks for selection
		if(x == "1")
		{
			std::ifstream inFile;
			inFile.open("data.txt");
			//load file into array
			if(inFile.is_open())
			{	
				std::string Line;
				std::stringstream conv;
				std::stringstream ss;
				std::string strNum;
			
				while(getline(inFile, Line))
				{
					ss.clear();
					ss.str("");
					ss.str(Line);
					while(getline(ss,strNum,','))
					{
						conv.clear();
						conv.str("");
						conv << strNum;
						conv >> list[i];
						i++;
					}
				}
				inFile.close();
			
			//print unsorted array
				std::cout<<"Unsorted List:";
				for(y=0;y<50;y++)
						{
							std::cout<<list[y]<<",";
							
						}
					std::cout<<"\b"<<" ";
					std::cout<<"\n";
				}
		else
		{
			std::cout<<"File not found"<<std::endl;
			break;
		}
			
			//second menu
			while(1)
			{
				
				std::cout<<"1.)Bubble Sort"<<std::endl;
				std::cout<<"2.)Insertion Sort"<<std::endl;
				std::cout<<"3.)Quick Sort"<<std::endl;
				std::cout<<"4.)Random Sort"<<std::endl;
				std::cout<<"5.)Exit"<<std::endl;
				std::cin>>in;
				std::cout<<"\n";
				//runs bubble sort algorithm and prints results
				if(in == "1")
				{
					bubble = new bubblesort();
					bubble->sortlist(list,0,0);
					std::cout<<"Bubble Sorted list:";
					for(y=0;y<50;y++)
					{
						std::cout<<list[y]<<",";
						
					}
					std::cout<<"\b"<<" ";
					std::cout<<"\n";
					delete bubble;
					break;
				}
				//runs insertion sort algorithm and prints results
				else if(in == "2")
				{
					insert = new insertsort();
					insert->sortlist(list,0,0);
					std::cout<<"Insertion Sorted List:";
					for(y=0;y<50;y++)
					{
						std::cout<<list[y]<<",";
						
					}
					std::cout<<"\b"<<" ";
					std::cout<<"\n";
					delete insert;
					break;
				}
				//quick sort and prints
				else if(in == "3")
				{
					quick = new quicksort();
					quick->sortlist(list,0,50);
					std::cout<<"Quick Sorted List:";
					for(y=0;y<50;y++)
					{
						std::cout<<list[y]<<",";
						
					}
					std::cout<<"\b"<<" ";
					std::cout<<"\n";
					delete quick;
					break;
				}
				//generates random number then uses that to select sort type using if statements
				else if(in == "4")
				{
					rand1 = rand() % 3 + 1;
					if(rand1 == 1)
					{
						bubble = new bubblesort();
						bubble->sortlist(list,0,0);
						std::cout<<"Bubble Sorted list:";
						delete bubble;
					}
					if(rand1 == 2)
					{
						insert = new insertsort();
						insert->sortlist(list,0,0);
						std::cout<<"Insertion Sorted List:";
						delete insert;
					}
					if(rand1 == 3)
					{
						quick = new quicksort();
						quick->sortlist(list,0,49);
						std::cout<<"Quick Sorted List:";
						delete quick;
					}
					//prints random sort array
					for(y=0;y<50;y++)
					{
						std::cout<<list[y]<<",";
						
					}
					std::cout<<"\b"<<" ";
					std::cout<<"\n";
					break;
				}
				//exits
				else if(in == "5")
				{
					x = "2";
					break;
				}
				//checks for invalid input
				else
				{
					std::cout<<"Please enter a valid option"<<std::endl;
					continue;
				}
			}
		}
		//exits second loop aka exits program
		if(x == "2")
		{
			std::cout<<"Goodbye!"<<std::endl;
			break;
		}
		//checks for invalid input
		else
		{
			std::cout<<"Please enter a valid option"<<std::endl;
			continue;
		}
	}
	
	
}