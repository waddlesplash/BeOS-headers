/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_LOCALE_H
#define MSIPL_LOCALE_H

#include <mcompile.h>
#include <typeinfo>	//961113 bkoz for bad_cast decl

//
// for messages facet
//
#ifdef MSIPL_NL_TYPES
#include MOD_INCLUDE(nl_types)
#endif

#include MOD_INCLUDE(vector)
#include MOD_INCLUDE(mtools)

#include MOD_C_INCLUDE(locale)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#undef toupper
#undef tolower

class locale {

public :

   //
   // types
   //
   class facet;
   class id;
   class imp;

   typedef int category;

   static  const    category   collate;
   static  const    category   ctype;
   static  const    category   none;
   static  const    category   monetary;
   static  const    category   numeric;
   static  const    category   time;
   static  const    category   messages;
   static  const    category   all;

   //
   // constructor/copy/destroy
   //
   locale () MSIPL_THROW
   {
       LOCK(mutex_bl, gl_mutex);
       if (global_)
           imp_ = global_;
       else
           imp_ = init ();

       imp_->add_ref ();
   }

   locale (const locale& other) MSIPL_THROW
   : imp_ (other.imp_)
   {
       imp_->add_ref ();
   }

   explicit
   locale (const char* std_name);

   locale (const locale& other, const char* std_name, category);

#ifdef MSIPL_MEMBER_TEMPLATE
   template <class Facet> 
   locale (const locale& loc, Facet* f);
   template <class Facet> 
   locale (const locale& other, const locale& one, Facet* f);
#else
   locale (const locale& other, locale::facet* f);
   locale (const locale& other, const locale& one, locale::facet* f);
#endif

   locale (const locale& one, const locale& other, category);

   ~locale () MSIPL_THROW  // non-virtual
   { 
       if (imp_->rem_ref ()) 
       { 
           if (imp_ == global_){ REMOVE(gl_mutex); global_ = 0; }
           delete imp_; 
       }
   }

   const locale&
   operator= (const locale& other) MSIPL_THROW ;

   //
   // locale operations
   //
   string
   name () const { return imp_->name_; }

   bool
   operator== (const locale& other) const
   {
       return ((imp_ == other.imp_) || (((name () != "*") == 0) &&
               ((name () == other.name ()) == 0)));
   }

   bool
   operator!= (const locale& other) const
   {
       return !(*this == other);
   }

#ifdef MSIPL_MEMBER_TEMPLATE
   template <class charT, class traits>
   inline bool
   operator() (const basic_string<charT, traits, allocator<charT> >& s1,
               const basic_string<charT, traits, allocator<charT> >& s2) const;
#else
   inline bool
   operator() (const string& s1, const string& s2) const;
#endif

   //
   // global locale objects : static members functions
   //
   static
   locale
   global (const locale&);   // replaces ::setlocale (...)

   static
   const locale&
   classic ();

public :

   imp*            imp_;  // the only data member
   static  imp*    global_;

   DEC_STATIC_MUTEX(gl_mutex) // static lock for global_;

   const locale::facet&
   delegate (const id& i) const;

private :

   locale (imp* imp_arg)
   : imp_(imp_arg) { imp_arg->add_ref (); }

   static
   void
   set_imp (imp*, imp*, const locale::id&);

   static
   void
   set_cat (imp*, imp*, locale::category);

   static
   imp*
   init ();

   void
   install (locale::facet*, id&, const string&);

public :

   class id {

     friend class locale;
      
   public :

     id () { }	
     //id (): id_(0) {}	 //961212 bkoz
     
     void init ()         
     { 
         LOCK(mut_block,_mutex);
         if (id_ == 0) { id_ = ++master_id_; }  
     }
   			
		operator size_t ()  const { LOCK(mut_block,_mutex); return (size_t)id_; }
     bool operator < (const id& ix) const 
     { 
         LOCK(mut_block,_mutex); 
         return (id_ < ix.id_); 
     }

     ~id () { REMOVE(_mutex); }

   private:

#ifdef MSIPL_MULTITHREAD
     static mutex_arith<size_t, mutex>   master_id_;

#else
     static size_t                       master_id_;

#endif

     size_t                              id_;

     DEC_MUTEX(_mutex)

     void operator= (const id&);           // not defined
     id (const id&);                       // not defined
     void operator& () { }                 // not usable
   }; 

   class facet {

     friend class locale;
     friend class locale::imp;

   private:
      
     facet (const facet&);                  // not defined
     void  operator= (const facet&);        // not defined
     // void  operator& () { }              // not usable
      
     virtual void add_ref () { if (response) ++refcount_; }
      
     bool rem_ref ()
     { return (response ? (--refcount_ == 0) :  false); }
      
#ifdef MSIPL_MULTITHREAD
     mutex_arith<size_t, mutex>     refcount_;
#else
     size_t                         refcount_;
#endif
      
   protected:
       explicit
 			facet (size_t refs = 0) 
     { response = !refs; if (response) refcount_ = 1;}
     
     virtual ~facet () { }

     virtual locale::id& get_id ()  { return id_priv; }
     
     bool operator== (const facet& f) const
     { return (this == &f) ? true : false; }

#ifdef MSIPL_APOGEE_ADDNL_FUNCTIONS
   public:
       virtual void __dummy ();
#endif
   private :
    
     bool response;
     locale::id id_priv;

   }; // end class locale::facet

    class imp : public locale::facet {
      
     friend class locale;

   public:

#ifdef MSIPL_APOGEE_ADDNL_FUNCTIONS
       virtual void __dummy ();
#endif

     typedef locale::facet                               base_type;
     typedef vector<base_type*, allocator<base_type*> >  vector_type;

     vector_type vec_;
      
     size_t      size_;

   private:
      
     string            name_;
      
     imp (const imp& other)
     : locale::facet (0), name_(other.name_),
       size_ (other.size_), vec_ (other.vec_)
     {
        for (int i = 1; i <= size_; i++)
           vec_[i]->add_ref ();
     }

     void add_ref ()
     {
        for (int i = 1; i <= size_; i++)
           vec_[i]->add_ref ();
        base_type::add_ref ();
     }

     bool rem_ref ()
     {
        for (int i = 1; i <= size_; i++)
           if (vec_[i]->rem_ref ()) delete vec_[i];
        return base_type::rem_ref ();
     }

     ~imp () { }

     imp (const char* std_name, locale::category cat = locale::all);

     imp (size_t size = 20)
     : locale::facet (0), name_ ("*", 1), size_(size)
     { if (size) vec_.resize (size, (locale::facet*)0); }
      
   };  /* end class locale::imp */

};  /* end class locale */

#ifdef MSIPL_MEMBER_TEMPLATE

template <class Facet>
inline
locale::locale (const locale& other, Facet* f)
: imp_(new locale::imp (*other.imp_))
{
    if (f != 0)
       install (f, Facet::id_, "*");
    else
    {
#ifdef MSIPL_EXCEPT
       throw runtime_error ("Null arg for locale::facet*");
#else
       fprintf (stderr, "Null arg for locale::facet*\n");
       exit (1);
#endif
    }
}

template <class Facet>
inline
locale::locale (const locale& other, const locale& one, Facet* f)
: imp_(new locale::imp (*other.imp_))
{
    if (f != 0)
        set_imp (imp_, one.imp_, Facet::id_);
    else
    {
#ifdef MSIPL_EXCEPT
       throw runtime_error ("Null arg for locale::facet*");
#else
       fprintf (stderr, "Null arg for locale::facet*\n");
       exit (1);
#endif
    }
    imp_->name_ = string("*");
}

#endif //MSIPL_MEMBER_TEMPLATE

template <class Facet>
inline
const Facet&
use_facet (const locale& loc, Facet* f)
{
   locale::facet* fp = f;       
   // check for derivation

   if (!fp) fp = NULL; // to ward off warnings

   if (!has_facet (loc, f))
   {
#ifdef MSIPL_EXCEPT
       throw bad_cast ("Facet not present in use_facet");	//951113 bkoz
#else
       fprintf (stderr, "Facet not present\n");
       exit (1);
#endif
   }
   if ((size_t) Facet::id_ < loc.imp_->vec_.size ())
       return (const Facet&)(*(loc.imp_->vec_[Facet::id_]));
   else
       return (const Facet&)loc.delegate (Facet::id_);
}

//
//  has_facet<facet>() simply reports whether a locale
//  implements a particular facet.  If has_facet<facet>()
//  is false, loc.use_facet<facet>() would throw an exception
//
template <class Facet>
inline
bool
has_facet (const locale& loc, Facet* f) MSIPL_THROW
{
   locale::facet* fp = f;       
   // check for derivation
   if (!fp) fp = NULL;
   return (Facet::id_ < loc.imp_->vec_.size ()) ? true : false;
}
 
//
// Note that the following functions are renamed from isF to is_F.
// for possible clash with C functions of same name.
//
template <class charT>
inline
bool
is_space (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::space, c);
}

template <class charT>
inline
bool
is_print (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::print, c);
}

template <class charT>
inline
bool
is_cntrl (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::cntrl, c);
}

template <class charT>
inline
bool
is_upper (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::upper, c);
}

template <class charT>
inline
bool
is_lower (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::lower, c);
}

template <class charT>
inline
bool
is_alpha (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::alpha, c);
}

template <class charT>
inline
bool
is_digit (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::digit, c);
}

template <class charT>
inline
bool
is_punct (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::punct, c);
}

template <class charT>
inline
bool
is_xdigit (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::xdigit, c);
}

template <class charT>
inline
bool
is_alnum (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::alnum, c);
}

template <class charT>
inline
bool
is_graph (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).is (ctype<charT>::graph, c);
}

template <class charT>
inline
bool
toupper_ (charT c, const locale& l)
{
   return use_facet (l,(ctype<charT>*)0).toupper (c);
}

template <class charT>
inline
bool
tolower_ (charT c, const locale& l)
{
   return use_facet (l, (ctype<charT>*)0).tolower (c);
}

//
// **************** CTYPE FACETS ***********************
//

class ctype_base {
public:

   enum mask 
   {
       space = 1<<0, print = 1<<1, cntrl  = 1<<2, 
       upper = 1<<3, lower = 1<<4, alpha  = 1<<5, 
       digit = 1<<6, punct = 1<<7, xdigit = 1<<8,
       alnum = alpha|digit,
       graph = alnum|punct,
       spcnt = space | cntrl,
       spprn = space | print,
       prpug = print | punct,
       prxag = print | xdigit | digit,
       puxag = print | upper  | xdigit | alpha,
       pualg = print | upper  | alpha,
       plxag = print | lower  | xdigit | alpha,
       plalg = print | lower  | alpha
   };

};

template <class charT>
class ctype : public ctype_base, public locale::facet {

   friend class locale::imp;

public:

   typedef charT char_type;

protected:

   virtual
   bool
   do_is (mask mask_, char_type c) const;

   virtual
   const char_type*
   do_is (const char_type* low, const char_type* high, 
      mask* vec) const;

   virtual
   const char*
   do_scan_is (mask mask_, const char_type* low, 
           const char_type* high) const;

   virtual
   const char*
   do_scan_not (mask mask_, const char_type* low, 
        const char_type* high) const;

   virtual
   char_type
   do_toupper (char_type) const;

   virtual
   const char_type*
   do_toupper (char_type* low, const char_type* high) const;

   virtual
   char_type
   do_tolower (char_type) const;

   virtual
   const char_type*
   do_tolower (char_type* low, const char_type* high) const;

   virtual
   char_type
   do_widen (char) const;

   virtual
   const char*
   do_widen (const char* lo, const char* hi, char_type* dest) const;

   virtual
   char
   do_narrow (char_type, char dfault) const;

   virtual
   const char_type*
   do_narrow (const char_type* lo, const char_type* hi,
          char dfault, char* dest) const;

   virtual
   locale::id&
   get_id () { id_.init(); return id_; }

public:

   bool
   is (mask mask_, char_type c) const
   {
       return do_is (mask_, c);
   }

   const char_type*
   is (const char_type* low, const char_type* high, 
       mask* vec) const
   {
       return do_is (low, high, vec);
   }

   const char_type*
   scan_is (mask mask_, const char_type* low, 
        const char_type* high) const
   {
       return do_scan_is (mask_, low, high);
   }

   const char_type*
   scan_not (mask mask_, const char_type* low, 
         const char_type* high) const
   {
       return do_scan_not (mask_, low, high);
   }

   char_type
   toupper (char_type c) const
   {
       return do_toupper (c);
   }

   const char_type*
   toupper (char_type* low, const char_type* high) const
   {
       return do_toupper (low, high);
   }

   char_type
   tolower (char_type c) const
   {
       return do_tolower (c);
   }

   const char_type*
   tolower (char_type* low, const char_type* high) const
   {
       return do_tolower (low, high);
   }

   char_type
   widen (char c) const
   {
       return do_widen (c);
   }

   const char*
   widen (const char* lo, const char* hi, char_type* to) const
   {
       return do_widen (lo, hi, to);
   }

   char
   narrow (char_type c, char dfault) const
   {
       return do_narrow (c, dfault);
   }

   const char_type*
   narrow (const char_type* lo, const char_type* hi, 
           char dfault, char* to) const
   {
       return do_narrow (lo, hi, dfault, to);
   }

   explicit
   ctype (size_t refs = 0)
   : locale::facet (refs) { }

//
// Static Data Member
//
   static locale::id id_;


protected:

   ~ctype () { }

};

template<class charT>
locale::id
ctype<charT>::id_;

