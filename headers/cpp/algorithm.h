/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */

/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_ALGORITHM_H
#define MSIPL_ALGORITHM_H

#include <mcompile.h>

#include MOD_INCLUDE(algobase)
#include MOD_INCLUDE(heap)
#include MOD_INCLUDE(mmemory)  //961216 ah
#include MOD_INCLUDE(mutex)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 25.1 -- Non-modifying sequence operations

// Section 25.1.1 -- For each

template <class InputIterator, class Function>
inline
Function
for_each (InputIterator first, InputIterator last, Function f)
{
    while (first != last) f (*first++);
    return f;
}

// Section 25.1.2 -- Find

template <class InputIterator, class T>
inline
InputIterator find (InputIterator first, InputIterator last,
                    const T& value)
{
    while (first != last && *first != value) ++first;
    return first;
}

template <class InputIterator, class Predicate>
inline
InputIterator find_if (InputIterator first, InputIterator last,
                       Predicate pred)
{
    while (first != last && !pred (*first)) ++first;
    return first;
}


// Section 25.1.3  Find End

template <class ForwardIterator1, class ForwardIterator2>
inline
ForwardIterator1
__find_end (ForwardIterator1 first1, 
            ForwardIterator1 last1, ForwardIterator2 first2, 
            ForwardIterator2 last2)
{

     typedef  typename iterator_trait<ForwardIterator1>::distance_type
                       Distance;
     Distance d1 = 0;
     Distance d2 = 0;
     d1 = distance (first1, last1);
     d2 = distance (first2, last2);

     if (d1 < d2) return last1;

     ForwardIterator1 current1 = first1;
     ForwardIterator1 iter_save = last1;

     while ((current1 = search (first1, last1, first2, last2)) != last1)
     {
           iter_save =  current1;
           first1 = iter_save;
           advance (first1, d2);
     }

     return iter_save;
}

