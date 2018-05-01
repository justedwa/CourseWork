#include "parse.h"
#include <string.h>
#include <stdlib.h>
/*Packet Structure:
[,Data,HR,Temp,time,humidity,]*/
int parse(char* str,info* currInfo){
    if(str[0] == '[')
        ;
    else
        return -1;
    char* temp = strtok(str,",");
    temp = strtok(NULL,",");
    if(!strcmp(temp,"Data")){
        temp = strtok(NULL,",");
        currInfo->hr = atoi(temp);
        temp = strtok(NULL,",");
        currInfo->temp = atoi(temp);
        temp = strtok(NULL,",");
        currInfo->humidity = atoi(temp);
        return 0;
    }
    else if(!strcmp(temp,"HRALERT"))
        return 1;
    else if(!strcmp(temp,"CRASH"))
        return 2;
    else if(!strcmp(temp,"FORWARD"))
        return 3;
    else if(!strcmp(temp,"BACK"))
        return 4;
    else if(!strcmp(temp,"GPS")){
        temp = strtok(NULL,",");
        currInfo->x = atof(temp);
        temp = strtok(NULL,",");
        currInfo->y = atof(temp);
        temp = strtok(NULL,",");
        currInfo->speed = atof(temp);
        return 0;
    }
    else if(!strcmp(temp,"WIFI")){ //[,WIFI,hr,temp,humidity,x,y,speed,lean,accel,gear,]
        temp = strtok(NULL,",");
        currInfo->hr = atoi(temp);
        temp = strtok(NULL,",");
        currInfo->temp = atoi(temp);
        temp = strtok(NULL,",");
        currInfo->humidity = atoi(temp);
         temp = strtok(NULL,",");
        currInfo->x = atof(temp);
        temp = strtok(NULL,",");
        currInfo->y = atof(temp);
        temp = strtok(NULL,",");
        currInfo->speed = atof(temp);
        temp = strtok(NULL,",");
        currInfo->lean = atof(temp);
        temp = strtok(NULL,",");
        currInfo->accel = atoi(temp);
        temp = strtok(NULL,",");
        currInfo->gear = atoi(temp);
        return 0;
        }       
    else
        return -1;
}
void initializeStruct(info* a){
    a->accel = 0;
    a->x = 0;
    a->y = 0;
    a->temp = 0;
    a->lean = 0;
    a->speed = 0;
    a->humidity = 0;
    a->hr = 0;
}    