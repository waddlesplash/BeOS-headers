/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_LIMIT_H
#define MSIPL_LIMIT_H

#include <mcompile.h>

#include MOD_C_INCLUDE(float)
//#include MOD_C_INCLUDE(limits)
#include MOD_C_INCLUDE(climits)  //961214 bkoz, to avoid recursion. . . 

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

//961214 bkoz 
/*
NB: this header file only contains declarations, all definitions are in mlimits.cpp.
*/

enum float_round_style {
     round_indeterminate       = -1,
     round_toward_zero         =  0,
     round_to_nearest          =  1,
     round_toward_infinity     =  2,
     round_toward_neg_infinity =  3
};

//prototypes
template <class T> class numeric_limits;
#ifdef MSIPL_BOOL_BUILTIN
	null_template class numeric_limits <bool>; 
#endif
null_template class numeric_limits <char>;
null_template class numeric_limits <signed char>;
null_template class numeric_limits <unsigned char>;
#ifdef MSIPL_WCHART
	null_template class numeric_limits <wchar_t>;
#endif
null_template class numeric_limits <short>;
null_template class numeric_limits <unsigned short>;
null_template class numeric_limits <int>;
null_template class numeric_limits <unsigned int>;
null_template class numeric_limits <long>;
null_template class numeric_limits <unsigned long>;
#ifdef __MSL_LONGLONG_SUPPORT__
	null_template class numeric_limits <long long>;
	null_template class numeric_limits <unsigned long long>;
#endif
null_template class numeric_limits <float>;
null_template class numeric_limits <double>;
null_template class numeric_limits <long double>;

//generic template
template <class T>
class numeric_limits {
public:
    static const bool is_specialized=false;
    static T min() throw();									//all: min value (CHAR_MIN)
    static T max() throw();									//all: max value (CHAR_MAX, DBL_MAX)
    static const int digits =0;								//int: non-sign bits, flt: x_MANT_DIG
    static const int digits10 = 0;							//all: base10 digits represnted (x_DIG)
    static const bool is_signed = false;					//all: true if signed
    static const bool is_integer = false;					//all: true if integer
    static const bool is_exact = false;						//int: true, flt: true if exact representation
    static const int radix =0;								//int: base (2), flt: base of exponent (2)
    static T epsilon() throw();								//int = 0, flt: (x_EPSILON)
    static T round_error() throw();							//all: max rounding error (rounding constants)
    
    static const int min_exponent = 0;						//int = 0, flt:(x_MIN_EXP)
    static const int min_exponent10 = 0;					//int = 0, flt: (x_MIN_10_EXP)
    static const int max_exponent = 0;						//int = 0, flt: (x_MAX_EXP)
    static const int max_exponent10 = 0;					//int = 0, flt: (x_MAX_10_EXP)
    
    static const bool has_infinity = false;					//all: true if ieee754 (fp only?)
    static const bool has_quiet_NaN = false;				//all: true if ieee754 (fp only?)
    static const bool has_signaling_NaN = false;			//all: true if ieee754 (fp only?)
    static const bool has_denorm = false;					//int = 0, flt: true if variable exp bits
    static const bool has_denorm_loss = false;				//all: (accuracy = denorm loss) == true, else (inexact result) == false
    
    static T infinity() throw();							//all: if ieee754, representation of +inf, if avail
    static T quietNaN() throw();							//all: if ieee754, representationof quiet NaN, if avail
    static T signaling_Nan() throw();						//all: if ieee754, rep of signaling NaN, if avail
    static T denorm_min() throw();							//all: min pos denorm value (fp only?) 
    
    static const bool is_iec559 = false;					//int = 0, flt: true if ieee754 (754 == 559)
    static const bool is_bounded = false;					//all: true if set of all values bounded 
    static const bool is_modulo = false;					//int: true (usual), flt: false (usual) (if can overflow)
    
    static const bool traps = false;						//all: true if trapped
    static const bool tinyness_before = false;				//int: 0, flt: true if tinyness detected before rounding
    static const float_round_style round_style=round_toward_zero; //:int: round_toward_zero, flt: rounding style    																												
};

null_template
class numeric_limits <float> {
public:
    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static float min ()          MSIPL_THROW    { return FLT_MIN; }
    static float max ()          MSIPL_THROW    { return FLT_MAX; }
    static float epsilon ()      MSIPL_THROW    { return FLT_EPSILON; }
    static float denorm_min ()   MSIPL_THROW    { return min (); }
    static float round_error ()  MSIPL_THROW    { return 0.5F; }    

    static float infinity ()       MSIPL_THROW  { return 0.0F; }  
    static float quiet_NaN ()      MSIPL_THROW  { return 0.0F; } 
    static float signalling_NaN () MSIPL_THROW  { return 0.0F; }

    static const float_round_style round_style;
};
    