template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 
find_end (ForwardIterator1 first1, ForwardIterator1 last1, 
          ForwardIterator2 first2, ForwardIterator2 last2)
{
    return __find_end (first1, last1, first2, last2);
                       
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline
ForwardIterator1
__find_end (ForwardIterator1 first1, 
            ForwardIterator1 last1, ForwardIterator2 first2, 
            ForwardIterator2 last2, BinaryPredicate binary_pred)
{
    typedef  typename iterator_trait<ForwardIterator1>::distance_type
                       Distance;
    Distance d1 = 0;
    d1 = distance (first1, last1);
    Distance d2 = 0;
    d2 = distance (first2, last2);

    ForwardIterator1 result = last1;

    if (d1 < d2) return result;

     ForwardIterator1 current1 = first1;
     ForwardIterator1 iter_save = last1;

     while ((current1 = search (first1, last1, first2, last2, binary_pred)) 
                != last1)
     {
           iter_save =  current1;
           first1 = iter_save;
           advance (first1, d2);
     }

     return iter_save;
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline ForwardIterator1 
find_end (ForwardIterator1 first1, ForwardIterator1 last1, 
          ForwardIterator2 first2, ForwardIterator2 last2, 
          BinaryPredicate binary_pred)
{
    return __find_end (first1, last1, first2,
                       last2, binary_pred);
}

// Section 25.1.4 -- Find First

template <class ForwardIterator1, class ForwardIterator2>
inline
ForwardIterator1
find_first_of (ForwardIterator1 first1, ForwardIterator1 last1,         /*mm 970916*/
               ForwardIterator2 first2, ForwardIterator2 last2)
{
    ForwardIterator1   current1 = first1;
    ForwardIterator2   current2 = first2;

    while (current1 != last1)
    {
        while (current2 != last2)
            if (*current1 == *current2++)
                return current1;
        ++current1;
        current2 = first2;
    }
    return last1;
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline
ForwardIterator1
find_first_of (ForwardIterator1 first1, ForwardIterator1 last1,  /* mm 970916 */
               ForwardIterator2 first2, ForwardIterator2 last2,
               BinaryPredicate binary_pred)
{
    ForwardIterator1   current1 = first1;
    ForwardIterator2   current2 = first2;

    while (current1 != last1)
    {
        while (current2 != last2)
            if (binary_pred (*current1, *current2++))
                return current1;
        ++current1;
        current2 = first2;
    }
    return last1;
}


// Section 25.1.5 -- Adjacent find

template <class ForwardIterator>
inline
ForwardIterator
adjacent_find (ForwardIterator first, ForwardIterator last)
{
    if (first == last) return last;
    ForwardIterator next = first;
    while (++next != last)
    {
        if (*first == *next) return first;
        first = next;
    }
    return last;
}

template <class ForwardIterator, class BinaryPredicate>
inline
ForwardIterator
adjacent_find (ForwardIterator first, ForwardIterator last,
               BinaryPredicate binary_pred)
{
    if (first == last) return last;
    ForwardIterator next = first;
    while (++next != last)
    {
        if (binary_pred (*first, *next)) return first;
        first = next;
    }
    return last;
}

// Section 25.1.6 -- Count

template <class InputIterator, class T>
inline
ptrdiff_t												//961112 bkoz hack around . . .
//typename iterator_trait<InputIterator>::distance_type	//961112 . . .this
count (InputIterator first, InputIterator last, const T& value)
{
    iterator_trait <InputIterator>::distance_type n = 0;
    while (first != last) 
        if (*first++ == value) ++n;
    return n;
}

template <class InputIterator, class Predicate>
inline
ptrdiff_t												//961112 bkoz hack around . . .
//typename iterator_trait<InputIterator>::distance_type	//961112 . . .this
count_if (InputIterator first, InputIterator last, Predicate pred)
{
    iterator_trait <InputIterator>::distance_type n = 0;
    while (first != last)
        if (pred (*first++)) ++n;
    return n;
}

// Section 25.1.7 -- Mismatch -- in algobase.h
// Section 25.1.8 -- Equal -- in algobase.h

// Section 25.1.9 -- Search

template <class ForwardIterator1, class ForwardIterator2>
inline
ForwardIterator1
__search (ForwardIterator1 first1, ForwardIterator1 last1,
          ForwardIterator2 first2, ForwardIterator2 last2)
{
    typedef  typename iterator_trait<ForwardIterator1>::distance_type
                       Distance1;
    typedef  typename iterator_trait<ForwardIterator2>::distance_type
                       Distance2;
    Distance1 d1 = 0;
    d1 = distance (first1, last1);
    Distance2 d2 = 0;
    d2 = distance (first2, last2);

    if (d1 < d2) return last1;

    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;

    while (current2 != last2)
    {
        if (*current1++ != *current2++)
            if (d1-- == d2)
                return last1;
            else 
            {
                current1 = ++first1;
                current2 = first2;
            }
    }
    return (current2 == last2) ? first1 : last1;
}

template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1
search (ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2)
{
    return __search (first1, last1, first2, last2);
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline
ForwardIterator1
__search (ForwardIterator1 first1, ForwardIterator1 last1,
          ForwardIterator2 first2, ForwardIterator2 last2,
          BinaryPredicate binary_pred)
{
    typedef  typename iterator_trait<ForwardIterator1>::distance_type
                       Distance1;
    typedef  typename iterator_trait<ForwardIterator2>::distance_type
                       Distance2;
    Distance1 d1 = 0;
    d1 = distance (first1, last1);
    Distance2 d2 = 0;
    d2 = distance (first2, last2);

    if (d1 < d2) return last1;

    ForwardIterator1 current1 = first1;
    ForwardIterator2 current2 = first2;

    while (current2 != last2)
    {
        if (!binary_pred (*current1++, *current2++))
            if (d1-- == d2)
                return last1;
            else 
            {
                current1 = ++first1;
                current2 = first2;
            }
    }
    return (current2 == last2) ? first1 : last1;
}

template <class ForwardIterator1, class ForwardIterator2,
          class BinaryPredicate>
inline ForwardIterator1
search (ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2,
        BinaryPredicate binary_pred) 
{
    return __search (first1, last1, first2, last2, binary_pred);
                     
}

template <class ForwardIterator, class Size, class T>
inline
ForwardIterator __search_n (ForwardIterator first, ForwardIterator last,
                            Size sz, const T& value)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    Distance d = 0;
    d = distance (first, last);

    if (d < sz) return last;


    ForwardIterator current = first;
    Size sz_cur = sz;

    while (sz_cur--)
    {
        if (*current++ != value)
            if (d-- == sz)
                return last;
            else 
            {
                current = ++first;
            }
    }
    return (sz_cur) ? first : last;
}

template <class ForwardIterator, class Size, class T>
inline
ForwardIterator search_n (ForwardIterator first, ForwardIterator last,
                          Size sz, const T& value)
{
    return __search_n (first, last, sz, value);

}

template <class ForwardIterator, class Size, class T,
          class BinaryPredicate>
inline
ForwardIterator __search_n (ForwardIterator first, ForwardIterator last,
                            Size sz, const T& value, BinaryPredicate b_pred)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    Distance d = distance (first, last);

    if (d < sz) return last;

    ForwardIterator current = first;
    Size sz_cur = sz;

    while (sz_cur--)
        if (!b_pred (*current++, value))
            if (d-- == sz)
                return last;
            else 
            {
                current = ++first;
            }
    return (sz_cur) ? first : last;
}

template <class ForwardIterator, class Size, class T,
          class BinaryPredicate>
inline
ForwardIterator search_n (ForwardIterator first, ForwardIterator last,
                          Size sz, const T& value, BinaryPredicate b_pred)
{
    return __search_n (first, last, sz, value, b_pred);

}

// Subclause 25.2 -- Mutating sequence operations

// Section 25.2.1.1 -- Copy -- in algobase.h
// Section 25.2.1.2 -- Copy backward -- in algobase.h
// Section 25.2.2.1 -- Swap -- in algobase.h

// Section 25.2.2.2 -- Swap ranges

template <class ForwardIterator1, class ForwardIterator2>
inline
ForwardIterator2
swap_ranges (ForwardIterator1 first1, ForwardIterator1 last1,
             ForwardIterator2 first2) 
{
    while (first1 != last1) iter_swap (first1++, first2++);
    return first2;
}

// Section 25.2.3 -- Transform

template <class InputIterator, class OutputIterator, class UnaryOperation>
inline
OutputIterator transform (InputIterator first, InputIterator last,
                          OutputIterator result, UnaryOperation op)
{
    while (first != last) *result++ = op (*first++);
    return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class BinaryOperation>
inline
OutputIterator transform (InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, OutputIterator result,
                          BinaryOperation binary_op)
{
    while (first1 != last1) *result++ = binary_op (*first1++, *first2++);
    return result;
}

// Section 25.2.4.1 -- Replace

template <class ForwardIterator, class T>
inline
void replace (ForwardIterator first, ForwardIterator last,
              const T& old_value, const T& new_value)
{
    while (first != last)
    {
        if (*first == old_value) *first = new_value;
        ++first;
    }
}

template <class ForwardIterator, class Predicate, class T>
inline
void replace_if (ForwardIterator first, ForwardIterator last,
                 Predicate pred, const T& new_value)
{
    while (first != last)
    {
        if (pred (*first)) *first = new_value;
        ++first;
    }
}

// Section 25.2.4.2 -- Replace copy

template <class InputIterator, class OutputIterator, class T>
inline
OutputIterator replace_copy (InputIterator first, InputIterator last,
                             OutputIterator result, const T& old_value,
                             const T& new_value)
{
    while (first != last)
    {
        *result++ = *first == old_value ? new_value : *first;
        ++first;
    }
    return result;
}

template <class Iterator, class OutputIterator, class Predicate, class T>
inline
OutputIterator replace_copy_if (Iterator first, Iterator last,
                                OutputIterator result, Predicate pred,
                                const T& new_value)
{
    while (first != last)
    {
        *result++ = pred (*first) ? new_value : *first;
        ++first;
    }
    return result;
}

// Section 25.2.5 -- Fill -- in algobase.h

// Section 25.2.6 -- Generate

template <class ForwardIterator, class Generator>
inline
void generate (ForwardIterator first, ForwardIterator last, Generator gen)
{
    while (first != last) *first++ = gen ();
}

template <class OutputIterator, class Size, class Generator>
inline
OutputIterator generate_n (OutputIterator first, Size n, Generator gen)
{
    while (n-- > 0) *first++ = gen ();
    return first;
}

// Section 25.2.7.2 -- Remove copy

template <class InputIterator, class OutputIterator, class T>
inline
OutputIterator remove_copy (InputIterator first, InputIterator last,
                            OutputIterator result, const T& value)
{
    while (first != last)
    {
        if (*first != value) *result++ = *first;
        ++first;
    }
    return result;
}

template <class InputIterator, class OutputIterator, class Predicate>
inline
OutputIterator remove_copy_if (InputIterator first, InputIterator last,
                               OutputIterator result, Predicate pred)
{
    while (first != last)
    {
        if (!pred (*first)) *result++ = *first;
        ++first;
    }
    return result;
}

// Section 25.2.7.1 -- Remove

template <class ForwardIterator, class T>
inline
ForwardIterator remove (ForwardIterator first, ForwardIterator last,
                        const T& value)
{
    first = find (first, last, value);
    ForwardIterator next = first;
    return first == last ? first
                         : remove_copy (++next, last, first, value);
}

template <class ForwardIterator, class Predicate>
inline
ForwardIterator remove_if (ForwardIterator first, ForwardIterator last,
                           Predicate pred)
{
    first = find_if (first, last, pred);
    ForwardIterator next = first;
    return first == last ? first
                         : remove_copy_if (++next, last, first, pred);
}

// Section 25.2.8.2 -- Unique copy

template <class InputIterator, class ForwardIterator>
inline
ForwardIterator
__unique_copy (InputIterator first, InputIterator last,
               ForwardIterator result, forward_iterator_tag)
{
    *result = *first;
    while (++first != last)
        if (*result != *first) *++result = *first;
    return ++result;
}

template <class InputIterator, class BidirectionalIterator>
inline BidirectionalIterator
__unique_copy (InputIterator first, InputIterator last,
               BidirectionalIterator result, 
               bidirectional_iterator_tag)
{
    return __unique_copy (first, last, result, forward_iterator_tag ());
}

template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
__unique_copy (InputIterator first, InputIterator last,
               RandomAccessIterator result, 
               random_access_iterator_tag)
{
    return __unique_copy (first, last, result, forward_iterator_tag ());
}

template <class InputIterator, class OutputIterator, class T>
inline
OutputIterator __unique_copy (InputIterator first, InputIterator last,
                              OutputIterator result, T*)
{
    T value = *first;
    *result = value;
    while (++first != last)
        if (value != *first)
        {
            value = *first;
            *++result = value;
        }
    return ++result;
}

template <class InputIterator, class OutputIterator>
inline OutputIterator
__unique_copy (InputIterator first, InputIterator last,
               OutputIterator result, output_iterator_tag)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    return __unique_copy (first, last, result, (Value*)0);
}

template <class InputIterator, class OutputIterator>
inline OutputIterator
unique_copy (InputIterator first, InputIterator last,
             OutputIterator result)
{
    typedef typename iterator_trait <OutputIterator>::iterator_category
                     Category;
    if (first == last) return result;
    return __unique_copy (first, last, result, Category ());
}

template <class InputIterator, class ForwardIterator,
          class BinaryPredicate>
inline
ForwardIterator
__unique_copy (InputIterator first, InputIterator last,
               ForwardIterator result, BinaryPredicate binary_pred,
               forward_iterator_tag)
{
    *result = *first;
    while (++first != last)
        if (!binary_pred (*result, *first)) *++result = *first;
    return ++result;
}

template <class InputIterator, class BidirectionalIterator,
          class BinaryPredicate>
inline BidirectionalIterator
__unique_copy (InputIterator first, InputIterator last,
               BidirectionalIterator result, 
               BinaryPredicate binary_pred,
               bidirectional_iterator_tag)
{
    return __unique_copy (first, last, result, binary_pred,
                          forward_iterator_tag ());
}

template <class InputIterator, class RandomAccessIterator,
          class BinaryPredicate>
inline RandomAccessIterator
__unique_copy (InputIterator first, InputIterator last,
               RandomAccessIterator result, BinaryPredicate binary_pred,
               random_access_iterator_tag)
{
    return __unique_copy (first, last, result, binary_pred, 
                          forward_iterator_tag ());
}

template <class InputIterator, class OutputIterator,
          class BinaryPredicate, class T>
inline
OutputIterator __unique_copy (InputIterator first, InputIterator last,
                              OutputIterator result,
                              BinaryPredicate binary_pred, T*)
{
    T value = *first;
    *result = value;
    while (++first != last)
        if (!binary_pred (value, *first))
        {
            value = *first;
            *++result = value;
        }
    return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator
__unique_copy (InputIterator first, InputIterator last,
               OutputIterator result, BinaryPredicate binary_pred,
               output_iterator_tag)
{
    typedef typename iterator_trait <InputIterator>::value_type
                     Value;
    return __unique_copy (first, last, result, binary_pred,
                          (Value*)0);
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator
unique_copy (InputIterator first, InputIterator last,
             OutputIterator result, BinaryPredicate binary_pred)
{
    typedef typename iterator_trait <OutputIterator>::iterator_category
                     Category;
    if (first == last) return result;
    return __unique_copy (first, last, result, binary_pred,
                          Category ());
}

// Section 25.2.8.1 -- Unique 

template <class ForwardIterator>
inline
ForwardIterator unique (ForwardIterator first, ForwardIterator last)
{
    first = adjacent_find (first, last);
    return unique_copy (first, last, first);
}

template <class ForwardIterator, class BinaryPredicate>
inline
ForwardIterator unique (ForwardIterator first, ForwardIterator last,
                        BinaryPredicate binary_pred)
{
    first = adjacent_find (first, last, binary_pred);
    return unique_copy (first, last, first, binary_pred);
}

// Section 25.2.9.1 -- Reverse

template <class BidirectionalIterator>
inline
void __reverse (BidirectionalIterator first, BidirectionalIterator last, 
                bidirectional_iterator_tag)
{
    while (true)
        if (first == last || first == --last)
            return;
        else
            iter_swap (first++, last);
}

template <class RandomAccessIterator>
inline
void __reverse (RandomAccessIterator first, RandomAccessIterator last,
                random_access_iterator_tag)
{
    while (first < last) iter_swap (first++, --last);
}

template <class BidirectionalIterator>
inline void reverse (BidirectionalIterator first,
                     BidirectionalIterator last)
{
    typedef typename iterator_trait <BidirectionalIterator>::
                     iterator_category            Category;
    __reverse (first, last, Category ());
}

// Section 25.2.9.2 -- Reverse copy

template <class BidirectionalIterator, class OutputIterator>
inline
OutputIterator reverse_copy (BidirectionalIterator first,
                             BidirectionalIterator last,
                             OutputIterator result)
{
    while (first != last) *result++ = *--last;
    return result;
}

// Section 25.2.10.1 -- Rotate

template <class ForwardIterator, class Distance>
inline
void __rotate (ForwardIterator first, ForwardIterator middle,
               ForwardIterator last, Distance*, forward_iterator_tag)
{
    for (ForwardIterator i = middle; ;)
    {
        iter_swap (first++, i++);
        if (first == middle)
        {
            if (i == last) return;
            middle = i;
        } else if (i == last)
            i = middle;
    }
}

template <class BidirectionalIterator, class Distance>
inline
void
__rotate (BidirectionalIterator first, BidirectionalIterator middle,
          BidirectionalIterator last, Distance*,
          bidirectional_iterator_tag)
{
    reverse (first, middle);
    reverse (middle, last);
    reverse (first, last);
}

template <class EuclideanRingElement>
inline
EuclideanRingElement
__gcd (EuclideanRingElement m, EuclideanRingElement n)
{
    while (n != 0)
    {
        EuclideanRingElement t = m % n;
        m = n;
        n = t;
    }
    return m;
}

template <class RandomAccessIterator, class Distance, class T>
inline
void __rotate_cycle (RandomAccessIterator first, RandomAccessIterator last,
                     RandomAccessIterator initial, Distance shift, T*)
{
    T value = *initial;
    RandomAccessIterator ptr1 = initial;
    RandomAccessIterator ptr2 = ptr1 + shift;
    while (ptr2 != initial)
    {
        *ptr1 = *ptr2;
        ptr1 = ptr2;
        if (last - ptr2 > shift)
            ptr2 += shift;
        else
            ptr2 = first + (shift - (last - ptr2));
    }
    *ptr1 = value;
}

template <class RandomAccessIterator, class Distance>
inline
void __rotate (RandomAccessIterator first, RandomAccessIterator middle,
               RandomAccessIterator last, Distance*,
               random_access_iterator_tag)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    Distance n = __gcd (last - first, middle - first);
    while (n--)
        __rotate_cycle (first, last, first + n, middle - first,
                        (Value*)0);
}

template <class ForwardIterator>
inline void rotate (ForwardIterator first, ForwardIterator middle,
                    ForwardIterator last)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<ForwardIterator>::iterator_category
                       Category;
    if (first == middle || middle == last) return;
    __rotate (first, middle, last, (Distance*)0, Category ());
}

// Section 25.2.10.2 -- Rotate copy

template <class ForwardIterator, class OutputIterator>
inline
OutputIterator
rotate_copy (ForwardIterator first, ForwardIterator middle,
             ForwardIterator last, OutputIterator result)
{
    return copy (first, middle, copy (middle, last, result));
}

// inlined code for the function "long_random"
// speeds up compilation times significantly on UNIX machines
 
// Section 25.2.11 -- Random Shuffle
 
class __random_generator {
protected:
    unsigned long table[55];
    size_t index1;
    size_t index2;
    DEC_MUTEX(_mutex)
public:
    unsigned long operator () (unsigned long limit)
    {
        LOCK(mut_block, _mutex);
        index1 = (index1 + 1) % 55;
        index2 = (index2 + 1) % 55;
        table[index1] = table[index1] - table[index2];
        return table[index1] % limit;
    }
    void seed (unsigned long j);
    __random_generator (unsigned long j) { seed (j); }

    ~__random_generator() { REMOVE(_mutex); }
};
 
// #define MSIPL_SEED_RANDOM 161803398
extern __random_generator __msipl_rd;

inline unsigned long
__long_random (unsigned long limit)
{
    return __msipl_rd (limit);
}

template <class RandomAccessIterator>
inline
void __random_shuffle (RandomAccessIterator first,
                       RandomAccessIterator last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        iter_swap (i, first + Distance (__long_random ((i - first) + 1)));
}

template <class RandomAccessIterator>
inline void random_shuffle (RandomAccessIterator first,
                            RandomAccessIterator last)
{
    __random_shuffle (first, last);
}

template <class RandomAccessIterator, class RandomNumberGenerator>
inline
void random_shuffle (RandomAccessIterator first, RandomAccessIterator last,
                     RandomNumberGenerator rand)
{
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        iter_swap (i, first + rand ((i - first) + 1));
}

// Section 25.2.12.1 -- partition

template <class BidirectionalIterator, class Predicate>
inline
BidirectionalIterator partition (BidirectionalIterator first,
                                 BidirectionalIterator last,
                                 Predicate pred)
{
    while (true)
    {
        while (true)
            if (first == last)
                return first;
            else if (pred (*first))
                ++first;
            else
                break;
        --last;
        while (true)
            if (first == last)
                return first;
            else if (!pred (*last))
                --last;
            else
                break;
        iter_swap (first, last);
        ++first;
    }
}

// Section 25.2.12.2 -- stable partition

template <class ForwardIterator, class Predicate, class Distance>
inline
ForwardIterator
__inplace_stable_partition (ForwardIterator first,
                            ForwardIterator last,
                            Predicate pred, Distance len)
{
    if (len == 1) return pred (*first) ? last : first;
    ForwardIterator middle = first;
    advance (middle, len / 2);
    ForwardIterator 
        first_cut = __inplace_stable_partition (first, middle, pred,
                                                len / 2);
    ForwardIterator 
        second_cut = __inplace_stable_partition (middle, last, pred,
                                                 len - len / 2);
    rotate (first_cut, middle, second_cut);
    len = distance (middle, second_cut);
    advance (first_cut, len);
    return first_cut;
}

template <class ForwardIterator, class Pointer, class Predicate,
          class Distance, class T>
inline
ForwardIterator
__stable_partition_adaptive (ForwardIterator first,
                             ForwardIterator last,
                             Predicate pred, Distance len,
                             Pointer buffer,
                             Distance buffer_size,
                             Distance& fill_pointer, T*)
{
    if (len <= buffer_size)
    {
        len = 0;
        ForwardIterator result1 = first;
        Pointer result2 = buffer;
        while (first != last && len < fill_pointer)
            if (pred (*first))
                *result1++ = *first++;
            else 
            {
                *result2++ = *first++;
                ++len;
            }
        if (first != last)
        {
            raw_storage_iterator<Pointer, T> result3(result2);
            while (first != last)           
                if (pred (*first))
                    *result1++ = *first++;
                else
                {
                    *result3++ = *first++;
                    ++len;
                }
            fill_pointer = len;
        }
        copy (buffer, buffer + len, result1);
        return result1;
    }
    ForwardIterator middle = first;
    advance (middle, len / 2);
    ForwardIterator first_cut = __stable_partition_adaptive
       (first, middle, pred, len / 2, buffer, buffer_size, fill_pointer, 
        (T*)0);
    ForwardIterator second_cut = __stable_partition_adaptive
       (middle, last, pred, len - len / 2, buffer, buffer_size, 
         fill_pointer, (T*)0);
    rotate (first_cut, middle, second_cut);
    len = distance (middle, second_cut);
    advance (first_cut, len);
    return first_cut;
}

template <class ForwardIterator, class Predicate, class Pointer,
          class Distance>
inline
ForwardIterator
__stable_partition (ForwardIterator first, ForwardIterator last,
                    Predicate pred, Distance len,
                    pair<Pointer, Distance> p)
{
    typedef typename iterator_trait <ForwardIterator>::value_type
                     Value;
    if (p.first == 0)
        return __inplace_stable_partition (first, last, pred, len);
    Distance fill_pointer = 0;
    ForwardIterator result = 
        __stable_partition_adaptive (first, last, pred, len,
                   p.first, p.second, fill_pointer, (Value*)0); 
    destroy (p.first, p.first + fill_pointer);
    return_temporary_buffer (p.first);
    return result;
}

template <class ForwardIterator, class Predicate, class Distance>
inline ForwardIterator
__stable_partition_aux (ForwardIterator first, ForwardIterator last, 
                        Predicate pred, Distance*)
{
    typedef typename iterator_trait <ForwardIterator>::value_type
                     Value;
    Distance len = distance (first, last);
    return __stable_partition (first, last, pred, len,
                               get_temporary_buffer (len, (Value*)0));
}

template <class ForwardIterator, class Predicate>
inline ForwardIterator
stable_partition (ForwardIterator first,
                  ForwardIterator last, Predicate pred)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    return __stable_partition_aux (first, last, pred, (Distance*)0);
}

// Subclause 25.3 -- Sorting and related algorithms

template <class RandomAccessIterator, class T>
inline
RandomAccessIterator
__unguarded_partition (RandomAccessIterator first, 
                       RandomAccessIterator last, T pivot)
{
    while (1)
    {
        while (*first < pivot) ++first;
        --last;
        while (pivot < *last) --last;
        if (! (first < last)) return first;
        iter_swap (first, last);
        ++first;
    }
}    

template <class RandomAccessIterator, class T, class Compare>
inline
RandomAccessIterator
__unguarded_partition (RandomAccessIterator first, 
                       RandomAccessIterator last, 
                       T pivot, Compare comp)
{
    while (1)
    {
        while (comp (*first, pivot)) ++first;
        --last;
        while (comp (pivot, *last)) --last;
        if (! (first < last)) return first;
        iter_swap (first, last);
        ++first;
    }
}

const int __stl_threshold = 16;

template <class T>
inline const T& __median (const T& a, const T& b, const T& c)
{
    if (a < b)
        if (b < c)
            return b;
        else if (a < c)
            return c;
        else
            return a;
    else if (a < c)
        return a;
    else if (b < c)
        return c;
    else
        return b;
}

template <class T, class Compare>
inline const T&
__median (const T& a, const T& b, const T& c, Compare comp)
{
    if (comp (a, b))
        if (comp (b, c))
            return b;
        else if (comp (a, c))
            return c;
        else
            return a;
    else if (comp (a, c))
        return a;
    else if (comp (b, c))
        return c;
    else
        return b;
}

template <class RandomAccessIterator, class T>
inline
void __quick_sort_loop_aux (RandomAccessIterator first,
                            RandomAccessIterator last, T*)
{
    while (last - first > __stl_threshold)
    {
        RandomAccessIterator cut = __unguarded_partition
            (first, last, T (__median (*first, * (first + (last - first)/2),
                                     *(last - 1))));
        if (cut - first >= last - cut)
        {
            __quick_sort_loop (cut, last);
            last = cut;
        } else 
        {
            __quick_sort_loop (first, cut);
            first = cut;
        }
    }
}

template <class RandomAccessIterator>
inline void __quick_sort_loop (RandomAccessIterator first,
                               RandomAccessIterator last)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __quick_sort_loop_aux (first, last, (Value*)0);
}

