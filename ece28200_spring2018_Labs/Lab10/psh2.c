\/**  prompting shell version 2
 **
 **		Solves the `one-shot' problem of version 1
 **			Uses execvp(), but fork()s first so that the
 **			shell waits around to perform another command
 **		New problem: shell catches signals.  Run vi, press ^c.
 **/

#include	<stdio.h>
#include	<stdlib.h>
#include	<signal.h>
#include 	<string.h>
#define	MAXARGS		20				/* cmdline args	*/
#define	ARGLEN		100				/* token length	*/
char** makestring();
void execute(char**);
main()
{
	int x;
					/* an array of ptrs	*/
					/* read stuff here	*/
	char** args = makestring();	/* malloc etc		*/
	if(args[0] != NULL){
		execute(args);
	}
	free(args);
	return 0;
}

void execute( char **arglist)
/*
 *	use fork and execvp and wait to do it
 */
{
	int	pid,exitstatus;				/* of child	*/

	pid = fork();					/* make new process */
	switch( pid ){
		case -1:	
			perror("fork failed");
			exit(1);
		case 0:
			execvp(*arglist[0], arglist);		/* do it */
			perror("execvp failed");
			exit(1);
		default:
			while( wait(&exitstatus) != pid )
				;
			printf("child exited with status %d,%d\n",
					exitstatus>>8, exitstatus&0377);
	}
}
char** makestring()
/*
 * trim off newline and create storage for the string
 */
{
	int i;
	char* str = (char*) malloc(sizeof(char) * 512);
	char* token;
	char **args = (char**)calloc(20, sizeof(char*));
	for(i = 0;i<20;i++){
		args[i] = (char*) malloc(128*sizeof(char));
	}
	gets(str);
	token = strtok(str," ");
	i=0;
	while(i < 20){
		if(token != NULL){
			args[i] = token;
			token = strtok(NULL," ");
		}
		else{
			args[i] = NULL;
		}
		i++;
	}
	free(str);
	return args;			/* return ptr	*/
}
