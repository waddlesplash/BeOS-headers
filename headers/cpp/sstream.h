/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_STRINGBUF_H
#define MSIPL_STRINGBUF_H

#include <mcompile.h>

#include MOD_INCLUDE(iostream)

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
class basic_stringbuf : public basic_streambuf<charT, traits> {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

public:
  
    typedef  char_traits<char_type>                   string_traits;
    typedef  basic_string<char_type, string_traits,
                          allocator<char_type> >      string_type;

public:

    explicit
    basic_stringbuf (ios_base::openmode which = 
                     ios_base::in | ios_base::out);

    explicit
    basic_stringbuf (const string_type& str,
                     ios_base::openmode which = 
                     ios_base::in | ios_base::out);

    virtual ~basic_stringbuf ();

    string_type
    str () const;

    void
    str (const string_type& str_arg);

protected:
//
//    Inherited functions
//    
    virtual int_type
    overflow (int_type c = traits::eof ());

    inline
    virtual void
    imbue (const locale& loc);

    virtual int_type
    pbackfail (int_type c = traits::eof ());
 
    virtual int_type
    underflow ();

    virtual pos_type
    seekoff (off_type off, ios_base::seekdir way,
             ios_base::openmode which = 
             ios_base::in | ios_base::out);
    
    virtual pos_type
    seekpos (pos_type sp, ios_base::openmode which = 
             ios_base::in | ios_base::out);

//
//    virtual streamsize
//    showmanyc ();
//
//    virtual int_type
//    uflow ();
//
//    virtual streamsize
//    xsgetn (char_type* s, streamsize n);
//
//    virtual streamsize
//    xsputn (const char_type* s, streamsize n);
// 
//    virtual basic_streambuf<char_type, traits>*
//    setbuf (char_type* s, streamsize n);
//
//    virtual int
//    sync ();
//
private:

    inline
    void
    init_string (const char_type* str, streamsize len, streamsize res);

    void
    init_copy (char_type* to, const char_type* from, streamsize len, 
               streamsize res);

    void
    clean_string ();

    char_type*               bend;   // To keep track of the buffer end
    ios_base::openmode       mode;

    char_type*               tmp;   // 970424 bkoz for ::overflow temporary buffer hack

    enum  buf_size { inc_size = 512 };