template <class RandomAccessIterator, class T, class Compare>
inline
void __quick_sort_loop_aux (RandomAccessIterator first, 
                            RandomAccessIterator last, T*, Compare comp)
{
    while (last - first > __stl_threshold)
    {
        RandomAccessIterator cut = __unguarded_partition
            (first, last, T (__median (*first, * (first + (last - first)/2), 
                                   *(last - 1), comp)), comp);
        if (cut - first >= last - cut)
        {
            __quick_sort_loop (cut, last, comp);
            last = cut;
        } else 
        {
            __quick_sort_loop (first, cut, comp);
            first = cut;
        }
    }
}

template <class RandomAccessIterator, class Compare>
inline void __quick_sort_loop (RandomAccessIterator first, 
                               RandomAccessIterator last, Compare comp)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __quick_sort_loop_aux (first, last, (Value*)0, comp);
}

template <class RandomAccessIterator, class T>
inline
void __unguarded_linear_insert (RandomAccessIterator last, T value)
{
    RandomAccessIterator next = last;
    --next;
    while (value < *next)
    {
        *last = *next;
        last = next--;
    }
    *last = value;
}

template <class RandomAccessIterator, class T, class Compare>
inline
void __unguarded_linear_insert (RandomAccessIterator last, T value, 
                                Compare comp)
{
    RandomAccessIterator next = last;
    --next;  
    while (comp (value , *next))
    {
        *last = *next;
        last = next--;
    }
    *last = value;
}

template <class RandomAccessIterator, class T>
inline void __linear_insert (RandomAccessIterator first, 
                             RandomAccessIterator last, T*)
{
    T value = *last;
    if (value < *first)
    {
        copy_backward (first, last, last + 1);
        *first = value;
    } else
        __unguarded_linear_insert (last, value);
}

template <class RandomAccessIterator, class T, class Compare>
inline void
__linear_insert (RandomAccessIterator first, 
                 RandomAccessIterator last, T*, Compare comp)
{
    T value = *last;
    if (comp (value, *first))
    {
        copy_backward (first, last, last + 1);
        *first = value;
    } else
        __unguarded_linear_insert (last, value, comp);
}

