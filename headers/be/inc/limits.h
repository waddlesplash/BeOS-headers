/*
 *   limits.h -- ANSI 
 *
 *   Constants that constrain the representation of numerical values.
 *
 *           Copyright (c) 1990, MetaWare Incorporated
 */

#ifndef _LIMITS_H
#define _LIMITS_H	

#ifdef __CPLUSPLUS__
extern "C" {
#endif

/* number of bits for smallest object (byte) */
#define CHAR_BIT                         8

#if  _I860 || (_I386 && _ATT4) || _UPA
#    define __SIGNED_CHARS 1
#else
#    define __SIGNED_CHARS 0
#endif

/* maximum value for an object of type char */
#define CHAR_MAX ('\xff' > 0 ? 255 : 127)

/* minimum value for an object of type char */
#define CHAR_MIN ('\xff' > 0 ? 0 : -128)

/* maximum value for an object of type signed char */
#define SCHAR_MAX                     +127

/* minimum value for an object of type signed char */
#define SCHAR_MIN                     -128

/* maximum value for an object of type unsigned char */
#define UCHAR_MAX                      255

/* maximum number of bytes in a multibyte character */
#if (defined(_AIX) && defined(_I386)) || defined(_IBM370)
#define MB_LEN_MAX			 4
#else
#define MB_LEN_MAX			 1
#endif

/* maximum value for an object of type short */
#define SHRT_MAX                    +32767

/* minimum value for an object of type short */
#define SHRT_MIN                    -32768

/* maximum value for an object of type unsigned short */
#define USHRT_MAX                    65535 


/* maximum value for an object of type int */
#define INT_MAX                 +2147483647 

/* minimum value for an object of type int */
#define INT_MIN                ((int)-2147483648)

/* maximum value for an object of type unsigned int */
#define UINT_MAX                4294967295U


/* maximum value for an object of type long */
#define LONG_MAX               +2147483647L

/* minimum value for an object of type long */
#define LONG_MIN               ((long)-2147483648L)

/* maximum value for an object of type unsigned long */
#if _NAM
#define ULONG_MAX		0x7fffffffL
#else
#define ULONG_MAX               4294967295UL
#endif

#ifdef __CPLUSPLUS__
}
#endif
#endif /*_LIMITS_H*/
