/*
 *   math.h -- ANSI 
 *
 *   Mathematical functions and constants.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _MATH_H
#define _MATH_H
#pragma push_align_members(64);

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#if defined(__PENPOINT__) && (!defined(EDOM) || !defined(ERANGE))
    #ifndef GO_INCLUDED
	#include <go.h>
    #endif
    #ifndef CLSMGR_INCLUDED
	#include <clsmgr.h>
    #endif
    #ifndef GOMATH_INCLUDED
	#include <gomath.h>
    #endif

    #define StsToErrno(sts) ((U32)(sts)&~flag31)

    #ifndef EDOM
	#define EDOM    StsToErrno(stsMathDomain)   /* Argument too large */
    #endif

    #ifndef ERANGE
	#define ERANGE  StsToErrno(stsMathRange)    /* Result too large */
    #endif
#else	/* ! __PENPOINT__ */
    #ifndef EDOM
	#define EDOM     33     /* errno's value for out of domain */
    #endif

    #ifndef ERANGE
	#define ERANGE   34     /* errno's value for out of range  */
    #endif
#endif

#if defined(_UPA)
#define HUGE_VAL 1.7976931348623157e+308
#else
#define HUGE_VAL (_fphuge[0])
#endif
extern double _fphuge[];


#define _PI 3.141592653589793238462643383279502884197169399
#define _E  2.718281828459045235360287471352662497757247093


extern double cos(double __x);
extern double sin(double __x);
extern double tan(double __x);
extern double atan(double __x);

extern double exp(double __x);
extern double log(double __x);
extern double sqrt(double __x);

extern double acos(double __x);
extern double asin(double __x);

extern double cosh(double __x);
extern double sinh(double __x);
extern double tanh(double __x);

extern double log10(double __x);

extern double fabs(double __x);

extern double ceil(double __x);
extern double floor(double __x);

extern double atan2(double __y, double __x);

extern double frexp(double __value, int *__exp);
extern double ldexp(double __x, int __exp);
extern double modf(double __value, double *__iptr);

extern double pow(double __x, double __y);

extern double fmod(double __x, double __y);

#if _AM29K
extern float cosf(float __x);
extern float sinf(float __x);
extern float tanf(float __x);
extern float atanf(float __x);

extern float expf(float __x);
extern float logf(float __x);
extern float sqrtf(float __x);

extern float acosf(float __x);
extern float asinf(float __x);

extern float coshf(float __x);
extern float sinhf(float __x);
extern float tanhf(float __x);

extern float log10f(float __x);

extern float fabsf(float __x);

extern float ceilf(float __x);
extern float floorf(float __x);

extern float atan2f(float __y, float __x);

extern float frexpf(float __value, int *__exp);
extern float ldexpf(float __x, int __exp);

extern float powf(float __x, float __y);

extern float fmodf(float __x, float __y);
#endif

#ifndef _NA_H
    #include <_na.h>
#endif

#ifndef _COMPLEX_DEFINED
    #define _COMPLEX_DEFINED
    #define _HUGE HUGE_VAL

    #if _HOBBIT            /* conforms to WATCOM member names */
	struct _complex { double real,imag; };
	#define _CPLXREAL(c) ((c).real)
	#define _CPLXIMAG(c) ((c).imag)
    #else
	struct _complex { double x,y; };
	#define _CPLXREAL(c) ((c).x)
	#define _CPLXIMAG(c) ((c).y)
    #endif

    #if __HIGHC__
	#if !defined(__CPLUSPLUS__) && (_NA_NAMES || _MSDOS)
	    #define complex _complex
	#endif
	#define HUGE HUGE_VAL
    #endif
#endif

/* definition of exception struct - this struct is passed to the matherr
 * function when a floating point exception is detected
 */

