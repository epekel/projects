#include "endian.h"

int main(int argc, char **argv)
{
    printf("This computer is %s endian\n", which_endianness() == LITTLE_ENDIAN_CPU ? "little" : "big");
    return 0;
}
