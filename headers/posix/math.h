/*
 *	math.h
 *	
 *		Copyright © 1995 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __math__
#define __math__

#pragma options align=mac68k
#pragma direct_destruction off

#include <ansi_parms.h>
#include <be_math.h>       /* useful constants like M_PI, etc */

#define HUGE_VAL	(*__huge_val)

extern const double *__huge_val;

/*
 *  Set the following define to 1 to force the ANSI math header to inline FPU
 *	calls whenever possible.  This behaviour is not ANSI compatible, so should
 *	be used with care.
 *	
 *	NB: on 680x0 macs, using inlines in conjunction with 8byte doubles will
 *	not work correctly.
 */

#if !defined(_INLINE_FPU_CALLS_) && __MC68K__
#define _INLINE_FPU_CALLS_	0
#endif

		/* function prototype declarations (common to both 68K and PPC) */

__extern_c

		/* float declarations */
float cosf(float);
float sinf(float);
float tanf(float);
float acosf(float);
float asinf(float);
float atanf(float);
float atan2f(float, float);
float coshf(float);
float sinhf(float);
float tanhf(float);
float expf(float);
float frexpf(float, int *);
float ldexpf(float, int);
float logf(float);
float log10f(float);
float modff(float, float*);
float fabsf(float);
float powf(float, float);
float sqrtf(float);
float ceilf(float);
float floorf(float);
float fmodf(float, float);

__end_extern_c

#if __POWERPC__

__extern_c

		/* double declarations */
double cos(double);
double sin(double);
double tan(double);
double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double cosh(double);
double sinh(double);
double tanh(double);
double exp(double);
double frexp(double, int *);
double ldexp(double, int);
double log(double);
double log10(double);
double modf(double, double *);
double pow(double, double);
double sqrt(double);
double ceil(double);
double floor(double);
double fmod(double, double);

__end_extern_c

#ifdef __cplusplus
		/* double inlines, for C++ */
inline double fabs(double x)	{ return __fabs(x); }
#else
		/* double macro overrides, for C */
double fabs(double);
#define fabs(x)			__fabs(x)
#endif

#else	/* !__POWERPC__ */

__extern_c

		/* long double declarations */
long double cosl(long double);
long double sinl(long double);
long double tanl(long double);
long double acosl(long double);
long double asinl(long double);
long double atanl(long double);
long double atan2l(long double, long double);
long double coshl(long double);
long double sinhl(long double);
long double tanhl(long double);
long double expl(long double);
long double frexpl(long double, int *);
long double ldexpl(long double, int);
long double logl(long double);
long double log10l(long double);
long double modfl(long double, long double *);
long double fabsl(long double);
long double powl(long double, long double);
long double sqrtl(long double);
long double ceill(long double);
long double floorl(long double);
long double fmodl(long double, long double);

__end_extern_c
		
#if _INLINE_FPU_CALLS_ && __MC68881__

__extern_c

		/* call the FPU directly (NOT ANSI COMPATIBLE) */
long double _fpucos(long double:__FP0):__FP0                    = { 0xF200,0x001D };
long double _fpusin(long double:__FP0):__FP0                    = { 0xF200,0x000E };
long double _fputan(long double:__FP0):__FP0                    = { 0xF200,0x000F };
long double _fpuacos(long double:__FP0):__FP0                   = { 0xF200,0x001C };
long double _fpuasin(long double:__FP0):__FP0                   = { 0xF200,0x000C };
long double _fpuatan(long double:__FP0):__FP0                   = { 0xF200,0x000A };
long double _fpucosh(long double:__FP0):__FP0                   = { 0xF200,0x0019 };
long double _fpusinh(long double:__FP0):__FP0                   = { 0xF200,0x0002 };
long double _fputanh(long double:__FP0):__FP0                   = { 0xF200,0x0009 };
long double _fpuexp(long double:__FP0):__FP0                    = { 0xF200,0x0010 };
long double _fpuldexp(long double:__FP0,long:__D0):__FP0        = { 0xF200,0x4026 };
long double _fpulog(long double:__FP0):__FP0                    = { 0xF200,0x0014 };
long double _fpulog10(long double:__FP0):__FP0                  = { 0xF200,0x0015 };
long double _fpufabs(long double:__FP0):__FP0                   = { 0xF200,0x0018 };
long double _fpusqrt(long double:__FP0):__FP0                   = { 0xF200,0x0004 };
long double _fpufmod(long double:__FP0,long double:__FP1):__FP0 = { 0xF200,0x0421 };

__end_extern_c

#ifdef __cplusplus
		/* double inlines, for C++ */
inline double cos(double x)							{ return (_fpucos(x));     }
inline double sin(double x)							{ return (_fpusin(x));     }
inline double tan(double x)							{ return (_fputan(x));     }
inline double acos(double x)						{ return (_fpuacos(x));    }
inline double asin(double x)						{ return (_fpuasin(x));    }
inline double atan(double x)						{ return (_fpuatan(x));    }
inline double cosh(double x)						{ return (_fpucosh(x));    }
inline double sinh(double x)						{ return (_fpusinh(x));    }
inline double tanh(double x)						{ return (_fputanh(x));    }
inline double exp(double x)							{ return (_fpuexp(x));     }
inline double ldexp(double x, int y)		{ return (_fpuldexp(x,y)); }
inline double log(double x)							{ return (_fpulog(x));     }
inline double log10(double x)						{ return (_fpulog10(x));   }
inline double fabs(double x)						{ return (_fpufabs(x));    }
inline double sqrt(double x)						{ return (_fpusqrt(x));    }
inline double fmod(double x, double y)	{ return (_fpufmod(x,y));  }
#else
		/* double macro overrides, for C */
