/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_HEAP_H
#define MSIPL_HEAP_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// For implementation of class priority_queue and Heap operations

template <class RandomAccessIterator, class Distance, class T>
inline
void __push_heap (RandomAccessIterator first, Distance holeIndex,
                  Distance topIndex, T value)
{
    Distance parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && *(first + parent) < value)
    {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }    
    *(first + holeIndex) = value;
}

template <class RandomAccessIterator, class Distance, class T>
inline void
__push_heap_aux (RandomAccessIterator first,
                 RandomAccessIterator last, Distance*, T*)
{
    __push_heap (first, Distance ((last - first) - 1), Distance (0), 
                 T (* (last - 1)));
}

template <class RandomAccessIterator>
inline void
push_heap (RandomAccessIterator first, RandomAccessIterator last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __push_heap_aux (first, last, (Distance*)0, (Value*)0);
}

template <class RandomAccessIterator, class Distance, class T, class Compare>
inline
void __push_heap (RandomAccessIterator first, Distance holeIndex,
                  Distance topIndex, T value, Compare comp)
{
    Distance parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp (* (first + parent), value))
    {
        *(first + holeIndex) = *(first + parent);
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    *(first + holeIndex) = value;
}

template <class RandomAccessIterator, class Compare,
          class Distance, class T>
inline void
__push_heap_aux (RandomAccessIterator first,
                 RandomAccessIterator last, Compare comp,
                 Distance*, T*)
{
    __push_heap (first, Distance ((last - first) - 1), Distance (0),
                T (* (last - 1)), comp);
}

// Section 25.3.6 -- Heap operations

// Section 25.3.6.1 -- push_heap

template <class RandomAccessIterator, class Compare>
inline void
push_heap (RandomAccessIterator first, RandomAccessIterator last,
           Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __push_heap_aux (first, last, comp, (Distance*)0, (Value*)0);
}

template <class RandomAccessIterator, class Distance, class T>
inline
void __adjust_heap (RandomAccessIterator first, Distance holeIndex,
                    Distance len, T value)
{
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;
    while (secondChild < len)
    {
        if (*(first + secondChild) < *(first + (secondChild - 1)))
            secondChild--;
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len)
    {
        *(first + holeIndex) = *(first + (secondChild - 1));
        holeIndex = secondChild - 1;
    }
    __push_heap (first, holeIndex, topIndex, value);
}

template <class RandomAccessIterator, class T, class Distance>
inline void
__pop_heap (RandomAccessIterator first, RandomAccessIterator last,
            RandomAccessIterator result, T value, Distance*)
{
    *result = *first;
    __adjust_heap (first, Distance (0), Distance (last - first), value);
}

template <class RandomAccessIterator, class T>
inline void
__pop_heap_aux (RandomAccessIterator first,
                RandomAccessIterator last, T*)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    __pop_heap (first, last - 1, last - 1, T (* (last - 1)),
                (Distance*)0);
}

template <class RandomAccessIterator>
inline void
pop_heap (RandomAccessIterator first, RandomAccessIterator last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __pop_heap_aux (first, last, (Value*)0);
}

template <class RandomAccessIterator, class Distance,
          class T, class Compare>
inline
void __adjust_heap (RandomAccessIterator first, Distance holeIndex,
                    Distance len, T value, Compare comp)
{
    Distance topIndex = holeIndex;
    Distance secondChild = 2 * holeIndex + 2;
    while (secondChild < len)
    {
        if (comp (* (first + secondChild), * (first + (secondChild - 1))))
            secondChild--;
        *(first + holeIndex) = *(first + secondChild);
        holeIndex = secondChild;
        secondChild = 2 * (secondChild + 1);
    }
    if (secondChild == len)
    {
        *(first + holeIndex) = *(first + (secondChild - 1));
        holeIndex = secondChild - 1;
    }
    __push_heap (first, holeIndex, topIndex, value, comp);
}

template <class RandomAccessIterator, class T,
          class Compare, class Distance>
inline void
__pop_heap (RandomAccessIterator first, RandomAccessIterator last,
            RandomAccessIterator result, T value, Compare comp,
            Distance*)
{
    *result = *first;
    __adjust_heap (first, Distance (0),
                   Distance (last - first), value, comp);
}

template <class RandomAccessIterator, class T, class Compare>
inline void
__pop_heap_aux (RandomAccessIterator first,
                RandomAccessIterator last, T*, Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    __pop_heap (first, last - 1, last - 1, T (* (last - 1)), comp,
                (Distance*)0);
}

// Section 25.3.6.2 -- pop_heap

template <class RandomAccessIterator, class Compare>
inline void
pop_heap (RandomAccessIterator first, RandomAccessIterator last,
          Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __pop_heap_aux (first, last, (Value*)0, comp);
}

template <class RandomAccessIterator, class T, class Distance>
inline
void
__make_heap (RandomAccessIterator first, RandomAccessIterator last, T*,
             Distance*)
{
    if (last - first < 2) return;
    Distance len = last - first;
    Distance parent = (len - 2)/2;
    
    while (true)
    {
        __adjust_heap (first, parent, len, T (* (first + parent)));
        if (parent == 0) return;
        parent--;
    }
}

// Section 25.3.6.3 -- make_heap

template <class RandomAccessIterator>
inline void
make_heap (RandomAccessIterator first, RandomAccessIterator last)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __make_heap (first, last, (Value*)0, (Distance*)0);
}

template <class RandomAccessIterator, class Compare,
          class T, class Distance>
inline
void
__make_heap (RandomAccessIterator first, RandomAccessIterator last,
             Compare comp, T*, Distance*)
{
    if (last - first < 2) return;
    Distance len = last - first;
    Distance parent = (len - 2)/2;
    
    while (true)
    {
        __adjust_heap (first, parent, len, T (* (first + parent)), comp);
        if (parent == 0) return;
        parent--;
    }
}

template <class RandomAccessIterator, class Compare>
inline void
make_heap (RandomAccessIterator first, RandomAccessIterator last,
           Compare comp)
{
    typedef  typename iterator_trait<RandomAccessIterator>::distance_type
                       Distance;
    typedef  typename iterator_trait<RandomAccessIterator>::value_type
                       Value;
    __make_heap (first, last, comp, (Value*)0, (Distance*)0);
}

// Section 25.3.6.4 -- sort_heap
 
template <class RandomAccessIterator>
inline
void sort_heap (RandomAccessIterator first, RandomAccessIterator last)
{
    while (last - first > 1) pop_heap (first, last--);
}

template <class RandomAccessIterator, class Compare>
inline
void sort_heap (RandomAccessIterator first, RandomAccessIterator last,
                Compare comp)
{
    while (last - first > 1) pop_heap (first, last--, comp);
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_HEAP_H */

//961210 bkoz added alignment wrapper
