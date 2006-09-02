/*
	Copyright (c) 2003-04, Thomas Kurschel
	Distributed under the terms of the MIT License.

	Part of PnP Core
	
	Wrapper to abstract different BeOS versions.
*/
	
#ifndef _R5_WRAPPER_H
#define _R5_WRAPPER_H

#include <size_t.h>
#include <Errors.h>


// missing exports and constants under R5

#ifndef B_BEOS_VERSION_DANO
#define B_BEOS_VERSION_DANO 0x0510
#endif

#if B_BEOS_VERSION < B_BEOS_VERSION_DANO

// string.h
size_t strlcat( char *dst, const char *src, size_t len );
size_t strlcpy( char *dst, const char *src, size_t len );

// stdlib.h
char *realpath( const char *path, char *resolved );

// Errors.h
enum {
	B_DEV_INVALID_PIPE = B_DEV_DOOR_OPEN + 1,
	B_DEV_CRC_ERROR,
	B_DEV_STALLED,
	B_DEV_BAD_PID,
	B_DEV_UNEXPECETD_PID,
	B_DEV_DATA_OVERRUN,
	B_DEV_DATA_UNDERRUN,
	B_DEV_FIFO_OVERRUN,
	B_DEV_FIFO_UNDERRUN,
	B_DEV_PENDING,
	B_DEV_MULTIPLE_ERRORS,
	B_DEV_TOO_LATE
};

#endif

#ifndef PURE_MALLOC

// debugging: rename malloc function to debug version
#define malloc dmalloc
#define free dfree
#define strdup dstrdup
#define calloc dcalloc
#define realloc drealloc

// if you need to undef free temporarily, use stdfree to redefine it
#define stdfree dfree

extern void *dmalloc(size_t num_bytes);
extern void *drealloc(void * old_ptr, size_t new_size);
extern void *dcalloc(size_t num_elements, size_t size);
extern void dfree(void *ptr);

#endif

#endif
