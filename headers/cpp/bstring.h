/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_BSTRING_H
#define MSIPL_BSTRING_H

#include <mcompile.h>

#include MOD_C_INCLUDE(stdio)
#include MOD_C_INCLUDE(ctype)
#include MOD_C_INCLUDE(string)

#ifdef MSIPL_WCHART
#include MOD_C_INCLUDE(wchar)
#include MOD_C_INCLUDE(wctype)
#endif

#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(mmemory) 	//961216 ah

#include MOD_INCLUDE(mutex)

#include <algorithm.h>			//961111 bkoz for swap

#ifdef DebugNew_H       		//970401 bkoz
	#undef new
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

template <class charT>
class char_traits { };	// 961217 KO

typedef  long    streamoff;
typedef  size_t  streamsize;

#ifdef MSIPL_WCHART
  // typedef mbstate_t  fstate_t;
  // CHECK
  typedef int        fstate_t;
#else
  typedef int        fstate_t;
#endif
//
// Implementation defined conversion state
// struct which is for file i/o.
//

#ifdef MSIPL_WCHART
typedef  long    wstreamoff;
#endif

class streampos {
public:

    streampos (streamoff off_arg = 0, fstate_t fst_arg = 0)
    : off (off_arg), fst (fst_arg), fpt(0) 
    { 
    }

    streampos (const streampos& rhs)
    : off (rhs.off), fst (rhs.fst), fpt (rhs.fpt) 
    { 
    }

    streamoff offset () const { return off; }

    fstate_t state () const { return fst; }

    streampos&
    operator= (const streampos& rhs)
    {
       if (this != &rhs)
       {
          off = rhs.off;
          fst = rhs.fst;
          fpt = rhs.fpt;
       }
       return *this;
    }

    streamoff
    operator- (const streampos& rhs) const
    {
       return ((off == -1 || rhs.off == -1) ? -1 : 
                off - rhs.off);
    }

    streampos&
    operator+= (streamoff off_arg)
    {
        off += off_arg;
        return *this;
    }

    streampos&
    operator-= (streamoff off_arg)
    {
        off -= off_arg;
        return *this;
    }

    streampos
    operator+ (streamoff off_arg) const
    {
       streampos  tmp (*this);
       return (tmp += off_arg);
    }    

    streampos
    operator- (streamoff off_arg) const
    {
       streampos  tmp (*this);
       return (tmp -= off_arg);
    }

    bool
    operator== (const streampos& rhs) const
    {
        if ((off == -1) || (rhs.off == -1)) 
            return (off == rhs.off);
        else
            return ((off == rhs.off) && (fpt == rhs.fpt) &&
                   (fst  == rhs.fst));
    }

    bool
    operator!= (const streampos& rhs) const
    {
       return (! (*this == rhs));
    }

private:

    streamoff    off;
    fpos_t       fpt;
    fstate_t     fst;

};

#ifdef MSIPL_WCHART
class  wstreampos {
public:
    wstreampos (const wstreampos& pos_arg, mbstate_t fst_arg)
    : off (pos_arg.off), fst (fst_arg) { }

    wstreampos (wstreamoff off_arg, mbstate_t fst_arg)
    : off (off_arg), fst (fst_arg) { }

    wstreampos (wstreamoff off_arg = 0)
    : off (off_arg) { }

    wstreampos (const wstreampos& rhs)
    : off (rhs.off), fst (rhs.fst), fpt (rhs.fpt) { }

    wstreamoff offset () const { return off; }

    mbstate_t state () const
    {
        return fst;
    }

    wstreampos&
    operator= (wstreampos& rhs)
    {
       if (this != &rhs)
       {
          off = rhs.off;
          fst = rhs.fst;
          fpt = rhs.fpt;
       }
       return *this;
    }

    wstreamoff   
    operator- (wstreampos& rhs) const
    {
       return ((off == -1 || rhs.off == -1) ? -1 :
                off - rhs.off);
    }

    wstreampos&  
    operator+= (wstreamoff off_arg)
    {
        off += off_arg;
        return *this;
    }
 
    wstreampos&  
    operator-= (wstreamoff off_arg)
    {
        off -= off_arg;
        return *this;
    }
 
    wstreampos   
    operator+ (wstreamoff off_arg) const
    {
       wstreampos  tmp (*this);
       return (tmp += off_arg);
    }

    wstreampos   
    operator- (wstreamoff off_arg) const
    {
       wstreampos  tmp (*this);
       return (tmp -= off_arg);
    }
 
    bool         
    operator== (const wstreampos& rhs) const
    {
        if ((off == -1) || (rhs.off == -1))
            return (off == rhs.off);
        else
            return ((off == rhs.off) && (fpt == rhs.fpt) &&
                   (fst  == rhs.fst));
    }
 
    bool         
    operator!= (const wstreampos& rhs) const
    {
       return (! (*this == rhs));
    }
 
private:
 
     wstreamoff   off;      // absolute position within the sequence
     fpos_t       fpt;
     mbstate_t    fst;      // conversion state

};
#endif
         
null_template
class char_traits<char> {	// 961217 KO
public:

    typedef char         char_type;
    typedef int          int_type;
    typedef streampos    pos_type;
    typedef streamoff    off_type;
    typedef fstate_t     state_type;

    // constraint member functions
    
    static void
    assign (char_type& c1, const char_type& c2) { c1 = c2; }

    static bool
    eq (const char_type& c1, const char_type& c2) { return (c1 == c2); }

    static bool
    lt (const char_type& c1, const char_type& c2) { return (c1 < c2); }

    //
    // speed-up functions
    //
    inline
    static int
    compare (const char_type* s1, const char_type* s2, size_t n) 
    {
#ifdef MSIPL_USING_NAMESPACE 
       // return std::memcmp (s1, s2, n);
        return ::memcmp (s1, s2, n);
#else
        return ::memcmp (s1, s2, n);
#endif
    }
    
	static size_t
	length (const char_type* s) 
    {
#ifdef MSIPL_USING_NAMESPACE 
        // return std::strlen (s);
        return ::strlen (s);
#else
        return ::strlen (s);
#endif
    }
    
	static char_type*
	copy (char_type* s1, const char_type* s2, size_t n) 
    {
        // type cast required as memcpy returns void*
#ifdef MSIPL_USING_NAMESPACE
        // return (char_type*)std::memcpy (s1, s2, n);
        return (char_type*)::memcpy (s1, s2, n);
#else
        return (char_type*)::memcpy (s1, s2, n);
#endif
    }
    
	static const char_type*
	find (const char_type* s, int n, const char_type& a)
    {
#ifdef MSIPL_USING_NAMESPACE
        // return (const char_type*)std::memchr (s, a, n);
        return (const char_type*)::memchr (s, a, n);
#else
         return (const char_type*)::memchr (s, a, n);
#endif
    }
    
	static char_type*
	move (char_type* s1, const char_type* s2, size_t n)
    {
#ifndef MSIPL_EDG232
#ifdef MSIPL_USING_NAMESPACE
        return (char_type*)std::memmove(s1, s2, n);
#else
        return (char_type*)::memmove(s1, s2, n);
#endif
#else
        char_type* s = s1;
        char_type* tempstr = new char_type[n];
        copy (tempstr, s2, n);
        for (size_t i = 0; i < n; ++i, ++s1)
            assign (*s1, tempstr[i]);
        delete [] tempstr;
        return s;
#endif
    }
    
	static char_type*
	assign (char_type* s, size_t n, char_type a)
 	{
	#ifdef MSIPL_USING_NAMESPACE
	        // return (char_type*)std::memset (s, a, n);
	        return (char_type*)::memset (s, a, n);
	#else
	        return (char_type*)::memset (s, a, n);
	#endif
	}   
 
    static int_type 
    not_eof (const int_type& c)
    {
        if (!eq (c, eof ()))
            return c;
        return ~c;
    }
    
    static char_type
    to_char_type (const int_type& c)
    {
        if (eq_int_type (c, to_int_type (c)))   
            return c;
        return char_type(0);
    }
    
    static int_type
    to_int_type (const char_type& c)
    {
#ifdef MSIPL_UCHAR
        return ((c+1) & 0xFF) - 1;
#else
        return (unsigned char)c;
#endif
    }
    
    static bool
    eq_int_type (const int_type& c1, const int_type& c2)
    {
        return (c1 == c2);
    }
        
    static state_type
	get_state (streampos pos)
	{
	    return pos.state();
	}

	static pos_type
	get_pos (pos_type pos, state_type state)
	{
	    return pos_type(pos.offset (), state);
	}

    static int_type
    eof ()
    {
        return EOF;
    }
    
    static char_type
    eos ()
    {
        return 0;
    }
    
    static char_type
    newline ()
    {
        return '\n';
    }
};


#ifdef MSIPL_WCHART
 
null_template
class char_traits<wchar_t> {	// 961217 KO
public:

    typedef wchar_t         char_type;
    typedef wint_t          int_type;
    typedef wstreampos      pos_type;
    typedef wstreamoff      off_type;
    typedef mbstate_t       state_type;

    // constraint member functions
    
    static void
    assign (char_type& c1, const char_type& c2) { c1 = c2; }

    static bool
    eq (const char_type& c1, const char_type& c2) { return (c1 == c2); }

