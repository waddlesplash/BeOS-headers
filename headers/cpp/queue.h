/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_QUEUE_H
#define MSIPL_QUEUE_H

#include <mcompile.h>

#include MOD_INCLUDE(heap)
#include MOD_INCLUDE(functional)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 23.2.4.1 -- clause queue

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Container = deque<T>,
          class Allocator = allocator<T> >
#else
template <class T, class Container, class Allocator>
#endif
class queue {

    friend bool
    operator== (const queue<T, Container, Allocator>& x,
                const queue<T, Container, Allocator>& y);
    friend bool
    operator< (const queue<T, Container, Allocator>& x,
               const queue<T, Container, Allocator>& y);
public:

    typedef typename Container::value_type   value_type;
    typedef typename Container::size_type    size_type;
    typedef          Allocator               allocator_type;

protected:

    Container c;

public:

    explicit queue (const Allocator& alloc = Allocator()) 
    : c(alloc) {}

    allocator_type     get_allocator ()     const { return c.get_allocator (); }
    bool               empty ()             const { return c.empty (); }
    size_type          size ()              const { return c.size ();  }
    value_type&        front ()                   { return c.front (); }
    const value_type&  front ()             const { return c.front (); }
    value_type&        back ()                    { return c.back ();  }
    const value_type&  back ()              const { return c.back ();  }
    void               push (const value_type& x) { c.push_back (x);   }
    void               pop ()                     { c.pop_front ();    }
};

template <class T, class Container, class Allocator>
inline
bool
operator== (const queue<T, Container, Allocator>& x,
            const queue<T, Container, Allocator>& y)
{
    return x.c == y.c;
}

template <class T, class Container, class Allocator>
inline
bool
operator< (const queue<T, Container, Allocator>& x,
           const queue<T, Container, Allocator>& y)
{
    return x.c < y.c;
}

// Subclause 23.2.4.2 -- clause priority_queue

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Container = vector<T>,
          class Compare = less<typename Container::value_type>,
          class Allocator = allocator<T> >
#else
template <class T, class Container, class Compare, class Allocator>
#endif
class  priority_queue {
public:
    typedef typename Container::value_type        value_type;
    typedef typename Container::size_type         size_type;

    typedef typename Container::const_iterator    iter_type;
    typedef          Allocator                    allocator_type;

protected:
    Container c;
    Compare   comp;

public:

    explicit
    priority_queue (const Compare& x = Compare (),
                    const Allocator& alloc = Allocator()) 
    :  c (alloc), comp (x) {}

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    priority_queue (InputIterator first, InputIterator last,
                    const Compare& x = Compare (),
                    const Allocator& alloc = Allocator())
    : c (first, last, alloc), comp (x) 
    {
        make_heap (c.begin (), c.end (), comp);
    }
#else
    priority_queue (iter_type first, iter_type last,
                    const Compare& x = Compare (),
                    const Allocator& alloc = Allocator())
    : c (first, last, alloc), comp (x)
    {
        make_heap (c.begin (), c.end (), comp);
    }
#endif /* MSIPL_MEMBER_TEMPLATE */

    allocator_type    get_allocator() const { return c.get_allocator (); }
    bool              empty ()        const { return c.empty (); }
    size_type         size ()         const { return c.size ();  }
    value_type&       top ()                { return c.front (); }
    const value_type& top ()          const { return c.front (); }

    void push (const value_type& x)
    {
        c.push_back (x); 
        push_heap (c.begin (), c.end (), comp);
    }
    void pop ()
    {
        pop_heap (c.begin (), c.end (), comp);
        c.pop_back (); 
    }
};

// no equality is provided

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_QUEUE_H */

//961210 bkoz added alignment wrapper