#include <stdlib.h>
#include <stdio.h>
#include "boot_sect.h"

FILE *file;

void main(int argc, char **argv) {
	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("File not found.\n"); // NULL check for file pointer
		return;
	}

	boot_sect_t *info = malloc(sizeof(boot_sect_t));
	unsigned char buffer[513];
	uint16_t ssize, numreserved, numroot, sectperfat16, numhidden, sectors16, sectpertrack, heads;
	int fat_offset, root_offset, cluster2_offset;
	
	fread(buffer, 512, 1, file);
	buffer[(sizeof(buffer)) - 1] = 0;
	
	/*
	* Sector size.
	*/
	info->ssize[1] = (uint8_t) buffer[11];
	info->ssize[0] = (uint8_t) buffer[12];
	ssize = (info->ssize[0] << 8) + info->ssize[1];
	printf("Sector size: %d\n", ssize);

	/*
	* Cluster size in sectors.
	*/
	info->csize = (uint8_t) buffer[13];
	printf("Cluster size in sectors: %d\n", info->csize);

	/*
	* The number of entries in the root directory.
	*/
	info->numroot[1] = (uint8_t) buffer[17];
	info->numroot[0] = (uint8_t) buffer[18];
	numroot = (info->numroot[0] << 8) + info->numroot[1];
	printf("Root directory size (nb of entries): %d\n", numroot);

	/*
	* The number of sectors per file allocation table.
	*/
	info->sectperfat16[1] = (uint8_t) buffer[22];
	info->sectperfat16[0] = (uint8_t) buffer[23];
	sectperfat16 = (info->sectperfat16[0] << 8) + info->sectperfat16[1];
	printf("Sectors per fat: %d\n", sectperfat16);

	/*
	* The number of reserved sectors on the disk.
	*/
	info->reserved[1] = (uint8_t) buffer[14];
	info->reserved[0] = (uint8_t) buffer[15];
	numreserved = (info->reserved[0] << 8) + info->reserved[1];
	printf("Reserved sectors: %d\n", numreserved);

	/*
	* The number of hidden sectors on the disk (hidden sectors are sectors preceding the partition).
	*/
	info->prevsect[1] = (uint8_t) buffer[28];
	info->prevsect[0] = (uint8_t) buffer[29];
	numhidden = (info->prevsect[0] << 8) + info->prevsect[1];
	printf("Hidden sectors: %d\n", numhidden);

	/*
	* The boot sector is at sector 0 (in this case). 
	* In FAT12, FAT copies are kept in sectors right after the boot sector, i.e. reserved sectors. [1]
	* Reserved sectors are sectors that appear before, and including, the boot sector. [2] 
	* In other words, reserved sectors are sectors preceding the start of the first FAT, including the boot sector itself. [3]
	* So, the sector number of the first copy of the file allocation table will be (numreserved).
	* Also, the FAT copies are consecutive on the disk, and are followed by the root directory. [3], [1]
	* So, the sector number of the first sector of the root directory will be (fat_offset + (numfat * sectperfat16)).
	* Moreover, the first usable cluster comes after the root directory. Each entry in the root directory requires 32 bytes. [2]
	* In order to calculate first usable cluster offset in sectors, we need to know how many sectors the root directory requires. 
	* This value will be (numroot * 32) / ssize. So, the offset will be ( root_offset + ((numroot * 32) / ssize) ).
	*
	* ----- REFERENCES -----
	* [1] http://www.c-jump.com/CIS24/Slides/FAT/lecture.html
	* [2] https://samskalicky.wordpress.com/2013/08/08/a-look-back-at-the-fat12-file-system/
	* [3] http://www.dewassoc.com/kbase/hard_drives/boot_sector.htm
	* ----------------------
	*/
	
	fat_offset = (int) numreserved;
	printf("Fat offset in sectors: %d\n", fat_offset);

	info->numfat = (uint8_t) buffer[16]; // Number of FATs
	root_offset = (int) (fat_offset + (info->numfat * sectperfat16));
	printf("Root directory offset in sectors: %d\n", root_offset);

	cluster2_offset = (int) (root_offset + ((numroot * 32) / ssize));
	printf("First usable cluster offset (cluster #2) in sectors: %d\n", cluster2_offset);

	/*
	*----------------------------
	* Part 2 starting from here.
	*----------------------------
	*/
	fseek(file, (long) root_offset*ssize, SEEK_SET);
	unsigned char buffer2[numroot*32 + 1];
	fread(buffer2, numroot*32, 1, file);
	buffer2[(sizeof(buffer2)) - 1] = 0;
	int i, j;
	char *name;
	uint32_t size;
	uint16_t cluster_id;
	for (i = 0; i < numroot; i++) {
		for (j = 0; j < 11; j++) {
			name[j] = (char) buffer2[j + 32 * i];
			// might add a condition check for the extension
		}
		printf("%s", *name);
		size = (uint32_t) ((buffer2[31] << 24) + (buffer2[30] << 16) + (buffer2[29] << 8) + buffer2[28]);
		printf(" (size = %d)", size);
		if (size == 0) {
			printf(" [This file is a directory]");
		}
		cluster_id = (uint16_t) ((buffer2[27 + 32*i] << 8) + buffer2[26 + 32*i]);
		printf(": %d\n", cluster_id);
	}
	

	fclose(file);
}
