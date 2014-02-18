/*
 * Written by Brendan Whitfield
 *
 * Contains all of the codes, and code accessors/decompressors needed to achieve the desired function
 * Use by calling getCode() with a pointer to the desired code.
 * Codes are stored in tables according to their function.
 * Codes are organized in rough order of manufacturer prevalence.
 */



#include "Codes.h"



/*
 * Code accessors. Retrieves and decompresses a code from the flash memory.
 * Accepts pointer to IRCode struct from codeSet array.
 * Returns array of burst pairs, ready for sending.
 * DON'T FORGET to delete[] the memory
 */

BurstPair* getCode(const IRCode* desired)
{
  //get struct information
  PGM_P current = (PGM_P)desired;
  BurstPair* dict = (BurstPair*)pgm_read_word(current);
  current += sizeof(BurstPair*);
  Nibbles* code = (Nibbles*)pgm_read_word(current);
  uint8_t codeLength = (uint8_t) getLength(desired);
  
  //allocate a place for the finished product to go
  BurstPair* pairs = new BurstPair[codeLength];
  
  //decompress and build burst pair array
  for(int i = 0; i < codeLength; i++)
  {
    NibbleUnion n;
    BurstUnion b;
    n.i = pgm_read_byte(code + ((int)(i / 2)));
    if(i % 2) { b.i = pgm_read_dword(dict + n.n.lo); } //use LOW
    else      { b.i = pgm_read_dword(dict + n.n.hi); } //use HI
    pairs[i] = b.b;
  }
  
  return pairs;
}

int getLength(const IRCode* desired)
{
  return (int)(uint8_t)pgm_read_byte(((PGM_P)desired) + sizeof(BurstPair*)
                                                      + sizeof(Nibbles*));
}

int getCarrier(const IRCode* desired)
{
  return (int)(uint8_t)pgm_read_byte(((PGM_P)desired) + sizeof(BurstPair*)
                                                      + sizeof(Nibbles*)
                                                      + 1);
}



/*
 * Raw dictionary and code data. Linked to functions by pointers (shared dictionaries save space)
 * Dictionaries store the different burst pairs.
 * Codes store the a list of dictionary indices in the order of transmission.
 * Indices for the codes are stored in nibbles to save space (hence the grouping)
 * Full list of burst pairs is compiled prior to transmission (slower, but saves space)
 */

//TVs

const BurstPair dict_samsung_tv[] PROGMEM = {{172, 171}, {21, 65}, {21, 22}};
const Nibbles code_samsung_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {2, 2}, {1, 1}, {2, 2}, {1, 2}, {1, 1}, {2, 2}, {1, 1}, {2, 2}};
const Nibbles code_samsung_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {2, 2}, {1, 1}, {2, 2}};
const Nibbles code_samsung_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 2}};
const Nibbles code_samsung_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {1, 2}};
const Nibbles code_samsung_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 2}, {1, 2}, {2, 2}, {2, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 2}};
const Nibbles code_samsung_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 2}, {2, 1}, {2, 2}, {2, 1}, {2, 1}, {1, 2}, {1, 1}, {1, 2}};
const Nibbles code_samsung_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 1}, {2, 2}, {2, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 2}};

const BurstPair dict_lge_tv[] PROGMEM = {{343, 171}, {22, 21}, {22, 63}};
const Nibbles code_lge_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 1}, {2, 2}, {2, 1}, {1, 1}};
const Nibbles code_lge_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 2}, {2, 1}, {1, 1}};
const Nibbles code_lge_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 1}, {2, 2}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_lge_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_lge_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_lge_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_lge_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 1}};

const BurstPair dict_sony_tv[] PROGMEM = {{96, 24}, {24, 24}, {48, 24}};
const Nibbles code_sony_tv_POWER_ON[]     PROGMEM = {{0, 1}, {2, 2}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_POWER_OFF[]    PROGMEM = {{0, 2}, {2, 2}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {2, 1}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_VOLUME_DOWN[]  PROGMEM = {{0, 2}, {2, 1}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 1}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 0}};
const Nibbles code_sony_tv_CHANNEL_DOWN[] PROGMEM = {{0, 2}, {1, 1}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {1, 0}};

