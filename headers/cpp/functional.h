/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_FUNCTIONAL_H
#define MSIPL_FUNCTIONAL_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 20.3
// Section 20.3.1 -- Base

template <class Arg, class Result>
struct unary_function {
    typedef Arg       argument_type;
    typedef Result    result_type;
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1     first_argument_type;
    typedef Arg2     second_argument_type;
    typedef Result   result_type;
};      

// Section 20.3.2 -- Arithmetic operations

template <class T>
struct plus : binary_function<T, T, T> {
    typedef typename binary_function<T, T, T>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, T>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, T>::result_type
                     result_type;
    T operator () (const T& x, const T& y) const { return x + y; }
};

template <class T>
struct minus : binary_function<T, T, T> {
    typedef typename binary_function<T, T, T>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, T>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, T>::result_type
                     result_type;
    T operator () (const T& x, const T& y) const { return x - y; }
};

template <class T>
struct multiplies : binary_function<T, T, T> {
    typedef typename binary_function<T, T, T>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, T>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, T>::result_type
                     result_type;
    T operator () (const T& x, const T& y) const { return x * y; }
};

template <class T>
struct divides : binary_function<T, T, T> {
    typedef typename binary_function<T, T, T>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, T>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, T>::result_type
                     result_type;
    T operator () (const T& x, const T& y) const { return x / y; }
};

template <class T>
struct modulus : binary_function<T, T, T> {
    typedef typename binary_function<T, T, T>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, T>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, T>::result_type
                     result_type;

    T operator () (const T& x, const T& y) const { return x % y; }
};

template <class T>
struct negate : unary_function<T, T> {

    T operator () (const T& x) const { return -x; }
};

// Section 20.3.3 -- Comparisons

template <class T>
struct equal_to : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const
    {
         return x == y; 
    }
};

template <class T>
struct not_equal_to : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const { return x != y; }
};

template <class T>
struct greater : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const { return x > y; }
};

template <class T>
struct less : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const
    {
         return x < y; 
    }
};

template <class T>
struct greater_equal : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const { return x >= y; }
};

template <class T>
struct less_equal : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const { return x <= y; }
};

// Section 20.3.4 -- Logical operations

template <class T>
struct logical_and : binary_function<T, T, bool> {
    typedef typename binary_function<T, T, bool>::first_argument_type
                     first_argument_type;
    typedef typename binary_function<T, T, bool>::second_argument_type
                     second_argument_type;
    typedef typename binary_function<T, T, bool>::result_type
                     result_type;

    bool operator () (const T& x, const T& y) const { return x && y; }
};

template <class T>
struct logical_or : binary_function<T, T, bool> {
    bool operator () (const T& x, const T& y) const { return x || y; }
};

template <class T>
struct logical_not : unary_function<T, bool> {

    bool operator () (const T& x) const { return !x; }
};

// Section 20.3.5 -- Negators

template <class Predicate>
class unary_negate : public unary_function<typename Predicate::argument_type,
                                           bool> {
protected:
    Predicate pred;
public:
    typedef typename Predicate::argument_type argument_type;
    explicit
    unary_negate (const Predicate& x) : pred (x) {}
    bool operator () (const argument_type& x) const { return !pred (x); }
};

template <class Predicate>
inline
unary_negate<Predicate> not1 (const Predicate& pred)
{
    return unary_negate<Predicate> (pred);
}

template <class Predicate> 
class binary_negate 
    : public binary_function<typename Predicate::first_argument_type,
                             typename Predicate::second_argument_type, bool> {
protected:
    Predicate pred;
public:
    explicit
    binary_negate (const Predicate& x) : pred (x) {}
    bool operator () (const typename Predicate::first_argument_type& x, 
                      const typename Predicate::second_argument_type& y) const
    {
        return !pred (x, y); 
    }
};

template <class Predicate>
inline
binary_negate<Predicate> not2 (const Predicate& pred)
{
    return binary_negate<Predicate> (pred);
}

// Section 20.3.6   -- Binders
// Section 20.3.6.1 -- binder1st

template <class Operation> 
class binder1st 
  : public unary_function<typename Operation::second_argument_type,
                          typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::first_argument_type value;
public:
    typedef typename Operation::second_argument_type argument_type;
    binder1st (const Operation& x,
               const typename Operation::first_argument_type& y)
              : op (x), value (y) {}
    typename Operation::result_type
    operator () (const argument_type& x) const 
    {
        return op (value, x); 
    }
};

// Section 20.3.6.2 -- bind1st

template <class Operation, class T>
inline
binder1st<Operation> bind1st (const Operation& op, const T& x)
{
    return binder1st<Operation> (op, Operation::first_argument_type (x));
}

// Section 20.3.6.3 -- binder2nd

template <class Operation> 
class binder2nd 
  : public unary_function<typename Operation::first_argument_type,
                          typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    typedef typename Operation::first_argument_type argument_type;
    binder2nd (const Operation& x,
               const typename Operation::second_argument_type& y) 
        : op (x), value (y) {}

    typename Operation::result_type
    operator () (const argument_type& x) const 
    {
        return op (x, value); 
    }
};

// Section 20.3.6.4 -- bind2nd

template <class Operation, class T>
inline
binder2nd<Operation> bind2nd (const Operation& op, const T& x)
{
    return binder2nd<Operation> (op, Operation::second_argument_type (x));
}

// Section 20.3.7 -- Adaptors for pointers to functions

template <class Arg, class Result>
class pointer_to_unary_function : public unary_function<Arg, Result> {
protected:
    Result (*ptr) (Arg);
public:
    pointer_to_unary_function () {}  // For Compare () default argument
    explicit
    pointer_to_unary_function (Result (*x) (Arg)) : ptr (x) {}
    Result operator () (const Arg& x) const { return ptr (x); }
};

