/* ++++++++++
	FILE:	be_string.h
	REVS:	$Revision: 1.2 $
	NAME:	pierre
	DATE:	Mon Dec 16 10:41:32 PST 1996
	Copyright (c) 1996 by Be Incorporated.  All Rights Reserved.
+++++ */

#ifndef _BE_STRING_H_
#define _BE_STRING_H_

/* special functions to handle non cachable memory operations
   */
#ifdef __cplusplus
extern "C" {
#endif

void * memcpy_c2nc(void * dst, const void * src, size_t len);
void * memcpy_nc2c(void * dst, const void * src, size_t len);
void * memcpy_nc2nc(void * dst, const void * src, size_t len);
void * memmove_nc(void * dst, const void * src, size_t len);
void * memset_nc(void * dst, int val, size_t len);
	
#ifdef __cplusplus
}
#endif

#endif


