/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2009 Pierre-Alexandre Meyer
 *
 *   Some parts borrowed from chain.c32:
 *
 *   Copyright 2003-2009 H. Peter Anvin - All Rights Reserved
 *   Copyright 2009 Intel Corporation; author: H. Peter Anvin
 *
 *   This file is part of Syslinux, and is made available under
 *   the terms of the GNU General Public License version 2.
 *
 * ----------------------------------------------------------------------- */

#include <stdlib.h>
#include <disk/geom.h>
#include <disk/partition.h>
#include <disk/read.h>

static inline int is_extended_partition(struct part_entry *ptab)
{
	return (ptab->ostype == 0x05 ||
		ptab->ostype == 0x0f ||
		ptab->ostype == 0x85);
}
static inline int msdos_magic_present(char *ptab)
{
	return ( *(uint16_t *)(ptab + 0x1fe) == 0xaa55 );
}

/**
 * process_extended_partition - execute a callback for each partition contained listed in an ebr
 * @drive_info:		driveinfo struct describing the drive
 * @partition_offset:	Absolute start (lba) of the partition
 * @callback:		Callback to execute
 * @error:		Buffer for I/O errors
 * @nb_part_seen:	Number of partitions found on the disk so far
 **/
static void process_extended_partition(struct driveinfo *drive_info,
				       int partition_offset,
				       void *callback(struct driveinfo *, struct part_entry *, int, int),
				       int *error, int nb_part_seen)
{
	/* The ebr is located at the first sector of the extended partition */
	char* ebr = read_sectors(drive_info, partition_offset, 1, error);

	/* If something bad during the read happens, we can't do much: bail out */
	if (*error)
		return;

	/* Check msdos magic signature */
	if (!msdos_magic_present(ebr))
		return;

	struct part_entry *ptab = (struct part_entry *)(ebr + PARTITION_TABLES_OFFSET);

	for (int i = 0; i < 4; i++) {
		if (!is_extended_partition(&ptab[i])) {
			/*
			 * This EBR partition table entry points to the
			 * logical partition associated to that EBR
			 */
			int logical_partition_start = partition_offset + ptab[i].start_lba;

			/* Last EBR in the extended partition? */
			if (!logical_partition_start)
				continue;

			/*
			 * Check for garbage:
			 * 3rd and 4th entries in an EBR should be zero
			 * Some (malformed) partitioning software still add some
			 * data partitions there.
			 */
			if (ptab[i].start_lba <= 0 || ptab[i].length <= 0)
				continue;

			nb_part_seen++;
			callback(drive_info,
				 &ptab[i],
				 logical_partition_start,
				 nb_part_seen);
		} else
			process_extended_partition(drive_info,
						   partition_offset + ptab[i].start_lba,
						   callback,
						   error, nb_part_seen);
	}
}

/**
 * process_mbr - execute a callback for each partition contained in an {m,e}br
 * @drive_info:	driveinfo struct describing the drive
 * @ptab:	Pointer to the partition table
 * @callback:	Callback to execute
 * @error:	Return the error code (I/O), if needed
 **/
static void process_mbr(struct driveinfo *drive_info, struct part_entry *ptab,
		        void *callback(struct driveinfo *, struct part_entry *, int, int),
		        int *error)
{
	for (int i = 0; i < 4; i++) {
		if (*error)
			return;

		if (ptab[i].start_sect > 0) {
			if (is_extended_partition(&ptab[i])) {
				callback(drive_info,
					 &ptab[i],
					 ptab[i].start_lba,
					 i+1);
				process_extended_partition(drive_info, ptab[i].start_lba, callback, error, 4);
			} else
				callback(drive_info,
					 &ptab[i],
					 ptab[i].start_lba,
					 i+1);
		}
	}
}

/**
 * parse_partition_table - execute a callback for each partition entry
 * @d:		driveinfo struct describing the drive
 * @callback:	Callback to execute
 * @error:	Return the error code (I/O), if needed
 *
 * The signature of the callback should be the following:
 *
 * void callback(struct driveinfo *drive_info,
 *		 struct part_entry *ptab,
 *		 int offset_root,
 *		 int nb_part_seen)
 **/
int parse_partition_table(struct driveinfo *d, void *callback, int *error)
{
	char *mbr = read_mbr(d->disk, error);
	if (!mbr)
		return -1;
	else {
		/* Check msdos magic signature */
		if (!msdos_magic_present(mbr))
			return -1;

		struct part_entry *ptab = (struct part_entry *)(mbr + PARTITION_TABLES_OFFSET);
		process_mbr(d, ptab, callback, error);
		if (*error)
			return -1;
		else
			return 0;
	}
}
