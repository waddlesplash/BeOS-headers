/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_ITERATOR_H
#define MSIPL_ITERATOR_H

#include <mcompile.h>

#include MOD_INCLUDE(iosfwd)
#include MOD_C_INCLUDE(stddef)
#include MOD_C_INCLUDE(mutex)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 24.3.1 -- Standard global_iterator tags

struct input_iterator_tag         {};
struct output_iterator_tag        {};
struct forward_iterator_tag 
  : public output_iterator_tag,
    public input_iterator_tag     {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

// Subclause 24.3.2 -- Basic iterators

#ifdef MSIPL_DEF_TEMPARG
template <class Category, class T, class Distance = ptrdiff_t>    
#else
template <class Category, class T, class Distance>    
#endif
struct global_iterator {
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  distance_type;
};

template <class Iterator>
struct iterator_trait {
    typedef typename Iterator::iterator_category  iterator_category;
    typedef typename Iterator::value_type         value_type;
    typedef typename Iterator::distance_type      distance_type;
};

#ifdef MSIPL_PARTIAL_TEMPL
template <class T>
struct iterator_trait <T*> {
    typedef ptrdiff_t                    distance_type;
    typedef T                            value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#else // Specialization for Pointer type iterators

null_template
struct iterator_trait <void *const *> {
    typedef ptrdiff_t                    distance_type;
    typedef void *const                  value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <void * *> {
    typedef ptrdiff_t                    distance_type;
    typedef void *                       value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#ifdef MSIPL_BOOL_BUILTIN

null_template
struct iterator_trait <const bool*> {
    typedef ptrdiff_t                    distance_type;
    typedef const bool                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      bool*> {
    typedef ptrdiff_t                    distance_type;
    typedef       bool                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      bool* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef       bool* const        	 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#endif

null_template
struct iterator_trait <const char*> {
    typedef ptrdiff_t                    distance_type;
    typedef const char                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <char*> {
    typedef ptrdiff_t                    distance_type;
    typedef char                         value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <char* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef char* const                         value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const unsigned char*> {
    typedef ptrdiff_t                    distance_type;
    typedef const unsigned char                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <unsigned char*> {
    typedef ptrdiff_t                    distance_type;
    typedef unsigned char                         value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <unsigned char* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef unsigned char* const       	 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const int*> {
    typedef ptrdiff_t                    distance_type;
    typedef const int                    value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <int*> {
    typedef ptrdiff_t                    distance_type;
    typedef int                          value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <int* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef int* const                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const unsigned int*> {
    typedef ptrdiff_t                    distance_type;
    typedef const unsigned int           value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <unsigned int*> {
    typedef ptrdiff_t                    distance_type;
    typedef unsigned int                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <unsigned int* const *> {
    typedef ptrdiff_t                    distance_type;
    typedef unsigned int* const          value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const long*> {
    typedef ptrdiff_t                    distance_type;
    typedef const long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long*> {
    typedef ptrdiff_t                    distance_type;
    typedef       long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long* const *> {
    typedef ptrdiff_t                    distance_type;
    typedef long* const                    value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const unsigned long*> {
    typedef ptrdiff_t                    distance_type;
    typedef const unsigned long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      unsigned long*> {
    typedef ptrdiff_t                    distance_type;
    typedef unsigned long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <unsigned long* const *> {
    typedef ptrdiff_t                    distance_type;
    typedef  unsigned long* const        value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#ifdef __MSL_LONGLONG_SUPPORT__

null_template
struct iterator_trait <const long long*> {
    typedef ptrdiff_t                    distance_type;
    typedef const long long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long long*> {
    typedef ptrdiff_t                    distance_type;
    typedef       long long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long long* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef  long long* const                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const unsigned long long*> {
    typedef ptrdiff_t                    distance_type;
    typedef const unsigned long long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      unsigned long long*> {
    typedef ptrdiff_t                    distance_type;
    typedef  unsigned long long                   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      unsigned long long* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef  unsigned long long* const   value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#endif //__MSL_LONGLONG_SUPPORT__

//970120 bkoz size_t and unsigned long ==redeclared
/*
null_template
struct iterator_trait <const size_t*> {
    typedef ptrdiff_t                    distance_type;
    typedef const size_t                       value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <size_t*> {
    typedef ptrdiff_t                    distance_type;
    typedef size_t                       value_type;
    typedef random_access_iterator_tag   iterator_category;
};
*/
null_template
struct iterator_trait <const float*> {
    typedef ptrdiff_t                    distance_type;
    typedef const float                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      float*> {
    typedef ptrdiff_t                    distance_type;
    typedef       float                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      float* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef float* const                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const double*> {
    typedef ptrdiff_t                    distance_type;
    typedef const double                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      double*> {
    typedef ptrdiff_t                    distance_type;
    typedef       double                 value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      double* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef double* const                value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <const long double*> {
    typedef ptrdiff_t                    distance_type;
    typedef const long double            value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long double*> {
    typedef ptrdiff_t                    distance_type;
    typedef long double                  value_type;
    typedef random_access_iterator_tag   iterator_category;
};

null_template
struct iterator_trait <      long double* const*> {
    typedef ptrdiff_t                    distance_type;
    typedef long double* const           value_type;
    typedef random_access_iterator_tag   iterator_category;
};

#endif // no MSIPL_PARTIAL_TEMPL; ie DON'T support partial template 

struct output_iterator
    : public global_iterator <output_iterator_tag, void, void> {};

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Distance = ptrdiff_t> 
#else
template <class T, class Distance> 
#endif
struct input_iterator 
    : public global_iterator <input_iterator_tag, T, Distance> {};

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Distance = ptrdiff_t> 
#else
template <class T, class Distance> 
#endif
struct forward_iterator
    : public global_iterator <forward_iterator_tag, T, Distance> {};

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Distance = ptrdiff_t> 
#else
template <class T, class Distance> 
#endif
struct bidirectional_iterator
    : public global_iterator <bidirectional_iterator_tag, T, Distance> {};

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Distance = ptrdiff_t> 
#else
template <class T, class Distance> 
#endif
struct random_access_iterator
    : public global_iterator <random_access_iterator_tag, T, Distance> {};


template <class InputIterator, class Distance>
inline
void
__distance (InputIterator first, InputIterator last, Distance& n, 
            input_iterator_tag)
{
    while (first != last) { ++first; ++n; }
}

template <class ForwardIterator, class Distance>
inline
void
__distance (ForwardIterator first, ForwardIterator last, Distance& n, 
            forward_iterator_tag)
{
    while (first != last) { ++first; ++n; }
}

template <class BidirectionalIterator, class Distance>
inline
void
__distance (BidirectionalIterator first, BidirectionalIterator last, 
            Distance& n, bidirectional_iterator_tag)
{
    while (first != last) { ++first; ++n; }
}

template <class RandomAccessIterator, class Distance>
inline void
__distance (RandomAccessIterator first, RandomAccessIterator last, 
            Distance& n, random_access_iterator_tag)
{
    n += last - first;
}

template <class InputIterator>
inline 
ptrdiff_t																									//961112 MM  hack around . . .
//typename iterator_trait<InputIterator>::distance_type		//961112 . . .this
distance (InputIterator first, InputIterator last)
{
    iterator_trait<InputIterator>::distance_type n = 0;
    __distance (first, last, n, 
                iterator_trait<InputIterator>::iterator_category ());
    return n;
}

template <class InputIterator, class Distance>
inline
void __advance (InputIterator& i, Distance n, input_iterator_tag)
{
    while (n--) ++i;
}

template <class ForwardIterator, class Distance>
inline
void
__advance (ForwardIterator& i, Distance n, forward_iterator_tag)
{
    while (n--) ++i;
}

template <class BidirectionalIterator, class Distance>
inline
void __advance (BidirectionalIterator& i, Distance n, 
                bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __advance (RandomAccessIterator& i, Distance n, 
                       random_access_iterator_tag)
{
    i += n;
}

template <class InputIterator, class Distance>
inline void advance (InputIterator& i, Distance n)
{
    typedef typename iterator_trait <InputIterator>::iterator_category
                     Category;
    __advance (i, n, Category ());
}

// Subclause 24.4 -- Predefined iterators
// Section 24.4.1 -- Reverse iterators


// Section 24.4.1.1 and 24.4.1.2 -- reverse_bidirectional_iterator

#ifdef MSIPL_DEF_TEMPARG
template <class BidirectionalIterator, 
          class T = typename iterator_trait<BidirectionalIterator>::value_type&,
          class Reference = T&, class Pointer = T*, 
          class Distance = ptrdiff_t> 
#else
template <class BidirectionalIterator, class T,
          class Reference, class Pointer, class Distance> 
#endif
class reverse_bidirectional_iterator 
    : public global_iterator<bidirectional_iterator_tag, T, Distance> {

    typedef reverse_bidirectional_iterator<BidirectionalIterator, T,
                                           Reference,
                                           Pointer, Distance> self;

    friend bool operator== (const self& x, const self& y);


protected:

    BidirectionalIterator current;

    DEC_OBJ_LOCK(r_mutex)

public:

    reverse_bidirectional_iterator () {}

    explicit
    reverse_bidirectional_iterator (BidirectionalIterator x)
    : current (x) {}

    ~reverse_bidirectional_iterator () { REMOVE(r_mutex); }

    BidirectionalIterator base () const 
      { READ_LOCK(r_mutex); return current; }

    Reference operator*() const
    {
        READ_LOCK(r_mutex);
        BidirectionalIterator tmp = current;
        return *--tmp;
    }

    //
    // Waiting for clarifications on this
    //
    // Pointer operator-> () const { return & (operator* ()); }

    self& operator++ ()
    {
        WRITE_LOCK(r_mutex);
        --current;
        return *this;
    }
    self operator++ (int)
    {
        WRITE_LOCK(r_mutex);
        self tmp = *this;
        --current;
        return tmp;
    }
    self& operator-- ()
    {
        WRITE_LOCK(r_mutex);
        ++current;
        return *this;
    }
    self operator-- (int)
    {
        WRITE_LOCK(r_mutex);
        self tmp = *this;
        ++current;
        return tmp;
    }
};

template <class BidirectionalIterator, class T,
          class Reference, class Pointer,
          class Distance>
inline bool operator== (
  const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                       Pointer, Distance>& x, 
  const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
                                       Pointer, Distance>& y)
{
    return x.current == y.current;
}


// Subclause 24.4.1.3 and 24.4.1.4 -- class reverse_iterator

#ifdef MSIPL_DEF_TEMPARG
template <class RandomAccessIterator, 
          class T = typename iterator_trait<RandomAccessIterator>::value_type&, 
          class Reference = T&, class Pointer = T*, 
          class Distance = ptrdiff_t> 
#else
template <class RandomAccessIterator, class T, class Reference, class Pointer, class Distance> 
#endif
class reverse_iterator 
    : public global_iterator<random_access_iterator_tag, T, Distance> {

    typedef reverse_iterator<RandomAccessIterator, T, Reference,
                             Pointer, Distance> self;

    friend bool operator== (const self& x, const self& y);
    friend bool operator< (const self& x, const self& y);
    friend Distance operator- (const self& x, const self& y);
    friend self operator+ (Distance n, const self& x);

protected:

    RandomAccessIterator current;

    DEC_OBJ_LOCK(r_mutex)

public:

    reverse_iterator () {}

    explicit
    reverse_iterator (RandomAccessIterator x) : current (x) {}

    ~reverse_iterator () { REMOVE(r_mutex); }

    RandomAccessIterator base () const { READ_LOCK(r_mutex); return current; }

    Reference operator*() const { READ_LOCK(r_mutex); return *(current - 1); }

    //
    // Waiting for clarifications on this
    //
    // Pointer   operator-> () const { return & (operator* ()); }

    self& operator++ ()
    {
        WRITE_LOCK(r_mutex);
        --current;
        return *this;
    }
    self operator++ (int)
    {
        WRITE_LOCK(r_mutex);
        self tmp = *this;
        --current;
        return tmp;
    }
    self& operator-- ()
    {
        WRITE_LOCK(r_mutex);
        ++current;
        return *this;
    }
    self operator-- (int)
    {
        WRITE_LOCK(r_mutex);
        self tmp = *this;
        ++current;
        return tmp;
    }
    //970216 bkoz move these out of line so that they will not be syntax checked on
    // every instantiation
	self operator+ (Distance n) const;
    self& operator+= (Distance n);
    self operator- (Distance n) const;
    self& operator-= (Distance n);
	/*
    self operator+ (Distance n) const
    {
        READ_LOCK(r_mutex);
        return self (current - n);
    }
    self& operator+= (Distance n)
    {
        WRITE_LOCK(r_mutex);
        current -= n;
        return *this;
    }
    self operator- (Distance n) const
    {
        READ_LOCK(r_mutex);
        return self (current + n);
    }
    self& operator-= (Distance n)
    {
        WRITE_LOCK(r_mutex);
        current += n;
        return *this;
    }
    */
    Reference operator[] (Distance n) const 
      { READ_LOCK(r_mutex); return * (*this + n); }
};

//970216 bkoz provide definitions out of line for following optional operators
#define R_I_T template <class RandomAccessIterator, class T, class Reference, class Pointer, class Distance>
#define R_I_T_T reverse_iterator<RandomAccessIterator, T, Reference, Pointer, Distance > //970131 bkoz
    
R_I_T
R_I_T_T
R_I_T_T::operator+ (Distance n) const
{
    READ_LOCK(r_mutex);
    return self (current - n);
}

R_I_T
R_I_T_T&
R_I_T_T::operator+= (Distance n)
{
    WRITE_LOCK(r_mutex);
    current -= n;
    return *this;
}

R_I_T
R_I_T_T
R_I_T_T::operator- (Distance n) const
{
    READ_LOCK(r_mutex);
     return self (current + n);
    
}

R_I_T
R_I_T_T&
R_I_T_T::operator-= (Distance n)
{
    WRITE_LOCK(r_mutex);
     current += n;     
     return *this;
}
//end bkoz
template <class RandomAccessIterator, class T, class Reference,
          class Pointer,  class Distance>
inline bool
operator== (const reverse_iterator<RandomAccessIterator, T,
                                  Reference, Pointer, Distance>& x, 
           const reverse_iterator<RandomAccessIterator, T,
                                  Reference, Pointer, Distance>& y)
{
    return x.current == y.current;
}

template <class RandomAccessIterator, class T, class Reference,
          class Pointer, class Distance>
inline bool
operator< (const reverse_iterator<RandomAccessIterator, T,
                                 Reference,Pointer, Distance>& x, 
          const reverse_iterator<RandomAccessIterator, T,
                                 Reference, Pointer, Distance>& y)
{
    return y.current < x.current;
}

template <class RandomAccessIterator, class T, class Reference, 
          class Pointer, class Distance>
inline Distance operator- (const reverse_iterator<RandomAccessIterator, T,
                                                 Reference, Pointer,
                                                 Distance>& x, 
                          const reverse_iterator<RandomAccessIterator, T,
                                                 Reference, Pointer,
                                                 Distance>& y)
{
    return y.current - x.current;
}

template <class RandomAccessIterator, class T, class Reference,
          class Pointer, class Distance>
inline
reverse_iterator<RandomAccessIterator, T, Reference, Pointer, Distance> 
operator+ (Distance n,
          const reverse_iterator<RandomAccessIterator, T, Reference,
                                 Pointer, Distance>& x)
{
    return reverse_iterator<RandomAccessIterator, T, Reference,
                            Pointer, Distance>
       (x.current - n);
}


// Subclause 24.4.2 -- Insert iterators

// Section 24.4.2.1 -- class back_insert_iterator

template <class Container>
class back_insert_iterator 
    : public global_iterator <output_iterator_tag, void, void> {
protected:

    Container& container;

    typename Container::iterator     iter;

public:

    explicit
    back_insert_iterator (Container& x) : container (x) {}

    back_insert_iterator<Container>&
    operator= (const typename Container::value_type& value)
    {
        container.push_back (value);
        return *this;
    }

    back_insert_iterator<Container>& operator*()     { return *this; }
    back_insert_iterator<Container>& operator++ ()    { return *this; }
    back_insert_iterator<Container>& operator++ (int) { return *this; }
};

template <class Container>
inline
back_insert_iterator<Container> back_inserter (Container& x)
{
    return back_insert_iterator<Container> (x);
}


// Section 24.4.2.3 -- class front_insert_iterator

template <class Container>
class front_insert_iterator 
    : public global_iterator <output_iterator_tag, void, void> {
protected:

    Container& container;

public:

    explicit
    front_insert_iterator (Container& x) : container (x) {}

    front_insert_iterator<Container>&
    operator= (const typename Container::value_type& value)
    { 
        container.push_front (value);
        return *this;
    }

    front_insert_iterator<Container>& operator*()      { return *this; }
    front_insert_iterator<Container>& operator++ ()    { return *this; }
    front_insert_iterator<Container>& operator++ (int) { return *this; }
};

template <class Container>
inline
front_insert_iterator<Container> front_inserter (Container& x)
{
    return front_insert_iterator<Container> (x);
}

// Section 24.4.2.5 -- class insert_iterator

template <class Container>
class insert_iterator 
    : public global_iterator <output_iterator_tag, void, void> {
protected:

    Container& container;
    typename Container::iterator iter;

public:

    insert_iterator (Container& x, typename Container::iterator i) 
        : container (x), iter (i) {}

    insert_iterator<Container>&
    operator= (const typename Container::value_type& value)
    { 
        iter = container.insert (iter, value);
        ++iter;
        return *this;
    }

    insert_iterator<Container>& operator*()      { return *this; }
    insert_iterator<Container>& operator++ ()    { return *this; }
    insert_iterator<Container>& operator++ (int) { return *this; }
};

template <class Container, class Iterator>
inline
insert_iterator<Container> inserter (Container& x, Iterator i)
{
    return insert_iterator<Container> (x, Container::iterator (i));
}


// Subclause stream iterators

#ifdef MSIPL_DEF_TEMPARG
template <class T, class charT, class traits = char_traits<charT>,
          class Distance = ptrdiff_t>
#else
template <class T, class charT, class traits, class Distance>
#endif
class istream_iterator 
    : public global_iterator <input_iterator_tag, T, Distance> {

friend bool operator== (const istream_iterator<T, charT, traits, Distance>& x,
                        const istream_iterator<T, charT, traits, Distance>& y);
public:
    typedef basic_istream<charT, traits>   istream_type;

protected:

    typedef  T*  Pointer;

    istream_type* stream;
    T        value;
    bool     end_marker;

    DEC_OBJ_LOCK(is_mutex)

    void read ()
    {
        WRITE_LOCK(is_mutex);
        end_marker = (*stream) ? true : false;
        if (end_marker) *stream >> value;
        end_marker = (*stream) ? true : false;
    }

public:

    istream_iterator ()           : stream (&cin), end_marker (false) {}
    istream_iterator (istream_type& s) : stream (&s) { read (); }

    istream_iterator (const istream_iterator& x)
        : stream(x.stream), end_marker (x.end_marker), value (x.value) {}

    ~istream_iterator () {}

    const T& operator*() const { READ_LOCK(is_mutex); return value; }

    //
    // Waiting for clarifications on this
    //
    // Pointer   operator-> () { return & (operator* ()); }

    istream_iterator<T, charT, traits, Distance>& operator++ ()
    { 
        read (); 
        return *this;
    }

    istream_iterator<T, charT, traits, Distance> operator++ (int)
    {
        istream_iterator<T, charT, traits, Distance> tmp = *this;
        read ();
        return tmp;
    }
};

template <class T, class charT, class traits, class Distance>
inline
bool operator== (const istream_iterator<T, charT, traits, Distance>& x,
                const istream_iterator<T, charT, traits, Distance>& y)
{
    return x.stream == y.stream && x.end_marker == y.end_marker ||
           x.end_marker == false && y.end_marker == false;
}

#ifdef MSIPL_DEF_TEMPARG
template <class T, class charT, class traits = char_traits<charT> >
#else
template <class T, class charT, class traits>
#endif
class ostream_iterator 
    : public global_iterator <output_iterator_tag, void, void> {

public:
    typedef basic_ostream<charT, traits>   ostream_type;

protected:

    ostream_type* stream;
    charT*    char_string;

    DEC_MUTEX(os_mutex)

public:
    ostream_iterator (ostream_type& s)  
        : stream (&s), char_string (0)                   {}
    ostream_iterator (ostream_type& s, const charT* c) 
        : stream (&s), char_string ((charT*)c)           {}

    ostream_iterator (const ostream_iterator& x) 
        : stream (x.stream), char_string (x.char_string) {}

    ~ostream_iterator () {}

    ostream_iterator<T, charT, traits>& operator= (const T& value)
    { 
        LOCK(bl_mut, os_mutex);
        *stream << value;
        if (char_string) *stream << char_string;
        return *this;
    }
    ostream_iterator<T, charT, traits>& operator*()      { return *this; }
    ostream_iterator<T, charT, traits>& operator++ ()    { return *this; } 
    ostream_iterator<T, charT, traits>& operator++ (int) { return *this; } 
};

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT>,
          class Distance = ptrdiff_t>
#else
template <class charT, class traits, class Distance>
#endif
class istreambuf_iterator
    : public global_iterator <input_iterator_tag, charT, Distance> {

public:

    typedef  charT                char_type;
    typedef  traits               traits_type;

    typedef  typename traits::pos_type     pos_type;
    typedef  typename traits::off_type     off_type;
    typedef  typename traits::int_type     int_type;

    typedef  basic_streambuf<char_type, traits>     streambuf_type;
    typedef  basic_istream<char_type, traits>       istream_type;

public:

    class proxy {

    protected :

        char_type           keep_;
        streambuf_type*     sbuf_;

        inline proxy (char_type c, streambuf_type* sb)
        : keep_ (c), sbuf_ (sb) {}

    public:

        inline char_type
        operator* () { return keep_; }

        //  Should the return value be *sbuf_ ?????
        inline 
        operator istreambuf_iterator() { return sbuf_; }

        friend class istreambuf_iterator;
    };

public:
    
    inline
    istreambuf_iterator () MSIPL_THROW;

    inline
    istreambuf_iterator (istream_type& is) MSIPL_THROW;

    inline
    istreambuf_iterator (streambuf_type* sb) MSIPL_THROW;

    inline
    istreambuf_iterator (const proxy& p) MSIPL_THROW;

    inline
    char_type  
    operator* () const;

    inline
    istreambuf_iterator<char_type, traits, Distance>&
    operator++ ();

    inline
    proxy
    operator++ (int);

    inline
    bool
    equal (const istreambuf_iterator& b) const;

private:

    streambuf_type* sbuf_;

};

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::istreambuf_iterator () MSIPL_THROW
: sbuf_ (0) { }

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::
istreambuf_iterator (istream_type&  is) MSIPL_THROW
: sbuf_ (is.rdbuf ()) { }

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::
istreambuf_iterator (streambuf_type*  sb) MSIPL_THROW
: sbuf_ (sb) { }

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::
istreambuf_iterator (const proxy& p) MSIPL_THROW
: sbuf_ (p.sbuf_) { }

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::char_type
istreambuf_iterator<charT, traits, Distance>::operator* () const
{
    return traits::to_char_type (sbuf_ ? sbuf_->sgetc () : traits::eof ());
}

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>&
istreambuf_iterator<charT, traits, Distance>::operator++ ()
{
    if (sbuf_ && traits::eq_int_type (sbuf_->sbumpc (),
                                      traits::eof ()))
    {
        sbuf_ = 0;
    }
    return *this; 
}

template <class charT, class traits, class Distance>
inline
istreambuf_iterator<charT, traits, Distance>::proxy
istreambuf_iterator<charT, traits, Distance>::operator++ (int)
{
    // char_type        ch       =  (*(*this)); 
    char_type        ch       =   sbuf_->sbumpc ();
    streambuf_type*  sbuf_sav =   sbuf_;


    // ++ (*this);
    return  proxy (ch, sbuf_sav);
}

template <class charT, class traits, class Distance>
inline
bool
istreambuf_iterator<charT, traits, Distance>::
equal (const istreambuf_iterator& b) const
{
      return ((sbuf_ == 0  && b.sbuf_ == 0) || ((sbuf_ == 0) && 
             (traits::eq_int_type (b.sbuf_->sgetc (), traits::eof ()))) ||
             ((b.sbuf_ == 0) && (traits::eq_int_type (sbuf_->sgetc (),
                                                      traits::eof ()))) ||
              (sbuf_ != 0  && b.sbuf_ != 0));
}

template <class charT, class traits, class Distance>
inline 
bool
operator== (const istreambuf_iterator<charT, traits, Distance>& a,
            const istreambuf_iterator<charT, traits, Distance>& b)
{
    return a.equal (b);
}

#ifdef MSIPL_NONDEF
template <class charT, class traits, class Distance>
inline 
bool
operator!= (const istreambuf_iterator<charT, traits, Distance>& a,
            const istreambuf_iterator<charT, traits, Distance>& b)
{
    return ! (a.equal (b));
}
#endif

#ifdef MSIPL_DEF_TEMPARG
template <class charT, class traits = char_traits<charT> >
#else
template <class charT, class traits>
#endif
class ostreambuf_iterator 
    : public global_iterator <output_iterator_tag, void, void> {

public:

    typedef  charT                char_type;
    typedef  traits               traits_type;

    typedef  typename traits::pos_type     pos_type;
    typedef  typename traits::off_type     off_type;
    typedef  typename traits::int_type     int_type;

    typedef  basic_ostream<char_type, traits>        ostream_type;
    typedef  basic_streambuf<char_type, traits>      streambuf_type;

public:
    
    inline ostreambuf_iterator (ostream_type& s)  MSIPL_THROW 
        : sbuf_ (s.rdbuf ()) { failed_ = false; }

    inline ostreambuf_iterator (streambuf_type* s) MSIPL_THROW
        : sbuf_ (s)         { failed_ = false; }

    inline ostreambuf_iterator& 
    operator* () { return *this; }

    inline ostreambuf_iterator& 
    operator++ () { return *this; }

    inline ostreambuf_iterator&
    operator++ (int) { return *this; }

    inline ostreambuf_iterator&
    operator= (char_type c)
    {
        if (!failed_)
            if (traits::eq_int_type (sbuf_->sputc (traits::to_int_type (c)),
                                     traits::eof ()))
                failed_ = true;
        return *this;
    }

    inline bool 
    failed () const MSIPL_THROW { return failed_; }

private:

    streambuf_type*  sbuf_;
    bool             failed_;

};

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_ITERATOR_H */

//961112 mm	line 196 change paramaterized return type to ptr_difft
//961120 bkoz line 174, 244 change template struct iterator to global_iterator
//961120 bkoz lines 575, 579, 507, 599 change Container::iterator to iterator
//961210 bkoz lines 52-4 change iterator to global_iterator
//961210 bkoz added wrapper for alignment
//961217 bkoz line 122 to 164 provide specializations for fp pointers
//961223 bkoz line 165, added tenative FSpec pointer specialization for iterator_trait
//970216 bkoz added 2.2 iterator_traits specializations, in cohesive order w/ list* types also
//970217 bkoz moved reverse_iterator::operator +,-,+=,-= out of line