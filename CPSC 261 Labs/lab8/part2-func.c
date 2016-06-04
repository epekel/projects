#include <stdlib.h>
#include <stdio.h>
#include "boot_sect.h"

FILE *file;
int fat_offset, root_offset, cluster2_offset;
uint16_t ssize, numreserved, numroot, sectperfat16, numhidden;

/*
* -----------------------------------------
*          Function Prototypes
* -----------------------------------------
*/
unsigned char *read_buffer(FILE *file, size_t num_elt, size_t size);
boot_sect_t *store_boot_sector(unsigned char *buffer);
void print_boot_sector(boot_sect_t *info);
unsigned int convert_little_endian(unsigned char *buffer, int offset, int size);
void print_root_entries(FILE *file, unsigned char *buffer);


void main(int argc, char **argv) {
	file = fopen(argv[1], "r");
	if (file == NULL) {
		printf("File not found.\n"); // NULL check for file pointer
		return;
	}

	/*
	*----------------------------
	*          Part 1
	*----------------------------
	*/
	boot_sect_t *info;
	unsigned char *buffer;
	
	buffer = read_buffer(file, 1, 512);
	info = store_boot_sector(buffer);
	print_boot_sector(info);
	
	/*
	*----------------------------
	*          Part 2
	*----------------------------
	*/
	printf("\n");
	fseek(file, (long) root_offset*ssize, SEEK_SET);
	unsigned char *buffer2;

	print_root_entries(file, buffer2);


	fclose(file);
}

/*
* Returns an unsigned char buffer created according to the given file, number of elements to be read from the file, and size of each element to be read in bytes. 
*/
unsigned char *read_buffer(FILE *file, size_t num_elt, size_t size) {
	unsigned char *buffer = malloc((size + 1)*sizeof(unsigned char));
	fread(buffer, size, num_elt, file);
	buffer[(sizeof(buffer)) - 1] = 0;
	return buffer;
}

/*
* Returns a boot_sect_t struct that has stored information extracted from a given buffer.
*/
boot_sect_t *store_boot_sector(unsigned char *buffer) {
	boot_sect_t *info = malloc(sizeof(boot_sect_t));

	info->ssize[1] = (uint8_t)buffer[11]; // Sector size
	info->ssize[0] = (uint8_t)buffer[12];
	info->csize = (uint8_t)buffer[13]; // Cluster size
	info->numroot[1] = (uint8_t)buffer[17]; // Number of root entries
	info->numroot[0] = (uint8_t)buffer[18];
	info->sectperfat16[1] = (uint8_t)buffer[22]; // Sectors per FAT
	info->sectperfat16[0] = (uint8_t)buffer[23];
	info->reserved[1] = (uint8_t)buffer[14]; // Reserved sectors
	info->reserved[0] = (uint8_t)buffer[15];
	info->prevsect[1] = (uint8_t)buffer[28]; // Sectors before partition (hidden sectors)
	info->prevsect[0] = (uint8_t)buffer[29];
	info->numfat = (uint8_t)buffer[16]; // Number of FATs

	return info;
}

/*
* Prints information about the boot sector, given a boot_sect_t struct.
* Responsible for printing the correct big endian values stored in the boot_sect_t struct.
*/
void print_boot_sector(boot_sect_t *info) {
	/*
	* Sector size.
	*/
	ssize = (info->ssize[0] << 8) + info->ssize[1];
	printf("Sector size: %d\n", ssize);

	/*
	* Cluster size in sectors.
	*/
	printf("Cluster size in sectors: %d\n", info->csize);

	/*
	* The number of entries in the root directory.
	*/
	numroot = (info->numroot[0] << 8) + info->numroot[1];
	printf("Root directory size (nb of entries): %d\n", numroot);

	/*
	* The number of sectors per file allocation table.
	*/
	sectperfat16 = (info->sectperfat16[0] << 8) + info->sectperfat16[1];
	printf("Sectors per fat: %d\n", sectperfat16);

	/*
	* The number of reserved sectors on the disk.
	*/
	numreserved = (info->reserved[0] << 8) + info->reserved[1];
	printf("Reserved sectors: %d\n", numreserved);

	/*
	* The number of hidden sectors on the disk (hidden sectors are sectors preceding the partition).
	*/
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

	fat_offset = (int)numreserved;
	printf("Fat offset in sectors: %d\n", fat_offset);

	root_offset = (int)(fat_offset + (info->numfat * sectperfat16));
	printf("Root directory offset in sectors: %d\n", root_offset);

	cluster2_offset = (int)(root_offset + ((numroot * 32) / ssize));
	printf("First usable cluster offset (cluster #2) in sectors: %d\n", cluster2_offset);
}

/*
* Returns an unsigned int converted from little endian to big endian given a buffer, an offset to start converting from, and number of bytes (size) we want to convert.
*/
unsigned int convert_little_endian(unsigned char *buffer, int offset, int size) {
	unsigned int converted = 0;
	int i;

	for (i = 0; i < size; i++) {
		converted += (buffer[offset + i] << (8 * i));
	}

	return converted;
}

/*
* Prints out information about the entries in the root directory.
*/
void print_root_entries(FILE *file, unsigned char *buffer) {
	int i, j, k;
	uint32_t size;
	uint16_t cluster_id;

	for (i = 0; i < numroot; i++) {
		buffer = read_buffer(file, 1, 32);

		// Check to see if the directory ends.
		if (buffer[0] == 0 || buffer[0] == 0xe5) {
			break;
		}

		// Name.
		for (j = 0; j < 8; j++) {
			if (buffer[j] == ' ') {
				break;
			}
			printf("%c", buffer[j]);
		}

		// Extension.
		if (buffer[8] != ' ') {
			printf(".");
			for (k = 8; k < 11; k++) {
				if (buffer[k] == ' ') {
					break;
				}
				printf("%c", buffer[k]);
			}
		}

		// Size (and whether or not file is a directory).
		size = (uint32_t)convert_little_endian(buffer, 28, 4);
		if (size == 0) {
			printf(" (directory)");
		}
		else {
			printf(" (size = %d)", size);
		}

		// Cluster number.
		cluster_id = (uint16_t)convert_little_endian(buffer, 26, 2);
		printf(": %d\n", cluster_id);

	}
}
