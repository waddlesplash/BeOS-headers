/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_ALGOBASE_H
#define MSIPL_ALGOBASE_H

#include <mcompile.h>
#include MOD_INCLUDE(iterator)
#include MOD_INCLUDE(utility)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Section 25.3.7.1 -- min

template <class T>
inline const T& (min) (const T& a, const T& b)
{
    return b < a ? b : a;
}

template <class T, class Compare>
inline const T& (min) (const T& a, const T& b, Compare comp)
{
    return comp(b, a) ? b : a;
}

// Section 25.3.7.2 -- max

template <class T>
inline const T& (max) (const T& a, const T& b)
{
    return  a < b ? b : a;
}

template <class T, class Compare>
inline const T& (max) (const T& a, const T& b, Compare comp)
{
    return comp (a, b) ? b : a;
}

// Section 25.1.7 -- Mismatch

template <class InputIterator1, class InputIterator2>
inline
pair<InputIterator1, InputIterator2>
mismatch (InputIterator1 first1, InputIterator1 last1,
          InputIterator2 first2)
{
    while (first1 != last1 && *first1 == *first2)
    {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2>(first1, first2);
}

template <class InputIterator1, class InputIterator2,
          class BinaryPredicate>
inline
pair<InputIterator1, InputIterator2>
mismatch (InputIterator1 first1, InputIterator1 last1,
          InputIterator2 first2, BinaryPredicate binary_pred)
{
    while (first1 != last1 && binary_pred (*first1, *first2))
    {
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2> (first1, first2);
}

// Section 25.1.8 -- Equal

template <class InputIterator1, class InputIterator2>
inline bool
equal (InputIterator1 first1, InputIterator1 last1,
       InputIterator2 first2)
{
    return mismatch (first1, last1, first2).first == last1;
}

template <class InputIterator1, class InputIterator2,
          class BinaryPredicate>
inline bool
equal(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, BinaryPredicate binary_pred)
{
    return mismatch (first1, last1, first2, binary_pred).first == last1;
}

// Section 25.2.1.1 -- Copy 

template <class InputIterator, class OutputIterator>
inline
OutputIterator copy (InputIterator first, InputIterator last,
                     OutputIterator result)
{
    while (first != last) *result++ = *first++;
    return result;
}

// Section 25.2.1.2 -- Copy backward 

template <class BidirectionalIterator1, class BidirectionalIterator2>
inline
BidirectionalIterator2 copy_backward (BidirectionalIterator1 first, 
                                      BidirectionalIterator1 last, 
                                      BidirectionalIterator2 result)
{
    while (first != last) *--result = *--last;
    return result;
}

// Section 25.2.2.1 -- swap

template <class T>
inline void swap (T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

// Required for implementing swap_ranges and other functions

template <class ForwardIterator1, class ForwardIterator2, class T>
inline void
__iter_swap (ForwardIterator1 a, ForwardIterator2 b, T*)
{
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template <class ForwardIterator1, class ForwardIterator2>
inline void
iter_swap (ForwardIterator1 a, ForwardIterator2 b)
{
    typedef typename iterator_trait <ForwardIterator1>::value_type
                     Value;
    __iter_swap (a, b, (Value*)0);
}

// Section 25.2.5 -- Fill 

template <class ForwardIterator, class T>
inline
void
fill (ForwardIterator first, ForwardIterator last, const T& value)
{
    while (first != last) *first++ = value;
}

template <class OutputIterator, class Size, class T>
inline
OutputIterator
fill_n (OutputIterator first, Size n, const T& value)
{
    while (n-- > 0) *first++ = value;
    return first;
}

// Section 25.3.8 -- Lexicographical comparison 

template <class InputIterator1, class InputIterator2>
inline
bool
lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 < *first2) return true;
        if (*first2++ < *first1++) return false;
    }
    return first1 == last1 && first2 != last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
inline
bool
lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         Compare comp)
{
    while (first1 != last1 && first2 != last2)
    {
        if (comp (*first1, *first2)) return true;
        if (comp (*first2++, *first1++)) return false;
    }
    return first1 == last1 && first2 != last2;
}

//
// The following functions are provided for 
// Implementation of Numerics Library
//
template <class InputIterator, class OutputIterator, 
          class T, class BinaryFunction>
inline
OutputIterator
__msipl_copy_value (InputIterator first, InputIterator last, 
                    const T& value, OutputIterator result,
                    BinaryFunction binary_func)
{
    while (first != last)
    {
        *result = binary_func (*first, value);
        ++result, ++first;
    }
    return result;
}

template <class InputIterator, class OutputIterator, 
          class T, class BinaryFunction>
inline
OutputIterator
__msipl_copy_value (const T& value, 
                    InputIterator first, InputIterator last, 
                    OutputIterator result, BinaryFunction binary_func)
{
    while (first != last)
    {
        *result = binary_func (value, *first);
        ++result, ++first;
    }
    return result;
}

template <class InputIterator, class OutputIterator, 
          class UnaryFunction>
inline
OutputIterator
__msipl_copy_value (InputIterator first, InputIterator last, 
                    OutputIterator result, UnaryFunction unary_func)
{
    while (first != last)
    {
        *result = unary_func (*first);
        ++result, ++first;
    }
    return result;
}
      
template <class InputIterator1, class InputIterator2, 
          class OutputIterator, class BinaryFunction>
inline
OutputIterator
__msipl_copy_array (InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, OutputIterator result,
                    BinaryFunction binary_func)
{
    while (first1 != last1)
    {
        *result = binary_func (*first1, *first2);
        ++first1, ++first2, ++result;
    }
    return result;
}

template <class InputIterIter, class OutputIterator>
inline
OutputIterator
__msipl_copy_iter (InputIterIter first,  InputIterIter last,
                   OutputIterator result)
{
    while (first != last) 
    {
       *result = *(*first);
       ++first, ++result;
    }
    return result;
}

template <class BidirectIterIter, class BidirectionalIterator>
inline
BidirectionalIterator
__msipl_copy_iter_backward (BidirectIterIter first,  
                            BidirectIterIter last,
                            BidirectionalIterator result)
{
    while (first != last)
    {
        --last, --result;
        *result = *(*last);
    }
    return result;
}

template <class BidirectIterIter, class BidirectionalIterator>
inline
BidirectIterIter
__msipl_iter_copy_backward (BidirectionalIterator first,
                            BidirectionalIterator last,
                            BidirectIterIter result)
{
    while (first != last)
    {
        --last, --result;
        *(*result) = *last;
    }
    return result;
}

template <class BidirectIterIter1, class BidirectIterIter2,
          class BidirectionalIterator, class BinaryFunction>
inline
BidirectIterIter2
__msipl_iter_copy_backward (BidirectionalIterator first,
                            BidirectionalIterator last,
                            BidirectIterIter1 last1,
                            BidirectIterIter2 result,
                            BinaryFunction binary_func)
{
    while (first != last)
    {
        --last, --last1, --result;
        *(*result) = binary_func (*(*last1), *last);
    }
    return result;
}

template <class OutputIterIter, class Size,class T>
inline
void __msipl_fill_iter_n(OutputIterIter first, Size n, const T& value) 
{
   while (n-- > 0) 
   {
      *(*first) = value;
      ++first;
   }
}


#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_ALGOBASE_H */

//961210 bkoz wrapped all headers with pragma options align=native
