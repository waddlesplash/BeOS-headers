/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_IOS_H

#include <mcompile.h>

#include MOD_INCLUDE(mutex)

#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(locale)
#else
#include MOD_INCLUDE(mlocale)
#endif

#ifndef IOS_SEEN

#include MOD_INCLUDE(vector)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

class locale;

template <class charT, class traits> class basic_streambuf;
template <class charT, class traits> class basic_ostream;

class ios_base {

public:

     //
     // Nested class for exception handling in failure conditions
     //
#ifdef   MSIPL_EXCEPT
#ifndef  __EDG_EXCEPT_CLASSES
     class failure : public exception {
     public:
         failure (const string& what_arg = "Failure reported")
         : exception (what_arg) { }
         virtual ~failure () MSIPL_THROW { }
         //
         // virtual string what () const;
         //
     };
#else
     class failure : public msipl_exception {
     public:
         failure (const char* what_arg) 
         : msipl_exception (what_arg) { }
         virtual ~failure () MSIPL_THROW { }
         //
         // virtual const char* what () const;
         //
     };
#endif
#endif

     enum fmt_flags {
          null         =  0,
          boolalpha    =  1<<0,
          dec          =  1<<1,
          fixed        =  1<<2,
          hex          =  1<<3,
          internal     =  1<<4,
          left         =  1<<5,
          oct          =  1<<6,
          right        =  1<<7,
          scientific   =  1<<8,
          showbase     =  1<<9,
          showpoint    =  1<<10,
          showpos      =  1<<11,
          skipws       =  1<<12,
          unitbuf      =  1<<13,
          uppercase    =  1<<14,
          adjustfield  =  left  | right | internal,
          basefield    =  dec   | hex   | oct,
          floatfield   =  fixed | scientific
     };

     enum io_state {
          badbit   = 1<<0,
          eofbit   = 1<<1,
          failbit  = 1<<2,
          goodbit  = 0
     };

     enum open_mode {
          app       = 1<<0,
          ate       = 1<<1,
          binary    = 1<<2,
          in        = 1<<3,
          out       = 1<<4,
          trunc     = 1<<5
     };

     enum seekdir {
          beg      = 1<<0,
          cur      = 1<<1,
          end      = 1<<2
     };

     enum event { 
          erase_event,
          imbue_event, 
          copyfmt_event 
     };

     typedef long  int fmtflags;     
     typedef short int openmode;
     typedef short int iostate;

     typedef  void (*event_callback) (event, ios_base&, int index);

     class Init {
     
     public:

         Init ();

#ifdef wrong // Be-mani 960829 begin

         ~Init ();

     private:
 
#ifdef MSIPL_MULTITHREAD
         static mutex_arith<int, mutex>        init_cnt;
#else
         static int                            init_cnt;
#endif

#endif /* wrong */ // Be-mani 960829 end

     };

     inline
     iostate
     exceptions () const;

     inline
     void
     exceptions (iostate except_arg);

     inline
     fmtflags
     flags () const;

     inline
     fmtflags
     flags (fmtflags fmtfl_arg);

     inline
     fmtflags
     setf (fmtflags fmtfl_arg);

     inline
     fmtflags
     setf (fmtflags fmtfl_arg, fmtflags mask);

     inline
     void
     unsetf (fmtflags mask);

     inline
     streamsize
     precision () const;

     inline
     streamsize
     precision (streamsize prec_arg);

     inline
     streamsize
     width () const;

     inline
     streamsize
     width (streamsize wide_arg);

     inline
     bool
     good () const;

     inline
     bool
     eof () const;

     inline
     bool
     fail () const;

     inline
     bool
     bad () const;

     inline
     iostate
     rdstate () const;
    
     inline
     void
     clear (iostate state_arg = goodbit);

     inline
     void
     setstate (iostate state_arg);

     inline
     operator bool () const;

     inline bool 
     operator! () const;

     inline static 
     int
     xalloc ();

