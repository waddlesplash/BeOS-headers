/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_STREAMBUF_H
#define MSIPL_STREAMBUF_H

#include <mcompile.h>

#include MOD_INCLUDE(ios)	//970406 bkoz

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

class basic_streambuf {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;
    //
    // This  typedef  added so that a  user can invoke 
    // traits member functions through a stream buffer

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

    virtual ~basic_streambuf ();

    inline
    pos_type
    pubseekoff (off_type  off, ios_base::seekdir way,
                ios_base::openmode which = ios_base::in | ios_base::out);

    inline
    pos_type
    pubseekpos (pos_type sp,
                ios_base::openmode which = ios_base::in | ios_base::out);

    inline 
    basic_streambuf<char_type, traits>*
    pubsetbuf (char_type* s, streamsize n);

    inline
    streamsize
    in_avail ();

    inline
    int
    pubsync ();

    inline
    int_type
    sbumpc ();

    inline
    int_type
    sgetc ();

    inline
    streamsize
    sgetn (char_type* s, streamsize n);

    inline
    int_type
    snextc ();

    inline
    int_type
    sputbackc (char_type c);

    inline
    int_type 
    sungetc ();

    inline
    int_type 
    sputc (char_type c);

    inline
    streamsize
    sputn (const char_type* s, streamsize n);

    locale
    pubimbue (const locale& loc_arg);

    locale
    getloc () const;
 
protected:

    basic_streambuf ();

    inline
    char_type*
    eback () const;

    inline
    char_type*
    gptr () const;

    inline
    char_type*
    egptr () const;

    inline
    void
    gbump (int n);

    inline
    void
    setg (char_type* gbeg_arg, char_type* gnext_arg, char_type* gend_arg);

    inline
    char_type*
    pbase () const;

    inline
    char_type*
    pptr () const;

    inline
    char_type*
    epptr () const;

    inline
    void
    pbump (int n);

    inline
    void
    setp (char_type* pbeg_arg, char_type* pend_arg);
 
    virtual void
    imbue (const locale& loc_arg);

    inline
    virtual int_type
    overflow (int_type c = traits::eof ());

    virtual int_type                                     //MW-mm 961227
    __pbfile (int_type);                                 //MW-mm 961227

    inline
    virtual int_type
    pbackfail (int_type c = traits::eof ());
 
    inline
    virtual streamsize
    showmanyc ();

    inline
    virtual int_type
    underflow ();

    inline
    virtual int_type
    uflow ();

    virtual streamsize
    xsgetn (char_type* s, streamsize n);

    virtual streamsize
    xsputn (const char_type* s, streamsize n);
 
    inline
    virtual pos_type
    seekoff (off_type off, ios_base::seekdir way, ios_base::openmode which = ios_base::in | ios_base::out)
	{
	    off;way;which;
	    // default behaviour
	    return pos_type (-1);
	    // assuming this to be an invalid pos_type
	}
    
    inline
    virtual pos_type
    seekpos (pos_type sp, ios_base::openmode which = ios_base::in | ios_base::out)
	{
	    sp;which;
	    // default behaviour
	    return pos_type (-1);
	    // assuming this to be an invalid pos_type
	}


    virtual basic_streambuf<char_type, traits>*
    setbuf (char_type* s, streamsize n);

    inline
    virtual int
    sync () { return 0;}

//
//  These functions are added for our implementation
//

    inline bool
    avail_readpos ();

    inline bool
    avail_writepos ();

    inline bool
    avail_putbackpos ();

    inline void
    init ();

    //
    //  protected data member
    //
    locale       loc;
    /* mm 970711 The following declarations moved from private*/               
    char_type*   gbeg;             
    char_type*   gnext;
    char_type*   gend;
    char_type*   pbeg;
    char_type*   pnext;
    char_type*   pend;
    /* mm 970711 End of move*/               

    // mutex locks for the get and put area.
    //
    DEC_MUTEX(put_lock)
    DEC_MUTEX(get_lock)

private:

    // to be undefined
    basic_streambuf (const basic_streambuf<charT, traits>&  rhs); //970408 bkoz defined

    // to be undefined
    basic_streambuf<charT, traits>&
    operator= (const basic_streambuf<charT, traits>&  rhs); //970408 bkoz defined
};

template <class charT, class traits>
inline
void 
basic_streambuf<charT, traits>::setg (char_type* gbeg_arg, 
                                char_type* gnext_arg, char_type* gend_arg)
{
    gbeg   = gbeg_arg;
    gnext  = gnext_arg;
    gend   = gend_arg;
}

