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
/* B_REF_TYPE struct */

struct record_ref {
	record_id	record;
	database_id	database;
};


#endif
