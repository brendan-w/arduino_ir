/*
 * Written by: Brendan Whitfield, 2013
 */


#include "Codes.h"


//digital pin layout
#define OUTPUT_IR_A 4 //12 - 8
#define OUTPUT_IR_B 5 //13 - 8
#define OUTPUT_DISPLAY 2 //occupies pins [x, x+9]

//analog pin layout




void setup()
{
  //make all the pins outputs
  for(int i = 2; i < 14; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  //pinMode(OUTPUT_IR, OUTPUT);
  
  //wake-up flash
  for(int i = 0; i < 20; i++)
  {
    setDisplay(i % 10);
    delay(24);
  }
  
  setDisplay(-1); //turn the display off
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
    bitWrite(PORTB, OUTPUT_IR_A, 1);
    delayMicroseconds(carrier);
    bitWrite(PORTB, OUTPUT_IR_A, 0);
    delayMicroseconds(carrier);
  }
  
  //OFF
  bitWrite(PORTB, OUTPUT_IR_A, 0);
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
