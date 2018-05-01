#include "game.h"
#include <time.h>

void initializegame(int arr[][SCREENHEIGHT])
{
    //create counting variables
    int i,k;

    //loop through 2x2 array and assign starting variables
    for(i=0;i<SCREENWIDTH;i++)
    {
        for(k=0;k<SCREENHEIGHT;k++)
        {
            if(k == 0 || i == 0)
            {
                arr[i][k] = 9;
            }
            else if (k ==(SCREENHEIGHT-1) || i ==(SCREENWIDTH-1))
            {
                arr[i][k]=9;
            }
            else if(k == 10 && i == 25)
            {
                arr[i][k] = 1;
            }
            else if(k == 20 && i == 45)
            {
                arr[i][k] = 2;
            }
            else
            {
                arr[i][k] = 0;
            }
        }
    }
}

//function for adding trophies
void addfood(int arr[][SCREENHEIGHT])
{
    //seed with random time and create random x and y
    srand(time(NULL));
    int randx,randy;
    while(1)
    {
        //create ran position and check if availble, break out if so
        randx = rand()%(SCREENWIDTH-1) + 1;
        randy = rand()%(SCREENHEIGHT-1) + 1;
        if(arr[randx][randy] == 0)
        {
            arr[randx][randy] = 8;
            break;
        }
    }
}