     inline
     long&
     iword (int index_arg);

     inline
     void*&
     pword (int index_arg);

     ~ios_base () 
     { 
         // Should it be call_regpair (erase_event); ???????
         call_regpair (*this, imbue_event); 
         REMOVE(_mutex);
      }

     locale 
     imbue (const locale& loc_arg);

     locale 
     getloc () const;

     void
     register_callback (event_callback fn, int index);

protected:

     inline
     ios_base ();

     inline
     void 
     base_init ();

     static 
     inline
     void
     throwfailure ();

     inline
     void
     copyfmt (const ios_base&  rhs);

     inline
     void
     assign_state (iostate iostate_arg);

     inline
     void
     call_regpair (ios_base&, event e);

     //
     // Protected data member.
     //
     locale                                  loc;
     iostate                                 except;

#if __MOTO__
public:
#endif
     typedef   pair<event_callback, int>                    event_pair;
#if __MOTO__
protected:
#endif
     typedef   vector<event_pair, allocator<event_pair> >   ev_vector_type;
     typedef   vector<long, allocator<long> >               l_vector_type;
     typedef   vector<void*, allocator<void*> >             v_vector_type;

     ev_vector_type                              rvec;
     size_t                                      rvec_size;

private:

//
//   Data members
//
     
     streamsize                              prec;
     streamsize                              wide;
     iostate                                 state;
     fmtflags                                fmtfl;

     vector<long, allocator<long> >          ivec;
     vector<void*, allocator<void*> >        pvec;

#ifdef MSIPL_MULTITHREAD
     static  mutex_arith<int, mutex>         index;
#else
     static  int                             index;
#endif

     DEC_OBJ_LOCK(_mutex)
 
     // not to be defined
     ios_base (const ios_base& base);
     ios_base& operator= (const ios_base& base);

};

//961211 bkoz via andreas, for new FE inining, specializing for pointer type iterators
#ifndef MSIPL_PARTIAL_TEMPL
null_template
struct iterator_trait <const ios_base::event_pair*> {
    typedef ptrdiff_t                    	distance_type;
    typedef const ios_base::event_pair		value_type;
    typedef random_access_iterator_tag   	iterator_category;
};
#endif

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

     inline
     void
     clear (iostate state = ios_base::goodbit);

     inline
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
     basic_ios (const basic_ios<char_type, traits>& rhs);  

     // not to be defined
     basic_ios&
     operator= (const basic_ios<char_type, traits>& rhs);  

//
//   Data members
//
     basic_streambuf<char_type, traits>*    sb;
     basic_ostream<char_type, traits>*      tiestr;
     char_type                              fillch;

     DEC_OBJ_LOCK(_mutex)
};

//
// Format flag -- fmtflags -- Manipulators
//
inline
ios_base&
boolalpha (ios_base&  str)
{
    str.setf (ios_base::boolalpha);
    return (str);
}

inline
ios_base&  
noboolalpha (ios_base&  str)
{
    str.unsetf (ios_base::boolalpha);
    return (str);
}

inline
ios_base&  
showbase (ios_base&  str)
{
    str.setf (ios_base::showbase);
    return (str);
}

inline
ios_base&  
noshowbase (ios_base&  str)
{
    str.unsetf (ios_base::showbase);
    return (str);
}

//
// Show point / position -- Manipulators
//
inline
ios_base&  
showpoint (ios_base&  str)
{
    str.setf (ios_base::showpoint);
    return (str);
}

inline
ios_base&  
noshowpoint (ios_base&  str)
{
    str.unsetf (ios_base::showpoint);
    return (str);
}

inline
ios_base&  
showpos (ios_base&  str)
{
    str.setf (ios_base::showpos);
    return (str);
}

inline
ios_base&  
noshowpos (ios_base&  str)
{
    str.unsetf (ios_base::showpos);
    return (str);
}

inline 
ios_base&
unitbuf (ios_base& str)
{
    str.setf (ios_base::unitbuf);
    return (str);
}

