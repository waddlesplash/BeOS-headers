/*
 *   new.h
 *
 *   C++ operator new and related functions.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

/*   $Id: new.h,v 1.1 1994/08/19 17:51:23 ming Exp $ */


#ifndef __NEW_H
#define __NEW_H

#ifdef __CPLUSPLUS__

// The "new handler" will be called whenever operator new is unable to
// allocate memory.  After it returns, operator new will return NULL (0).
extern void (*set_new_handler(void(*)(void)))(void);

#endif __CPLUSPLUS__

#endif __NEW_H

/**          Copyright (c) 1991-1992, MetaWare Incorporated            **/