    static bool
    lt (const char_type& c1, const char_type& c2) { return (c1 < c2); }

    //
    // speed-up functions
    //
    static int
    compare (const char_type* s1, const char_type* s2, size_t n) 
    {
#ifdef MSIPL_USING_NAMESPACE
        // return std::wmemcmp (s1, s2, n);
        return ::wmemcmp (s1, s2, n);
#else
        return ::wmemcmp (s1, s2, n);
#endif
    }
    static size_t
    length (const char_type* s) 
    {
#ifdef MSIPL_USING_NAMESPACE
        // return std::wcslen (s);
        return ::wcslen (s);
#else
        return ::wcslen (s);
#endif
    }
    static char_type*
    copy (char_type* s1, const char_type* s2, size_t n) 
    {
        // type cast required as memcpy returns void*
#ifdef MSIPL_USING_NAMESPACE
        // return (char_type*)std::wmemcpy (s1, s2, n);
        return (char_type*)::wmemcpy (s1, s2, n);
#else
        return (char_type*)::wmemcpy (s1, s2, n);
#endif
    }
    static const char_type*
    find (const char_type* s, int n, const char_type& a)
    {
#ifdef MSIPL_USING_NAMESPACE
        // return (const char_type*)std::wmemchr (s, a, n);
        return (const char_type*)::wmemchr (s, a, n);
#else
        return (const char_type*)::wmemchr (s, a, n);
#endif
    }
    static char_type*
    move (char_type* s1, const char_type* s2, size_t n)
    {
#ifndef MSIPL_EDG232
#ifdef MSIPL_USING_NAMESPACE
        return (char_type*)std::wmemmove(s1, s2, n);
#else
        return (char_type*)::wmemmove(s1, s2, n);
#endif
#else
        char_type* s = s1;
        char_type* tempstr = new char_type[n];
        copy (tempstr, s2, n);
        for (size_t i = 0; i < n; ++i, ++s1)
            assign (*s1, tempstr[i]);
        delete [] tempstr;
        return s;
#endif
    }
    static char_type*
    assign (char_type* s, size_t n, char_type a)
    {
#ifdef MSIPL_USING_NAMESPACE
        // return (char_type*)std::wmemset (s, a, n);
        return (char_type*)::wmemset (s, a, n);
#else
        return (char_type*)::wmemset (s, a, n);
#endif
    }
    static int_type 
    not_eof (const int_type& c)
    {
        if (!eq (c, eof ()))
            return c;
        return ~c;
    }
    static char_type
    to_char_type (const int_type& c)
    {
        if (eq_int_type (c, to_int_type (c)))   
            return c;
        return char_type(0);
    }
    static int_type
    to_int_type (const char_type& c)
    {
        return (int_type)c;
    }
    static bool
    eq_int_type (const int_type& c1, const int_type& c2)
    {
        return (c1 == c2);
    }
    static state_type
    get_state (pos_type pos) 
    {
        return pos.state ();
    }
    static pos_type
    get_pos (pos_type pos, state_type state) 
    {
        return pos_type (pos.offset (), state);
    }
    static int_type
    eof ()
    {
        return WEOF;
    }
    static char_type
    eos ()
    {
        return 0;
    }
    static char_type
    newline ()
    {
        return L'\n';
    }
};

#endif /* MSIPL_WCHART */

template <class charT, class traits, class Allocator>
class basic_string;

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT>,
          class Allocator = allocator<charT> >
#else
template <class charT, class traits, class Allocator>
#endif
class basic_string_ref {
public:
   typedef  charT                           char_type;
   typedef  Allocator                       allocator_type;

   //
   // friend class declaration
   //
   friend class basic_string<charT, traits, Allocator>;

private:

   //
   // typedef declaration
   //
   typedef  traits                                   traits_type;
   typedef  typename traits::char_type               value_type;
   typedef  typename allocator_type::size_type       size_type;
   typedef  typename allocator_type::difference_type difference_type;
   typedef  typename allocator_type::reference       reference;
   typedef  typename allocator_type::const_reference const_reference;
   typedef  typename allocator_type::pointer         pointer;
   typedef  typename allocator_type::const_pointer   const_pointer;
   typedef           pointer                         iterator;
   typedef           const_pointer                   const_iterator;

   //
   // private data members
   //
   allocator_type               string_allocator;
   pointer                      start;
   pointer                      finish;
   pointer                      end_of_storage;
  
#ifdef MSIPL_MULTITHREAD
   mutex_arith<size_t, mutex>   count;   // reference count
#else
   size_t                       count;   // reference count
#endif
  
   //
   // private constructors and destructors
   //
    basic_string_ref (const Allocator& = Allocator ()) ;
  
    basic_string_ref (const basic_string<charT, traits, Allocator>& str,
                            size_type pos , size_type rlen,
                            const Allocator& = Allocator ());
  
    basic_string_ref (const charT* s, size_type n,
                            const Allocator& = Allocator ()) ;
 
    basic_string_ref (const charT* s, const Allocator& = Allocator ());

#ifdef MSIPL_MEMBER_TEMPLATE
   template <class InputIterator>
   
   basic_string_ref (InputIterator begin, InputIterator end,
                     const Allocator& = Allocator ());
#else
    basic_string_ref (iterator begin, iterator end, 
                            const Allocator& = Allocator ()) ;

    basic_string_ref (const_iterator begin, const_iterator end,
                            const Allocator& = Allocator ()) ;
#endif

    basic_string_ref (size_type rep, charT c,
                            const Allocator& = Allocator ()) ;


    ~basic_string_ref () ;

   inline 
   size_type
   size () const { return size_type (finish - start); }

   inline 
   size_type
   capacity () const { return size_type (end_of_storage - start); }

   const allocator_type& 
   get_allocator () const  { return string_allocator; }

   inline
   void
   add_count () { ++count; }

   inline
   bool
   rem_count () { return (--count); } 

   void
   cleanup () ;

   inline
   charT eos () { return traits_type::eos (); }

   static pointer
   uninitialized_copy (const charT* first, const charT* last, 
                       pointer result)
   {
#ifdef MSIPL_USING_NAMESPACE
       return std::uninitialized_copy (first, last, result);
#else
       return ::uninitialized_copy (first, last, result);
#endif
   }

   static void
   uninitialized_fill_n (pointer first, size_type n, charT c)
   {
#ifdef MSIPL_USING_NAMESPACE
       std::uninitialized_fill_n (first, n, c);
#else
       ::uninitialized_fill_n (first, n, c);
#endif
   }

   static pointer
   copy (const charT* first, const charT* last, pointer result)
   {
       while (first != last) traits_type::assign (*result++, *first++);
       return result;
   }

   static pointer
   copy_backward (const charT* first, const charT* last, pointer result)
   {
       while (first != last) traits_type::assign (*--result, *--last);
       return result;
   }

   static void
   fill_n (pointer first, size_type n, charT c)
   {
       while (n-- > 0) traits_type::assign (*first++, c);
   }

   static void
   throwlength () ;

   static void
   throwrange () ;

   friend 
   void
   destroy (basic_string_ref* ref);

   //
   // For efficient implementation of operator+
   //
   basic_string_ref (const charT* s, size_type rlen, size_type rres, const Allocator& = Allocator ()) ;
 
};



#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT>,
          class Allocator = allocator<charT> >
#else
template <class charT, class traits, class Allocator>
#endif
class basic_string {

public:

   //
   // typedef declarations
   //
   typedef  charT                                         char_type;
   typedef  traits                                        traits_type;
   typedef  typename traits::char_type                    value_type;
   typedef  Allocator                                     allocator_type;
   typedef  typename allocator_type::size_type            size_type;
   typedef  typename allocator_type::difference_type      difference_type;
   typedef  typename allocator_type::reference            reference;
   typedef  typename allocator_type::const_reference      const_reference;
   typedef  typename allocator_type::pointer              pointer;
   typedef  typename allocator_type::const_pointer        const_pointer;
   typedef  pointer                                       iterator;
   typedef  const_pointer                                 const_iterator;
   typedef  reverse_iterator<const_iterator, value_type, 
            const_reference, const_pointer,
            difference_type>                       const_reverse_iterator;
   typedef  reverse_iterator<iterator, value_type, 
            reference, pointer, difference_type>         reverse_iterator;

   typedef  basic_string_ref<charT, traits, Allocator>   string_reference;

#ifdef MSIPL_MEMBER_TEMPLATE
   typedef  typename Allocator::rebind<string_reference>::other 
                                                       reference_alloc_type;
#else
   typedef           DefAllocator<string_reference>    reference_alloc_type;
#endif

   typedef  typename reference_alloc_type::pointer   reference_pointer;
   typedef  typename reference_alloc_type::size_type reference_size_type;

	//
	//moved data members
	//
	static const size_type         npos;
	
    //
    // construct/copy/destroy
    //
    explicit
    basic_string (const Allocator& = Allocator()) ;

    basic_string (const basic_string& str, size_type pos = 0, size_type n = npos) ;

    basic_string (const charT* s, size_type n, const Allocator& = Allocator()) ;

    basic_string (const charT* s, const Allocator& = Allocator()) ;

    basic_string (size_type n, charT c, const Allocator& = Allocator()) ;

#ifdef MSIPL_MEMBER_TEMPLATE

