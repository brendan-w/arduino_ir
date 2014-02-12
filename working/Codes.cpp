#include <stdint.h>

/*
 * Structs
 */

struct Nibbles
{
  //1 byte, 2 values
  unsigned int hi:4;
  unsigned int lo:4;
  //slower to execute, but saves sooooo much space
};

struct BurstPair
{
  //measured in cycles of the carrier
  int on;
  int off;
};

struct IRCode
{
  const uint8_t    carrier;    //microseconds of on time (wavelength / 2)
  const BurstPair* dict;       //dictionary of burst pairs
  //const Nibbles*   code;       //code in terms of burst pairs in dict;
  const uint8_t* code;
  const uint8_t    codeLength; //number of nibbles in code[]
};





/*
 * Raw dictionary and code data. Linked to functions by pointers (shared dictionaries save space)
 * Dictionaries store the different burst pairs.
 * Codes store the a list of dictionary indices.
 * Full list of burst pairs is compiled prior to transmission (slower, but saves space)
 */

const BurstPair dict_panasonic[] =          {{16, 16}, {16, 48}, {128, 63}, {16, 255}};
const Nibbles   code_panasonic_POWER_ON[] = {{2, 0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0}, {1,0}, {0,0}, {0,0}, {0,0}, {0,0}, {1,1}, {1,1}, {1,0}, {0,0}, {1,1}, {1,1}, {1,0}, {1,3}};

const BurstPair norm_dict[] =                {{16, 16}, {16, 48}, {128, 63}, {16, 255}};
const uint8_t   norm_code[] =                {2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 3};

/*
 * Codes organized by function, then sorted by manufacturers (major to minor)
 */

//POWER ON
const IRCode POWER_ON[] = {
  //{14, dict_panasonic, code_panasonic_POWER_ON, 50}
  {14, norm_dict, norm_code, 50}
};
