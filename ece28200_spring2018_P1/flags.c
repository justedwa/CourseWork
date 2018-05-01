#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
/*This function will search the arguments for flags and the file name specified. If no file name is specified then one will be
generated automatically. The arguments passed on runtime must also be passed to this function as well as the timeout period and a file
pointer to store the newly opened file for editing*/

int flagsearch(int ac,char *av[],int* index,int* timeout);

FILE* flags(int ac,char *av[],FILE *fp,int* timeout){ //takes in args and returns a file pointer based on args
	int laststat; //variable for -l flag
	int* index = malloc(sizeof(int)); //creates a pointer to store the index of the file arg
	*index = -1; //defaults to -1
	laststat=flagsearch(ac,av,index,timeout); //uses flagsearch to look for -l and -t flags setting respective variables
	FILE *tmp;									//also modifies index to store the index of the file arg
	if((ac == 1 || *index == -1) && !laststat){ //if there is no input generate a file
		char buffer [80];
		time_t ttime; //this creates a time struct and formats to proper formats
		time(&ttime);
		struct tm * timeinfo = localtime(&ttime);
		strftime(buffer,80,"%Y%m%d-%H%M%S",timeinfo);
		char* temp = buffer;
		temp[strlen(temp)-1] = 0; //the formatted string then gets the .nte extention
		strcat(temp,".nte");
		tmp = fopen("note.cfg","w"); //stores this newly created file as the last file opened in the config file
		chmod("note.cfg",0600); //sets permissions
		fputs(temp,tmp); //stores the filename in .cfg file then closes
		fclose(tmp);
		fp = fopen(temp,"ab"); //opens the newly created file
		chmod(temp,0600); //permissions
		free(index); //memory management for index
		return fp; //returns file pointer
		}
    else if(laststat){	//if the last file flag set open note.cfg and read last file read line
		tmp = fopen("note.cfg","r");
		if(tmp == NULL){ //if there was no file previously throw an error
			printf("\nNo previous file found\n");
			exit(0);
		}
		char* c = (char*) malloc(512); //otherwise read in the first line of .cfg and open that file
		fgets(c,50,tmp);
		fclose(tmp);
		fp = fopen(c,"ab");
		chmod(c,0600); //permissions
		//if(fp == NULL) printf("hey");
		free(c); //memory management
		free(index);
		return fp;
    }
    else{ //if there is no -l flag and a file arg then open that arg using the index variable
		tmp = fopen("note.cfg","w");
		fputs(av[*index],tmp);
		fclose(tmp);
		printf("%s",av[*index]);
		fp = fopen(av[*index],"ab");
		chmod(av[*index],0600);
		free(index);
		return fp;
    }
}

int flagsearch(int ac,char *av[],int* index,int* timeout){
	int x;
	int y = 0; //counter variables and local variable for -l flag
	int last = 0;
	for(x=0;x<ac;x++){
		if((strcmp(av[x],"-t")) == 0){ //checks each arg for the -t flag
			if(ac >= x+1){
				int a = atoi(av[x+1]); //if found convert to an integer and store for use later
				*timeout = a;
				//printf("%s",av[x]);
				printf("%d",*timeout);
				x++;
			}
			else{ //if there is a -t flag but no number print error
				printf("Syntax: note -t [seconds]\n");
			}
		}
		else if(!strcmp(av[x],"-l")){ //if a -l flag is seen set last variable
			last = 1;
		}
		else{ //otherwise keep the index of the file arg
			if((x > 0) && (*index == -1))
				*index = x;
		}
	}
	return last;
}