template <class Arg, class Result>
inline
pointer_to_unary_function<Arg, Result> ptr_fun (Result (*x) (Arg))
{
    return pointer_to_unary_function<Arg, Result> (x);
}

template <class Arg1, class Arg2, class Result>
class pointer_to_binary_function 
          : public binary_function<Arg1, Arg2, Result> {
protected:
    Result (*ptr) (Arg1, Arg2);
public:
    pointer_to_binary_function () {}  // For Compare () default argument
    explicit
    pointer_to_binary_function (Result (*x) (Arg1, Arg2)) : ptr (x) {}
    Result operator () (const Arg1& x, const Arg2& y) const
    { 
        return ptr (x, y); 
    }
};

template <class Arg1, class Arg2, class Result>
inline
pointer_to_binary_function<Arg1, Arg2, Result> 
ptr_fun (Result (*x) (Arg1, Arg2))
{
    return pointer_to_binary_function<Arg1, Arg2, Result> (x);
}

//961204 bkoz
/*template <class S, class T> 
class mem_fun_t : public unary_function<T*, S> {
protected:
    S (T::*ptr) ();		//961204 bkoz will not compile, mwcppc cannot scope like this
    //S (*ptr) ();				//961204 bkoz
public:
    mem_fun_t () {}     
    explicit mem_fun_t (S (T::*p)()): ptr(p) { }; //961204 bkoz here we are also screwed
    //mem_fun_t (S (*p)()): ptr(p) { };
    S operator () (T* p) { return (p->*ptr) (); }
};


template <class S, class T>
inline
mem_fun_t <S, T>
mem_fun (S (T::*f)())
{
    return mem_fun_t<S, T> (f);
}


template <class S, class T, class A> 
class mem_fun1_t : public binary_function<T*, A, S> {
protected:
    S (T::*ptr) (A);
public:
    mem_fun1_t () {}     
    explicit
    mem_fun1_t (S (T::*p)(A)): ptr(p) { };
    S operator () (T* p, A x) { return (p->*ptr)(x); }
};

template <class S, class T, class A>
inline
mem_fun1_t <S, T, A>
mem_fun1 (S (T::*f)(A))
{
    return mem_fun1_t<S, T, A> (f);
}

template <class S, class T> 
class mem_fun_ref_t : public unary_function<T, S> {

protected:
    S (T::*ptr) ();
public:
    mem_fun_ref_t () {}     
    explicit
    mem_fun_ref_t (S (T::*p)()): ptr(p) { };
    S operator () (T& r) { return (r.*ptr)(); }
};

template <class S, class T>
inline
mem_fun_ref_t <S, T>
mem_fun_ref (S (T::*f)())
{
    return mem_fun_ref_t<S, T> (f);
}

template <class S, class T, class A> 
class mem_fun1_ref_t : public binary_function<T, A, S> {

protected:
    S (T::*ptr) (A);
public:
    mem_fun1_ref_t () {}     
    explicit
    mem_fun1_ref_t (S (T::*p)(A)): ptr(p) { };
    S operator () (T& r, A x) { return (r.*ptr)(x); }
};

template <class S, class T, class A>
inline
mem_fun1_ref_t <S, T, A>
mem_fun1_ref (S (T::*f)(A))
{
    return mem_fun1_ref_t<S, T, A> (f);
}
*/
//end bkoz

//
// The following is not a part of DRAFT
//
template <class Operation1, class Operation2>
class unary_compose 
  : public unary_function<typename Operation2::argument_type,
                          typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
public:
    typedef typename unary_function<typename Operation2::argument_type,
            typename Operation1::result_type>::argument_type argument_type;
    unary_compose (const Operation1& x, const Operation2& y)
    : op1 (x), op2 (y) {}

    typename Operation1::result_type 
    operator () (const argument_type& x) const
    {
        return op1 (op2 (x));
    }
};

template <class Operation1, class Operation2>
inline
unary_compose<Operation1, Operation2> compose1 (const Operation1& op1, 
                                               const Operation2& op2)
{
    return unary_compose<Operation1, Operation2> (op1, op2);
}

template <class Operation1, class Operation2, class Operation3>
class binary_compose 
  : public unary_function<typename Operation2::argument_type,
                          typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
    Operation3 op3;
public:
    typedef typename unary_function<typename Operation2::argument_type,
            typename Operation1::result_type>::argument_type argument_type;
    binary_compose (const Operation1& x, const Operation2& y, 
                   const Operation3& z) : op1 (x), op2 (y), op3 (z) { }
    typename Operation1::result_type
    operator () (const argument_type& x) const
    {
        return op1 (op2 (x), op3 (x));
    }
};

template <class Operation1, class Operation2, class Operation3>
inline
binary_compose<Operation1, Operation2, Operation3> 
compose2 (const Operation1& op1, const Operation2& op2,
         const Operation3& op3)
{
    return binary_compose<Operation1, Operation2,
                          Operation3> (op1, op2, op3);
}

template <class T, class U>
struct select1st : public unary_function<T, U> {
    const U& operator () (const T& x) const { return x.first; }
};
 
template <class T, class U>
struct ident : public unary_function<T, U> {
    const U& operator () (const T& x) const { return x; }
};

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_FUNCTIONAL_H */

//961204 	bkoz commented out line 353-434, as mwcppc cannot scope template members, thus this
//				code is unusable. Unfortunately this limits the unsefulness of algorithm.h
//961210 bkoz added alignment wrapper