/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_COMPLEX_H
#define MSIPL_COMPLEX_H

#ifdef MSIPL_EDG232
#undef complex
#endif

#include <mcompile.h>

#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(sstream)
#include MOD_INCLUDE(extmath)
#include MOD_INCLUDE(utility)
#include MOD_INCLUDE(mutex)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Section 26.1 -- complex Numbers

//
// forward declarations
//
template <class T> class complex;
null_template class complex<float>;
null_template class complex<double>;
null_template class complex<long double>;

template <class T> class complex {
private:

    T  re_;
    T  im_;

    DEC_OBJ_LOCK(c_mutex)

public:

    typedef T value_type;

    complex (T re = T(), T im = T()) : re_ (re), im_ (im) {}

    ~complex () { REMOVE(c_mutex); }

    T real () const  { READ_LOCK(c_mutex); return re_; }

    T imag () const  { READ_LOCK(c_mutex); return im_; }

    complex <T>&
    operator= (const T& rhs)
    {
        // im_ = ?????????
        re_ = rhs;
        return *this;
    }

    complex <T>&
    operator+= (const T& rhs)
    {
        re_ += rhs;
        return *this;
    }

    complex <T>&
    operator-= (const T& rhs)
    {
        re_ -= rhs;
        return *this;
    }

    complex <T>&
    operator*= (const T& rhs)
    {
        re_ *= rhs;
        im_ *= rhs;
        return *this;
    }

    complex <T>&
    operator/= (const T& rhs)
    {
        re_ /= rhs;
        im_ /= rhs;
        return *this;
    }

#ifdef MSIPL_MEMBER_TEMPLATE

    template <class X>
    complex (const complex<X>& cx) 
                    : re_ (cx.real ()), im_ (cx.imag ()) {}

    //
    // Member operator functions
    //
    template <class X>
    complex<T>&
    operator= (const complex<X>& cx)
    {
        WRITE_LOCK(c_mutex);
        if (this != &cx)
        {
            re_ = cx.real ();
            im_ = cx.imag ();
        }
        return *this;
    }

    template <class X>
    complex<T>&
    operator+= (const complex<X>& cx)
    {
        WRITE_LOCK(c_mutex);
        re_ += cx.real ();
        im_ += cx.imag ();
        return *this;
    }

    template <class X>
    complex<T>&
    operator-= (const complex<X>& cx)
    {
        WRITE_LOCK(c_mutex);
        re_ -= cx.real ();
        im_ -= cx.imag ();
        return *this;
    }

    template <class X>
    complex<T>&
    operator*= (const complex<X>& cx)
    {
        WRITE_LOCK(c_mutex);
        T  re_t = re_*cx.real () - im_*cx.imag ();
        T  im_t = re_*cx.imag () + im_*cx.real ();
        re_ = re_t;
        im_ = im_t;
        return *this;
    }

    template <class X>
    complex<T>&
    operator/= (const complex<X>& cx)
    {
        // check for division by zero
        if (! (cx.real () || cx.imag ()))
        {
            __msipl_report_error ("Division by zero error");
        }
        T  value = __msipl_pow (cx.real (), 2) + __msipl_pow (cx.imag (), 2);
        WRITE_LOCK(c_mutex);
        T  re_t  = (re_*cx.real () + im_*cx.imag ())/value;
        T  im_t  = (im_*cx.real () - re_*cx.imag ())/value;
        re_ = re_t;
        im_ = im_t;
        return *this;
    }

#else

    complex (const complex<T>& cx)
                     : re_ (cx.real ()), im_ (cx.imag ()) {}

    //
    // Member operator functions
    //
    complex<T>&
    operator= (const complex<T>& cx)
    {
        WRITE_LOCK(c_mutex);
        if (this != &cx)
        {
            re_ = cx.real ();
            im_ = cx.imag ();
        }
        return *this;
    }

    complex<T>&
    operator+= (const complex<T>& cx)
    {
        WRITE_LOCK(c_mutex);
        re_ += cx.real ();
        im_ += cx.imag ();
        return *this;
    }

    complex<T>&
    operator-= (const complex<T>& cx)
    {
        WRITE_LOCK(c_mutex);
        re_ -= cx.real ();
        im_ -= cx.imag ();
        return *this;
    }

    complex<T>&
    operator*= (const complex<T>& cx)
    {
        WRITE_LOCK(c_mutex);
        T  re_t = re_*cx.real () - im_*cx.imag ();
        T  im_t = re_*cx.imag () + im_*cx.real ();
        re_ = re_t;
        im_ = im_t;
        return *this;
    }

    complex<T>&
    operator/= (const complex<T>& cx)
    {
        // check for division by zero
        if (! (cx.real () || cx.imag ()))
        {
            __msipl_report_error ("Division by zero error");
        }
        T  value = __msipl_pow (cx.real (), 2) + __msipl_pow (cx.imag (), 2);
        WRITE_LOCK(c_mutex);
        T  re_t  = (re_*cx.real () + im_*cx.imag ())/value;
        T  im_t  = (im_*cx.real () - re_*cx.imag ())/value;
        re_ = re_t;
        im_ = im_t;
        return *this;
    }

#endif

};