template <class charT>
class ctype_byname : public ctype<charT> {

   friend class locale::imp;

// This class is specialized by vendors for char and wchar_t.

public:

   typedef  charT  char_type;

public:

   explicit
   ctype_byname (const char*, size_t /* refs */ = 0)
   : ctype <charT> () { }

protected:

   ~ctype_byname () { }

};

// Specializations

null_template
class ctype<char> : public ctype_base, public locale::facet {
 
   friend class locale::imp;

public:

   typedef  char  char_type;

protected:

                      mask*     table_;
   static const       mask      classic_table_[UCHAR_MAX+1];
                 // classic_table_[numeric_limits<unsigned char>::max()+1];
   static const       short         toupper_tab[UCHAR_MAX+3];
                 // toupper_tab   [numeric_limits<unsigned char>::max()+3];
   static const       short           tolower_tab[UCHAR_MAX+3];    
                 // tolower_tab   [numeric_limits<unsigned char>::max()+3];

   virtual
   char_type
   do_toupper (char_type) const;

   virtual
   const char_type*
   do_toupper (char_type* low, const char_type* high) const;

   virtual
   char_type
   do_tolower (char_type) const;

   virtual
   const char_type*
   do_tolower (char_type* low, const char_type* high) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   bool
   is (mask mask_, char_type c) const;

   const char_type*
   is (const char_type* lo, const char_type* hi, mask* vec) const;

   const char_type*
   scan_is (mask mask_, const char_type* low, 
        const char_type* high) const;

   const char_type*
   scan_not (mask mask_, const char_type* low, 
         const char_type* high) const;

   char_type
   toupper (char_type c) const
   {
      return do_toupper(c);
   }

   const char_type*
   toupper (char_type* low, const char_type* high) const
   {
      return do_toupper (low, high);
   }

   char_type
   tolower (char_type c) const
   {
      return do_tolower(c);
   }

   const char_type*
   tolower (char_type* low, const char_type* high) const
   {
      return do_tolower (low, high);
   }

   char_type
   widen (char_type c) const
   {
      return c;
   }

   const char_type*
   widen (const char_type* lo, const char_type* hi, char_type* to) const;

   char_type
   narrow (char_type c, char_type /* dfault */ ) const
   {
      return c;
   }

   const char_type*
   narrow (const char_type* lo, const char_type* hi, 
       char_type  dfault , char_type* to) const;

   explicit
   ctype (const mask* tab = 0, bool del = false, size_t refs = 0)
   : locale::facet (refs), table_ (tab ? (mask*)tab : (mask*)classic_table_),
     delete_it_ (tab ? del : false) 
   { 
   }

//
// Static Data Members
//
   static locale::id id_;

#ifdef MSIPL_STATIC_CONST_INIT
   static const size_t table_size = UCHAR_MAX+1;
#else
   static const size_t table_size;
#endif

protected:

   const mask* table () const MSIPL_THROW { return table_; }

   static const mask* classic_table () MSIPL_THROW
   { return classic_table_; }

   ~ctype () 
   {
      if (delete_it_) { delete (mask*)table_; }
   }

private :

   bool delete_it_;

};

null_template
class ctype_byname<char> : public ctype<char> {

public :

   explicit ctype_byname (const char*, size_t refs = 0)
   : ::ctype<char> (0, false, refs) { }
   
protected :
  
   ~ctype_byname () { }
/*
   virtual
   char
   do_toupper (char) const;

   virtual
   const char*
   do_toupper (char* low, const char* high) const;

   virtual
   char
   do_tolower (char) const;

   virtual
   const char*
   do_tolower (char* low, const char* high) const;
*/

};

#ifdef MSIPL_WCHART

null_template
class ctype<wchar_t> : public ctype_base, public locale::facet {

   friend class locale::imp;

public:

   typedef wchar_t char_type;

private:

   ctype_base::mask
   get_mask (char_type c) const;

protected:

   virtual
   bool
   do_is (mask mask_, char_type c) const;

   virtual
   const char_type*
   do_is (const char_type* low, const char_type* high, 
      mask* vec) const;

   virtual
   const char_type*
   do_scan_is (mask mask_, const char_type* low, 
           const char_type* high) const;

   virtual
   const char_type*
   do_scan_not (mask mask_, const char_type* low, 
        const char_type* high) const;

   virtual
   char_type
   do_toupper (char_type) const;

   virtual
   const char_type*
   do_toupper (char_type* low, const char_type* high) const;

   virtual
   char_type
   do_tolower (char_type) const;

   virtual
   const char_type*
   do_tolower (char_type* low, const char_type* high) const;

   virtual
   char_type
   do_widen (char) const;

   virtual
   const char*
   do_widen (const char* lo, const char* hi, char_type* dest) const;

   virtual
   char
   do_narrow (char_type, char dfault) const;

   virtual
   const char_type*
   do_narrow (const char_type* lo, const char_type* hi,
          char dfault, char* dest) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   bool
   is (mask mask_, char_type c) const
   {
       return do_is (mask_, c);
   }

   const char_type*
   is (const char_type* low, const char_type* high, 
       mask* vec) const
   {
       return do_is (low, high, vec);
   }

   const char_type*
   scan_is (mask mask_, const char_type* low, 
        const char_type* high) const
   {
       return do_scan_is (mask_, low, high);
   }

   const char_type*
   scan_not (mask mask_, const char_type* low, 
         const char_type* high) const
   {
       return do_scan_not (mask_, low, high);
   }

   char_type
   toupper (char_type c) const
   {
       return do_toupper (c);
   }

   const char_type*
   toupper (char_type* low, const char_type* high) const
   {
       return do_toupper (low, high);
   }

   char_type
   tolower (char_type c) const
   {
       return do_tolower (c);
   }

   const char_type*
   tolower (char_type* low, const char_type* high) const
   {
       return do_tolower (low, high);
   }

   char_type
   widen (char c) const
   {
       return do_widen (c);
   }

   const char*
   widen (const char* lo, const char* hi, char_type* to) const
   {
       return do_widen (lo, hi, to);
   }

   char
   narrow (char_type c, char dfault) const
   {
       return do_narrow (c, dfault);
   }

   const char_type*
   narrow (const char_type* lo, const char_type* hi, 
       char dfault, char* to) const
   {
       return do_narrow (lo, hi, dfault, to);
   }

   explicit
   ctype (size_t refs = 0)
   : locale::facet (refs) { }

//
// Static Data Member
//
   static locale::id id_;


protected:

   ~ctype () { }

};

#endif  //MSIPL_WCHART


#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset


#include MOD_INCLUDE(ios)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

//
// ************* CODECVT FACET ***********************
//
class codecvt_base {
public:
  enum result { ok = 0, partial, error, noconv };
};

template <class fromT, class toT, class stateT>
class codecvt : public locale::facet, public codecvt_base {
 
   friend class locale::imp;

public:

   typedef fromT     from_type;
   typedef toT       to_type;
   typedef stateT    state_type;

protected:

   virtual
   codecvt_base::result
   do_convert (state_type& /*state*/, const from_type* /*from*/,
               const from_type* /*from_end*/,
               const from_type*& /*from_next*/, to_type* /*to*/,
               to_type* /*to_limit*/, to_type*& /*to_next*/) const;

   virtual
   bool
   do_always_noconv () const MSIPL_THROW { return true; }

   virtual
   int
   do_length (const state_type& /*state*/, const from_type* /*from*/,
              const from_type* /*from_end*/, 
              size_t /*max*/) const MSIPL_THROW
   { return 0; }

   virtual
   int
   do_max_length () const MSIPL_THROW { return 0; }

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   codecvt_base::result
   convert (state_type& state, const from_type* from,
            const from_type* from_end, const from_type*& from_next,
            to_type* to, to_type* to_limit, to_type*& to_next) const
   {
       return do_convert (state, from, from_end, from_next,
                          to, to_limit, to_next);
   }

   bool
   always_noconv () const MSIPL_THROW
   { return do_always_noconv (); }

   int
   length (const state_type& state, const from_type* from,
           const from_type* from_end, size_t max) const MSIPL_THROW
   { return do_length (state, from, from_end, max); }

   int
   max_length () const MSIPL_THROW
   {  return do_max_length (); }

//
// Static Data Member
//
   static locale::id id_;

   explicit
   codecvt (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~codecvt () { }

};

template <class fromT, class toT, class stateT>
locale::id
codecvt<fromT, toT, stateT>::id_;

template <class fromT, class toT, class stateT>
class codecvt_byname : public codecvt<fromT, toT, stateT> {

   friend class locale::imp;

public:

   explicit 
   codecvt_byname (const char*, size_t refs = 0) 
   : codecvt<fromT, toT, stateT> (refs) { }

protected:

