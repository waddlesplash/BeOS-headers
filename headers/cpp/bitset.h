/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_BITSET_H
#define MSIPL_BITSET_H

#include <mcompile.h>
 
#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(string)
#include MOD_INCLUDE(limits)
#else
#include MOD_INCLUDE(bstring)
#include MOD_INCLUDE(mlimits)
#endif
#include MOD_INCLUDE(algorithm)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

template <size_t N>
class bitset {

public:
    //
    // bit reference
    //
    class reference {
       friend class bitset;
       reference () : val (0) {}
    protected :
       char* val;
       DEC_OBJ_LOCK(ref_mutex)
       reference (char* val_) : val (val_) {}
    public :
       reference& operator= (bool x) 
         { WRITE_LOCK(ref_mutex); *val = (x ? 1 : 0); return *this; }
       reference& operator= (const reference& x)
         { return *this = bool (x); }
       bool       operator~ () const 
         { READ_LOCK(ref_mutex); return (*val ? 0 : 1); }
       operator   bool () const { READ_LOCK(ref_mutex); return *val; }
       reference& flip () 
         { WRITE_LOCK(ref_mutex); *val = (*val ? 0 : 1); return *this; }

       ~reference () { REMOVE(ref_mutex); }
    };

    //
    // 23.2.1.1 constructors
    //
    bitset ();
    bitset (unsigned long val);

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class charT, class traits>
    explicit
    bitset (const basic_string<charT, traits, allocator<charT> >& str,
            typename basic_string<charT, traits,
                                  allocator<charT> >::size_type pos = 0,
            typename basic_string<charT, traits,
                                  allocator<charT> >::size_type n = 
                    basic_string<charT, traits, allocator<charT> >::npos);

    bitset (const basic_string<char, char_traits<char>,
                               allocator<char> >& str,
            basic_string<char, char_traits<char>,
                         allocator<char> >::size_type pos = 0,
            basic_string<char, char_traits<char>,
                         allocator<char> >::size_type n =
            basic_string<char, char_traits<char>,
                         allocator<char> >::npos);
#else

    explicit
    bitset (const string& str, size_t pos = 0, size_t n = size_t (-1));

#endif

    ~bitset () { REMOVE(_mutex); }
    //
    // 23.2.1.2  bitset operations:
    //
    bitset<N>& operator&= (const bitset<N>& rhs);
    bitset<N>& operator|= (const bitset<N>& rhs);
    bitset<N>& operator^= (const bitset<N>& rhs);
    bitset<N>& operator<<= (size_t pos);
    bitset<N>& operator>>= (size_t pos);

    bitset<N>& set ();
    bitset<N>& set (size_t pos, int val = true);

    bitset<N>& reset ();
    bitset<N>& reset (size_t pos);

    bitset<N> operator~ () const;

    bitset<N>& flip ();
    bitset<N>& flip (size_t pos);

    //
    // element access
    //
    reference operator[] (size_t pos);

    //
    // conversions
    //
    unsigned long        to_ulong () const;

#if defined(MSIPL_MEMBER_TEMPLATE) && defined(MSIPL_TFN_DEFARG)
    template <class charT, class traits>
    basic_string<charT, traits, allocator<charT> >
    to_string () const;
#else
    string               to_string () const;
#endif

    //
    // utilities
    //
    size_t count () const;
    size_t size () const;

    //
    // comparisons
    //
    bool      operator== (const bitset<N>& rhs) const;
    bool      operator!= (const bitset<N>& rhs) const;
    bool      test (size_t pos) const;
    bool      any () const;
    bool      none () const;
    bitset<N> operator<< (size_t pos) const;
    bitset<N> operator>> (size_t pos) const;

private:

    char array[N];
    DEC_OBJ_LOCK(_mutex)
    
    static void throwrange ();
    static void throwinvalid ();
    static void throwoverflow ();

};

//
//  static member functions
//
template <size_t N>
inline
void 
bitset<N>::throwrange ()
{ 
#ifdef MSIPL_EXCEPT
    throw out_of_range ("Out of range exception occured.");
#else
    fprintf (stderr, "Out of range exception occured\n");
    exit (1);
#endif
}

