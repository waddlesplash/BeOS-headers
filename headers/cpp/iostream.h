/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_IOSTREAM_H
#define MSIPL_IOSTREAM_H

#include <mcompile.h>

#include MOD_INCLUDE(istream)
#include MOD_INCLUDE(ostream)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_iostream 
  : public basic_istream<charT, traits>, 
    public basic_ostream<charT, traits> {

public:
   // constructor/destructor
   explicit
   basic_iostream (basic_streambuf<charT, traits>* sb)
   :basic_istream<charT, traits>(sb), basic_ostream<charT, traits>(sb),
    basic_ios<charT, traits>(sb)
   { 
   }

   virtual ~basic_iostream () { }
};

extern istream cin;
extern ostream cout;
extern ostream clog;
extern ostream cerr;

static ios_base::Init  __msipl_ios_init; 

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_IOSTREAM_H */

//961210 bkoz added alignment wrapper