    // declare a mutex object.
    //
    DEC_OBJ_LOCK(_mutex)

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_istringstream : public basic_istream<charT, traits> {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;
 
public: 
 
    typedef  char_traits<char_type>                   string_traits;
    typedef  basic_string<char_type, string_traits,
                          allocator<char_type> >      string_type;
    typedef  basic_stringbuf<char_type, traits>       sb_type;

public:

    explicit
    basic_istringstream (ios_base::openmode which = ios_base::in);

    explicit
    basic_istringstream (const string_type& str,
                         ios_base::openmode which = ios_base::in);

    virtual  ~basic_istringstream ();

    inline
    sb_type*
    rdbuf () const;

    inline
    string_type
    str () const;

    inline
    void 
    str (const string_type& str);

private:

    sb_type   sbuf;

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_ostringstream : public basic_ostream<charT, traits> {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;
 
public:
 
    typedef  char_traits<char_type>                   string_traits;
    typedef  basic_string<char_type, string_traits,
                          allocator<char_type> >      string_type;
    typedef  basic_stringbuf<char_type, traits>       sb_type;

public:

    explicit
    basic_ostringstream (ios_base::openmode which = ios_base::out);

    explicit
    basic_ostringstream (const string_type& str,
                         ios_base::openmode which = ios_base::out);

    virtual  ~basic_ostringstream ();

    inline
    sb_type*
    rdbuf () const;

    inline
    string_type
    str () const;

    inline
    void 
    str (const string_type& str);

private:
 
    sb_type   sbuf;

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_stringstream : public basic_iostream<charT, traits> {

public:

    typedef  charT               char_type;
    typedef  traits              traits_type;

    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;
 
public: 
 
    typedef  char_traits<char_type>                   string_traits;
    typedef  basic_string<char_type, string_traits,
                          allocator<char_type> >      string_type;
    typedef  basic_stringbuf<char_type, traits>       sb_type;

public:

    explicit
    basic_stringstream (ios_base::openmode which = 
                          ios_base::in | ios_base::out);

    explicit
    basic_stringstream (const string_type& str,
                        ios_base::openmode which =
                          ios_base::in | ios_base::out);

    virtual  ~basic_stringstream ();

    inline
    sb_type*
    rdbuf () const;

    inline
    string_type
    str () const;

    inline
    void 
    str (const string_type& str);

private:

    sb_type   sbuf;

};

//#pragma dont_inline on	//970408 bkoz
template <class charT, class traits>
basic_stringbuf<charT, traits>::basic_stringbuf (ios_base::openmode which)
: basic_streambuf<charT, traits> (), mode (which) , bend (0), tmp(0)
{
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::basic_stringbuf (const string_type& str, 
	ios_base::openmode which)
: basic_streambuf<charT, traits> (), mode (which) , tmp(0)
{
    if (str.size () != 0)
    {
       init_string (str.data (), str.size (), 
                   (str.size ()/inc_size + 1)*inc_size);
    }
    else
    {
       bend = 0;
    }
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::~basic_stringbuf ()
{
    clean_string ();
    REMOVE(_mutex);
    if (tmp) {  //970424 bkoz to delete temporary buffer
    	delete [] tmp;
    }
}


template <class charT, class traits>
void
basic_stringbuf<charT, traits>::init_string (const char_type* str, 
                                streamsize len, streamsize res)
{
    char_type*  tmp = new char_type [res];
    init_copy (tmp, str, len, res);
}

template <class charT, class traits>
void
basic_stringbuf<charT, traits>::init_copy (char_type* to, 
                                const char_type* from, streamsize len, 
                                streamsize res)
{
    traits::copy (to, from, len);
    if ((mode & ios_base::in) != 0)
    {
        setg (to, to, to+len);
    }
    if ((mode & ios_base::out) != 0)
    {
        setp (to, to+len);
    }
    bend = to + res;
}

template <class charT, class traits>
void
basic_stringbuf<charT, traits>::clean_string ()
{
          /* mm 970710 begin insert */
    if (gnext) 
    	delete[] gbeg;
    else if (pnext) 
    	delete[] pbeg;
    gbeg = gnext = gend = pbeg= pnext = pend = bend = 0;
          /* mm 970710 end insert */
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::string_type
basic_stringbuf<charT, traits>::str () const
{
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    if (gptr () != 0)
    {
        return string_type (eback (), (((pptr () != 0) &&
                           (pptr () > egptr ())) ? pptr ()
                           : egptr ())-eback ());
    }
    else if (pptr () != 0)
    {
        return string_type (pbase (), pptr ()-pbase ());
    }
    else
    {
        return string_type ();
    }
}

template <class charT, class traits>
void
basic_stringbuf<charT, traits>::str (const string_type& str)
{
    WRITE_LOCK(_mutex);
    LOCK(put_mut_block, put_lock);
    LOCK(get_mut_block, get_lock);
    streamsize  len = 0;
    char_type*  tmp;
    //
    // mode should be either in or out
    if ((mode & ios_base::out) != 0)
    {
        tmp = pbase ();
    }
    else if ((mode & ios_base::in) != 0)
    {
        tmp = eback ();
    }
    len = bend-tmp;
    if (str.size () != 0)
    {
       if ((str.size () > len) || (tmp == 0))
       {
          clean_string ();
          init_string (str.data (), str.size (), 
                      ((str.size ()/inc_size+1)*inc_size));
       }
       else
       {
          init_copy (tmp, str.data (), str.size (), len);
       }
    }
    else
    {
       clean_string ();
    }
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::int_type
basic_stringbuf<charT, traits>::overflow (int_type c)
{
          /* mm 970710 begin insert */
    if(traits::eq_int_type(c,traits::eof())) 
    	return traits::not_eof(c);
    if(mode&ios_base::out) 
    {
       if(pend<bend) 
       	  pend++;
       else 
       {
          streamsize gsize = gnext - gbeg;
          streamsize psize = pnext - pbeg;
          size_t     nsize = (psize / inc_size+1) * inc_size;
          char_type* tmp   = new char_type[nsize];
          traits::copy(tmp, pbeg, psize);
          clean_string();
          pbeg  = tmp;
          pnext = pbeg + psize;
          pend  = pnext + 1;
          bend  = tmp + nsize;
          if (mode&ios_base::in)
          {
          	gbeg  = tmp;
          	gnext = gbeg + gsize;
          }
       }
       *pnext++=traits::to_char_type(c); 
       if(mode&ios_base::in)
          gend=pnext; 
       return c;
    }
    return traits::eof();
          /* mm 970710 end insert */
}

template <class charT, class traits>
void
basic_stringbuf<charT, traits>::imbue (const locale& loc_arg)
{
    loc = loc_arg;
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::int_type
basic_stringbuf<charT, traits>::pbackfail (int_type c)
{
//
// If the function can succeed in more than one of these ways,
// which way should be chosen ??
//
    if (avail_putbackpos ())
    {
        if (traits::eq_int_type (c, traits::eof ()))
        {
            gbump (-1);
            return traits::not_eof (c);
        }
        else
        {
            if (traits::eq_int_type (c, traits::to_int_type (gptr ()[-1])))
            {
                gbump (-1);
            }
            else if ((mode & ios_base::out) != 0)
            {
                gbump (-1);
                gptr ()[0] = traits::to_char_type (c);
            }
            else
            {
                return traits::eof ();
            }
        }
        return c;
    }
    return traits::eof ();
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::int_type
basic_stringbuf<charT, traits>::underflow ()
{
    if (gptr () != 0) 
    {
       if (((mode & ios_base::out) != 0) && 
          (! (gptr () < egptr ())) &&
          (pptr () > egptr ()))
       {
           setg (eback (), gptr (), pptr ());
       }
       if (gptr () < egptr ())
       {
           return traits::to_int_type (*gptr ());
       }
    }
    return traits::eof ();
}

template <class charT, class traits>
basic_stringbuf<charT, traits>::pos_type
basic_stringbuf<charT, traits>::seekoff (off_type off, ios_base::seekdir way,
                                         ios_base::openmode which)
{
    off_type   newoff = -1;
    
    if ((((which & ios_base::in)  == which) && (gptr ()!= 0)) ||
        (((which & ios_base::out) == which) && (pptr () !=0)) ||
        (((which & (ios_base::in | ios_base::out)) == 
          (ios_base::in | ios_base::out)) && (gptr ()!=0) && (pptr ()!=0) &&
         ((way & (ios_base::beg | ios_base::end)) != 0)))        
    {
        //
        // If more than one way is set, it is an error.
        //
        if (((way & ios_base::beg) == way) ||
            ((way & ios_base::end) == way) ||
            ((way & ios_base::cur) == way))
        {
            off_type   posin = 0;   // way == ios_base::beg
            //
            // if way == basic_ios::cur set posin = xnext - xbeg.
            if ((way & ios_base::cur) != 0)
            {
               if (gptr () != 0)
                   posin = gptr ()-eback ();
               else if (pptr () != 0)
                   posin = pptr ()-pbase ();
            }
            //
            // if way == basic_ios::end set posin = xend - xbeg.
            else if ((way & ios_base::end) != 0)
            {
               if ((gptr () != 0) && (egptr () > pptr ()))
                   posin = egptr ()-eback ();
               else if ((pptr () != 0) && (gptr () == 0))
                   posin = epptr ()-pbase ();
               else
               {
                   setg (eback (),gptr (),pptr ());
                   posin = pptr ()-eback ();
               }
            }
            if ((which & ios_base::in) != 0)
            {
                if (((posin + off) >= 0)  && 
                    ((egptr ()-eback ()) >= (posin + off)))
                {
                   newoff = posin+off;
                   gbump (eback ()-gptr ()+newoff);
                }
                if ((which & ios_base::out) != 0)
                   pbump (gptr ()-pptr ());
            }
            else if ((which & ios_base::out) != 0)
            {
                if (((posin + off) >= 0) && 
                    ((epptr ()-pbase ()) >= (posin + off)))
                {
                   newoff = posin+off;
                   pbump (pbase ()-pptr ()+newoff);
                }
            }
        }
    }
    return pos_type (newoff);
} 

template <class charT, class traits>
basic_stringbuf<charT, traits>::pos_type
basic_stringbuf<charT, traits>::seekpos (pos_type sp, ios_base::openmode which)
{
   off_type newoff = -1;

   if ((((which & ios_base::in)  == which) && (gptr ()== 0)) ||
        (((which & ios_base::out) == which) && (pptr () ==0)))
       return pos_type (newoff);
   
   if ((newoff = sp.offset ()) < 0)
         return pos_type (-1);

   if ((gptr () != 0) && (pptr () !=0) && (egptr () < pptr ()))
        setg (eback (), gptr (), pptr ());

   if ((which & ios_base::in) && (gptr () != 0))
   {
       if (newoff <= (egptr ()-eback ()))
       {
            gbump (newoff+eback ()-gptr ());
            //
            // If out specified then make next pointer of
            // output sequence equal to next pointer of input
            // sequence
            //
            if ((which & ios_base::out) && (pptr () != 0))
                pbump (gptr ()-pptr ());
       }
       else
            newoff = -1;
   }
   else if ((which & ios_base::out) && (pptr () != 0))
   {
       if (newoff <= (epptr ()-pbase ()))
            pbump (newoff+pbase ()-pptr ());
       else
            newoff = -1;
   }
   else
       newoff = -1;

   return pos_type (newoff);
}

//#pragma dont_inline on	//970408 bkoz
template <class charT, class traits>
basic_istringstream<charT, traits>::basic_istringstream (ios_base::openmode which)
: basic_istream<charT, traits> (0), sbuf (which) 
{ 
    init (&sbuf);
}

template <class charT, class traits>
basic_istringstream<charT, traits>::basic_istringstream
(const string_type& str, ios_base::openmode which)
: basic_istream<charT, traits> (0), sbuf (str, which) 
{
    init (&sbuf);
}

template <class charT, class traits>
basic_istringstream<charT, traits>::~basic_istringstream ()
{
}
// mf 101597 #pragma dont_inline reset	//970408 bkoz

template <class charT, class traits>
basic_istringstream<charT, traits>::sb_type*
basic_istringstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<sb_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<sb_type*> (&sbuf);
    return (sb_type*) (&sbuf);
}

template <class charT, class traits>
basic_istringstream<charT, traits>::string_type
basic_istringstream<charT, traits>::str () const
{
    return rdbuf ()->str ();
    // return sbuf.str ();
}

template <class charT, class traits>
void
basic_istringstream<charT, traits>::str (const string_type& str_arg)
{
    rdbuf ()->str (str_arg);
    // sbuf.str (str_arg);
}

//#pragma dont_inline on //970408 bkoz
template <class charT, class traits>
basic_ostringstream<charT, traits>::basic_ostringstream (ios_base::openmode which)
: basic_ostream<charT, traits> (0), sbuf (which) 
{ 
    init (&sbuf);
}

template <class charT, class traits>
basic_ostringstream<charT, traits>::basic_ostringstream
(const string_type& str, ios_base::openmode which)
: basic_ostream<charT, traits> (0), sbuf (str, which) 
{ 
    init (&sbuf);
}

template <class charT, class traits>
basic_ostringstream<charT, traits>::~basic_ostringstream ()
{
}
// mf 101597 #pragma dont_inline reset //970408 bkoz

template <class charT, class traits>
basic_ostringstream<charT, traits>::sb_type*
basic_ostringstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<sb_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<sb_type*> (&sbuf);
    return (sb_type*) (&sbuf);
}

template <class charT, class traits>
basic_ostringstream<charT, traits>::string_type
basic_ostringstream<charT, traits>::str () const
{
    return rdbuf ()->str ();
    // return sbuf.str ();
}

template <class charT, class traits>
void
basic_ostringstream<charT, traits>::str (const string_type& str_arg)
{
    rdbuf ()->str (str_arg);
    // sbuf.str (str_arg);
}


//
// basic_stringstream members
//

//#pragma dont_inline on //970408 bkoz
template <class charT, class traits>
basic_stringstream<charT, traits>::basic_stringstream (ios_base::openmode which)
: basic_iostream<charT, traits> (0), sbuf (which) 
{ 
    init (&sbuf);
}

template <class charT, class traits>
basic_stringstream<charT, traits>::
basic_stringstream (const string_type& str, ios_base::openmode which)
: basic_iostream<charT, traits> (0), sbuf (str, which) 
{
    init (&sbuf);
}

template <class charT, class traits>
basic_stringstream<charT, traits>::~basic_stringstream ()
{
}
// mf 101597 #pragma dont_inline reset //970408 bkoz

template <class charT, class traits>
basic_stringstream<charT, traits>::sb_type*
basic_stringstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<sb_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<sb_type*> (&sbuf);
    return (sb_type*) (&sbuf);
}

template <class charT, class traits>
basic_stringstream<charT, traits>::string_type
basic_stringstream<charT, traits>::str () const
{
    return rdbuf ()->str ();
    // return sbuf.str ();
}

template <class charT, class traits>
void
basic_stringstream<charT, traits>::str (const string_type& str_arg)
{
    rdbuf ()->str (str_arg);
    // sbuf.str (str_arg);
}
// mf 101597 #pragma dont_inline reset	//970408 bkoz
typedef basic_stringbuf<char, char_traits<char> >        stringbuf;
typedef basic_istringstream <char, char_traits<char> >  istringstream;
typedef basic_ostringstream <char, char_traits<char> >  ostringstream;
typedef basic_stringstream <char, char_traits<char> >    stringstream;

#ifdef MSIPL_WCHART
typedef basic_stringbuf<wchar_t, char_traits<wchar_t> >        wstringbuf;
typedef basic_istringstream <wchar_t, char_traits<wchar_t> >  wistringstream;
typedef basic_ostringstream <wchar_t, char_traits<wchar_t> >  wostringstream;
typedef basic_stringstream <wchar_t, char_traits<wchar_t> >    wstringstream;
#endif

#ifdef __MSL_NO_INSTANTIATE__
	//these are instantiated in inst1.cpp, in the library, for char types
	template __dont_instantiate class basic_stringbuf<char, char_traits<char> >;
	template __dont_instantiate class basic_istringstream<char, char_traits<char> >;
	template __dont_instantiate class basic_ostringstream<char, char_traits<char> >;
	template __dont_instantiate class basic_stringstream<char, char_traits<char> >;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_STRINGBUF_H */

/*   Change record
 * 961210 bkoz 	added alignment wrapper
 * 970424 bkoz 	line 452 overflow needs to have tmp deallocated, so
 * 				move into basic_stringbuf as a data member charT* tmp
 * 				init to zero in ctors, destroy in dtor
 * 				check for non-zero in overflow, if so delete--NOTE THIS IS NOT SAFE
 * 				looking for better approach. Should copy this into another tmp buffer 
 * 				before deallocating and set pointers in stringbuf to this tmp buffer.
 * 				(what a mess)
 * mm 970710  Incorporated changes from Modena Version 2.2, 27th February 1997 
 */