   ~codecvt_byname () { }

};

#ifdef MSIPL_WCHART

null_template
class codecvt<char, wchar_t, mbstate_t> 
     : public locale::facet, public codecvt_base {
 
   friend class locale::imp;

public:

   typedef char         from_type;
   typedef wchar_t      to_type;
   typedef mbstate_t    state_type;

protected:

   virtual
   codecvt_base::result
   do_convert (state_type& state, const from_type* from,
               const from_type* from_end, const from_type*& from_next,
               to_type* to, to_type* to_limit, to_type*& to_next) const;

   virtual
   bool
   do_always_noconv () const MSIPL_THROW { return true; }

   virtual
   int
   do_length (const state_type& state, const from_type* from,
              const from_type* from_end, size_t max) const MSIPL_THROW;

   virtual
   int
   do_max_length () const MSIPL_THROW { return MB_CUR_MAX; }

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   codecvt_base::result
   convert (state_type& state, const from_type* from,
            const from_type* from_end, const from_type*& from_next,
            to_type* to, to_type* to_limit, to_type*& to_next) const
   {
      return do_convert (state, from, from_end, from_next, to, 
                         to_limit, to_next);
   }

   bool
   always_noconv () const MSIPL_THROW
   { return do_always_noconv (); }

   int
   length (const state_type& state, const from_type* from,
           const from_type* from_end, size_t max) const MSIPL_THROW
   { return do_length (state, from, from_end, max); }

   int
   max_length () const MSIPL_THROW
   {  return do_max_length (); }


//
// Static Data Member
//
   static locale::id id_;

   explicit
   codecvt (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~codecvt () { }

};

null_template
class codecvt<wchar_t, char, mbstate_t>
       : public locale::facet, public codecvt_base {
 
   friend class locale::imp;


public:

   typedef wchar_t         from_type;
   typedef char            to_type;
   typedef mbstate_t       state_type;

protected:

   virtual
   codecvt_base::result
   do_convert (state_type& state, const from_type* from,
               const from_type* from_end, const from_type*& from_next,
               to_type* to, to_type* to_limit, to_type*& to_next) const;

   virtual
   bool
   do_always_noconv () const MSIPL_THROW { return true; }

   virtual
   int
   do_length (const state_type& state, const from_type* from,
              const from_type* from_end, size_t max) const MSIPL_THROW;

   virtual
   int
   do_max_length () const MSIPL_THROW { return MB_CUR_MAX; }


   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   codecvt_base::result
   convert (state_type& state, const from_type* from,
            const from_type* from_end, const from_type*& from_next,
            to_type* to, to_type* to_limit, to_type*& to_next) const
   {
      return do_convert (state, from, from_end, from_next, to, 
                         to_limit, to_next);
   }

   bool
   always_noconv () const MSIPL_THROW
   { return do_always_noconv (); }

   int
   length (const state_type& state, const from_type* from,
           const from_type* from_end, size_t max) const MSIPL_THROW
   { return do_length (state, from, from_end, max); }

   int
   max_length () const MSIPL_THROW
   {  return do_max_length (); }


//
// Static Data Member
//
   static locale::id id_;

   explicit
   codecvt (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~codecvt () { }

};

null_template
class codecvt<char, char, mbstate_t> 
     : public locale::facet, public codecvt_base {
 
   friend class locale::imp;

public:

   typedef char               from_type;
   typedef char               to_type;
   typedef mbstate_t          state_type;

protected:

   virtual
   codecvt_base::result
   do_convert (state_type& state, const from_type* from,
               const from_type* from_end, const from_type*& from_next,
               to_type* to, to_type* to_limit, to_type*& to_next) const;

   virtual
   bool
   do_always_noconv () const MSIPL_THROW { return true; }

   virtual
   int
   do_length (const state_type& /*state*/, const from_type* /*from*/,
              const from_type* /*from_end*/,
              size_t /*max*/) const MSIPL_THROW;

   virtual
   int
   do_max_length () const MSIPL_THROW { return 0; }


   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   codecvt_base::result
   convert (state_type& state, const from_type* from,
            const from_type* from_end, const from_type*& from_next,
            to_type* to, to_type* to_limit, to_type*& to_next) const
   {
      return do_convert (state, from, from_end, from_next, to, 
                         to_limit, to_next);
   }

   bool
   always_noconv () const MSIPL_THROW
   { return do_always_noconv (); }

   int
   length (const state_type& state, const from_type* from,
           const from_type* from_end, size_t max) const MSIPL_THROW
   { return do_length (state, from, from_end, max); }

   int
   max_length () const MSIPL_THROW
   {  return do_max_length (); }


//
// Static Data Member
//
   static locale::id id_;

   explicit
   codecvt (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~codecvt () { }

};

#endif

null_template
class codecvt<char, char, int> 
     : public locale::facet, public codecvt_base {
 
   friend class locale::imp;

public:

   typedef char               from_type;
   typedef char               to_type;
   typedef int                state_type;

protected:

   virtual
   codecvt_base::result
   do_convert (state_type& state, const from_type* from,
               const from_type* from_end, const from_type*& from_next,
               to_type* to, to_type* to_limit, to_type*& to_next) const;

   virtual
   bool
   do_always_noconv () const MSIPL_THROW { return true; }

   virtual
   int
   do_length (const state_type& /*state*/, const from_type* from,
              const from_type* from_end,
              size_t max) const MSIPL_THROW
   { return (from_end - from) < max ? from_end - from : max; }

   virtual
   int
   do_max_length () const MSIPL_THROW { return 0; }


   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   codecvt_base::result
   convert (state_type& state, const from_type* from,
            const from_type* from_end, const from_type*& from_next,
            to_type* to, to_type* to_limit, to_type*& to_next) const
   {
      return do_convert (state, from, from_end, from_next, to, 
                         to_limit, to_next);
   }

   bool
   always_noconv () const MSIPL_THROW
   { return do_always_noconv (); }

   int
   length (const state_type& state, const from_type* from,
           const from_type* from_end, size_t max) const MSIPL_THROW
   { return do_length (state, from, from_end, max); }

   int
   max_length () const MSIPL_THROW
   {  return do_max_length (); }


//
// Static Data Member
//
   static locale::id id_;

   explicit
   codecvt (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~codecvt () { }

};

//
//  ************** COLLATE FACETS ***********************
//
template <class charT>
class collate : public locale::facet {
 
   friend class locale::imp;

public:

   typedef charT                                                      char_type;
   typedef basic_string<charT, char_traits<charT>, allocator<charT> > string_type;

protected:

   virtual
   int
   do_compare (const char_type* low1, const char_type* high1,
               const char_type* low2, const char_type* high2) const;

   virtual
   string_type
   do_transform (const char_type* low, const char_type* high) const;

   virtual
   long
   do_hash (const char_type* low, const char_type* high) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public :

   int
   compare (const char_type* low1, const char_type* high1,
            const char_type* low2, const char_type* high2) const
   {
       return  do_compare (low1, high1, low2, high2);
   }

   string_type
   transform (const char_type* low, const char_type* high) const
   {
       return  do_transform (low, high);
   }

   long
   hash (const char_type* low, const char_type* high) const
   {
       return  do_hash (low, high);
   }

   static locale::id id_;

   explicit
   collate (size_t refs = 0)
   : locale::facet (refs) { }

protected:

    ~collate () { }

};

template<class charT>
locale::id
collate<charT>::id_;

template <class charT>
class collate_byname : public collate<charT> {

   friend class locale::imp;

public :

   explicit
   collate_byname (const char * name_, size_t refs = 0) 
   : ::collate<charT> (refs), name (name_) { }

protected:

   ~collate_byname () { }

    typename ::collate<charT>::string_type    name;

};


// Specialization for char

null_template
class collate<char> : public locale::facet {
 
   friend class locale::imp;

public:

   typedef char         char_type;
   typedef string       string_type;

protected:

   virtual
   int
   do_compare (const char* low1, const char* high1,
               const char* low2, const char* high2) const;

   virtual
   string_type
   do_transform (const char* low, const char* high) const;

   virtual
   long
   do_hash (const char* low, const char* high) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public :

   int
   compare (const char* low1, const char* high1,
            const char* low2, const char* high2) const
   {
       return do_compare (low1, high1, low2, high2);
   }

   string_type
   transform (const char* low, const char* high) const
   {
       return do_transform (low, high);
   }

   long
   hash (const char* low, const char* high) const
   {
       return do_hash (low, high);
   }

   static locale::id id_;

   explicit
   collate (size_t refs = 0)
   : locale::facet (refs) { }

protected:

    ~collate () { }

};

#ifdef MSIPL_WCHART

null_template
class collate<wchar_t> : public locale::facet {
 
   friend class locale::imp;

public:

   typedef wchar_t                                              char_type;
   typedef basic_string<wchar_t, char_traits<wchar_t>,
                        allocator<wchar_t> >                    string_type;

protected:

   virtual
   int
   do_compare (const char_type* low1, const char_type* high1,
               const char_type* low2, const char_type* high2) const;
      
   virtual
   string_type
   do_transform (const char_type* low, const char_type* high) const;

   virtual
   long
   do_hash (const char_type* low, const char_type* high) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public :

   int
   compare (const char_type* low1, const char_type* high1,
            const char_type* low2, const char_type* high2) const
   {
       return do_compare (low1, high1, low2, high2);
   }

   string_type
   transform (const char_type* low, const char_type* high) const
   {
       return do_transform (low, high);
   }

   long
   hash (const char_type* low, const char_type* high) const
   {
       return do_hash (low, high);
   }

   static locale::id id_;

   explicit 
   collate (size_t refs = 0)
   : locale::facet (refs) { }

protected:

    ~collate () { }

};

#endif

//
// ************ NUMERIC FACETS *************************
//
#ifdef MSIPL_DEF_TEMPARG
template <class charT, class InputIterator = 
                             istreambuf_iterator<charT> >
#else
template <class charT, class InputIterator>
#endif
class num_get : public locale::facet {
 
   friend class locale::imp;

public:

   typedef  charT                                            char_type;
   typedef  InputIterator                                    iter_type;
   typedef  ios_base::iostate                                io_state;
   typedef  basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;

   // members of num_get take a locale argument because they
   // may need to refer to the locale's numpunct facet.

protected:

#ifdef MSIPL_BOOL_BUILTIN
   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, bool& v) const;
#endif

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, unsigned short& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, unsigned int& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, long& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, unsigned long& v) const;

#ifdef __MSL_LONGLONG_SUPPORT__                                // mm 970110
   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, long long& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, unsigned long long& v) const;
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, float& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, double& v) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, long double& v) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

#ifdef MSIPL_BOOL_BUILTIN
   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state,  bool& v)  const
   {
      return do_get (from, end, f, state, v);
   }
#endif

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, unsigned short& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, unsigned int& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, long& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, unsigned long& v) const
   {
      return do_get (from, end, f, state, v);
   }

#ifdef __MSL_LONGLONG_SUPPORT__                                // mm 970110
   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, long long& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, unsigned long long& v) const
   {
      return do_get (from, end, f, state, v);
   }
#endif   /* __MSL_LONGLONG_SUPPORT__*/                 // mm 970110

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, float& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, double& v) const
   {
      return do_get (from, end, f, state, v);
   }

   iter_type
   get (iter_type from, iter_type end, ios_base& f,
        io_state& state, long double& v) const
   {
      return do_get (from, end, f, state, v);
   }

//
// Static Data Member
//
   static locale::id id_;

   explicit
   num_get (size_t refs = 0)
   : locale::facet (refs) { }

private :

   static
   int 
   scan_integral_type (iter_type&, iter_type&, ios_base&, char*) ;

   static
   bool 
   scan_float_type (iter_type&, iter_type&, ios_base&, char*) ;

protected:

   ~num_get () { }

};

template <class charT, class InputIterator>
locale::id
num_get<charT, InputIterator>::id_;

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class OutputIterator =
                       ostreambuf_iterator<charT> >
#else
template <class charT, class OutputIterator>
#endif
class num_put : public locale::facet {
 
   friend class locale::imp;


public:
   typedef  size_t                                           size_type;
   typedef  charT                                            char_type;
   typedef  OutputIterator                                   iter_type;
   typedef  ios_base::iostate                                io_state;
   typedef  basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;
private: 
   static 
   iter_type
   print_integral_type (iter_type begin, ios_base& io, char_type cfill,
                        char* buff, size_type n);

   static
   char* 
   int_fmt (char* fmt, char type, ios_base::fmtflags flag);

#ifdef __MSL_LONGLONG_SUPPORT__                   // mm 970110
   static
   char* 
   int_fmt_ll (char* fmt, char type, ios_base::fmtflags flag);
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

   static
   iter_type 
   print_float_type(iter_type begin, ios_base& io, char_type cfill,
                    char* buff, size_type nz, size_type n);

   static 
   char*
   float_fmt (char* fmt, char type, ios_base& io);
 
protected:

#ifdef MSIPL_BOOL_BUILTIN
   virtual
   iter_type
   do_put (iter_type, ios_base&, char_type cfill, bool v) const;
#endif

   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, long v) const      
   {
       char buff[200], fmt[6];
       return (print_integral_type (begin, io, cfill, buff,
           sprintf(buff, int_fmt (fmt, 'd', io.flags()),v)));
   }

#if  __dest_os == __win32_os || __MOTO__
   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, unsigned long v) const  
   {
       char buff[200], fmt[6];
       return (print_integral_type (begin, io, cfill, buff,
           sprintf(buff, int_fmt (fmt, 'u', io.flags()), (unsigned long)v)));
   }
#else
	virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, size_type v) const  
   {
       char buff[200], fmt[6];
       return (print_integral_type (begin, io, cfill, buff,
           sprintf(buff, int_fmt (fmt, 'u', io.flags()), (size_type)v)));
   }
#endif

#ifdef __MSL_LONGLONG_SUPPORT__                                           // mm 970110
   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, long long  v) const // mm 970110
   {
       char buff[200], fmt[6];
       return (print_integral_type (begin, io, cfill, buff,
           sprintf(buff, int_fmt_ll (fmt, 'd', io.flags()),  v)));
   }

   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, unsigned long long  v) const // mm 970110
   {
       char buff[200], fmt[6];
       return (print_integral_type (begin, io, cfill, buff,
           sprintf(buff, int_fmt_ll (fmt, 'u', io.flags()), (unsigned long long)v)));
   }
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, double v) const
   {
       char buff[200], fmt[8];
       size_type prec = io.precision() <= 0
                 && !(io.flags() & ios_base::fixed) ? 6
                 : io.precision();
       int MAX_CHAR = numeric_limits<char>::max ();
       int pre = MAX_CHAR < prec ? MAX_CHAR : prec;
       return (print_float_type (begin, io, cfill, buff, prec - pre,
               sprintf(buff, float_fmt (fmt, '\0', io),pre, v)));
   }

   virtual
   iter_type
   do_put (iter_type begin, ios_base& io, char_type cfill, long double v) const
   {
       char buff[200], fmt[8];
       size_type prec = io.precision() <= 0
                 && !(io.flags() & ios_base::fixed) ? 6
                 : io.precision();
       int MAX_CHAR = numeric_limits<char>::max ();
       int pre = MAX_CHAR < prec ? MAX_CHAR : prec;
       return (print_float_type (begin, io, cfill, buff, prec - pre, 
           sprintf(buff, float_fmt (fmt, 'L', io),pre, v)));
   }

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

#ifdef MSIPL_BOOL_BUILTIN
   iter_type
   put (iter_type s, ios_base& f, char_type cfill, bool v) const
   {
      return do_put (s, f, cfill, v);
   }
#endif

   iter_type
   put (iter_type s, ios_base& f, char_type cfill, long v) const
   {
      return do_put (s, f, cfill, v);
   }

#ifdef __MSL_LONGLONG_SUPPORT__                                   // mm 970110
   iter_type
   put (iter_type s, ios_base& f, char_type cfill, long long v) const  // mm 970110
   {
      return do_put (s, f, cfill, v);
   }
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

   iter_type
   put (iter_type s, ios_base& f, char_type cfill, unsigned long v) const
   {
      return do_put (s, f, cfill, v);
   }

#ifdef __MSL_LONGLONG_SUPPORT__                                           // mm 970110
   iter_type
   put (iter_type s, ios_base& f, char_type cfill, unsigned long long v) const  // mm 970110
   {
      return do_put (s, f, cfill, v);
   }
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

   iter_type
   put (iter_type s, ios_base& f, char_type cfill, double v)const
   {
      return do_put (s, f, cfill, v);
   }

   iter_type
   put (iter_type s, ios_base& f, char_type cfill, long double v) const
   {
      return do_put (s, f, cfill, v);
   }

//
// Static Data Member
//
   static locale::id id_;

   explicit
   num_put (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~num_put () { }

};

template <class charT, class InputIterator>
locale::id
num_put<charT, InputIterator>::id_;

// numpunct is used by num_get and num_put facets.

template <class charT>
class numpunct : public locale::facet {
 
   friend class locale::imp;

public:

   typedef  charT                                            char_type;
   typedef  basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;

protected:

   virtual
   char_type
   do_decimal_point () const { return dec_pt; }

   virtual
   char_type
   do_thousands_sep () const { return thou_sep; }

   virtual
   string
   do_grouping () const { return grp; }

   virtual
   string_type
   do_truename () const { return name_true; }

   virtual
   string_type
   do_falsename () const { return name_false; }

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

   explicit
   numpunct (const char* name, size_t refs = 0) 
   : locale::facet (refs) { init (name); }

   ~numpunct () { }

public:

   char_type
   decimal_point () const { return do_decimal_point (); }

   char_type
   thousands_sep () const { return do_thousands_sep (); }

   string
   grouping () const { return do_grouping (); }

   string_type
   truename () const { return do_truename (); }

   string_type
   falsename () const { return do_falsename (); }

   explicit
   numpunct (size_t refs = 0)
   : locale::facet (refs) { init ("C"); }

//
// Static Data Member
//
   static locale::id id_;

private:

