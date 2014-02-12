/*
 * Written by: Brendan Whitfield, 2013
 */


#include "Codes.h"


//digital pin layout
#define OUTPUT_IR 4 //0
#define INPUT_IR 1
#define OUTPUT_DISPLAY 2 //occupies pins [x, x+9]
#define OUTPUT_CAP_SENSE 13

//analog pin layout
#define INPUT_BUTTON_UP 0
#define INPUT_BUTTON_DOWN 1
#define INPUT_BODY 2
#define INPUT_RING_UP 3
#define INPUT_RING_DOWN 4



void setup()
{
  pinMode(OUTPUT_IR, OUTPUT);
}

void loop()
{
  sendCode(POWER_ON + 3);
  delay(1000);
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
    bitWrite(PORTD, OUTPUT_IR, 1);
    delayMicroseconds(carrier);
    bitWrite(PORTD, OUTPUT_IR, 0);
    delayMicroseconds(carrier);
  }
  
  //OFF
  bitWrite(PORTD, OUTPUT_IR, 0);
  delayMicroseconds(carrier * 2 * pair.off);
}

