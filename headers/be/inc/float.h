/*
 *   float.h -- ANSI 
 *
 *   Constants that constrain float, double, and long double representation.
 *   NOTE: WEITEK does not support "long doubles". Thus all "long doubles" 
 *   are mapped to "doubles".
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _FLOAT_H
#define _FLOAT_H

#ifdef __CPLUSPLUS__
extern "C" {
#endif

#if (_IBM370 || _ENGINE)
/* Characteristics of floating types -- 370 fp format */
/* radix of float exponent representation */
#define FLT_RADIX    16

/* float addition rounds (1) or chops (0) */
#define FLT_ROUNDS   0

/* number of base-FLT_RADIX mant digits */
#define FLT_MANT_DIG                    6
#define DBL_MANT_DIG                    14
#if _IBM370
#define LDBL_MANT_DIG                   28
#else
#define LDBL_MANT_DIG                   14
#endif

/* minimum positive floating-point number x | 1.0 + x != 1.0 */
#define FLT_EPSILON	9.5367431640625e-7
#define DBL_EPSILON     2.22044604925031e-16
#define LDBL_EPSILON    ((long double)2.22044604925031e-16)

/* maximum number of decimal digits of floating_point precision  */
#define FLT_DIG                         6
#define DBL_DIG                         15
#if _IBM370
#define LDBL_DIG                        33
#else
#define LDBL_DIG                        15
#endif

/* minimum integer x | FLT_RADIX**x aproximates a normalized number */
#define FLT_MIN_EXP                     -63
#define DBL_MIN_EXP                     -63
#define LDBL_MIN_EXP                    -63

/* minimum normalized positive number */
#define FLT_MIN                         5.39760534693403e-79
#define DBL_MIN                         5.39760534693403e-79
#define LDBL_MIN                        ((long double)5.39760534693403e-79)

/* minimum integer x | 10**x aproximates a normalized number */
#define FLT_MIN_10_EXP                  -78
#define DBL_MIN_10_EXP                  -78
#define LDBL_MIN_10_EXP                 -78

/* maximum integer x | FLT_RADIX**x aproximates a normalized number */
#define FLT_MAX_EXP                     64
#define DBL_MAX_EXP                     64
#define LDBL_MAX_EXP                    64

/* maximum representable finite number */
#define FLT_MAX                         7.23700514597312e75
#define DBL_MAX                         7.23700557733226e75
#define LDBL_MAX                        ((long double)7.23700557733226e75)

/* maximum integer x | 10**x aproximates a normalized number */
#define FLT_MAX_10_EXP                  75
#define DBL_MAX_10_EXP                  75
#define LDBL_MAX_10_EXP                 75

#else   /*---------------------------- IEEE ---------------------------------*/

/* Characteristics of floating types -- ieee format */

/* radix of float exponent representation */
#define FLT_RADIX    2
#define DBL_RADIX    2
#define LDBL_RADIX   2

/* float addition rounding mode */
/* All IEEE machines that we support ROUNDs. */
#define FLT_ROUNDS   1
#define DBL_ROUNDS   1
#define LDBL_ROUNDS  1

/* Doubles or longdoubles? */
#if (_SPARC && _SOL) || (_UPA && !NOLONGDOUBLE)
    #define _D_or_LD(d,ld,lld) lld      /* Yes, extra long doubles.   */
#elif _MC68 || _HOBBIT || (_I386 && !_WEITEK)
    #define _D_or_LD(d,ld,lld) ld       /* Yes, long doubles.   */
#else
    #define _D_or_LD(d,ld,lld) d        /* No,  doubles only. */
#endif

/* number of base-FLT_RADIX mant digits */
#define FLT_MANT_DIG                    24
#define DBL_MANT_DIG                    53
#define LDBL_MANT_DIG _D_or_LD(DBL_MANT_DIG,64,113)

/* minimum positive floating-point number x | 1.0 + x != 1.0 */
#define FLT_EPSILON                     1.19209290e-07F
#define DBL_EPSILON                     2.2204460492503131e-16
#define LDBL_EPSILON _D_or_LD(2.2204460492503131e-16L,\
			      1.084202172485504434e-19L,\
			      1.925929944387235853055977942584927319E-34L)

/* maximum number of decimal digits of floating_point precision  */
#define FLT_DIG                         6
#define DBL_DIG                         15
#define LDBL_DIG _D_or_LD(DBL_DIG,19,33)

/* minimum integer x | FLT_RADIX**x aproximates a normalized number */
#define FLT_MIN_EXP                     -125
#define DBL_MIN_EXP                     -1021
#define LDBL_MIN_EXP _D_or_LD(DBL_MIN_EXP,-16381,-16381)

/* minimum normalized positive number */
#define FLT_MIN                         1.175494350822287508e-38F
#define DBL_MIN                         2.225073858507201383e-308
#define LDBL_MIN _D_or_LD(2.225073858507201383e-308L,\
			  3.3621031431120935064e-4932L,\
			  3.362103143112093506262677817321752603E-4932L)

/* minimum integer x | 10**x aproximates a normalized number */
#define FLT_MIN_10_EXP                  -37
#define DBL_MIN_10_EXP                  -307
#define LDBL_MIN_10_EXP _D_or_LD(DBL_MIN_10_EXP,-4932,-4932)

/* maximum integer x | FLT_RADIX**x aproximates a normalized number */
#define FLT_MAX_EXP                     128
#define DBL_MAX_EXP                     1024
#define LDBL_MAX_EXP _D_or_LD(DBL_MAX_EXP,16384,16384)