   void
   init (const char* name)
   {
       const char* old_name = setlocale (LC_ALL, 0);

       if (setlocale (LC_NUMERIC, name) != 0)
       {
           struct lconv* lptr = localeconv ();
           dec_pt     = lptr->decimal_point[0];
           thou_sep   = lptr->thousands_sep[0];
           name_true  = string_type ("true");
           name_false = string_type ("false");
           grp        = string (lptr->grouping); 
       }
       else 
       {
#ifdef MSIPL_EXCEPT           
           throw runtime_error ("Invalid locale name");
#else 
           fprintf (stderr, "Invalid locale name\n");
           exit (1);
#endif
       }
       setlocale (LC_ALL, old_name);
   }

   char_type         dec_pt;
   char_type         thou_sep;
   string            grp;
   string_type       name_true;
   string_type       name_false;

};

template <class charT>
locale::id
numpunct<charT>::id_;

template <class charT>
class numpunct_byname : public numpunct<charT> {

   friend class locale::imp;

public:

   typedef  charT                                            char_type;
   typedef  basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;

   //
   // constructor
   //
   explicit
   numpunct_byname (const char* name, size_t refs = 0) 
   : numpunct<charT> (name, refs) { } 

protected:

   ~numpunct_byname () { }

};

#ifdef MSIPL_BOOL_BUILTIN
template <class charT, class OutputIterator>
inline
num_put<charT, OutputIterator>::iter_type
num_put<charT, OutputIterator>::
do_put (iter_type iter, ios_base& io, char_type cfill, bool v) const
{
   cfill;		//961205 bkoz this to remove strict compiler warnings
   const locale& loc = io.getloc ();
   const numpunct<charT>& punct = use_facet (loc, (numpunct<charT>*)0);

   string_type str;

   if (io.flags() & ios_base::boolalpha)
   {
      str = (v ? punct.truename() : punct.falsename());
      size_t cnt = 0;
      while (cnt < str.size())
      {
     *iter++ = str[cnt];
     cnt ++;
      }
   } else
   {
      *iter++ = (v ? '1' : '0');
   }
   return iter;
}
#endif

template <class charT, class OutputIterator>
inline 
num_put<charT, OutputIterator>::iter_type 
num_put<charT, OutputIterator>::print_integral_type(iter_type begin,
                      ios_base& io, char_type cfill,
                      char *buff, size_type n)
{
   size_type p = *buff == '+' || *buff == '-' ? 1 : *buff == '0' &&
                         (buff[1] == 'x' || buff[1] == 'X')? 2 
                         : *buff != '0' ? 0 : 
                          *(buff+1) != '\0'? 1:0;
   const numpunct<charT>& punct = 
                use_facet (io.getloc(), (numpunct<charT>*)0);
   const char_type        thou_sep  = punct.thousands_sep ();
   const char* G = punct.grouping ().c_str();
   size_type index = n;
   const int MAX_CHAR = numeric_limits<char>::max ();

   for (; *G !=MAX_CHAR && *G < (index - p) && *G > '\0'; )
   {
        index -= *G;
        memmove(&buff[index+1] ,&buff[index] ,n + 1 - index);
        buff[index] = ',', ++n;
        if ('\0' < G[1])
           ++G;
   }

   size_type pad = io.width() > n ? io.width() - n : 0;
   ios_base::fmtflags flag = io.flags() & ios_base::adjustfield;
   
   if (flag == ios_base::internal) 
        for ( ; p > 0; p--, n--, begin++, buff++)
             *begin = *buff;
   if(flag != ios_base::left)
        for ( ; pad > 0; pad--, begin++)
             *begin = cfill;     

   for( ; n > 0; ++begin, ++buff, --n)
        if (*buff == ',')
           *begin = thou_sep;
        else
           *begin = *buff;
   io.width(0);
    
   for ( ; pad > 0; pad--, begin++)
        *begin = cfill;     
    
   return begin;
}


template <class charT, class OutputIterator>
inline char* 
num_put<charT, OutputIterator>::int_fmt (char* fmt, char type,
                                         ios_base::fmtflags flag)
{
    char *fmt1 = fmt;
    *fmt1++ = '%';
    if(flag & ios_base::showpos)
        *fmt1++ = '+';
    if(flag & ios_base::showbase)
        *fmt1++ = '#';
    *fmt1++ = 'l';
    ios_base::fmtflags Bflag = flag & ios_base::basefield; 
    *fmt1++ = Bflag == ios_base::oct ? 'o'
           : Bflag != ios_base::hex ? type
           : flag & ios_base::uppercase ? 'X' : 'x';   
    *fmt1++ = '\0';
    return fmt;
}

