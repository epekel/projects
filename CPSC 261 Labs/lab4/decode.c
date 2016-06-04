#include <stdlib.h>
#include "endian.h"


int main(int argc, char **argv)
{
    int iAmLittleEndian, fileIsLittleEndian, swap;
    long index, count;
    long magic;
    FILE *f;
    char tag;
    char c;
    int i;
    long l;
    void *p;
    char s[4096];

    if (argc != 2)
    {
	fprintf(stderr, "Incorrect number of arguments\n");
	exit(1);
    }

    f = fopen(argv[1], "rb");
    if (f == NULL)
    {
 	fprintf(stderr, "Can't open file \"%s\"\n", argv[1]);
	exit(1);
    }

    iAmLittleEndian = which_endianness() == LITTLE_ENDIAN_CPU;
    printf("This computer is %s endian\n", iAmLittleEndian ? "little" : "big");
    read_long(f, 0, &magic);
    if (magic == 0x0102030405060708) 
	fileIsLittleEndian = iAmLittleEndian;
    else if (magic == 0x0807060504030201)
	fileIsLittleEndian = !iAmLittleEndian;
    else {
 	fprintf(stderr, "Invalid magic tag in file %016lx\n", magic);
	fclose(f);
	exit(1);
    }
    printf("The data file is %s endian\n", fileIsLittleEndian ? "little" : "big");
    swap = iAmLittleEndian != fileIsLittleEndian;
	
    while (!feof(f))
    {
	read_char(f, 0, &tag);
	if (feof(f)) break;
	read_long(f, swap, &count);
	for (index = 0; index < count; ++index) {
	    switch(tag) {
	    case 1:
		read_char(f, swap, &c);
		printf("char: %c\n", c);
		break;
	    case 2:
		read_string(f, swap, s);
		printf("string: %s\n", s);
		break;
	    case 3:
		read_long(f, swap, &l);
		printf("long: %ld\n", l);
		break;
	    case 4:
		read_ptr(f, swap, &p);
		printf("pointer: %p\n", p);;
		break;
	    default:
		fprintf(stderr, "Bogus tag %d in file\n", tag);
		fclose(f);
		exit(1);
	    }
	}
    }
    fclose(f);
    return 0;
}
