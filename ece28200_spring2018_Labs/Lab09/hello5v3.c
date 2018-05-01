/* hello5.c
 *    purpose  bounce a message back and forth across the screen
 *    compile  cc hello5.c -lcurses -o hello5
 */
#include	<curses.h>
#include	<stdio.h>
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
TOP:	pos = LEFTEDGE;
	x=100000;
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
			usleep(1000);
			move(ROW,pos);
			addstr(blank);
			refresh();
			usleep(1000);
			move(12,35);
			addch(message[0]);
			move(9,35);
			addch(message[1]);
			move(12,37);
			addch(message[2]);
			move(8,37);
			addch(message[3]);
			move(10,40);
			addch(message[4]);
			refresh();
			sleep(1);
			clear();
			goto TOP;
		}
	  }
}