const BurstPair dict_panasonic_tv[] PROGMEM = {{16, 16}, {16, 48}, {128, 64}};
const Nibbles code_panasonic_tv_POWER_ON[]     PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 1}, {1, 1}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_POWER_OFF[]    PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {1, 1}, {1, 1}, {1, 0}, {0, 1}, {1, 1}, {1, 1}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_MUTE[]         PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 1}, {1, 0}, {0, 0}, {1, 0}, {0, 1}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_VOLUME_UP[]    PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_VOLUME_DOWN[]  PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 0}, {0, 0}, {1, 0}, {0, 1}, {0, 0}, {0, 0}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_CHANNEL_UP[]   PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 1}, {1, 0}, {0, 0}, {0, 1}, {0, 1}, {1, 0}, {1, 0}};
const Nibbles code_panasonic_tv_CHANNEL_DOWN[] PROGMEM = {{2, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 1}, {0, 1}, {0, 1}, {1, 0}, {0, 1}, {0, 1}, {0, 1}, {1, 0}, {1, 0}};

const BurstPair dict_sharp_tv[] PROGMEM = {{10, 72}, {10, 29}};
const Nibbles code_sharp_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 1}, {0, 0}, {0, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 1}, {1, 0}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 1}, {1, 0}, {1, 1}, {1, 0}, {1, 1}, {1, 0}, {1, 1}};
const Nibbles code_sharp_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 1}, {1, 0}, {1, 1}};

const BurstPair dict_philips_tv[] PROGMEM = {{32, 32}, {64, 32}, {32, 64}, {64, 64}};
const Nibbles code_philips_tv_POWER_ON[]     PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {2, 0}, {0, 0}, {0, 0}, {0, 0}};
const Nibbles code_philips_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {2, 0}, {0, 0}, {3, 0}};
const Nibbles code_philips_tv_MUTE[]         PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {0, 0}, {2, 0}, {3, 0}};
const Nibbles code_philips_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {0, 2}, {1, 0}, {0, 0}};
const Nibbles code_philips_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {0, 2}, {1, 0}, {2, 0}};
const Nibbles code_philips_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {2, 1}, {0, 0}, {0, 0}};
const Nibbles code_philips_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {0, 0}, {0, 0}, {2, 1}, {0, 0}, {2, 0}};

const BurstPair dict_vizio_tv[] PROGMEM = {{343, 172}, {21, 22}, {21, 65}};
const Nibbles code_vizio_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {2, 1}, {2, 1}, {2, 1}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {2, 1}};
const Nibbles code_vizio_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {2, 1}, {2, 2}, {1, 2}, {2, 1}};
const Nibbles code_vizio_tv_MUTE_ON[]      PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {2, 1}, {1, 2}, {2, 2}, {2, 2}, {1, 2}, {2, 1}};
const Nibbles code_vizio_tv_MUTE_OFF[]     PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {2, 1}, {1, 1}, {2, 2}, {2, 2}, {1, 2}, {2, 1}};
const Nibbles code_vizio_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_vizio_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_vizio_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 1}};
const Nibbles code_vizio_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {2, 1}};

const BurstPair dict_pioneer_tv[] PROGMEM = {{360, 180}, {22, 22}, {22, 67}};
const Nibbles code_pioneer_tv_POWER_ON[]     PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_pioneer_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {2, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_pioneer_tv_MUTE[]         PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 1}, {2, 1}, {1, 2}, {1, 1}, {2, 2}, {1, 2}, {2, 1}, {2, 1}};
const Nibbles code_pioneer_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 2}, {1, 2}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_pioneer_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_pioneer_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 1}, {2, 2}, {2, 1}};
const Nibbles code_pioneer_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 2}, {2, 1}, {2, 2}, {2, 1}};

