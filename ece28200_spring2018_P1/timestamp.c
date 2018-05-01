#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
/*This function will generate a timestamp using the time.h library then append to the currently opened file which is passed
as a file pointer*/

void timestamp(FILE *fp){ //creates a time structure and generates a formatted string
		char buffer [80];
		time_t ttime;
		time(&ttime);
		struct tm *timeinfo = localtime(&ttime);
		strftime(buffer,80,"[%D %T %A]",timeinfo);
		char* temp = buffer; //puts the formatted string into the end of the current filelength
		fputs(temp,fp);
		fputs("\n",fp);
		return;

}