#ifdef __MSL_LONGLONG_SUPPORT__             // mm 970110
template <class charT, class OutputIterator>
inline char* 
num_put<charT, OutputIterator>::int_fmt_ll (char* fmt, char type,
                                         ios_base::fmtflags flag)
{
    char *fmt1 = fmt;
    *fmt1++ = '%';
    if(flag & ios_base::showpos)
        *fmt1++ = '+';
    if(flag & ios_base::showbase)
        *fmt1++ = '#';
    *fmt1++ = 'L';                       // mm 970110
    ios_base::fmtflags Bflag = flag & ios_base::basefield; 
    *fmt1++ = Bflag == ios_base::oct ? 'o'
           : Bflag != ios_base::hex ? type
           : flag & ios_base::uppercase ? 'X' : 'x';   
    *fmt1++ = '\0';
    return fmt;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                      // mm 970110

template <class charT, class OutputIterator>
inline 
num_put<charT, OutputIterator>::iter_type 
num_put<charT, OutputIterator>::print_float_type(iter_type begin,
                      ios_base& io, char_type cfill,
                      char *buff, size_type nz, size_type n)
{
   int pad = io.width() > n + nz ? io.width() - n - nz: 0;
   ios_base::fmtflags flag = io.flags() & ios_base::adjustfield;

   if ((*buff == '+' || *buff == '-') && (io.flags() & ios_base::internal))
   {   
       *begin = *buff++;
       begin++, --n;
   }
   if(flag != ios_base::left)
        for ( ; pad > 0; pad--, begin++)
             *begin = cfill;     

   char* p = (char*)memchr (buff, localeconv()->decimal_point[0],n); 
   if (p)
   {     
        for (; buff != p; begin++, --n)
             *begin = *buff++;
        *begin = use_facet (io.getloc(), (numpunct<charT>*)0).decimal_point();
        begin++, buff++, --n;
   }

   //if (p = (char*)memchr (buff,'e',n))	//961205 bkoz
   p = (char*)memchr (buff,'e',n);
   if (p)
   {
        for (;buff != p; begin++, --n)
                *begin = *buff++;
        for (; nz > 0; nz--)
             *begin = '0';
        *begin = io.flags() & ios_base::uppercase ? 'E' : 'e';
        begin++, buff++, --n;
   }


   for( ;n > 0; n--, begin++)
        *begin = *buff++;
   for( ;nz > 0; nz--, begin++)
        *begin = '0';
   
   io.width(0);
    
   for ( ; pad > 0; pad--, begin++)
        *begin = cfill;     
    
   return begin;
}

template <class charT, class OutputIterator>
inline char* 
num_put<charT, OutputIterator>::float_fmt (char* fmt, char type, ios_base& io)
{
    char *fmt1 = fmt;
    ios_base::fmtflags flag = io.flags();
   
    *fmt1++ = '%';
    if(flag & ios_base::showpos)
        *fmt1++ = '+';
    if(flag & ios_base::showbase)
        *fmt1++ = '#';
    *fmt1++ = '.';
    *fmt1++ = '*' ;
    if(type != '\0')
        *fmt1++ = type;
    ios_base::fmtflags Fflag = flag & ios_base::floatfield; 
    *fmt1++ = Fflag == ios_base::fixed ? 'f'
           : Fflag == ios_base::scientific ? 'e' : 'g';   
    *fmt1++ = '\0';
    return fmt;
}

template <class charT, class InputIterator>
inline 
int 
num_get<charT, InputIterator>::
scan_integral_type (iter_type &begin, iter_type &end,
                    ios_base& io, char* buf) 
{

   typedef string_type::traits_type straits_type;
   const numpunct<charT>& punct    = use_facet (io.getloc (), (numpunct<charT>*)0);

   const string&          grp      =  punct.grouping ();
   const char_type        thou_sep =  punct.thousands_sep ();

   // For checking grouping
   //
   int     seps [20];
   int     num_seps    = 0;
   int     digits_seen = 0;
   const int Size = grp.size();


   char*  cur  = buf;

  if(begin != end && memchr("-+",*cur = *begin, 2)) 
      cur++, ++begin;
 
  const ios_base::fmtflags radflag = io.flags () & ios_base::basefield;
  int radix = radflag == ios_base::oct ? 8:
      radflag == ios_base::hex ? 16:
      radflag == ios_base::dec ? 10 : 0;

  if (begin != end && straits_type::eq (*begin, '0'))
          if ((radix == 16|| radix==0) && (++begin) != end &&    // mm 970121
           ( straits_type::eq(*begin, 'x') || straits_type::eq(*begin, 'X')))
              ++begin, radix = 16;
          else
             if (radix == 8 || radix == 0)         //MW-mm 970130
             {                                     //MW-mm 970130
             	++begin;                           //MW-mm 970130
	            radix = 8; 
	         }                                     //MW-mm 970130

  int len = radix == 0 || radix == 10 ? 10: radix == 8 ? 8 : 24;
  for (;begin != end; ++begin)
      if(memchr("0123456789abcdefABCDEF", *cur = *begin, len))
          ++cur, ++digits_seen;
      else if (Size && straits_type::eq (*begin, thou_sep))
          seps[num_seps++] = digits_seen;
      else
          break;

  int fflag = true;
  size_t count = 0;
  const int MAX_CHAR = numeric_limits<char>::max ();
  if (num_seps) 
  {
    do 
      if (grp[count] == MAX_CHAR) fflag = false;
      else { digits_seen -= (grp[count] & 0xF);
           if (digits_seen != seps[--num_seps]) fflag = false;
           else if ((count+1) < Size) ++count;} 
    while (num_seps && fflag);
    if (grp[count] != MAX_CHAR && 
       digits_seen > (grp[count] & 0xF))
       fflag = false; 
  }  
   if(!fflag)
       cur = buf;
   *cur         = '\0';
   return radix;
}

template <class charT, class InputIterator>
inline bool 
num_get<charT, InputIterator>::
scan_float_type (iter_type& begin,
                 iter_type& end, ios_base& io, char* buf) 
{
   typedef string_type::traits_type straits_type;
   const numpunct<charT>&        punct     =  use_facet (io.getloc(),
                                           (numpunct<charT>*)0);
   const string&                  grp       =  punct.grouping ();
   const charT thou_sep = punct.thousands_sep ();

   bool    flag               = false;
   int     seps [20];
   int     num_seps    = 0;
   int     digits_seen = 0;
   const int Size = grp.size();
   char*  cur  = buf;

   if(begin != end && memchr("-+",*cur = *begin, 2)) 
       cur++, ++begin;

   for (;begin != end; ++begin)       
       if(memchr("0123456789", *cur = *begin, 10))
           flag = false, ++cur, ++digits_seen;
       else if (Size && *cur == thou_sep)
           flag = true, seps[num_seps++] = digits_seen;    
       else break;
              
   if(flag)
       return false;
   
   if (begin != end && straits_type::eq (*begin, punct.decimal_point ()))
       for (flag = true, *cur++ = localeconv()->decimal_point[0], ++begin;
            begin != end && memchr("0123456789", *cur = *begin, 10); ++begin)
           ++cur, flag = false;
   if(flag)
       return false;

   if(begin != end && memchr("eE",*cur = *begin, 2)) 
   {
      flag = true, ++cur, ++begin;
      if(begin != end && memchr("-+",*cur = *begin, 2))
         ++cur, ++begin;
      for (;begin != end && memchr("0123456789", *cur = *begin, 10); ++cur,++begin)
         flag = false;  
   }
   if(flag)
       return false;

   size_t count = 0;
   const int MAX_CHAR = numeric_limits<char>::max ();
   if (num_seps) 
   {
      do 
       if (grp[count] == MAX_CHAR) 
         return false;
         else if ((digits_seen -= (grp[count] & 0xF)) != seps[--num_seps]) 
         return false;
         else if ((count+1) < Size) ++count; 
      while (num_seps);
      if (digits_seen > (grp[count] & 0xF))
          return false; 
  }  
  *cur = '\0';

  return true;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, float& units) const
{
    char    buf [200];
    float    result = 0.0F;
    int scanned = 0;

    if(scan_float_type (begin, end, io, buf))
       scanned = sscanf (buf, "%f", &result);
    if(begin == end)
       state |= ios_base::eofbit;
    if (scanned != 1) 
       state |= ios_base::failbit;
    units = result;
    return begin;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, double& units) const
{
    char    buf [200];
    double    result = 0.0F;
    int scanned = 0;
    
    if(scan_float_type (begin, end, io, buf))
        scanned = sscanf (buf, "%lf", &result);
    if(begin == end)
       state |= ios_base::eofbit;
    if (scanned != 1) 
       state |= ios_base::failbit;
    units = result;
    return begin;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, long double& units) const
{
    char    buf [200];
    long double    result = 0.0F;
    int scanned = 0;
    char    fmt[4] = "%Lf";
    
    if(scan_float_type (begin, end, io, buf))
       scanned = sscanf (buf, fmt, &result);
    if(begin == end)
       state |= ios_base::eofbit;
    if (scanned != 1) 
       state |= ios_base::failbit;
    units = result;
    return begin;
}


template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, long& units) const
{
    char   buf [200], *p;
    int OldErr = errno;
    const long result = strtol(buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = result;
    errno = OldErr;
    return begin;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, unsigned long& units) const
{
    char   buf [200], *p;
    int OldErr = errno;

    unsigned long result = strtoul (buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = result;
    errno = OldErr;
    return begin;
}

#ifdef __MSL_LONGLONG_SUPPORT__                                     // mm 970110
template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, long long& units) const
{
    char   buf [200], *p;
    int OldErr = errno;
    const long long result = strtoll(buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = result;
    errno = OldErr;
    return begin;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, unsigned long long& units) const
{
    char   buf [200], *p;
    int OldErr = errno;

    unsigned long long result = strtoull (buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = result;
    errno = OldErr;
    return begin;
}
#endif   /* __MSL_LONGLONG_SUPPORT__*/                            // mm 970110

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, unsigned short& units) const
{
    char   buf [200], *p;
    int OldErr = errno;

    unsigned long result = strtoul (buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = (unsigned short)result;
    if (result > USHRT_MAX)
    {
       units = USHRT_MAX;
       state |= ios_base::failbit;
    }
    errno = OldErr;
    return begin;
}

template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, unsigned int& units) const
{
    char   buf [200], *p;
    int OldErr = errno;

    unsigned long result = strtoul (buf, &p, scan_integral_type (begin, end, io, buf));

    if(begin == end)
       state |= ios_base::eofbit;

    if(buf == p || errno == ERANGE)
       state |= ios_base::failbit;
    units = (unsigned int)result;

    if (result > UINT_MAX)
    {
       units = UINT_MAX;
       state |= ios_base::failbit;
    }

    errno = OldErr;
    return begin;
}

#ifdef MSIPL_BOOL_BUILTIN
template <class charT, class InputIterator>
inline
num_get<charT, InputIterator>::iter_type
num_get<charT, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io,
        io_state& state, bool& units) const
{
   const locale& loc            = io.getloc ();
   const numpunct<charT>& punct =  use_facet (loc, (numpunct<charT>*)0);

   const string_type&     true_name  =  punct.truename ();
   const string_type&     false_name =  punct.falsename ();

   size_t  bool_pos = 0;


   //
   // Assumption that true_name & false_name are non-empty
   // And they do not match in the first character
   //
   if (io.flags () & ios_base::skipws)
   {
       while ((begin != end) && is_space (*begin, loc))
       ++begin;
   } else if (is_space (*begin, loc))
   {
       state |= ios_base::failbit;
       return begin;
   }

   if (io.flags () & ios_base::boolalpha)
   {
        while ((begin != end) && (bool_pos < true_name.size()) &&
               string_type::traits_type::eq(*begin,
                                            true_name[bool_pos]))
        {
            ++begin;
            ++bool_pos;
        }
        if (bool_pos == true_name.size())
        {
            units = true;
            return begin;
        }
        else if (bool_pos == 0)
        {
            while ((begin != end) && (bool_pos < false_name.size()) &&
                   string_type::traits_type::eq(*begin,
                             false_name[bool_pos]))
            {
                ++begin;
                ++bool_pos;
            }
            if (bool_pos == false_name.size())
            {
                units = false;
                return begin;
            }
        }
   }
   else
   {
       if (string_type::traits_type::eq (*begin, '0') ||
           string_type::traits_type::eq (*begin, '1'))
       {
           units = string_type::traits_type::eq (*begin, '1');
           ++begin;
           return begin;
       }
   }

   state |= ios_base::failbit;
   return begin;
}
#endif

//
//  ************** MONETARY FACETS ***********************
//

class money_base {

public:
   enum part { symbol='?', sign='-', space=' ', value='v', none='0' };

   struct pattern { char field[4+1]; };

   static money_base::pattern get_pat ()
   { 
       pattern ret;
       strcpy (ret.field, "?-v0");
       return ret;
   }

   static money_base::pattern
   get_pat (int cs_precedes, int sep_by_space,
            int sign_posn, bool& paren)
   {
       paren = false;
       const char pat_arr[16][5] = { "- v?", "v? -", "v-? ", "v?- ",
                                     "-v ?", "v ?-", "v -?", "v ?-",
                                     "- ?v", "?v -", "-?v ", "?-v ",
                                     "-? v", "? v-", "-? v", "?- v"
                                   };
   
       if (sign_posn) sign_posn--;
       else paren = true;
   
       int idx = (cs_precedes<<3) + (sep_by_space<<2) + sign_posn;
   
       pattern ret;
       strncpy(ret.field, pat_arr[idx], 4);
       ret.field[4] = 0;
       return ret;
   }
};  // end class money_base

#ifdef MSIPL_DEF_TEMPARG
template <class charT, bool Intl = false>
#else
template <class charT, bool Intl>
#endif
class moneypunct : public locale::facet , public money_base {
 
   friend class locale::imp;

public:

   typedef charT                                            char_type;
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >                  string_type;

#ifdef MSIPL_STATIC_CONST_INIT
   static const bool intl = Intl;
#else
   static const bool intl;
#endif

protected:

   virtual
   char_type
   do_decimal_point () const { return dec_pt; }

   virtual
   char_type
   do_thousands_sep () const { return thou_sep; }

   virtual
   string
   do_grouping () const { return grp; }

   virtual
   string_type
   do_curr_symbol () const { return curr_sym; }

   virtual
   string_type
   do_positive_sign () const { return pos_sign; }

   virtual
   string_type
   do_negative_sign () const { return neg_sign; }

   virtual
   int
   do_frac_digits () const { return frac_dig; }

   virtual
   money_base::pattern
   do_pos_format () const { return money_base::get_pat (); }

   virtual
   money_base::pattern
   do_neg_format () const { return money_base::get_pat (); }
  
   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

   explicit
   moneypunct (const char* name, size_t refs = 0) 
   : locale::facet (refs) { init (name); }

   ~moneypunct () { }

public:

   char_type
   decimal_point () const { return do_decimal_point (); }

   char_type
   thousands_sep () const { return do_thousands_sep (); }

   string
   grouping () const { return do_grouping (); }

   string_type
   curr_symbol () const { return do_curr_symbol (); }

   string_type
   positive_sign () const { return do_positive_sign (); }

   string_type
   negative_sign () const { return do_negative_sign (); }

   int
   frac_digits () const { return do_frac_digits (); }

   money_base::pattern
   pos_format () const { return do_pos_format (); }

   money_base::pattern
   neg_format () const { return do_neg_format (); }

   explicit
   moneypunct (size_t refs = 0)
   : locale::facet (refs) { init (""); }

   static locale::id id_;

private:

   void
   init (const char* name)
   {
       const char* old_name = setlocale (LC_ALL, 0);
       if (setlocale (LC_MONETARY, name) != 0)
       {
          struct lconv* lptr = localeconv ();
          if (intl)
          {
             curr_sym = string_type(lptr->int_curr_symbol);
             frac_dig = lptr->int_frac_digits;
          } 
          else
          {
             curr_sym = string_type(lptr->currency_symbol);
             frac_dig = lptr->frac_digits;
          }

          dec_pt   = lptr->mon_decimal_point[0];
          thou_sep = lptr->mon_thousands_sep[0];
          pos_sign = string_type (lptr->positive_sign);
          neg_sign = string_type (lptr->negative_sign);
    
          grp      = string (lptr->mon_grouping);

          bool paren;
          pos_fmt  = money_base::get_pat (lptr->p_cs_precedes & 0x1,
                                          lptr->p_sep_by_space & 0x1,
                                          lptr->p_sign_posn & 0xf, paren);
          if (paren) { pos_sign.append (1, (char_type)'(');
                       pos_sign.append (1, (char_type)')'); }
          neg_fmt  = money_base::get_pat (lptr->n_cs_precedes & 0x1,
                                          lptr->p_sep_by_space & 0x1,
                                          lptr->n_sign_posn & 0xf, paren);
          if (paren) { neg_sign.append (1, (char_type)'(');
                       neg_sign.append (1, (char_type)')'); }
       } 
       else 
       {
#ifdef MSIPL_EXCEPT           
          throw runtime_error ("Invalid locale name");
#else 
          fprintf (stderr, "Invalid locale name\n");
          exit (1);
#endif
       }
       setlocale (LC_ALL, old_name);
   }

   char_type             dec_pt;
   char_type             thou_sep;
   string_type           curr_sym;
   string_type           pos_sign;
   string_type           neg_sign;
   string                grp;
   int                   frac_dig;
   
   money_base::pattern   pos_fmt;
   money_base::pattern   neg_fmt;

};

#ifndef MSIPL_STATIC_CONST_INIT
template <class charT, bool Intl>
const bool
moneypunct<charT, Intl>::intl = Intl;
#endif

template <class charT, bool Intl>
locale::id
moneypunct<charT, Intl>::id_;

#ifdef MSIPL_DEF_TEMPARG
template <class charT, bool Intl = false>
#else
template <class charT, bool Intl>
#endif
class moneypunct_byname : public moneypunct<charT, Intl> {

   friend class locale::imp;

public:

   typedef charT                                            char_type;
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >                  string_type;
 
   //
   // constructor
   //
   explicit
   moneypunct_byname (const char* name, size_t refs = 0) 
   : moneypunct<charT, Intl> (name, refs) { }

protected:

   ~moneypunct_byname () { }

};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, bool Intl = false,
          class OutputIterator =
          ostreambuf_iterator<charT> >
#else
template <class charT, bool Intl, class OutputIterator>
#endif
class money_put : public locale::facet {
 
   friend class locale::imp;

public:

   typedef charT                                            char_type;
   typedef OutputIterator                                   iter_type;
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >                  string_type;

#ifdef MSIPL_STATIC_CONST_INIT
   static const bool intl = Intl;
#else
   static const bool intl;
#endif

protected:

   virtual
   iter_type
   do_put (iter_type, ios_base&, char_type cfill, long double units) const;

   virtual
   iter_type
   do_put (iter_type, ios_base&, char_type cfill,
           const string_type& digits) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   iter_type
   put (iter_type s, ios_base& f, char_type cfill,
        long double& units) const
   {
      return do_put (s, f, cfill, units);
   }

   iter_type
   put (iter_type s, ios_base& f, char_type cfill,
        string_type& digits) const
   {
      return do_put (s, f, cfill, digits);
   }

   static locale::id id_;

   explicit 
   money_put (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~money_put () { }

private:

   static 
   string_type
   money_fmt (ios_base& io, char_type cfill,
              const moneypunct<charT, Intl>& punct, 
              long double units);


};

template <class charT, bool Intl, class InputIterator>
locale::id
money_put<charT, Intl, InputIterator>::id_;

#ifndef MSIPL_STATIC_CONST_INIT
template <class charT, bool Intl, class InputIterator>
const bool
money_put<charT, Intl, InputIterator>::intl = Intl;
#endif

#ifdef MSIPL_DEF_TEMPARG
template <class charT, bool Intl = false,
          class InputIterator =
          istreambuf_iterator<charT> >
#else
template <class charT, bool Intl,class InputIterator>
#endif
class money_get : public locale::facet {

   friend class locale::imp;

public:

   typedef charT                                           char_type;
   typedef InputIterator                                   iter_type;
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >                 string_type;
   typedef ios_base::iostate                               io_state;

#ifdef MSIPL_STATIC_CONST_INIT
   static const bool intl = Intl;
#else
   static const bool intl;
#endif

protected:

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, long double& units) const;

   virtual
   iter_type
   do_get (iter_type, iter_type, ios_base&,
           io_state& state, string_type& digits) const;

   virtual
   locale::id&
   get_id () { id_.init (); return id_; }

public:

   iter_type
   get (iter_type s, iter_type e, ios_base& f,
        io_state& state, long double& units) const
   {
       return do_get (s, e, f, state, units);
   }

   iter_type
   get (iter_type s, iter_type e, ios_base& f,
        io_state& state, string_type& digits) const
   {
       return do_get (s, e, f, state, digits);
   }

   static locale::id id_;

   explicit
   money_get (size_t refs = 0)
   : locale::facet (refs) { }

protected:

   ~money_get () { }

private:

    static 
    iter_type
    extract_value (iter_type begin, iter_type end, ios_base& io,
                   io_state& state, charT* buf, int& charTread, bool);

};

template <class charT, bool Intl, class InputIterator>
locale::id 
money_get<charT, Intl, InputIterator>::id_;

#ifndef MSIPL_STATIC_CONST_INIT
template <class charT, bool Intl, class InputIterator>
const bool
money_get<charT, Intl, InputIterator>::intl = Intl;
#endif

template <class charT, bool Intl, class InputIterator>
inline
money_get<charT, Intl, InputIterator>::iter_type
money_get<charT, Intl, InputIterator>::
extract_value (iter_type begin, iter_type end, ios_base& io,
               io_state& state, charT* buf, int& charTread, bool paren)
{
   typedef basic_string<charT, char_traits<charT>,
                        allocator<charT> >                 string_type;
   typedef string_type::traits_type                        straits_type;

   const locale& loc                        = io.getloc ();
   const moneypunct<charT, Intl>& punct     = use_facet (loc,
                                      (moneypunct<charT, Intl>*)0);
   const string&                  grp       = punct.grouping ();
   char_type                      dec_pt    = punct.decimal_point ();
   char_type                      thou_sep  = punct.thousands_sep ();
   int                            frac_dig  = punct.frac_digits ();
   money_base::pattern            pat       = punct.neg_format ();

   bool   no_thou_sep = false;

   bool   founddpt       = false;
   bool   end_parsing    = false;

   // on input, if punct::grouping returns the empty string
   // thousand separators shld not be considered
   if (grp.size () == 0)
      no_thou_sep = true;

   // For checking grouping
   // Assumption that seps array of 20 ints
   // should be sufficient
   int    seps [20];
   int    num_seps    = 0;
   int    digits_seen = 0;

   charT* cur         = buf;

   charTread          = 0;

   *cur  = straits_type::eos();

   while (begin != end && is_digit (*begin, loc) && !end_parsing)
   {
        *cur++ = *begin++;
        ++digits_seen;
        if (founddpt) frac_dig--;
        if (!founddpt && !no_thou_sep &&
            straits_type::eq (*begin, thou_sep))
        {
            begin++;
            if (straits_type::eq (thou_sep, ' '))
            {
              if (begin != end)
              {
                if (straits_type::eq (*begin, thou_sep))
                {
                   end_parsing = true;
                   if (paren || pat.field[3] != money_base::value) begin++;
                }
              } else { state |= ios_base::failbit; return begin; }
            }
            seps[num_seps++] = digits_seen;
        } else if (!founddpt && straits_type::eq (*begin, dec_pt))
        {
            if (!__msipl_check_grouping (digits_seen, num_seps, seps, grp))
            {
                state |= ios_base::failbit;
                return begin;
            }
            founddpt = true;
            digits_seen = 0;
            ++begin;
        } else if (founddpt && frac_dig == 0)
        {   // extra frac digits
            if (begin != end && is_digit (*begin, loc))
            {
                state |= ios_base::failbit;
                return begin;
            }
            else if (!no_thou_sep && straits_type::eq (thou_sep, ' ') &&
                     straits_type::eq (*begin, thou_sep))
            { 
               ++begin;
               if (begin != end)
               {
                   if (straits_type::eq (*begin, thou_sep))
                   {
                      end_parsing = true;
                      if (paren || pat.field[3] != money_base::value)
                        ++begin;
                   }
               } else { state |= ios_base::failbit; return begin; }
            } else if (is_space (*begin, loc))
               end_parsing = true;
        }
    }
    if (frac_dig == punct.frac_digits () && !founddpt)
    {
        end_parsing = true; 
    }
    
    if (cur == buf)
       end_parsing = false;
    if (frac_dig)
       for (int i = 0; i < frac_dig; i++) *cur++ = '0';
    *cur = straits_type::eos ();
    charTread = (end_parsing  ? cur - buf : 0);
    return begin;
}

template <class charT, bool Intl, class InputIterator>
inline
money_get<charT, Intl, InputIterator>::iter_type
money_get<charT, Intl, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io, io_state& state,
        long double& units) const
{
    typedef  string_type::traits_type   straits_type;

    string_type    str;
    charT          buffer [200];

    begin = do_get (begin, end, io, state, str);

    straits_type::copy (buffer, str.data(), str.size());
    buffer[str.size ()] = straits_type::eos ();

    long double result;
    charT    fmt[4] = "%Lf";

    int scanned = __msipl_sscanf (buffer, fmt, &result);

    if (scanned != 1)
       state |= ios_base::failbit;
    else
       units = result;
 
    return begin;
}