#ifndef _EXCEPTION_DEFINED
    struct _exception {
	int type;           /* exception type - see constants below */
	char *name;         /* name of function where error occured */
	double arg1;        /* first argument to function           */
	double arg2;        /* second argument (if any) to function */
	double retval;      /* value to be returned by function     */
	} ;

/* Constant definitions for the exception type passed in the exception struct*/
	#define _DOMAIN      1   /* argument domain error     */
	#define _SING        2   /* argument singularity      */
	#define _OVERFLOW    3   /* overflow range error      */
	#define _UNDERFLOW   4   /* underflow range error     */
	#define _TLOSS       5   /* total loss of precision   */
	#define _PLOSS       6   /* partial loss of precision */
    #define _EXCEPTION_DEFINED
    #if __HIGHC__
	#if _NA_NAMES || _MSDOS
	    #define exception _exception
	#endif
	#define DOMAIN      1   /* argument domain error                */
	#define SING        2   /* argument singularity                 */
	#define OVERFLOW    3   /* overflow range error                 */
	#define UNDERFLOW   4   /* underflow range error                */
	#define TLOSS       5   /* total loss of precision              */
	#define PLOSS       6   /* partial loss of precision            */
    #endif
#endif

#define _NULL_MATHERR (int (*)())0
int _matherr (struct _exception *__s);
extern void _set_matherr( int (*rtn)(struct _exception *err_info) );

extern double _cabs(struct _complex);
extern double _hypot(double __x, double __y);
extern double _log2(double __x);

/* Bessel function routines  */

double _yn(int __n, double __x);
double _jn(int __n, double __x);
double _y0(double __x);
double _y1(double __x);
double _j0(double __x);
double _j1(double __x);

/* inverse hyperbolic trigonometric functions */
extern double _atanh(double __x);
extern double _acosh(double __x);
extern double _asinh(double __x);

#include <_na.h>
#if _NA_NAMES

    /* non-ansi versions of math functions */
    _NA(cabs)
    _NA(hypot)
    _NA(log2)
    _NA(matherr)
    _NA(yn)
    _NA(jn)
    _NA(y0)
    _NA(y1)
    _NA(j0)
    _NA(j1)
    _NA(atanh)
    _NA(acosh)
    _NA(asinh)
#elif _MSDOS && __HIGHC__
    extern double cabs(struct complex __z);
    extern double hypot(double __x, double __y);
    extern double log2(double __x);
    extern int matherr (struct exception *__s);
    extern double yn(int __n, double __x);
    extern double jn(int __n, double __x);
    extern double y0(double __x);
    extern double y1(double __x);
    extern double j0(double __x);
    extern double j1(double __x);
    extern double atanh(double __x);
    extern double acosh(double __x);
    extern double asinh(double __x);
#endif /*_NA_NAMES*/

#if (_MSDOS || _MSNT || _OS2)

    /* floating point format conversion   */
    int _fieeetomsbin(float *__x, float *__x1);
    int _fmsbintoieee(float *__x, float *__x1);
    int _dieeetomsbin(double *__x, double *__x1);
    int _dmsbintoieee(double *__x, double *__x1);

    int _matherrx (struct _exception *__s);

    #include <_na.h>
    #if _NA_NAMES
	_NA(matherrx)
	_NA(fieeetomsbin)
	_NA(fmsbintoieee)
	_NA(dieeetomsbin)
	_NA(dmsbintoieee)
    #elif _MSDOS && __HIGHC__
	extern int matherrx (struct exception *__s);
	extern int fieeetomsbin(float *__x, float *__x1);
	extern int fmsbintoieee(float *__x, float *__x1);
	extern int dieeetomsbin(double *__x, double *__x1);
	extern int dmsbintoieee(double *__x, double *__x1);
    #endif /*_NA_NAMES*/

#endif /*_MSDOS*/

#if __HIGHC__
extern double atof(const char *__nptr);
#endif

#ifdef __CPLUSPLUS__
}
#endif
#pragma pop_align_members();
#endif /*_MATH_H*/
