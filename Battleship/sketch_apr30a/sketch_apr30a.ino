

const int rst = 12;
const int y1 = 11;
const int y2 = 10;
const int x1 = 9;
const int x2 = 8;
const int hm = 7;
const int speak = 6;
const int outstat = 5;
const int instat = 4;
const int turnled = 3;
const int hmenable = 2;
const int testpin = 13;
void setup() 
{
  // put your setup code here, to run once:
pinMode(rst, INPUT);
pinMode(y1, INPUT);
pinMode(y2, INPUT);
pinMode(x1, INPUT);
pinMode(x2, INPUT);
pinMode(hm, OUTPUT);
pinMode(speak, OUTPUT);
pinMode(outstat, OUTPUT);
pinMode(instat, INPUT);
pinMode(turnled, OUTPUT);
pinMode(hmenable, OUTPUT);
pinMode(testpin, OUTPUT);
}

void loop() 
{
  //Declarations
  boolean y1val, y2val, x1val, x2val;
  int i, j, x, y, a, b, c, d;
  int yc, xc;
  int phits = 0;
  int aihits = 0;
  int pfield[4][4];
  int aifield[4][4];
  int guessx, guessy;
  int wincheck;
  y = 0;
  x = 0;
  //Sets the win check, and player hits to zero at the beginning of each game
  wincheck = 0;
  phits = 0;
  aihits = 0;
  digitalWrite(turnled,LOW);
  //Prests hit/miss enable to off
  digitalWrite(hmenable, LOW);
  delay(5000);
  //Seed the random number generation
  randomSeed(analogRead(0));
  
  //Initializing elements to zero
  for(i=0;i<=3;i++)
  {
  for(j=0;j<=3;j++)
  {
    pfield[i][j]=0;
    aifield[i][j]=0;
  }
  }
  
  //Generating ships
 while(true)
  {
  //This will generate four ships in random spots,
  //making sure not to put two in the same spot 
  while(x<4)
  {
    
    a = random(0,3);
    b = random(0,3);
    
    if(pfield[a][b] != 1)
    {
      pfield[a][b] = 1;
      x++;
    delay(1000);
    digitalWrite(testpin,HIGH);
    delay(100);
    digitalWrite(testpin,LOW);
    }
  }
  
  while(y<4)
  {
    digitalWrite(testpin,HIGH);
    delay(100);
    digitalWrite(testpin,LOW);
    c = random(0,3);
    d = random(0,3);
    
    if(aifield[c][d] != 1)
    {
      aifield[c][d] = 1;
      y++;
    delay(1000);
    digitalWrite(testpin,HIGH);
    delay(100);
    digitalWrite(testpin,LOW);
    }
  }
  break;
  }
 ///Tells fpga that the field is generated 
digitalWrite(outstat, HIGH);
digitalWrite(outstat, LOW);
 //Loop for the turns 
  while(true)
  {
    digitalWrite(turnled, HIGH);
    
    if(digitalRead(instat) == HIGH)
    {
      digitalWrite(turnled, LOW);
      
      
      y1val = digitalRead(y1);
      y2val = digitalRead(y2);
      x1val = digitalRead(x1);
      x2val = digitalRead(x2);
      
    
      //converts y coordinate 
      if(y1val==LOW&&y2val==LOW)
      {
        yc = 0;
      }
      else if(y1val==LOW&&y2val==HIGH)
      {
        yc = 1;
      }
      else if(y1val==HIGH&&y2val==LOW)
      {
        yc = 2;
      }
      else 
      {
        yc = 3;
      }
      
      //converts x coordinate 
      if(x1val==LOW&&x2val==LOW)
      {
        xc = 0;
      }
      else if(x1val==LOW&&x2val==HIGH)
      {
        xc = 1;
      }
      else if(x1val==HIGH&&x2val==LOW)
      {
        xc = 2;
      }
      else 
      {
        xc = 3;
      }
      
      /*This will check the player guess against the ai field, 
      to dtermine whether it was a hit or miss*/
     
      //For hit
      if(aifield[yc][xc]==1)
      {
        //"Sinks" ship and adds to sink count
        aifield[yc][xc] = 0;
        phits++;
        
        //Turn hit/miss enable on, and displays hit
        digitalWrite(hm, HIGH);
        digitalWrite(hmenable, HIGH);
        delay(3000);
        digitalWrite(hm,LOW);
        digitalWrite(hmenable,LOW);
        delay(3000);
      }
      
      //For miss
      else
      {
        //Turns hit/miss enable on, and displays miss
        digitalWrite(hm, LOW);
        digitalWrite(hmenable, HIGH);
        delay(3000);
        digitalWrite(hmenable,LOW);
        delay(3000);
      }
    
      
      //Generate the ai's guess 
      guessx = random(0,3);
      guessy = random(0,3);
      
      //For hit
      if(pfield[guessy][guessx]==1)
      {
        //"Sinks" ship and adds to sink count
        pfield[guessy][guessx] = 0;
        aihits++;
        
        //Turn hit/miss enable on, and displays hit
        digitalWrite(hm, HIGH);
        digitalWrite(hmenable, HIGH);
        delay(3000);
        digitalWrite(hm, LOW);
        digitalWrite(hmenable,LOW);
        delay(3000);
      }
      
      else
      {
        //Turns hit/miss enable on, and displays miss
        digitalWrite(hm, LOW);
        digitalWrite(hmenable, HIGH);
        delay(3000);
        digitalWrite(hmenable,LOW);
        delay(3000);
      }
    
      
      if(phits==4)
      {
        digitalWrite(speak, HIGH);
        delay(3000);
        digitalWrite(speak, LOW);
        
        digitalWrite(outstat, HIGH);
        digitalWrite(outstat, LOW);
        
        while(true)
        {
          if(digitalRead(rst) == HIGH)
          { 
          //Shows that someone won
            wincheck = 1;
            break;
          }
        }
        
          
        
        
        
      }
      
      else if(aihits == 4)
      {
        digitalWrite(speak, HIGH);
        delay(500);
        digitalWrite(speak, LOW);
        delay(500);
        digitalWrite(speak, HIGH);
        delay(500);
        digitalWrite(speak, LOW);
        
        digitalWrite(outstat, HIGH);
        digitalWrite(outstat, LOW);
        
        while(true)
        {
          if(digitalRead(rst) == HIGH)
          { 
          //Shows that someone won
            wincheck = 1;
            break;
          }
        }
      }
      
    }
    
    if(wincheck == 1)
    {
      break;
    }
    digitalWrite(outstat, HIGH);
    digitalWrite(outstat, LOW);
    
  }


 


}
