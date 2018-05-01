#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "functions.h"
#include "product.h"
#include "HX711.h"
#include "Dht11.h"

Dht11 sensor(D7);
float maxtemp = 80;
DigitalOut buzzer(D2);
DigitalOut LED(PTB22);

volatile float Farenheit;
volatile int Humidity;
extern int id[10];
extern int flag1;
extern int flag2;

//Adds a new product type to the database
struct product *addproduct(struct product *head)
{
    struct product *newp = (struct product*)malloc(sizeof( struct product));
    char name[20];
    unsigned int pid1, pid2, pid3, pid4;
    float weight, priceper;

    fflush(stdin);

    printf("\n\rName:\n\r");
    scanf("%20s", &name);
    fflush(stdin);
    printf("\n\rpid(1):\n\r");
    scanf("%d", &pid1);
    printf("\n\rpid(2):\n\r");
    scanf("%d", &pid2);
    printf("\n\rpid(3):\n\r");
    scanf("%d", &pid3);
    printf("\n\rpid(4):\n\r");
    scanf("%d", &pid4);
    printf("\n\rPriceper:\n\r");
    scanf("%f", &priceper);

    strcpy(newp->pname, name);
    newp->pid[0] = pid1;
    newp->pid[1] = pid2;
    newp->pid[2] = pid3;
    newp->pid[3] = pid4;
    newp->count = 1;
    newp->priceper = priceper;


    newp->next = head;
    head = newp;

    std::cout << "\n\r\n\r";
    
    return head;
}

//Sorts the list by product name alphabetical order
struct product *sortlist(struct product *head)
{
    struct product *temp, *ptr, *prev;
    int x, check;

    while(1)
    {
        check = 0;
        ptr = head;
        prev = head;

        while((ptr->next != NULL) && (ptr != NULL))
        {
            if(strcmp(ptr->pname, ptr->next->pname) > 0)
            {
                if(ptr == head)
                {
                    temp = ptr->next->next;
                    ptr->next->next = ptr;
                    head = ptr->next;
                    ptr->next = temp;
                    check = 1;
                    
                }

                else
                {
                    temp = ptr->next->next;
                    prev->next = ptr->next;
                    ptr->next->next = ptr;
                    ptr->next = temp;
                    check = 1;
                }
            }

            if(ptr->next == NULL)
                break;
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }

        //Breaks if no swap occured
        if(check == 0)
            break;
    }

    return head;
}

//Displays the inventory list to the user
struct product* displaylist(struct product *head)
{
    struct product *ptr;

    if(head == NULL)
    {
        printf("\n\r\n\rNothing in stock!\n\r\n\r");
        return head;
    }

    head = sortlist(head);

    ptr = head;

    while(ptr != NULL)
    {
        //Doesn't print out of stock items
        if(ptr->count <= 0)
        {
            ptr = ptr->next;
            continue;
        }
            
        //Clears input buffer
        fflush(stdin);

        printf("\n\r%15s:    ID: %4d%4d%4d%4d    Price/lb: %6.2f    In Stock: %d\n\r", ptr->pname, ptr->pid[0], ptr->pid[1], 
        ptr->pid[2], ptr->pid[3], ptr->priceper, ptr->count);
        ptr = ptr->next;
    }

    printf("\n\r\n\r");
    return head;
}

