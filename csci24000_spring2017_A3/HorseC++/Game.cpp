//Honor Pledge: I pledge that I have neither given nor received any help on this assignment
#include<iostream>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include "Player.h"
#include <unistd.h>
char str1[6] = "HORSE";
int main (void)
{
	int w,l;
	char c;
	srand(time(NULL));
	while(1)
	{
		player *play1 = new player; //creates both new players
		player *play2 = new player;
		play1->initstring(); //initializes strings
		play2->initstring();
		std::cout<<"Welcome to the game of horse\n";
		std::cout<<"          ____|"<<std::endl;
		std::cout<<"        o  \%/ |~~\\"<<std::endl;
		std::cout<<" o//              |"<<std::endl;
		std::cout<<" 8                |"<<std::endl;
		std::cout<<"/ >               |"<<std::endl;
		std::cout<<"~ ~             ~~~~~~"<<std::endl;
		sleep(2);
		while(play1->getscore() < 5 && play2->getscore() < 5 ) //loop will run and simulate until 5 points are scored
		{
			w = play1->shot(); //generates the random numbers 0 or 1
			l = play2->shot();
			if (w == 1 && l == 0) //victory conditions
			{
				std::cout<<"Player #1: Hit the Shot!\n";
				std::cout<<"Player #2: Missed the Shot!\n";
				play2->setstring();
				play2->setscore();
				std::cout<<"Player #2 added a '"<< str1[(play2->getscore())-1] << "'\n";
			}
			if ( w== 0 && l == 1)
			{
				std::cout<<"Player #2: Hit the Shot!\n";
				std::cout<<"Player #1: Missed the Shot!\n";
				play1->setstring();
				play1->setscore();
				std::cout<<"Player #1 added a '"<< str1[(play1->getscore())-1] << "'\n";
			}
			if (w == 0 && l == 0)
			{
				std::cout<<"Both Players Missed!!\n";
			}
			if (w == 1 && l == 1)
			{
				std::cout<<"Both Players Hit the shot!!\n";
			}
			sleep(1);
		}
		// prints the final value of the strings
		std::cout<<"Player 1:"<<play1->getstring();
		std::cout<<"                 Player 2:"<<play2->getstring()<<std::endl;
		//displays victor
		if(strcmp(play1->getstring(),str1)== 0)
			{
				std::cout<<"Player 2 is victorious!\n";
			}
		else
			{
				std::cout<<"Player 1 is victorious!\n";
			}
		//asks user to play again and deletes memory allocated on the heap
		std::cout<<"Play Again? (Y/N)\n";
		std::cin>>c;
		if(c == 'y' || c == 'Y')
			{
				delete play1;
				delete play2;
			}
		else
			{
				delete play1;
				delete play2;
				break;
			}
	}
	return 0;
}
	
	
