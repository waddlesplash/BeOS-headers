/* 
	fs_info.h

	Copyright (c) 1997 by Be Incorporated.  All Rights Reserved.
*/

#pragma once

#ifndef _FS_INFO_H
#define	_FS_INFO_H

#include <sys/types.h>
#include <SupportDefs.h>
#include <OS.h>


#define	B_FS_IS_READONLY		0x00000001
#define	B_FS_IS_REMOVABLE		0x00000002
#define	B_FS_IS_PERSISTENT		0x00000004
#define	B_FS_IS_SHARED			0x00000008
#define	B_FS_HAS_MIME			0x00010000
#define	B_FS_HAS_ATTR			0x00020000
#define	B_FS_HAS_QUERY			0x00040000

struct fs_info {
	dev_t	dev;								/* fs dev_t */
	ino_t	root;								/* root ino_t */
	uint32	flags;								/* file system flags */
	off_t	block_size;							/* fundamental block size */
	off_t	io_size;							/* optimal io size */
	off_t	total_blocks;						/* total number of blocks */
	off_t	free_blocks;						/* number of free blocks */
	off_t	total_nodes;						/* total number of nodes */
	off_t	free_nodes;							/* number of free nodes */
	char	device_name[128];					/* device holding fs */
	char	volume_name[B_FILE_NAME_LENGTH];	/* volume name */
	char	fsh_name[B_OS_NAME_LENGTH];			/* name of fs handler */
};

typedef struct fs_info	fs_info;

#endif
