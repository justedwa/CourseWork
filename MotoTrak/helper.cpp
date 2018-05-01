#include "helper.h"
#include "mbed.h"

void printStruct(info* currInfo,Serial pc){
    pc.printf("%d",currInfo->gear);
}