/*
 * Written by Brendan Whitfield
 *
 */


#include <avr/pgmspace.h>
#include <stdint.h>


#define NUM_ELEM(x) (sizeof (x) / sizeof (*(x)));


struct BurstPair
{
  //measured in cycles of the carrier
  uint16_t on;
  uint16_t off;
};

union BurstUnion
{
  BurstPair b;
  uint32_t i;
};


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

//code tables

//TVs
extern const IRCode POWER_ON[] PROGMEM;
extern const uint8_t POWER_ON_TOTAL;
extern const IRCode POWER_OFF[] PROGMEM;
extern const uint8_t POWER_OFF_TOTAL;
extern const IRCode MUTE[] PROGMEM;
extern const uint8_t MUTE_TOTAL;
extern const IRCode VOLUME_UP[] PROGMEM;
extern const uint8_t VOLUME_UP_TOTAL;
extern const IRCode VOLUME_DOWN[] PROGMEM;
extern const uint8_t VOLUME_DOWN_TOTAL;
extern const IRCode CHANNEL_UP[] PROGMEM;
extern const uint8_t CHANNEL_UP_TOTAL;
extern const IRCode CHANNEL_DOWN[] PROGMEM;
extern const uint8_t CHANNEL_DOWN_TOTAL;

//projectors
extern const IRCode PROJ_POWER_OFF[] PROGMEM;
extern const uint8_t PROJ_POWER_OFF_TOTAL;
extern const IRCode PROJ_POWER_ON[] PROGMEM;
extern const uint8_t PROJ_POWER_ON_TOTAL;
extern const IRCode PROJ_VOLUME_UP[] PROGMEM;
extern const uint8_t PROJ_VOLUME_UP_TOTAL;
extern const IRCode PROJ_VOLUME_DOWN[] PROGMEM;
extern const uint8_t PROJ_VOLUME_DOWN_TOTAL;
