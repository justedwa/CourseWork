#include <stdio.h>
#ifndef fnct_H
#define fnct_H
//Function Prototypes
void auth();
int readIn(FILE *fp,int* timeout);
FILE* flags(int ac,char *av[],FILE *fp,int* timeout);
void timestamp(FILE *fp);
void exitNote(FILE *fp);



#endif