template <class RandomAccessIterator>
inline
void
__insertion_sort (RandomAccessIterator first, RandomAccessIterator last)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    if (first == last) return; 
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        __linear_insert (first, i, (Value*)0);
}

template <class RandomAccessIterator, class Compare>
inline
void __insertion_sort (RandomAccessIterator first,
                       RandomAccessIterator last, Compare comp)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    if (first == last) return;
    for (RandomAccessIterator i = first + 1; i != last; ++i)
        __linear_insert (first, i, (Value*)0, comp);
}

template <class RandomAccessIterator, class T>
inline
void __unguarded_insertion_sort_aux (RandomAccessIterator first, 
                                     RandomAccessIterator last, T*)
{
    for (RandomAccessIterator i = first; i != last; ++i)
        __unguarded_linear_insert (i, T (*i));
}

template <class RandomAccessIterator>
inline void __unguarded_insertion_sort (RandomAccessIterator first, 
                                        RandomAccessIterator last)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __unguarded_insertion_sort_aux (first, last, (Value*)0);
}

template <class RandomAccessIterator, class T, class Compare>
inline
void __unguarded_insertion_sort_aux (RandomAccessIterator first, 
                                     RandomAccessIterator last,
                                     T*, Compare comp)
{
    for (RandomAccessIterator i = first; i != last; ++i)
        __unguarded_linear_insert (i, T (*i), comp);
}

template <class RandomAccessIterator, class Compare>
inline void __unguarded_insertion_sort (RandomAccessIterator first, 
                                        RandomAccessIterator last,
                                        Compare comp)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __unguarded_insertion_sort_aux (first, last, (Value*)0, comp);
}

template <class RandomAccessIterator>
inline
void __final_insertion_sort (RandomAccessIterator first, 
                             RandomAccessIterator last)
{
    if (last - first > __stl_threshold)
    {
        __insertion_sort (first, first + __stl_threshold);
        __unguarded_insertion_sort (first + __stl_threshold, last);
    } else
        __insertion_sort (first, last);
}

template <class RandomAccessIterator, class Compare>
inline
void __final_insertion_sort (RandomAccessIterator first, 
                             RandomAccessIterator last, Compare comp)
{
    if (last - first > __stl_threshold)
    {
        __insertion_sort (first, first + __stl_threshold, comp);
        __unguarded_insertion_sort (first + __stl_threshold, last, comp);
    } else
        __insertion_sort (first, last, comp);
}

// Section 25.3.1 -- Sorting

// Section 25.3.1.1 -- sort

template <class RandomAccessIterator>
inline
void sort (RandomAccessIterator first, RandomAccessIterator last)
{
    __quick_sort_loop (first, last);
    __final_insertion_sort (first, last);
}

template <class RandomAccessIterator, class Compare>
inline
void sort (RandomAccessIterator first, RandomAccessIterator last,
           Compare comp)
{
   __quick_sort_loop (first, last, comp);
   __final_insertion_sort (first, last, comp);
}

template <class RandomAccessIterator>
inline
void __inplace_stable_sort (RandomAccessIterator first,
                            RandomAccessIterator last)
{
    if (last - first < 15)
    {
        __insertion_sort (first, last);
        return;
    }
    RandomAccessIterator middle = first + (last - first) / 2;
    __inplace_stable_sort (first, middle);
    __inplace_stable_sort (middle, last);
    __merge_without_buffer (first, middle, last, middle - first,
                           last - middle);
}

template <class RandomAccessIterator, class Compare>
inline
void __inplace_stable_sort (RandomAccessIterator first,
                            RandomAccessIterator last, Compare comp)
{
    if (last - first < 15)
    {
        __insertion_sort (first, last, comp);
        return;
    }
    RandomAccessIterator middle = first + (last - first) / 2;
    __inplace_stable_sort (first, middle, comp);
    __inplace_stable_sort (middle, last, comp);
    __merge_without_buffer (first, middle, last, middle - first,
                           last - middle, comp);
}

// The code has been removed from here in the latest STL release.

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class RandomAccessIterator3, class Distance, class T>
inline
RandomAccessIterator3 __merge_aux (RandomAccessIterator1 first1,
                                   RandomAccessIterator1 last1,
                                   RandomAccessIterator2 first2,
                                   RandomAccessIterator2 last2,
                                   RandomAccessIterator3 result,
                                   Distance& fill_pointer, T*)
{
    Distance len = 0;
    while (first1 != last1 && first2 != last2 && len < fill_pointer)
    {
        ++len;
        if (*first2 < *first1)
            *result++ = *first2++;
        else
            *result++ = *first1++;
    }
    if (fill_pointer == len)
    {
        raw_storage_iterator<RandomAccessIterator3, T> p(result);
        result += (last1 - first1) + (last2 - first2);
        fill_pointer += (last1 - first1) + (last2 - first2);
        while (first1 != last1 && first2 != last2)
            if (*first2 < *first1)
                *p++ = *first2++;
            else
                *p++ = *first1++;
        copy (first2, last2, copy (first1, last1, p));
    } else if (first2 == last2)
    {
        while (first1 != last1 && len < fill_pointer)
        { 
            ++len;
            *result++ = *first1++;
        }
        if (fill_pointer == len)
        {
            raw_storage_iterator<RandomAccessIterator3, T> p(result);  
            result += last1 - first1;
            fill_pointer += last1 - first1;
            while (first1 != last1) *p++ = *first1++;
        }
    } else
    {
        while (first2 != last2 && len < fill_pointer)
        { 
            ++len;
            *result++ = *first2++;
        }
        if (fill_pointer == len)
        {
            raw_storage_iterator<RandomAccessIterator3, T> p(result);  
            result += last2 - first2;
            fill_pointer += last2 - first2;
            while (first2 != last2) *p++ = *first2++;
        }
    }
    return result;
}       

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class RandomAccessIterator3, class Distance, class T,
          class Compare>
