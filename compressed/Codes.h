
#include <avr/pgmspace.h>
#include <stdint.h>

#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)));

struct Nibbles
{
  //1 byte, 2 values (codes will be programmed pair-wise, but it's really just a sequential string)
  unsigned int hi:4;
  unsigned int lo:4;
  //slower to execute, but saves sooooo much space
};

union NibbleUnion
{
  Nibbles n;
  uint8_t i;
};

struct BurstPair
{
  //measured in cycles of the carrier
  uint8_t on;
  uint8_t off;
};

union BurstUnion
{
  BurstPair b;
  uint16_t i;
};

struct IRCode
{
  const BurstPair* dict;       //dictionary of burst pairs
  const Nibbles*   code;       //code in terms of burst pairs in dict;
  const uint8_t    codeLength; //number of nibbles in code[]
  const uint8_t    carrier;    //microseconds of on time (wavelength / 2)
};

//accessor methods (retrieves and decompresses from flash)
BurstPair* getCode(const IRCode* code);
int getCarrier(const IRCode* desired);
int getLength(const IRCode* desired);

extern const IRCode POWER_ON[] PROGMEM;
