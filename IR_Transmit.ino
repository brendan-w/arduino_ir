/*
 * Written by Brendan Whitfield
 *
 */


#include "Codes.h"


//digital pin layout
#define OUTPUT_IR_A 4 //12 - 8
#define OUTPUT_IR_B 5 //13 - 8
#define OUTPUT_DISPLAY 2 //occupies pins [x, x+9]

//buttons!
#define INPUT_BANK A2
#define INPUT_UP A1
#define INPUT_DOWN A0
#define CODE_DELAY 6

//vars
int bankNum = 0;
int lastBank = 0;

int currentCode = 0;

void setup()
{
  //Serial.begin(9600);
  
  //make all the pins outputs
  for(int i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  //wake-up flash
  for(int i = 19; i >= 0; i--)
  {
    setDisplay(i % 10);
    delay(25);
  }
}

void loop()
{
  //buttons take so long to analogRead(), no need to debounce
  int currentBank = readButton(INPUT_BANK);
  int currentUp = readButton(INPUT_UP);
  int currentDown = readButton(INPUT_DOWN);
  
  //switch bank on button down
  if(currentBank && (!lastBank))
  {
    bankNum++;
    bankNum = bankNum % 10;
    setDisplay(bankNum);
  }
  lastBank = currentBank;
  
  
  if(currentUp && !currentDown)
  {
    
    switch(bankNum)
    {
      case 0: //TV power on
        currentCode = currentCode % POWER_ON_TOTAL;
        sendCode(POWER_ON + currentCode);
        break;
      case 1: //TV volume up
        currentCode = currentCode % VOLUME_UP_TOTAL;
        sendCode(VOLUME_UP + currentCode);
        break;
      case 2:
        currentCode = currentCode % CHANNEL_UP_TOTAL;
        sendCode(CHANNEL_UP + currentCode);
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
    }
    currentCode++;
    delay(CODE_DELAY);
  }
  else if(currentDown && !currentUp)
  {
    switch(bankNum)
    {
      case 0: //TV power on
        currentCode = currentCode % POWER_OFF_TOTAL;
        sendCode(POWER_OFF + currentCode);
        break;
      case 1: //TV volume up
        currentCode = currentCode % VOLUME_DOWN_TOTAL;
        sendCode(VOLUME_DOWN + currentCode);
        break;
      case 2:
        currentCode = currentCode % CHANNEL_DOWN_TOTAL;
        sendCode(CHANNEL_DOWN + currentCode);
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
    }
    currentCode++;
    delay(CODE_DELAY);
  }
  else
  {
    currentCode = 0;
  }
  
  //sendCode(POWER_ON + 3);
}


void sendCode(const IRCode* code)
{
  BurstPair* pairs = getCode(code);
  int length = getLength(code);
  int carrier = getCarrier(code);
  
  for(int i = 0; i < length; i++)
  {
    sendBurst(pairs[i], carrier);
  }
  
  delete[] pairs;
}

void sendBurst(BurstPair pair, uint8_t carrier)
{
  //ON
  for(int i = 0; i < pair.on; i++)
  {
    //bitWrite(PORTB, OUTPUT_IR_A, 1);
    PORTB |= B00110000; //HIGH
    delayMicroseconds(carrier);
    //bitWrite(PORTB, OUTPUT_IR_A, 0);
    PORTB &= B11001111; //LOW
    delayMicroseconds(carrier);
  }
  
  //OFF
  //bitWrite(PORTB, OUTPUT_IR_A, 0);
  PORTB &= B11001111; //LOW
  delayMicroseconds(carrier * 2 * pair.off);
}


void setDisplay(int n) //0-9
{
  //turn everything off FIRST (one resistor for many LEDS)
  for(int i = OUTPUT_DISPLAY; i < OUTPUT_DISPLAY + 10; i++)
  {
    digitalWrite(i, LOW);
  }
  
  if((n >= 0) && (n <= 9))
  {
    digitalWrite(OUTPUT_DISPLAY + n, HIGH);
  }
}

int readButton(int pin)
{
  int val = analogRead(pin);
  if(val >= 512)
  {
    return 1;
  }
  return 0;
}