inline 
ios_base&
nounitbuf (ios_base& str)
{
    str.unsetf (ios_base::unitbuf);
    return (str);
}

inline
ios_base&  
skipws (ios_base&  str)
{
    str.setf (ios_base::skipws);
    return (str);
}

inline
ios_base&  
noskipws (ios_base&  str)
{
    str.unsetf (ios_base::skipws);
    return (str);
}

inline
ios_base&  
uppercase (ios_base&  str)
{
    str.setf (ios_base::uppercase);
    return (str);
}

inline
ios_base&  
nouppercase (ios_base&  str)
{
    str.unsetf (ios_base::uppercase);
    return (str);
}

//
// Field adjust -- Manipulators
//
inline
ios_base&  
internal (ios_base&  str)
{
    str.setf (ios_base::internal, ios_base::adjustfield);
    return (str);
}

inline
ios_base&  
left (ios_base&  str)
{
    str.setf (ios_base::left, ios_base::adjustfield);
    return (str);
}

inline
ios_base&  
right (ios_base&  str)
{
    str.setf (ios_base::right, ios_base::adjustfield);
    return (str);
}

//
// Base Field -- Manipulators
//
inline
ios_base&  
dec (ios_base&  str)
{
    str.setf (ios_base::dec, ios_base::basefield);
    return (str);
}

inline
ios_base&  
hex (ios_base&  str)
{
    str.setf (ios_base::hex, ios_base::basefield);
    return (str);
}

inline
ios_base&  
oct (ios_base&  str)
{
    str.setf (ios_base::oct, ios_base::basefield);
    return (str);
}

//
// Float Field -- Manipulators
//
inline
ios_base&  
fixed (ios_base&  str)
{
    str.setf (ios_base::fixed, ios_base::floatfield);
    return (str);
}

inline
ios_base&  
scientific (ios_base&  str)
{
    str.setf (ios_base::scientific, ios_base::floatfield);
    return (str);
}

inline
ios_base::iostate
ios_base::exceptions () const
{
    return (except);
}

inline
void
ios_base::exceptions (iostate except_arg)
{
    except = except_arg;
    clear (rdstate ());
}

inline
ios_base::fmtflags
ios_base::flags () const
{
    return (fmtfl);
}

inline
ios_base::fmtflags
ios_base::flags (fmtflags fmtfl_arg)
{
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl = fmtfl_arg;
    return (fmtfl_sav);
}

inline
ios_base::fmtflags
ios_base::setf (fmtflags fmtfl_arg)
{
    WRITE_LOCK(_mutex);
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl |= fmtfl_arg;
    return (fmtfl_sav);
}
 
inline
ios_base::fmtflags
ios_base::setf (fmtflags fmtfl_arg, fmtflags mask)
{
    WRITE_LOCK(_mutex);
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl &= (~mask);
    fmtfl |= (fmtfl_arg & mask);
    return (fmtfl_sav);
}

inline
void
ios_base::unsetf (fmtflags mask)
{
    WRITE_LOCK(_mutex);
    fmtfl &= (~mask);
}

inline
streamsize
ios_base::precision () const
{
    return (prec);
}

inline
streamsize
ios_base::precision (streamsize prec_arg) 
{
    streamsize prec_sav = prec;
    prec = prec_arg;
    return (prec_sav);
}

inline
streamsize
ios_base::width () const
{
    return (wide);
}
 
inline
streamsize
ios_base::width (streamsize wide_arg)
{
    streamsize wide_sav = wide;
    wide = wide_arg;
    return (wide_sav);
}

inline
int
ios_base::xalloc ()
{
    return (index++);
}

inline
long&
ios_base::iword (int index_arg)
{
    if (index > (int)ivec.size ()) ivec.resize (index * 2);
    if (index_arg < ivec.size ())
       return ivec[index_arg];
    else
       return ivec.back ();
}
 
