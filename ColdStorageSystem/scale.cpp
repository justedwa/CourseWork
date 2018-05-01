
#include "functions.h"
#include "HX711.h"
#include <stdio.h>

float scale(HX711 scale)
{
    float weight;
    int x;
    
        fflush(stdin);
        getchar();
        printf("\n\r\n\rPlease remove all weight from scale, "
        "then press any button to zero the scale\n\r\n\r");
        getchar();
         scale.tare();
        
        printf("\n\r\n\rPress any button again to begin weighing!\n\r\n\r");
        getchar();
        

         weight = scale.getGram();

        
        //Handles negligible weight and calibration factor
        if((weight < 0.5) && (weight > -0.5))
            weight =0;
        else
           weight *= (15.625);
            
        //Converts to pounds
        weight *= 0.0022046;
            
        printf("\n\r\n\rWeight:  %.2f lbs\n\r\n\r", weight);
            
            
        return weight;  
}