#include <stdlib.h>
#include <stdio.h>
#include "boot_sect.h"

FILE *file;
//unsigned int sector_size, cluster_size, num_entries, num_sectors_perfat16, num_reserved, num_hidden, sn_first_copy, sn_first_root, sn_first_cluster;

void main(int argc, char **argv) {
	boot_sect_t *info = malloc(sizeof(boot_sect_t));
	file = fopen(argv[1], "r"); // or rb
	unsigned char buffer[513];
	uint16_t ssize, reserved, numroot, sectperfat16, hidden, sectors16, sectpertrack, heads;

	//might add a condition check for the file (if it is NULL or not).

	fread(buffer, 512, 1, file);
	buffer[(sizeof(buffer)) - 1] = 0;
	
	info->ssize[1] = (uint8_t) buffer[11];
	info->ssize[0] = (uint8_t) buffer[12];
	ssize = (info->ssize[0] << 8) + info->ssize[1];
	printf("Sector size: %d\n", ssize);

	info->csize = (uint8_t) buffer[13];
	printf("Cluster size in sectors: %d\n", info->csize);

	info->numroot[1] = (uint8_t) buffer[17];
	info->numroot[0] = (uint8_t) buffer[18];
	numroot = (info->numroot[0] << 8) + info->numroot[1];
	printf("Root directory size (nb of entries): %d\n", numroot);

	info->sectperfat16[1] = (uint8_t) buffer[22];
	info->sectperfat16[0] = (uint8_t) buffer[23];
	sectperfat16 = (info->sectperfat16[0] << 8) + info->sectperfat16[1];
	printf("Sectors per fat: %d\n", sectperfat16);

	info->reserved[1] = (uint8_t) buffer[14];
	info->reserved[0] = (uint8_t) buffer[15];
	reserved = (info->reserved[0] << 8) + info->reserved[1];
	printf("Reserved sectors: %d\n", reserved);

	info->prevsect[1] = (uint8_t) buffer[28];
	info->prevsect[0] = (uint8_t) buffer[29];
	hidden = (info->prevsect[0] << 8) + info->prevsect[1];
	printf("Hidden sectors: %d\n", hidden);

	info->numfat = (uint8_t) buffer[16];
	printf("Number of FAT copies: %d\n", info->numfat);

	info->sectors16[1] = (uint8_t) buffer[19];
	info->sectors16[0] = (uint8_t) buffer[20];
	sectors16 = (info->sectors16[0] << 8) + info->sectors16[1];
	printf("Total number of sectors: %d\n", sectors16);

	info->media[0] = (uint8_t) buffer[21];
	printf("Media descriptor type: %d\n", info->media[0]);

	info->sectpertrack[1] = (uint8_t) buffer[24];
	info->sectpertrack[0] = (uint8_t) buffer[25];
	sectpertrack = (info->sectpertrack[0] << 8) + info->sectpertrack[1];
	printf("Number of sectors per track: %d\n", sectpertrack);

	info->heads[1] = (uint8_t) buffer[26];
	info->heads[0] = (uint8_t) buffer[27];
	heads = (info->heads[0] << 8) + info->heads[1];
	printf("Number of heads: %d\n", heads);

	/*
	 * The boot sector is at sector 0. 
	 * In FAT12, FAT copies are kept in sectors right after the boot sector. (reference [1])
	 * So, the sector number of the first copy of the file allocation table is 1.
	 * Also, the FAT copies are kept in consecutive sectors, and are followed by the root directory. (reference [2])
	 * So, the sector number of the first sector of the root directory will be numfat * sectperfat16.
	 * Moreover, the first usable cluster comes after the root directory. Each entry in the root directory requires 32 bytes. (reference [3])
	 * In order to calculate first usable cluster offset in sectors, we need to know how many sectors the root directory requires. 
	 * This value will be (numroot * 32) / ssize. So, the offset will be ( root offset + ((numroot * 32) / ssize) ).
	 */
	
	//printf("Fat offset in sectors: %d\n", );

	//printf("Root directory offset in sectors: %d\n", );

	//printf("First usable cluster offset (cluster #2) in sectors: %d\n", );


	fclose(file);
}
