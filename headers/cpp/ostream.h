/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_OSTREAM_H
#define MSIPL_OSTREAM_H

#include <mcompile.h>

#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(streambuf)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif   /*MSIPL_USING_NAMESPACE*/

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif /*MSIPL_DEF_TEMPARG*/
class basic_ostream : virtual public basic_ios<charT, traits> {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

protected:

    typedef  basic_ostream<char_type, traits>        ostream_type;
    typedef  basic_streambuf<char_type, traits>      streambuf_type;

private:

    typedef  ostreambuf_iterator<char_type,
             char_traits<char_type> >    iter_type;
    typedef  num_put<char_type, ostreambuf_iterator<char_type,
             char_traits<char_type> > >  facet_type;

    // declare a mutex object.
    //
    DEC_MUTEX(_mutex)

public:

    class sentry {

        bool ok_;
        basic_ostream <charT, traits>* pos;

    public:

        //explicit
        //sentry (basic_ostream<charT, traits>& os);
		 sentry (basic_ostream<charT, traits>& os) : pos (&os)
		{
		    if (os.good ())
		    {
		        if (os.tie ())
		        {
		            os.tie ()->flush ();
		        }
		    }
		    if (os.good ())
		        ok_ = true;
		    else
		        ok_ = false;
		}


        ~sentry ()
  		{
		    if (pos->flags () & unitbuf)
		        pos->flush ();
		    // Is it the right place to reset width ?
		    pos->width (0);
		}


        operator bool () { return ok_; }
    };

    explicit
    basic_ostream (streambuf_type* sb);

    basic_ostream (ios_base::fmt_flags fmt_arg);
 
    virtual ~basic_ostream ();

    inline
    ostream_type& 
    operator<< (ostream_type& (*pf) (ostream_type&));

    inline
    ostream_type& 
    operator<< (ios_base& (*pf) (ios_base&));

    ostream_type& 
    operator<< (const char_type* s);

    ostream_type& 
    operator<< (char_type c);

#ifdef MSIPL_BOOL_BUILTIN

    ostream_type& 
    operator<< (bool n);

#endif  //MSIPL_BOOL_BUILTIN

    inline
    ostream_type& 
    operator<< (short n);

    inline
    ostream_type& 
    operator<< (unsigned short n);

    inline
    ostream_type& 
    operator<< (int n);

    inline
    ostream_type& 
    operator<< (unsigned int n);

    inline                                              
    ostream_type& 
    operator<< (long n);

    inline                                               
    ostream_type& 
    operator<< (unsigned long n);

#ifdef __MSL_LONGLONG_SUPPORT__                          /*mm 970110*/
    inline                                               /*mm 970110*/
    ostream_type&                                        /*mm 970110*/
    operator<< (long long n);                            /*mm 970110*/

    inline                                               /*mm 970110*/
    ostream_type&                                        /*mm 970110*/
    operator<< (unsigned long long n);                   /*mm 970110*/

#endif   /* __MSL_LONGLONG_SUPPORT__*/                   /*mm 970110*/

    inline
    ostream_type&
    operator<< (float f);

    ostream_type&
    operator<< (double f);

    ostream_type&
    operator<< (long double f);

    ostream_type&
    operator<< (void* p);

    ostream_type&
    operator<< (streambuf_type* sb);

    ostream_type&
    put (char_type c);

    ostream_type&
    write (const char_type* s, streamsize n);

    ostream_type&
    flush ();

    pos_type
    tellp ();

    ostream_type&
    seekp (pos_type);

    ostream_type&
    seekp (off_type, ios_base::seekdir);


};

//
// Manipulators -- Standard basic_ostream
//
template <class charT, class traits>
basic_ostream<charT, traits>&  
endl (basic_ostream<charT, traits>&  os);

template <class charT, class traits>
basic_ostream<charT, traits>&  
ends (basic_ostream<charT, traits>&  os);

template <class charT, class traits>
basic_ostream<charT, traits>&  
flush (basic_ostream<charT, traits>&  os);