null_template
class complex<float> {

private :

    float re_;
    float im_;
 
    DEC_OBJ_LOCK(fl_mutex)

public :

    typedef float   value_type;

    complex (float re = 0.0f, float im = 0.0f) 
    : re_ (re), im_ (im) {}

    complex (const complex<float>& cx) 
    : re_ (cx.real ()), im_ (cx.imag ()) {}

    explicit complex (const complex<double>& cx);

    explicit complex (const complex<long double>& cx);
 
    ~complex () { REMOVE(fl_mutex); }

    float real () const { READ_LOCK(fl_mutex); return re_; }

    float imag () const { READ_LOCK(fl_mutex); return im_; }

    complex <float>&
    operator= (float rhs)
    {
        re_ = rhs;
        return *this;
    }

    complex <float>&
    operator+= (float rhs)
    {
        re_ += rhs;
        return *this;
    }

    complex <float>&
    operator-= (float rhs)
    {
        re_ -= rhs;
        return *this;
    }

    complex <float>&
    operator*= (float rhs)
    {
        re_ *= rhs;
        im_ *= rhs;
        return *this;
    }

    complex <float>&
    operator/= (float rhs)
    {
        re_ /= rhs;
        im_ /= rhs;
        return *this;
    }

#ifdef MSIPL_MEMBER_TEMPLATE

    template <class X>
    complex<float>&
    operator= (const complex<X>& cx);

    template <class X>
    complex<float>&
    operator+= (const complex<X>& cx);

    template <class X>
    complex<float>&
    operator-= (const complex<X>& cx);

    template <class X>
    complex<float>&
    operator*= (const complex<X>& cx);

    template <class X>
    complex<float>&
    operator/= (const complex<X>& cx);

#else

    complex<float>& operator= (const complex<float>& cx);
    complex<float>& operator+= (const complex<float>& cx);
    complex<float>& operator-= (const complex<float>& cx);
    complex<float>& operator*= (const complex<float>& cx);
    complex<float>& operator/= (const complex<float>& cx);

    complex<float>& operator= (const complex<double>& cx);
    complex<float>& operator+= (const complex<double>& cx);
    complex<float>& operator-= (const complex<double>& cx);
    complex<float>& operator*= (const complex<double>& cx);
    complex<float>& operator/= (const complex<double>& cx);
 
    complex<float>& operator= (const complex<long double>& cx);
    complex<float>& operator+= (const complex<long double>& cx);
    complex<float>& operator-= (const complex<long double>& cx);
    complex<float>& operator*= (const complex<long double>& cx);
    complex<float>& operator/= (const complex<long double>& cx);

#endif

};

null_template
class complex<double> {

private :

    double re_;
    double im_;

    DEC_OBJ_LOCK(d_mutex)

public :

    typedef double   value_type;

    complex (double re = 0.0, double im = 0.0) 
                     : re_ (re), im_ (im) {}

    complex (const complex<float>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}

    complex (const complex<double>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}

    explicit complex (const complex<long double>& cx);

    ~complex () { REMOVE(d_mutex); }

    double real () const { READ_LOCK(d_mutex); return re_; }

    double imag () const { READ_LOCK(d_mutex); return im_; }

    complex <double>&
    operator= (double rhs)
    {
        re_ = rhs;
        return *this;
    }

    complex <double>&
    operator+= (double rhs)
    {
        re_ += rhs;
        return *this;
    }

    complex <double>&
    operator-= (double rhs)
    {
        re_ -= rhs;
        return *this;
    }

    complex <double>&
    operator*= (double rhs)
    {
        re_ *= rhs;
        im_ *= rhs;
        return *this;
    }

