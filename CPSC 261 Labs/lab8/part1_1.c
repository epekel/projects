#include <stdlib.h>
#include <stdio.h>
#include "boot_sect.h"

FILE *file;
//unsigned int sector_size, cluster_size, num_entries, num_sectors_perfat16, num_reserved, num_hidden, sn_first_copy, sn_first_root, sn_first_cluster;

void main(int argc, char **argv) {
	boot_sect_t *info = malloc(sizeof(boot_sect_t));
	file = fopen(argv[1], "r"); // or rb
	unsigned int *buffer = malloc(512);
	unsigned int superblock;
	fread(buffer, 512, 1, file);
	
	superblock = *buffer;
	info->ssize[0] = (uint8_t) superblock >> 11; // *(uint8_t *) de olabilir (basa & da konabilir)
	info->ssize[1] = (uint8_t) superblock >> 12;
	printf("Sector size: %i\n", *info->ssize);
	//info->csize = 
	

	/*info.ssize = sector_size; // array
	info.csize = cluster_size;
	info.reserved = num_reserved; // array
	info.numroot = num_entries; // array
	info.sectperfat16 = num_sectors_perfat16; // array*/

	fclose(file);
}