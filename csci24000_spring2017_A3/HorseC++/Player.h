//Honor Pledge: I pledge that I have neither given nor received any help on this assignment
#ifndef player_H
#define player_H

class player {
	private:
		int score = 0; //for holding the amount of shots hit
		char *string; //for holding the horse string
	public:
		//Default Constructor
		player();
		//Destructor
		~player();
		int shot(); //runs the shooting simulation
		int getscore(); //getters for private variables
		char *getstring();
		void setstring(); //setters to manipulate variables
		void setscore();
		void initstring(); //sets initial value of string
};

#endif