/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_ISTREAM_H
#define MSIPL_ISTREAM_H

#include <mcompile.h>

#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(limits)
#else
#include MOD_INCLUDE(mlimits)
#endif

#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(extmath)
#include MOD_INCLUDE(streambuf)
#include <errno.h>

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
class basic_istream : virtual public basic_ios<charT, traits> {

public:

    typedef  charT                  char_type;
    typedef  traits                 traits_type;

    typedef typename  traits::pos_type       pos_type;
    typedef typename  traits::off_type       off_type;
    typedef typename  traits::int_type       int_type;

protected:

//
// For abbreviation
//
    typedef  basic_istream<char_type, traits>     istream_type;
    typedef  basic_streambuf<char_type, traits>   streambuf_type;

private:

    typedef  istreambuf_iterator<char_type, char_traits<char_type>,
                                 ptrdiff_t >                         iter_type;

    typedef  num_get<char_type, istreambuf_iterator<char_type,
                     char_traits<char_type>, ptrdiff_t > >          facet_type;

    typedef  ctype<char_type>                                      ctype_facet;

public:

    explicit
    basic_istream (streambuf_type*  sb);

    basic_istream (ios_base::fmt_flags fmt_arg);

    virtual 
    ~basic_istream ();

    class sentry {

        bool ok_;
        
        typedef  ctype<char_type>         ctype_facet;

    public:

        //explicit sentry (basic_istream<charT, traits>& is, bool noskipws = false);
        explicit sentry (basic_istream<charT, traits>& is, bool noskipws = false)	//961206 bkoz
				{
				#ifdef MSIPL_EXCEPT
				    try {
				#endif
				    // setting chcount to 0 for unformatted functions
				    is.setcount ();
				    ok_ = false;

				    if (is.good ())
				    {
				       if (is.tie () != 0)
				       {
				           // this call may not occur if no synchronization is necessary
				           // can that situation be determined here
				           is.tie ()->flush ();
				       }
				       if ((!noskipws) && (is.flags () & ios_base::skipws))
				       {
				           //
				           // extract and discard each character as long as the next 
				           // available input character c is a whitespace character
				           //
				           int_type  ch;
				           const ctype_facet& ct= use_facet (is.getloc (), (ctype_facet *)0);

				           ch = is.rdbuf ()->sbumpc ();
				           while ((!traits::eq_int_type (ch, traits::eof ())) && 
				                   ct.is (ct.space, ch))
				               ch = is.rdbuf ()->sbumpc ();
				           if (traits::eq_int_type (ch, traits::eof ()))
				           {
				               is.setstate (eofbit);
				           }
				           else
				           {
				               is.rdbuf ()->sputbackc (traits::to_char_type (ch));
				           }
				       }
				       if (is.good ())
				       {
				           ok_ = true;
				       }
				    }

				#ifdef MSIPL_EXCEPT
				    }
				    catch (...)
				    {
				    }
				#endif
				    if (!is.good ())
				        is.setstate (failbit);
				}


        ~sentry () {};
        
        operator bool () { return ok_; }
    };

    inline
    istream_type& 
    operator>> (istream_type& (*pf) (istream_type&));

    inline
    istream_type& 
    operator>> (ios_base& (*pf) (ios_base&));

    istream_type& 
    operator>> (char_type* s);

    istream_type& 
    operator>> (char_type& c);

#ifdef MSIPL_BOOL_BUILTIN

    istream_type& 
    operator>> (bool& n);

#endif

    istream_type& 
    operator>> (short& n);

    istream_type& 
    operator>> (unsigned short& n);

    istream_type& 
    operator>> (int& n);

    istream_type& 
    operator>> (unsigned int& n);

    istream_type& 
    operator>> (long& n);

    istream_type& 
    operator>> (unsigned long& n);

#ifdef __MSL_LONGLONG_SUPPORT__                  /* mm 970110 */
    istream_type&                                /* mm 970110 */
    operator>> (long long& n);                   /* mm 970110 */
                                                 /* mm 970110 */
    istream_type&                                /* mm 970110 */
    operator>> (unsigned long long& n);          /* mm 970110 */
#endif   /* __MSL_LONGLONG_SUPPORT__*/           /* mm 970110 */