inline
void*&
ios_base::pword (int index_arg)
{
    if (index_arg > pvec.size ()) pvec.insert (pvec.end (), (void*)0);
    return pvec[index_arg];
}

inline
ios_base::operator bool () const
{
    READ_LOCK(_mutex);
    return ((state & (failbit | badbit)) == 0);
}

inline 
bool
ios_base::operator! () const
{
    return fail ();
}

inline 
ios_base::iostate
ios_base::rdstate () const
{
    return (state);
}

inline
void
ios_base::clear (iostate state_arg)
{
    assign_state (state_arg);
    if ((rdstate () & except) != 0)
    {
        throwfailure ();
    }
}

inline
void
ios_base::setstate (iostate state_arg)
{
    clear (rdstate () | state_arg);
}

inline
bool
ios_base::good () const
{
    READ_LOCK(_mutex);
    return (state == 0);
}

inline
bool
ios_base::eof () const
{
    READ_LOCK(_mutex);
    return ((state & eofbit) != 0);
}

inline
bool
ios_base::fail () const
{
    READ_LOCK(_mutex);
    return ((state & (failbit | badbit)) != 0);
}

inline
bool
ios_base::bad () const
{
    READ_LOCK(_mutex);
    return ((state & badbit) != 0);
}

inline
void
ios_base::assign_state (iostate iostate_arg)
{
    state = iostate_arg;
}

inline
void
ios_base::call_regpair (ios_base& is, event e)
{
    for (int i=rvec_size-1; i >= 0; i--)
    {
       (*(rvec[i].first)) (e, is, rvec[i].second);
    }
}

inline 
ios_base::ios_base ()
: ivec (l_vector_type  ((l_vector_type::size_type)10, (long)0)),
  pvec (v_vector_type  ((v_vector_type::size_type)10, (void*)0)),
  rvec (ev_vector_type ((ev_vector_type::size_type)10, event_pair ()))
{ 
    rvec_size = 0;
}

inline
void
ios_base::base_init ()
{
    fmtfl     =  skipws | dec;
    wide      =  0;
    prec      =  6;
    state     =  badbit;
}

inline
void
ios_base::copyfmt (const ios_base&  rhs)
{
    fmtfl     =  rhs.fmtfl;
    wide      =  rhs.wide;
    prec      =  rhs.prec;
    ivec      =  rhs.ivec;
    pvec      =  rhs.pvec;
}
 
inline
void
ios_base::throwfailure ()
{
#ifdef MSIPL_EXCEPT
    throw failure ("Failure reported");
#else
    fprintf (stderr, "Failure in I/O\n");
    exit (1);
#endif
}

inline
locale
ios_base::imbue (const locale& loc_arg)
{
   locale  loc_sav = loc;
   loc   = loc_arg;
   call_regpair (*this, imbue_event);
   return  loc_sav;
}

inline
locale
ios_base::getloc () const
{
   return loc;
}

inline
void
ios_base::register_callback (event_callback fn, int index)
{
   if ( rvec_size > rvec.size ()) rvec.resize (rvec.size () * 2);
   rvec[rvec_size++] = make_pair (fn, index);
}

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
inline
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
inline
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

template <class charT, class traits>
inline
basic_ios<charT, traits>::~basic_ios ()
{
    REMOVE(_mutex);
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
basic_ios<charT, traits>&
basic_ios<charT, traits>::copyfmt (const basic_ios<charT, traits>& rhs)
{
    if (this != &rhs)
    {
        call_regpair (*this, erase_event);
        loc     = rhs.getloc ();
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

#define IOS_SEEN

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* IOS_SEEN */

#define MSIPL_IOS_H

#endif /* MSIPL_IOS_H */

//961210 bkoz added wrapper for alignment
//961211 bkoz line 314 added andreas's iterator specializations for new FE
//961221 bkoz line 281 added moto change (mmoss)

/* Change log
Be-mani 960829	Fix serious bug in iostream.cpp. Corresponding changes here.
*/
