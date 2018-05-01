/* hello1.c
 *	purpose	 show the minimal calls needed to use curses
 *	outline  initialize, draw stuff, wait for input, quit
 */

#include	<stdio.h>
#include	<curses.h>

main(int ac, char *av[])
{
	//printf("%d",ac);
	//sleep(1);
	initscr() ;		/* turn on curses	*/
	int x,y;
	for(x = 0;x<8;x++){
		sleep(1);
		if(ac == 1){			/* send requests	*/
			printw("Hello World!");
		}
		else{
			for(y=1;y<ac;y++){
				printw("%s",av[y]);
				printw(" ");
			}
		}	
		refresh();
		sleep(1);
		clear();		/* update the screen	*/
		refresh();
	}
	getch();		/* wait for user input	*/
	endwin();		/* turn off curses	*/
}
