/*
 *   memory.h -- extra-ANSI 
 *
 *   Functions for moving and comparing portions of memory.
 *
 *           Copyright (c) 1990-1991, MetaWare Incorporated
 */

#ifndef _MEMORY_H
#define _MEMORY_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

extern void * _memccpy(void *,void *,int ,unsigned int );
extern int _memicmp(const void *,const void *,unsigned int );
extern void _movedata(unsigned int ,unsigned int ,unsigned int ,unsigned int ,unsigned int );

#include <sizet.h>

#if (__HIGHC__ && _IBM370 && _UNIXLIB)	/* Agree with AIX/ESA 370. */
    extern void * memccpy(void *,const void *,int ,size_t);
#endif

#include <_na.h>
#if _NA_NAMES
    #if !(_IBM370 && _UNIXLIB)
	_NA(memccpy)
    #endif
    _NA(memicmp)
    _NA(movedata)
#elif _MSDOS && __HIGHC__
    extern void * memccpy(void *,void *,int ,unsigned int );
    extern int memicmp(const void *,const void *,unsigned int );
    extern void movedata(unsigned int ,unsigned int ,unsigned int,
	    unsigned int ,unsigned int );
#endif /* _NA_NAMES */

extern void * memchr(const void *,int ,size_t);
extern void * memset(void *,int ,size_t);
extern void * memcpy(void *,const void *,size_t);

extern int memcmp(const void *__s1, const void *__s2, size_t __n);

#ifdef __CPLUSPLUS__
}
#endif
#endif /* _MEMORY_H */
