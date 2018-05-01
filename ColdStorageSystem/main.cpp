#include "mbed.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "product.h"
#include "HX711.h"
#include "SDFileSystem.h"
#include "Dht11.h"
#include "MFRC522.h"
#define SPI_MOSI    D11
#define SPI_MISO    D12
#define SPI_SCLK    D13
#define SPI_CS      D10
#define MF_RESET    D9


SDFileSystem sd(PTE3, PTE1, PTE2, PTE4, "sd"); // MOSI, MISO, SCK, CS
MFRC522   RfChip(SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_CS, MF_RESET);

Ticker ticker;
Ticker rfidtick;

void rfidsense();
struct product *head = NULL;
int id[10] = {0,0,0,0,0,0,0,0,0,0};
int flag1 =1, flag2;

int main()
{
    //Declarations and initializations
    char k[5];
    HX711 scale1(A0,A1);
    ticker.attach(&timer_temp_hum_isr, 2);
    rfidtick.attach(&rfidsense, .25);
    head = loadlist();
    RfChip.PCD_Init();
    

    while(1)
    {
        printf("\n\r1:  Add product to database\n\r2:  Check in product\n\r3:  See inventory\n\r4:  "
            "Check out product\n\r5:  Cooler Status\n\r6:  Set max temperature\n\r7:  Quit\n\r\n\r");
        scanf("%5s", &k);
        
        
        //User choices
        if(strcmp(k, "1") == 0)
            head = addproduct(head);

        else if(strcmp(k, "2") == 0)
            head = checkin(head);

        else if(strcmp(k, "3") == 0)
            head = displaylist(head);

        else if(strcmp(k, "4") == 0)
            head = checkout(head, scale1);
            
        else if(strcmp(k, "5") == 0)
            getstatus();
            
        else if(strcmp(k, "6") == 0)
            setmax();

        else if(strcmp(k, "7") == 0)
            break;

        //Clears input buffer
        fflush(stdin);
    }
    
    if(head == NULL)
        return 0;


    savelist(head);

    freelist(head);
    return 0;
}

void rfidsense()
{
    

     // Look for new cards
     if ( ! RfChip.PICC_IsNewCardPresent())
     {
       return;
     }

     // Select one of the cards
     if ( ! RfChip.PICC_ReadCardSerial())
     {
       return;
     }

           
    for (uint8_t i = 0; i < RfChip.uid.size; i++)
    {
        id[i] = RfChip.uid.uidByte[i]; 
        printf(" %d ", RfChip.uid.uidByte[i]);
    }
            
    //Add corresponding product to list based on rfid
    if(flag1 == 1)
        head = findrfid(id, head);  
          
    flag2 = 1;
    
    printf("\n\r\n\rRFID Scanned!!\n\r\n\r");
}