template <class charT, class traits>
inline
basic_ostream<charT, traits>::basic_ostream (streambuf_type* sb)
: basic_ios<charT, traits> (sb) { }

template <class charT, class traits>
inline
basic_ostream<charT, traits>::basic_ostream (ios_base::fmt_flags fmt_arg)
: basic_ios<charT, traits> (fmt_arg) { }
 
template <class charT, class traits>
inline
basic_ostream<charT, traits>::~basic_ostream ()
{
	flush();					/* Be-mani 960829 */
    REMOVE(_mutex);
}//961113 bkoz move inline to get around compiler error. . 
/*
template <class charT, class traits>
inline
basic_ostream<charT, traits>::
sentry::sentry (basic_ostream<charT, traits>& os)
  : pos (&os)
{
    if (os.good ())
    {
        if (os.tie ())
        {
            os.tie ()->flush ();
        }
    }
    if (os.good ())
        ok_ = true;
    else
        ok_ = false;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>::
sentry::~sentry ()
{
    if (pos->flags () & unitbuf)
        pos->flush ();
    // Is it the right place to reset width ?
    pos->width (0);
}
*/
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::flush ()
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif  //MSIPL_EXCEPT

    if ((rdbuf () != 0) && ((rdbuf ()->pubsync ()) == -1))
        setstate (badbit);

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif  //MSIPL_EXCEPT

    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (ostream_type& (*pf) (ostream_type&))
{
    LOCK(mut_block,_mutex);
    return (*pf) (*this);
}
 
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (ios_base& (*pf) (ios_base&))
{
    LOCK(mut_block,_mutex);
    (*pf) (*this);
    return *this;
}


template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (long n)
{
    LOCK(mut_block,_mutex);

#ifdef MSIPL_EXCEPT
    try {
#endif  //MSIPL_EXCEPT
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), n);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif  //MSIPL_EXCEPT
 
    return *this;

}

#ifdef __MSL_LONGLONG_SUPPORT__                   /*mm 970110*/
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (long long n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif  //MSIPL_EXCEPT
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), n);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif  //MSIPL_EXCEPT
 
    return *this;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      /*mm 970110*/

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (unsigned long n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif  //MSIPL_EXCEPT
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), n);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif  //MSIPL_EXCEPT
 
    return *this;
}

