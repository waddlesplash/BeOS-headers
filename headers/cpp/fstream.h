/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.0, July 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_FSTREAM_H
#define MSIPL_FSTREAM_H

#include <mcompile.h>

#include MOD_INCLUDE(iostream)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#define __msipl_temp_bufsize   8

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_filebuf : public basic_streambuf<charT, traits> {
public :

    typedef  charT                             char_type;
    typedef  traits                            traits_type;
 
    typedef typename  traits::pos_type                  pos_type;
    typedef typename  traits::off_type                  off_type;
    typedef typename  traits::int_type                  int_type;
    typedef typename  traits::state_type                state_type;
 
    typedef  basic_filebuf<charT, traits>      filebuf_type;

private:

    typedef codecvt<char_type,char,state_type> ofacet_type;
    typedef codecvt<char,char_type,state_type> ifacet_type;
    typedef codecvt_base::result               result;
    const ofacet_type* ftype;
    void set_facet();
    bool no_conversion_required;

public:

    basic_filebuf ();

    basic_filebuf (FILE* pfile_arg);

    virtual ~basic_filebuf ();

    bool 
    is_open () const;

    filebuf_type*
    open (const char* s, ios_base::openmode mode);

    filebuf_type*
    close ();


protected :

    //
    // Inherited Functions
    //
    virtual int_type 
    overflow (int_type c = traits::eof ());

    virtual int_type 
    pbackfail (int_type c = traits::eof ());

    virtual int_type                               //MW-mm 961227
    __pbfile(int_type);                            //MW-mm 961227

    virtual int_type 
    underflow ();

    virtual pos_type 
    seekoff (off_type off, ios_base::seekdir way,
             ios_base::openmode which = 
             ios_base::in | ios_base::out);

    virtual pos_type 
    seekpos (pos_type sp, ios_base::openmode which =
             ios_base::in | ios_base::out);

    virtual basic_streambuf<charT, traits>*
    setbuf (char_type* s, streamsize n);

    virtual int 
    sync ();

    virtual int_type
    uflow ();

    virtual void
    imbue (const locale& loc);

    virtual streamsize 
    showmanyc ();

    virtual streamsize 
    xsgetn (char_type* s, streamsize n);

    virtual streamsize 
    xsputn (const char_type* s, streamsize n);

    //
    //

private :

    FILE*                pfile; 
    ios_base::openmode  mode_;

    // declare a mutex object.
    DEC_OBJ_LOCK(_mutex)

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_ifstream : public basic_istream<charT, traits> {
public :

    typedef  charT               char_type;
    typedef  traits              traits_type;
 
    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

    typedef  basic_filebuf<charT, traits>   filebuf_type;

public :

    basic_ifstream ();

    explicit
    basic_ifstream (const char* s,
                    ios_base::openmode mode = ios_base::in);

    virtual ~basic_ifstream ();

    filebuf_type* 
    rdbuf () const;

    inline
    bool 
    is_open ();

    inline
    void 
    open (const char* s, ios_base::openmode mode = ios_base::in);

    inline
    void 
    close ();

private :

    filebuf_type     fbuf;

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_ofstream : public basic_ostream<charT, traits> {
public :

    typedef  charT               char_type;
    typedef  traits              traits_type;
 
    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

    typedef  basic_filebuf<charT, traits>   filebuf_type;

public :

    basic_ofstream ();

    explicit
    basic_ofstream (const char* s,
                    ios_base::openmode mode = ios_base::out |
                                              ios_base::trunc
                   );

    virtual ~basic_ofstream ();

    filebuf_type*
    rdbuf () const;

    inline
    bool 
    is_open ();

    inline
    void 
    open (const char* s, ios_base::openmode mode = 
          ios_base::out | ios_base::trunc);

    inline
    void 
    close ();


private :

    filebuf_type     fbuf;

};

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::basic_filebuf ()
: basic_streambuf<charT, traits> (), pfile (0)
{
    set_facet();
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::basic_filebuf (FILE* pfile_arg)
: basic_streambuf<charT, traits> (), pfile (pfile_arg)
{
    set_facet();
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::~basic_filebuf ()
{
   close ();
   REMOVE(_mutex);
}

template <class charT, class traits>
inline
bool
basic_filebuf<charT, traits>::is_open () const
{
   READ_LOCK(_mutex);
   return (pfile != 0);
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::filebuf_type*
basic_filebuf<charT, traits>::open (const char* s, 
                              ios_base::openmode mode)
{
   mode_ = mode;

#ifdef MSIPL_EDG232
   const ios_base::openmode  valid_modes[] = {
#else
   static const ios_base::openmode  valid_modes[] = {
#endif
   ios_base::in, 
   ios_base::in  | ios_base::out,
   ios_base::in  | ios_base::binary,
   ios_base::out | ios_base::trunc,
   ios_base::out | ios_base::app, 
   ios_base::out | ios_base::trunc | ios_base::binary,
   ios_base::out | ios_base::app   | ios_base::binary, 
   ios_base::in  | ios_base::out   | ios_base::trunc,
   ios_base::in  | ios_base::out   | ios_base::app,
   ios_base::in  | ios_base::out   | ios_base::binary,
   ios_base::in  | ios_base::out   | ios_base::trunc   | ios_base::binary,
   ios_base::in  | ios_base::out   | ios_base::app     | ios_base::binary,
   0 };

#ifdef MSIPL_EDG232
   const char* char_modes[] = {
#else
   static const char* char_modes[] = {
#endif
   "r", "r+", "rb", "w", "a", "wb", "ab", "w+", "a+", 
   "r+b", "w+b", "a+b", 0 };

   ios_base::openmode    mode_save = mode;
   WRITE_LOCK(_mutex);
   if (!is_open ()) 
   {
      int index;
      init ();
      mode &= ~ios_base::ate;
      index = 0;
      while ((valid_modes[index] != 0) && (valid_modes[index] != mode)) 
          ++index;

      if (char_modes[index] && 
         ((pfile = fopen (s, char_modes[index])) != 0))  
      {
          if  (((mode_save & ios_base::ate) != 0) && 
             (fseek (pfile, 0, SEEK_END) != 0))
          {
             close ();
          }
          else
          {
             return this;
          }
      }
   }
   return 0;              
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::filebuf_type*
basic_filebuf<charT, traits>::close ()
{
   if ((pfile == stdin) || (pfile == stdout) || (pfile == stderr))
      return this;
   WRITE_LOCK(_mutex);
   if (is_open () && (fclose (pfile) == 0))
   {
      pfile = 0;
      return this;
   }
   return 0;
}

template <class charT, class traits>
inline
int
basic_filebuf<charT, traits>::sync ()
{
    return (is_open () ? fflush (pfile) : 0);
}

template <class charT, class traits>
inline
basic_streambuf<charT, traits>*
basic_filebuf<charT, traits>::setbuf (char_type* s, streamsize n)
{
    //
    // Fully buffered input/output.
    // Can't call setvbuf for wchar_t if we don't have 
    // our own buffer.
    //
    if (!is_open () || setvbuf (pfile, s, _IOFBF, n))
        return 0;
    return this;
}

template <class charT, class traits>
inline void 
basic_filebuf<charT, traits>::set_facet()
{
    ftype = &(use_facet (getloc (), (ofacet_type*)0));
    no_conversion_required = ftype->always_noconv();
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::int_type
basic_filebuf<charT, traits>::overflow (int_type c)
{
    state_type     fst;
    const char_type*          end;
    char           buf [__msipl_temp_bufsize];
    char*          ebuf;

    char_type      ch = traits_type::to_char_type (c);

    if (!is_open ())
        return traits_type::eof ();
    if (traits_type::eq_int_type (c, traits::eof ()))
        return traits_type::not_eof (c);
    int_type  value = c;
    if(no_conversion_required)
    {
        if (fputc (c, pfile) == EOF)
            value = traits_type::eof ();
        return value;
    }
    result conv = ftype->convert (fst, &ch, &ch + 1, end, buf,
                          buf+__msipl_temp_bufsize, ebuf);

    if ((conv == codecvt_base::partial) ||
        (conv == codecvt_base::error))
    {
        value = traits_type::eof ();
    }
    else if (conv == codecvt_base::noconv)
    {
         if (fputc (c, pfile) == EOF)
             value = traits_type::eof ();
    }
    else
    {
        // conv == codecvt_base::ok
        ebuf = 0;
        if (fputs (buf, pfile) == EOF)
            value = traits_type::eof ();
    }
    return value;
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::int_type
basic_filebuf<charT, traits>::underflow ()
{
    int_type value = traits_type::eof ();
    //
    // Assumption that at least one-character can be putback
    // and this operation would never fail
    //
    if (is_open () && (value = ungetc (fgetc (pfile),pfile)) == EOF )
        value = traits_type::eof ();
    return value;
}


template <class charT, class traits>
inline
streamsize
basic_filebuf<charT, traits>::xsputn (const char_type* s, streamsize n)
{
    state_type     fst;
    const char_type*          end;
    char           buf [__msipl_temp_bufsize];
    char*          ebuf;
 
    streamsize value = 0;
    if (!is_open ())
        return value;
 
    if(no_conversion_required)
        return  fwrite (s, sizeof(char), n, pfile);

    result conv = ftype->convert (fst, s, s + n, end, buf,
                          buf+__msipl_temp_bufsize, ebuf);
 
    if ((conv == codecvt_base::partial) ||
        (conv == codecvt_base::error))
        value = 0;
    else if (conv == codecvt_base::noconv)
        value = fwrite (s, sizeof(char), n, pfile);
    else
    {
        // conv == codecvt_base::ok
        ebuf = 0;
        int ret_val = 0;
        if ((ret_val = fputs (buf, pfile)) == EOF)
            value = 0;
        else
            value = ret_val/sizeof(char_type);
    }
    return value;
}


template <class charT, class traits>
inline
basic_filebuf<charT, traits>::int_type
basic_filebuf<charT, traits>::pbackfail (int_type c)
{
    int_type value = traits_type::eof ();

    if (is_open ())
    {
        long p_sav = ftell (pfile);
        int_type ch;
        if (!fseek (pfile, -1, SEEK_CUR))
        {
            ch = sgetc ();
            if (pubseekpos (pos_type(p_sav)) == pos_type(-1))
                return value;
        }
        else
            return value;

        if (traits_type::eq_int_type (ch, c) ||
            (mode_ & ios_base::out) != 0)
        {
            value = ungetc (c, pfile);
            if (value == EOF)
                value = traits_type::eof ();
        }
        if (traits_type::eq_int_type (c, traits::eof ()))
        {
            value = fseek (pfile, -1, SEEK_CUR);
            if (value)
                value = traits_type::eof ();
        }
    }
            
    return value;
}

template <class charT, class traits>                                            //MW-mm 961227
basic_filebuf<charT, traits>::int_type                                          //MW-mm 961227
basic_filebuf<charT, traits>::__pbfile (int_type c)                             //MW-mm 961227
{                                                                               //MW-mm 961227
    int_type value = traits_type::eof ();                                       //MW-mm 961227
                                                                                //MW-mm 961227
    if (is_open ())                                                             //MW-mm 961227
    {                                                                           //MW-mm 961227
        long p_sav = ftell (pfile);                                             //MW-mm 970107
        if (p_sav == -1L)                                                       //MW-mm 970128
	    {                                                                       //MW-mm 970128
	       value = ungetc(c, pfile);                                            //MW-mm 970128
	       if (value)                                                           //MW-mm 970128
	          value = traits_type::eof ();                                      //MW-mm 970128
	    }                                                                       //MW-mm 970128
	    else                                                                    //MW-mm 970128
	    {                                                                       //MW-mm 970128
	        int_type ch;                                                        //MW-mm 970107
	        if (!fseek (pfile, -1, SEEK_CUR))                                   //MW-mm 970107
	        {                                                                   //MW-mm 970107
	            ch = sgetc ();                                                  //MW-mm 970107
	            if (pubseekpos (pos_type(p_sav)) == pos_type(-1))               //MW-mm 970107
	                return value;                                               //MW-mm 970107
	        }                                                                   //MW-mm 970107
	        else                                                                //MW-mm 970107
	            return value;                                                   //MW-mm 970107
	                                                                            //MW-mm 970107
	        if (traits_type::eq_int_type (ch, c) ||                             //MW-mm 970107
	            (mode_ & ios_base::out) != 0)                                   //MW-mm 970107
	        {                                                                   //MW-mm 970107
	            value = ungetc (c, pfile);                                      //MW-mm 970107
	            if (value == EOF)                                               //MW-mm 970107
	                value = traits_type::eof ();                                //MW-mm 970107
	        }                                                                   //MW-mm 970107
	        if (traits_type::eq_int_type (c, traits::eof ()))                   //MW-mm 970107
	        {                                                                   //MW-mm 970107
	            value = fseek (pfile, -1, SEEK_CUR);                            //MW-mm 970107
	            if (value)                                                      //MW-mm 970107
	                value = traits_type::eof ();                                //MW-mm 970107
	        }                                                                   //MW-mm 970107
	    }                                                                       //MW-mm 970107
	}                                                                           //MW-mm 961227
                                                                                //MW-mm 961227            
    return value;                                                               //MW-mm 961227
}                                                                               //MW-mm 961227


template <class charT, class traits>
inline
basic_filebuf<charT, traits>::int_type
basic_filebuf<charT, traits>::uflow ()
{
    int_type value = traits_type::eof ();

    if ( is_open () &&  ((value = fgetc (pfile)) == EOF ))
        value = traits_type::eof ();

    return value;
}

template <class charT, class traits>
inline
streamsize 
basic_filebuf<charT, traits>::xsgetn (char_type* s, streamsize n)
{
    streamsize value = 0;

    if (is_open ())
    {
       value = fread (s, sizeof(char), n, pfile); 
    }
    return value;
}

template <class charT, class traits>
inline
void
basic_filebuf<charT, traits>::imbue (const locale& loc_arg)
{
    loc = loc_arg;
}

template <class charT, class traits>
inline
streamsize
basic_filebuf<charT, traits>::showmanyc ()
{
    long int curpos = ftell (pfile);
    if (curpos == -1)
        return 0;
    //
    // Seek to the end of file.
    //
    fseek (pfile,0,SEEK_END);
    long int endpos = ftell (pfile);
    if (endpos == -1)
        return 0;

    fseek (pfile, curpos, SEEK_SET);
    return (streamsize(endpos - curpos));
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::pos_type
basic_filebuf<charT, traits>::seekoff (off_type  off,
                                       ios_base::seekdir way,
                                       ios_base::openmode /* which */)
{
    if (!is_open () || (off == -1) || 
       ((way & ios_base::beg) && (off < 0)) ||
       ((way & ios_base::end) && (off > 0)))
         return pos_type (-1);
    int  poseek  = SEEK_CUR;
    switch (way)
    {
        case ios_base::beg :
            poseek = SEEK_SET;
            break;
        case ios_base::end :
            poseek = SEEK_END;
            break;
    }
    if (fseek (pfile, off, poseek))
        return pos_type (-1);
    return pos_type (ftell (pfile));
}

template <class charT, class traits>
inline
basic_filebuf<charT, traits>::pos_type
basic_filebuf<charT, traits>::seekpos (pos_type sp,
                                       ios_base::openmode /* which */)
{
    if ( !is_open () ||  sp == pos_type (-1))
        return pos_type (-1);
    if (fseek (pfile, sp.offset (),SEEK_SET))
        return pos_type (-1);
    return pos_type (ftell (pfile));
}

template <class charT, class traits>
inline
basic_ifstream<charT, traits>::basic_ifstream ()
: basic_istream<charT, traits> (0) 
{ 
    init (&fbuf);
}

template <class charT, class traits>
inline
basic_ifstream<charT, traits>::basic_ifstream (const char* s, 
                               ios_base::openmode mode) 
: basic_istream<charT, traits> (0) 
{
    init (&fbuf);
    rdbuf ()->open (s, mode);
}

template <class charT, class traits>
inline
basic_ifstream<charT, traits>::~basic_ifstream () { }

template <class charT, class traits>
inline
basic_ifstream<charT, traits>::filebuf_type*
basic_ifstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<filebuf_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<filebuf_type*> (&fbuf);
    return (filebuf_type*) (&fbuf);
}

template <class charT, class traits>
inline
bool
basic_ifstream<charT, traits>::is_open ()
{
    return rdbuf ()->is_open ();
}

template <class charT, class traits>
inline
void
basic_ifstream<charT, traits>::open (const char* s,
                                     ios_base::openmode mode)
{
    rdbuf ()->open (s, mode);
    if (!is_open ())
    {
        setstate (failbit);
    }
}

template <class charT, class traits>
inline
void
basic_ifstream<charT, traits>::close ()
{
    if (rdbuf ()->close () == 0)
    {
        setstate (failbit);
    }
}

template <class charT, class traits>
inline
basic_ofstream<charT, traits>::basic_ofstream ()
: basic_ostream<charT, traits> (0)
{
    init (&fbuf);
}

template <class charT, class traits>
inline
basic_ofstream<charT, traits>::basic_ofstream (const char* s, 
                               ios_base::openmode mode)
: basic_ostream<charT, traits> (0)
{
    init (&fbuf);
    rdbuf ()->open (s, mode);
}

template <class charT, class traits>
inline
basic_ofstream<charT, traits>::~basic_ofstream () { }

template <class charT, class traits>
inline
basic_ofstream<charT, traits>::filebuf_type*
basic_ofstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<filebuf_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<filebuf_type*> (&fbuf);
    return (filebuf_type*) (&fbuf);
}

template <class charT, class traits>
inline
bool
basic_ofstream<charT, traits>::is_open ()
{
    return rdbuf ()->is_open ();
}

template <class charT, class traits>
inline
void
basic_ofstream<charT, traits>::open (const char* s,
                                     ios_base::openmode mode)
{
    rdbuf ()->open (s, mode);
    if (!is_open ())
    {
        setstate (failbit);
    }
}

template <class charT, class traits>
inline
void
basic_ofstream<charT, traits>::close ()
{
    if (rdbuf ()->close () == 0)
    {
        setstate (failbit);
    }
}

//
// class basic_fstream
//

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class basic_fstream : public basic_iostream<charT, traits> {
public :

    typedef  charT               char_type;
    typedef  traits              traits_type;
 
    typedef typename  traits::pos_type    pos_type;
    typedef typename  traits::off_type    off_type;
    typedef typename  traits::int_type    int_type;

    typedef  basic_filebuf<charT, traits>   filebuf_type;

public :

    basic_fstream ();

    explicit
    basic_fstream (const char* s,
                   ios_base::openmode mode = ios_base::in | ios_base::out);

    virtual ~basic_fstream ();

    filebuf_type* 
    rdbuf () const;

    inline
    bool 
    is_open ();

    inline
    void 
    open (const char* s,
          ios_base::openmode mode = ios_base::in | ios_base::out);

    inline
    void 
    close ();

private :

    filebuf_type     fbuf;

};

template <class charT, class traits>
inline
basic_fstream<charT, traits>::basic_fstream ()
: basic_iostream<charT, traits> (0) 
{ 
    init (&fbuf);
}

template <class charT, class traits>
inline
basic_fstream<charT, traits>::basic_fstream (const char* s, 
                               ios_base::openmode mode) 
: basic_iostream<charT, traits> (0) 
{
    init (&fbuf);
    rdbuf ()->open (s, mode);
}

template <class charT, class traits>
inline
basic_fstream<charT, traits>::~basic_fstream () { }

template <class charT, class traits>
inline
basic_fstream<charT, traits>::filebuf_type*
basic_fstream<charT, traits>::rdbuf () const
{
    // use dynamic cast
    // return dynamic_cast<filebuf_type*> (basic_ios<charT, traits>::rdbuf ());
    // return const_cast<filebuf_type*> (&fbuf);
    return (filebuf_type*) (&fbuf);
}

template <class charT, class traits>
inline
bool
basic_fstream<charT, traits>::is_open ()
{
    return rdbuf ()->is_open ();
}

template <class charT, class traits>
inline
void
basic_fstream<charT, traits>::open (const char* s,
                                    ios_base::openmode mode)
{
    rdbuf ()->open (s, mode);
    if (!is_open ())
    {
        setstate (failbit);
    }
}

template <class charT, class traits>
inline
void
basic_fstream<charT, traits>::close ()
{
    if (rdbuf ()->close () == 0)
    {
        setstate (failbit);
    }
}

typedef basic_filebuf <char, char_traits<char> >    filebuf;
typedef basic_ifstream<char, char_traits<char> >   ifstream;
typedef basic_ofstream<char, char_traits<char> >   ofstream;
typedef basic_fstream <char, char_traits<char> >    fstream;

#ifdef MSIPL_WCHART
typedef basic_filebuf <wchar_t, char_traits<wchar_t> >   wfilebuf;
typedef basic_ifstream<wchar_t, char_traits<wchar_t> >   wifstream;
typedef basic_ofstream<wchar_t, char_traits<wchar_t> >   wofstream;
typedef basic_fstream <wchar_t, char_traits<wchar_t> >   wfstream;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_FSTREAM_H */

/*   Change record
//961210 bkoz added alignment wrapper
//MW-mm 961227 Changes to allow for dealing with bufferless files part of fix in streambuf.h
//MW-mm 970107 Corrections from MSIPL to __pbfile
//MW-mm 970128 More corrections to __pbfile
*/
