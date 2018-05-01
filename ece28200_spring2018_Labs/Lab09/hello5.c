/* hello5.c
 *    purpose  bounce a message back and forth across the screen
 *    compile  cc hello5.c -lcurses -o hello5
 */
#include	<curses.h>

#define	LEFTEDGE	10
#define	RIGHTEDGE	50
#define	ROW		10

main()
{
	char	message[] = "Hello";
	char	blank[]   = "     ";
	int	dir = +1;
	int	pos = LEFTEDGE ;
	int x = 100000;
	initscr();
	  clear();
	  while(1){
		move(ROW,pos);
		addstr( message );		/* draw string		*/
		move(LINES-1,COLS-1);		/* park the cursor	*/
		refresh();			/* show string		*/
		usleep(x);
		x = x - 2500;
		if(x < 0) x = 100;
		move(ROW,pos);			/* erase string		*/
		addstr( blank );
		pos += dir;			/* advance position	*/
		if ( pos >= RIGHTEDGE ){		/* check for bounce	*/
			x=100000;
			dir = -1;
		}
		if ( pos <= LEFTEDGE ){
			x=100000;
			dir = +1;
		}
	  }
}
