#include "sense.h"

void SetGear(info* currInfo,DigitalIn Nswitch){
    if(Nswitch == 1)
        currInfo->gear = 0;
    else if(Nswitch == 0)
        currInfo->gear = 1;
}