    istream_type&
    operator>> (float& f);

    istream_type&
    operator>> (double& f);

    istream_type&
    operator>> (long double& f);

    istream_type&
    operator>> (void*& p);

    istream_type&
    operator>> (streambuf_type* sb);

    int_type
    get ();

    istream_type&
    get (char_type* s, streamsize n, char_type delim = traits::newline ());

    inline
    istream_type&
    get (char_type& c);

    istream_type&
    get (streambuf_type& sb, char_type delim = traits::newline ());

    istream_type&
    getline (char_type* s, streamsize n,
             char_type delim = traits::newline ());

    istream_type&
    ignore (streamsize n = 1, int_type delim = traits::eof ());

    istream_type&
    read (char_type* s, streamsize n);

    streamsize 
    readsome (char_type* s, streamsize n);

    int_type
    peek ();

    istream_type&
    putback (char_type c);

    istream_type&
    unget ();

    inline
    streamsize
    gcount () const;

    inline
    void
    setcount (int cnt = 0);

    int
    sync ();

    pos_type
    tellg ();

    istream_type&
    seekg (pos_type);

    istream_type&
    seekg (off_type, ios_base::seekdir);

private:

    streamsize  chcount;

    // declare a mutex object.
    //
    DEC_MUTEX(_mutex)

};

//
// Manipulators -- Standard basic_istream
//
template <class charT, class traits>
basic_istream<charT, traits>&  
ws (basic_istream<charT, traits>&  is);


template <class charT, class traits>
inline
basic_istream<charT, traits>::basic_istream (streambuf_type* sb)
: basic_ios<charT, traits> (sb), chcount (0) 
{ 
}

template <class charT, class traits>
inline
basic_istream<charT, traits>::
basic_istream (ios_base::fmt_flags fmt_arg)
: basic_ios<charT, traits> (fmt_arg) 
{ 
}

template <class charT, class traits>
inline
basic_istream<charT, traits>::~basic_istream () 
{ 
    REMOVE(_mutex);
}

