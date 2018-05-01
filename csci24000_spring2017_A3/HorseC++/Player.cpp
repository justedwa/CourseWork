//Honor Pledge: I pledge that I have neither given nor received any help on this assignment
#include "Player.h"
#include <stdlib.h>
#include <ctime>
char str[6] = "HORSE";
//constructor
player::player()
{
	player::string = new char [6];
}
//generates chance to make the shot
int player::shot()
{
	int a;
	a = rand() %2;
	return a;
}
//Getters
int player::getscore()
{
	return player::score;
}
char *player::getstring()
{	
	return player::string;
}
//setters
void player::setscore()
{
	this->score = score + 1;
}
void player::setstring()
{
	int x = getscore();
	this->string[x] = str[x];
}
//initializes the string to contain spaces
void player::initstring()
{
	int t;
	for(t=0;t<6;t++)
		{
			this->string[t] = ' ';
		}
}

//Destructor
player::~player()
{
	delete[] this->string;
}