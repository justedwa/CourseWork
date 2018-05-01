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

int main( int ac , char *av[] )
{
	char* in;
	char* out;
	if (ac < 2)
	{
		printf("\nSyntax Error");
		exit(1);
	}
	if (ac == 2)
	{
		if(strcmp(av[1],"--help") == 0)
		{
			printf("\nAppends the contents of the source file to the destination\n");
			printf("Usage: append [destination] [source]\n");
			printf("Optional Flags:\n--help - Displays Help menu\n");
			exit(1);
		}
		else
		{
			printf("Syntax error!\n");
			exit(1);
		}
	}
	if (ac == 3)
	{	
		in = av[2];
		out = av[1];
	}
	if (ac > 3)
	{
		in = av[2];
		out = av[1];
		printf("Input Truncated to two args see --help for proper usage\n");
	}
	FILE	*fp;
	FILE *oFile;
	if ( out != NULL)
	{
		oFile = fopen(out , "a");
		printf("test1");
	}
	printf("test");
	if ( (fp = fopen( in , "r" )) != NULL)
	{
		do_more( fp,out,in,oFile ) ; 
		fclose( fp );
		fclose(oFile);
	}
	else
	{
		printf("Unable to open source file!");
		fclose(fp);
		fclose(oFile);
	}
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
		if ( out != NULL)
		{
			fputs (line,oFile);
		}		
	}
}


