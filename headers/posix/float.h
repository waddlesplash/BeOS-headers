/*
 *	float.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __float__
#define __float__

#if __MC68K__

#define FLT_ROUNDS					1
#define FLT_RADIX						2

#define FLT_MANT_DIG				24
#define FLT_DIG							6
#define FLT_MIN_EXP					(-125)
#define FLT_MIN_10_EXP			(-37)
#define FLT_MAX_EXP					128
#define FLT_MAX_10_EXP			38
#define FLT_MAX							(* (float *) __float_max)
#define FLT_EPSILON					(* (float *) __float_epsilon)
#define FLT_MIN							(* (float *) __float_min)

extern unsigned char __float_min[], __float_max[], __float_epsilon[];

#if __option(IEEEdoubles)

#define DBL_MANT_DIG				53
#define DBL_DIG							15
#define DBL_MIN_EXP					(-1021)
#define DBL_MIN_10_EXP			(-307)
#define DBL_MAX_EXP					1024
#define DBL_MAX_10_EXP			308
#define DBL_MAX							(* (double *) __double_max)
#define DBL_EPSILON					(* (double *) __double_epsilon)
#define DBL_MIN							(* (double *) __double_min)

extern unsigned char __double_min[], __double_max[], __double_epsilon[];

#else

#define DBL_MANT_DIG				64
#define DBL_DIG							18
#define DBL_MIN_EXP					(-16382)
#define DBL_MIN_10_EXP			(-4931)
#define DBL_MAX_EXP					16384
#define DBL_MAX_10_EXP			4932
#define DBL_MAX							(* (double *) __extended_max)
#define DBL_EPSILON					(* (double *) __extended_epsilon)
#define DBL_MIN							(* (double *) __extended_min)

#endif

#define LDBL_MANT_DIG				64
#define LDBL_DIG						18
#define LDBL_MIN_EXP				(-16382)
#define LDBL_MIN_10_EXP			(-4931)
#define LDBL_MAX_EXP				16384
#define LDBL_MAX_10_EXP			4932
#define LDBL_MAX						(* (long double *) __extended_max)
#define LDBL_EPSILON				(* (long double *) __extended_epsilon)
#define LDBL_MIN						(* (long double *) __extended_min)

extern unsigned char __extended_min[], __extended_max[], __extended_epsilon[];

#endif

#if __POWERPC__

#define FLT_ROUNDS					1
#define FLT_RADIX						2

#define FLT_MANT_DIG				24
#define FLT_DIG							6
#define FLT_MIN_EXP					(-125)
#define FLT_MIN_10_EXP			(-37)
#define FLT_MAX_EXP					128
#define FLT_MAX_10_EXP			38
#define FLT_MAX							(* (float *) __float_max)
#define FLT_EPSILON					(* (float *) __float_epsilon)
#define FLT_MIN							(* (float *) __float_min)

extern unsigned char __float_min[], __float_max[], __float_epsilon[];

#define DBL_MANT_DIG				53
#define DBL_DIG							15
#define DBL_MIN_EXP					(-1021)
#define DBL_MIN_10_EXP			(-307)
#define DBL_MAX_EXP					1024
#define DBL_MAX_10_EXP			308
#define DBL_MAX							(* (double *) __double_max)
#define DBL_EPSILON					(* (double *) __double_epsilon)
#define DBL_MIN							(* (double *) __double_min)

#define LDBL_MANT_DIG				53
#define LDBL_DIG						15
#define LDBL_MIN_EXP				(-1021)
#define LDBL_MIN_10_EXP			(-307)
#define LDBL_MAX_EXP				1024
#define LDBL_MAX_10_EXP			308
#define LDBL_MAX						(* (long double *) __double_max)
#define LDBL_EPSILON				(* (long double *) __double_epsilon)
#define LDBL_MIN						(* (long double *) __double_min)

extern unsigned char __double_min[], __double_max[], __double_epsilon[];

#endif

#endif
