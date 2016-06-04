#include <stdio.h>

#define LITTLE_ENDIAN_CPU 1
#define BIG_ENDIAN_CPU    2

extern void read_char(FILE *f, int swap, char *c);
extern void read_string(FILE *f, int swap, char *c);
extern void read_int(FILE *f, int swap, int *c);
extern void read_long(FILE *f, int swap, long *c);
extern void read_ptr(FILE *f, int swap, void **c);

extern void write_char(FILE *f, char c);
extern void write_string(FILE *f, char *c);
extern void write_int(FILE *f, int c);
extern void write_long(FILE *f, long c);
extern void write_ptr(FILE *f, void *c);

extern long reverse_long(long);
extern int  which_endianness(void);
