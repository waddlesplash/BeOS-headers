/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef  MSIPL_UTILITY_H
#define  MSIPL_UTILITY_H

#include <mcompile.h>

#include  MOD_INCLUDE(iosfwd)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 20.2.1 -- Operators

#ifdef MSIPL_USING_NAMESPACE
// namespace rel_ops {
#endif

template <class T>
inline bool
operator!= (const T& x, const T& y)
{
    return ! (x == y);
}

template <class T>
inline bool
operator> (const T& x, const T& y)
{
    return y < x;
}

template <class T>
inline bool
operator<= (const T& x, const T& y)
{
    return ! (y < x);
}

template <class T>
inline bool
operator>= (const T& x, const T& y)
{
    return ! (x < y);
}

#ifdef MSIPL_USING_NAMESPACE
// }  /* namespace rel_ops */
#endif

// Subclause 20.2.2 -- Tuples

// Section 20.2.2.1 -- Empty
// May have been removed from Draft

//  struct empty {};
//  
//  inline bool operator== (const empty&, const empty&) {
//      return true;
//  }
//  
//  inline bool operator!= (const empty&, const empty&) {
//      return false;
//  }

// Section 20.2.2 -- Pair

template <class T1, class T2>
struct pair {

    typedef T1    first_type;
    typedef T2    second_type;

    T1 first;
    T2 second;

    pair () : first (T1 ()), second (T2 ()) {}
    pair (const T1& a, const T2& b)
    : first (a), second (b) {}

#ifdef MSIPL_MEMBER_TEMPLATE
    template<class U, class V>
    pair (const pair<U, V> &p): first(p.first), second (p.second) {}
#else
    pair (const pair &p): first(p.first), second (p.second) {}
#endif

};

template <class T1, class T2>
inline bool
operator== (const pair<T1, T2>& x, const pair<T1, T2>& y)
{ 
    return x.first == y.first && x.second == y.second; 
}

template <class T1, class T2>
inline bool
operator< (const pair<T1, T2>& x, const pair<T1, T2>& y)
{ 
    return x.first < y.first || (! (y.first < x.first) &&
                                    x.second < y.second); 
}

template <class T1, class T2>
inline pair<T1, T2>
make_pair (const T1& x, const T2& y)
{
    return pair<T1, T2> (x, y);
}

// struct triple -- For Implementation Of Hash Tables

template <class T1, class T2, class T3>
struct triple {
    T1 first;
    T2 second;
    T3 third;
    triple (const T1& a, const T2& b, const T3& c) :
           first (a), second (b), third (c) {}
};

template <class T1, class T2, class T3>
inline bool
operator== (const triple<T1, T2, T3>& x, const triple<T1, T2, T3>& y)
{
    return x.first == y.first && x.second == y.second && x.third == y.third;
}

template <class T1, class T2, class T3>
inline bool
operator< (const triple<T1, T2, T3>& x, const triple<T1, T2, T3>& y)
{
    return x.first < y.first ||
           (! (y.first < x.first) && (x.second < y.second ||
          (! y.second < x.second) && (x.third == y.third)));
}

template <class T1, class T2, class T3>
inline triple<T1, T2, T3>
make_triple (const T1& x, const T2& y, const T3& z)
{
    return triple<T1, T2, T3> (x, y, z);
}

// Section 20.2.2.3 -- Restrictor

template <class T>
class restrictor {
protected:
    T value;
public:
    restrictor (const T& x) : value (x) {}
    friend bool operator== (const restrictor<T>& x, const restrictor<T>& y);
    friend bool operator< (const restrictor<T>& x, const restrictor<T>& y);
};

template <class T>
inline bool
operator== (const restrictor<T>& x, const restrictor<T>& y)
{
    return (x.value == y.value);
}

template <class T>
inline bool
operator< (const restrictor<T>& x, const restrictor<T>& y)
{
    return (x.value < y.value);
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_UTILITY_H */

//961210 bkoz added alignment wrapper
