/*
 * Copyright (c) 1993 MetaWare, Incorporated
 */

#ifndef _MWCTOR_H
#define _MWCTOR_H

#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

typedef struct {
       unsigned long	init_level;	/* C++ initialization level */
       void (*ct)();			/* pointer to constructor function */
       unsigned long	slop;		/* not used now, maybe used later. */
       } ct_elem, *ct_array;

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();

#endif