/*
template <class charT, class traits>
inline
basic_istream<charT, traits>::
sentry::sentry (basic_istream<charT, traits>& is, bool noskipws)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    // setting chcount to 0 for unformatted functions
    is.setcount ();
    ok_ = false;

    if (is.good ())
    {
       if (is.tie () != 0)
       {
           // this call may not occur if no synchronization is necessary
           // can that situation be determined here
           is.tie ()->flush ();
       }
       if ((!noskipws) && (is.flags () & ios_base::skipws))
       {
           //
           // extract and discard each character as long as the next 
           // available input character c is a whitespace character
           //
           int_type  ch;
           const ctype_facet& ct= use_facet (is.getloc (), (ctype_facet *)0);

           ch = is.rdbuf ()->sbumpc ();
           while ((!traits::eq_int_type (ch, traits::eof ())) && 
                   ct.is (ct.space, ch))
               ch = is.rdbuf ()->sbumpc ();
           if (traits::eq_int_type (ch, traits::eof ()))
           {
               is.setstate (eofbit);
           }
           else
           {
               is.rdbuf ()->sputbackc (traits::to_char_type (ch));
           }
       }
       if (is.good ())
       {
           ok_ = true;
       }
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
    }
#endif
    if (!is.good ())
        is.setstate (failbit);
}
*/
template <class charT, class traits>
inline
int
basic_istream<charT, traits>::sync ()
{
    if (rdbuf () == 0)
    {
        return -1;
    }
    else
    {
        LOCK(mut_block,_mutex);
        if ((rdbuf ()->pubsync ()) == -1)
        {
            setstate (badbit);
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::
operator>> (istream_type& (*pf) (istream_type&))
{
    LOCK(mut_block,_mutex);
    return (*pf) (*this);
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::
operator>> (ios_base& (*pf) (ios_base&))
{
    LOCK(mut_block,_mutex);
    (*pf) (*this);
    return *this;
}
    
template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (void*& p)
{
   fmtflags  flag_sav = flags ();
   char_type buf[200];
   void *result = 0;
   char_type fmt[5];

   fmt[0] = '%';
   fmt[1] = 'p';
   fmt[2] = traits_type::eos ();

   LOCK(mut_block,_mutex);

#ifdef MSIPL_EXCEPT
   try {
#endif
    sentry  s_ (*this);
    if (s_)
    {
        char_type*  ssav  = buf;
        int_type    ch;
	    const ctype_facet& ct= use_facet (getloc (), (ctype_facet *)0);
        while ((!traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                       traits::eof ())) &&
               (!ct.is (ct.space, ch)))
            *ssav++ = traits::to_char_type (ch);
        *ssav = traits::eos ();

        if (ct.is (ct.space, ch))
            rdbuf ()->sputbackc (traits::to_char_type (ch));
        if (traits::eq_int_type (ch, traits::eof ()))
            setstate (eofbit);
        if (ssav == buf)
            setstate (failbit);
        
        int scanned = __msipl_sscanf (buf, fmt, &result);

        if ( scanned != 1 || errno )
            setstate (failbit);
        else
            p = result;
    }
#ifdef MSIPL_EXCEPT
   }
   catch (...)
   {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
   }
#endif
   return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (char_type* s)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_(*this);
    if (s_)
    {
        int  count = width () > 0 ? width () 
                                    : numeric_limits<int>::max ();

        char_type*  ssav  = s;
        int_type    ch = rdbuf ()->sgetc ();
	    const ctype_facet& ct= use_facet (getloc (), (ctype_facet *)0);
        for (; 0 < --count; ch = rdbuf ()-> snextc ())
             if(ct.is (ct.space, ch))
                  break;
             else if (traits::eq_int_type (ch, traits::eof ()))
                  {  setstate (eofbit); 
                  break; }
             else
             {
                  *ssav++ = traits::to_char_type (ch);
                  if (traits::eq_int_type (ch, traits::eos ()))
                       break;
             }
        *ssav = traits::eos();
        width(0);
        if (ssav == s) setstate (failbit);
    }

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif

    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (char_type& c)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    int_type  ch;

    sentry s_(*this);
    if (s_)
        if (!(traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                   traits::eof ()))) 
            c = traits::to_char_type (ch);
        else
            setstate (failbit);
    else
        setstate (failbit);
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

#ifdef MSIPL_BOOL_BUILTIN

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (bool& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
    sentry s_(*this);
    if (s_)
    {
       short int state_arg = ios_base::goodbit;
       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

#endif /* MSIPL_BOOL_BUILTIN */

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (short& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short   nval;
       long    val;
       short int state_arg = ios_base::goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, val);
       if ((state_arg & failbit) == 0)
       {
          nval = (short)val;
          if (nval != val)
             setstate (failbit);
          else
              n = nval;
       }
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (int& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       long      val;
       int       nval;
       short int  state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, val);
       if (!(state_arg & failbit))
       {
          nval = (int)val;
          if (nval != val)
             setstate (failbit);
          else
              n = nval;
       }
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (long& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int  state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}


#ifdef __MSL_LONGLONG_SUPPORT__                          /* mm 970110 */
template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (long long& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int  state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                     /* mm 970110 */

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (unsigned short& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int      state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
           
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (unsigned int& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int        state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (unsigned long& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int       state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

#ifdef __MSL_LONGLONG_SUPPORT__                                /* mm 970110 */
template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (unsigned long long& n)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int       state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, n);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                /* mm 970110 */

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (float& f)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, f);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (double& f)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, f);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (long double& f)
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_(*this);
    if (s_)
    {
       short int     state_arg = goodbit;

       const facet_type&  fmt = use_facet (getloc (), (facet_type*)0);
       fmt.get (*this, iter_type (), *this, state_arg, f);
       setstate (state_arg);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}


template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::operator>> (streambuf_type*  sb)
{
    bool        point = false;
    bool        fail_set = false;
    int_type    ch;
    streamsize  count = 0;

    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
    if (!sb)
        setstate (ios_base::badbit);
    sentry s_(*this);
    if (s_)
    {
        while ((! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                         traits::eof ()))))
        {
            point = true;
            if (traits::eq_int_type (sb->sputc (traits::to_char_type (ch)),
                                     traits::eof ()))
            {
                rdbuf ()->sputbackc (traits::to_char_type (ch));
                break;
            }
            else
                count++;
            point = false;
        }
        if (traits::eq_int_type (ch, traits::eof ()))
           setstate (eofbit);
        if (count == 0)
        {
           fail_set = true;
           setstate (failbit);
        }
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        if (count == 0 && !fail_set)
        {
            fail_set = true;
            setstate (failbit);
        }
        if (point)
            rdbuf ()->sputbackc (traits::to_char_type (ch));
        else 
            if (exceptions () & failbit)
                throw;
    }
#endif
    if (count == 0 && !fail_set)
        setstate (failbit);
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>::int_type
basic_istream<charT, traits>::get ()
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
    
    int_type   ch;

    sentry s_ (*this, true);
    if (s_)
    {
        if (! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                    traits::eof ())))
            chcount  = 1;
    }
    if (chcount == 0)
    {
       setstate (failbit);
       return traits::eof ();
    }
    else
       return ch;
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif

    return traits::eof ();
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::
get (char_type* s, streamsize n, char_type delim)
{
    LOCK(mut_block,_mutex);
    bool fail_set = false;
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this, true);
    if (s_)
    {
        int_type    ch;
        if (n != 0)
        {
            while ((--n > 0) &&
                  (! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()), 
                                           traits::eof ()))) &&
                  (traits::to_char_type (ch) != delim))
            {
                *s++ = traits::to_char_type (ch);
                chcount++;
            }
            if (traits::eq_int_type (ch, traits::eof ()))
                setstate (eofbit);
            else if (traits::to_char_type (ch) == delim)
                rdbuf ()->sputbackc (traits::to_char_type (ch));
        }
        *s = traits::eos ();
        if (chcount == 0)
        {
            fail_set = true;
            setstate (failbit);
        }
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        *s = traits::eos ();
        if (chcount == 0 && !fail_set)
            setstate (failbit);
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::get (char_type& c)
{
    LOCK(mut_block,_mutex);
    int_type  ch = get ();
    if (! (traits::eq_int_type (ch, traits::eof ())))
        c = traits::to_char_type (ch);
    return *this;
}


template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::get (streambuf_type& sb, char_type delim)
{
    bool  point    = false;
    bool  fail_set = false;
    int_type      ch;

    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_ (*this, true);
    if (s_)
    {
        while (! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                       traits::eof ())))
        {
            point = true;
            if ((traits::to_char_type (ch) == delim) ||
                (traits::eq_int_type (sb.sputc (traits::to_char_type (ch)), 
                                      traits::eof ())))
            {
                rdbuf ()->sputbackc (traits::to_char_type (ch));
                break;
            }
            else
                chcount++;
            point = false;
        }
        if (traits::eq_int_type (ch, traits::eof ()))
            setstate (eofbit);
        if (chcount == 0)
        {
            fail_set = true;
            setstate (failbit);
        }
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        if (point)
            rdbuf ()->sputbackc (traits::to_char_type (ch));
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
    if (chcount == 0 && !fail_set)
        setstate (failbit);
 
    return *this;
}