    template <class InputIterator>
    basic_string (InputIterator begin, InputIterator end, const Allocator& = Allocator()) ;
#else

    basic_string (iterator begin, iterator end, const Allocator& = Allocator()) ;

    basic_string (const_iterator begin, const_iterator end, const Allocator& = Allocator()) ;
#endif

    ~basic_string () ;

    basic_string&
    operator= (const basic_string& str) ;

    basic_string&
    operator= (const charT* s) ;

    basic_string&
    operator= (charT c) ;

    //
    // iterators
    //
    inline
    iterator 
    begin () 
    { 
        READ_LOCK(_mutex);
        return string_pointer->start;
    }

    inline
    const_iterator
    begin () const 
    { 
        READ_LOCK(_mutex);
        return string_pointer->start;
    }

    inline
    iterator
    end () 
    { 
        READ_LOCK(_mutex);
        return string_pointer->finish;
    }

    inline
    const_iterator
    end () const 
    { 
        READ_LOCK(_mutex);
        return string_pointer->finish;
    }

    inline
    reverse_iterator
    rbegin () 
    {
        return reverse_iterator (end ()); 
    }

    inline
    const_reverse_iterator
    rbegin () const 
    { 
        return const_reverse_iterator (end ()); 
    }

    inline
    reverse_iterator
    rend () 
    { 
        return reverse_iterator (begin ());
    }

    inline
    const_reverse_iterator
    rend () const 
    { 
        return const_reverse_iterator (begin ()); 
    }

    //
    // capacity
    //
    size_type size () const;

    inline
    size_type
    length () const 
    { 
        return size (); 
    }

    size_type max_size () const ;  //970408 bkoz

    void resize (size_type n)
    { 
        resize (n, charT ()); 
    }

    void resize (size_type n, charT c) ;

    size_type capacity () const;
  
    void reserve (size_type res_arg = 0) ;

    bool
    empty () const
    { 
        return (size () == 0); 
    }

    //
    // element access
    //
  
    // const_reference -- Waiting for clarifications on this.
    charT operator[] (size_type pos) const;
 
    reference operator[] (size_type pos) ;

    const_reference at (size_type pos) const ;

    reference at (size_type pos) ;

    //
    // modifiers
    //
    basic_string&
    operator+= (const basic_string& rhs) ;

    basic_string&
    operator+= (const charT* s) ;

    basic_string&
    operator+= (charT c) ;

    basic_string&
    append (const basic_string& str);
    
    basic_string&
    append (const basic_string& str, size_type pos, 
            size_type n) ;

    basic_string&
    append (const charT* s, size_type n) ;

    basic_string&
    append (const charT* s) ;

    basic_string&
    append (size_type n, charT c);

#ifdef MSIPL_MEMBER_TEMPLATE
    
    template <class InputIterator>
    basic_string&
    append (InputIterator first, InputIterator last);

#else

    basic_string&
    append (iterator first, iterator last);

    basic_string&
    append (const_iterator first, const_iterator last);

#endif

    basic_string&
    assign (const basic_string& str);

    basic_string&
    assign (const basic_string& str, size_type pos, 
            size_type n) ;

    basic_string&
    assign (const charT* s, size_type n) ;

    basic_string&
    assign (const charT* s) ;

    basic_string&
    assign (size_type n, charT c);

#ifdef MSIPL_MEMBER_TEMPLATE
    
    template <class InputIterator>
    basic_string&
    assign (InputIterator first, InputIterator last);

#else

    basic_string&
    assign (iterator first, iterator last);

    basic_string&
    assign (const_iterator first, const_iterator last);

#endif

    basic_string&
    insert (size_type pos1, const basic_string& str);

    basic_string&
    insert (size_type pos1, const basic_string& str, 
            size_type pos2, size_type n) ;

    basic_string&
    insert (size_type pos, const charT* s, size_type n) ;

    basic_string&
    insert (size_type pos, const charT* s) ;

    basic_string&
    insert (size_type pos, size_type n, charT c);

    iterator
    insert (iterator position, charT c = charT());

    void
    insert (iterator position, size_type n, charT c);

#ifdef MSIPL_MEMBER_TEMPLATE
    
    template <class InputIterator>
    void
    insert (iterator p, InputIterator first, InputIterator last);

#else

    void
    insert (iterator p, iterator first, iterator last);

    void
    insert (iterator p, const_iterator first, const_iterator last);

#endif

    basic_string&
    erase (size_type pos = 0, size_type n = npos) ;

    iterator
    erase (iterator position);

    iterator
    erase (iterator first, iterator last);

    basic_string&
    replace (size_type pos1, size_type n1, const basic_string& str); 

    basic_string&
    replace (size_type pos1, size_type n1, const basic_string& str, 
             size_type pos2, size_type n2) ;

    basic_string&
    replace (size_type pos, size_type n1, const charT* s, 
             size_type n2) ;

    basic_string&
    replace (size_type pos, size_type n1, const charT* s) ;

    basic_string&
    replace (size_type pos, size_type n, size_type rep, charT c);
     
    basic_string&
    replace (iterator i1, iterator i2, const basic_string& str);

    basic_string&
    replace (iterator i1, iterator i2, const charT* s, size_type n);

    basic_string&
    replace (iterator i1, iterator i2, const charT* s);
 
    basic_string&
    replace (iterator i1, iterator i2, size_type n, charT c);

#ifdef MSIPL_MEMBER_TEMPLATE
    
    template <class InputIterator>
    basic_string&
    replace (iterator i1, iterator i2, InputIterator first,
             InputIterator last);

#else

    basic_string&
    replace (iterator i1, iterator i2, iterator first, iterator last);

    basic_string&
    replace (iterator i1, iterator i2, 
             const_iterator first, const_iterator last);

#endif

    size_type
    copy (charT* s, size_type n, size_type pos = 0) const ;

