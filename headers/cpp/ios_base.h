/*  Metrowerks Standard Library  Version 2.2b1  1997 September 10  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/
//971002 bds incorporated Be changes
//970417 ios_base declarations/definitions

#ifndef __ios_base_h__
#define __ios_base_h__

#include <size_t.h>
#include <vector.h>


#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

//foward declarations, typedefs
typedef  size_t  streamsize;		//from bstring.h
class locale;


//
//	class ios_base
//
class ios_base {
public:

     //
     // Nested class for exception handling in failure conditions
     //
#ifdef   MSIPL_EXCEPT
#ifndef  __EDG_EXCEPT_CLASSES
     class failure : public exception {
     public:
         failure (const string& what_arg)
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

         ~Init ();

     private:
 
#if __dest_os != __be_os
#ifdef MSIPL_MULTITHREAD
         static mutex_arith<int, mutex>        init_cnt;
#else
         static int                            init_cnt;
#endif
#endif		 

     };

     inline
     iostate
     exceptions () const;

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
    
     void
     clear (iostate state_arg = goodbit);

     void
     setstate (iostate state_arg);

     inline
     operator bool () const;

     inline bool 
     operator! () const;

     inline static 
     int
     xalloc ();

     long&
     iword (int index_arg);

     void*&
     pword (int index_arg);

     ~ios_base ();					//970420 bkoz 
  
    locale	imbue (const locale& loc_arg);

    locale	getloc () const;

     void	register_callback (event_callback fn, int index);

protected:

     ios_base ();				//970420 bkoz

     inline
     void 
     base_init () {
	    fmtfl     =  skipws | dec;
	    wide      =  0;
	    prec      =  6;
	    state     =  badbit;
	}


     static 
     inline
     void
     throwfailure ();

     void
     copyfmt (const ios_base&  rhs);

     inline
     void
     assign_state (iostate iostate_arg);

     void
     call_regpair (ios_base&, event e);

     //
     // Protected data member.
     //
     locale*                       			loc;
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
     ios_base (const ios_base& base) ;
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

ios_base::iostate
ios_base::exceptions () const
{
    return (except);
}

ios_base::fmtflags
ios_base::flags () const
{
    return (fmtfl);
}

ios_base::fmtflags
ios_base::flags (fmtflags fmtfl_arg)
{
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl = fmtfl_arg;
    return (fmtfl_sav);
}

ios_base::fmtflags
ios_base::setf (fmtflags fmtfl_arg)
{
    WRITE_LOCK(_mutex);
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl |= fmtfl_arg;
    return (fmtfl_sav);
}
 
ios_base::fmtflags
ios_base::setf (fmtflags fmtfl_arg, fmtflags mask)
{
    WRITE_LOCK(_mutex);
    fmtflags  fmtfl_sav = fmtfl;
    fmtfl &= (~mask);
    fmtfl |= (fmtfl_arg & mask);
    return (fmtfl_sav);
}

void
ios_base::unsetf (fmtflags mask)
{
    WRITE_LOCK(_mutex);
    fmtfl &= (~mask);
}

streamsize
ios_base::precision () const
{
    return (prec);
}

streamsize
ios_base::precision (streamsize prec_arg) 
{
    streamsize prec_sav = prec;
    prec = prec_arg;
    return (prec_sav);
}

streamsize
ios_base::width () const
{
    return (wide);
}
 
streamsize
ios_base::width (streamsize wide_arg)
{
    streamsize wide_sav = wide;
    wide = wide_arg;
    return (wide_sav);
}

int
ios_base::xalloc ()
{
    return (index++);
}


ios_base::operator bool () const
{
    READ_LOCK(_mutex);
    return ((state & (failbit | badbit)) == 0);
}

bool
ios_base::operator! () const
{
    return fail ();
}

ios_base::iostate
ios_base::rdstate () const
{
    return (state);
}

bool
ios_base::good () const
{
    READ_LOCK(_mutex);
    return (state == 0);
}

bool
ios_base::eof () const
{
    READ_LOCK(_mutex);
    return ((state & eofbit) != 0);
}

bool
ios_base::fail () const
{
    READ_LOCK(_mutex);
    return ((state & (failbit | badbit)) != 0);
}

bool
ios_base::bad () const
{
    READ_LOCK(_mutex);
    return ((state & badbit) != 0);
}

void
ios_base::assign_state (iostate iostate_arg)
{
    state = iostate_arg;
}


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


#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif  //__ios_base_h__

/* Change record
 * mm 971110 Modified changes from Be
 * Be-mani 980107 We don't like static members of global objects!
*/
