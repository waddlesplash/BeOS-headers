/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_IOSFWD_H
#define MSIPL_IOSFWD_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

template <class charT>                    class  char_traits;

template <class charT, class traits>      class basic_ios;
template <class charT, class traits>      class basic_istream;
template <class charT, class traits>      class basic_ostream;
template <class charT, class traits>      class basic_streambuf;

typedef  basic_ios<char,              char_traits<char> >     ios;
typedef  basic_istream<char,          char_traits<char> >     istream; 
typedef  basic_ostream<char,          char_traits<char> >     ostream; 

#ifdef MSIPL_WCHART
typedef  basic_ios<wchar_t,    char_traits<wchar_t> >   wios;
typedef basic_istream<wchar_t, char_traits<wchar_t> >   wistream;
typedef basic_ostream<wchar_t, char_traits<wchar_t> >   wostream;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_IOSFWD_H */


//961210 bkoz added alignment wrapper
