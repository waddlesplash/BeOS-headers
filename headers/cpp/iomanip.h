/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_MANIPULATOR_H
#define MSIPL_MANIPULATOR_H

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
 
//
// Input Manipulators
//

//
// Template class basic_imanip
//

#ifdef MSIPL_DEF_TEMPARG
template <class T, class charT, class traits = char_traits<charT> >
#else
template <class T, class charT, class traits>
#endif
class basic_imanip {

    friend
    basic_istream<charT, traits>&
    operator>> (basic_istream<charT, traits>& is, 
                const basic_imanip<T, charT, traits>& a);

public :

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef  typename traits::pos_type    pos_type;
    typedef  typename traits::off_type    off_type;
    typedef  typename traits::int_type    int_type;
 
protected:

    typedef  basic_istream<charT, traits>    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public :

    inline
    basic_imanip (pf_type, T);

private:

    pf_type    pf;
    T          manarg;

};

template <class T> class imanip 
: public basic_imanip<T, char, char_traits<char> > 
{ 
protected:

    typedef  basic_istream<char, char_traits<char> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public:
    imanip (pf_type pf, T t)
      : basic_imanip<T, char, char_traits<char> > (pf, t) {}
};

//
// Template class basic_omanip
//

#ifdef MSIPL_DEF_TEMPARG
template <class T, class charT, class traits = char_traits<charT> >
#else
template <class T, class charT, class traits>
#endif
class basic_omanip {

    friend
    basic_ostream<charT, traits>&
    operator<< (basic_ostream<charT, traits>& os, 
                const basic_omanip<T, charT, traits>& a);

public :
 
    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef  typename traits::pos_type    pos_type;
    typedef  typename traits::off_type    off_type;
    typedef  typename traits::int_type    int_type;
 
protected:
 
    typedef  basic_ostream<charT, traits>    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public :

    inline
    basic_omanip (pf_type, T);

private:

    pf_type    pf;
    T          manarg;

};

template <class T> class omanip 
: public basic_omanip<T, char, char_traits<char> > 
{ 
protected:

    typedef  basic_ostream<char, char_traits<char> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public:
    omanip (pf_type pf, T t)
      : basic_omanip<T, char, char_traits<char> > (pf, t) {}
};

//
// Template class basic_smanip
//

template <class T, class charT, class traits>
class basic_smanip {

    friend
    basic_istream<charT, traits>&
    operator>> (basic_istream<charT, traits>& is, 
                const basic_smanip<T, charT, traits>& a);
    
    friend
    basic_ostream<charT, traits>&
    operator<< (basic_ostream<charT, traits>& os, 
                const basic_smanip<T, charT, traits>& a);

public :

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef  typename traits::pos_type    pos_type;
    typedef  typename traits::off_type    off_type;
    typedef  typename traits::int_type    int_type;
 
    inline static
    int_type eof () {  return typename traits::eof (); }
 
    inline static
    char_type newline () {  return typename traits::newline (); }

private:

    typedef  basic_ios<charT, traits>    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public :

    inline
    basic_smanip (pf_type, T);

private:

    pf_type    pf;
    T          manarg;
};

template <class T> 
class smanip : public basic_smanip<T, char, char_traits<char> > 
{
private:

    typedef  basic_ios<char, char_traits<char> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public :

    smanip (pf_type pf_arg, T arg) 
       : basic_smanip<T, char, char_traits<char> > (pf_arg, arg)
   { }

};

template <class T, class charT, class traits>
inline
basic_imanip<T, charT, traits>::
basic_imanip (pf_type pf_arg, T manarg_arg)
: pf (pf_arg), manarg (manarg_arg) { }

template <class T, class charT, class traits>
inline
basic_omanip<T, charT, traits>::
basic_omanip (pf_type pf_arg, T manarg_arg)
: pf (pf_arg), manarg (manarg_arg) { }

template <class T, class charT, class traits>
inline
basic_smanip<T, charT, traits>::
basic_smanip (pf_type pf_arg, T manarg_arg)
: pf (pf_arg), manarg (manarg_arg) { }