inline
RandomAccessIterator3 __merge_aux (RandomAccessIterator1 first1,
                                   RandomAccessIterator1 last1,
                                   RandomAccessIterator2 first2,
                                   RandomAccessIterator2 last2,
                                   RandomAccessIterator3 result,
                                   Distance& fill_pointer, T*,
                                   Compare comp)
{
    Distance len = 0;
    while (first1 != last1 && first2 != last2 && len < fill_pointer)
    {
        ++len;
        if (comp (*first2, *first1))
            *result++ = *first2++;
        else
            *result++ = *first1++;
    }
    if (fill_pointer <= len)
    {
        raw_storage_iterator<RandomAccessIterator3, T> p(result);
        result += (last1 - first1) + (last2 - first2);
        fill_pointer += (last1 - first1) + (last2 - first2);
        while (first1 != last1 && first2 != last2)
            if (comp (*first2, *first1))
                *p++ = *first2++;
            else
                *p++ = *first1++;
        copy (first2, last2, copy (first1, last1, p));
    } else if (first2 == last2)
    {
        while (first1 != last1 && len < fill_pointer)
        { 
            ++len;
            *result++ = *first1++;
        }
        if (fill_pointer == len)
        {
            raw_storage_iterator<RandomAccessIterator3, T> p(result);  
            result += last1 - first1;
            fill_pointer += last1 - first1;
            while (first1 != last1) *p++ = *first1++;
        }
    } else
    {
        while (first2 != last2 && len < fill_pointer)
        { 
            ++len;
            *result++ = *first2++;
        }
        if (fill_pointer == len)
        {
            raw_storage_iterator<RandomAccessIterator3, T> p(result);  
            result += last2 - first2;
            fill_pointer += last2 - first2;
            while (first2 != last2) *p++ = *first2++;
        }
    }
    return result;
}       

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance, class T>
inline
void __merge_sort_loop_aux (RandomAccessIterator1 first,
                            RandomAccessIterator1 last, 
                            RandomAccessIterator2 result,
                            Distance step_size,
                            Distance& fill_pointer, T*)
{
    Distance two_step = 2 * step_size;

    while (last - first >= two_step)
    {
        result = __merge_aux (first, first + step_size, first + step_size,
                        first + two_step, result, fill_pointer, (T*)0);
        first += two_step;
    }
    step_size = min (Distance (last - first), step_size);

    __merge_aux (first, first + step_size, first + step_size, last, result,
                fill_pointer, (T*)0);
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance, class T, class Compare>
inline
void __merge_sort_loop_aux (RandomAccessIterator1 first,
                            RandomAccessIterator1 last, 
                            RandomAccessIterator2 result,
                            Distance step_size,
                            Distance& fill_pointer, T*, Compare comp)
{
    Distance two_step = 2 * step_size;

    while (last - first >= two_step)
    {
        result = __merge_aux (first, first + step_size, first + step_size, 
                 first + two_step, result, fill_pointer, (T*)0, comp);
        first += two_step;
    }
    step_size = min (Distance (last - first), step_size);

    __merge_aux (first, first + step_size, first + step_size, last, result, 
                fill_pointer, (T*)0, comp);
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance>
inline
void __merge_sort_loop (RandomAccessIterator1 first,
                        RandomAccessIterator1 last, 
                        RandomAccessIterator2 result, Distance step_size)
{
    Distance two_step = 2 * step_size;

    while (last - first >= two_step)
    {
        result = merge (first, first + step_size,
                       first + step_size, first + two_step, result);
        first += two_step;
    }
    step_size = min (Distance (last - first), step_size);

    merge (first, first + step_size, first + step_size, last, result);
}

template <class RandomAccessIterator1, class RandomAccessIterator2,
          class Distance, class Compare>
inline
void __merge_sort_loop (RandomAccessIterator1 first,
                        RandomAccessIterator1 last, 
                        RandomAccessIterator2 result, Distance step_size,
                        Compare comp)
{
    Distance two_step = 2 * step_size;

    while (last - first >= two_step)
    {
        result = merge (first, first + step_size,
                       first + step_size, first + two_step, result, comp);
        first += two_step;
    }
    step_size = min (Distance (last - first), step_size);

    merge (first, first + step_size, first + step_size, last, result, comp);
}

const int __stl_chunk_size = 7;
        
template <class RandomAccessIterator, class Distance>
inline
void __chunk_insertion_sort (RandomAccessIterator first, 
                             RandomAccessIterator last,
                             Distance chunk_size)
{
    while (last - first >= chunk_size)
    {
        __insertion_sort (first, first + chunk_size);
        first += chunk_size;
    }
    __insertion_sort (first, last);
}

template <class RandomAccessIterator, class Distance, class Compare>
inline
void __chunk_insertion_sort (RandomAccessIterator first, 
                             RandomAccessIterator last,
                             Distance chunk_size, Compare comp)
{
    while (last - first >= chunk_size)
    {
        __insertion_sort (first, first + chunk_size, comp);
        first += chunk_size;
    }
    __insertion_sort (first, last, comp);
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T>
inline
void __merge_sort_with_buffer (RandomAccessIterator first, 
                               RandomAccessIterator last,
                               Pointer buffer, Distance*, T*)
{
    Distance len = last - first;
    Pointer buffer_last = buffer + len;

    Distance step_size = __stl_chunk_size;
    __chunk_insertion_sort (first, last, step_size);
    while (step_size < len)
    {
        __merge_sort_loop (first, last, buffer, step_size);
        step_size *= 2;
        __merge_sort_loop (buffer, buffer_last, first, step_size);
        step_size *= 2;
    }
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T, class Compare>
inline
void __merge_sort_with_buffer (RandomAccessIterator first, 
                               RandomAccessIterator last, Pointer buffer,
                               Distance*, T*, Compare comp)
{
    Distance len = last - first;
    Pointer buffer_last = buffer + len;

    Distance step_size = __stl_chunk_size;
    __chunk_insertion_sort (first, last, step_size, comp);

    while (step_size < len)
    {
        __merge_sort_loop (first, last, buffer, step_size, comp);
        step_size *= 2;
        __merge_sort_loop (buffer, buffer_last, first, step_size, comp);
        step_size *= 2;
    }
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T>
inline
void __stable_sort_adaptive (RandomAccessIterator first, 
                             RandomAccessIterator last, Pointer buffer,
                             Distance buffer_size, T*)
{
    Distance len = (last - first + 1) / 2;
    RandomAccessIterator middle = first + len;
    if (len > buffer_size)
    {
        __stable_sort_adaptive (first, middle, buffer, buffer_size, (T*)0);
        __stable_sort_adaptive (middle, last, buffer, buffer_size, (T*)0);
    } else
    {
        __merge_sort_with_buffer (first, middle, buffer,
                                 (Distance*)0, (T*)0);
        __merge_sort_with_buffer (middle, last, buffer,
                                 (Distance*)0, (T*)0);
    }
    __merge_adaptive (first, middle, last, Distance (middle - first), 
                      Distance (last - middle), buffer, buffer_size, (T*)0);
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T, class Compare>
inline
void __stable_sort_adaptive (RandomAccessIterator first, 
                             RandomAccessIterator last, Pointer buffer,
                             Distance buffer_size, T*, Compare comp)
{
    Distance len = (last - first + 1) / 2;
    RandomAccessIterator middle = first + len;
    if (len > buffer_size)
    {
        __stable_sort_adaptive (first, middle, buffer, buffer_size,
                              (T*)0, comp);
        __stable_sort_adaptive (middle, last, buffer, buffer_size,
                              (T*)0, comp);
    } else
    {
        __merge_sort_with_buffer (first, middle, buffer, (Distance*)0,
                                (T*)0, comp);
        __merge_sort_with_buffer (middle, last, buffer, (Distance*)0,
                                (T*)0, comp);
    }
    __merge_adaptive (first, middle, last, Distance (middle - first), 
                     Distance (last - middle), buffer, buffer_size,
                    (T*)0, comp);
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T>
inline void __stable_sort (RandomAccessIterator first,
                           RandomAccessIterator last,
                           pair<Pointer, Distance> p, T*)
{
    if (p.first == 0)
    {
        __inplace_stable_sort (first, last);
        return;
    }
    Distance len = min (p.second, Distance (last-first));
    copy (first, first + len, raw_storage_iterator<Pointer, T> (p.first));
    __stable_sort_adaptive (first, last, p.first, p.second, (T*)0);
    destroy (p.first, p.first + len);
    return_temporary_buffer (p.first);
}

template <class RandomAccessIterator, class Pointer,
          class Distance, class T, class Compare>
inline void __stable_sort (RandomAccessIterator first,
                           RandomAccessIterator last,
                           pair<Pointer, Distance> p, T*, Compare comp)
{
    if (p.first == 0)
    {
        __inplace_stable_sort (first, last, comp);
        return;
    }
    Distance len = min (p.second, Distance (last - first));
    copy (first, first + len, raw_storage_iterator<Pointer, T> (p.first));
    __stable_sort_adaptive (first, last, p.first, p.second, (T*)0, comp);
    destroy (p.first, p.first + len);
    return_temporary_buffer (p.first);
}

template <class RandomAccessIterator, class T, class Distance>
inline void __stable_sort_aux (RandomAccessIterator first,
                               RandomAccessIterator last, T*, Distance*)
{
    pair<T*, Distance> temp =
        get_temporary_buffer (Distance (last - first), (T*)0);
    __stable_sort (first, last, temp, (T*)0);
}

template <class RandomAccessIterator, class T, class Distance,
          class Compare>
inline void __stable_sort_aux (RandomAccessIterator first,
                               RandomAccessIterator last, T*, Distance*,
                               Compare comp)
{
    pair<T*, Distance> temp =
        get_temporary_buffer (Distance (last - first), (T*)0);
    __stable_sort (first, last, temp, (T*)0, comp);
}


// Section 25.3.1.2 -- stable sort

template <class RandomAccessIterator>
inline void stable_sort (RandomAccessIterator first,
                         RandomAccessIterator last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __stable_sort_aux (first, last, (Value*)0, (Distance*)0);
}

template <class RandomAccessIterator, class Compare>
inline void stable_sort (RandomAccessIterator first,
                         RandomAccessIterator last, Compare comp)
{
    // __stable_sort_aux (first, last, distance_type (first), comp);
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __stable_sort_aux (first, last, (Value*)0, (Distance*)0, comp);
}

template <class RandomAccessIterator, class T>
inline
void __partial_sort (RandomAccessIterator first,
                     RandomAccessIterator middle,
                     RandomAccessIterator last, T*)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    make_heap (first, middle);
    for (RandomAccessIterator i = middle; i < last; ++i)
       if (*i < *first)
          __pop_heap (first, middle, i, T (*i), (Distance*)0);
    sort_heap (first, middle);
}

// Section 25.3.1.3 -- partial sort

template <class RandomAccessIterator>
inline void partial_sort (RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __partial_sort (first, middle, last, (Value*)0);
}

template <class RandomAccessIterator, class T, class Compare>
inline
void __partial_sort (RandomAccessIterator first,
                     RandomAccessIterator middle,
                     RandomAccessIterator last, T*, Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    make_heap (first, middle, comp);
    for (RandomAccessIterator i = middle; i < last; ++i)
        if (comp (*i, *first))
          __pop_heap (first, middle, i, T (*i), comp, (Distance*)0);
    sort_heap (first, middle, comp);
}

template <class RandomAccessIterator, class Compare>
inline void partial_sort (RandomAccessIterator first,
                          RandomAccessIterator middle,
                          RandomAccessIterator last, Compare comp)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __partial_sort (first, middle, last, (Value*)0, comp);
}

template <class InputIterator, class RandomAccessIterator, class Distance,
          class T>
inline
RandomAccessIterator
__partial_sort_copy (InputIterator first, InputIterator last,
                     RandomAccessIterator result_first,
                     RandomAccessIterator result_last, 
                     Distance*, T*)
{
    if (result_first == result_last) return result_last;
    RandomAccessIterator result_real_last = result_first;
    while (first != last && result_real_last != result_last)
        *result_real_last++ = *first++;
    make_heap (result_first, result_real_last);
    while (first != last)
    {
        if (*first < *result_first) 
            __adjust_heap (result_first, Distance (0),
                Distance (result_real_last - result_first), T (*first));
        ++first;
    }
    sort_heap (result_first, result_real_last);
    return result_real_last;
}

// Section 25.3.1.4 -- partial sort copy

template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator
partial_sort_copy (InputIterator first, InputIterator last,
                   RandomAccessIterator result_first,
                   RandomAccessIterator result_last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<InputIterator>::value_type
                       Value;
    return __partial_sort_copy (first, last, result_first, result_last, 
                    (Distance*)0, (Value*)0);
}

template <class InputIterator, class RandomAccessIterator, class Compare,
          class Distance, class T>
inline
RandomAccessIterator
__partial_sort_copy (InputIterator first, InputIterator last,
                     RandomAccessIterator result_first,
                     RandomAccessIterator result_last,
                     Compare comp, Distance*, T*)
{
    if (result_first == result_last)
        return result_last;

    RandomAccessIterator result_real_last = result_first;

    while (first != last && result_real_last != result_last)
        *result_real_last++ = *first++;

    make_heap (result_first, result_real_last, comp);

    while (first != last)
    {
      if (comp (*first, *result_first)) 
            __adjust_heap (result_first, Distance (0),
                    Distance (result_real_last - result_first), T (*first),
                          comp);
        ++first;
    }

    sort_heap (result_first, result_real_last, comp);

    return result_real_last;
}

template <class InputIterator, class RandomAccessIterator, class Compare>
inline RandomAccessIterator
partial_sort_copy (InputIterator first, InputIterator last,
                   RandomAccessIterator result_first,
                   RandomAccessIterator result_last, Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<InputIterator>::value_type
                       Value;
    return __partial_sort_copy (first, last, result_first, result_last,
                  comp, (Distance*)0, (Value*)0);
}

template <class RandomAccessIterator, class T>
inline
void __nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last, T*)
{
    while (last - first > 3)
    {
        RandomAccessIterator cut = __unguarded_partition
         (first, last, T (__median (*first, * (first + (last - first)/2),
                                     *(last - 1))));
        if (cut <= nth)
            first = cut;
        else 
            last = cut;
    }
    __insertion_sort (first, last);
}

// Section 25.3.2 -- Nth element

template <class RandomAccessIterator>
inline void nth_element (RandomAccessIterator first,
                         RandomAccessIterator nth,
                         RandomAccessIterator last)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __nth_element (first, nth, last, (Value*)0);
}

template <class RandomAccessIterator, class T, class Compare>
inline
void __nth_element (RandomAccessIterator first, RandomAccessIterator nth,
                    RandomAccessIterator last, T*, Compare comp)
{
    while (last - first > 3)
    {
        RandomAccessIterator cut = __unguarded_partition
         (first, last, T (__median (*first, * (first + (last - first)/2),
                                     *(last - 1), comp)), comp);
        if (cut <= nth)
            first = cut;
        else 
            last = cut;
    }
    __insertion_sort (first, last, comp);
}

template <class RandomAccessIterator, class Compare>
inline void
nth_element (RandomAccessIterator first,
             RandomAccessIterator nth,
             RandomAccessIterator last, Compare comp)
{
    typedef typename iterator_trait <RandomAccessIterator>::value_type
                     Value;
    __nth_element (first, nth, last, (Value*)0, comp);
}

// Section 25.3.3 -- Binary search

template <class ForwardIterator, class T, class Distance>
inline
ForwardIterator __lower_bound (ForwardIterator first, ForwardIterator last,
                               const T& value, Distance*,
                               forward_iterator_tag)
{
    Distance len = distance (first, last);
    Distance half;
    ForwardIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (*middle < value)
        {
            first = middle;
            ++first;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

template <class ForwardIterator, class T, class Distance>
inline ForwardIterator __lower_bound (ForwardIterator first,
                                      ForwardIterator last,
                                      const T& value, Distance*,
                                      bidirectional_iterator_tag)
{
    return __lower_bound (first, last, value, (Distance*)0,
                         forward_iterator_tag ());
}

template <class RandomAccessIterator, class T, class Distance>
inline
RandomAccessIterator
__lower_bound (RandomAccessIterator first,
               RandomAccessIterator last, const T& value,
               Distance*, random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (*middle < value)
        {
            first = middle + 1;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

// Section 25.3.3.1 -- lower_bound

template <class ForwardIterator, class T>
inline ForwardIterator
lower_bound (ForwardIterator first, ForwardIterator last, const T& value)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<ForwardIterator>::iterator_category
                       Category;
    return __lower_bound (first, last, value, (Distance*)0, Category ());
}

template <class ForwardIterator, class T, class Compare, class Distance>
inline
ForwardIterator __lower_bound (ForwardIterator first, ForwardIterator last,
                               const T& value, Compare comp, Distance*,
                               forward_iterator_tag)
{
    Distance len =  distance (first, last);
    Distance half;
    ForwardIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (comp (*middle, value))
        {
            first = middle;
            ++first;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

template <class ForwardIterator, class T, class Compare, class Distance>
inline ForwardIterator
__lower_bound (ForwardIterator first,
               ForwardIterator last,
               const T& value, Compare comp, Distance*,
               bidirectional_iterator_tag)
{
    return __lower_bound (first, last, value, comp, (Distance*)0,
                         forward_iterator_tag ());
}

template <class RandomAccessIterator, class T,
          class Compare, class Distance>
inline
RandomAccessIterator
__lower_bound (RandomAccessIterator first,
               RandomAccessIterator last,
               const T& value, Compare comp, Distance*,
               random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (comp (*middle, value))
        {
            first = middle + 1;
            len = len - half - 1;
        } else
            len = half;
    }
    return first;
}

template <class ForwardIterator, class T, class Compare>
inline ForwardIterator
lower_bound (ForwardIterator first, ForwardIterator last,
             const T& value, Compare comp)
{
    typedef  typename iterator_trait<ForwardIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<ForwardIterator>::iterator_category
                       Category;
    return __lower_bound (first, last, value, comp, (Distance*)0,
                          Category ());
}

template <class ForwardIterator, class T, class Distance>
inline
ForwardIterator
__upper_bound (ForwardIterator first, ForwardIterator last,
               const T& value, Distance*,
               forward_iterator_tag)
{
    Distance len =  distance (first, last);
    Distance half;
    ForwardIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (value < *middle)
            len = half;
        else
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}

template <class ForwardIterator, class T, class Distance>
inline ForwardIterator __upper_bound (ForwardIterator first,
                                      ForwardIterator last,
                                      const T& value, Distance*,
                                      bidirectional_iterator_tag)
{
    return __upper_bound (first, last, value, (Distance*)0,
                         forward_iterator_tag ());
}

template <class RandomAccessIterator, class T, class Distance>
inline
RandomAccessIterator
__upper_bound (RandomAccessIterator first,
               RandomAccessIterator last, const T& value,
               Distance*, random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (value < *middle)
            len = half;
        else
        {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

// Section 25.3.3.2 -- upper_bound

template <class ForwardIterator, class T>
inline ForwardIterator
upper_bound (ForwardIterator first, ForwardIterator last, const T& value)
{
    typedef  typename 
      iterator_trait<ForwardIterator>::distance_type       Distance;
    typedef  typename 
      iterator_trait<ForwardIterator>::iterator_category   Category;
    return __upper_bound (first, last, value, (Distance*)0, Category ());
}

template <class ForwardIterator, class T, class Compare, class Distance>
inline
ForwardIterator
__upper_bound (ForwardIterator first, ForwardIterator last,
               const T& value, Compare comp, Distance*,
               forward_iterator_tag)
{
    Distance len =  distance (first, last);
    Distance half;
    ForwardIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (comp (value, *middle))
            len = half;
        else
        {
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}

template <class ForwardIterator, class T, class Compare, class Distance>
inline ForwardIterator
__upper_bound (ForwardIterator first,
               ForwardIterator last,
               const T& value, Compare comp, Distance*,
               bidirectional_iterator_tag)
{
    return __upper_bound (first, last, value, comp, (Distance*)0,
                          forward_iterator_tag ());
}

template <class RandomAccessIterator, class T, class Compare,
          class Distance>
inline
RandomAccessIterator
__upper_bound (RandomAccessIterator first, RandomAccessIterator last,
               const T& value, Compare comp, Distance*,
               random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (comp (value, *middle))
            len = half;
        else
        {
            first = middle + 1;
            len = len - half - 1;
        }
    }
    return first;
}

template <class ForwardIterator, class T, class Compare>
inline ForwardIterator
upper_bound (ForwardIterator first, ForwardIterator last,
             const T& value, Compare comp)
{
    typedef  typename 
      iterator_trait<ForwardIterator>::distance_type      Distance;
    typedef  typename 
      iterator_trait<ForwardIterator>::iterator_category  Category;
    return __upper_bound (first, last, value, comp, (Distance*)0,
                          Category ());
}

template <class ForwardIterator, class T, class Distance>
inline
pair<ForwardIterator, ForwardIterator>
__equal_range (ForwardIterator first, ForwardIterator last, const T& value,
               Distance*, forward_iterator_tag)
{
    Distance len = distance (first, last);
    Distance half;
    ForwardIterator middle, left, right;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (*middle < value)
        {
            first = middle;
            ++first;
            len = len - half - 1;
        } else if (value < *middle)
            len = half;
        else
        {
            left = lower_bound (first, middle, value);
            advance (first, len);
            right = upper_bound (++middle, first, value);
            return pair<ForwardIterator, ForwardIterator> (left, right);
        }
    }
    return pair<ForwardIterator, ForwardIterator> (first, first);
}

template <class ForwardIterator, class T, class Distance>
inline pair<ForwardIterator, ForwardIterator>
__equal_range (ForwardIterator first, ForwardIterator last, const T& value,
               Distance*, bidirectional_iterator_tag)
{
    return __equal_range (first, last, value, (Distance*)0, 
                          forward_iterator_tag ());
}

template <class RandomAccessIterator, class T, class Distance>
inline
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range (RandomAccessIterator first, RandomAccessIterator last,
               const T& value, Distance*, random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle, left, right;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (*middle < value)
        {
            first = middle + 1;
            len = len - half - 1;
        } else if (value < *middle)
            len = half;
        else
        {
            left = lower_bound (first, middle, value);
            right = upper_bound (++middle, first + len, value);
            return pair<RandomAccessIterator,
                        RandomAccessIterator> (left, right);
        }
    }
    return pair<RandomAccessIterator, RandomAccessIterator> (first, first);
}

//  Section 25.3.3.3 -- equal range

template <class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator>
equal_range (ForwardIterator first, ForwardIterator last, const T& value)
{
    typedef  typename
      iterator_trait<ForwardIterator>::distance_type     Distance;
    typedef  typename
      iterator_trait<ForwardIterator>::iterator_category Category;
    return __equal_range (first, last, value, (Distance*)0,
                          Category ());
}

template <class ForwardIterator, class T, class Compare, class Distance>
inline
pair<ForwardIterator, ForwardIterator>
__equal_range (ForwardIterator first, ForwardIterator last, const T& value,
               Compare comp, Distance*, forward_iterator_tag)
{
    Distance len = distance (first, last);
    Distance half;
    ForwardIterator middle, left, right;

    while (len > 0)
    {
        half = len / 2;
        middle = first;
        advance (middle, half);
        if (comp (*middle, value))
        {
            first = middle;
            ++first;
            len = len - half - 1;
        } else if (comp (value, *middle))
            len = half;
        else
        {
            left = lower_bound (first, middle, value, comp);
            advance (first, len);
            right = upper_bound (++middle, first, value, comp);
            return pair<ForwardIterator, ForwardIterator> (left, right);
        }
    }
    return pair<ForwardIterator, ForwardIterator> (first, first);
}           

template <class ForwardIterator, class T, class Compare, class Distance>
inline pair<ForwardIterator, ForwardIterator>
__equal_range (ForwardIterator first, ForwardIterator last, const T& value,
               Compare comp, Distance*, bidirectional_iterator_tag)
{
    return __equal_range (first, last, value, comp, (Distance*)0, 
                          forward_iterator_tag ());
}

template <class RandomAccessIterator, class T, class Compare,
          class Distance>
inline
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range (RandomAccessIterator first, RandomAccessIterator last,
               const T& value, Compare comp, Distance*,
               random_access_iterator_tag)
{
    Distance len = last - first;
    Distance half;
    RandomAccessIterator middle, left, right;

    while (len > 0)
    {
        half = len / 2;
        middle = first + half;
        if (comp (*middle, value))
        {
            first = middle + 1;
            len = len - half - 1;
        } else if (comp (value, *middle))
            len = half;
        else
        {
            left = lower_bound (first, middle, value, comp);
            right = upper_bound (++middle, first + len, value, comp);
            return pair<RandomAccessIterator,
                        RandomAccessIterator> (left, right);
        }
    }
    return pair<RandomAccessIterator, RandomAccessIterator> (first, first);
}           

template <class ForwardIterator, class T, class Compare>
inline pair<ForwardIterator, ForwardIterator>
equal_range (ForwardIterator first, ForwardIterator last, const T& value,
             Compare comp)
{
    typedef  typename
      iterator_trait<ForwardIterator>::distance_type      Distance;
    typedef  typename 
      iterator_trait<ForwardIterator>::iterator_category  Category;
    return __equal_range (first, last, value, comp, (Distance*)0,
                          Category ());
}    

//  Section 25.3.3.4 -- binary search

template <class ForwardIterator, class T>
inline
bool binary_search (ForwardIterator first, ForwardIterator last,
                    const T& value)
{
    ForwardIterator i = lower_bound (first, last, value);
    return i != last && ! (value < *i);
}

template <class ForwardIterator, class T, class Compare>
inline
bool binary_search (ForwardIterator first, ForwardIterator last,
                    const T& value, Compare comp)
{
    ForwardIterator i = lower_bound (first, last, value, comp);
    return i != last && !comp (value, *i);
}

// Section 25.3.4 -- Merge

// Section 25.3.4.1 -- merge

template <class InputIterator1, class InputIterator2, class OutputIterator>
inline
OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
        if (*first2 < *first1)
            *result++ = *first2++;
        else
            *result++ = *first1++;
    return copy (first2, last2, copy (first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
inline
OutputIterator merge (InputIterator1 first1, InputIterator1 last1,
                      InputIterator2 first2, InputIterator2 last2,
                      OutputIterator result, Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first2, *first1))
            *result++ = *first2++;
        else
            *result++ = *first1++;
    return copy (first2, last2, copy (first1, last1, result));
}

template <class BidirectionalIterator, class Distance>
inline
void __merge_without_buffer (BidirectionalIterator first,
                             BidirectionalIterator middle,
                             BidirectionalIterator last,
                             Distance len1, Distance len2)
{
    if (len1 == 0 || len2 == 0) return;
    if (len1 + len2 == 2)
    {
        if (*middle < *first) iter_swap (first, middle);
        return;
    }
    BidirectionalIterator first_cut = first;
    BidirectionalIterator second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2)
    {
        len11 = len1 / 2;
        advance (first_cut, len11);
        second_cut = lower_bound (middle, last, *first_cut);
        len22 = distance (middle, second_cut);
    } else
    {
        len22 = len2 / 2;
        advance (second_cut, len22);
        first_cut = upper_bound (first, middle, *second_cut);
        len11 = distance (first, first_cut);
    }
    rotate (first_cut, middle, second_cut);
    BidirectionalIterator new_middle = first_cut;
    advance (new_middle, len22);
    __merge_without_buffer (first, first_cut, new_middle, len11, len22);
    __merge_without_buffer (new_middle, second_cut, last, len1 - len11,
                            len2 - len22);
}

template <class BidirectionalIterator, class Distance, class Compare>
inline
void __merge_without_buffer (BidirectionalIterator first,
                             BidirectionalIterator middle,
                             BidirectionalIterator last,
                             Distance len1, Distance len2, Compare comp)
{
    if (len1 == 0 || len2 == 0) return;
    if (len1 + len2 == 2)
    {
        if (comp (*middle, *first)) iter_swap (first, middle);
        return;
    }
    BidirectionalIterator first_cut = first;
    BidirectionalIterator second_cut = middle;
    Distance len11 = 0;
    Distance len22 = 0;
    if (len1 > len2)
    {
        len11 = len1 / 2;
        advance (first_cut, len11);
        second_cut = lower_bound (middle, last, *first_cut, comp);
        len22 = distance (middle, second_cut);
    } else
    {
        len22 = len2 / 2;
        advance (second_cut, len22);
        first_cut = upper_bound (first, middle, *second_cut, comp);
        len11 = distance (first, first_cut);
    }
    rotate (first_cut, middle, second_cut);
    BidirectionalIterator new_middle = first_cut;
    advance (new_middle, len22);
    __merge_without_buffer (first, first_cut, new_middle, len11, len22, comp);
    __merge_without_buffer (new_middle, second_cut, last, len1 - len11,
                            len2 - len22, comp);
}


template <class InputIterator, class OutputIterator>
inline
OutputIterator
__borland_bugfix_copy (InputIterator first, InputIterator last,
                       OutputIterator result)
{
// this is used in __rotate_adaptive to work around some obscure Borland
// bug. It is the same as copy, but with a different (and appropriate) name.
    while (first != last) *result++ = *first++;
    return result;
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class Distance>
inline
BidirectionalIterator1 __rotate_adaptive (BidirectionalIterator1 first,
                                          BidirectionalIterator1 middle,
                                          BidirectionalIterator1 last,
                                          Distance len1, Distance len2,
                                          BidirectionalIterator2 buffer,
                                          Distance buffer_size)
{
    BidirectionalIterator2 buffer_end;
    if (len1 > len2 && len2 <= buffer_size)
    {
        buffer_end = __borland_bugfix_copy (middle, last, buffer);
        copy_backward (first, middle, last);
        return copy (buffer, buffer_end, first);
    } else if (len1 <= buffer_size)
    {
        buffer_end = __borland_bugfix_copy (first, middle, buffer);
        copy (middle, last, first);
        return copy_backward (buffer, buffer_end, last);
    } else  {
        rotate (first, middle, last);
        advance (first, len2);
        return first;
    }
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class BidirectionalIterator3>
inline
BidirectionalIterator3 __merge_backward (BidirectionalIterator1 first1,
                                         BidirectionalIterator1 last1,
                                         BidirectionalIterator2 first2,
                                         BidirectionalIterator2 last2,
                                         BidirectionalIterator3 result)
{
    if (first1 == last1) return copy_backward (first2, last2, result);
    if (first2 == last2) return copy_backward (first1, last1, result);
    --last1;
    --last2;
    while (true)
    {
        if (*last2 < *last1)
        {
            *--result = *last1;
            if (first1 == last1)
                return copy_backward (first2, ++last2, result);
            --last1;
        } else
        {
            *--result = *last2;
            if (first2 == last2)
                return copy_backward (first1, ++last1, result);
            --last2;
        }
    }
}

template <class BidirectionalIterator1, class BidirectionalIterator2,
          class BidirectionalIterator3, class Compare>
inline
BidirectionalIterator3 __merge_backward (BidirectionalIterator1 first1,
                                         BidirectionalIterator1 last1,
                                         BidirectionalIterator2 first2,
                                         BidirectionalIterator2 last2,
                                         BidirectionalIterator3 result,
                                         Compare comp)
{
    if (first1 == last1) return copy_backward (first2, last2, result);
    if (first2 == last2) return copy_backward (first1, last1, result);
    --last1;
    --last2;
    while (true)
    {
        if (comp (*last2, *last1))
        {
            *--result = *last1;
            if (first1 == last1)
                return copy_backward (first2, ++last2, result);
            --last1;
        } else
        {
            *--result = *last2;
            if (first2 == last2)
                return copy_backward (first1, ++last1, result);
            --last2;
        }
    }
}

template <class BidirectionalIterator, class Distance,
          class Pointer, class T>
inline
void __merge_adaptive (BidirectionalIterator first, 
                       BidirectionalIterator middle, 
                       BidirectionalIterator last, Distance len1,
                       Distance len2, Pointer buffer,
                       Distance buffer_size, T*)
{
    if (len1 <= len2 && len1 <= buffer_size)
    {
        Pointer end_buffer = copy (first, middle, buffer);
        merge (buffer, end_buffer, middle, last, first);
    } else if (len2 <= buffer_size)
    {
        Pointer end_buffer = copy (middle, last, buffer);
        __merge_backward (first, middle, buffer, end_buffer, last);
    } else
    {
        BidirectionalIterator first_cut = first;
        BidirectionalIterator second_cut = middle;
        Distance len11 = 0;
        Distance len22 = 0;
        if (len1 > len2)
        {
            len11 = len1 / 2;
            advance (first_cut, len11);
            second_cut = lower_bound (middle, last, *first_cut);
            len22 = distance (middle, second_cut);
        } else
        {
            len22 = len2 / 2;
            advance (second_cut, len22);
            first_cut = upper_bound (first, middle, *second_cut);
            len11 = distance (first, first_cut);
        }
        BidirectionalIterator new_middle =
            __rotate_adaptive (first_cut, middle, second_cut, len1 - len11,
                               len22, buffer, buffer_size);
        __merge_adaptive (first, first_cut, new_middle, len11, len22, buffer,
                          buffer_size, (T*)0);
        __merge_adaptive (new_middle, second_cut, last, len1 - len11,
                          len2 - len22, buffer, buffer_size, (T*)0);
    }
}

template <class BidirectionalIterator, class Distance, class Pointer,
          class T, class Compare>
inline
void __merge_adaptive (BidirectionalIterator first, 
                       BidirectionalIterator middle, 
                       BidirectionalIterator last, Distance len1,
                       Distance len2, Pointer buffer,
                       Distance buffer_size, T*, Compare comp)
{
    if (len1 <= len2 && len1 <= buffer_size)
    {
        Pointer end_buffer = copy (first, middle, buffer);
        merge (buffer, end_buffer, middle, last, first, comp);
    } else if (len2 <= buffer_size)
    {
        Pointer end_buffer = copy (middle, last, buffer);
        __merge_backward (first, middle, buffer, end_buffer, last, comp);
    } else
    {
        BidirectionalIterator first_cut = first;
        BidirectionalIterator second_cut = middle;
        Distance len11 = 0;
        Distance len22 = 0;
        if (len1 > len2)
        {
            len11 = len1 / 2;
            advance (first_cut, len11);
            second_cut = lower_bound (middle, last, *first_cut, comp);
            len22 = distance (middle, second_cut);
        } else
        {
            len22 = len2 / 2;
            advance (second_cut, len22);
            first_cut = upper_bound (first, middle, *second_cut, comp);
            len11 = distance (first, first_cut);
    }
        BidirectionalIterator new_middle =
            __rotate_adaptive (first_cut, middle, second_cut, len1 - len11,
                               len22, buffer, buffer_size);
        __merge_adaptive (first, first_cut, new_middle, len11, len22, buffer,
                          buffer_size, (T*)0, comp);
        __merge_adaptive (new_middle, second_cut, last, len1 - len11,
                          len2 - len22, buffer, buffer_size, (T*)0, comp);
    }
}

template <class BidirectionalIterator, class Distance,
          class Pointer, class T>
inline
void __inplace_merge (BidirectionalIterator first,
                      BidirectionalIterator middle,
                      BidirectionalIterator last, Distance len1,
                      Distance len2, pair<Pointer, Distance> p, T*)
{
    if (p.first == 0)
    {
        __merge_without_buffer (first, middle, last, len1, len2);
        return;
    }
    Distance len = min (p.second, len1 + len2);
    raw_storage_iterator<Pointer, T> iter(p.first);
    fill_n (iter, len, *first);
    __merge_adaptive (first, middle, last, len1, len2,
                      p.first, p.second, (T*)0);
    destroy (p.first, p.first + len);
    return_temporary_buffer (p.first);
}

template <class BidirectionalIterator, class Distance, class Pointer,
          class T, class Compare>
inline
void __inplace_merge (BidirectionalIterator first,
                      BidirectionalIterator middle,
                      BidirectionalIterator last, Distance len1,
                      Distance len2, pair<Pointer, Distance> p,
                      T*, Compare comp)
{
    if (p.first == 0)
    {
        __merge_without_buffer (first, middle, last, len1, len2, comp);
        return;
    }
    Distance len = min (p.second, len1 + len2);
    fill_n (raw_storage_iterator<Pointer, T> (p.first), len, *first);
    __merge_adaptive (first, middle, last, len1, len2,
                      p.first, p.second, (T*)0, comp);
    destroy (p.first, p.first + len);
    return_temporary_buffer (p.first);
}

template <class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux (BidirectionalIterator first,
                                 BidirectionalIterator middle,
                                 BidirectionalIterator last, T*, Distance*)
{
    Distance len1 = distance (first, middle);
    Distance len2 = distance (middle, last);
    pair<T*, Distance> temp = get_temporary_buffer (len1+len2, (T*)0);
    __inplace_merge (first, middle, last, len1, len2, temp, (T*)0);
}
 
template <class BidirectionalIterator, class T, class Distance,
          class Compare>
inline void __inplace_merge_aux (BidirectionalIterator first,
                                 BidirectionalIterator middle,
                                 BidirectionalIterator last, T*, Distance*,
                                 Compare comp)
{
    Distance len1 = distance (first, middle);
    Distance len2 = distance (middle, last);
    pair<T*, Distance> temp = get_temporary_buffer (len1+len2, (T*)0);
    __inplace_merge (first, middle, last, len1, len2, temp, (T*)0, comp); 
}

// Section 25.3.4.2 -- inplace_merge

template <class BidirectionalIterator>
inline void inplace_merge (BidirectionalIterator first,
                           BidirectionalIterator middle,
                           BidirectionalIterator last)
{
    typedef  typename iterator_trait<BidirectionalIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<BidirectionalIterator>::value_type
                       Value;
     if (first == middle || middle == last) return;
    __inplace_merge_aux (first, middle, last, (Value*)0, (Distance*)0);
}

template <class BidirectionalIterator, class Compare>
inline void inplace_merge (BidirectionalIterator first,
                           BidirectionalIterator middle,
                           BidirectionalIterator last, Compare comp)
{
    typedef  typename iterator_trait<BidirectionalIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<BidirectionalIterator>::value_type
                       Value;
    __inplace_merge_aux (first, middle, last, (Value*)0,
                         (Distance*)0, comp);
}


// Section 25.3.5 -- Set operations on sorted structures

// Section 25.3.5.1 -- includes

template <class InputIterator1, class InputIterator2>
inline
bool includes (InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1 && first2 != last2)
        if (*first2 < *first1)
            return false;
        else if (*first1 < *first2) 
            ++first1;
        else
            ++first1, ++first2;

    return first2 == last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
inline
bool includes (InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2, Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first2, *first1))
            return false;
        else if (comp (*first1, *first2)) 
            ++first1;
        else
            ++first1, ++first2;

    return first2 == last2;
}

// Section 25.3.5.2 -- set union

template <class InputIterator1, class InputIterator2, class OutputIterator>
inline
OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, InputIterator2 last2,
                          OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
        if (*first1 < *first2)
            *result++ = *first1++;
        else if (*first2 < *first1)
            *result++ = *first2++;
        else
        {
            *result++ = *first1++;
            first2++;
        }
    return copy (first2, last2, copy (first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
inline
OutputIterator set_union (InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2, InputIterator2 last2,
                          OutputIterator result, Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first1, *first2))
            *result++ = *first1++;
        else if (comp (*first2, *first1))
            *result++ = *first2++;
        else
        {
            *result++ = *first1++;
            ++first2;
        }
    return copy (first2, last2, copy (first1, last1, result));
}

// Section 25.3.5.3 -- set intersection

template <class InputIterator1, class InputIterator2, class OutputIterator>
inline
OutputIterator
set_intersection (InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, InputIterator2 last2,
                  OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
        if (*first1 < *first2)
            ++first1;
        else if (*first2 < *first1)
            ++first2;
        else
        {
            *result++ = *first1++;
            ++first2;
        }
    return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
inline
OutputIterator
set_intersection (InputIterator1 first1, InputIterator1 last1,
                  InputIterator2 first2, InputIterator2 last2,
                  OutputIterator result, Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first1, *first2))
            ++first1;
        else if (comp (*first2, *first1))
            ++first2;
        else
        {
            *result++ = *first1++;
            ++first2;
        }
    return result;
}

// Section 25.3.5.4 -- set difference

template <class InputIterator1, class InputIterator2, class OutputIterator>
inline
OutputIterator
set_difference (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, InputIterator2 last2,
                OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
        if (*first1 < *first2)
            *result++ = *first1++;
        else if (*first2 < *first1)
            ++first2;
        else
        {
            ++first1;
            ++first2;
        }
    return copy (first1, last1, result);
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
inline
OutputIterator
set_difference (InputIterator1 first1, InputIterator1 last1,
                InputIterator2 first2, InputIterator2 last2, 
                OutputIterator result, Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first1, *first2))
            *result++ = *first1++;
        else if (comp (*first2, *first1))
            ++first2;
        else
        {
            ++first1;
            ++first2;
        }
    return copy (first1, last1, result);
}

// Section 25.3.5.5 -- set symmetric difference

template <class InputIterator1, class InputIterator2, class OutputIterator>
inline
OutputIterator set_symmetric_difference (InputIterator1 first1,
                                         InputIterator1 last1,
                                         InputIterator2 first2,
                                         InputIterator2 last2,
                                         OutputIterator result)
{
    while (first1 != last1 && first2 != last2)
        if (*first1 < *first2)
            *result++ = *first1++;
        else if (*first2 < *first1)
            *result++ = *first2++;
        else
        {
            ++first1;
            ++first2;
        }
    return copy (first2, last2, copy (first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class Compare>
inline
OutputIterator set_symmetric_difference (InputIterator1 first1,
                                         InputIterator1 last1,
                                         InputIterator2 first2,
                                         InputIterator2 last2,
                                         OutputIterator result,
                                         Compare comp)
{
    while (first1 != last1 && first2 != last2)
        if (comp (*first1, *first2))
            *result++ = *first1++;
        else if (comp (*first2, *first1))
            *result++ = *first2++;
        else
        {
            ++first1;
            ++first2;
        }
    return copy (first2, last2, copy (first1, last1, result));
}

// Section 25.3.6 -- Heap operations
// Section 25.3.6.1 -- push_heap -- in heap.h
// Section 25.3.6.2 -- pop_heap  -- in heap.h
// Section 25.3.6.3 -- make_heap -- in heap.h
// Section 25.3.6.4 -- sort_heap -- in heap.h

// Section 25.3.7 -- Minimum and Maximum

// Section 25.3.7.1 -- min  -- in algobase.h
// Section 25.3.7.2 -- max  -- in algobase.h

// Section 25.3.7.3 -- max_element

template <class ForwardIterator>
inline
ForwardIterator max_element (ForwardIterator first, ForwardIterator last)
{
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last) 
        if (*result < *first) result = first;
    return result;
}

template <class ForwardIterator, class Compare>
inline
ForwardIterator max_element (ForwardIterator first, ForwardIterator last,
                             Compare comp)
{
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last) 
        if (comp (*result, *first)) result = first;
    return result;
}

// Section 25.3.7.4 -- min_element

template <class ForwardIterator>
inline
ForwardIterator min_element (ForwardIterator first, ForwardIterator last)
{
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last) 
        if (*first < *result) result = first;
    return result;
}

template <class ForwardIterator, class Compare>
inline
ForwardIterator min_element (ForwardIterator first, ForwardIterator last,
                             Compare comp)
{
    if (first == last) return first;
    ForwardIterator result = first;
    while (++first != last) 
        if (comp (*first, *result)) result = first;
    return result;
}

// Section 25.3.8 -- Lexicographical comparison -- in algobase.h

// Section 25.3.9 -- Permutation generators

// Section 25.3.9.1 -- next permutation

template <class BidirectionalIterator>
inline
bool next_permutation (BidirectionalIterator first,
                       BidirectionalIterator last)
{
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;)
    {
        BidirectionalIterator ii = i--;
        if (*i < *ii)
        {
            BidirectionalIterator j = last;
            --j;
            while (!(*i < *j)) --j;
            iter_swap (i, j);
            reverse (ii, last);
            return true;
        }
        if (i == first)
        {
            reverse (first, last);
            return false;
        }
    }
}

template <class BidirectionalIterator, class Compare>
inline
bool
next_permutation (BidirectionalIterator first, BidirectionalIterator last,
                  Compare comp)
{
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;)
    {
        BidirectionalIterator ii = i--;
        if (comp (*i, *ii))
        {
            BidirectionalIterator j = last;
            --j;
            while (!comp (*i, *j)) --j;
            iter_swap (i, j);
            reverse (ii, last);
            return true;
        }
        if (i == first)
        {
            reverse (first, last);
            return false;
        }
    }
}

// Section 25.3.9.2 -- previous permutation

template <class BidirectionalIterator>
inline
bool prev_permutation (BidirectionalIterator first,
                       BidirectionalIterator last)
{
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;)
    {
        BidirectionalIterator ii = i--;
        if (*ii < *i)
        {
            BidirectionalIterator j = last;
            --j;
            while (!(*j < *i)) --j;
            iter_swap (i, j);
            reverse (ii, last);
            return true;
        }
        if (i == first)
        {
            reverse (first, last);
            return false;
        }
    }
}

template <class BidirectionalIterator, class Compare>
inline
bool
prev_permutation (BidirectionalIterator first, BidirectionalIterator last,
                  Compare comp)
{
    if (first == last) return false;
    BidirectionalIterator i = first;
    ++i;
    if (i == last) return false;
    i = last;
    --i;

    for (;;)
    {
        BidirectionalIterator ii = i--;
        if (comp (*ii, *i))
        {
            BidirectionalIterator j = last;
            while (!comp (*--j, *i));
            iter_swap (i, j);
            reverse (ii, last);
            return true;
        }
        if (i == first)
        {
            reverse (first, last);
            return false;
        }
    }
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_ALGORITHM_H */

/*Change record
 * 961112 mm	line 223,235 change paramaterized return type to ptr_difft
 * 961210 bkoz added pragma options align=native pragma
 * 961216 ah changed memory -> mmemory
 */
//970916 mm Corrected typos in both versions find_first_of  MW00491
