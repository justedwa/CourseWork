#include "parse.h"
#include <string.h>
#include <stdlib.h>
#include "info.h"
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
    else if(!strcmp(temp,"CRASH")){
        currInfo->crash = 1;
        return 2;
    }
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
        temp = strtok(NULL,",");
        currInfo->crash = atoi(temp);
        return 0;
        }       
    else
        return -1;
}   