null_template
class numeric_limits <double> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static double min ()         MSIPL_THROW { return DBL_MIN; }
    static double max ()         MSIPL_THROW { return DBL_MAX; }
    static double epsilon ()     MSIPL_THROW { return DBL_EPSILON; }
    static double denorm_min ()  MSIPL_THROW { return min (); }
    static double round_error () MSIPL_THROW { return 0.5; }

    static double infinity ()       MSIPL_THROW { return 0.0; }
    static double quiet_NaN ()      MSIPL_THROW { return 0.0; }
    static double signalling_NaN () MSIPL_THROW { return 0.0; }

    static const float_round_style round_style;
};

null_template
class numeric_limits <long double> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static long double min ()       MSIPL_THROW { return LDBL_MIN; }  // DBL_MIN
    static long double max ()       MSIPL_THROW { return LDBL_MAX; }  // DBL_MAX
    static long double epsilon ()     MSIPL_THROW { return LDBL_EPSILON; }
    static long double denorm_min ()  MSIPL_THROW { return min (); }
    static long double round_error () MSIPL_THROW { return 0.5L; }

    static long double infinity ()       MSIPL_THROW { return 0.0L; }
    static long double quiet_NaN ()      MSIPL_THROW { return 0.0L; }
    static long double signalling_NaN () MSIPL_THROW { return 0.0L; }

    static const float_round_style round_style;
};

null_template
class numeric_limits <int> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static int min ()         MSIPL_THROW { return INT_MIN; }
    static int max ()         MSIPL_THROW { return INT_MAX; }
    static int epsilon ()     MSIPL_THROW { return 1; }
    static int denorm_min ()  MSIPL_THROW { return min (); }
    static int round_error () MSIPL_THROW { return 0; }

    static int infinity ()       MSIPL_THROW { return 0; }
    static int quiet_NaN ()      MSIPL_THROW { return 0; }
    static int signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <unsigned int> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
 
    static unsigned int min ()         MSIPL_THROW { return 0; }
    static unsigned int max ()         MSIPL_THROW { return UINT_MAX; }
    static unsigned int epsilon ()     MSIPL_THROW { return 1; }
    static unsigned int denorm_min ()  MSIPL_THROW { return min (); }
    static unsigned int round_error () MSIPL_THROW { return 0; }

    static unsigned int infinity ()       MSIPL_THROW { return 0; }
    static unsigned int quiet_NaN ()      MSIPL_THROW { return 0; }
    static unsigned int signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;
};


