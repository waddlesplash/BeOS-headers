/*
 *   sizet.h -- extra-ANSI 
 *
 *   Declare the type for size_t.
 *
 *           Copyright (c) 1990-1991, MetaWare Incorporated
 */

#ifndef _SIZET_H
#define _SIZET_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#ifndef _SIZE_T_DEFINED
#   define _SIZE_T_DEFINED _SIZE_T_DEFINED
#   if _SUN || _BSD && !_RT && !_I386 || _ENGINE
	typedef int size_t;	/* Must match /usr/include/sys/types.h */
#   elif _SOL || _UPA
	typedef	unsigned int size_t;
#   elif _IBMESA || _BSD && _I386
			typedef unsigned long int size_t;
#   elif (_RT && _BSD) || _IBM370 || (_AIX && _I386)
#	if __HIGHC__
			typedef long int size_t;
#	else
			typedef unsigned long int size_t;
#	endif
#   elif _NEXT
			typedef unsigned long int size_t;
#   elif _ATT && _MC68	/* HP system V has two definitions of size_t. */
	#ifndef __STDC__
			typedef int size_t;
	#else
			typedef unsigned int size_t;
	#endif
#   elif _NEWS && _MC68
	typedef long size_t;
#   elif _RS6000
	typedef unsigned long size_t;
#   else
       typedef unsigned int size_t;
#   endif
#endif

#ifdef __CPLUSPLUS__
}
#endif

#endif /*_SIZET_H*/