template <size_t N>
inline
void 
bitset<N>::throwinvalid ()
{ 
#ifdef MSIPL_EXCEPT
    throw invalid_argument ("Invalid value in the string");
#else
    fprintf (stderr, "Invalid value in the string\n");
    exit (1);
#endif
}

template <size_t N>
inline
void 
bitset<N>::throwoverflow ()
{ 
#ifdef MSIPL_EXCEPT
    throw overflow_error ("Bit value can not be converted");
#else
    fprintf (stderr, "Bit value can not be converted\n");
    exit (1);
#endif
}

//
// default constructor
//
template <size_t N>
inline
bitset<N>::bitset ()
{
    for (size_t index =0; index < N; index++)
        array[index] = 0;            // intialize all to zero
}

//
// intializing the first M bit positions to the corresponding
// bit values in val
//
template <size_t N>
inline
bitset<N>:: bitset (unsigned long val)
{
#ifdef MSIPL_USING_NAMESPACE
    size_t M = std::min ((size_t)N,
                         (size_t)numeric_limits<unsigned long>::digits);
#else
    size_t M = ::min ((size_t)N,
                      (size_t)numeric_limits<unsigned long>::digits);
#endif
    size_t index = 0;
    unsigned long mask = 0x1;

    while (index < N)
    {
        if (index < M)
        {
            array[index] = ((val & mask) ? 1 : 0);
            mask <<= 1;
        }
        else
        {
            array[index] = 0;
        }
        ++index;
    }
} 

template < size_t N>
inline
bitset<N>&
bitset<N>::operator&= (const bitset<N>& rhs)
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N; index ++)
        array[index] &= rhs.array[index];
    return *this;
} 

template < size_t N>
inline
bitset<N>&
bitset<N>::operator|= (const bitset<N>& rhs)
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
        array[index] |=  rhs.array[index];
    return *this;
}

template <size_t N>
inline
bitset<N>&
bitset<N>::operator^= (const bitset<N>& rhs )
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
       array[index] ^= rhs.array[index];
    return *this;
}

//
// Replaces each bit position I in *this with a value
// if I < pos, the new value is zero
// if I >= pos the new value is the previous value
//             of the bit at position I-pos
//
template <size_t N>
inline
bitset<N>&
bitset<N>::operator<<= (size_t pos)
{
    WRITE_LOCK(_mutex);
    for (size_t index = N ; index > 0 ; index-- )
        array[index-1] = ((index-1 < pos ) ? 0 : array[index-1-pos]);
    return * this;
}

//
// Replaces each bit position I in *this with a value determined as
// if pos >= N - I the new value is zero
// if pos < N - I, the new value is previous value of the bit at position
//    I + pos.
//
template <size_t N>
inline
bitset<N>&
bitset<N>::operator>>= (size_t pos)
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
        array[index] = (((N- index) <= pos ) ? 0 : array[index+pos]);
    return *this;
} 

template <size_t N>
inline
bitset<N>&
bitset<N>::set ()
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N ; index++ )
        array[index] = 1;
    return *this;
}

template <size_t N>
inline
bitset<N>&
bitset<N>::set (size_t pos, int val)
{
    WRITE_LOCK(_mutex);
    if (pos >= N) throwrange (); 
        array[pos] = (val ? 1 : 0);
    return *this;
} 

template <size_t N>
inline
bitset<N>&
bitset<N>::reset ()
{
    WRITE_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
        array[index] = 0;
    return *this;
}

template <size_t N>
inline
bitset<N>&
bitset<N>::reset (size_t pos)
{
    if (pos >= N) throwrange (); 
    WRITE_LOCK(_mutex);
    array[pos] = 0;
    return *this;
} 

template <size_t N>
inline
bitset<N>
bitset<N>::operator~ () const
{
    bitset<N> x (*this );
    return  x.flip ();
} 

template <size_t N>
inline
bitset<N>&
bitset<N>::flip ()
{
    WRITE_LOCK(_mutex);
    for (size_t index =0; index <N; index++)
        array[index] = (array[index] ? 0 : 1);
    return *this;
}

//
// Section : 23.2.1.17
//
template< size_t N>
inline
bitset<N>&
bitset<N>::flip (size_t pos )
{
    WRITE_LOCK(_mutex);
    if (pos >= N) throwrange ();
    array[pos] = (array[pos] ? 0 : 1);
    return *this;
} 