const BurstPair dict_mitsubishi_tv[] PROGMEM = {{10, 68}, {10, 29}};
const Nibbles code_mitsubishi_tv_POWER_ON[]     PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 1}, {1, 1}, {0, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_POWER_OFF[]    PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 1}, {0, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_MUTE[]         PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 1}, {0, 0}, {1, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_VOLUME_UP[]    PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 1}, {1, 0}, {1, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_VOLUME_DOWN[]  PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 0}, {1, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_CHANNEL_UP[]   PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 0}};
const Nibbles code_mitsubishi_tv_CHANNEL_DOWN[] PROGMEM = {{0, 0}, {0, 1}, {1, 1}, {0, 1}, {1, 0}, {1, 1}, {0, 1}, {1, 1}, {1, 0}};

const BurstPair dict_fujitsu_tv[] PROGMEM = {{122, 61}, {15, 15}, {15, 46}};
const Nibbles code_fujitsu_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 1}, {2, 1}, {1, 2}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 2}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 2}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 1}};
const Nibbles code_fujitsu_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 2}, {1, 2}, {2, 1}, {1, 1}, {2, 1}, {1, 2}, {2, 1}, {1, 1}, {1, 1}};

const BurstPair dict_toshiba_tv[] PROGMEM = {{343, 172}, {21, 22}, {21, 65}};
const Nibbles code_toshiba_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 1}};
const Nibbles code_toshiba_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}, {2, 2}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {2, 1}};
const Nibbles code_toshiba_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 1}, {2, 2}, {2, 1}};
const Nibbles code_toshiba_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 1}, {2, 2}, {1, 1}, {1, 2}, {1, 2}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_toshiba_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_toshiba_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_toshiba_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 1}};

const BurstPair dict_sanyo_tv[] PROGMEM = {{343, 172}, {21, 22}, {21, 65}};
const Nibbles code_sanyo_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {2, 1}, {1, 2}, {1, 1}, {1, 2}, {1, 2}, {2, 1}, {2, 2}, {2, 1}};
const Nibbles code_sanyo_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {1, 2}, {2, 2}, {1, 2}, {1, 1}, {2, 1}, {1, 1}, {2, 1}};
const Nibbles code_sanyo_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {1, 1}, {2, 2}, {1, 1}, {1, 2}, {2, 2}, {1, 1}, {2, 2}, {2, 1}};
const Nibbles code_sanyo_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {2, 2}, {2, 1}, {1, 1}, {1, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_sanyo_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 2}, {2, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_sanyo_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 2}, {1, 2}, {1, 2}, {2, 2}, {2, 1}};
const Nibbles code_sanyo_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 1}, {2, 2}, {2, 1}, {1, 2}, {2, 2}, {1, 1}, {1, 2}, {2, 2}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {1, 2}, {1, 2}, {2, 2}, {2, 1}};

const BurstPair dict_jvc_tv[] PROGMEM = {{321, 160}, {20, 60}, {20, 20}};
const Nibbles code_jvc_tv_POWER_ON[]     PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_POWER_OFF[]    PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 2}, {1, 2}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_MUTE[]         PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 2}, {2, 1}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_VOLUME_UP[]    PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 2}, {1, 1}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_VOLUME_DOWN[]  PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 1}, {1, 1}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_CHANNEL_UP[]   PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 1}, {2, 2}, {1, 1}, {2, 2}, {2, 2}};
const Nibbles code_jvc_tv_CHANNEL_DOWN[] PROGMEM = {{0, 1}, {1, 2}, {2, 1}, {2, 1}, {2, 2}, {2, 2}, {1, 1}, {2, 2}, {2, 2}};

