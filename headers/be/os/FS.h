/* ++++++++++
	FS.h
	Copyright (C) 1991-3 Be Inc.  All Rights Reserved.
	
	This file contains all includes necessary to use the native
	interface to the Be kernel file system

	Modification History (most recent first):
	16 aug 93	elr	New today
+++++ */

#ifndef _FS_H
#define _FS_H

#ifndef _SUPPORT_DEFS_H
#include "support/SupportDefs.h"
#endif

/*#include <drivers.h>*/

#define FILENAME_LEN	(32)		/* max length of a file name */
#define VOLNAME_LEN	(32)		/* max length of a volume name */
#define DRIVERNAME_LEN	(32)		/* max length of a driver name */

/*---------------------------------------------------------------------------*/
/* FILE_TYPE parcel struct */

struct file_descriptor {
	long vol_id;
	long dir_id;
	char name[32];
};

/*---------------------------------------------------------------------------*/
/*
 * Interfaces for kernel volume management calls
 */
/* ---
   volume info structure
--- */

struct vol_info {
	unsigned long	count;			/* total # sectors */
	unsigned long	used;			/* # sectors in use */
	int		id;			/* volume id */
	char		name[VOLNAME_LEN];	/* name */
	char		dev_name[DRIVERNAME_LEN];/* device driver name */
	char		is_removeable;		/* non-zero if removeable media */
	char		is_read_only;		/* non-zero if read only */
};

/* ----------
	get_vol_info is used to step though all volumes to get information
	about each volume.

	passed: 	info->id.
	returns:	information for next valid volume whose id is equal to
			or greater than passed id (and a return value of zero).
			If no more volumes, returns SYS_ERROR;
----- */
#ifdef __CPLUSPLUS__
extern "C" {
#endif		/* ifdef __CPLUSPLUS__ */
extern int 	get_vol_info (struct vol_info *);
#ifdef __CPLUSPLUS__
}
#endif		/* ifdef __CPLUSPLUS__ */


/*-------------------------------------------------------------------*/

struct	FileEntry
{
	char	FileName[FILENAME_LEN];	/*  0, 32		 */
	long	FirstAllocList;	   	/* 32, 36		 */
					/* If this is a Dir, this	 */
					/* is used to point to it	 */
	long	LastAllocList;	   	/* 36, 40		 */
	long	FileType;	   	/* 40, 44 		 */
					/* !! the FileType SDIR is	 */
					/* reserved for SubDir		 */
	long	CreationDate;	   	/* 44, 48		 */
	long	ModificationDate;  	/* 48, 52		 */
	long	LogicalSize;	   	/* 52, 56		 */
	long	PhysicalSize;	   	/* 56, 60		 */
	long	Creator;		/* 60, 64		 */
};

/*-------------------------------------------------------------------*/

struct	DirEntry
{
	char	DirName[FILENAME_LEN];	/*32			 */
	long    DirPointer;		/*36			 */
	long	Unused1;		/*40			 */
	long	FileType;		/*44			 */
	long	CreationDate;		/*48			 */
	long	ModificationDate;	/*52			 */
	long	Unused2;		/*56			 */
	long	Unused3;		/*60			 */
	long	Unused4;		/*64			 */
};					

/*-------------------------------------------------------------------*/

typedef struct FileEntry	*	FileEntryPtr;
typedef struct FileEntry		FileEntry;

/*-------------------------------------------------------------------*/

typedef struct DirEntry		*	DirEntryPtr; 
typedef struct DirEntry			DirEntry; 

/*-------------------------------------------------------------------*/

#endif
