/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/*
 *	float.h
 *	
 *		Copyright © 1995-1997 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __cfloat__
#define __cfloat__
#include <ansi_parms.h>
/* #pragma options align=native */
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

__namespace(__stdc_space(float))
__extern_c	/* 961212 KO */

#define FLT_ROUNDS					1  /* see fenv.h for changing rounding modes intel/mac only */
#define FLT_RADIX					2
#define FLT_MANT_DIG				24
#define FLT_DIG						6
#define FLT_MIN_EXP					(-125)
#define FLT_MIN_10_EXP				(-37)
#define FLT_MAX_EXP					128
#define FLT_MAX_10_EXP				38

/* begin 980107 Be-mani */

#if __dest_os == __be_os

typedef union {
	unsigned char c[4];
	float f;
} __fcu_t;

typedef union {
	unsigned char c[8];
	double d;
} __dcu_t;

typedef union {
	unsigned char c[8];
	double e;
} __ecu_t;

# define FLT_MAX					(__float_max.f)
# define FLT_EPSILON				(__float_epsilon.f)
# define FLT_MIN					(__float_min.f)

extern _IMPEXP_ROOT const __fcu_t __float_min, __float_max, __float_epsilon;

#else /* __dest_os */ /* end 980107 Be-mani */

# define FLT_MAX						(*(float *) __std(__float_max))
# define FLT_EPSILON					(*(float *) __std(__float_epsilon))
# define FLT_MIN						(*(float *) __std(__float_min))

long __float_min[], __float_max[], __float_epsilon[];
long __double_min[], __double_max[], __double_epsilon[];
long __extended_min[],__extended_max[],__extended_epsilon[];

#endif /* __dest_os */ /* 980107 Be-mani */

#if   __MC68K__ /* whether or not the format of a long double on 68K is
                   10 or 12 bytes, the range of permissble values is the 
                   same.  Note that the extra 16 bits on 68881 are just for
                   padding to keep data aligned along 32 bit boundaries,
                   not for additional precision.  Therefore this has
                   no effect on the constants in this file.
                */

#define LDBL_MANT_DIG				64
#define LDBL_DIG					18
#define LDBL_MIN_EXP				(-16381)
#define LDBL_MIN_10_EXP				(-4931)
#define LDBL_MAX_EXP				16384
#define LDBL_MAX_10_EXP				4932

 #if !(__option(IEEEdoubles))
	/* doubles are >= 10 bytes when IEEE doubles is not specified */
	
  #define DBL_MANT_DIG				    LDBL_MANT_DIG
  #define DBL_DIG						LDBL_DIG
  #define DBL_MIN_EXP					LDBL_MIN_EXP
  #define DBL_MIN_10_EXP				LDBL_MIN_10_EXP	
  #define DBL_MAX_EXP					LDBL_MAX_EXP
  #define DBL_MAX_10_EXP				LDBL_MAX_10_EXP
 #else
 
  #define DBL_MANT_DIG					53
  #define DBL_DIG						15
  #define DBL_MIN_EXP					(-1021)
  #define DBL_MIN_10_EXP				(-308)
  #define DBL_MAX_EXP					1024
  #define DBL_MAX_10_EXP				308

 #endif /* IEEEdoubles */

#else

 #define DBL_MANT_DIG					53
 #define DBL_DIG						15
 #define DBL_MIN_EXP					(-1021)
 #define DBL_MIN_10_EXP					(-308)
 #define DBL_MAX_EXP					1024
 #define DBL_MAX_10_EXP					308

 #define LDBL_MANT_DIG					DBL_MANT_DIG
 #define LDBL_DIG						DBL_DIG	
 #define LDBL_MIN_EXP					DBL_MIN_EXP	
 #define LDBL_MIN_10_EXP				DBL_MIN_10_EXP
 #define LDBL_MAX_EXP					DBL_MAX_EXP
 #define LDBL_MAX_10_EXP				DBL_MAX_10_EXP
#endif /* __MC68K__ */

/* begin 980107 Be-mani */

#if __dest_os == __be_os 

# define DBL_MAX		(__double_max.d)
# define DBL_EPSILON	(__double_epsilon.d)
# define DBL_MIN		(__double_min.d)

# define LDBL_MAX		(__extended_max.e)
# define LDBL_EPSILON	(__extended_epsilon.e)
# define LDBL_MIN		(__extended_min.e)

extern _IMPEXP_ROOT const __dcu_t __double_min, __double_max, __double_epsilon;
extern _IMPEXP_ROOT const __ecu_t __extended_min, __extended_max, __extended_epsilon;

#else /* __dest_os */ /* end 980107 Be-mani */

# define DBL_MAX						(* (double *) __std(__double_max))
# define DBL_EPSILON					(* (double *) __std(__double_epsilon))
# define DBL_MIN						(* (double *) __std(__double_min))
# define LDBL_MAX					(* (long double*) __std(__extended_max))
# define LDBL_EPSILON				(* (long double*) __std(__extended_epsilon))
# define LDBL_MIN					(* (long double*) __std(__extended_min))

#endif /* __dest_os */ /* 980107 Be-mani */

__end_extern_c	/* 961212 KO */

__end_namespace(stdc_space(float))

__import_stdc_into_std_space(float)

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
/* #pragma options align=reset */
#endif /* __cfloat__ */
/*     Change record
961212 KO	Added __extern_c wrapper to accomodate new x86 name mangling.
970801 Matt Fassiotto- this header is now as platform independent as possible, for
                       details on the platform dependent macros __double_max, etc... 
                       see the source file float.c in the MSL C common sources.
980107 Be-mani Merge in Be changes for floating constants and shared libs.
       
*/
