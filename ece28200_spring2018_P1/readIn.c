#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

/*Function will read user input and store into a file. The file being used must be passed as a FILE* argument as well
as the getstr() timeout period*/

int sig = 0; //global variable for signal handler
jmp_buf buf; //jmp_buf for setting jump position
void handler(int signum); //prototype for handler

int readIn(FILE *fp,int* timeout){
	signal(SIGINT, handler); //sets up signal handlers for SIGINT and SIGALRM
	signal(SIGALRM, handler);
	char* c; //character pointer for storing user input
	int x = 0; //dummy variable used as counter
	if(fp == NULL) perror(0); //if the file does not exist display an error and exit
	printw("Type QUIT to quit.\n");
    while(1){ //while loop keeps taking user input until timeout, keyboard escape, or QUIT
		setjmp(buf); //sets position for jump function
		if(sig == 1) break; //checks variable set by signal handler if set exit
		c = (char*) malloc(512); //allocates memory to pointer so that it is ready to take input
			alarm(*timeout); //sets an alarm that will go off after the timeout period specified by user
			getstr(c); //gets a string from the user and stores in c
			alarm(0); //resets timer if the getstr succeeds
		if(strcmp(c,"QUIT") == 0){ //if QUIT is typed then free memory for C then exit
			free(c);
			if(x>0) //if there has been input return 1 else 0
				return 1;
			else
				return 0;
		}
		fputs(c,fp); //places inputted string into file
		fputs("\n",fp); //places newline
		free (c); //free's C so that input can be taken again
		x++; //increments counter to show that input has been taken
    }
	if(x>0) //checks to see if input has been taken
		return 1;
	else
		return 0;
}

void handler(int signum){
	sig = 1; //sets flag is signal has been triggered
	longjmp(buf,0); //jumps to setjmp location
}