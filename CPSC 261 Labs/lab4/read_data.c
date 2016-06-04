#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "endian.h"

void read_char(FILE *f, int swap, char *dest)
{
	fread(dest, 1, 1, f);
}

void read_long(FILE *f, int swap, long *dest)
{
	fread(dest, 8, 1, f);
	if (swap) {
		*dest = reverse_long(*dest);
	}
}

void read_string(FILE *f, int swap, char *dest)
{
	char *index = dest;
	while (1) {
		fread(index, 1, 1, f);
		if (*index == '\0')
		{
			break;
		}
		index++;
	}
}

void read_ptr(FILE *f, int swap, void **dest)
{
	fread(dest, 8, 1, f);
	if (swap) {
		*dest = (void*)reverse_long((long)*dest);
	}
}