void updategame(int arr[][SCREENHEIGHT], int input,int *length,int *losecondition, int input2,int *length2,int *losecondition2)
{
    //create needed variables for conditions
    int i,k;
    int foodeaten = 0;
    int foodeaten2 = 0;
    int erasex,erasey;
    int newx,newy;
    int y11,x11;
    int y1,x1;

    //go through entire array and do snake 1 logic for movements
    for(i=0;i<SCREENWIDTH;i++)
    {
        for(k=0;k<SCREENHEIGHT;k++)
        {
            if(arr[i][k] == 1)
            {
                if(input == 'a' || input == 'd' || input == 's' || input == 'w')
                {
                    erasex =i;
                    erasey =k;
                }

                if(input == 'a')
                {
                    if((i-1)<1)
                    {
                        newx = SCREENWIDTH-2;
                        *losecondition = 1;
                    }
                    else
                    newx =i-1;
                    newy =k;
                }
                else if (input == 'd')
                {
                    if((i+1)==(SCREENWIDTH-1)){
                        newx = 1;
                        *losecondition = 1;
                    }
                    else
                    newx =i+1;
                    newy =k;
                }
                else if (input == 's')
                {
                    newx =i;
                    if((k+1)==(SCREENHEIGHT-1)){
                        newy = 1;
                        *losecondition = 1;
                    }
                    else
                    newy =k+1;
                }
                else if (input == 'w')
                {
                    newx =i;
                    if((k-1) < 1){
                        newy = SCREENHEIGHT-2;
                        *losecondition = 1;
                    }
                    else
                    newy =k-1;
                }
            }
        }
    }
    //check to see if input was appropriate for movement
    if(input == 'a' || input == 'd' || input == 's' || input == 'w')
    {
        //check if food was eaten and respond appropriately
        if(arr[newx][newy] == 8)
        {
            arr[erasex][erasey] = 10 + *length;
            arr[newx][newy] = 1;
            *length = *length + 1;
            foodeaten = 1;
        }
        //check for lose condition and respond appropriately
        else if((arr[newx][newy] < (2*MAXLENGTH+10) && arr[newx][newy] > 10) || arr[newx][newy] == 2)
        {
            *losecondition = 1;
            if(arr[newx][newy] == 2)
            {
                *losecondition2 = 1;
            }
        }
        else
        {
            //move snake's variables appropriately
            if(*length == 1)
            {
                arr[erasex][erasey] = 0;
            }
            else
            {
                for(i=0;i<SCREENWIDTH;i++)
                {
                    for(k=0;k<SCREENHEIGHT;k++)
                    {
                        if((arr[i][k]<MAXLENGTH) && (arr[i][k] > 10))
                        {
                            if(arr[i][k] == 11)
                            {
                                x1 = erasex;
                                y1 = erasey;
                                erasex = i;
                                erasey = k;
                            }
                            else
                            {
                                if((arr[i][k]-1) == 11)
                                {
                                    x11 = i;
                                    y11 = k;
                                }
                                else
                                {
                                    arr[i][k] = arr[i][k]-1;
                                }
                            }
                        }


                    }
                }
                arr[x1][y1] = *length + 9;
                if(*length > 2)
                {
                    arr[x11][y11] = 11;
                }

                arr[erasex][erasey] = 0;
            }
            arr[newx][newy] = 1;
        }
        if(foodeaten == 1)
        {
            addfood(arr);
        }
    }

    //chose to use same process for second player as it works fine and will be easiest solution
    //see above comments for logic behind code

    for(i=0;i<SCREENWIDTH;i++)
    {
        for(k=0;k<SCREENHEIGHT;k++)
        {
            if(arr[i][k] == 2)
            {
                if(input2 == 'a' || input2 == 'd' || input2 == 's' || input2 == 'w')
                {
                    erasex =i;
                    erasey =k;
                }

                if(input2 == 'a')
                {
                    if((i-1)<1)
                    {
                        newx = SCREENWIDTH-2;
                        *losecondition2 = 1;
                    }
                    else
                    newx =i-1;
                    newy =k;
                }
                else if (input2 == 'd')
                {
                    if((i+1)==(SCREENWIDTH-1)){
                        newx = 1;
                        *losecondition2 = 1;
                    }
                    else
                    newx =i+1;
                    newy =k;
                }
                else if (input2 == 's')
                {
                    newx =i;
                    if((k+1)==(SCREENHEIGHT-1)){
                        newy = 1;
                        *losecondition2 = 1;
                    }
                    else
                    newy =k+1;
                }
                else if (input2 == 'w')
                {
                    newx =i;
                    if((k-1) < 1){
                        newy = SCREENHEIGHT-2;
                        *losecondition2 = 1;
                    }
                    else
                    newy =k-1;
                }
            }
        }
    }

    if(input2 == 'a' || input2 == 'd' || input2 == 's' || input2 == 'w')
    {
        if(arr[newx][newy] == 8)
        {
            arr[erasex][erasey] = MAXLENGTH + *length2;
            arr[newx][newy] = 2;
            *length2 = *length2 + 1;
            foodeaten2 = 1;
        }
        else if((arr[newx][newy] < (2*MAXLENGTH+10) && arr[newx][newy] > 10) || arr[newx][newy] == 1)
        {
            *losecondition2 = 1;
            if(arr[newx][newy] == 1)
            {
                *losecondition = 1;
            }
        }
        else
        {
            if(*length2 == 1)
            {
                arr[erasex][erasey] = 0;
            }
            else
            {
                for(i=0;i<SCREENWIDTH;i++)
                {
                    for(k=0;k<SCREENHEIGHT;k++)
                    {
                        if((arr[i][k]<(2*MAXLENGTH+10) && (arr[i][k] > MAXLENGTH)))
                        {
                            if(arr[i][k] == (MAXLENGTH+1))
                            {
                                x1 = erasex;
                                y1 = erasey;
                                erasex = i;
                                erasey = k;
                            }
                            else
                            {
                                if((arr[i][k]-1) == (MAXLENGTH+1))
                                {
                                    x11 = i;
                                    y11 = k;
                                }
                                else
                                {
                                    arr[i][k] = arr[i][k]-1;
                                }
                            }
                        }


                    }
                }
                arr[x1][y1] = *length2 + (MAXLENGTH-1);
                if(*length2 > 2)
                {
                    arr[x11][y11] = MAXLENGTH+1;
                }

                arr[erasex][erasey] = 0;
            }
            arr[newx][newy] = 2;
        }
        if(foodeaten2 == 1)
        {
            addfood(arr);
        }
    }

}
