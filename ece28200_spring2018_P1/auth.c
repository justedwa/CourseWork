#include "fnct.h"
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* This Function takes user input with echo turned off and compares agains a hard coded password if a match is 
found the program continues otherwise an error message is displayed and the program will exit */

void auth(){
	printf("Please enter user password to continue:\n");
    struct termios currterm; //creates terminal struct so attribs can be edited
    tcgetattr(STDIN_FILENO, &currterm); //gets attributes
    char* tmp = (char*) malloc (512); //creates a char to store password input
    currterm.c_lflag &= ~ECHO; //turns echo off
    tcsetattr(STDIN_FILENO, TCSANOW, &currterm); //sets echo off attrib
    fflush(stdin); //clear buffer
    scanf("%s",tmp);
    if(strcmp(tmp,"abc") == 0){ //checks to see if pass is correct
		printf("\n Success!"); //if successful turn echo back on and free string 
		currterm.c_lflag |= ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &currterm);
		free(tmp);
		return;
    }
    else{ //else turn echo back on free string and exit
		printf("\n Failure!");
		currterm.c_lflag |= ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW,  &currterm);
		free(tmp);
		exit(0);
    }
}