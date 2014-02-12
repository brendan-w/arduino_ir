
#include "Codes.h"

/*
 * Code accessors. Retrieves and decrompresses a code from the flash memory.
 * Accepts pointer to IRCode struct from codeSet array.
 * Returns array of burst pairs, ready for sending
 */

BurstPair* getCode(const IRCode* desired)
{
  //get struct information
  PGM_P current = (PGM_P)desired;
  PGM_P dict =    (PGM_P)pgm_read_word(current += 2);
  PGM_P code =    (PGM_P)pgm_read_word(current += 2);
  uint8_t codeLength = (uint8_t) getLength(desired);
  
  //allocate a place for the finished product to go
  BurstPair* pairs = new BurstPair[codeLength];
  
  for(int i = 0; i < codeLength; i++)
  {
    //get data
    NibbleUnion n;
    n.i = pgm_read_byte(code + ((int)(i / 2)));
    
    uint8_t dictValue;
    if(i % 2) { dictValue = n.n.lo; } //use LOW
    else      { dictValue = n.n.hi; } //use HI
    
    BurstUnion b;
    b.i = pgm_read_word(dict + (sizeof(BurstPair)*dictValue));
    
    //load data
    pairs[i].on = b.b.on;
    pairs[i].off = b.b.off;
  }
  
  return pairs;
}

int getLength(const IRCode* desired)
{
  return (int)(uint8_t)pgm_read_byte(((PGM_P)desired) + 4);
}

int getCarrier(const IRCode* desired)
{
  return (int)(uint8_t)pgm_read_byte(((PGM_P)desired) + 5);
}

/*
 * Raw dictionary and code data. Linked to functions by pointers (shared dictionaries save space)
 * Dictionaries store the different burst pairs.
 * Codes store the a list of dictionary indices in the order of transmission.
 * Full list of burst pairs is compiled prior to transmission (slower, but saves space)
 */

const BurstPair dict_panasonic[] PROGMEM =          {{16, 16}, {16, 48}, {128, 63}, {16, 255}};
const Nibbles   code_panasonic_POWER_ON[] PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 1}, {1, 1}, {1, 0}, {1, 3}};



/*
 * Codes organized by function, then sorted by manufacturers (major to minor)
 */

//POWER ON
const IRCode POWER_ON[] PROGMEM = {
  {dict_panasonic, code_panasonic_POWER_ON, 50, 14}
};
const uint8_t POWER_ON_TOTAL = NUM_ELEM(POWER_ON);

//POWER OFF
//MUTE
//VOLUME UP
//VOLUME DOWN
//CHANNEL UP
//CHANNEL DOWN
