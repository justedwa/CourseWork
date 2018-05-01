//Honor Pledge: I pledge that I have neither given nor received any help on this assignment
#include <iostream>
#include <stdlib.h> 
#include <ctime>

#define RACE_LENGTH 50

void advanceRacerA(int* ptrRacerA);
void advanceRacerB(int* ptrRacerB);
void printPosition(int* ptrRacerA, int* ptrRacerB);

void advanceRacerA(int* ptrRacerA)
{
	//rolls a random number to determine obstacle or not
	int a = rand() % 10 + 1;
	//conditions for the result of random number generation
	if (a <= 3)
	{
		*ptrRacerA += 4;
	}
	if (a == 4)
	{
		*ptrRacerA += 5;
	}
	if (5 <= a && a <= 7)
	{
		*ptrRacerA -= 2;
	}
	if (8 <= a && a <= 9)
	{
		*ptrRacerA -= 3;
	}
	if (a == 10)
	{
		*ptrRacerA -= 4;
	}
}

void advanceRacerB(int* ptrRacerB)
{
	//creates another random number
	int a = rand() % 10 + 1;
	//conditional statements for racer B's movement
	if (a <= 4)
	{
		*ptrRacerB += 5;
	}
	if (a == 5)
	{
		*ptrRacerB += 6;
	}
	if (6 <= a && a <= 7)
	{
		*ptrRacerB -= 1;
	}
	if (8 <= a && a <= 9)
	{
		*ptrRacerB -= 2;
	}
	if (a == 10)
	{
		*ptrRacerB -= 4;
	}
}
void printPosition(int* ptrRacerA, int* ptrRacerB)
{
	int x;
	//uses for loops to print the position of the racers
	for(x = 1; x <= 50; x++) 
	{
		if (x == *ptrRacerA) 
		{
			std :: cout << "A";
		}
		else if (x == *ptrRacerB) 
		{
			std :: cout << "B";
		}
		else 
		{
			std :: cout << " ";
		}
	}
	
	std::cout<<"|";
	// Shows the racer crossing the finish line
	if (*ptrRacerA >= 50)
		{
			std::cout<<"A";
		}
		if (*ptrRacerB >= 50)
		{
			std::cout<<"B";
		}
	std::cout<<"\n";
}

int main()
{
	int a, b;
	a = 0;
	b = 0;
	srand(time(NULL));
	// seeds random number generator with time
	std::cout << "Welcome to the Spartan Race!\n";
	std::cout << "READY...SET...GO!\n";
	std::cout << "Start                                             Finish\n";
	while (1)
	{
		advanceRacerA(&a);
		advanceRacerB(&b);
		//sets conditions for racer position eliminates negatives
		if (a < 0)
		{
			a = 1;
		}
		if (b < 0)
		{
			b = 1;
		}
		//keeps racers from landing on each other
		if ((a == b))
		{
			if (a == 0)
			{
				b++;
			}
			else
			{
				a--;
			}
		}
		printPosition(&a, &b);
		//displays victor also shows start and finish
		if (a >= 50)
		{
			std::cout << "---------------------------------------------------\n";
			std::cout << "Start                                             Finish\n";
			std::cout << "I am victorious\n";
			break;
		}
		if (b >= 50)
		{
			std::cout << "---------------------------------------------------\n";
			std::cout << "Start                                             Finish\n";
			std::cout << "Racer B is victorious\n";
			std::cout<< "I must train harder \n";
			break;
		}
	}

}

