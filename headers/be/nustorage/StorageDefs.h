/******************************************************************************

	File:			StorageDefs.h

	Description:	Storage Kit miscellany

	Copyright 1993-97, Be Incorporated

******************************************************************************/

#pragma once

#ifndef _STORAGE_DEFS_H
#define	_STORAGE_DEFS_H

#include <fcntl.h>
#include <sys/param.h>
#include <limits.h>

/*----LIMITS--------------------------------*/
#define B_FILE_NAME_LENGTH		NAME_MAX
#define B_PATH_NAME_LENGTH 		MAXPATHLEN
#define B_ATTR_NAME_LENGTH		(B_FILE_NAME_LENGTH-1)
#define B_MIME_TYPE_LENGTH		(B_ATTR_NAME_LENGTH - 15)
#define B_MAX_SYMLINKS			SYMLINK_MAX


/*----FILE OPEN MODES--------------------------------*/

#define B_READ_ONLY 	O_RDONLY  /* read only */
#define B_WRITE_ONLY 	O_WRONLY /* write only */
#define B_READ_WRITE 	O_RDWR   /* read and write */

#define	B_FAIL_IF_EXISTS	O_EXCL		/* exclusive create */
#define B_CREATE_FILE		O_CREAT		/* create the file */
#define B_ERASE_FILE		O_TRUNC		/* erase the file's data */
#define B_OPEN_AT_END	   	O_APPEND	/* point to the end of the data */


/*----NODE FLAVORS--------------------------------*/

enum node_flavor {
  B_FILE_NODE=0x01,
  B_SYMLINK_NODE=0x02,
  B_DIRECTORY_NODE=0x04,
  B_ANY_NODE= 0x07
};


#endif
