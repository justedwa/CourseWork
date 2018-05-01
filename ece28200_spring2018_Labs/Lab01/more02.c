/*  more02.c  - version 0.2 of more
 *	read and print 24 lines then pause for a few special commands
 *      feature of version 0.2: reads from /dev/tty for commands
 */
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#define	PAGELEN	24
#define	LINELEN	512

void do_more(FILE *,char*,char*,FILE *);
int see_more(FILE *);

int main( int ac , char *av[] )
{
	char* in;
	char* out = NULL;
	if (ac == 2)
	{
		if(strcmp(av[1],"-o") == 0)
		{
			printf("Syntax Error \n");
			exit(1);
		}
	}
	if (ac > 2)
	{	
		if (strcmp(av[1],"-o") == 0)
		{
			out = av[2];
			in = av[3];
		}
		else if (strcmp(av[2],"-o") == 0)
		{
			out = av[3];
			in = av[1];
		}
	}
	else if (ac > 1 && ac < 3)
	{
		in = av[1];
		out = NULL;
	}
	FILE	*fp;
	FILE *oFile;
	if (out != NULL)
	{
		oFile = fopen(out,"a");
	}
	if ( ac == 1 )
		do_more( stdin,out,in,oFile);
	else
			if ( (fp = fopen( in , "r" )) != NULL)
			{
				do_more( fp,out,in,oFile ) ; 
				fclose( fp );
				//fclose(oFile);
			}
			else
				fclose(oFile);
				exit(1);
	return 0;
}

void do_more( FILE *fp,char* out,char* in,FILE *oFile)
/*
 *  read PAGELEN lines, then call see_more() for further instructions
 */
{
	char	line[LINELEN];
	int	num_of_lines = 0;
	int	see_more(FILE *), reply;
	FILE	*fp_tty;

	fp_tty = fopen( "/dev/tty", "r" );	   /* NEW: cmd stream   */
	if ( fp_tty == NULL )			   /* if open fails     */
		exit(1);                           /* no use in running */

	while ( fgets( line, LINELEN, fp ) ){		/* more input	*/
		if ( num_of_lines == PAGELEN ) {	/* full screen?	*/
			reply = see_more(fp_tty);  /* NEW: pass FILE *  */
			if ( reply == 0 )		/*    n: done   */
				break;
			num_of_lines -= reply;		/* reset count	*/
		}
		if ( out != NULL)
		{
			fputs (line,oFile);
		}
		if ( fputs( line, stdout )  == EOF )	/* show line	*/
			exit(1);			/* or die	*/
		num_of_lines++;				/* count it	*/
	}
}

int see_more(FILE *cmd)				   /* NEW: accepts arg  */
/*
 *	print message, wait for response, return # of lines to advance
 *	q means no, space means yes, CR means one line
 */
{
	int	c;

	printf("\033[7m more? \033[m");		/* reverse on a vt100	*/
	while( (c=getc(cmd)) != EOF )		/* NEW: reads from tty  */
	{
		if ( c == 'q' )			/* q -> N		*/
			return 0;
		if ( c == ' ' )			/* ' ' => next page	*/
			return PAGELEN;		/* how many to show	*/
		if ( c == '\n' )		/* Enter key => 1 line	*/
			return 1;		
	}
	return 0;
}