/* maximum representable finite number */
#define FLT_MAX                         3.402823466385288598e+38F
#define DBL_MAX                         1.797693134862315708e+308
#define LDBL_MAX _D_or_LD(1.797693134862315708e+308L,\
			  1.189731495357231765e+4932L,\
			  1.189731495357231765085759326628007016E+4932L)

/* maximum integer x | 10**x aproximates a normalized number */
#define FLT_MAX_10_EXP                  38
#define DBL_MAX_10_EXP                  308
#define LDBL_MAX_10_EXP _D_or_LD(DBL_MAX_10_EXP,4932,4932)

#endif  /* IEEE */

#if _MSDOS || _OS2 || _MSNT
#if __HIGHC__

/*  The routines defined in this include file emulate only 80387 MSC
 *  operations.  MSC reflects the same changes and info in emulated math
 *  modes, but the HIGH C math emulation uses higher precision formats
 *  and is not readily modified to meet the requirements of this emulation.
 */

/* 80387 Status Word format   */
#define SW_INVALID        0x0001  /* Invalid operation       */
#define SW_DENORMAL       0x0002  /* Denormalized operand    */
#define SW_ZERODIVIDE     0x0004  /* Zero divide             */
#define SW_OVERFLOW       0x0008  /* Overflow                */
#define SW_UNDERFLOW      0x0010  /* Underflow                               */
#define SW_INEXACT        0x0020  /* Precision       (Inexact result)        */
#define SW_STACKFAULT     0x0040  /* Floating point stack fault   */
#define SW_IR             0x0080  /* IR unmasked exception flag   */
#define SW_C0             0x0100  /* Condition bit 0         */
#define SW_C1             0x0200  /* Condition bit 1         */
#define SW_C2             0x0400  /* Condition bit 2         */
#define SW_TOS            0x3800  /* FP stack pointer (3 bits,0-7)*/
#define SW_C3             0x4000  /* Condition bit 3         */
#define SW_B              0x8000  /* B       unmasked exception flag */

#define MCW_EM            0x003f  /* interrupt Exception Masks */
#define     EM_INVALID    0x0001  /*  invalid               */
#define     EM_DENORMAL   0x0002  /* denormal       */
#define     EM_ZERODIVIDE 0x0004  /* zero divide    */
#define     EM_OVERFLOW   0x0008  /* overflow       */
#define     EM_UNDERFLOW  0x0010  /* underflow      */
#define     EM_INEXACT    0x0020  /*  inexact (precision) */
#define     EM_STACKFAULT 0x0040  /* stack fault (always 1) */

#define MCW_RC  0x0c00  /* Rounding Control */
#define     RC_CHOP     0x0c00  /*      chop */
#define     RC_UP       0x0800  /*      up */
#define     RC_DOWN     0x0400  /*      down */
#define     RC_NEAR     0x0000  /*      near */

#define MCW_PC          0x0300  /*      Precision Control  */
#define     PC_24            0x0000  /* 24 bits */
#define     PC_53            0x0200  /* 53 bits */
#define     PC_64            0x0300  /* 64 bits */

#define MCW_IC          0x1000  /* Rounding Control              */
#define IC_AFFINE            0x1000  /* affine, uses + and - infinity   */
#define IC_PROJECTIVE        0x0000  /* 80387 ONLY!! Proective infinity */

/* This is equivalent to the state left by fninit, which is also the
   condition at program startup.  Used by _fpreset to reset the state of the
   coprocessor.
*/
#define CW_DEFAULT (IC_AFFINE|RC_NEAR|PC_64|MCW_EM|EM_STACKFAULT)


/*  EMULATION WORDS  */
/* user Status Word bit definitions */
#define    ESW_INVALID          0x0001  /*   invalid operation          */
#define    ESW_DENORMAL         0x0002  /*   denormal                   */
#define    ESW_ZERODIVIDE       0x0004  /*   zero divide                */
#define    ESW_OVERFLOW         0x0008  /*   overflow                   */
#define    ESW_UNDERFLOW        0x0010  /*   underflow                  */
#define    ESW_INEXACT          0x0020  /*   inexact (precision)        */

/* invalid subconditions (SW_INVALID also set)                          */

#define SW_UNEMULATED       0x0040 /* unemulated instruction       */
                                   /*      not used in 1/15/90 version */
#define SW_SQRTNEG          0x0080      /* square       root of a neg   number  */
/* 1/15/90 - TRUTH:MSC5.1-NEGATIVE SQRT results in INEXACT and C2 set   */
/*                      indicating      first arg is    Normal, error return is */
/*                      underflow.                                              */
#define SW_STACKOVERFLOW    0x0200      /* FP stack overflow            */
#define SW_STACKUNDERFLOW   0x0400      /* FP stack underflow           */


/* STATUS WORD for MSC emulation ****************************************/
#ifdef _REENTRANT
    #include <static.h>
#else
    extern unsigned short int _mwfp_status;
#endif

/* prototypes ***********************************************************/
extern unsigned short int _clear87(void);
extern unsigned short int _control87(unsigned short int __cw, unsigned short int __mask);
extern void     _fpreset(void);
extern unsigned short int _status87(void);
extern unsigned short int _stat387(void);

/*  required assembler prototypes **************************************/
extern void _fpclear87(void);   /*  clear   the 80387 exception bits */
                                /* get/set the 80387 status word */
extern void _fpgetcw(unsigned short int *__fpcntrl);
extern void _fpsetcw(unsigned short int *__fpcntrl);

extern unsigned short int _fpgetsw(void);  /* get the 80387 status word */
extern void _fpinit(void);                 /* reset the 80387 */

#endif /*__HIGHC__ */
#endif /*_MSDOS or _OS2 or _MSNT */

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_FLOAT_H*/
