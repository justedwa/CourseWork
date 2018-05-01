#include <stdlib.h>
#include <stdio.h>
#include <curses.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "fnct.h"
#include <signal.h>
/*Program allows the user to create text file notes from the command line. Syntax note [filename] -l -t [seconds].
the -t flag allows the user to set a timeout period. -l flag will open previous file.*/

int main(int ac,char *av[])
{
	int* timeout = malloc(sizeof(int)); //creates a pointer to store the timeout variable
	*timeout = 3; //sets timeout to the default
    auth(); //runs the password authentication function
    FILE *fp; //creates file pointer used to open the note file
    fp = flags(ac,av,fp,timeout); //sets the file pointer to point to the proper file determined by the args
   
    WINDOW *w; //curse windows instance
	
 
    //starts curse screen
	w = initscr();
    if (w == NULL) { //if you cant start the curse library exit
		fprintf(stderr, "Error initializing curses library.\n");
        return EXIT_FAILURE;
    }
    raw(); //terminal in raw mode
    int status = 0; //initializes status to default to no timestamp
	status = readIn(fp,timeout); //reads in the user input then will return an into based on wether there was input
	if(status == 1) timestamp(fp); //if the user added to a file also add a timestamp
    /* Done. */
    endwin(); //close the curses window		
    fclose(fp); //close the file pointer
	free(timeout); //free the dynamically allocated timeout variable
    return EXIT_SUCCESS;
}