null_template
class numeric_limits <long> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static long min ()         MSIPL_THROW { return LONG_MIN; }
    static long max ()         MSIPL_THROW { return LONG_MAX; }
    static long epsilon ()     MSIPL_THROW { return 1; }
    static long denorm_min ()  MSIPL_THROW { return min (); }
    static long round_error () MSIPL_THROW { return 0; }

    static long infinity ()       MSIPL_THROW { return 0; }
    static long quiet_NaN ()      MSIPL_THROW { return 0; }
    static long signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <unsigned long> {
public:

    static const bool is_specialized;				

    static const int  radix;								
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
 
    static unsigned long min ()         MSIPL_THROW { return 0; }
    static unsigned long max ()         MSIPL_THROW { return ULONG_MAX; }
    static unsigned long epsilon ()     MSIPL_THROW { return 1; }
    static unsigned long denorm_min ()  MSIPL_THROW { return min (); }
    static unsigned long round_error () MSIPL_THROW { return 0; }

    static unsigned long infinity ()       MSIPL_THROW { return 0; }
    static unsigned long quiet_NaN ()      MSIPL_THROW { return 0; }
    static unsigned long signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

#ifdef __MSL_LONGLONG_SUPPORT__

null_template
class numeric_limits <long long> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static long long min ()         MSIPL_THROW { return LONGLONG_MIN; }
    static long long max ()         MSIPL_THROW { return LONGLONG_MAX; }
    static long long epsilon ()     MSIPL_THROW { return 1; }
    static long long denorm_min ()  MSIPL_THROW { return min (); }
    static long long round_error () MSIPL_THROW { return 0; }

    static long long infinity ()       MSIPL_THROW { return 0; }
    static long long quiet_NaN ()      MSIPL_THROW { return 0; }
    static long long signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <unsigned long long> {
public:

    static const bool is_specialized;				

    static const int  radix;								
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
 
    static unsigned long long min ()         MSIPL_THROW { return 0; }
    static unsigned long long max ()    MSIPL_THROW { return ULONGLONG_MAX; }
    static unsigned long long epsilon ()     MSIPL_THROW { return 1; }
    static unsigned long long denorm_min ()  MSIPL_THROW { return min (); }
    static unsigned long long round_error () MSIPL_THROW { return 0; }

    static unsigned long long infinity ()       MSIPL_THROW { return 0; }
    static unsigned long long quiet_NaN ()      MSIPL_THROW { return 0; }
    static unsigned long long signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

#endif //__MSL_LONGLONG_SUPPORT__

null_template
class numeric_limits <short> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
 
    static short min ()         MSIPL_THROW { return SHRT_MIN; }
    static short max ()         MSIPL_THROW { return SHRT_MAX; }
    static short epsilon ()     MSIPL_THROW { return 1; }
    static short denorm_min ()  MSIPL_THROW { return min (); }
    static short round_error () MSIPL_THROW { return 0; }

    static short infinity ()       MSIPL_THROW { return 0; }
    static short quiet_NaN ()      MSIPL_THROW { return 0; }
    static short signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};


null_template
class numeric_limits <unsigned short> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static unsigned short min ()         MSIPL_THROW { return 0; }
    static unsigned short max ()         MSIPL_THROW { return USHRT_MAX; }
    static unsigned short epsilon ()     MSIPL_THROW { return 1; }
    static unsigned short denorm_min ()  MSIPL_THROW { return min (); }
    static unsigned short round_error () MSIPL_THROW { return 0; }

    static unsigned short infinity ()       MSIPL_THROW { return 0; }
    static unsigned short quiet_NaN ()      MSIPL_THROW { return 0; }
    static unsigned short signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <char> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static char min ()         MSIPL_THROW { return CHAR_MIN; }
    static char max ()         MSIPL_THROW { return CHAR_MAX; }
    static char epsilon ()     MSIPL_THROW { return 1; }
    static char denorm_min ()  MSIPL_THROW { return min (); }
    static char round_error () MSIPL_THROW { return 0; }

    static char infinity ()       MSIPL_THROW { return 0; }
    static char quiet_NaN ()      MSIPL_THROW { return 0; }
    static char signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <signed char> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static signed char min ()         MSIPL_THROW { return SCHAR_MIN; }
    static signed char max ()         MSIPL_THROW { return SCHAR_MAX; }
    static signed char epsilon ()     MSIPL_THROW { return 1; }
    static signed char denorm_min ()  MSIPL_THROW { return min (); }
    static signed char round_error () MSIPL_THROW { return 0; }

    static signed char infinity ()       MSIPL_THROW { return 0; }
    static signed char quiet_NaN ()      MSIPL_THROW { return 0; }
    static signed char signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

null_template
class numeric_limits <unsigned char> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static unsigned char min ()         MSIPL_THROW { return 0; }
    static unsigned char max ()         MSIPL_THROW { return UCHAR_MAX; }
    static unsigned char epsilon ()     MSIPL_THROW { return 1; }
    static unsigned char denorm_min ()  MSIPL_THROW { return min (); }
    static unsigned char round_error () MSIPL_THROW { return 0; }

    static unsigned char infinity ()       MSIPL_THROW { return 0; }
    static unsigned char quiet_NaN ()      MSIPL_THROW { return 0; }
    static unsigned char signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

#ifdef MSIPL_BOOL_BUILTIN
null_template
class numeric_limits <bool> {
public:
    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static bool min ()         MSIPL_THROW { return 0; }
    static bool max ()         MSIPL_THROW { return 1; }
    static bool epsilon ()     MSIPL_THROW { return 1; }
    static bool denorm_min ()  MSIPL_THROW { return min (); }
    static bool round_error () MSIPL_THROW { return 0; }

    static bool infinity ()       MSIPL_THROW { return 0; }
    static bool quiet_NaN ()      MSIPL_THROW { return 0; }
    static bool signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;
};
#endif

#ifdef MSIPL_WCHART

null_template
class numeric_limits <wchar_t> {
public:

    static const bool is_specialized;

    static const int  radix;
    static const int  digits;
    static const int  digits10;
    static const int  min_exponent;
    static const int  max_exponent;
    static const int  min_exponent10;
    static const int  max_exponent10;

    static const bool is_signed;
    static const bool is_integer;
    static const bool is_exact;

    static const bool has_infinity;
    static const bool has_quiet_NaN;
    static const bool has_signaling_NaN;
    static const bool has_denorm;
    static const bool has_denorm_loss;

    static const bool is_iec559;
    static const bool is_bounded;
    static const bool is_modulo;
    static const bool traps;
    static const bool tinyness_before;
 
    static wchar_t min ()         MSIPL_THROW { return 0; }
    static wchar_t max ()         MSIPL_THROW { return UINT_MAX; }
    static wchar_t epsilon ()     MSIPL_THROW { return 1; }
    static wchar_t denorm_min ()  MSIPL_THROW { return min (); }
    static wchar_t round_error () MSIPL_THROW { return 0; }

    static wchar_t infinity ()       MSIPL_THROW { return 0; }
    static wchar_t quiet_NaN ()      MSIPL_THROW { return 0; }
    static wchar_t signalling_NaN () MSIPL_THROW { return 0; }

    static const float_round_style round_style;

};

#endif /* MSIPL_WCHART */

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_LIMIT_H */

//961210 bkoz added alignment wrapper
//961212 bkoz added prototypes, added bool
//961214 bkoz changed has_signalling_NaN to has_signaling_NaN
//961214 bkoz added generic template members, commentary on field values
//961214 bkoz added bool specialization. Have to use 1 byte bool types. ..
//961216 bkoz line 405 to 495 added long long, unsigned long long specializations
