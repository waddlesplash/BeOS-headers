//******************************************************************************
//
//	File:		StorageDefs.h
//
//	Copyright 1994-96 Be Incorporated. All Rights Reserved.
//
//******************************************************************************/


#ifndef _STORAGE_DEFS_H
#define	_STORAGE_DEFS_H

/*-----------------------------------------------------------------*/
typedef long 	record_id;
typedef long 	database_id;
typedef	long	field_key;

/*-----------------------------------------------------------------*/
/* File open mode 
/* The latter two (only) are used as args to Open().
 * All three are potential return values from IsOpen()
 */
enum  {
	B_FILE_NOT_OPEN=-1,
	B_READ_ONLY=0,
	B_READ_WRITE,
	B_EXCLUSIVE } ;

/* File seek_mode constants */
enum {
	B_SEEK_TOP,
	B_SEEK_MIDDLE,
	B_SEEK_BOTTOM };

/*-----------------------------------------------------------------*/
/* B_REF_TYPE struct */

struct record_ref {
	record_id	record;
	database_id	database;

	int			operator==(record_ref) const;
	int			operator!=(record_ref) const;
};

inline int record_ref::operator==(record_ref r) const
{
	return((record == r.record) && (database == r.database));
}

inline int record_ref::operator!=(record_ref r) const
{
	return((record != r.record) || (database != r.database));
}

#endif
