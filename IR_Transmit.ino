/*
 * Written by Brendan Whitfield
 *
 */


#include "Codes.h"


#define OUTPUT_DISPLAY 2 //occupies pins [x, x+9]
#define INPUT_BANK A2
#define INPUT_UP A1
#define INPUT_DOWN A0
#define CODE_DELAY 6

//running vars
int bankNum = 0; //current code bank (bar graph indicator)
int lastBank = 0; //old button value (to detect DOWN press)
int currentCode = 0; //current code to send (incremented every loop())

void setup()
{
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
  //get button values
  //buttons take so long to analogRead(), no need to debounce
  int currentBank = readButton(INPUT_BANK);
  int currentUp = readButton(INPUT_UP);
  int currentDown = readButton(INPUT_DOWN);
  
  //switch bank when button is DOWN
  if(currentBank && (!lastBank))
  {
    bankNum++;
    bankNum = bankNum % 10; //wrap
    setDisplay(bankNum);
  }
  lastBank = currentBank;
  
  //perform action based on button press states
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
  }
  else
  {
    currentCode = 0;
    setDisplay(bankNum);
  }
  
  if(currentDown != currentUp) //XOR (one of the buttons is pressed)
  {
    setDisplay(currentCode % 10);
    currentCode++;
    delay(CODE_DELAY);
  }
  
  //sendCode(POWER_ON + 3);
}


void setDisplay(int n) //0-9
{
  PORTD &= B00000011; //LOW
  PORTB &= B11110000; //LOW
  
  //turn on the corresponding pin, if its in the correct range
  if((n >= 0) && (n <= 9))
  {
    digitalWrite(OUTPUT_DISPLAY + n, HIGH);
  }
}

int readButton(int pin)
{
  int val = analogRead(pin);
  if(val >= 512) { return 1; }
  return 0;
}


//function for sending an IR code. Provide pointer to code.
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
  //ON portion
  for(int i = 0; i < pair.on; i++)
  {
    PORTB |= B00110000; //HIGH
    delayMicroseconds(carrier);
    PORTB &= B11001111; //LOW
    delayMicroseconds(carrier);
  }
  
  //OFF portion
  PORTB &= B11001111; //LOW
  delayMicroseconds(carrier * 2 * pair.off);
}

