/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_STACK_H
#define MSIPL_STACK_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 23.2.4.3 -- class stack

#ifdef MSIPL_DEF_TEMPARG
	template <class T, class Container = deque<T>, class Allocator = allocator<T> >
#else
	template <class T, class Container, class Allocator>
#endif
class stack {

    friend bool
    operator== (const stack<T, Container, Allocator>& x,
                const stack<T, Container, Allocator>& y);
    friend bool
    operator< (const stack<T, Container, Allocator>& x,
               const stack<T, Container, Allocator>& y);

public:
    typedef typename Container::value_type    value_type;
    typedef typename Container::size_type     size_type;
    typedef          Allocator                allocator_type;

protected:

    Container c;

public:

	explicit stack (const Allocator& alloc = Allocator()):c(alloc) {};
	
    allocator_type      get_allocator() const { return c.get_allocator(); }; //970402 bkoz

    bool                empty ()   const { return c.empty (); }
    size_type           size ()    const { return c.size ();  }
    value_type&         top ()           { return c.back ();  }
    const value_type&   top ()     const { return c.back ();  }

    void                push (const value_type& x) { c.push_back (x); }
    void                pop ()                     { c.pop_back (); }

};

template <class T, class Container, class Allocator>
inline
bool
operator== (const stack<T, Container, Allocator>& x,
            const stack<T, Container, Allocator>& y)
{
    return x.c == y.c;
}

template <class T, class Container, class Allocator>
inline
bool
operator< (const stack<T, Container, Allocator>& x,
           const stack<T, Container, Allocator>& y)
{
    return x.c < y.c;
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_STACK_H */

//961121 bkoz took out default argument
//961210 bkoz added alignment wrapper
//970402 line 52 added default argument to stack::stack(allocator)
//970402 line 52 stack::get_allocator() added parens
