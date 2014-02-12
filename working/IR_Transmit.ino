#include <stdint.h>
#include "Codes.cpp"




#define OUTPIN 4


void setup()
{
  pinMode(OUTPIN, OUTPUT);
}

void loop()
{
  sendCode(POWER_ON[0]);
  delay(200);
}


void sendCode(IRCode code)
{
  //decompress codes
  BurstPair pairs[code.codeLength];
  
  for(int i = 0; i < code.codeLength; i++)
  {
    /*
    uint8_t dictValue;
    if(i % 2) { dictValue = code.code[(int)(i / 2)].hi; } //use HI
    else      { dictValue = code.code[(int)(i / 2)].lo; } //use LOW
    pairs[i] = code.dict[dictValue];
    */
    pairs[i] = code.dict[code.code[i]];
  }
  
  //transmit code
  for(int i = 0; i < code.codeLength; i++)
  {
    sendBurst(pairs[i], code.carrier);
  }
}


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

