/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_EXTMATH_H
#define MSIPL_EXTMATH_H

#include <mcompile.h>

#include MOD_C_INCLUDE(stdio)
#include MOD_C_INCLUDE(assert)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

/*
#ifdef MSIPL_USE_EXTERNAL_MATHLIB
extern "C" {
#endif

//#include MOD_C_INCLUDE(math.h) //961223 bkoz

#ifdef MSIPL_USE_EXTERNAL_MATHLIB
}
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif
*/


//
// For reporting errors
//
void  __msipl_report_error (const char* s);

//
// Extended math Library
//
#ifndef MSIPL_USE_EXTERNAL_MATHLIB

float __msipl_sin  (float);
float __msipl_cos  (float);
float __msipl_tan  (float);
float __msipl_exp  (float);
float __msipl_log  (float);
float __msipl_sqrt (float);
float __msipl_asin (float);
float __msipl_acos (float);
float __msipl_sinh (float);
float __msipl_cosh (float);
float __msipl_tanh (float);
float __msipl_atan (float);
float __msipl_cotan (float);
float __msipl_log10 (float);
float __msipl_pow  (float, float);
float __msipl_atan2 (float, float);

long double __msipl_sin  (long double);
long double __msipl_cos  (long double);
long double __msipl_tan  (long double);
long double __msipl_exp  (long double);
long double __msipl_log  (long double);
long double __msipl_sqrt (long double);
long double __msipl_asin (long double);
long double __msipl_acos (long double);
long double __msipl_sinh (long double);
long double __msipl_cosh (long double);
long double __msipl_tanh (long double);
long double __msipl_atan (long double);
long double __msipl_cotan (long double);
long double __msipl_log10 (long double);
long double __msipl_pow  (long double, long double);
long double __msipl_atan2 (long double, long double);

double __msipl_sin  (double);
double __msipl_cos  (double);
double __msipl_tan  (double);
double __msipl_exp  (double);
double __msipl_log  (double);
double __msipl_sqrt (double);
double __msipl_asin (double);
double __msipl_acos (double);
double __msipl_sinh (double);
double __msipl_cosh (double);
double __msipl_tanh (double);
double __msipl_atan (double);
double __msipl_cotan (double);
double __msipl_log10 (double);
double __msipl_pow  (double, double);
double __msipl_atan2 (double, double);

#else

#define  __msipl_pow    pow
#define  __msipl_sin    sin
#define  __msipl_cos    cos
#define  __msipl_tan    tan
#define  __msipl_exp    exp
#define  __msipl_log    log
#define  __msipl_sqrt   sqrt
#define  __msipl_asin   asin
#define  __msipl_acos   acos
#define  __msipl_sinh   sinh
#define  __msipl_cosh   cosh
#define  __msipl_tanh   tanh
#define  __msipl_atan   atan
#define  __msipl_cotan  cotan
#define  __msipl_log10  log10
#define  __msipl_atan2  atan2

#endif /* MSIPL_USE_EXTERNAL_MATHLIB */

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_EXTMATH_H */

//961210 bkoz added alignment wrapper
//961223 bkoz removed math.h header due to conflict with iostreams/fp.h
