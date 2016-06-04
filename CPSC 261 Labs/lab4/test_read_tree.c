#include "tree.h"
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include "endian.h"

int main (int argc, char* argv[])
{
    tree_node *t;
    int iAmLittleEndian, fileIsLittleEndian, swap;
    long magic;
    
    if (argc != 2) {
	fprintf(stderr, "Usage: test_read_tree tree_source_file\n");
	return 1;
    }
    srandom(time(0));
    char *fname = argv[1];
    FILE *file = fopen(fname, "rb");
    if (file == NULL) {
	fprintf(stderr, "Can't open file \"%s\" for reading\n", fname);
	return 1;
    }	

    if (argc != 2) {
	fprintf(stderr, "Incorrect number of arguments\n");
	exit(1);
    }

    iAmLittleEndian = which_endianness() == LITTLE_ENDIAN_CPU;
    read_long(file, 0, &magic);
    if (magic == 0x0102030405060708) 
	fileIsLittleEndian = iAmLittleEndian;
    else if (magic == 0x0807060504030201)
	fileIsLittleEndian = !iAmLittleEndian;
    else {
 	fprintf(stderr, "Invalid magic tag in file %016lx\n", magic);
	fclose(file);
	return 1;
    }
    // printf("The data file is %s endian\n", fileIsLittleEndian ? "little" : "big");
    swap = iAmLittleEndian != fileIsLittleEndian;

    t = read_tree(file, swap);

    // printtree_node(t);
    show_tree_node(t);
    return 0;
}