    void
    swap (basic_string& rhs)
    {
        WRITE_LOCK(_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (string_pointer, rhs.string_pointer);
#else
        ::swap (string_pointer, rhs.string_pointer);
#endif
    }

    //
    // string operations
    //
    const charT* c_str () const ;

#ifdef MSIPL_MULTITHREAD
    const charT*
    c_str (charT* s) const     // re-entrant function.
    {
        READ_LOCK(_mutex);
        if (!empty ())
        {
            traits_type::copy (s, begin (), size ());
        }
        traits_type::assign (*(s +size ()), eos ());
        return s;
    }
#endif

    //970415 bkoz change to make pch
    //971001 mf -- previous change was bogus
    
    const charT*
    data () const 
    {
       READ_LOCK(_mutex);
       static charT s[1];
       traits_type::assign (s[0], traits_type::eos());
       return (empty () ? s : c_str ()); 
    }

  	

/*    const charT*
    data () const
    {
       READ_LOCK(_mutex);
       return (empty () ? 0  : c_str() );  //in effect, specializing for char
    }

  */
  	
    const allocator_type& get_allocator () const; //970408 bkoz out of line

    size_type
    find (const basic_string& str, size_type pos = 0) const ;

    size_type
    find (const charT* s, size_type pos, size_type n) const ;

    size_type
    find (const charT* s, size_type pos = 0) const ;

    size_type
    find (charT c, size_type pos = 0) const ;

    size_type
    rfind (const basic_string& str, size_type pos = npos) const ;

    size_type
    rfind (const charT* s, size_type pos, size_type n) const ;

    size_type
    rfind (const charT* s, size_type pos = npos) const ;

    size_type
    rfind (charT c, size_type pos = npos) const ;

    size_type
    find_first_of (const basic_string& str, size_type pos = 0) const ;

    size_type
    find_first_of (const charT* s, size_type pos, size_type n) const ;

    size_type
    find_first_of (const charT* s, size_type pos = 0) const ;

    size_type
    find_first_of (charT c, size_type pos = 0) const ;

    size_type
    find_last_of (const basic_string& str, size_type pos = npos) const ;

    size_type
    find_last_of (const charT* s, size_type pos, size_type n) const ;

    size_type
    find_last_of (const charT* s, size_type pos = npos) const ;

    size_type
    find_last_of (charT c, size_type pos = npos) const ;

    size_type
    find_first_not_of (const basic_string& str, size_type pos = 0) const ;

    size_type
    find_first_not_of (const charT* s, size_type pos, size_type n) const ;

    size_type
    find_first_not_of (const charT* s, size_type pos = 0) const ;

    size_type
    find_first_not_of (charT c, size_type pos = 0) const ;

    size_type
    find_last_not_of (const basic_string& str, size_type pos = npos) const ;

    size_type
    find_last_not_of (const charT* s, size_type pos, size_type n) const ;

    size_type
    find_last_not_of (const charT* s, size_type pos = npos) const ;

    size_type
    find_last_not_of (charT c, size_type pos = npos) const ;

    basic_string
    substr (size_type pos = 0,  size_type n = npos) const ;

    int
    compare (const basic_string& str) const ;

    int
    compare (size_type pos1, size_type n1,
             const basic_string& str) const;

    int
    compare (size_type pos1, size_type n1,
             const basic_string& str,
             size_type pos2, size_type n2) const;

    int
    compare (const charT* s) const ;

    int
    compare (size_type pos, size_type n1,
             const charT* str, size_type n2 = npos) const;

private:

    size_t
    reference_count () const { return string_pointer->count; }

    void
    adjust_end (size_type n)  { 
       string_pointer->finish = string_pointer->start+n; 
    }

    void cleanup(); 	//970408	bkoz move out of line

public:

    static charT eos ()
    {
        return traits_type::eos ();
    }

    //static const size_type         npos;

private:

    //
    // data member
    //
    reference_alloc_type    reference_allocator;
    charT*                  c_str_ptr;
    reference_pointer       string_pointer;

    //
    // declare a mutex object.
    //
    DEC_OBJ_LOCK(_mutex)

};

typedef  basic_string<char, char_traits<char>, 
                      allocator<char> >                 string;

#ifdef MSIPL_WCHART
typedef  basic_string<wchar_t, char_traits<wchar_t>,
                      allocator<wchar_t> >              wstring;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(stdexcept)
#else
#include MOD_INCLUDE(mexcept)
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

//basic_string_ref defs that depend on exception definitions being seen
//970420 bkoz for .pch
#if !__option(precompile)
template <class charT, class traits, class Allocator>
const typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::npos = (typename basic_string<charT, traits, Allocator>::size_type )-1;
#endif

template <class charT, class traits, class Allocator>
void
basic_string_ref<charT, traits, Allocator>::throwlength ()
{
#ifdef MSIPL_EXCEPT
   throw   length_error ("Length exception occurred");
#else
   fprintf (stderr, "Length exception occurred\n");
   exit (1);
#endif
}

template <class charT, class traits, class Allocator>
void
basic_string_ref<charT, traits, Allocator>::throwrange ()
{
#ifdef  MSIPL_EXCEPT
   throw   out_of_range ("Out of range exception occurred");
#else
   fprintf (stderr, "Out of range exception occurred\n");
   exit (1);
#endif
}

template <class charT, class traits, class Allocator>
void
basic_string_ref<charT, traits, Allocator>::cleanup () 
{
    destroy (start, finish);
    if (capacity () > 0)
    {
        string_allocator.deallocate (start);
    }
    start = finish = end_of_storage = 0;
}

//#pragma dont_inline on //970407 bkoz
template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::basic_string_ref (const Allocator& alloc) 
:string_allocator(alloc)
{
    start = finish = end_of_storage = 0;
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (const basic_string<charT, traits, Allocator>& str, 
                  size_type pos, size_type rlen,
                  const Allocator& alloc) 
:string_allocator (alloc)
{
    //
    // Assumption that range checking has been done previously
    //
    if (rlen)
    {
        start  = string_allocator.allocate (rlen);
        // finish = uninitialized_copy (str.begin ()+pos, 
        //                              str.begin ()+pos+rlen, start);
        finish = (traits::copy (start, str.begin ()+pos, rlen))+rlen;
        end_of_storage = finish;
    }
    else
    {
        start = finish = end_of_storage = 0;
    }
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (const charT* s, size_type rlen, size_type rres, 
                  const Allocator& alloc)
:string_allocator(alloc)
{
    //
    // Assumption that rlen <= rres, 
    // and s is a non-null pointer if rlen != 0
    //
    if (rres)
    { 
        start  = string_allocator.allocate (rres);
        // finish = uninitialized_copy (s, s+rlen, start);
        finish = (traits::copy (start, s, rlen))+rlen;
        end_of_storage = start + rres;
    }
    else
    {
        start = finish = end_of_storage = 0;
    }
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (const charT* s, size_type n,
                  const Allocator& alloc)
:string_allocator(alloc)
{
    typedef basic_string<charT, traits, Allocator> string_type;
    //
    // Assumption that s is a non-null pointer if n != 0
    //
    if (n == string_type::npos)
    {
       throwlength ();
    }
    if (n)
    {
        start = string_allocator.allocate (n);
        //finish = uninitialized_copy (s, s+n, start);
        finish = (traits::copy (start, s, n))+n;
        end_of_storage = finish;
    }
    else
    {
        start = finish = end_of_storage = 0;
    }
    count = 1;
}

#ifdef MSIPL_MEMBER_TEMPLATE
template <class charT, class traits, class Allocator>
template <class InputIterator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (InputIterator begin, InputIterator end,
                  const Allocator& alloc)
:string_allocator(alloc)
{
    typedef basic_string<charT, traits, Allocator> string_type;
    start = string_allocator.allocate (end - begin);
    // finish = uninitialized_copy (begin, end, start);
    finish = (traits::copy (start, begin, end-begin) + (end-begin));
    end_of_storage = finish;
    count = 1;
}
#else
template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (iterator begin, iterator end,
                   const Allocator& alloc)
:string_allocator(alloc)
{
    typedef basic_string<charT, traits, Allocator> string_type;
    start = string_allocator.allocate (end - begin);
    // finish = uninitialized_copy (begin, end, start);
    //finish = (traits::copy (start, begin, end-begin) - (end-begin)); //961206 bkoz
    finish = (traits::copy (start, begin, end-begin) + (end-begin));
    end_of_storage = finish;
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (const_iterator begin, const_iterator end,
                   const Allocator& alloc)
:string_allocator(alloc)
{
    typedef basic_string<charT, traits, Allocator> string_type;
    start = string_allocator.allocate (end - begin);
    // finish = uninitialized_copy (begin, end, start);
    finish = traits::copy (start, begin, end-begin) + (end - begin);
    end_of_storage = finish;
    count = 1;
}
#endif

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (const charT* s, const Allocator& alloc) 
:string_allocator(alloc)
{
    //
    // Assumption that s is a non-null pointer
    //
    size_type  size = traits_type::length (s);
    if (size)
    {
        start = string_allocator.allocate (size);
        // finish = uninitialized_copy (s, s+size, start);
        finish = traits::copy (start, s, size) + size;
        end_of_storage = finish;
    }
    else
    {
        start = finish = end_of_storage = 0;
    }
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>::
basic_string_ref (size_type rep, charT c,const Allocator& alloc)
:string_allocator(alloc)
{
    typedef basic_string<charT, traits, Allocator> string_type;
    if (rep == string_type::npos)
    {
       throwlength ();
    }
    if (rep)
    {
        start = string_allocator.allocate (rep);
        uninitialized_fill_n (start, rep, c);
        end_of_storage = finish = start + rep;
    }
    else
    {
        start = finish = end_of_storage = 0;
    }
    count = 1;
}

template <class charT, class traits, class Allocator>
basic_string_ref<charT, traits, Allocator>:: ~basic_string_ref () 
{
    cleanup ();
}
// mf 101597 #pragma dont_inline reset //970407 bkoz

//#pragma dont_inline on //970407 bkoz
template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::basic_string (const Allocator& alloc) 
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (alloc);
    c_str_ptr = 0;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (const basic_string<charT, traits, Allocator>& str, size_type pos, size_type n) 
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(str.reference_allocator)
#endif
{
    if (pos > str.size ())
    {
       string_reference::throwrange ();
    }
    WRITE_LOCK(_mutex);
    size_type rlen = (n > (str.size () - pos)) ? 
                          (str.size () - pos)  : n;
    if ((rlen == str.size ()) && 
       (str.reference_count () != npos))
    {
      (string_pointer = str.string_pointer)->add_count ();
    }
    else
    {
       string_pointer = reference_allocator.allocate (1);
       new (string_pointer) string_reference (str, pos, rlen,
                              (str.string_pointer)->string_allocator);
    }
    c_str_ptr = 0;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (const charT* s, size_type n, const Allocator& alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    if (n >= npos)
    {
        string_reference::throwlength ();
    }
    WRITE_LOCK(_mutex);
    if (s)
    {
        string_pointer = reference_allocator.allocate (1);
        new (string_pointer) string_reference (s, n, alloc);
        c_str_ptr = 0;
    }
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (const charT* s, const Allocator& alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (s, alloc);
    c_str_ptr = 0;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (size_type rep, charT c, const Allocator& alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (rep, c, alloc);
    c_str_ptr = 0;
}

#ifdef MSIPL_MEMBER_TEMPLATE

template <class charT, class traits, class Allocator>
template <class InputIterator>
basic_string<charT, traits, Allocator>::
basic_string (InputIterator begin, InputIterator end,const Allocator& alloc)
: reference_allocator(alloc)
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (begin, end, alloc);
    c_str_ptr = 0;
}

#else

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (iterator begin, iterator end,const Allocator& alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (begin, end, alloc);
    c_str_ptr = 0;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
basic_string (const_iterator begin, const_iterator end,const Allocator& alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
: reference_allocator(alloc)
#endif
{
    WRITE_LOCK(_mutex);
    string_pointer = reference_allocator.allocate (1);
    new (string_pointer) string_reference (begin, end, alloc);
    c_str_ptr = 0;
}

#endif

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::
~basic_string () 
{
    cleanup ();
    if (c_str_ptr)
    { 
       delete[] c_str_ptr;
    }
    REMOVE(_mutex);
}
// mf 101597 #pragma dont_inline reset //970407 bkoz

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator= (const basic_string<charT, traits, Allocator>& str) 
{
    WRITE_LOCK(_mutex);
    if (this != &str)
    {
        if (str.reference_count () != npos)
        {
            str.string_pointer->add_count ();
            cleanup ();
            string_pointer = str.string_pointer;
        }
        else
        {
            cleanup ();
            new (string_pointer) string_reference (str, 0, str.size (),
                                  (str.string_pointer)->string_allocator);
        }
    }
    return *this;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator= (const charT* s) 
{
    return *this = basic_string<charT, traits, Allocator>(s);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator= (charT c) 
{
    return *this = basic_string<charT, traits, Allocator>(1, c);
}

template <class charT, class traits, class Allocator>
void
basic_string<charT, traits, Allocator>::
resize (size_type n, charT c) 
{
    if (n > max_size ())
    {
        string_reference::throwlength ();
    }
    WRITE_LOCK(_mutex);
    if ((reference_count () > 1) || (n > capacity ()))
    {
        reference_pointer tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), ((n > size ()) ?
                                             size () : n), n);
        cleanup ();
        string_pointer = tmp;
    }
    if (n > size ())
    {
        string_reference::uninitialized_fill_n (end (), n-size (), c);
    }
    else
    {
        destroy (begin ()+n, end ());
    }
    adjust_end (n);
}

template <class charT, class traits, class Allocator>
void
basic_string<charT, traits, Allocator>::
reserve (size_type res_arg) 
{
    if (res_arg == npos)
    {
        string_reference::throwlength ();
    }
    WRITE_LOCK(_mutex);
    if (res_arg > capacity ())
    {
        reference_pointer tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), size (), res_arg);
        cleanup ();
        string_pointer = tmp;
    }
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::reference
basic_string<charT, traits, Allocator>::
at (size_type pos) 
{
    if (pos >= size ())
    {
        string_reference::throwrange ();
    }
    WRITE_LOCK(_mutex);
    if (reference_count () > 1)
    {
        reference_pointer tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), size (), size ());
        cleanup ();
        string_pointer = tmp;
    }
    return (*(begin ()+pos));
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator+= (const basic_string<charT, traits, Allocator>& rhs)
{
    WRITE_LOCK(_mutex);
    return append (rhs);
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator+= (const charT* s) 
{
    return *this += basic_string<charT, traits,
                                 Allocator>(s, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
operator+= (charT c) 
{
    return *this += basic_string<charT, traits, Allocator>(1, c);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (const basic_string<charT, traits, Allocator>& str)
{
    return append (str, 0, npos);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (const basic_string<charT, traits, Allocator>& str,
        size_type pos, size_type n)
{
    if (pos > str.size ())
    {
        string_reference::throwrange ();
    }

    WRITE_LOCK(_mutex);

    size_type rlen = (n > (str.size () - pos)) ? 
                         (str.size () - pos)  : n;
    
    if (size () >= (npos - rlen))
    {
        string_reference::throwlength ();
    }

    bool     newalloc = false;
    reference_pointer   tmp;

    if ((reference_count () > 1) || (rlen > (capacity ()-size ())))
    {
        tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), size (), size ()+rlen);
        newalloc = true;
    }
    else
    {
        tmp = string_pointer;
    }

//    string_reference::uninitialized_copy (str.begin ()+pos ,
//                                          str.begin ()+pos+rlen, tmp->finish);
    traits_type::copy (tmp->finish, str.begin ()+pos, rlen);
    if (newalloc) cleanup ();
    string_pointer = tmp;
    adjust_end (size ()+rlen);
    return *this;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (const charT* s, size_type n) 
{
    return append (basic_string<charT, traits, Allocator>(s, n));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (const charT* s) 
{
    return append (s, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (size_type rep, charT c) 
{
    return append (basic_string<charT, traits,
                                Allocator>((size_type)rep, c));
}

#ifdef MSIPL_MEMBER_TEMPLATE

template <class charT, class traits, class Allocator>
template <class InputIterator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (InputIterator first, InputIterator last)
{
    return append (basic_string<charT, traits, Allocator>(first, last));
}

#else

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (iterator first, iterator last)
{
    return append (basic_string<charT, traits, Allocator>(first, last));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
append (const_iterator first, const_iterator last)
{
    return append (basic_string<charT, traits, Allocator>(first, last));
}

#endif

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (const basic_string<charT, traits, Allocator>& str)
{
    return assign (str, 0, npos);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (const basic_string<charT, traits, Allocator>& str,
        size_type pos, size_type n)
{
    if (pos > str.size ())
    {
        string_reference::throwrange ();
    }
    WRITE_LOCK(_mutex);
    size_type rlen = (n > (str.size () - pos)) ? 
                         (str.size () - pos)  : n;

    if ((rlen == str.size ()) && 
       (str.reference_count () != npos))
    {
       cleanup ();
      (string_pointer = str.string_pointer)->add_count ();
       return *this;
    }
    else
    {
	    if (rlen == npos)
	    {
		    string_reference::throwlength ();
	    }
	    if ((reference_count () > 1) || (rlen && (capacity () < rlen)))
	    {
		    reference_pointer tmp = reference_allocator.allocate (1);
		    new (tmp) string_reference (str.begin ()+pos, rlen);
		    cleanup ();
		    string_pointer = tmp;
	    }
	    else
	    {
		    if (rlen > size ())
		    {
			    string_reference::copy (str.begin ()+pos,
                                        str.begin()+pos+size (), begin ());
			    string_reference::uninitialized_copy (str.begin ()+pos+size (), 
							      str.begin ()+pos+rlen, end ());
		    }
		    else
		    {
			    string_reference::copy (str.begin ()+pos,
                                        str.begin ()+pos+rlen, begin ());
			    destroy (begin ()+rlen, end ());
		    }
		    adjust_end (rlen);
	    }
	    return *this;
    }
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (const charT* s, size_type n) 
{
    return assign (basic_string<charT, traits, Allocator>(s, n));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (const charT* s) 
{
    return assign (s, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (size_type rep, charT c) 
{
    return assign (basic_string<charT, traits, Allocator>(rep, c));
}

#ifdef MSIPL_MEMBER_TEMPLATE

template <class charT, class traits, class Allocator>
template <class InputIterator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (InputIterator first, InputIterator last)
{
    return assign (basic_string<charT, traits, Allocator>(first, last));
}

#else

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (iterator first, iterator last)
{
    return assign (basic_string<charT, traits, Allocator>(first, last));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
assign (const_iterator first, const_iterator last)
{
    return assign (basic_string<charT, traits, Allocator>(first, last));
}

#endif

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
insert (size_type pos1, const basic_string<charT, traits, Allocator>& str)
{
    return insert (pos1, str, 0, npos);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
insert (size_type pos1, const basic_string<charT, traits, Allocator>& str,
        size_type pos2, size_type n) 
{
    if (pos1 > size () || pos2 > str.size ())
    {
        string_reference::throwrange ();
    }
    WRITE_LOCK(_mutex);
    size_type rlen = (n > (str.size () - pos2)) ? 
                         (str.size () - pos2)  : n;

    if (size () >= (npos-rlen))
    {
        string_reference::throwlength ();
    }
    if (rlen) 
    {
        reference_pointer tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), pos1, size ()+rlen);
        string_reference::uninitialized_copy (begin ()+pos1, 
                          end (), tmp->finish+rlen);        
        string_reference::uninitialized_copy (str.begin ()+pos2,
                                              str.begin ()+pos2+rlen,
                                              tmp->finish);        
        tmp->finish = tmp->start + size () + rlen;
        cleanup ();
        string_pointer = tmp;
    }
    return *this;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
insert (size_type pos, const charT* s, size_type n)
{
    return insert (pos, basic_string<charT, traits, Allocator>(s, n));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
insert (size_type pos, const charT* s)
{
    return insert (pos, basic_string<charT, traits,
                                 Allocator>(s, traits_type::length (s)));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
insert (size_type pos, size_type rep, charT c) 
{
    return insert (pos, basic_string<charT, traits, Allocator>(rep, c));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::iterator
basic_string<charT, traits, Allocator>::
insert (iterator position, charT c)
{
    WRITE_LOCK(_mutex);
    difference_type dist = position - begin ();
    insert (position - begin (),
            basic_string<charT, traits, Allocator>(1, c));
    return begin () + dist;
}

template <class charT, class traits, class Allocator>
void
basic_string<charT, traits, Allocator>::
insert (iterator position, size_type rep, charT c)
{
    insert (position-begin (),
            basic_string<charT, traits, Allocator>(rep, c));
}


#ifdef MSIPL_MEMBER_TEMPLATE

template <class charT, class traits, class Allocator>
template <class InputIterator>
void
basic_string<charT, traits, Allocator>::
insert (iterator p, InputIterator first, InputIterator last)
{
    insert (p - begin (),
            basic_string<charT, traits, Allocator>(first, last));
}

#else

template <class charT, class traits, class Allocator>
void
basic_string<charT, traits, Allocator>::
insert (iterator p, iterator first, iterator last)
{
    insert (p - begin(),
            basic_string<charT, traits, Allocator>(first, last));
}

template <class charT, class traits, class Allocator>
void 
basic_string<charT, traits, Allocator>::
insert (iterator p, const_iterator first, const_iterator last)
{
    insert (p - begin (),
            basic_string<charT, traits, Allocator>(first, last));
}

#endif

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
erase (size_type pos, size_type n) 
{
    WRITE_LOCK(_mutex);
    if (pos > size ())
    {
        string_reference::throwrange ();
    }
    size_type xlen = (n > (size ()-pos)) ? (size ()-pos) : n;
    if (reference_count () > 1)
    {
        reference_pointer tmp = reference_allocator.allocate (1);
        new (tmp) string_reference (begin (), pos, size ());
        string_reference::uninitialized_copy (begin ()+pos+xlen, 
                          end (), tmp->start+pos);
        tmp->finish = tmp->start+size ()-xlen;
        cleanup ();
        string_pointer = tmp;
    }
    else if (xlen == size ())
    {
        string_pointer->cleanup ();
    }
    else if (xlen)
    {
        string_reference::copy (begin ()+pos+xlen, end (), 
                                begin ()+pos);
        destroy (end ()-xlen, end ());
        adjust_end (size ()-xlen);
    }
    return *this;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::iterator
basic_string<charT, traits, Allocator>::
erase (iterator position)
{
    WRITE_LOCK(_mutex);
    difference_type len = position - begin ();
    erase (position-begin (), 1);
    iterator ret_iter = begin () + len;
    return ret_iter;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::iterator
basic_string<charT, traits, Allocator>::
erase (iterator first, iterator last)
{
    difference_type len = 0;
    WRITE_LOCK(_mutex);
    iterator ret_iter = begin ();
    while (ret_iter != last) { ++len; ++ret_iter; }
    erase (first-begin (), last-first);
    ret_iter = begin ();
    for (int i=0; i < len - (last - first); ++i) ++ret_iter;
    return ret_iter;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (size_type pos1, size_type n1,
         const basic_string<charT, traits, Allocator>& str)
{
    return replace (pos1, n1, str, 0, npos);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (size_type pos1, size_type n1,
         const basic_string<charT, traits, Allocator>& str,
         size_type pos2, size_type n2) 
{
    if ((pos1 > size ()) || (pos2 > str.size ()))
    {
        string_reference::throwrange ();
    }
    WRITE_LOCK(_mutex);
    size_type xlen = (n1 > (size ()-pos1))     ? 
                          (size ()-pos1)      : n1;
    size_type rlen = (n2 > (str.size ()-pos2)) ? 
                          (str.size ()-pos2)  : n2;

    if ((size ()-xlen) >= (npos-rlen))
    {
        string_reference::throwlength ();
    }
   
    reference_pointer tmp = reference_allocator.allocate (1);
    new (tmp) string_reference (begin (), pos1, size ()+rlen-xlen);
    string_reference::uninitialized_copy (begin ()+pos1+xlen, 
                      end (), tmp->finish+rlen);
    string_reference::uninitialized_copy (str.begin ()+pos2,
                                          str.begin ()+pos2+rlen, tmp->finish);        
    tmp->finish = tmp->start+size ()+rlen-xlen;
    cleanup ();
    string_pointer = tmp;
    return *this;
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (size_type pos, size_type n1, const charT* s, size_type n2)
{
    return replace (pos, n1, basic_string<charT, traits, Allocator>(s, n2));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (size_type pos, size_type n1, const charT* s)
{
    return replace (pos, n1, basic_string<charT, traits,
                              Allocator>(s, traits_type::length (s)));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (size_type pos, size_type n1, size_type n2, charT c) 
{
    return replace (pos, n1, basic_string<charT, traits, Allocator> (n2, c));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2,
         const basic_string<charT, traits, Allocator>& str)
{
    return replace (i1-begin (), i2-i1, str);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, const charT* s, size_type n)
{
    return replace (i1-begin (), i2-i1, s, n);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, const charT* s)
{
    return replace (i1-begin (), i2-i1, s);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, size_type n, charT c)
{
    return replace (i1-begin (), i2-i1, n, c);
}

#ifdef MSIPL_MEMBER_TEMPLATE

template <class charT, class traits, class Allocator>
template <class InputIterator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, InputIterator first, InputIterator last)
{
    return replace(i1, i2, basic_string<charT, traits,
                                        Allocator>(first, last));
}

#else

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, iterator first, iterator last)
{
    return replace(i1, i2, basic_string<charT, traits,
                                        Allocator>(first, last));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>&
basic_string<charT, traits, Allocator>::
replace (iterator i1, iterator i2, const_iterator first, const_iterator last)
{
    return replace (i1, i2, basic_string<charT, traits,
                                         Allocator>(first, last));
}

#endif

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
copy (charT* s, size_type n, size_type pos) const 
{
    WRITE_LOCK(_mutex);
    if (pos > size ())
    {
        string_reference::throwrange ();
    }
    size_type  rlen = (n > (size ()-pos)) ? 
                          (size ()-pos)  : n;

    if (!empty ())
    {
        traits_type::copy (s, begin ()+pos, rlen);
    }
    return rlen;
}

template <class charT, class traits, class Allocator>
const charT*
basic_string<charT, traits, Allocator>::
c_str () const 
{
    typedef  basic_string<charT, traits, Allocator>   string_type;

    charT*&  cptr_iter = ((string_type*)this)->c_str_ptr;

    if (c_str_ptr) 
    {
        if (traits_type::length (c_str_ptr) < size ())
        {
           delete[] cptr_iter;
           cptr_iter = new charT [size ()+1];
        }
    }
    else
    {
        cptr_iter = new charT [size ()+1];
    }
    if (!empty ())
    {
        traits_type::copy (cptr_iter, begin (), size ());
    }
    traits_type::assign (*(cptr_iter +size ()), eos ());
    return c_str_ptr;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find (const basic_string<charT, traits, Allocator>& str, size_type pos) const
{
    size_type  count = pos;
    size_type  str_len = str.size ();
    READ_LOCK(_mutex);
    if (empty () || str.empty())
        return npos;
    const_iterator str_iter = str.begin ();
    charT c = *str.begin ();
    if (size() > pos && str_len <= (count = size ()-pos))
    {
		const_iterator iter1 = begin() + pos;
        const_iterator iter2;
        for (count -= str.size()-1;
             //(iter2 = traits_type::find(iter1, count, c));
             ((iter2 = traits_type::find(iter1, count, c)) != 0); //961209 mm
             count -= iter2-iter1+1, iter1 = iter2+1) 
        {
            if (traits_type::compare (iter2, str_iter, str_len) == 0)
                return (iter2 - begin());
        }
    }
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find (const charT* s, size_type pos, size_type n) const 
{
    READ_LOCK(_mutex);
    return find (basic_string<charT, traits, Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find (const charT* s, size_type pos) const 
{
    READ_LOCK(_mutex);
    return find (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find (charT c, size_type pos) const 
{
    READ_LOCK(_mutex);
    return find (basic_string<charT, traits, Allocator>(1, c), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
rfind (const basic_string<charT, traits, Allocator>& str, size_type pos) const
{
    size_type  n = str.size ();
    READ_LOCK(_mutex);
    size_type  count = (pos < (size ()-n)) ? pos : (size ()-n);
    if ((size () < n) || (n == 0))
        return npos;
    const_iterator str_iter = str.begin();
    charT c = *str_iter;
    const_iterator iter = begin ()+count;
    for (;;--iter)
        if (traits_type::eq (*iter, c) &&
            traits_type::compare (iter, str_iter, n) == 0)
            return (iter - begin()); 
        else
        if (iter == begin()) break;
        
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
rfind (const charT* s, size_type pos, size_type n) const 
{
    return rfind (basic_string<charT, traits, Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
rfind (const charT* s, size_type pos) const 
{
    return rfind (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
rfind (charT c, size_type pos) const 
{
    READ_LOCK(_mutex);
    size_type count = ((pos < size ()) ? pos+1 : size ());
    if (empty ())
        return npos;
    while (!(traits_type::eq (*(begin ()+count-1), c)) && (count > 1))
        --count;
    if ((count == 1) && !(traits_type::eq (*(begin ()), c)))
        return npos;
    else
        return (count-1);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_of (const basic_string<charT, traits, Allocator>& str,
               size_type pos) const
{
    const_iterator str_iter = str.begin ();
    size_type str_len = str.size ();
    READ_LOCK(_mutex);
    if (!str.empty() && size() > pos)
    {
        const_iterator iter1 = begin() + pos;
        const_iterator iter2 = begin() + size ();
        for (; iter1 < iter2; ++iter1)
            if (traits_type::find (str_iter, str_len, *iter1) != 0)
                return (iter1 - begin());
    }
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_of (const charT* s, size_type pos, size_type n) const 
{
    return find_first_of (basic_string<charT, traits, Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_of (const charT* s, size_type pos) const
{
    return find_first_of (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_of (charT c, size_type pos) const 
{
    return find_first_of (basic_string<charT, traits, Allocator>(1, c), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_of (const basic_string<charT, traits, Allocator>& str,
              size_type pos) const
{
    READ_LOCK(_mutex);
    size_type count = (size () > pos) ? pos : (size()-1);
    if (!str.empty() && size() > 0)
    {
        const_iterator iter = begin () + count;
        for (;;--iter)
            if (traits_type::find (str.begin(), str.size(), *iter) != 0)
                return (iter - begin());
            else 
            if (iter == begin())
                break;
    }
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_of (const charT* s, size_type pos, size_type n) const 
{
    return find_last_of (basic_string<charT, traits,
                                      Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_of (const charT* s, size_type pos) const 
{
    return find_last_of (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_of (charT c, size_type pos) const 
{
    return find_last_of (basic_string<charT, traits, Allocator>(1, c), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_not_of (const basic_string<charT, traits, Allocator>& str,
                   size_type pos) const
{
    size_type n = str.size ();
    const_iterator str_iter = str.begin();
    READ_LOCK(_mutex);
    if (size() > pos)
    {
        const_iterator iter1 = begin() + pos;
        const_iterator iter2 = begin() + size();
        for (; iter1 < iter2; ++iter1)
            if (traits_type::find (str_iter, n, *iter1) == 0)
                return (iter1 - begin());
    }
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_not_of (const charT* s, size_type pos, size_type n) const 
{
    return find_first_not_of (basic_string<charT, traits,
                                            Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_not_of (const charT* s, size_type pos) const
{
    return find_first_not_of (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_first_not_of (charT c, size_type pos) const 
{
    return find_first_not_of (basic_string<charT, traits,
                                           Allocator>(1, c), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_not_of (const basic_string<charT, traits, Allocator>& str,
                  size_type pos) const
{
    size_type n = str.size ();
    const_iterator str_iter = str.begin();
    READ_LOCK(_mutex);
    size_type count = (pos < size ()) ? pos : (size ()-1);
    if (size())
    {
        for(const_iterator iter = begin() + count;;--iter)
            if (traits_type::find (str_iter, n, *iter) == 0)
                return (iter - begin());
            else 
            if (iter == begin())
                break;
    }
    return npos;
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_not_of (const charT* s, size_type pos, size_type n) const 
{
    return find_last_not_of (basic_string<charT, traits,
                                          Allocator>(s, n), pos);
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_not_of (const charT* s, size_type pos) const
{
    return find_last_not_of (s, pos, traits_type::length (s));
}

template <class charT, class traits, class Allocator>
typename basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::
find_last_not_of (charT c, size_type pos) const 
{
    return find_last_not_of (basic_string<charT, traits,
                                          Allocator>(1, c), pos);

//    size_type count = ((pos < size ()) ? pos+1 : size ());
//    if (empty ())
//        return npos;
//    while ((traits_type::eq (*(begin ()+count-1), c)) && (count > 1))
//        --count;
//    if ((count == 1) && (traits_type::eq (*(begin ()), c)))
//        return npos;
//    else
//        return (count-1);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>
basic_string<charT, traits, Allocator>::
substr (size_type pos,  size_type n) const 
{
    typedef basic_string<charT, traits, Allocator>    string_type;

    READ_LOCK(_mutex);
    if (pos > size ())
    {
        string_reference::throwrange ();
    }
    if (empty ())
        return  string_type ();
    else
        return  string_type (begin ()+pos, 
                           ((n > (size ()-pos)) ? (size ()-pos) : n));
}

template <class charT, class traits, class Allocator>
int
basic_string<charT, traits, Allocator>::
compare (const basic_string<charT, traits, Allocator>& str) const
{
    READ_LOCK(_mutex);
    size_type rlen = (size () > str.size ()) ? str.size () : size ();
    int result = traits_type::compare (data (), str.data (), rlen);
    return (result ? result : size () - str.size ());
}

template <class charT, class traits, class Allocator>
int
basic_string<charT, traits, Allocator>::
compare (size_type pos1, size_type n1,
         const basic_string<charT, traits, Allocator>& str) const
{
    typedef basic_string<charT, traits, Allocator>   string_type;

    READ_LOCK(_mutex);
    return string_type (*this, pos1, n1).compare (string_type (str));
}

template <class charT, class traits, class Allocator>
int
basic_string<charT, traits, Allocator>::
compare (size_type pos1, size_type n1,
         const basic_string<charT, traits, Allocator>& str,
         size_type pos2, size_type n2) const
{
    typedef basic_string<charT, traits, Allocator>   string_type;

    READ_LOCK(_mutex);
    return string_type (*this, pos1, n1).compare (string_type (str, pos2, n2));
}

template <class charT, class traits, class Allocator>
int
basic_string<charT, traits, Allocator>::
compare (const charT* s) const
{
    READ_LOCK(_mutex);
    return compare (basic_string<charT, traits, Allocator>(s));
}

template <class charT, class traits, class Allocator>
int
basic_string<charT, traits, Allocator>::
compare (size_type pos, size_type n1,
         const charT* s, size_type n2) const
{
    typedef basic_string<charT, traits, Allocator>   string_type;

    READ_LOCK(_mutex);
    return string_type (*this, pos, n1).compare (string_type (s, n2));
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::size_type
basic_string<charT, traits, Allocator>::size () const 
    { 
        READ_LOCK(_mutex);
        return string_pointer->size (); 
    }

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::size_type 
basic_string<charT, traits, Allocator>::max_size () const 
{ 
   // return string_reference::string_allocator.max_size (); 
   return reference_allocator.max_size (); 
}


template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::size_type 
basic_string<charT, traits, Allocator>::capacity () const 
{ 
    READ_LOCK(_mutex);
    return string_pointer->capacity (); 
}


template <class charT, class traits, class Allocator>
charT
basic_string<charT, traits, Allocator>::operator[] (size_type pos) const
{
    READ_LOCK(_mutex);
    return ((pos < size ()) ? (*(begin ()+pos)) : eos ());
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::reference
basic_string<charT, traits, Allocator>::operator[] (size_type pos) 
{
    READ_LOCK(_mutex);
    return  at (pos);
}

template <class charT, class traits, class Allocator>
basic_string<charT, traits, Allocator>::const_reference
basic_string<charT, traits, Allocator>::at (size_type pos) const 
{
   READ_LOCK(_mutex);
   if (pos >= size ())
   {
       string_reference::throwrange ();
   }
   return (*(begin ()+pos));
}

template <class charT, class traits, class Allocator>
const basic_string<charT, traits, Allocator>::allocator_type&
basic_string<charT, traits, Allocator>::get_allocator () const{
	return string_pointer->get_allocator();
}

template <class charT, class traits, class Allocator>
void
basic_string<charT, traits, Allocator>::cleanup ()  { 
   if (!(string_pointer->rem_count ()))
   {
       destroy (string_pointer);
       reference_allocator.deallocate (string_pointer);
   }
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>
operator+ (const basic_string<charT, traits, Allocator>& lhs, 
           const basic_string<charT, traits, Allocator>& rhs)
{
    return basic_string<charT, traits, Allocator> (lhs).append (rhs);
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>
operator+ (const charT* lhs, 
           const basic_string<charT, traits, Allocator>& rhs) 
{
    return basic_string<charT, traits, Allocator> (lhs).append (rhs);
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>
operator+ (charT lhs, 
           const basic_string<charT, traits, Allocator>& rhs) 
{
    return basic_string<charT, traits, Allocator> (1, lhs).append (rhs);
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>
operator+ (const basic_string<charT, traits, Allocator>& lhs, 
           const charT* rhs) 
{
    typedef basic_string<charT, traits, Allocator>   string_type;

    return string_type (lhs).append (string_type (rhs));
}

template <class charT, class traits, class Allocator>
inline
basic_string<charT, traits, Allocator>
operator+ (const basic_string<charT, traits, Allocator>& lhs, 
           charT rhs) 
{
    typedef basic_string<charT, traits, Allocator>   string_type;

    return string_type (lhs).append (string_type (1, rhs));
}

template <class charT, class traits, class Allocator>
inline bool
operator== (const basic_string<charT, traits, Allocator>& lhs, 
            const basic_string<charT, traits, Allocator>& rhs)
{
    return !(lhs.compare (rhs));
}

template <class charT, class traits, class Allocator>
inline bool
operator== (const charT* lhs, 
            const basic_string<charT, traits, Allocator>& rhs) 
{
    return !(rhs.compare (lhs));
}

template <class charT, class traits, class Allocator>
inline bool
operator== (const basic_string<charT, traits, Allocator>& lhs, 
            const charT* rhs) 
{
    return !(lhs.compare (rhs));
}

#ifdef MSIPL_NONDEF
template <class charT, class traits, class Allocator>
inline bool
operator!= (const basic_string<charT, traits, Allocator>& lhs, 
            const basic_string<charT, traits, Allocator>& rhs)
{
    return lhs.compare (rhs);
}
#endif

template <class charT, class traits, class Allocator>
inline bool
operator!= (const charT* lhs, 
            const basic_string<charT, traits, Allocator>& rhs) 
{
    return rhs.compare (lhs);
}

template <class charT, class traits, class Allocator>
inline bool
operator!= (const basic_string<charT, traits, Allocator>& lhs, 
            const charT* rhs) 
{
    return lhs.compare (rhs);
}

template <class charT, class traits, class Allocator>
inline bool
operator< (const basic_string<charT, traits, Allocator>& lhs, 
           const basic_string<charT, traits, Allocator>& rhs)
{
    if (lhs.compare (rhs) < 0)
        return true;
    else
        return false;
}

template <class charT, class traits, class Allocator>
inline bool
operator< (const charT* lhs, 
           const basic_string<charT, traits, Allocator>& rhs) 
{
    if (rhs.compare (lhs) > 0)
        return true;
    else
        return false;
}

template <class charT, class traits, class Allocator>
inline bool
operator< (const basic_string<charT, traits, Allocator>& lhs, 
           const charT* rhs) 
{
    if (lhs.compare (rhs) < 0)
        return true;
    else
        return false;
}

#ifdef  MSIPL_NONDEF
template <class charT, class traits, class Allocator>
inline bool
operator> (const basic_string<charT, traits, Allocator>& lhs, 
           const basic_string<charT, traits, Allocator>& rhs)
{
    return (rhs < lhs);
}
#endif

template <class charT, class traits, class Allocator>
inline bool
operator> (const charT* lhs, 
           const basic_string<charT, traits, Allocator>& rhs) 
{
    return (rhs < lhs);
}

template <class charT, class traits, class Allocator>
inline bool
operator> (const basic_string<charT, traits, Allocator>& lhs, 
           const charT* rhs) 
{
    return (rhs < lhs);
}

#ifdef  MSIPL_NONDEF
template <class charT, class traits, class Allocator>
inline bool
operator>= (const basic_string<charT, traits, Allocator>& lhs, 
            const basic_string<charT, traits, Allocator>& rhs)
{
    return !(lhs < rhs);
}
#endif

template <class charT, class traits, class Allocator>
inline bool
operator>= (const charT* lhs, 
            const basic_string<charT, traits, Allocator>& rhs) 
{
    return !(lhs < rhs);
}

template <class charT, class traits, class Allocator>
inline bool
operator>= (const basic_string<charT, traits, Allocator>& lhs, 
            const charT* rhs) 
{
    return !(lhs < rhs);
}

#ifdef  MSIPL_NONDEF
template <class charT, class traits, class Allocator>
inline bool
operator<= (const basic_string<charT, traits, Allocator>& lhs, 
            const basic_string<charT, traits, Allocator>& rhs)
{
    return !(rhs < lhs);
}
#endif

template <class charT, class traits, class Allocator>
inline bool
operator<= (const charT* lhs, 
            const basic_string<charT, traits, Allocator>& rhs) 
{
    return !(rhs < lhs);
}

template <class charT, class traits, class Allocator>
inline bool
operator<= (const basic_string<charT, traits, Allocator>& lhs, 
            const charT* rhs) 
{
    return !(rhs < lhs);
}

//
// Check : Compile time error. Clashes with swap in algobase.h
//
// template <class charT, class traits, class Allocator>
// void swap (basic_string<charT, traits, Allocator>& lhs, 
//            basic_string<charT, traits, Allocator>& rhs)
// {
//     lhs.swap (rhs);
// }

template <class charT, class IS_traits, class STR_traits, class STR_Alloc>
basic_istream<charT, IS_traits>&
operator>> (basic_istream<charT, IS_traits>& is,
            basic_string<charT, STR_traits, STR_Alloc>& str) 
{
    STR_traits::int_type c;
    const int BSIZE = 512;
    charT buf[BSIZE];
    int bcnt = 0;

    const ctype<charT>& ctype_ = use_facet (is.getloc (), (ctype<charT>*)0);
    typedef basic_string<charT, STR_traits, STR_Alloc> string_type;

    str.erase ();

    typename basic_istream <charT, IS_traits>::sentry  s_ (is);          // mm 970121
    //typename basic_istream <charT, IS_traits>::sentry  s_ (is, true);  // mm 970121
    if (s_)
    {
       typename basic_string<charT, STR_traits,
                             STR_Alloc>::size_type size_max =
             (is.width () ? is.width () : str.max_size ());

       typename basic_string<charT, STR_traits,
                             STR_Alloc>::size_type size_ = 0;

        while (size_ < size_max)
        {
            c = is.rdbuf()->sbumpc ();
            size_++;
            if (IS_traits::eq_int_type (c, IS_traits::eof ()))
            {
                is.setstate (ios_base::eofbit);
                break;
            }
            else if (ctype_.is (ctype_.space, c))
                break;
            else
            {
                //if (bcnt <= BSIZE)  // MSIPL 961216
                if (bcnt < BSIZE)
                {
                    buf[bcnt++] = STR_traits::to_char_type (c);
                }
                else
                {
                    str.append (buf, bcnt);
                    buf[0] = STR_traits::to_char_type (c);
                    bcnt = 1;
                }
            }
        }
        if (bcnt != 0)
            str.append(buf,bcnt);
    }
    return is;
}

/*	970415 bkoz 
	equivalent, last one faster
*/
/*
template <class charT, class OS_traits, class STR_traits, class STR_Alloc>
basic_ostream<charT, OS_traits>&
operator<< (basic_ostream<charT, OS_traits>& os, 
            const basic_string<charT, STR_traits, STR_Alloc>& str) 
{
    os.write (str.data (), str.size ());
    return os;
}
*/
template <class charT, class OS_traits, class STR_traits, class STR_Alloc>
basic_ostream<charT, OS_traits>&
operator<< (basic_ostream<charT, OS_traits>& os, 
            const basic_string<charT, STR_traits, STR_Alloc>& str) 
{
   os.write (str.begin(), str.size ());
    return os;
}

//The following is retrofitted from Modena revision 970402              mm-970402
template<class charT, class traits, class Allocator>
basic_istream<charT, traits>&
getline(basic_istream<charT, traits>& is, basic_string<charT, traits, Allocator>& str, charT delim)
{
    typename traits::int_type c;
    typename basic_string<charT,traits,Allocator>::size_type count = 
                                                             str.max_size();
    ios_base::iostate flg = ios_base::goodbit;  // state of istream obj.
    typename basic_istream<charT,traits>::sentry s_(is, true); 
                                                // don't skip white spaces 
    if(s_)                                    
    {
        const int BSIZE = 512;
        charT buf[BSIZE];
        int bcnt = 0;
        str.erase (); 
        //str.clear();                         // clear() is used instead of erase()
                                             // for better performance.
        while (count)
        {
            c = is.rdbuf()->sbumpc();        // try to extract a character
            if (traits::eq_int_type (c, traits::eof ()))
            {
                flg |= ios_base::eofbit;
                break;                       // stop reading - eof was reached
            }

            --count;                         // a character was extracted

            if (traits::eq_int_type (traits::to_int_type (delim), c))
                break;                       // stop reading - delim reached

            if (bcnt == BSIZE)
            {
                str.append (buf, bcnt);      // buffer full, append to str.
                bcnt = 0;                    // reset buffer pointer
            }
            buf[bcnt++] = traits::to_char_type (c);
        }
        if (bcnt != 0)
            str.append(buf,bcnt);            // empty the buffer
    }
    if (count == 0 || (count == str.max_size ())) // count == 0 => max_size of 
        flg |= ios_base::failbit;                 // string reached .
                                                  // count == str.max_size =>
                                                  // no characters are extracted.
    if (flg != ios_base::goodbit)       // setstate is called now to avoid  
        is.setstate (flg);              // throwing 'eof' exception even when no 
                                        // char is extracted, in which case 
                                        // failure should be thrown.
    return is;               // is.setcount() is removed in nov. DWP.
}

template<class charT, class traits, class Allocator>
inline
basic_istream<charT, traits>&
getline(basic_istream<charT, traits>& is, basic_string<charT, traits, Allocator>& str)
{
    //return getline(is, str, is.widen('\n'));  // traits::newline() no more exists.
    return getline(is, str, traits::newline());  //Can't find is.wident()   mm
}



// End of Modena code from 970402
#ifndef MSIPL_PARTIAL_TEMPL
null_template
struct iterator_trait <const string*> {
    typedef ptrdiff_t                    distance_type;
    typedef const string                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};
null_template
struct iterator_trait <string*> {
    typedef ptrdiff_t                    distance_type;
    typedef string                       value_type;
    typedef random_access_iterator_tag   iterator_category;
};
#endif /* MSIPL_PARTIAL_TEMPL */

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#ifdef __MSL_NO_INSTANTIATE__
	//these are instantiated in inst1.cpp, in the library, for char types
	template __dont_instantiate class char_traits<char>;
	template __dont_instantiate class basic_string_ref<char, char_traits<char>, allocator<char> >;
	template __dont_instantiate class basic_string <char, char_traits<char>, allocator<char> >;
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#ifdef DebugNew_H       //970401 bkoz
	#define new NEW
#endif

#endif /* MSIPL_BSTRING_H */

/*  Change record
MW-jh 960205a  Moved line from 1258 to 742 to avoid undeclared identifier
mw-bk 961113   line 3182, cannot compile getline as is, had to immediately specialize to char
mw-bk 961111   line 11, add include algorithm for swap
mw-bk 961205 	line 2499, 2507 use pragma warn_possunwant to remove warning
mw-bk 961206 	line 1466 bkoz changed traits::copy(it, it, usl) to correctly set finish pointer
							for string_pointer member of basic_string
mw-mm 961209  pragma warn_possunwant doesn't seem to work so changed assignment to logical expr
mw-bk 961210  added alignment wrapper
mw-ah 961216  changed memory -> mmemory
MSIPL 961216  lines 3155, 3214 Correction so that 512 chars stored and not 513.
KO    961217	Changed char_traits from a struct to a class. Needed for the new x86 compiler.
mm 970121     Cause initial whitespace to be skipped in >> and getline.
mm-970402     Corrected version of getline from Modena with changes following Aaron Zicks analysis
mw-bk 970415	line 3131 ostream::operator<<(ostream, string) uses begin()
mw-bk 970415	line 1127 	remove static char from data() so .pch will work
*/