template <class charT, class traits>
inline
void 
basic_streambuf<charT, traits>::setp (char_type* pbeg_arg, char_type* pend_arg)
{
    pnext = pbeg = pbeg_arg;
    pend         = pend_arg;
}

template <class charT, class traits>
inline
void
basic_streambuf<charT, traits>::init ()
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    setg (0, 0, 0);    
    setp (0, 0); 
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::eback () const
{
    return (gbeg);
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::gptr () const
{
    return (gnext);
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::egptr () const
{
    return (gend);
}

template <class charT, class traits>
inline
void 
basic_streambuf<charT, traits>::gbump (int n)
{
    gnext += n;
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::pbase () const
{
    return (pbeg);
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::pptr () const
{
    return (pnext);
}

template <class charT, class traits>
inline
charT*
basic_streambuf<charT, traits>::epptr () const
{
    return (pend);
}

template <class charT, class traits>
inline
void 
basic_streambuf<charT, traits>::pbump (int n)
{
    pnext += n;
}
 
template <class charT, class traits>
inline 
bool
basic_streambuf<charT, traits>::avail_readpos ()
{
    return (gnext && (gnext < gend));
}

template <class charT, class traits>
inline 
bool
basic_streambuf<charT, traits>::avail_writepos ()
{
    return (pnext && (pnext < pend));
}

template <class charT, class traits>
inline 
bool
basic_streambuf<charT, traits>::avail_putbackpos ()
{
    return (gnext && (gbeg < gnext));
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::pos_type
basic_streambuf<charT, traits>::pubseekoff (off_type  off,
                                ios_base::seekdir way, ios_base::openmode which)
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    return seekoff (off, way, which);
}


template <class charT, class traits>
inline
basic_streambuf<charT, traits>::pos_type
basic_streambuf<charT, traits>::pubseekpos (pos_type sp, 
                                ios_base::openmode which)
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    return seekpos (sp, which);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>*
basic_streambuf<charT, traits>::setbuf (char_type* /* s */,
                                        streamsize /* n */)
{
    // default behaviour
    return this;
}


template <class charT, class traits>
inline
basic_streambuf<charT, traits>*
basic_streambuf<charT, traits>::pubsetbuf (char_type* s, streamsize n)
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    return setbuf (s, n);
}

template <class charT, class traits>
inline
int
basic_streambuf<charT, traits>::pubsync ()
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    return sync ();
}

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::in_avail ()
{
    LOCK(get_mut_block, get_lock);
    return (avail_readpos () ? (gend-gnext) : showmanyc ());
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::overflow (int_type /* c */)
{
    // default behaviour
    return traits::eof ();
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::pbackfail (int_type /* c */)
{
    // default behaviour
    return traits::eof ();
}

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::showmanyc ()
{
    // default behaviour
    return 0;
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::underflow ()
{
    // default behaviour
    return traits::eof ();
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::uflow ()
{
    // default behaviour
    if (underflow () == traits::eof ())
        return traits::eof ();
    else
        return traits::to_int_type (*gnext++);
        // what if gnext is a null pointer
        // perhaps in that case underflow () returns traits::eof ().

}

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::xsgetn (char_type* s, streamsize n)
{
    streamsize  nvalue = 0;
    off_type    nsize;
    int_type    ch;

    while (n > 0)
    {
        nsize   =  ((n > (egptr ()-gptr ())) ? (egptr ()-gptr ()) : n);
        nvalue +=  nsize;
        n      -=  nsize;

        traits::copy (s, gnext, nsize);
        s      +=  nsize;
        gnext  +=  nsize;

        if (n > 0)
        {
            if (traits::eq_int_type ((ch = uflow ()), traits::eof ()))
                break;
            else
            {
                *s++ = traits::to_char_type (ch);
                ++nvalue;
                --n;
            }
         }
     }
     return nvalue;
} 

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::xsputn (const char_type* s, streamsize n)
{
    streamsize  nvalue = 0;
    off_type    nsize;

    while (n > 0)
    {
        nsize   =  ((n > (epptr ()-pptr ())) ? (epptr ()-pptr ()) : n);
        nvalue +=  nsize;
        n      -=  nsize;

        traits::copy (pnext, s, nsize);
        s      +=  nsize;
        pnext  +=  nsize;

        if (n > 0)
        {
            if (traits::eq_int_type (overflow (traits::to_int_type (*s)),
                                     traits::eof ()))
                break;
            else
            {
                ++s;
                ++nvalue;
                --n;
            }
         }
     }
     return nvalue;
}



template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::sbumpc ()
{
    LOCK(get_mut_block, get_lock);
    return (avail_readpos () ? 
            traits::to_int_type (*gnext++) : uflow ());
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::sgetc ()
{
    LOCK(get_mut_block, get_lock);
    return (avail_readpos () ? 
            traits::to_int_type (*gnext) : underflow ());
}

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::sgetn (char_type* s, streamsize n)
{
    LOCK(get_mut_block, get_lock);
    return xsgetn (s, n);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::snextc ()
{
    LOCK(get_mut_block, get_lock);
    return (traits::eq_int_type (sbumpc (), traits::eof ()) 
              ? traits::eof () : sgetc ());
}

template <class charT, class traits>                          // MW-mm 961227
basic_streambuf<charT, traits>::int_type                      // MW-mm 961227
basic_streambuf<charT, traits>::__pbfile (int_type)           // MW-mm 961227
{                                                             // MW-mm 961227
    // default behaviour                                      // MW-mm 961227
    return traits::eof ();                                    // MW-mm 961227
}                                                             // MW-mm 961227

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::sputbackc (char_type c)
{
    LOCK(get_mut_block, get_lock);
//    return ((avail_putbackpos () && (traits::eq (c, * (gnext-1)))) ? 
//             traits::to_int_type (*--gnext) : 
//             pbackfail (traits::to_int_type (c)));
      if (avail_putbackpos () && (traits::eq (c, * (gnext-1))))
         return(traits::to_int_type (*--gnext));
      else
    	  if ((gbeg == NULL) && (gnext == NULL) && (gend == NULL)) // MW-mm 961227
    	  // There is no buffer so must be a file; use __pbfile    // MW-mm 961227
    		  return(__pbfile((unsigned char)c));                  // MW-mm 971010
    	  else                                                     // MW-mm 961227
    		  return(pbackfail(traits::to_int_type (c)));          // MW-mm 961227
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::sungetc ()
{
    LOCK(get_mut_block, get_lock);
    return (avail_putbackpos () ? 
            traits::to_int_type (*--gnext) : pbackfail ());
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::int_type
basic_streambuf<charT, traits>::sputc (char_type c)
{
    LOCK(put_mut_block, put_lock);
    return (avail_writepos () ? 
            traits::to_int_type (*pnext++ = c) : 
            overflow (traits::to_int_type (c)));
}

template <class charT, class traits>
inline
streamsize
basic_streambuf<charT, traits>::sputn (const char_type* s, streamsize n)
{
    LOCK(put_mut_block, put_lock);
    return xsputn (s, n);
}

template <class charT, class traits>
inline
void
basic_streambuf<charT, traits>::imbue (const locale& /* loc_arg */)
{
   // Does Nothing. Derived classes should take care of this.
}

template <class charT, class traits>
inline
locale
basic_streambuf<charT, traits>::pubimbue (const locale& loc_arg)
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    locale  loc_sav = loc;
    imbue (loc_arg);
    return  loc_sav;
}
 
template <class charT, class traits>
inline
locale
basic_streambuf<charT, traits>::getloc () const
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    return loc;
}
 
template <class charT, class traits>
inline
basic_streambuf<charT, traits>::~basic_streambuf ()
{
    REMOVE(put_lock);
    REMOVE(get_lock);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>::basic_streambuf ()
{
    init ();
}

typedef basic_streambuf<char, char_traits<char> >         streambuf;

#ifdef MSIPL_WCHART
typedef basic_streambuf<wchar_t, char_traits<wchar_t> >   wstreambuf;
#endif

#ifndef MSIPL_LOCALE_H
#error no locale
#endif

#ifdef __MSL_NO_INSTANTIATE__
	//these are instantiated in inst1.cpp, in the library, for char types
	template __dont_instantiate class basic_streambuf<char, char_traits<char> >;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_STREAMBUF_H */

/*   Change record
 * 961210 bkoz added alignment wrapper
 * MW-mm 961227 Changes to allow for dealing with bufferless files part of fix in fstream.h
 * 970404	bkoz	added __dont_instantiate support
 * 970406 bkoz moved basic_ios::imbue into streambuf.h so pubimbue defined.
 * mm 970711  Moved declarations from private to protected in accordance with Modena Version 2.2
 * mm 971010  This needs to be unsigned char just in case this gets compiled with signed chars as default.
 *            This fixes bug number MW00876
 */