double cos(double);
double sin(double);
double tan(double);
double acos(double);
double asin(double);
double atan(double);
double cosh(double);
double sinh(double);
double tanh(double);
double exp(double);
double ldexp(double, int);
double log(double);
double log10(double);
double fabs(double);
double sqrt(double);
double fmod(double, double);
#define cos(x)				_fpucos(x)
#define sin(x)				_fpusin(x)
#define tan(x)				_fputan(x)
#define acos(x)				_fpuacos(x)
#define asin(x)				_fpuasin(x)
#define atan(x)				_fpuatan(x)
#define cosh(x)				_fpucosh(x)
#define sinh(x)				_fpusinh(x)
#define tanh(x)				_fputanh(x)
#define exp(x)				_fpuexp(x)
#define ldexp(x,n)		_fpuldexp(x,n)
#define log(x)				_fpulog(x)
#define log10(x)			_fpulog10(x)
#define fabs(x)				_fpufabs(x)
#define sqrt(x)				_fpusqrt(x)
#define fmod(x,y)			_fpufmod(x,y)
#endif

#elif __option(IEEEdoubles)

__extern_c

		/* ANSI compatible double overrides */
double cosd(double);
double sind(double);
double tand(double);
double acosd(double);
double asind(double);
double atand(double);
double coshd(double);
double sinhd(double);
double tanhd(double);
double expd(double);
double ldexpd(double, int);
double logd(double);
double log10d(double);
double fabsd(double);
double sqrtd(double);
double fmodd(double, double);

__end_extern_c

#ifdef __cplusplus
		/* double inlines, for C++ */
inline double cos(double x)							{ return (cosd(x));     }
inline double sin(double x)							{ return (sind(x));     }
inline double tan(double x)							{ return (tand(x));     }
inline double acos(double x)						{ return (acosd(x));    }
inline double asin(double x)						{ return (asind(x));    }
inline double atan(double x)						{ return (atand(x));    }
inline double cosh(double x)						{ return (coshd(x));    }
inline double sinh(double x)						{ return (sinhd(x));    }
inline double tanh(double x)						{ return (tanhd(x));    }
inline double exp(double x)							{ return (expd(x));     }
inline double ldexp(double x, int y)		{ return (ldexpd(x,y)); }
inline double log(double x)							{ return (logd(x));     }
inline double log10(double x)						{ return (log10d(x));   }
inline double fabs(double x)						{ return (fabsd(x));    }
inline double sqrt(double x)						{ return (sqrtd(x));    }
inline double fmod(double x, double y)	{ return (fmodd(x,y));  }
#else
		/* double macro overrides, for C */
double cos(double);
double sin(double);
double tan(double);
double acos(double);
double asin(double);
double atan(double);
double cosh(double);
double sinh(double);
double tanh(double);
double exp(double);
double ldexp(double, int);
double log(double);
double log10(double);
double fabs(double);
double sqrt(double);
double fmod(double, double);
#define cos(x)				cosd(x)
#define sin(x)				sind(x)
#define tan(x)				tand(x)
#define acos(x)				acosd(x)
#define asin(x)				asind(x)
#define atan(x)				atand(x)
#define cosh(x)				coshd(x)
#define sinh(x)				sinhd(x)
#define tanh(x)				tanhd(x)
#define exp(x)				expd(x)
#define ldexp(x,n)		ldexpd(x,n)
#define log(x)				logd(x)
#define log10(x)			log10d(x)
#define fabs(x)				fabsd(x)
#define sqrt(x)				sqrtd(x)
#define fmod(x,y)			fmodd(x,y)
#endif

#else	/* we don't have FPU inlines, nor do we have 8 byte IEEE Doubles */

__extern_c

double cos(double);
double sin(double);
double tan(double);
double acos(double);
double asin(double);
double atan(double);
double cosh(double);
double sinh(double);
double tanh(double);
double exp(double);
double ldexp(double, int);
double log(double);
double log10(double);
double fabs(double);
double sqrt(double);
double fmod(double, double);

__end_extern_c

#endif	/* _INLINE_FPU_CALLS_ && __MC68881__ */

#if __option(IEEEdoubles)

__extern_c

double atan2d(double, double);
double frexpd(double, int *);
double modfd(double, double *);
double powd(double, double);
double ceild(double);
double floord(double);

__end_extern_c

#ifdef __cplusplus
		/* double inlines, for C++ */
inline double atan2(double x, double y)				{ return (atan2d(x,y));   }
inline double frexp(double x, int *exp)				{ return (frexpd(x,exp)); }
inline double modf(double x, double *iptr)		{ return (modfd(x,iptr)); }
inline double pow(double x, double y)					{ return (powd(x,y));     }
inline double ceil(double x)									{ return (ceild(x));      }
inline double floor(double x)									{ return (floord(x));     }
#else
		/* double macro overrides, for C */
double atan2(double, double);
double frexp(double, int *);
double modf(double, double *);
double pow(double, double);
double ceil(double);
double floor(double);
#define atan2(x,y)		atan2d(x,y)
#define frexp(x,exp)	frexpd(x,exp)
#define modf(x,iptr)	modfd(x,iptr)
#define pow(x,y)			powd(x,y)
#define ceil(x)				ceild(x)
#define floor(x)			floord(x)
#endif

#else

__extern_c

double atan2(double, double);
double frexp(double, int *);
double modf(double, double *);
double pow(double, double);
double ceil(double);
double floor(double);

__end_extern_c

#endif

#endif	/* __POWERPC__ */

#pragma options align=reset
#pragma direct_destruction reset

#endif