const BurstPair dict_rca_tv[] PROGMEM = {{1152, 217}, {29, 55}, {63, 458}, {232, 1}, {29, 111}};
const Nibbles code_rca_tv_POWER_ON[]     PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {4, 4}, {1, 4}, {1, 1}, {1, 1}, {1, 4}, {4, 1}, {1, 1}, {4, 1}, {4, 2}, {3, 0}};
const Nibbles code_rca_tv_POWER_OFF[]    PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {4, 4}, {1, 4}, {4, 1}, {1, 1}, {1, 4}, {4, 1}, {1, 1}, {4, 1}, {1, 2}, {3, 0}};
const Nibbles code_rca_tv_MUTE[]         PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {4, 4}, {4, 4}, {4, 1}, {1, 1}, {1, 4}, {4, 1}, {1, 1}, {1, 1}, {1, 2}, {3, 0}};
const Nibbles code_rca_tv_VOLUME_UP[]    PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {1, 4}, {4, 4}, {4, 1}, {1, 1}, {1, 4}, {4, 1}, {4, 1}, {1, 1}, {1, 2}, {3, 0}};
const Nibbles code_rca_tv_VOLUME_DOWN[]  PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {1, 4}, {4, 4}, {1, 1}, {1, 1}, {1, 4}, {4, 1}, {4, 1}, {1, 1}, {4, 2}, {3, 0}};
const Nibbles code_rca_tv_CHANNEL_UP[]   PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {1, 4}, {4, 1}, {4, 1}, {1, 1}, {1, 4}, {4, 1}, {4, 1}, {1, 4}, {1, 2}, {3, 0}};
const Nibbles code_rca_tv_CHANNEL_DOWN[] PROGMEM = {{0, 4}, {4, 4}, {4, 1}, {1, 4}, {1, 4}, {4, 1}, {1, 1}, {1, 1}, {1, 4}, {4, 1}, {4, 1}, {1, 4}, {4, 2}, {3, 0}};

//projectors

const BurstPair dict_sharp_projector[] PROGMEM = {{10, 70}, {10, 30}, {10, 1657}};
const Nibbles code_sharp_projector_POWER_STANDBY[] PROGMEM = {{0, 1}, {0, 0}, {1, 0}, {0, 1}, {0, 1}, {1, 1}, {0, 0}, {1, 2}, {0, 1}, {0, 0}, {1, 1}, {1, 0}, {1, 0}, {0, 0}, {1, 1}, {0, 1}};
const Nibbles code_sharp_projector_POWER_ON[] PROGMEM = {{0, 1}, {0, 0}, {1, 1}, {0, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 2}, {0, 1}, {0, 0}, {1, 0}, {1, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
const Nibbles code_sharp_projector_VOLUME_UP[] PROGMEM = {{0, 1}, {0, 0}, {1, 1}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 2}, {0, 1}, {0, 0}, {1, 0}, {0, 1}, {0, 1}, {0, 0}, {0, 1}, {0, 1}};
const Nibbles code_sharp_projector_VOLUME_DOWN[] PROGMEM = {{0, 1}, {0, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 1}, {1, 0}, {1, 2}, {0, 1}, {0, 0}, {1, 1}, {0, 1}, {0, 1}, {0, 0}, {0, 1}, {0, 1}};

//sources


/*
 * Codes organized by function, then sorted by manufacturers (major to minor)
 */

//TVs

//POWER ON==================================================
const IRCode POWER_ON[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_POWER_ON, 34, 13},
  {dict_lge_tv, code_lge_tv_POWER_ON, 34, 13},
  {dict_sony_tv, code_sony_tv_POWER_ON, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_POWER_ON, 50, 14},
  {dict_sharp_tv, code_sharp_tv_POWER_ON, 16, 13},
  {dict_philips_tv, code_philips_tv_POWER_ON, 13, 14},
  {dict_vizio_tv, code_vizio_tv_POWER_ON, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_POWER_ON, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_POWER_ON, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_POWER_ON, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_POWER_ON, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_POWER_ON, 34, 13},
  {dict_jvc_tv, code_jvc_tv_POWER_ON, 18, 13},
  {dict_rca_tv, code_rca_tv_POWER_ON, 27, 9}
};
const uint8_t POWER_ON_TOTAL = NUM_ELEM(POWER_ON);