template <class T, class charT, class traits>
inline
basic_istream<charT, traits>&
operator>> (basic_istream<charT, traits>& is, 
            const basic_imanip<T, charT, traits>& a)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    (*a.pf) (is, a.manarg);
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        is.setstate (ios_base::failbit);
    }
#endif
    return is;
}

template <class T, class charT, class traits>
inline
basic_ostream<charT, traits>&
operator<< (basic_ostream<charT, traits>& os, 
            const basic_omanip<T, charT, traits>& a)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    (*a.pf) (os, a.manarg);
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        os.setstate (ios_base::failbit);
    }
#endif
    return os;
}

template <class T, class charT, class traits>
inline
basic_istream<charT, traits>&
operator>> (basic_istream<charT, traits>& is, 
            const basic_smanip<T, charT, traits>& a)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    (*a.pf) (is, a.manarg);
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        is.setstate (ios_base::failbit);
    }
#endif
    return is;
}

template <class T, class charT, class traits>
inline
basic_ostream<charT, traits>&
operator<< (basic_ostream<charT, traits>& os, 
            const basic_smanip<T, charT, traits>& a)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    (*a.pf) (os, a.manarg);
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        os.setstate (ios_base::failbit);
    }
#endif
    return os;
}

//
// Standard Manipulators
//
template <class charT, class traits>
inline
basic_ios<charT, traits>&
freset (basic_ios<charT, traits>& str, 
        ios_base::fmtflags  mask)
{
    // reset specified flags
    str.setf ((basic_ios<charT, traits>::fmtflags)0, mask);
    return str;
}

template <class charT, class traits>
inline
basic_ios<charT, traits>&
fset (basic_ios<charT, traits>& str, ios_base::fmtflags  mask)
{
    // set specified flags
    str.setf (mask);
    return str;
}

template <class charT, class traits>
inline
basic_ios<charT, traits>&
fsetbase (basic_ios<charT, traits>& str, int n)
{
    // set basefield
    str.setf ((n ==  8) ?  ios_base::oct :
             (n == 10) ?  ios_base::dec :
             (n == 16) ?  ios_base::hex :
             (basic_ios<charT, traits>::fmtflags)0,
              ios_base::basefield);
    return str;
}

//961114 bkoz orig
/*
template <class charT, class traits>
inline
basic_ios<charT, traits>&
ffill (basic_ios<charT, traits>& str,
//       typename basic_ios<charT, traits>::int_type c)
       int c)		//961120 bkoz
{
    // set fill character
    str.fill (c);
    return str;
}
*/

basic_ios<char, char_traits<char> >&
ffill (basic_ios<char, char_traits<char> >& str,
       basic_ios<char, char_traits<char> >::int_type c);
#ifdef MSIPL_WCHART
basic_ios<wchar_t, char_traits<wchar_t> >&
ffill (basic_ios<wchar_t, char_traits<wchar_t> >& str,
       basic_ios<wchar_t, char_traits<wchar_t> >::int_type c);
#endif

/**********************************************************
inline
basic_ios<char, char_traits<char> >&
ffill (basic_ios<char, char_traits<char> >& str,
      basic_ios<char, char_traits<char> >::int_type c)
{
    // set fill character
    str.fill (c);
    return str;
}

#ifdef MSIPL_WCHART

inline
basic_ios<wchar_t, char_traits<wchar_t> >&
ffill (basic_ios<wchar_t, char_traits<wchar_t> >& str,
       basic_ios<wchar_t, char_traits<wchar_t> >::int_type c)
{
    // set fill character
    str.fill (c);
    return str;
}
#endif
**********************************************************/

template <class charT, class traits>
inline
basic_ios<charT, traits>&
fprecise (basic_ios<charT, traits>& str, streamsize n)
{
    // set precision
    str.precision (n);
    return str;
}

template <class charT, class traits>
inline
basic_ios<charT, traits>&
fwidth (basic_ios<charT, traits>& str, streamsize n)
{
    // set width
    str.width (n);
    return str;
}

smanip <ios_base::fmtflags>
resetiosflags (ios_base::fmtflags  mask);

