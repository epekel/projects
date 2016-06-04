#include <stdio.h>
#include <stdlib.h>
#include "endian.h"

int which_endianness(void)
{
  int endianness;                
  int x = 0x01020304;            
  char *y = (char*) &x;          

  if(*y == 0x04) {
    endianness = LITTLE_ENDIAN_CPU;
  } else {                  
    endianness = BIG_ENDIAN_CPU;
  }
  return endianness;
}
