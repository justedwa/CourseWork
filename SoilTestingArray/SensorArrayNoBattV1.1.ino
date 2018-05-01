/* 
 ** Using SPI  
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)
*/


#include <SD.h>

extern volatile unsigned long timer0_millis;
unsigned long timerRst = 0;
const int sense[4] = {0,1,2,3};
const int errPin = 2;
const int Heartbeat = 6;
const int ledPin = 5;
const int startButton = 3;
const int chipSelect = 4;
volatile bool interrupt = false;

void setup() {
  // put your setup code here, to run once:
  asm( "cli \n");
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //declares LED output pinmodes
  pinMode(Heartbeat, OUTPUT);
  pinMode(errPin, OUTPUT);
  pinMode(startButton, INPUT);
   if (!SD.begin(chipSelect)){ //starts SD session with pin 4 if the SD card is unabled to be access do error handling
    Serial.println("Card does not exist"); //error handling
    delay(10);
    digitalWrite(errPin, HIGH);
    while(!SD.begin(chipSelect))
      digitalWrite(ledPin, !(digitalRead(ledPin)));
  }
  digitalWrite(ledPin,LOW);
  digitalWrite(errPin, LOW);
  attachInterrupt(digitalPinToInterrupt(startButton), EarlyExit, HIGH);
  Serial.println("Card Initialized"); //setup complete
  delay(100);
}

void setMilli(unsigned long currTime){
  uint8_t oldSREG = SREG;
  cli();
  timer0_millis = currTime;
  SREG = oldSREG;
  sei();
}

void EarlyExit(){
  interrupt == true;
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long millisCnt = 0;
  String dataString = "";
  int sensorRead;
  int x;
  File dataFile = SD.open("datalog.csv",FILE_WRITE);
  dataFile.println("Sensor 1, Sensor 2, Sensor 3, Sensor 4, Timestamp(ms)");
  digitalWrite(ledPin, HIGH);
  while(1)
  {
    if(digitalRead(startButton) == HIGH)
    {
      digitalWrite(ledPin, LOW);
      delay(10);
      asm ("sei \n");
      break;
    }
    else
      continue;
  }
  setMilli(timerRst);
  while(millis() < 3600000)
  {
    if(interrupt == true){
      delay(10);
      asm("cli \n");
      break;
    }
    for(x=0;x<4;x++)
    {
      sensorRead = analogRead(sense[x]);
      dataString += String(sensorRead);
      dataString += ",";
    }
    millisCnt = millis();
    dataString += String(millisCnt);
    if (dataFile)
    {
      dataFile.println(dataString);
      Serial.println(dataString);
    }
    else
    {
      Serial.println("Error opening datalog.csv");
      delay(10);
      digitalWrite(errPin, HIGH);
      exit(0);
    }
    dataString = "";
    digitalWrite(Heartbeat,HIGH);
    delay(495);
    digitalWrite(Heartbeat,LOW);
    delay(495);
  }
  Serial.println("Data Collection Complete");
  digitalWrite(ledPin,HIGH);
  dataFile.close();
  exit(0);
}