//POWER OFF=================================================
const IRCode POWER_OFF[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_POWER_OFF, 34, 13},
  {dict_lge_tv, code_lge_tv_POWER_OFF, 34, 13},
  {dict_sony_tv, code_sony_tv_POWER_OFF, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_POWER_OFF, 50, 14},
  {dict_sharp_tv, code_sharp_tv_POWER_OFF, 16, 13},
  {dict_philips_tv, code_philips_tv_POWER_OFF, 12, 14},
  {dict_vizio_tv, code_vizio_tv_POWER_OFF, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_POWER_OFF, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_POWER_OFF, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_POWER_OFF, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_POWER_OFF, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_POWER_OFF, 34, 13},
  {dict_jvc_tv, code_jvc_tv_POWER_OFF, 18, 13},
  {dict_rca_tv, code_rca_tv_POWER_OFF, 27, 9}
};
const uint8_t POWER_OFF_TOTAL = NUM_ELEM(POWER_OFF);

//MUTE======================================================
const IRCode MUTE[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_MUTE, 34, 13},
  {dict_lge_tv, code_lge_tv_MUTE, 34, 13},
  {dict_sony_tv, code_sony_tv_MUTE, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_MUTE, 50, 14},
  {dict_sharp_tv, code_sharp_tv_MUTE, 16, 13},
  {dict_philips_tv, code_philips_tv_MUTE, 12, 14},
  //{dict_vizio_tv, code_vizio_tv_MUTE, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_MUTE, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_MUTE, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_MUTE, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_MUTE, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_MUTE, 34, 13},
  {dict_jvc_tv, code_jvc_tv_MUTE, 18, 13},
  {dict_rca_tv, code_rca_tv_MUTE, 27, 9}
};
const uint8_t MUTE_TOTAL = NUM_ELEM(MUTE);

//VOLUME UP=================================================
const IRCode VOLUME_UP[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_VOLUME_UP, 34, 13},
  {dict_lge_tv, code_lge_tv_VOLUME_UP, 34, 13},
  {dict_sony_tv, code_sony_tv_VOLUME_UP, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_VOLUME_UP, 50, 14},
  {dict_sharp_tv, code_sharp_tv_VOLUME_UP, 16, 13},
  {dict_philips_tv, code_philips_tv_VOLUME_UP, 12, 14},
  {dict_vizio_tv, code_vizio_tv_VOLUME_UP, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_VOLUME_UP, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_VOLUME_UP, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_VOLUME_UP, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_VOLUME_UP, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_VOLUME_UP, 34, 13},
  {dict_jvc_tv, code_jvc_tv_VOLUME_UP, 18, 13},
  {dict_rca_tv, code_rca_tv_VOLUME_UP, 27, 9}
};
const uint8_t VOLUME_UP_TOTAL = NUM_ELEM(VOLUME_UP);

//VOLUME DOWN===============================================
const IRCode VOLUME_DOWN[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_VOLUME_DOWN, 34, 13},
  {dict_lge_tv, code_lge_tv_VOLUME_DOWN, 34, 13},
  {dict_sony_tv, code_sony_tv_VOLUME_DOWN, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_VOLUME_DOWN, 50, 14},
  {dict_sharp_tv, code_sharp_tv_VOLUME_DOWN, 16, 13},
  {dict_philips_tv, code_philips_tv_VOLUME_DOWN, 12, 14},
  {dict_vizio_tv, code_vizio_tv_VOLUME_DOWN, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_VOLUME_DOWN, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_VOLUME_DOWN, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_VOLUME_DOWN, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_VOLUME_DOWN, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_VOLUME_DOWN, 34, 13},
  {dict_jvc_tv, code_jvc_tv_VOLUME_DOWN, 18, 13},
  {dict_rca_tv, code_rca_tv_VOLUME_DOWN, 27, 9}
};
const uint8_t VOLUME_DOWN_TOTAL = NUM_ELEM(VOLUME_DOWN);

