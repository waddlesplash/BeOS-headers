/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_IOS_H
#define MSIPL_IOS_H

#include <mcompile.h>
#include MOD_INCLUDE(mutex)
#include <locale>		//970417 bkoz

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

//foward declarations
class locale;
template <class charT, class traits> class basic_streambuf;
template <class charT, class traits> class basic_ostream;
class ios_base;

//
//	970418 bkoz
//	class ios_base now declared in ios_base.h
//	definitions of larger member functions in iostream.cpp
//

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_ios : public ios_base {

public:
   
//
//   Public typdef declaration
//
     typedef  charT                 char_type;
     typedef  traits                traits_type;

     typedef typename  traits::pos_type      pos_type;
     typedef typename  traits::off_type      off_type;
     typedef typename  traits::int_type      int_type;
     typedef typename  ios_base::iostate     iostate;

     inline
     explicit
     basic_ios (basic_streambuf<char_type, traits>* sb_arg);

     virtual ~basic_ios ();

     basic_ios<charT, traits>& 
     copyfmt (const basic_ios<charT, traits>& rhs);

     inline
     basic_ostream<char_type, traits>* 
     tie () const;

     inline
     basic_ostream<char_type, traits>* 
     tie (basic_ostream<char_type, traits>* tiestr_arg);

     inline
     basic_streambuf<char_type, traits>* 
     rdbuf () const;

     inline
     basic_streambuf<char_type, traits>*
     rdbuf (basic_streambuf<char_type, traits>* sb_arg);

     inline
     char_type
     fill () const;

     inline
     char_type
     fill (char_type ch);

     void
     clear (iostate state = ios_base::goodbit);

     locale 
     imbue (const locale& loc_arg);

protected:

     inline
     basic_ios ();

     inline
     basic_ios (ios_base::fmt_flags fmt_arg);

     void
     init (basic_streambuf<char_type, traits>* sb_arg);

private:

     // not to be defined
     basic_ios (const basic_ios<char_type, traits>& rhs);   //970408 bkoz not  defined

     // not to be defined
     basic_ios&
     operator= (const basic_ios<char_type, traits>& rhs);  //970408 bkoz not defined

//
//   Data members
//
     basic_streambuf<char_type, traits>*    sb;
     basic_ostream<char_type, traits>*      tiestr;
     char_type                              fillch;

     DEC_OBJ_LOCK(_mutex)
};


template <class charT, class traits>
inline 
basic_ostream<charT, traits>*
basic_ios<charT, traits>::tie () const
{
    READ_LOCK(_mutex);
    return tiestr;
}

template <class charT, class traits>
inline 
basic_ostream<charT, traits>*
basic_ios<charT, traits>::tie (basic_ostream<charT, traits>* tiestr_arg)
{
    WRITE_LOCK(_mutex);
    basic_ostream<charT, traits>*  tiestr_sav = tiestr;
    tiestr = tiestr_arg;
    return (tiestr_sav);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>*
basic_ios<charT, traits>::rdbuf () const
{
    READ_LOCK(_mutex);
    return (sb);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>*
basic_ios<charT, traits>::rdbuf (basic_streambuf<charT, traits>* sb_arg)
{
    WRITE_LOCK(_mutex);
    basic_streambuf<charT, traits>*  sb_sav = sb;
    //
    // Should there be a call to sb_sav->sync () ?
    sb = sb_arg;
    clear ();
    return (sb_sav);
}

template <class charT, class traits>
inline
basic_ios<charT, traits>::char_type
basic_ios<charT, traits>::fill () const
{
    return (fillch);
}

template <class charT, class traits>
inline
basic_ios<charT, traits>::char_type
basic_ios<charT, traits>::fill (char_type fillch_arg)
{
    char_type fillch_sav = fillch;
    fillch               = fillch_arg;
    return (fillch_sav);
}

template <class charT, class traits>
void
basic_ios<charT, traits>::clear (iostate state_arg)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    ios_base::clear (state_arg);

#ifdef MSIPL_EXCEPT
    }
    catch (...) {
    if (sb == 0)
        assign_state (rdstate () | badbit);
    throwfailure ();
    }
#endif
    if (sb == 0)
        assign_state (rdstate () | badbit);
    if ((rdstate () & except) != 0)
    {
        throwfailure ();
    }
}

template <class charT, class traits>
locale
basic_ios<charT, traits>::imbue (const locale& loc_arg)
{
    locale loc_save = ios_base::imbue(loc_arg);
    if (rdbuf() != 0)
        rdbuf()->pubimbue(loc_arg);
 
    return loc_save;
}


template <class charT, class traits>
inline
void
basic_ios<charT, traits>::init (basic_streambuf<charT, traits>* sb_arg)
{
    sb        =  sb_arg;
    tiestr    =  0;
    except    =  goodbit;
    fillch    =  ' ';

    base_init ();
    assign_state (sb_arg ? goodbit : badbit);
}

template <class charT, class traits>
inline
basic_ios<charT, traits>::basic_ios ()
: ios_base ()
{
    init (0);
}

template <class charT, class traits>
inline
basic_ios<charT, traits>::basic_ios (ios_base::fmt_flags /* fmt_arg */)
: ios_base ()
{
}
 
template <class charT, class traits>
inline
basic_ios<charT, traits>::basic_ios (basic_streambuf<charT, traits>* sb_arg)
: ios_base ()
{
    init (sb_arg);
}

//#pragma dont_inline on //970408 bkoz
template <class charT, class traits>
basic_ios<charT, traits>::~basic_ios ()
{
    REMOVE(_mutex);
}
// mf 101597 #pragma dont_inline reset //970408 bkoz
 

template <class charT, class traits>
basic_ios<charT, traits>&
basic_ios<charT, traits>::copyfmt (const basic_ios<charT, traits>& rhs)
{
    if (this != &rhs)
    {
        call_regpair (*this, erase_event);
        *loc     = rhs.getloc ();
        tiestr  = rhs.tiestr;
        fillch  = rhs.fillch;

        ios_base::copyfmt (rhs);

        rvec_size = 0;
        for (int i=0; i< rhs.rvec_size; i++)
        {
            register_callback (rhs.rvec[i].first, rhs.rvec[i].second);    
            (*(rhs.rvec[i].first)) (copyfmt_event, *this,
                                    rhs.rvec[i].second);
        }
        exceptions (rhs.except);
    }
    return *this;
}


#ifdef __MSL_NO_INSTANTIATE__
	template __dont_instantiate class basic_ios<char, char_traits<char> >;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset


#endif /* MSIPL_IOS_H */

//961210 bkoz added wrapper for alignment
//961211 bkoz line 314 added andreas's iterator specializations for new FE
//961221 bkoz line 281 added moto change (mmoss)
//970417 bkoz took ios_base defs out for #pragma once
