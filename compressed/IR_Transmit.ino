
#include "Codes.h"

#define OUTPIN 4


void setup()
{
  pinMode(OUTPIN, OUTPUT);
}

void loop()
{
  sendCode(POWER_ON);
  delay(200);
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
  
  //sendBurst(pairs, carrier);
  delete[] pairs;
}


/*
void sendCode(IRCode code)
{
  //decompress codes
  BurstPair pairs[code.codeLength];
  
  for(int i = 0; i < code.codeLength; i++)
  {
    uint8_t dictValue;
    if(i % 2) { dictValue = code.code[(int)(i / 2)].lo; } //use LOW
    else      { dictValue = code.code[(int)(i / 2)].hi; } //use HI
    pairs[i] = code.dict[dictValue];
  }
  
  //transmit code
  for(int i = 0; i < code.codeLength; i++)
  {
    sendBurst(pairs[i], code.carrier);
  }
}
*/

void sendBurst(BurstPair pair, uint8_t carrier)
{
  //ON
  for(int i = 0; i < pair.on; i++)
  {
    bitWrite(PORTD, OUTPIN, 1);
    delayMicroseconds(carrier);
    bitWrite(PORTD, OUTPIN, 0);
    delayMicroseconds(carrier);
  }
  
  //OFF
  bitWrite(PORTD, OUTPIN, 0);
  delayMicroseconds(carrier * 2 * pair.off);
}

