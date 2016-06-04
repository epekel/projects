#include "endian.h"

int main(int argc, char **argv)
{
    int faillong = 0, failint = 0;
    
    if (reverse_long(0x0102030405060708L) != 0x0807060504030201L)
    {
	printf("reverse_long failed on 0x0102030405060708L\n");
	faillong++;
    }
    if (faillong == 0)
    {
	printf("reverse_long works\n");
    }

    return faillong;
}
