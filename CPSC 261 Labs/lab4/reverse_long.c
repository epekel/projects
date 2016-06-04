#include <stdio.h>
#include <stdlib.h>

long reverse_long(long x)
{
    long byte = 0;
    long y = 0;
    int i = sizeof(x);
    while(i > 0)
    {
	y <<= 8;
	byte = 0xff & x;
	y |= byte;
	x >>= 8;
	i--;
    }
    return y;
}
