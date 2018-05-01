#include "mbed.h"
#include <string>
#include "parse.h"
#include "sense.h"
#include "TextLCD.h"

TextLCD lcd(A0,A1,A2,A3,A4,A5,TextLCD::LCD16x2);
Serial pc(USBTX, USBRX);
InterruptIn gearUp(PTA4);
InterruptIn gearDown(PTC6);
DigitalIn Nswitch(D7);
Serial blue(PTC15,PTC14);
Ticker display;
Ticker Wifi;
char rx[50];
Serial esp8266(PTC4,PTC3);
//DigitalOut myled(PTB22);
//DigitalOut myled3(PTB21);
info* currInfo = (info*) malloc(sizeof(struct info));
volatile bool flag = false;
long y = 0;
void gUp();
void gDown();
void updateDisplay();
void updateWifi();


void onBluetoothReceived(void) {
    if(y == 1000){
        y = 0;
        while(blue.readable()){
            //myled = !myled;
            //pc.printf("Interrupt!\r\n");
            blue.gets(rx,50);
            //pc.puts(rx);
            //pc.puts("\n");
            if(rx[0] == '[' && strlen(rx) > 24){
                //pc.puts(rx);
            }
            else
               rx[0] = '\0';
        }
    }
    else
        y++;
}

int main() 
{   
    initializeStruct(currInfo);
    Wifi.attach(&updateWifi,5);
    display.attach(&updateDisplay,.5);
    SetGear(currInfo,Nswitch);
    gearUp.rise(&gUp);
    gearDown.rise(&gDown);
    rx[0] = '\0';
    int status;
    currInfo->x = 0;
    //info* currInfo = (info*) malloc(sizeof(struct info));
    blue.attach(&onBluetoothReceived, Serial::RxIrq);
    blue.baud(115200);
    pc.baud(115200);
    esp8266.baud(115200);
    pc.printf("start!");
    // echo back characters and toggle the LED
    while (1) 
    {
        //pc.printf("%f %f %f %d \r\n",currInfo->x,currInfo->y,currInfo->speed,currInfo->gear);
        status = parse(rx,currInfo);
     }
}

void gUp(){
    if(currInfo->gear == 6)
        return;
    if(currInfo->gear == 0){
        currInfo->gear = 2;
        return;
    }
    currInfo->gear++;    
}

void gDown(){
    if(currInfo->gear == 0)
        currInfo->gear++;
    else if(currInfo->gear == 1)
        return;
    else
        currInfo->gear--;    
}

void updateDisplay(){
    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("Angle: %.2f",currInfo->x);
    lcd.locate(0,1);
    lcd.printf("m/s:%.2f G:%d",currInfo->speed,currInfo->gear);
}
void updateWifi(){     //[,WIFI,hr,temp,humidity,x,y,speed,lean,accel,gear,]
       esp8266.printf("[,WIFI,%d,%d,%d,%f,%f,%f,%d,%d,%d,]",currInfo->hr,currInfo->temp,currInfo->humidity,currInfo->x,currInfo->y,currInfo->speed,currInfo->lean,currInfo->accel,currInfo->gear);
       //pc.printf("[,WIFI,%d,%d,%d,%f,%f,%f,%d,%d,%d,]",currInfo->hr,currInfo->temp,currInfo->humidity,currInfo->x,currInfo->y,currInfo->speed,currInfo->lean,currInfo->accel,currInfo->gear);
}