//CHANNEL UP================================================
const IRCode CHANNEL_UP[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_CHANNEL_UP, 34, 13},
  {dict_lge_tv, code_lge_tv_CHANNEL_UP, 34, 13},
  {dict_sony_tv, code_sony_tv_CHANNEL_UP, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_CHANNEL_UP, 50, 14},
  {dict_sharp_tv, code_sharp_tv_CHANNEL_UP, 16, 13},
  {dict_philips_tv, code_philips_tv_CHANNEL_UP, 12, 14},
  {dict_vizio_tv, code_vizio_tv_CHANNEL_UP, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_CHANNEL_UP, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_CHANNEL_UP, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_CHANNEL_UP, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_CHANNEL_UP, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_CHANNEL_UP, 34, 13},
  {dict_jvc_tv, code_jvc_tv_CHANNEL_UP, 18, 13},
  {dict_rca_tv, code_rca_tv_CHANNEL_UP, 27, 9}
};
const uint8_t CHANNEL_UP_TOTAL = NUM_ELEM(CHANNEL_UP);

//CHANNEL DOWN==============================================
const IRCode CHANNEL_DOWN[] PROGMEM = {
  {dict_samsung_tv, code_samsung_tv_CHANNEL_DOWN, 34, 13},
  {dict_lge_tv, code_lge_tv_CHANNEL_DOWN, 34, 13},
  {dict_sony_tv, code_sony_tv_CHANNEL_DOWN, 13, 12},
  {dict_panasonic_tv, code_panasonic_tv_CHANNEL_DOWN, 50, 14},
  {dict_sharp_tv, code_sharp_tv_CHANNEL_DOWN, 16, 13},
  {dict_philips_tv, code_philips_tv_CHANNEL_DOWN, 12, 14},
  {dict_vizio_tv, code_vizio_tv_CHANNEL_DOWN, 34, 13},
  {dict_pioneer_tv, code_pioneer_tv_CHANNEL_DOWN, 34, 13},
  {dict_mitsubishi_tv, code_mitsubishi_tv_CHANNEL_DOWN, 17, 15},
  {dict_fujitsu_tv, code_fujitsu_tv_CHANNEL_DOWN, 50, 13},
  {dict_toshiba_tv, code_toshiba_tv_CHANNEL_DOWN, 34, 13},
  {dict_sanyo_tv, code_sanyo_tv_CHANNEL_DOWN, 34, 13},
  {dict_jvc_tv, code_jvc_tv_CHANNEL_DOWN, 18, 13},
  {dict_rca_tv, code_rca_tv_CHANNEL_DOWN, 27, 9}
};
const uint8_t CHANNEL_DOWN_TOTAL = NUM_ELEM(CHANNEL_DOWN);



//projectors

//POWER ON==================================================
const IRCode PROJ_POWER_STANDBY[] PROGMEM = {
  {dict_sharp_projector, code_sharp_projector_POWER_STANDBY, 32, 13}
};
const uint8_t PROJ_POWER_STANDBY_TOTAL = NUM_ELEM(PROJ_POWER_STANDBY);

//POWER OFF=================================================
const IRCode PROJ_POWER_ON[] PROGMEM = {
  {dict_sharp_projector, code_sharp_projector_POWER_ON, 32, 13}
};
const uint8_t PROJ_POWER_OFF_TOTAL = NUM_ELEM(PROJ_POWER_ON);


//VOLUME UP=================================================
const IRCode PROJ_VOLUME_UP[] PROGMEM = {
  {dict_sharp_projector, code_sharp_projector_VOLUME_UP, 32, 13}
};
const uint8_t PROJ_VOLUME_UP_TOTAL = NUM_ELEM(PROJ_VOLUME_UP);

//VOLUME DOWN===============================================
const IRCode PROJ_VOLUME_DOWN[] PROGMEM = {
  {dict_sharp_projector, code_sharp_projector_VOLUME_DOWN, 32, 13}
};
const uint8_t PROJ_VOLUME_DOWN_TOTAL = NUM_ELEM(PROJ_VOLUME_DOWN);