template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::getline (char_type* s, streamsize n, 
                                       char_type delim)
{
    LOCK(mut_block,_mutex);
    bool fail_set = false;
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this, true);
    if (s_)
    {
        int_type    ch;
        if (n != 0)
        {
            while ((! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                            traits::eof ()))) &&
                   (traits::to_char_type (ch) != delim) && 
                  (--n > 0)) 
            {
                *s++ = traits::to_char_type (ch);
                chcount++;
            }
            if (traits::eq_int_type (ch, traits::eof ()))
                setstate (eofbit);
            else if (traits::to_char_type (ch) == delim)
                chcount++;
            else if (n == 0)
            {
                rdbuf ()->sputbackc (traits::to_char_type (ch));
                setstate (failbit);
            }
        }
        *s = traits::eos ();
        // To check this code
        if (chcount == 0) 
        {
            fail_set = true;
            setstate (failbit);
        }
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        *s = traits::eos ();
        if (chcount == 0 && !fail_set)
            setstate (failbit);
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::ignore (streamsize n, int_type delim)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif

    sentry s_ (*this, true);
    if (s_)
    {
        int_type    ch;
        while (((n == numeric_limits<int>::max ()) || (n-- > 0)) &&
              (! (traits::eq_int_type ((ch = rdbuf ()->sbumpc ()),
                                       traits::eof ()))))
        {
            ++chcount;
            if (ch == delim)
                break;
        }
        if (traits::eq_int_type (ch, traits::eof ()))
            setstate (eofbit);
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::read (char_type* s, streamsize n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    sentry s_ (*this, true);
    if (s_)
    {
        streamsize ch_read = rdbuf()->sgetn (s, n);
        chcount += ch_read;
        if (ch_read != n)
            setstate (ios_base::eofbit | ios_base::failbit); 
    }
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
streamsize
basic_istream<charT, traits>::readsome (char_type* s, streamsize n)
{
    LOCK(mut_block,_mutex);
#ifdef MSIPL_EXCEPT
    try {
#endif
    sentry s_ (*this, true);
    if (s_)
    {
        streamsize  navail = rdbuf ()->in_avail ();
        if (navail == 0)
           setstate (eofbit);
        else
	    if (navail > 0)
           read (s,min (n,navail));
    }
    else
        setstate (failbit);
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return streamsize (chcount);
}

template <class charT, class traits>
inline
basic_istream<charT, traits>::int_type
basic_istream<charT, traits>::peek ()
{
    int_type ch; 
#ifdef MSIPL_EXCEPT
    try {
#endif

    ch = (good () ? (rdbuf ()->sgetc ()) : traits::eof ());

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return ch;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::putback (char_type c)
{
#ifdef MSIPL_EXCEPT
    try {
#endif

    if (!rdbuf ())
        setstate (badbit);
    sentry s_ (*this, true);
    if (s_ && traits::eq_int_type (rdbuf ()->sputbackc (c),
                                   traits::eof ()))
       setstate (badbit);

#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::unget ()
{
#ifdef MSIPL_EXCEPT
    try {
#endif
 
    if (!rdbuf ())
        setstate (badbit);
    sentry s_ (*this, true);
    if (s_ && traits::eq_int_type (rdbuf ()->sungetc (),
                                   traits::eof ()))
       setstate (badbit);
 
#ifdef MSIPL_EXCEPT
    }
    catch (...)
    {
        setstate (badbit);
        if (exceptions () & badbit)
            throw;
    }
#endif
 
    return *this;
}

template <class charT, class traits>
inline
streamsize
basic_istream<charT, traits>::gcount () const
{
    LOCK(mut_block,_mutex);
    return chcount;
}

template <class charT, class traits>
inline
void
basic_istream<charT, traits>::setcount (int cnt)
{
    LOCK(mut_block,_mutex);
    chcount = cnt;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>::pos_type
basic_istream<charT, traits>::tellg ()
{
    if (fail ())
        return pos_type (-1);
    return (rdbuf ()->pubseekoff (0, ios_base::cur, ios_base::in));
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::seekg (pos_type pos)
{
    if (!fail ())
        rdbuf ()->pubseekpos (pos);

    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
basic_istream<charT, traits>::seekg (off_type off,
                                     ios_base::seekdir dir)
{
    if (!fail ())
        rdbuf ()->pubseekoff (off,dir);

    return *this;
}

template <class charT, class traits>
inline
basic_istream<charT, traits>&
ws (basic_istream<charT, traits>&  is)
{
    ios_base::fmtflags  fmtflag_sav  =  is.flags ();

    is.setf (ios_base::skipws);
    typename basic_istream<charT, traits>::sentry s_ (is);
    is.flags (fmtflag_sav);

    return is;
}

typedef basic_istream<char, char_traits<char> >       istream;

#ifdef MSIPL_WCHART
typedef basic_istream<wchar_t, char_traits<wchar_t> >   wistream;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_ISTREAM_H */

//961206 received from atul
//961206 bkoz lines 237-295 moved inline to line 80 so cw will compile nested class ctor
//961210 bkoz added wrapper for alignment
//mm 970110  long long support
