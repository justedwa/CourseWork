/* setecho.c
 *   usage:  setecho [y|n]
 *   shows:  how to read, change, reset tty attributes
 */
#include	<stdlib.h>
#include        <stdio.h>
#include        <termios.h>
#include 	<string.h>
#define  oops(s,x) { perror(s); exit(x); }

main(int ac, char *av[])
{
        struct termios info;

        if ( ac != 2 ){
		printf("Usage: ./seterase [Char] "); 
		exit(0);
	}

        if ( tcgetattr(0,&info) == -1 )          /* get attribs   */
		oops("tcgettattr", 1);

        if ( strcmp(av[1],"--help") == 0 ){
                printf("Changes backspace to specified character\n");
		printf("Usage: ./seterase [Char]\n");
		printf("Pass 0 to restore to default\n");          /* turn on bit    */
	}
	else if( av[1][0] == '0' ){
		info.c_cc[VERASE] = 127;
	}
        else{
                info.c_cc[VERASE] = av[1][0];         /* turn off bit   */
	}
        if ( tcsetattr(0,TCSANOW,&info) == -1 ) /* set attribs    */
               oops("tcsetattr",2);
}