    complex <double>&
    operator/= (double rhs)
    {
        re_ /= rhs;
        im_ /= rhs;
        return *this;
    }

#ifdef MSIPL_MEMBER_TEMPLATE

    template <class X>
    complex<double>&
    operator= (const complex<X>& cx);

    template <class X>
    complex<double>&
    operator+= (const complex<X>& cx);

    template <class X>
    complex<double>&
    operator-= (const complex<X>& cx);

    template <class X>
    complex<double>&
    operator*= (const complex<X>& cx);

    template <class X>
    complex<double>&
    operator/= (const complex<X>& cx);

#else

    complex<double>& operator= (const complex<float>& cx);
    complex<double>& operator+= (const complex<float>& cx);
    complex<double>& operator-= (const complex<float>& cx);
    complex<double>& operator*= (const complex<float>& cx);
    complex<double>& operator/= (const complex<float>& cx);

    complex<double>& operator= (const complex<double>& cx);
    complex<double>& operator+= (const complex<double>& cx);
    complex<double>& operator-= (const complex<double>& cx);
    complex<double>& operator*= (const complex<double>& cx);
    complex<double>& operator/= (const complex<double>& cx);

    complex<double>& operator= (const complex<long double>& cx);
    complex<double>& operator+= (const complex<long double>& cx);
    complex<double>& operator-= (const complex<long double>& cx);
    complex<double>& operator*= (const complex<long double>& cx);
    complex<double>& operator/= (const complex<long double>& cx);

#endif

};

null_template
class complex<long double> {

private :

    long double re_;
    long double im_;

    DEC_OBJ_LOCK(ld_mutex)

public :

    typedef long double   value_type;

    complex (long double re = 0.0l, long double im = 0.0l) 
                     : re_ (re), im_ (im) {}
 
    complex (const complex<float>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}
 
    complex (const complex<double>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}

    complex (const complex<long double>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}
 
    ~complex () { REMOVE(ld_mutex); }

    long double real () const { READ_LOCK(ld_mutex); return re_; }
 
    long double imag () const { READ_LOCK(ld_mutex); return im_; }

    complex <long double>&
    operator= (long double rhs)
    {
        re_ = rhs;
        return *this;
    }

    complex <long double>&
    operator+= (long double rhs)
    {
        re_ += rhs;
        return *this;
    }

    complex <long double>&
    operator-= (long double rhs)
    {
        re_ -= rhs;
        return *this;
    }

    complex <long double>&
    operator*= (long double rhs)
    {
        re_ *= rhs;
        im_ *= rhs;
        return *this;
    }

    complex <long double>&
    operator/= (long double rhs)
    {
        re_ /= rhs;
        im_ /= rhs;
        return *this;
    }

#ifdef MSIPL_MEMBER_TEMPLATE

    template <class X>
    complex<long double>&
    operator= (const complex<X>& cx);

    template <class X>
    complex<long double>&
    operator+= (const complex<X>& cx);

    template <class X>
    complex<long double>&
    operator-= (const complex<X>& cx);

    template <class X>
    complex<long double>&
    operator*= (const complex<X>& cx);

    template <class X>
    complex<long double>&
    operator/= (const complex<X>& cx);

#else

    complex<long double>& operator= (const complex<float>& cx);
    complex<long double>& operator+= (const complex<float>& cx);
    complex<long double>& operator-= (const complex<float>& cx);
    complex<long double>& operator*= (const complex<float>& cx);
    complex<long double>& operator/= (const complex<float>& cx);

    complex<long double>& operator= (const complex<double>& cx);
    complex<long double>& operator+= (const complex<double>& cx);
    complex<long double>& operator-= (const complex<double>& cx);
    complex<long double>& operator*= (const complex<double>& cx);
    complex<long double>& operator/= (const complex<double>& cx);

    complex<long double>& operator= (const complex<long double>& cx);
    complex<long double>& operator+= (const complex<long double>& cx);
    complex<long double>& operator-= (const complex<long double>& cx);
    complex<long double>& operator*= (const complex<long double>& cx);
    complex<long double>& operator/= (const complex<long double>& cx);

#endif
   
};

#ifdef MSIPL_MEMBER_TEMPLATE