template <class charT, bool Intl, class InputIterator>
inline
money_get<charT, Intl, InputIterator>::iter_type
money_get<charT, Intl, InputIterator>::
do_get (iter_type begin, iter_type end, ios_base& io, io_state& state,
        string_type& digits) const
{
    typedef string_type::traits_type       straits_type;

    const locale& loc                    = io.getloc ();
    const moneypunct<charT, Intl>& punct = use_facet (loc,
                          (moneypunct<charT, Intl>*)0);

    const string_type&   curr_sym    =   punct.curr_symbol ();
    const string_type&   pos_sign    =   punct.positive_sign ();
    const string_type&   neg_sign    =   punct.negative_sign ();

    string_type          sign;
    money_base::pattern  pat = punct.neg_format ();

    bool                 paren  = false;
    bool                 sign_  = false;
    bool                 value_ = false;
    bool                 space_ = false;
    bool                 end_parsing = false;

    charT buffer[200];
    bool  isNeg = false;

    // eat leading white spaces
    if (io.flags () & ios_base::skipws)
    {
       while ((begin != end) && is_space (*begin, loc))
       ++begin;
    } else if (is_space (*begin, loc))
    {
       state |= ios_base::failbit;
       return begin;
    }

    for (int pat_cnt = 0; pat_cnt < 4; pat_cnt++)
    {
       switch (pat.field[pat_cnt])
       {
          case money_base::space :
          {
              if (begin != end && is_space (*begin, loc)) begin++;
              else { state |= ios_base::failbit; return begin; }
              space_ = true;
              end_parsing = space_ && value_ && sign_ ;
              break;
          }
          case money_base::symbol :
          {
              int sym_pos = 0;
              int sym_size = curr_sym.size ();
              bool is_needed = io.flags () & ios_base::showbase;
              
              if (is_needed || (!end_parsing && !is_needed) || paren)
              {
                  while (begin != end &&
                         sym_pos < sym_size &&
                         straits_type::eq (*begin, curr_sym[sym_pos]))
                  { sym_pos++; begin++; }
                  if (sym_pos != sym_size)
                  { state |= ios_base::failbit; return begin; }
              }
              break;
          }
          case money_base::sign :
          {
              if (straits_type::eq (*begin, neg_sign[0]))
              {
                  isNeg = true;
                  if (neg_sign.size () > 1) paren = true;
              } else if (straits_type::eq (*begin, pos_sign[0]))
              {
                  isNeg = false;
                  if (pos_sign.size () > 1) paren = true;
              } else { state |= ios_base::failbit; return begin; }
              begin++;
              sign = (isNeg ? neg_sign : pos_sign);
              if (sign.size () == 1) sign_ = true;
              break;
          }
          case money_base::value :
          {
              int charTread = 0;
              begin = extract_value (begin, end, io, state,
                                     buffer, charTread, paren);
              if (charTread == 0)
              { state |= ios_base::failbit; return begin; }
              value_ = true;
              break;
          }
       }
    } // end for loop
    if (!sign_)
    {
       int signPos = 1;
       while (begin!= end && signPos < sign.size () &&
              straits_type::eq (*begin, sign[signPos]))
       { signPos++; begin++; }
       if (signPos != sign.size ())
       { state |= ios_base::failbit; return begin; }
    }
    digits = buffer;
    if (isNeg)
       digits.insert ((string_type::size_type)0, 1, '-');
    return begin;
}

template <class charT, bool Intl, class OutputIterator>
inline
money_put<charT, Intl, OutputIterator>::iter_type
money_put<charT, Intl, OutputIterator>::
do_put (iter_type iter, ios_base& io, char_type cfill,
        long double units) const
{
   const locale& loc                    = io.getloc ();
   const moneypunct<charT, Intl>& punct = use_facet(loc,
                                         (moneypunct<charT, Intl>*)0);
   money_base::pattern      pat;
   string_type              sign;
   bool                     sign_ = false;
 
   string_type str;
 
   // read the format from moneypunct
   if (units > 0)
   {
       pat  =  punct.pos_format ();
       sign =  punct.positive_sign ();
   } 
   else
   {
       pat   =  punct.neg_format ();
       sign  =  punct.negative_sign ();
       units =  -units;
   }
 
   for (int i = 0; i < 4; ++i)
   {
      switch (pat.field[i])
      {
          case money_base::symbol :
               if (sign_ || io.flags() & ios_base::showbase)
                  str.append (punct.curr_symbol ()); 
               break;
          case money_base::sign   :
               if (sign.size () <= 1)
                  str.append (sign); 
               else { str.append (1, sign[0]); sign_ = true; }
               break;
          case money_base::space  :
               str.append (1, cfill);
               break;
          case money_base::value  :
               str.append (money_fmt (io, cfill, punct, units));
               break;
          case money_base::none   :
               str.append (1, cfill);
               break;
          default   : break;
      }
   }
   if (sign_) str.append (sign.data()+1);
 
   size_t cnt = 0;
   while (cnt < str.size ())
   {
      *iter++ = str[cnt];
      cnt++;
   }
   return iter;
}

template <class charT, bool Intl, class OutputIterator>
inline
money_put<charT, Intl, OutputIterator>::iter_type
money_put<charT, Intl, OutputIterator>::
do_put (iter_type iter, ios_base& io, char_type cfill,
        const string_type& str) const
{
    // 
    // The string str consists of a sequence of digits with an
    // optional sign (postive or negative) in the beginning.
    // All characters before [sign and the immediately
    // following digits] are ignored provided sign is there
    // and sign is non-null 
    //
    // Digits are extracted from str as far as possible.
    // Extraction stops when a non-digit is encountered in str
    //
    const locale& loc                    = io.getloc ();
    const moneypunct<charT, Intl>& punct = use_facet (loc,
                                           (moneypunct<charT, Intl>*)0);
  
    string_type sign        =  punct.negative_sign ();
    bool        isNeg       =  false;
    size_t      pos         =  0;
    long double      value  =  0.0L;
  
    if (sign.size() && ((pos = str.find (sign)) != string_type::npos))
    {
       isNeg = true;
    }
    if (!isNeg)
    {
       sign = punct.positive_sign();
       if (sign.size()) pos = str.find (sign);
    }
    if (pos == string_type::npos) pos = 0;
  
    while ((pos < str.size()) && is_digit (str[pos], loc))
    {
       value = (value*10) + __numeric_digits<charT>::value (str[pos], 10);
       ++pos;
    }
  
    if (isNeg) value = -value;
  
    return do_put (iter, io, cfill, value);
}

template <class charT, bool Intl, class OutputIterator>
inline
money_put<charT, Intl, OutputIterator>::string_type
money_put<charT, Intl, OutputIterator>::
money_fmt (ios_base& io, char_type cfill,
           const moneypunct<charT, Intl>& punct, long double units)
{
    charT fmt [16];
    charT buf [200];

    char_type              dec_pt    = punct.decimal_point ();
    char_type              thou_sep  = punct.thousands_sep ();

    if (!cfill)
        cfill = '\0';

    int tmp = punct.frac_digits ();
    while (tmp--)
       units /= 10.0L;

    // 
    // No padding and width considered
    //
    int                prec_sav  = io.precision (punct.frac_digits ());
    ios_base::fmtflags flags_sav = io.flags (ios_base::null);

    io.setf (ios_base::fixed | ios_base::dec);

    __msipl_fmt (io, fmt, 4);
    __msipl_sprintf (buf, sizeof(buf)/sizeof(charT), fmt, units);

    io.precision (prec_sav);
    io.flags (flags_sav);

    string_type str = __msipl_insert_thsep (string_type(buf),
                      punct.grouping (), thou_sep, dec_pt);

    return str;
}

//
// TIME CATEGORY
//
class time_base {
public :
    enum dateorder { no_order, dmy, mdy, ymd, ydm };

    enum t_conv_spec { a, A, b, B, c, d, H, I, j, m, M, p,
                       S, U, w, W, x, X, y, Y, END };
};

//
// this class is not specified in the draft : written for
// implementation purposes only
// 
// need to write specialization for wchar_t
//
template <class charT>
class timepunct : public time_base {

public :

    static const int t_conv_spec_width[time_base::END+1];

    //
    // typedefs
    //
    typedef charT                                           char_type;
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >                 string_type;

    explicit timepunct (const char_type* loc_name = "");

    virtual
    string_type
    get_week_day (const locale& loc, charT fmt, int wday) const
    {
         return (is_upper (fmt, loc) ? week_days[wday+7] 
                                     : week_days[wday]);
    }

    virtual
    string_type
    get_month_name (const locale& loc, char fmt, int mnth) const
    {
         return (is_upper (fmt, loc) ? mnth_name[mnth+12]
                                     : mnth_name[mnth]);
    }

    virtual
    string_type
    get_ampm_string (int hrs) const
    { return (12 - hrs > 0) ? am_string : pm_string; }

    //
    // strftime like function
    //
    virtual
    string_type
    print_format (const locale& loc, char fmt, const tm* tm_) const;

    virtual
    string_type*
    get_week_day_list () const { return (string_type*)week_days; }

    virtual
    string_type*
    get_month_name_list () const { return (string_type*)mnth_name; }

    virtual
    int
    get_spec_conv_width (charT spec)
    {
       switch (spec)
       {
          case 'a' :  return t_conv_spec_width [time_base::a];
          case 'A' :  return t_conv_spec_width [time_base::A];
          case 'b' :  return t_conv_spec_width [time_base::b];
          case 'B' :  return t_conv_spec_width [time_base::B];
          case 'c' :  return t_conv_spec_width [time_base::c];
          case 'd' :  return t_conv_spec_width [time_base::d];
          case 'H' :  return t_conv_spec_width [time_base::H];
          case 'I' :  return t_conv_spec_width [time_base::I];
          case 'j' :  return t_conv_spec_width [time_base::j];
          case 'm' :  return t_conv_spec_width [time_base::m];
          case 'M' :  return t_conv_spec_width [time_base::M];
          case 'p' :  return t_conv_spec_width [time_base::p];
          case 'S' :  return t_conv_spec_width [time_base::S];
          case 'U' :  return t_conv_spec_width [time_base::U];
          case 'w' :  return t_conv_spec_width [time_base::w];
          case 'W' :  return t_conv_spec_width [time_base::W];
          case 'x' :  return t_conv_spec_width [time_base::x];
          case 'X' :  return t_conv_spec_width [time_base::X];
          case 'y' :  return t_conv_spec_width [time_base::y];
          case 'Y' :  return t_conv_spec_width [time_base::Y];
          default  :  return t_conv_spec_width [time_base::END];
       }
    }
    //
    // eqvt to "%c" strftime
    //
    virtual
    string_type
    get_date_time_format () const
    { return string_type ("%a %b %d %H:%M:%S %Y"); }