//Frees the memory allocated for the inventory list
void freelist(struct product *head)
{
    struct product *ptr, *temp;

    ptr = head;

    while(ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}

//Saves the inventory list to a csv file
void savelist(struct product *head)
{
    FILE *fp;
    struct product *ptr;

    ptr = head;

    //Open file pointer to output file
    if((fp = fopen("/sd/inventory.txt", "w")) == NULL)
        perror("Error");

    while(ptr != NULL)
    {
        //Outputs attributes
        fprintf(fp, "%s,%d,%d,%d,%d,%d,%.3f,\n", ptr->pname,
            ptr->pid[0], ptr->pid[1], ptr->pid[2], ptr->pid[3], ptr->count, ptr->priceper);

        ptr = ptr->next;
    }

    fclose(fp);
}

//Loads the inventory list from the csv file 
struct product* loadlist()
{
    FILE *fp;
    char line[512], *token;
    int x, flag = 0;
    struct product *newprod, *head, *prev;
    

    //Opens file pointer to input file
    if((fp = fopen("/sd/inventory.txt", "r")) == NULL)
    {
        printf("\n\r\n\rInventory is empty:\n\r\n\r");
        return NULL;
    }

    
    //Reads in next line of file
    while(fgets(line, 512, fp) != NULL)
    {
        //Breaks when end of file is reached
        if(feof(fp))
            break;

        //Allocates memory for the product
        newprod = (struct product*)malloc(sizeof(struct product));

        //Adds the product to the list in order (flag is 0 for the first product only)
        if(flag == 0)
            head = newprod;
        else
            prev->next = newprod;

        //Moves prev up
        prev = newprod;
        newprod->next = NULL;

        //Breaks csv line into tokens with comma as the delimiter 
        token = strtok(line, ",");

        //Iterates once for each attribute in the product structure
        for(x=0;x<7;x++)
        {
            if(x == 0)
                strcpy(newprod->pname, token);

            else if(x == 1)
                newprod->pid[0] = atoi(token);
                
            else if(x == 2)
                newprod->pid[1] = atoi(token);
                
            else if(x == 3)
                newprod->pid[2] = atoi(token);    
                
            else if(x == 4)
                newprod->pid[3] = atoi(token); 
                
            else if(x == 5)
                newprod->count = atoi(token);
            
            else
                newprod->priceper = atof(token);

            //Goes to next token
            token = strtok(NULL, ",");
        }

        //Sets flag so it's 1 for all iterations except the first
        flag = 1;

    }

    fclose(fp);
    return head;
}

//Finds a product by its name and returns it or NULL if not found
struct product* findbyname(char name[50], struct product *head)
{
    struct product *ptr;
    
    ptr = head;

    while(ptr != NULL)
    {
        if(strcmp(ptr->pname, name) == 0)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;

}

struct product* findbyid(int id[10], struct product *head)
{
    struct product *ptr;
    int x;
    
    ptr = head;

    while(ptr != NULL)
    {
        for(x=0;x<4;x++)
        {
            if(id[x] != ptr->pid[x])
                break;
                
            if(x == 3)
                return ptr;
        }
        

        ptr = ptr->next;
    }

    return NULL;
}

//Checks in an item of given name by incrementing that product's count attribute
struct product* checkin(struct product *head)
{
    struct product *ptr;

    char entry[20];

        printf("\n\r\n\rPlease enter product name:\n\r\n\r");

        fflush(stdin);
        scanf("%20s", &entry);
        fflush(stdin);
        if((ptr = findbyname(entry, head)) == NULL)
            printf("\n\r\n\rNo such product!\n\r\n\r");
        else
            ptr->count++;

        return head;
}

//Checks a product out of inventory, and gives a price 
struct product* checkout(struct product *head, HX711 scale1)
{
    struct product *ptr;
    char entry[20];
    float weight = 3.5, price;
    int x, y;
 

    printf("\n\r\n\rPress:\n\r1:  rfid\n\r2:  manual\n\r\n\r");
    
    scanf("%20s", &entry);

    if(strcmp("1", entry) == 0)
    {
        printf("\n\r\n\rPlease scan rfid:\n\r\n\r");
        
        flag1 = 0;
        flag2 = 0;
    
        //Waits for rfid interrupt
        while(flag2 == 0)
        {
            wait(0.5);
            continue;
        }
        
        if((ptr = findbyid(id, head)) == NULL)
        {
            printf("\n\r\n\rNo such item!\n\r\n\r");
            flag1 = 1;
            return head;
        }

        else if(ptr->count <= 0)
        {
            printf("\n\r\n\rOut of stock!\n\r\n\r");
            flag1 = 1;
            return head;        
        }
        
    }
    
    else if(strcmp("2", entry) == 0)
    {
        printf("\n\r\n\rPlease enter product name:\n\r\n\r");
        fflush(stdin);
        scanf("%20s", &entry);
        fflush(stdin);
    

        if((ptr = findbyname(entry, head)) == NULL)
        {
            printf("\n\r\n\rNo such item!\n\r\n\r");
            return head;
        }

        else if(ptr->count <= 0)
        {
            printf("\n\r\n\rOut of stock!\n\r\n\r");
            return head;
        }
    }
    else
    {
        printf("\n\r\n\rIncorrect entry\n\r\n\r");
        return head;
    }

    
    weight = scale(scale1);
    price = ptr->priceper * weight;
    printf("\n\r\n\rPrice: %f\n\r\n\r", price);
    ptr->count--;   


    flag1 = 1;
    return head;
}

//Temperature sensor rti isr
void timer_temp_hum_isr()
{
    sensor.read();
    Farenheit = sensor.getFahrenheit();
    Humidity = sensor.getHumidity();
    
    if(Farenheit > maxtemp)
    {
        buzzer = 1;
        LED = 0;
    }
    else
    {
       buzzer = 0;
       LED = 1;
    }
}

//Prints the current teperature
void getstatus()
{
    printf("\n\rCurrent Temperature: %.2f F\n\r", Farenheit);
}

//Sets max alowable temperature
void setmax()
{
    printf("\n\r\n\rEnter max temperature:  ");
    scanf("%f", &maxtemp);
    printf("\n\r\n\r");
}

struct product* findrfid(int rfid[4], struct product *head)
{
    FILE *fp;
    char line[512], *token;
    int x, flag = 0, match = 0;
    struct product *newprod, *ptr;
    uint8_t temp;

    //Opens file pointer to input file
    if((fp = fopen("/sd/rfiddata.txt", "r")) == NULL)
        perror("Error");


    //Reads in next line of file
    while(fgets(line, 512, fp) != NULL)
    {
        match = 0;
        
        //Breaks csv line into tokens with comma as the delimiter 
        token = strtok(line, ",");

        for(x=0;x<4;x++)
        {
            if(rfid[x] != atoi(token))
                break;
              
            //Goes to next token
            token = strtok(NULL, ",");

            if(x == 3)
                match = 1;
        }

        if(match == 1)
        {
            
            if((ptr = findbyname(token, head)) != NULL)
            {
                ptr->count++;
                fclose(fp);
                return head;
            }
            
            //Allocates memory for the product
            newprod = (struct product*)malloc(sizeof(struct product));

            //Fills in new product attributes
            strcpy(newprod->pname, token);
            newprod->count = 1;
            
            //Goes to next token
            token = strtok(NULL, ",");
            newprod->priceper = atof(token);
            
            //Fills id
            newprod->pid[0] = rfid[0];
            newprod->pid[1] = rfid[1];
            newprod->pid[2] = rfid[2];
            newprod->pid[3] = rfid[3];

            //Adds to list
            newprod->next = head;
            head = newprod;
            break;
        }

        else
        {
            continue;
        }

    }

    fclose(fp);
    return head;
}