template <class X>
inline
complex<float>&
complex<float>::operator= (const complex<X>& cx)
{
     WRITE_LOCK(fl_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(fl_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(fl_mutex);
    re_ -= cx.real ();
    im_ -= cx.imag ();
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(fl_mutex);
    float  re_t = re_*cx.real () - im_*cx.imag ();
    float  im_t = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    im_ = im_t;
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator/= (const complex<X>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Division by zero error");
    }
    float  value = __msipl_pow (float(cx.real ()), 2.0F) +
                   __msipl_pow (float(cx.imag ()), 2.0F);
    WRITE_LOCK(fl_mutex);
    float  re_t  = (re_*cx.real () + im_*cx.imag ())/value;
    float  im_t  = (im_*cx.real () - re_*cx.imag ())/value;
    re_ = re_t;
    im_ = im_t;
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator= (const complex<X>& cx)
{
     WRITE_LOCK(d_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(d_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(d_mutex);
    re_ -= cx.real ();
    im_ -= cx.imag ();
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(d_mutex);
    double  re_t = re_*cx.real () - im_*cx.imag ();
    double  im_t = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    im_ = im_t;
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator/= (const complex<X>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Division by zero error");
    }
    double  value = __msipl_pow ((double)cx.real (), 2.0) + 
                    __msipl_pow ((double)cx.imag (), 2.0);
    WRITE_LOCK(d_mutex);
    double  re_t  = (re_*cx.real () + im_*cx.imag ())/value;
    double  im_t  = (im_*cx.real () - re_*cx.imag ())/value;
    re_ = re_t;
    im_ = im_t;
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator= (const complex<X>& cx)
{
     WRITE_LOCK(ld_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(ld_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(ld_mutex);
    re_ -= (long double)cx.real ();
    im_ -= (long double)cx.imag ();
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(ld_mutex);
    long double  re_t = re_*cx.real () - im_*cx.imag ();
    long double  im_t = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    im_ = im_t;
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator/= (const complex<X>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Division by zero error");
    }
    long double  value = __msipl_pow ((long double)cx.real (), 2.0L) +
                         __msipl_pow ((long double)cx.imag (), 2.0L);
    WRITE_LOCK(ld_mutex);
    long double  re_t  = (re_*cx.real () + im_*cx.imag ())/value;
    long double  im_t  = (im_*cx.real () - re_*cx.imag ())/value;
    re_ = re_t;
    im_ = im_t;
    return *this;
}

#endif

//
// Section 26.2.6 complex value operations
//
template <class T> inline T real (const complex<T>& x)
{
    return x.real ();
}

template <class T> inline T imag (const complex<T>& x)
{
    return x.imag ();
}

template <class T> inline T arg (const complex<T>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Domain error");
    }
    return __msipl_atan2 (cx.imag (), cx.real ());
}

template <class T> inline T norm (const complex<T>& cx)
{
    return __msipl_pow (cx.real (), 2) + __msipl_pow (cx.imag (), 2);
}

template <class T> inline complex<T> conj (const complex<T>& cx)
{
    return complex<T> (cx.real (), -cx.imag ());
}

template <class T> inline complex<T> polar (const T& r, const T& arg)
{
    return complex<T> (r*__msipl_cos (arg), r*__msipl_sin (arg));
}

//
// implementation specific
//
template <class T> inline T abs (const complex<T>& cx)
{
    return __msipl_sqrt (norm (cx));
}

template <class T> inline complex<T> inv (const complex<T>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Inverse of zero error"); 
    }
    T value = norm (cx);
    //return complex<T> (cx.real ()/value, -cx.imag ()/value);     //MW-mm 961218
    return complex<T> (cx.real ()/value, cx.imag ()/value);       //Mw-mm 961218
}

//
// Section 26.2.7 complex transcendentals
//

// Yet to be implemented

// template <class T> inline complex<T> acos (const complex<T>& cx);
// template <class T> inline complex<T> asin (const complex<T>& cx);
// template <class T> inline complex<T> atan (const complex<T>& cx);

// template <class T> inline complex<T>
//       atan2 (const complex<T>& cx);
// template <class T> inline complex<T>
//       atan2 (const complex<T>& cx, T y);
// template <class T> inline complex<T>
//       atan2 (T x, const complex<T>& cx);
// template <class T> inline complex<T> log10 (const complex<T>& cx)


template <class T> inline complex<T> cos (const complex<T>& cx)
{
    return complex<T> (
      __msipl_cos (cx.real ())*__msipl_cosh (cx.imag ()) ,
      -__msipl_sin (cx.real ())*__msipl_sinh (cx.imag ())
                     );
}

template <class T> inline complex<T> cosh (const complex<T>& cx)
{
    return complex<T> (
      __msipl_cos (cx.imag ())*__msipl_cosh (cx.real ()) ,
      __msipl_sin (cx.imag ())*__msipl_sinh (cx.real ())
                     );
}

template <class T> inline complex<T> exp (const complex<T>& cx)
{
    T value = __msipl_exp (cx.real ());
    return complex<T> (value*__msipl_cos (cx.imag ()),
                      value*__msipl_sin (cx.imag ()));
}

template <class T> inline complex<T> log (const complex<T>& cx)
{
   return complex<T> (__msipl_log (abs (cx)), arg (cx));
}

template <class T> inline complex<T>
pow (const complex<T>& cb, const complex<T>& ce)
{
    return exp (ce*log (cb));
}

template <class T> inline complex<T> pow (const complex<T>& cx, T re)
{
    return polar (__msipl_pow (abs (cx), re), re*arg (cx));
}

template <class T> inline complex<T> pow (T re, const complex<T>& cx)
{
    return exp (re*log (cx));
}

template <class T> inline complex<T> pow (const complex<T>& cx, int i)
{
    return polar (__msipl_pow (abs (cx), i), i*arg (cx));
}

template <class T> inline complex<T> sin (const complex<T>& cx)
{
    return complex<T> (
      __msipl_sin (cx.real ())*__msipl_cosh (cx.imag ()) ,
      __msipl_cos (cx.real ())*__msipl_sinh (cx.imag ())
                     );
}

template <class T> inline complex<T> sinh (const complex<T>& cx)
{
    return complex<T> (
      __msipl_cos (cx.imag ())*__msipl_sinh (cx.real ()) ,
      __msipl_sin (cx.imag ())*__msipl_cosh (cx.real ())
                     );
}

//MSIPL 961218
template <class T> inline complex<T> sqrt (const complex<T>& cx)
{
    if (!cx.imag())                     
        if(!cx.real())
            return complex<T> ();
        else if(cx.real() == abs(cx))
            return complex<T> (__msipl_sqrt(abs(cx)), 0);
        else
            return complex<T> (0, __msipl_sqrt(abs(cx)));
    T value = __msipl_sqrt ((cx.real () + abs (cx))/2);
        return complex<T> (value, cx.imag ()/ (2*value));

}
//MSIPL 961218

template <class T> inline complex<T> tan (const complex<T>& cx)
{
    T value = __msipl_cos (2*cx.real ()) + __msipl_cosh (2*cx.imag ());
    if (value)
        return complex<T> (__msipl_sin (2*cx.real ())/value,
                          __msipl_sinh (2*cx.imag ())/value);
    else
        return complex<T> (__msipl_tan (cx.real ()), 0);
}

template <class T> inline complex<T> tanh (const complex<T>& cx)
{
    T value = __msipl_cos (2*cx.imag ()) + __msipl_cosh (2*cx.real ());
    if (value)
        return complex<T> (__msipl_sinh (2*cx.real ())/value,
                          __msipl_sin (2*cx.imag ())/value);
    else
        return complex<T> (0, __msipl_tan (cx.real ()));
}

//
// Section 26.2.5 complex non-member operations
//
template <class T> inline complex<T> operator+ (const complex<T>& cx)
{
    return complex<T> (cx.real (), cx.imag ());
}

template <class T>
inline complex<T>
operator+ (const complex<T>& c1, const complex<T>& c2)
{
    return complex<T> (c1.real ()+c2.real (), c1.imag ()+c2.imag ());
}

template <class T> inline complex<T> operator+ (T re, const complex<T>& cx)
{
    return complex<T> (re+cx.real (), cx.imag ());
}

template <class T> inline complex<T> operator+ (const complex<T>& cx, T re)
{
    return complex<T> (re+cx.real (), cx.imag ());
}

template <class T>
inline complex<T>
operator- (const complex<T>& cx)
{
    return complex<T> (-cx.real (), -cx.imag ());
}

template <class T>
inline complex<T>
operator- (const complex<T>& c1, const complex<T>& c2)
{
    return complex<T> (c1.real ()-c2.real (), c1.imag ()-c2.imag ());
}

template <class T> inline complex<T> operator- (T re, const complex<T>& cx)
{
    return complex<T> (re-cx.real (), - (cx.imag ()));
}

template <class T> inline complex<T> operator- (const complex<T>& cx, T re)
{
    return complex<T> (cx.real ()-re, cx.imag ());
}

template <class T>
inline complex<T>
operator* (const complex<T>& c1, const complex<T>& c2)
{
    return complex<T> ((c1.real ()*c2.real ()-c1.imag ()*c2.imag ()),
                      (c1.real ()*c2.imag ()+c2.real ()*c1.imag ()));
}

template <class T> inline complex<T> operator* (T re, const complex<T>& cx)
{
    return complex<T> (re*cx.real (), re*cx.imag ());
}

template <class T> inline complex<T> operator* (const complex<T>& cx, T re)
{
    return complex<T> (re*cx.real (), re*cx.imag ());
}

template <class T>
inline complex<T>
operator/ (const complex<T>& c1, const complex<T>& c2)
{
    // check for division by zero
    if (! (c2.real () || c2.imag ()))
    {
        __msipl_report_error ("Division by zero error");
    }
    T value = norm (c2);
    return complex<T> (
      (c1.real ()*c2.real ()+c1.imag ()*c2.imag ())/value,
      (c2.real ()*c1.imag ()-c1.real ()*c2.imag ())/value
                     );
}

template <class T> inline complex<T> operator/ (T re, const complex<T>& cx)
{
    // check for division by zero
    if (! (cx.real () || cx.imag ()))
    {
        __msipl_report_error ("Division by zero error");
    }
    T value = norm (cx);
    return complex<T> (re*cx.real ()/value, -re*cx.imag ()/value);
}

template <class T> inline complex<T> operator/ (const complex<T>& cx, T re)
{
    // check for division by zero
    if (!re)
    {
       __msipl_report_error ("Division by zero error");
    }
    return complex<T> (cx.real ()/re, cx.imag ()/re);
}

template <class T>
inline bool
operator== (const complex<T>& c1, const complex<T>& c2)
{
    return ((c1.real () == c2.real ()) && (c1.imag () == c2.imag ()));
}

template <class T> inline bool operator== (T re, const complex<T>& cx)
{
    return ((re == cx.real ()) && (!cx.imag ()));
}

template <class T> inline bool operator== (const complex<T>& cx, T re)
{
    return ((re == cx.real ()) && (!cx.imag ()));
}

#ifdef  MSIPL_NONDEF
template <class T>
inline
bool
operator!= (const complex<T>& c1, const complex<T>& c2)
{
    return ((c1.real () != c2.real ()) || (c1.imag () != c2.imag ()));
}
#endif /* MSIPL_NONDEF */

template <class T> inline bool operator!= (T re, const complex<T>& cx)
{
    return ((re != cx.real ()) || (cx.imag ()));
}

template <class T> inline bool operator!= (const complex<T>& cx, T re)
{
    return ((re != cx.real ()) || (cx.imag ()));
}

template <class T, class charT, class traits>
inline
basic_istream<charT, traits>&
operator>> (basic_istream<charT, traits>& is, complex<T>& cx)
{
    T    re_t = 0, im_t = 0;
    char ch;
    is >> ch;
    if (ch == '(')               // if '(' : one of (re), (re, im)
    {
       is >> re_t >> ch;
       if (ch == ',') { is >> im_t >> ch; }
       if (ch != ')')            // no ')' : error
       {
           is.setstate (ios_base::failbit);
           return is;
       }
    } else                       // no '(' in the beginning: "re"
    {
       is.putback (ch);    
       is >> re_t;
    }

    // check "is" is in good state
    if (!is.fail())
       cx = complex<T> (re_t, im_t);
    return is;
}

template <class T, class charT, class traits>
inline
basic_ostream<charT, traits>&
operator<< (basic_ostream<charT, traits>& os, const complex<T>& cx)
{
    basic_ostringstream<charT, traits> s;
    s.flags (os.flags ());
    s.imbue (os.getloc ());
    s.precision (os.precision ());
    s << '(' << cx.real () << ',' << cx.imag () << ')' << ends;
    return os << s.str ();
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_COMPLEX_H */

/* change record
//961210 bkoz added alignment wrappers
//MW-mm 961218  Correction to inv to get value collinear with given point and origin
//MSIPL 961218  Rewritten version of sqrt from Modena
*/