#ifndef _BE_MATH_H_
#define _BE_MATH_H_

#ifndef M_E
#define M_E         2.7182818284590452354   /* e */
#endif
#ifndef M_LOG2E
#define M_LOG2E     1.4426950408889634074   /* log 2e */
#endif
#ifndef M_LOG10E
#define M_LOG10E    0.43429448190325182765  /* log 10e */
#endif
#ifndef M_LN2
#define M_LN2       0.69314718055994530942  /* log e2 */
#endif
#ifndef M_LN10
#define M_LN10      2.30258509299404568402  /* log e10 */
#endif
#ifndef M_PI
#define M_PI        3.14159265358979323846  /* pi */
#endif
#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923  /* pi/2 */
#endif
#ifndef M_1_PI
#define M_1_PI      0.31830988618379067154  /* 1/pi */
#endif
#ifndef M_PI_4
#define M_PI_4      0.78539816339744830962  /* pi/4 */
#endif
#ifndef M_2_PI
#define M_2_PI      0.63661977236758134308  /* 2/pi */
#endif
#ifndef M_2_SQRTPI
#define M_2_SQRTPI  1.12837916709551257390  /* 2/sqrt(pi) */
#endif
#ifndef M_SQRT2
#define M_SQRT2     1.41421356237309504880  /* sqrt(2) */
#endif
#ifndef M_SQRT1_2
#define M_SQRT1_2   0.70710678118654752440  /* 1/sqrt(2) */
#endif

#ifndef PI                      /* as in stroustrup */
#define PI  M_PI
#endif
#ifndef PI2
#define PI2  M_PI_2
#endif

__extern_c

/* the Berkeley standard math functions */

extern double erf(double);
extern double erfc(double);
extern double gamma(double);
extern double hypot(double, double);
extern int isnan(double);
extern int finite(double);
extern double j0(double);
extern double j1(double);
extern double jn(int, double);
extern double lgamma(double);
extern double y0(double);
extern double y1(double);
extern double yn(int, double);

extern double acosh(double);
extern double asinh(double);
extern double atanh(double);
extern double cbrt(double);
extern double logb(double);
extern double nextafter(double, double);
extern double remainder(double, double);
extern double scalb(double, double);

extern int matherr(struct exception *);

/*
 * IEEE Test Vector
 */
extern double significand(double);

/*
 * Functions callable from C, intended to support IEEE arithmetic.
 */
extern double copysign(double, double);
extern int ilogb(double);
extern double rint(double);
extern double scalbn(double, int);

/*
 * BSD math library entry points
 */
extern double drem(double, double);
extern double expm1(double);
extern double log1p(double);

__end_extern_c


#endif /* _BE_MATH_H_ */