    //
    // eqvt to "%x" strftime
    //
    virtual
    string_type
    get_date_format () const
    { return string_type ("%m/%d/%y"); }

    //
    // eqvt to "%X" strftime
    //
    virtual
    string_type
    get_time_format () const
    { return string_type ("%H:%M:%S"); }

protected :

    virtual
    string_type
    __print_format (char fmt, const tm* tm_) const;

    string_type loc_name;

    string_type week_days [14];     // week days names
    string_type mnth_name [24];     // month names

    string_type am_string;              // am_string
    string_type pm_string;              // pm_string

};

template <class charT>
const int
timepunct<charT>::t_conv_spec_width[time_base::END+1] = { 3, -1, 3,
   -1, -1, 2, 2, 2, 3, 2, 2, -1, 2, 2, 1, 2, -1, -1, 2, 4, 0 };
// Z='Z' ; Time Zones not supported yet

#define MAXBUFF 512

template <class charT>
inline
timepunct<charT>::timepunct (const char_type* loc_name_)
: loc_name (loc_name_)
{
    const char* old_loc_name = setlocale (LC_ALL, 0);

    if (setlocale (LC_TIME, loc_name_) != 0)
    {
       tm tmb;
   
       tmb.tm_sec    = 30;   tmb.tm_min    = 30;   tmb.tm_hour   = 10;
       tmb.tm_mday   =  1;   tmb.tm_mon    =  8;   tmb.tm_year   = 96;
       tmb.tm_wday   =  0;   tmb.tm_yday   = -1;   tmb.tm_isdst  = -1;
   
       char_type fmt[3];
       char_type buff[MAXBUFF];
       unsigned int MB = MAXBUFF;
       fmt[0] = '%'; fmt[1] = 'c' ; fmt[2] = 0;
   
       // get the week days names
       for (int days = 0; days < 7; ++days)
       {
           tmb.tm_mday = days+1;
           tmb.tm_wday = days; // just to be sure
           fmt[1] = 'a';
           __msipl_strftime (buff, MB, fmt, &tmb);
           week_days [days] = string_type (buff);
           fmt[1] = 'A';
           __msipl_strftime (buff, MB, fmt, &tmb);
           week_days [days+7] = string_type (buff);
       }
   
       // get the month names
       for (int mths = 0; mths < 12; ++mths)
       {
           tmb.tm_mon = mths;
           fmt[1] = 'b';
           __msipl_strftime (buff, MB, fmt, &tmb);
           mnth_name [mths] = string_type (buff);
           fmt[1] = 'B';
           __msipl_strftime (buff, MB, fmt, &tmb);
           mnth_name [mths+12] = string_type (buff);
       }
   
       // get the am / pm strings
       fmt[1] = 'p';
       __msipl_strftime (buff, MB, fmt, &tmb);
       am_string = string_type (buff);
   
       tmb.tm_hour = 22;
       fmt[1] = 'p';
       __msipl_strftime (buff, MB, fmt, &tmb);
       pm_string = string_type (buff);
    }
    else
    {
#ifdef MSIPL_EXCEPT
       throw runtime_error ("Invalid locale name");
#else
       fprintf (stderr, "Invalid locale name\n");
       exit (1);
#endif
    }
    setlocale (LC_ALL, old_loc_name);
}

template <class charT>
inline
timepunct<charT>::string_type
timepunct<charT>::
__print_format (char fmt, const tm* tm_) const
{
    char_type fmt_str[10];
    fmt_str[0] = '%';

    char_type buff[MAXBUFF];
    unsigned int MB = MAXBUFF;

    fmt_str[1] = '.'; fmt_str[2] = '2';
    fmt_str[3] = 'd'; fmt_str[4] = 0;

    switch (fmt)
    {
         case 'd' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_mday);
            break;
         case 'H' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_hour);
            break;
         case 'I' :
         {
            int hr;    // [00, 23] to [01, 12]
            if (tm_->tm_hour == 0) hr = 12;
            else if (tm_->tm_hour > 12) hr = tm_->tm_hour - 12;
            __msipl_sprintf (buff, MB, fmt_str, hr);
            break;
         }
         case 'm' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_mon+1);
            break;
         case 'M' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_min);
            break;
         case 'S' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_sec);
            break;
         case 'U' :
         {
            int U_dat = (tm_->tm_yday - tm_->tm_wday + 7)/7;
            __msipl_sprintf (buff, MB, fmt_str, U_dat);
            break;
         }
         case 'W' :
         {
            int to_arr [7] = { 6, 0, 1, 2, 3, 4, 5 };
            int W_dat = (tm_->tm_yday - to_arr[tm_->tm_wday] + 7)/7;
            __msipl_sprintf (buff, MB, fmt_str, W_dat);
            break;
         }
         case 'y' :
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_year);
            break;
         case 'w' :
            fmt_str[2] = '1';
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_wday);
            break;
         case 'Y' :
            fmt_str[2] = '4';
            __msipl_sprintf (buff, MB, fmt_str, 1900+tm_->tm_year);
            break;
         case 'j' :
            fmt_str[2] = '3';
            __msipl_sprintf (buff, MB, fmt_str, tm_->tm_yday+1);
            break;
    }
    return string_type (buff);
}

template <class charT>
inline
timepunct<charT>::string_type
timepunct<charT>::
print_format (const locale& loc, char fmt, const tm* tm_) const
{
     string_type ret;

     switch (fmt)
     {
         case 'a' : case 'A' :
            if (tm_->tm_wday >= 0 && tm_->tm_wday < 6)
               ret.append (get_week_day (loc, fmt, tm_->tm_wday));
            break;
         case 'b' : case 'B' :
            if (tm_->tm_mon >= 0 && tm_->tm_mon < 12)
               ret.append (get_month_name (loc, fmt, tm_->tm_mon));
            break;
         case 'p' :
            if (tm_->tm_hour >= 0 && tm_->tm_hour < 24)
               ret.append (get_ampm_string (tm_->tm_hour));
            break;
         default :
            // 'd', 'H', 'I', 'j', 'm', 'M', 'S', 'U', 'w', 'W', 'y', 'Y'
            if (fmt != '%') ret.append (__print_format (fmt, tm_));
            else ret.append (string_type (1, '%'));
            break;
     }
     return ret;
}

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class InputIterator =
          istreambuf_iterator<charT> >
#else
template <class charT, class InputIterator>
#endif
class time_get : public locale::facet, public time_base {

public :

    //
    // typedefs
    //
    typedef charT                                            char_type;
    typedef InputIterator                                    iter_type;
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;
    typedef ios_base::iostate                                io_state;

    explicit
    time_get (size_t refs = 0)
    : locale::facet (refs) { }

    dateorder
    date_order () const
    { return do_date_order (); }

    iter_type
    get_time (iter_type s, iter_type end, ios_base& f, io_state& state,
              tm* t) const
    { return do_get_time (s, end, f, state, t); }

    iter_type
    get_date (iter_type s, iter_type end, ios_base& f, io_state& state,
              tm* t) const
    { return do_get_date (s, end, f, state, t); }
          
    iter_type
    get_weekday (iter_type s, iter_type end, ios_base& f, io_state& state,
                 tm* t) const
    { return do_get_weekday (s, end, f, state, t); }
          
    iter_type
    get_monthname (iter_type s, iter_type end, ios_base& f,
                   io_state& state, tm* t) const
    { return do_get_monthname (s, end, f, state, t); }
          
    iter_type
    get_year (iter_type s, iter_type end, ios_base& f, io_state& state,
              tm* t) const
    { return do_get_year (s, end, f, state, t); }

    static locale::id id_;

    virtual 
    locale::id&
    get_id () { id_.init (); return id_; }

protected :

    ~time_get () { }

    explicit
    time_get (const char* name, size_t refs = 0)
    : locale::facet (refs), name_ (name) { }

    virtual
    dateorder
    do_date_order () const { return time_base::dmy; }

    virtual
    iter_type
    do_get_time (iter_type s, iter_type end, ios_base& f, io_state& state,
                 tm* t) const;

    virtual
    iter_type
    do_get_date (iter_type s, iter_type end, ios_base& f, io_state& state,
                 tm* t) const;
          
    virtual
    iter_type
    do_get_weekday (iter_type s, iter_type end, ios_base& f,
                    io_state& state, tm* t) const;
          
    virtual
    iter_type
    do_get_monthname (iter_type s, iter_type end, ios_base& f,
                      io_state& state, tm* t) const;
          
    virtual
    iter_type
    do_get_year (iter_type s, iter_type end, ios_base& f, io_state& state,
                 tm* t) const;

    virtual
    iter_type
    which_matches (iter_type s, iter_type end, ios_base& f,
                   io_state& state, const string_type*, int, int&) const;

    virtual
    iter_type
    get_integral_data (iter_type s, iter_type end, ios_base& f,
                       io_state& state, charT fmt, int&) const;

    virtual
    iter_type
    do_time_scanf (iter_type s, iter_type end, ios_base& f, 
                   io_state& state, tm* t, const char_type* pattern,
                   const char_type* pat_end) const;

    string_type name_;

}; /* end class time_get */


#ifdef MSIPL_DEF_TEMPARG
template <class charT, class InputIterator =
          istreambuf_iterator<charT> >
#else
template <class charT, class InputIterator>
#endif
class time_get_byname : public time_get<charT, InputIterator> {

public:
    explicit
    time_get_byname (const char* name, size_t refs = 0)
    : time_get (name, refs) { }

protected:

    ~time_get_byname ();

    // all virtuals go here
};