//
//  reference operator[] (size_t pos);
//
template <size_t N>
inline
typename bitset<N>::reference
bitset<N>::operator[] (size_t pos)
{
    if (pos >= N) throwrange ();
    return  bitset<N>::reference (&array[pos]);
}

template <size_t N>
inline
unsigned long
bitset<N>::to_ulong () const
{
    size_t ulong_dig = numeric_limits<unsigned long>::digits;
    READ_LOCK(_mutex);
    if (N > ulong_dig)
    {
         for (int i = ulong_dig; i < N; i++)
             if (array[i])
                 throwoverflow ();
    }

    unsigned long convert   = 0ul;
    unsigned long factorial = 1ul;

    for (size_t index = 0; index < N; index++, factorial <<= 1)
        if (array[index]) convert += factorial;
    return convert;
} 

template <size_t N>
inline
size_t
bitset<N>::count () const
{
    size_t nc = 0;
    READ_LOCK(_mutex);
    for (size_t index = 0; index < N ; index++)
        if (array[index]) nc++;
    return nc;
}

template < size_t N>
inline
size_t
bitset<N>:: size () const { return N; }

template < size_t N>
inline
bool
bitset<N>::operator== (const bitset<N>& rhs) const
{
    READ_LOCK(_mutex);
    for (size_t index = 0; index < N; index++) 
        if (array[index] != rhs.array[index])
            return false;
    return true;
}

template <size_t N>
inline
bool
bitset<N>::operator!= (const bitset<N>& rhs) const
{
    return  ! (*this == rhs);
} 

template <size_t N>
inline
bool
bitset<N>::test (size_t pos)const
{
    if (pos >= N ) throwrange ();
    READ_LOCK(_mutex);
    return (array[pos] ? true : false);
}

template <size_t N>
inline
bool
bitset<N>::any () const
{
    READ_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
       if (array[index]) return true;
    return false;
} 

template <size_t N>
inline
bool
bitset<N>::none () const
{
    READ_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
       if (array[index]) return false;
    return true;
} 

template <size_t N>
inline
bitset<N>
bitset<N>::operator<< (size_t pos) const
{
    // create a temporary and return temp <<= pos.
    return (bitset<N> (*this) <<= pos) ;
} 

template <size_t N>
inline
bitset<N>
bitset<N>::operator>> (size_t pos) const
{
    // Create a temporary
    return (bitset<N> (*this) >>= pos);
}

#ifndef MSIPL_NON_TYPE_TEMPARG

template <size_t N>
inline
bitset<N>
operator& (const bitset<N>& lhs, const bitset<N>& rhs )
{
    return (bitset<N> (lhs) &= rhs) ;
}

template <size_t N>
inline
bitset<N>
operator| (const bitset<N>& lhs, const bitset<N>& rhs )
{
    return (bitset<N> (lhs) |= rhs) ;
}

template <size_t N>
inline
bitset<N>
operator^ (const bitset<N>& lhs, const bitset<N>& rhs )
{
    return (bitset<N> (lhs) ^= rhs) ;
} 

#endif  /* MSIPL_NON_TYPE_TEMPARG */

#ifdef MSIPL_MEMBER_TEMPLATE

template <size_t N>
template <class charT, class traits>
inline
bitset<N>::bitset (const basic_string<charT, traits,
                            allocator<charT> >& str,
                   typename basic_string<charT, traits,
                            allocator<charT> >::size_type pos,
                   typename basic_string<charT, traits,
                            allocator<charT> >::size_type n)
{
    size_t rlen, M;
    size_t index;

    if (pos > str.size ()) throwrange ();

#ifdef MSIPL_USING_NAMESPACE
    rlen  = std::min (n, str.size () -pos);
    M     = std::min ((size_t)N, (size_t)rlen);
#else
    rlen  = ::min (n, str.size () -pos);
    M     = ::min ((size_t)N, (size_t)rlen);
#endif

    for (index = 0; index < M; ++index)
    {
        switch (str[pos+M-1-index])
        {
            case '0' : array[index] = 0; break;
            case '1' : array[index] = 1; break;
            default  : throwinvalid (); 
        }
    }
    for ( ; index < N; ++index) array[index] = 0;
}