#ifdef __MSL_LONGLONG_SUPPORT__                   /*mm 970110*/
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (unsigned long long n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), n);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      /*mm 970110*/

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (double f)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), f);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (long double f)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this,  *this, fill (), f);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (short n)
{
    LOCK(mut_block,_mutex);
    return (*this << (long)n);                              
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (int n)
{
    LOCK(mut_block,_mutex);
    return (*this << (long)n);                              
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (unsigned short n)
{
    LOCK(mut_block,_mutex);
    return (*this << (unsigned long)n);                     
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (unsigned int n)
{
    LOCK(mut_block,_mutex);
    return (*this << (unsigned long)n);                     
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (float f)
{
    LOCK(mut_block,_mutex);
    return (*this << (double)f);
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::put (char_type c)
{
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this);
    if (! (s_ && !traits::eq_int_type ((rdbuf ()->sputc (c)),
                                       traits::eof ())))
    {
       setstate (badbit);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::write (const char_type* s, streamsize n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this);
    if (s_ && (n != rdbuf ()->sputn (s, n)))
    {
        setstate (badbit);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (streambuf_type*  sb)
{
    int_type    ch;
    bool        point = false;
    streamsize  count = 0;

    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif

    if (!sb)
        setstate (ios_base::badbit);
    sentry s_ (*this);
    if (s_) 
    {
        while ((! (traits::eq_int_type ((ch = sb->sbumpc ()),
                                        traits::eof ()))))
        {
            point = true;
            if (traits::eq_int_type (rdbuf ()->sputc (ch),
                                     traits::eof ()))
            {
                sb->sputbackc (traits::to_char_type (ch));
                break;
            }
            else
            {
                count++;
            }
            point = false;
        }
        if (count == 0)
        {
           setstate (failbit);
        }
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (failbit);
        if (point)
        {
            sb->sputbackc (traits::to_char_type (ch));
            if (exceptions () & failbit)
            {
                throw;
            }
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (const char_type* s)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this);
    if (s_)
    {
        streamsize prcount   = traits::length (s);
        streamsize fillcount = max (width (), prcount) - prcount;

        //
        // Can the following code be implemented in a better way ?
        if ((flags () & adjustfield) == right)
        {
            while ((fillcount > 0) && 
                   !traits::eq_int_type (rdbuf ()->
                   sputc (traits::to_char_type (fill ())), traits::eof ()))
                --fillcount;
            if ((rdbuf()->sputn (s, prcount)) != prcount)
                setstate (failbit);
        }
        else
        {
            if ((rdbuf()->sputn(s, prcount)) != prcount)
                setstate (failbit);
            while ((fillcount > 0) &&
                   !traits::eq_int_type (rdbuf ()->
                   sputc (traits::to_char_type (fill ())), traits::eof ()))
                --fillcount;
        }
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (failbit);
        if (exceptions () & failbit)
        {
            throw;
        }
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (char_type c)
{
#ifdef MSIPL_EXCEPT
    try {
#endif

    int wide_arg = width ();

    {  // Dummy Block to make sure that sentry destructor is called.
        sentry s_ (*this);
        if (s_)
        {
           rdbuf ()->sputc (c);
        }
    }
    width (wide_arg);

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif

    return *this;
}

#ifdef MSIPL_BOOL_BUILTIN
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (bool n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this);
    if (s_)
    {
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.put (*this, *this, fill (), n);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
        {
            throw;
        }
    }
#endif

    return *this;
}

#endif

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::operator<< (void* b)
{
   fmtflags  flag_sav = flags (0);
   char_type buf[200];
   char_type fmt[5];

   fmt[0] = '%';
   fmt[1] = 'p';
   fmt[2] = traits_type::eos ();

   width (0);

#ifdef MSIPL_EXCEPT
    try {
#endif
      __msipl_sprintf (buf, sizeof (buf)/sizeof (charT), fmt, b);

      *this << buf;

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
       flags (flag_sav);
       throw;
    }
#endif
    flags (flag_sav);
    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
endl (basic_ostream<charT, traits>&  os)
{
    os.put (traits::newline ());
    os.flush ();
    return os;
}
 
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
ends (basic_ostream<charT, traits>&  os)
{
    os.put (traits::eos ());
    // should we flush the stream?
    // os.flush ();
    return os;
}
 
template <class charT, class traits>
inline
basic_ostream<charT, traits>&
flush (basic_ostream<charT, traits>&  os)
{
    os.flush ();
    return os;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>::pos_type
basic_ostream<charT, traits>::tellp ()
{
    LOCK(mut_block,_mutex);
    if (fail ())
        return pos_type (-1);

    return (rdbuf ()->pubseekoff (0, ios_base::cur, ios_base::out));
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::seekp (pos_type pos)
{
    LOCK(mut_block,_mutex);
    if (!fail ())
        rdbuf ()->pubseekpos (pos);

    return *this;
}

template <class charT, class traits>
inline
basic_ostream<charT, traits>&
basic_ostream<charT, traits>::seekp (off_type off, ios_base::seekdir dir)
{
    LOCK(mut_block,_mutex);
    if (!fail ())
        rdbuf ()->pubseekoff (off, dir);

    return *this;
}


typedef basic_ostream<char, char_traits <char> >         ostream;

#ifdef MSIPL_WCHART
typedef basic_ostream<wchar_t, char_traits <wchar_t> >   wostream;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif /*MSIPL_USING_NAMESPACE*/

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_OSTREAM_H */

/* Change record
//961113 bkoz moved sentry::~sentry line 217 to line 80....
//961210 bkoz added alignment wrapper
//mm 970110   long long support
*/
/* Be-mani 960829	Add a call to flush to basic_ostream destructor. */