template <class charT, class InputIterator>
locale::id time_get<charT, InputIterator>::id_;

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_get_time (iter_type begin, iter_type end, ios_base& io, 
             io_state& state, tm* t) const
{
     timepunct<charT> tpunct;
     string_type time_list      = tpunct.get_time_format ();
     return do_time_scanf (begin, end, io, state, t,
       time_list.c_str (), time_list.c_str () + time_list.size ());
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_time_scanf (iter_type begin, iter_type end, ios_base& io, 
               io_state& state, tm* t, const char_type* pattern,
               const char_type* pat_end) const
{
     timepunct<charT> tpunct;

     const locale& loc          = io.getloc ();
     const ::ctype<charT>& ctype_ = use_facet (loc, (::ctype<charT>*)0);

     while (pattern != pat_end) // && io.good ()
     {
       if (!string_type::traits_type::eq (*pattern, '%'))
       { 
         if (!string_type::traits_type::eq (*begin, *pattern))
         { state |= ios_base::failbit; return begin; }
      
         else { begin++; pattern++; }
       } else
       {
         char_type c;
         switch (c = *++pattern)
         {
           // Assuming the appropriate versions will be given
           // No checking is done to check that!!
           case 'a' : case 'A' :
              begin = get_weekday (begin, end, io, state, t); break;
           case 'b' : case 'B' :
              begin = get_monthname (begin, end, io, state, t); break;
           case 'd' :
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_mday);
              if (t->tm_mday < 1 || t->tm_mday > 31)
                  state |= ios_base::failbit;
              break;
           case 'H' :
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_hour);
              if (t->tm_hour < 0 || t->tm_hour > 23)
                  state |= ios_base::failbit;
              break;
           case 'I' :
           {
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_hour);
              if (t->tm_hour < 1 || t->tm_hour > 12)
                  state |= ios_base::failbit;
              else t->tm_hour--;
              break;
           }
           case 'j' :
           {
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_yday);
              if (t->tm_yday < 0 || t->tm_yday > 365)
                  state |= ios_base::failbit;
              t->tm_yday++;
              break;
           }
           case 'm' :
           {
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_mon);
              if (t->tm_mon <= 0 || t->tm_mon > 12)
                  state |= ios_base::failbit;
              t->tm_mon--;
              break;
           }
           case 'M' :
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_min);
              if (t->tm_min < 0 || t->tm_min > 59)
                  state |= ios_base::failbit;
              break;
           case 'p' : case 'U' : case 'W' : //  YET TO BE DONE
               break;
           case 'S' :
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_sec);
              if (t->tm_sec < 0 || t->tm_sec > 62)
                  state |= ios_base::failbit;
              break;
           case 'w' :
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_wday);
              if (t->tm_wday < 0 || t->tm_wday > 6)
                  state |= ios_base::failbit;
              break;
           case 'y' : case 'Y' :
           {
              begin = get_integral_data (begin, end, io, state, c, 
                                         t->tm_year);
              if (t->tm_year > 1900) t->tm_year -= 1900;
              else if (t->tm_year < 0)
                  state |= ios_base::failbit;
              break;
           }
           default : state |= ios_base::failbit; break;
                    
         } /* end switch */
         pattern++;
       }
     } /* end while */
     return begin;
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_get_date (iter_type begin, iter_type end, ios_base& io, 
             io_state& state, tm* t) const
{
     timepunct<charT> tpunct;
     string_type date_list = tpunct.get_date_format ();
     const locale& loc            = io.getloc ();
     return do_time_scanf (begin, end, io, state, t,
                           date_list.c_str (),
                           date_list.c_str () + date_list.size ());
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_get_weekday (iter_type begin, iter_type end, ios_base& io, 
                io_state& state, tm* t) const
{
     timepunct<charT> tpunct;
     int wday = 0;
     iter_type ret = which_matches (begin, end, io, state,
            tpunct.get_week_day_list (), 14, wday);

     if (wday != -1)
        t->tm_wday = (wday > 6) ? wday - 6 : wday;
     else
        state |= ios_base::failbit;
 
     return ret;
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_get_monthname (iter_type begin, iter_type end, ios_base& io, 
                  io_state& state, tm* t) const
{
     timepunct<charT> tpunct;
     int mnth = 0;
     iter_type ret = which_matches (begin, end, io, state,
            tpunct.get_month_name_list (), 24, mnth);
     if (mnth != -1)
        t->tm_mon = (mnth > 11) ? mnth - 11 : mnth;
     else
        state |= ios_base::failbit;
 
     return ret;
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
get_integral_data (iter_type begin, iter_type end, ios_base& io, 
                   io_state& state, charT fmt, int& data) const
{
     data = 0;
     timepunct<charT> tpunct;
     int width = tpunct.get_spec_conv_width (fmt);
     if (width < 0) return begin;

     const locale& loc          = io.getloc ();
     const ::ctype<charT>& ctype_ = use_facet (loc, (::ctype<charT>*)0);

     if (io.flags () & ios_base::skipws)
     {
         while ((begin != end) && is_space (*begin, loc))
            ++begin;
     } else if (is_space (*begin, loc))
     {
         state |= ios_base::failbit;
         return begin;
     }
 
     while (begin != end && is_digit (*begin, loc) && width--)
     {
         data = data * 10 + (ctype_.narrow (*begin, 0) - '0');
         begin++;
     }

     if (!data) state |= ios_base::failbit;
                    
     return begin;
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
do_get_year (iter_type begin, iter_type end, ios_base& io, 
             io_state& state, tm* t) const
{
     int year = 0;
     const locale& loc            = io.getloc ();
     const ::ctype<charT>& ctype_ = use_facet (loc, (::ctype<charT>*)0);

     if (io.flags () & ios_base::skipws)
     {
         while ((begin != end) && is_space (*begin, loc))
            ++begin;
     } else if (is_space (*begin, loc))
     {
         state |= ios_base::failbit;
         return begin;
     }
 
     while (begin != end && is_digit (*begin, loc))
     {
         year = year * 10 + (ctype_.narrow (*begin, 0) - '0');
         begin++;
     }

     if (year && year < 100) t->tm_year = year;
     else if (year > 1900) t->tm_year = year - 1900;
     else state |= ios_base::failbit;
                    

     return begin;
}

template <class charT, class InputIterator>
inline
time_get<charT, InputIterator>::iter_type
time_get<charT, InputIterator>::
which_matches (iter_type begin, iter_type end, ios_base& io,
               io_state& state, const string_type* str_list,
               int list_size, int& matchPos) const
{
     int strPos    = 0;
     int startFrom = 0;
     string_type str;
     str.reserve (100);
     bool foundMatch = false;

     const locale& loc            = io.getloc ();

     if (io.flags () & ios_base::skipws)
     {
        while ((begin != end) && is_space (*begin, loc))
           ++begin;
     } else if (is_space (*begin, loc))
     {
        state |= ios_base::failbit;
        return begin;
     }

     while (begin != end && !foundMatch && startFrom < list_size)
     {
          if (strPos < str_list[startFrom].size () &&
              str_list[startFrom].compare (0, strPos,
                                           str, 0, strPos) == 0)
          {
             str.append (1, *begin);
             strPos++; begin++;
             if (str == str_list[startFrom])
                foundMatch = true;
          }
          else
             startFrom++;
     }

     matchPos = (foundMatch ?  startFrom : -1);
     return begin;
}


#ifdef MSIPL_DEF_TEMPARG
template <class charT, class OutputIterator =
          ostreambuf_iterator<charT> >
#else
template <class charT, class OutputIterator>
#endif
class time_put : public locale::facet {

public :

    //
    // typedefs
    //
    typedef charT                                            char_type;
    typedef OutputIterator                                   iter_type;
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >                  string_type;

    explicit time_put (size_t refs = 0)
    : locale::facet (refs) { }

    iter_type
    put (iter_type s, ios_base&, char_type cfill,
         const tm* tmb, const char_type* pattern,
         const char_type* pat_end) const;

    iter_type
    put (iter_type s, ios_base& io, char_type cfill,
         const tm* tmb, char format, char modifier = 0) const
    { return do_put (s, io, cfill, tmb, format, modifier); }

    static locale::id id_;

    virtual 
    locale::id&
    get_id () { id_.init (); return id_; }

protected :

    virtual
    iter_type
    do_put (iter_type s, ios_base&, char_type cfill,
            const tm* tmb, char format, char modifier = 0) const;
};
   
#ifdef MSIPL_DEF_TEMPARG
template <class charT, class OutputIterator =
          ostreambuf_iterator<charT> >
#else
template <class charT, class OutputIterator>
#endif
class time_put_byname : public time_put<charT, OutputIterator> {

public :

    explicit
    time_put_byname (const char* name, size_t refs = 0)
    : time_put<charT, OutputIterator> (name, refs) { }

protected :
    
    ~time_put_byname () { }

    // virtual
    // iter_type
    // do_put (iter_type s, ios_base& s, tm* t,
    //         char format, char modifier) const;

};

template <class charT, class OutputIterator>
locale::id time_put<charT, OutputIterator>::id_;

template <class charT, class OutputIterator>
inline
time_put<charT, OutputIterator>::iter_type
time_put<charT, OutputIterator>::
put (iter_type iter, ios_base& io, char_type cfill,
     const tm* t, const char_type* pattern,
     const char_type* pat_end) const
{
    const locale& loc          = io.getloc ();
    const ::ctype<charT>& ctype_ = use_facet (loc, (::ctype<charT>*)0);
    timepunct<charT> tpunct;

    const char_type* cur = pattern;

    while (cur != pat_end) //  && *cur
    {
       if (ctype_.narrow (*cur, 0) != '%')
           *iter++ = *cur++;
       else
       {
           char fmt = 0;
           if (pat_end != cur+1)
              fmt = ctype_.narrow (*++cur, 0);
           else
              return iter;
           if (fmt)
           {
              switch (fmt) 
              {
                case 'c' :
                {
                   string_type date_time_fmt = tpunct.get_date_time_format ();
                   const char_type* c_fmt_lst = date_time_fmt.c_str ();
                   iter = put (iter, io, cfill, t, c_fmt_lst,
                               c_fmt_lst+string_type::traits_type::
                               length (c_fmt_lst));
                   break;
                }
                case 'x' :
                {
                   string_type date_fmt = tpunct.get_date_format ();
                   const char_type* x_fmt_lst = date_fmt.c_str ();
                   iter = put (iter, io, cfill, t, x_fmt_lst,
                               x_fmt_lst + string_type::traits_type::
                               length (x_fmt_lst));
                   break;
                }
                case 'X' :
                {
                   string_type time_fmt = tpunct.get_time_format ();
                   const char_type* X_fmt_lst = time_fmt.c_str ();
                   iter = put (iter, io, cfill, t, X_fmt_lst,
                               X_fmt_lst + string_type::traits_type::
                               length (X_fmt_lst));
                   break;
                }
                default : iter = do_put (iter, io, cfill, t, fmt, 0); break;
              }
              cur++;
           }
        }
    } /* end while */
    return iter;
}

template <class charT, class OutputIterator>
inline
time_put<charT, OutputIterator>::iter_type
time_put<charT, OutputIterator>::
do_put (iter_type iter, ios_base& io, char_type cfill,
        const tm* t, char format, char modifier) const
{
    timepunct<charT> tpunct;

    if (io && modifier) // dont know how this is to be used ??
        modifier = '\0'; 

    switch (format) 
    {
      case 'c' :
      {
         string_type date_time_fmt = tpunct.get_date_time_format ();
         const char_type* c_fmt_lst = date_time_fmt.c_str ();
         iter = put (iter, io, cfill, t, c_fmt_lst,
                     c_fmt_lst + string_type::traits_type::
                     length (c_fmt_lst));
         break;
      }
      case 'x' :
      {
         string_type date_fmt = tpunct.get_date_format ();
         const char_type* x_fmt_lst = date_fmt.c_str ();
         iter = put (iter, io, cfill, t, x_fmt_lst,
                     x_fmt_lst + string_type::traits_type::
                     length (x_fmt_lst));
         break;
      }
      case 'X' :
      {
         string_type time_fmt = tpunct.get_time_format ();
         const char_type* X_fmt_lst = time_fmt.c_str ();
         iter = put (iter, io, cfill, t, X_fmt_lst,
                     X_fmt_lst + string_type::traits_type::
                     length (X_fmt_lst));
         break;
      }
      default :
         string_type str = tpunct.print_format (io.getloc (), format, t);
         size_t cnt = 0;
         while (cnt < str.size())
         {
            *iter++ = str[cnt];
            cnt++;
         }
    }
    return iter;
}

//
// MESSAGES CATEGORY
//
#ifdef MSIPL_NL_TYPES
class messages_base {
public :
    typedef nl_catd catalog;
};

template <class charT>
class messages : public locale::facet, public messages_base {
public :

    typedef charT                                           char_type;
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >                 string_type;

    explicit messages (size_t refs = 0) : locale::facet (refs) { }

    catalog
    open (const basic_string<char, char_traits<char>, allocator<char> >& fn,
          const locale& loc) const
    { return do_open (fn, loc); }

    string_type
    get (catalog c, int set, int msgid, const string_type& dfault) const;
    { return do_get (c, set, msgid, dfault); }

    void
    close (catalog c) const
    { return do_close (c); }

    static locale::id id_;

protected :

    ~messages ();

    virtual
    catalog
    do_open (const basic_string<char, char_traits<char>, allocator<char> >& fn,
             const locale& loc) const;

    virtual
    string_type
    do_get (catalog c, int set, int msgid,
            const string_type& dfault) const;
 
    virtual
    void
    do_close (catalog c) const;
};

template <class charT>
class messages_byname : public messages<charT> {
public :

    explicit messages_byname (const char*, size_t refs = 0);

protected :
   
    ~messages_byname ();
/*
    virtual
    catalog
    do_open (const basic_string<char, char_traits<char>, allocator<char> >&,
             const locale&) const;

    virtual
    string_type
    do_get (catalog, int set, int msgid, const string_type& dfault) const;

    virtual
    void
    do_close (catalog) const;
*/
};

template <class charT>
inline
messages<charT>::catalog
messages<charT>::
do_open (const basic_string<char, char_traits<char>, allocator<char> >& name,
         const locale& loc) const
{
     nl_catd cat = ::catopen (name.c_str (), 0);
     assert (cat != (nl_catd) -1);
     return cat;
}

template <class charT>
inline
messages<charT>::string_type
messages<charT>::
do_get (catalog cat, int set, int msgid, const string_type& dfault) const
{
    const charT* dflt = dfault.c_str ();
    const char* ret = ::catgets (cat, set, msgid, dflt);
    return string_type (ret);
}


template <class charT>
inline
void
messages<charT>::do_close (catalog cat) const
{
    int ret = ::catclose (cat);
    assert (ret != -1);
}

#endif /* MSIPL_NL_TYPES */

#ifdef MSIPL_MEMBER_TEMPLATE
template <class charT, class traits>
inline
bool
locale::operator() (const basic_string<charT, traits, allocator<charT> >& s1,
                    const basic_string<charT, traits, allocator<charT> >& s2) const
#else
inline
bool
locale::operator() (const string& s1, const string& s2) const
#endif
{
#ifdef MSIPL_USING_NAMESPACE
    const std::collate<char>& col = use_facet (*this,
                                              (std::collate<char>*)0);
#else
    const ::collate<char>& col = use_facet (*this, (::collate<char>*)0);
#endif

    return (col.compare (s1.data (), s1.data ()+ s1.size (),
            s2.data (), s2.data () + s2.size ()) < 0);
}

template <class charT, class Traits>
inline
basic_ostream<charT, Traits>&
operator<< (basic_ostream<charT, Traits>& os, const locale& loc)
{
    return os << loc.name () << endl;
}

template <class charT, class Traits>
inline
basic_istream<charT, Traits>&
operator>> (basic_istream<charT, Traits>& is, locale& loc)
{
    typedef basic_string<charT, char_traits<charT>,
                         allocator<charT> >          string_type;
    string_type str;

    is >> str;   // read the locale's name

    if (setlocale (LC_ALL, str.c_str()) != 0)
        loc = locale (str.c_str ());  // try to construct the locale
    else
        is.setstate (ios_base::failbit);

    return is;
}

#ifndef MSIPL_PARTIAL_TEMPL
null_template
struct iterator_trait <locale::facet *const *> {
    typedef ptrdiff_t                    distance_type;
    typedef bool                         value_type;
    typedef random_access_iterator_tag   iterator_category;
};
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_LOCALE_H */

//961113 bkoz line 12 added #include <typeinfo>	for bad_cast decl
//951113 bkoz line 373 add string literal to bad_cast throw
//961113 bkoz line 865, 4021, 4186, 4218, 4372 changed ctype to ::ctype
//961114 bkoz line 1581, 1575 changed collate to ::collate
//961204 bkoz line 2508, 2509 commented out printf's. . .
//961205 bkoz line 2168, added cfill; for strict compiler warnings
//961205 bkoz line 2289 lengthened line to remove compiler warnign (unwanted assignment)
//961210 bkoz added alignment wrapper
//961210 bkoz line 185 added to locale::id::id() to initialize id_ to zero. 2211205.c test
//961218 bkoz changed fill to cfill for namespace pollution bug
//970110 mm   long long support.
//970121 mm   allow a single 0 to be read in.