smanip <ios_base::fmtflags>
setiosflags (ios_base::fmtflags  mask);
/*********************************************************
inline
smanip <ios_base::fmtflags>
resetiosflags (ios_base::fmtflags  mask)
{
    return  smanip<ios_base::fmtflags> (&freset, mask);
}

inline
smanip <ios_base::fmtflags>
setiosflags (ios_base::fmtflags  mask)
{
    return  smanip<ios_base::fmtflags> (&fset, mask);
}
*********************************************************/

smanip <int> setbase (int base);

/*
template <class charT, class traits>
inline
basic_smanip <basic_ios<charT, traits>::fmtflags, charT, traits>
basic_setiosflags (basic_ios<charT, traits>::fmtflags  mask)
{
    return  basic_smanip<basic_ios<charT, traits>::fmtflags, 
                         charT, traits> (&fset, mask);
}

inline
smanip <int>
setbase (int base)
{
    return  smanip<int> (&fsetbase, base);
}
*/

//961114 bkoz use specialization below
/*
template <class charT, class traits>
inline
basic_smanip <typename basic_ios<charT, traits>::int_type, charT, traits>
setfill (typename basic_ios<charT, traits>::int_type c)
{
    return  basic_smanip<typename basic_ios<charT, traits>::int_type, 
                         charT, traits> (&ffill, c);
}
*/

//961114 bkoz orig sorce . .. use this instead of generalize template above 
basic_smanip <basic_ios<char, char_traits<char> >::int_type, char,
              char_traits<char> >
setfill (basic_ios<char, char_traits<char> >::int_type c);

#ifdef MSIPL_WCHART
basic_smanip <basic_ios<wchar_t, char_traits<wchar_t> >::int_type,
              wchar_t, char_traits<wchar_t> >
setfill (basic_ios<wchar_t, char_traits<wchar_t> >::int_type c);
#endif

/***********************************************
inline
basic_smanip <basic_ios<char, char_traits<char> >::int_type, char,
              char_traits<char> >
setfill (basic_ios<char, char_traits<char> >::int_type c)
{
    return  basic_smanip<basic_ios<char, char_traits<char> >::int_type, 
                          char, char_traits<char> > (&ffill, c);
}

#ifdef MSIPL_WCHART
inline
basic_smanip <basic_ios<wchar_t, char_traits<wchar_t> >::int_type,
              wchar_t, char_traits<wchar_t> >
setfill (basic_ios<wchar_t, char_traits<wchar_t> >::int_type c)
{
    return  basic_smanip<basic_ios<wchar_t,char_traits<wchar_t> >::int_type,
                         wchar_t, char_traits<wchar_t> > (&ffill, c);
}
#endif

inline
smanip <streamsize>
setprecision (streamsize n)
{
    return smanip<streamsize> (&fprecise, n);
}

inline
smanip <streamsize>
setw (streamsize n)
{
    return smanip<streamsize> (&fwidth, n);
}
***********************************************/
smanip <streamsize>
setprecision (streamsize n);

smanip <streamsize>
setw (streamsize n);

#ifdef MSIPL_WCHART

template <class T> class wimanip 
: public basic_imanip<T, wchar_t, char_traits<wchar_t> > 
{
protected:

    typedef  basic_istream<wchar_t, char_traits<wchar_t> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public:
    wimanip (pf_type pf, T t)
      : basic_imanip<T, wchar_t, char_traits<wchar_t> > (pf, t) {}
};

template <class T> class womanip 
: public basic_omanip<T, wchar_t, char_traits<wchar_t> > 
{ 
protected:

    typedef  basic_ostream<wchar_t, char_traits<wchar_t> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public:
    womanip (pf_type pf, T t)
      : basic_omanip<T, wchar_t, char_traits<wchar_t> > (pf, t) {}
};

template <class T> class wsmanip 
: public basic_smanip<T, wchar_t, char_traits<wchar_t> > 
{
private:

    typedef  basic_ios<wchar_t, char_traits<wchar_t> >    ios_type;
    typedef  ios_type&  (* pf_type) (ios_type&, T);
 
public :

    wsmanip (pf_type pf_arg, T arg) 
       : basic_smanip<T, wchar_t, char_traits<wchar_t> > (pf_arg, arg)
   { }

};

#endif /* MSIPL_WCHART */

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_MANIPULATOR_H */

//961114 bkoz line 334, 445 use specializations instead of generalized template
//961210 bkoz added alignment wrapper