template <size_t N>
inline
bitset<N>::bitset (const basic_string<char, char_traits<char>,
                                      allocator<char> >& str,
                   basic_string<char, char_traits<char>,
                                      allocator<char> >::size_type pos,
                   basic_string<char, char_traits<char>,
                                      allocator<char> >::size_type n)
{
    size_t rlen, M;
    size_t index;

    if (pos > str.size ()) throwrange ();

#ifdef MSIPL_USING_NAMESPACE
    rlen  = std::min (n, str.size () -pos);
    M     = std::min ((size_t)N, (size_t)rlen);
#else
    rlen  = ::min (n, str.size () -pos);
    M     = ::min ((size_t)N, (size_t)rlen);
#endif

    for (index = 0; index < M; ++index)
    {
        switch (str[pos+M-1-index])
        {
            case '0' : array[index] = 0; break;
            case '1' : array[index] = 1; break;
            default  : throwinvalid (); 
        }
    }
    for ( ; index < N; ++index) array[index] = 0;
}
#else /* MSIPL_MEMBER_TEMPLATE */

template <size_t N>
inline
bitset<N>::bitset (const string& str, size_t pos , size_t n )
{
    size_t rlen, M;
    size_t index;

    if (pos > str.size ()) throwrange ();

#ifdef MSIPL_USING_NAMESPACE
    rlen  = std::min (n, str.size () -pos);
    M     = std::min ((size_t)N, (size_t)rlen);
#else
    rlen  = ::min (n, str.size () -pos);
    M     = ::min ((size_t)N, (size_t)rlen);
#endif

    for (index = 0; index < M; ++index)
    {
        switch (str[pos+M-1-index])
        {
            case '0' : array[index] = 0; break;
            case '1' : array[index] = 1; break;
            default  : throwinvalid (); 
        }
    }
    for ( ; index < N; ++index) array[index] = 0;
}

#endif /* MSIPL_MEMBER_TEMPLATE */

#if defined(MSIPL_MEMBER_TEMPLATE) && defined(MSIPL_TFN_DEFARG)
template <size_t N>
template <class charT, class traits>
inline
basic_string<charT, traits, allocator<charT> >
bitset<N>::to_string () const
{
    basic_string<charT, traits, allocator<charT> >  convert ;
    //
    // Allocate space for N chars
    //
    convert.reserve (N); 

    READ_LOCK(_mutex);
    for (size_t index = 0; index < N; index++)
        convert.append (1, (array[N-1-index] ? '1' : '0'));
    return convert;
}

#else  /* !(MSIPL_MEMBER_TEMPLATE) || !(MSIPL_TFN_DEFARG) */

template <size_t N>
inline
string
bitset<N>::to_string () const
{
    string  convert ;
    //
    // Allocate space for N chars
    convert.reserve (N); 
    READ_LOCK(_mutex);
    for (size_t index =0; index< N; index++)
        convert.append (1, (array[N-1-index] ? '1' : '0'));
    return convert;
} 

#endif /* MSIPL_MEMBER_TEMPLATE && MSIPL_TFN_DEFARG */

template<class charT, class traits, size_t N>
inline
basic_istream<charT, traits>&
operator>> (basic_istream<charT, traits>& is, bitset<N>& x)
{
    char                                       ch;
    basic_string<charT, char_traits<charT>,
                 allocator<charT> >            store;
    size_t                                     index = 0;

    store.reserve (N);
    while (!is.eof () && (index < N))
    {
       is.get (ch);
       if (!is) break;
       if (isdigit (ch) && ((ch == '0') || (ch == '1')))
       {
          store.append (1, ch);
          ++index;
       }
       else
       {
          is.putback (ch);
          break;
       }
    }
    if (index == 0) is.setstate (ios_base::failbit);
    if (index < N) store.resize (N, '0');
    x = bitset<N> (store);
    return is;
}

template<class charT, class traits, size_t N>
inline
basic_ostream<charT, traits>&
operator<< (basic_ostream<charT, traits>& os, const bitset<N>& x)
{
    return os << x.to_string ();
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_BITSET_H */

//961210 bkoz add wrapper for alignment