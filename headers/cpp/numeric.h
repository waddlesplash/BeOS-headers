/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_NUMERIC_H
#define MSIPL_NUMERIC_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Section 26.4 -- Generic numeric operations

// Section 26.4.1 -- Accumulate

template <class InputIterator, class T>
inline
T accumulate (InputIterator first, InputIterator last, T init)
{
    while (first != last) 
        init = init + *first++;
    return init;
}

template <class InputIterator, class T, class BinaryOperation>
inline
T accumulate (InputIterator first, InputIterator last, T init,
             BinaryOperation binary_op)
{
    while (first != last) 
        init = binary_op (init, *first++);
    return init;
}

// Section 26.4.2 -- inner product

template <class InputIterator1, class InputIterator2, class T>
inline
T inner_product (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, T init)
{
    while (first1 != last1) 
        init = init + (*first1++ * *first2++);
    return init;
}

template <class InputIterator1, class InputIterator2, class T,
          class BinaryOperation1, class BinaryOperation2>
inline
T inner_product (InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, T init,
                 BinaryOperation1 binary_op1,
                 BinaryOperation2 binary_op2)
{
    while (first1 != last1) 
        init = binary_op1 (init, binary_op2 (*first1++, *first2++));
    return init;
}

template <class InputIterator, class OutputIterator, class T>
inline
OutputIterator __partial_sum (InputIterator first, InputIterator last,
                             OutputIterator result, T*)
{
    T value = *first;
    while (++first != last)
    {
        value = value + *first;
        *++result = value;
    }
    return ++result;
}

// Section 26.4.3 -- Partial Sum

template <class InputIterator, class OutputIterator>
inline
OutputIterator partial_sum (InputIterator first, InputIterator last,
                            OutputIterator result)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    if (first == last) return result;
    *result = *first;
    return __partial_sum (first, last, result, (Value*)0);
}

template <class InputIterator, class OutputIterator, class T,
          class BinaryOperation>
inline
OutputIterator __partial_sum (InputIterator first, InputIterator last,
                              OutputIterator result, T*,
                              BinaryOperation binary_op)
{
    T value = *first;
    while (++first != last)
    {
        value = binary_op (value, *first);
        *++result = value;
    }
    return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
inline
OutputIterator
partial_sum (InputIterator first, InputIterator last,
             OutputIterator result, BinaryOperation binary_op)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    if (first == last) return result;
    *result = *first;
    return __partial_sum (first, last, result,
                          (Value*)0, binary_op);
}

template <class InputIterator, class OutputIterator, class T>
inline
OutputIterator
__adjacent_difference (InputIterator first, InputIterator last, 
                       OutputIterator result, T*)
{
    T value = *first;
    while (++first != last)
    {
        T tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

// Section 26.4.4 -- Adjacent Difference

template <class InputIterator, class OutputIterator>
inline
OutputIterator
adjacent_difference (InputIterator first, InputIterator last, 
                     OutputIterator result)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    if (first == last) return result;
    *result = *first;
    return __adjacent_difference (first, last, result, (Value*)0);
}

template <class InputIterator, class OutputIterator, class T, 
          class BinaryOperation>
inline
OutputIterator
__adjacent_difference (InputIterator first, InputIterator last, 
                       OutputIterator result, T*,
                       BinaryOperation binary_op)
{
    T value = *first;
    while (++first != last)
    {
        T tmp = *first;
        *++result = binary_op (tmp, value);
        value = tmp;
    }
    return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryOperation>
inline
OutputIterator
adjacent_difference (InputIterator first, InputIterator last,
                     OutputIterator result,
                     BinaryOperation binary_op)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    if (first == last) return result;
    *result = *first;
    return __adjacent_difference (first, last, result, (Value*)0,
                                  binary_op);
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_NUMERIC_H */

//961210 bkoz added alignment wrapper