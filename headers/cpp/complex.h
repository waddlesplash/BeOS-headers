/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.3, 29th May 1997
 **
 ** Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_COMPLEX_H
#define MSIPL_COMPLEX_H

#ifdef MSIPL_EDG232
#undef complex
#endif

#include <mcompile.h>
#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(sstream)                     								
#include MOD_INCLUDE(utility)
#include MOD_INCLUDE(mutex)
#ifdef MSIPL_USE_EXTERNAL_MATHLIB
	#define __MSL_C9X__
	#include <math.h>	//970402 bkoz added for MSIPL_USE_EXTERNAL_MATHLIB
#endif

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

   
public:

	DEC_OBJ_LOCK(c_mutex)
    typedef T value_type;
   // complex (const T& re = T(), const T& im = T()) : re_ (re), im_ (im) {}
    complex (const T& re , const T& im) : re_ (re), im_ (im) {}
    ~complex () { REMOVE(c_mutex); }

    T real () const  { READ_LOCK(c_mutex); return re_; }
    
    T imag () const  { READ_LOCK(c_mutex); return im_; }

    complex <T>&
    operator= (const T& rhs)
    {
        
        im_ = 0.0;   //in draft standard section 6.2.1.6( m. fassiotto 6/16/97)
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
        im_ = re_*cx.imag () + im_*cx.real ();
        re_ = re_t;
        return *this;
    }

    template <class X>
    complex<T>&
    operator/= (const complex<X>& cx)
    {
        
        // allow division by zero(return infinity !! m. fassiotto 062697
        // the app writer can use fetestexcept to check fpu flags.
        
    double a, b, c, d, logbw, denom;
 	long llogbw = 0;
	a = (double)  re_; 
	b = (double)  im_; 
	c = (double)  cx.real(); 
	d = (double)  cx.imag();
	logbw = logb(fmax(fabs(c), fabs(d)));  //returns -infinity and raises
										  // divide by zero for cx=0
	if (isfinite(logbw)) 
	{
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	else {
	if(isnan(c) || isnan(d))
	{
	    re_=NAN;
	    im_=NAN;
	    return *this;
	}
		re_=re_/0.0 ;
		im_=im_ /0.0 ;
		return *this ;
	}
	denom =c*c + d*d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
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
        im_ = re_*cx.imag () + im_*cx.real ();
        re_ = re_t;
        return *this;
    }

    complex<T>&
    operator/= (const complex<T>& cx)
    {
  	<T> a, b, c, d, logbw, denom;
 	
	long llogbw = 0;
	a = (<T>)  re_; 
	b = (<T>)  im_; 
	c = (<T>)  cx.real(); 
	d = (<T>)  cx.imag();
	
	
	logbw = logb( fmax(fabs(c), fabs(d))  );
	if (isfinite(logbw)) {
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	else {
	if(isnan(c) || isnan(d))
	{
	    re_=NAN;
	    im_=NAN;
	    return *this;
	}
		re_=re_/0.0 ;
		im_=im_ /0.0 ;
		return *this ;
	}
	denom = c * c + d * d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
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
        im_ = 0.0 ;
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

    double real () const { READ_LOCK(c_mutex); return re_; }

    double imag () const { READ_LOCK(c_mutex); return im_; }

    complex <double>&
    operator= (double rhs)
    {
        re_ = rhs;
        im_ =0.0 ;
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



public :
    DEC_OBJ_LOCK(c_mutex)
    typedef long double   value_type;

    complex (long double re = 0.0l, long double im = 0.0l) 
                     : re_ (re), im_ (im) {}
 
    complex (const complex<float>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}
 
    complex (const complex<double>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}

    complex (const complex<long double>& cx) 
                     : re_ (cx.real ()), im_ (cx.imag ()) {}
 
    ~complex () { REMOVE(c_mutex); }
//    ~complex () { REMOVE(ld_mutex); }   /* Be 971107 */

    long double real () const { READ_LOCK(c_mutex); return re_; }
 
    long double imag () const { READ_LOCK(c_mutex); return im_; }

    complex <long double>& operator= (long double rhs)
    {
        re_ = rhs;
        im_ = 0.0 ;
        return *this;
    }

    complex <long double>& operator+= (long double rhs)
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
     WRITE_LOCK(c_mutex);
     READ_LOCK(cx.c_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ -= cx.real ();
    im_ -= cx.imag ();
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    float  re_t = re_*cx.real () - im_*cx.imag ();
    im_ = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    return *this;
}

template <class X>
inline
complex<float>&
complex<float>::operator/= (const complex<X>& cx)
{
   double a, b, c, d, logbw, denom;
 	long llogbw = 0;
	a = (double)  re_; 
	b = (double)  im_; 
	c = (double)  cx.real(); 
	d = (double)  cx.imag();
	
	logbw = logb( fmax(fabs(cx.real()), fabs(cx.imag()))  );
	if (isfinite(logbw)) 
	{
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	
	denom = divisor.real()*divisor.real() + d * d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator= (const complex<X>& cx)
{
     WRITE_LOCK(c_mutex);
     READ_LOCK(cx.c_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ -= cx.real ();
    im_ -= cx.imag ();
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    double  re_t = re_*cx.real () - im_*cx.imag ();
    im_ = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    return *this;
}

template <class X>
inline
complex<double>&
complex<double>::operator/= (const complex<X>& cx)
{
   template <class X>
inline
complex<long double>&
complex<long double>::operator/= (const complex<X>& cx)
{
	long double a, b, c, d, logbw, denom;
 	long llogbw = 0;
	a = (long double)  re_; 
	b = (long double)  im_; 
	c = (long double)  cx.real(); 
	d = (long double)  cx.imag();
	logbw = logb( fmax(fabs(c), fabs(d))  );
	if (isfinite(logbw)) {
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	else {
	if(isnan(c) || isnan(d))
	{
	    re_=NAN;
	    im_=NAN;
	    return *this;
	}
		re_=re_/0.0 ;
		im_=im_ /0.0 ;
		return *this ;
	}
	denom = c * c + d * d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator= (const complex<X>& cx)
{
     WRITE_LOCK(c_mutex);
     READ_LOCK(cx.c_mutex);
     re_ = cx.real ();
     im_ = cx.imag ();
     return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator+= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ += cx.real ();
    im_ += cx.imag ();
    return *this;
}

template <class X>
inline complex<long double>&
complex<long double>::operator-= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    re_ -= (long double)cx.real ();
    im_ -= (long double)cx.imag ();
    return *this;
}

template <class X>
inline complex<long double>&
complex<long double>::operator*= (const complex<X>& cx)
{
    WRITE_LOCK(c_mutex);
    READ_LOCK(cx.c_mutex);
    long double  re_t = re_*cx.real () - im_*cx.imag ();
    im_ = re_*cx.imag () + im_*cx.real ();
    re_ = re_t;
    return *this;
}

template <class X>
inline
complex<long double>&
complex<long double>::operator/= (const complex<X>& cx)
{
	long double a, b, c, d, logbw, denom;
 	
	long llogbw = 0;
	a = (long double)  re_; 
	b = (long double)  im_; 
	c = (long double)  cx.real(); 
	d = (long double)  cx.imag();
	
	
	logbw = logb( fmax(fabs(c), fabs(d))  );
	if (isfinite(logbw)) {
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	else {
	if(isnan(c) || isnan(d))
	{
	    re_=NAN;
	    im_=NAN;
	    return *this;
	}
		re_=re_/0.0 ;
		im_=im_ /0.0 ;
		return *this ;
	}
	denom = c * c + d * d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
	return *this;
    
}

#endif

//
// Section 26.2.6 complex value operations
//
template <class T> 
inline 
T real (const complex<T>& x)
{
    return x.real ();
}

template <class T> 
inline 
T imag (const complex<T>& x){
    return x.imag ();
}

template <class T> 
inline 
T arg (const complex<T>& cx){
    return atan2 ((double)cx.imag(),(double)cx.real());
}


//970424 via marcotty
template <class T> 
inline 
T norm (const complex<T>& cx) 
{
  return ( cx.real()*cx.real() + cx.imag()*cx.imag());
}

template <class T> 
inline 
complex<T> conj (const complex<T>& cx) 
{
  return complex<T> (cx.real (), -cx.imag ());
}

template <class T> 
inline 
complex<T> polar (const T& r, const T& arg){
    return complex<T> (r*cos (arg), r*sin (arg));
}

//
// implementation specific
//

//970320 bkoz/fassiotto
template <class T> 
inline 
T abs (const complex<T>& cx) 
{
    return (T) hypot(cx.real(),cx.imag());
}

//removed inv function completely.  It's functionality is
// completely supported by the complex division operator
// matt fassiotto- 6/16/97 and is not in the standard.

//
// Section 26.2.7 complex transcendentals
template <class T> 
inline 
complex<T> sqrt (const complex<T>& cx)
{
	T theta = .5*atan2((double)cx.imag(),(double)cx.real()); //half angle(demoivre's thm.)
	T r = sqrt( (T) hypot(cx.real() ,cx.imag() ) );  //sqrt of original magnitude from Demoivre's theorem.
	return complex<T> ( r*cos(theta), r*sin(theta) );				
}

template <class T> 
inline 
complex<T> log (const complex<T>& cx)
{
   return complex<T> (log (abs (cx)), arg (cx));
}

template <class T>
inline 
complex<T> log10 (const complex<T>& cx)
{
   return complex<T> (log(cx)/log(10.0));
}



template <class T> 
inline 
complex<T> exp (const complex<T>& cx)
{
    T value = exp (cx.real ());
    return complex<T> (value*cos (cx.imag ()),
                      value*sin (cx.imag ()));
}

template <class T> 
inline 
complex<T>pow (const complex<T>& cb, const complex<T>& ce)
{
    return exp (ce*log (cb));
}

template <class T> 
inline 
complex<T> pow (const complex<T>& cx, T re)
{
    return polar (pow ((long double) abs(cx), (long double) re), re*arg (cx));
}


template <class T> inline complex<T> pow (const complex<T>& cx, const T& re)
{ 
	return polar (pow ((double)abs (cx), (double)re), re*arg (cx)); 
}

template <class T> 
inline 
complex<T> pow (const complex<T>& cx, int i)
{
    return polar (pow (abs(cx), (long double) i), i*arg (cx));
}

template <class T>
inline 
complex<T> pow (const T& re, const complex<T>& cx)
{ return exp (cx*((T)log (re))); }

//complex trig functions

template <class T>
inline
complex<T> sin (const complex<T>& cx)
{ 
    return complex<T> (
      sin (cx.real ())*cosh (cx.imag ()) ,
      cos (cx.real ())*sinh (cx.imag ())
                     );
}

template <class T> 
inline 
complex<T> cos (const complex<T>& cx)
{
    return complex<T> (
      cos (cx.real ())*cosh (cx.imag ()) ,
      -sin (cx.real ())*sinh (cx.imag ())
                     );
}

template <class T>
inline 
complex<T> tan (const complex<T>& cx)
{
    T value = cos(2.*cx.real ()) + cosh(2.*cx.imag ());
    return complex<T> (sin(2.*cx.real ())/value,
                           sinh(2.*cx.imag ())/value);
}	  // return a correctly signed infinity and raise fpu flag upon 
      // division by zero (m. fassiotto 7/7/97
      // use fetestexcept from fenv.h to check for exceptions

template <class T>
inline
complex<T> sinh (const complex<T>& cx)
{
    return complex<T> (
      cos (cx.imag ())*sinh (cx.real ()) ,
      sin (cx.imag ())*cosh (cx.real ())
                     );
}

template <class T>
inline 
complex<T> cosh (const complex<T>& cx)
{
    return complex<T> (
      cos (cx.imag ())*cosh (cx.real ()) ,
      sin (cx.imag ())*sinh (cx.real ())
                     );
}

template <class T>
inline 
complex<T> tanh (const complex<T>& cx)
{
    T value = sin(cx.imag ())*sin(cx.imag ()) + cosh (cx.real ())*cosh (cx.real ());
  
        return complex<T> (sinh (2.* cx.real ())/value,
                          sin (2.* cx.imag ())/value);
}

//MSIPL 961218
//970320 bkoz/fassiotto
/*  tanh used to have the wrong denominator. rewrote it 7/9/97  m. fassiotto
*/
//MSIPL 961218
//970320 bkoz/fassiotto

//
// Section 26.2.5 complex non-member operations
//
template <class T> 
inline 
complex<T> operator+ (const complex<T>& cx)
{
    return complex<T> (cx.real (), cx.imag ());
}

template <class T>
inline 
complex<T> operator+ (const complex<T>& c1, const complex<T>& c2)
{
    return complex<T> (c1.real () + c2.real (), c1.imag () + c2.imag ());
}

template <class T> 
inline complex<T> 
operator+ (T re, const complex<T>& cx)
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

template <class T> 
inline complex<T>
operator- (T re, const complex<T>& cx)
{
    return complex<T> (re-cx.real (), - (cx.imag ()));
}

template <class T> 
inline complex<T> 
operator- (const complex<T>& cx, T re)
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

template <class T> 
inline complex<T>
operator* (T re, const complex<T>& cx)
{
    return complex<T> (re*cx.real (), re*cx.imag ());
}

template <class T> inline complex<T> operator* (const complex<T>& cx, const T& re)
{ return complex<T> (re*cx.real (), re*cx.imag ()); }





//970423 bkoz
//re-write to use pending C9X division, extended numeric support


template <class T>
inline
complex<T> operator/ (const complex<T>& c1, const complex<T>& c2)
{
 	double a, b, c, d, logbw, denom;
	long llogbw = 0;
	T re_(0);
	T im_(0);
	a = (double)  c1.real(); 
	b = (double)  c1.imag(); 
	c = (double)  c2.real(); 
	d = (double)  c2.imag();
	logbw = logb( fmax(fabs(c), fabs(d))  );
	if (isfinite(logbw)) {
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	denom = c * c + d * d;
	re_ = scalb((a * c + b * d) / denom, -llogbw);
	im_ = scalb((b * c - a * d) / denom, -llogbw);
	
    return complex<T> (re_, im_);
}
template <class T> inline 
complex<T> 
operator/ (const T& re, const complex<T>& cx)
{
        double a, c, d, logbw, denom;
 	long llogbw = 0;
	T re_(0);
	T im_(0);
	a = (double)  re; 
	c = (double)  cx.real(); 
	d = (double)  cx.imag();
	
	logbw = logb( fmax(fabs(c), fabs(d))  );
	if (isfinite(logbw)) {
		llogbw = (long)logbw;
		c = scalb(c, -llogbw);
		d = scalb(d, -llogbw);
	}
	denom = c * c + d * d;
	re_ = scalb((a * c) / denom, -llogbw);
	im_ = scalb((- a * d) / denom, -llogbw);
	return complex<T> (re_, im_);   
}

template <class T> 
inline 
complex<T> operator/ (const complex<T>& cx, T re)
{
	T re_(cx.real()/re);
	T im_(cx.imag()/re);
 	return complex<T> (re_, im_);
}


template <class T>
inline 
bool
operator== (const complex<T>& c1, const complex<T>& c2)
{
    return ((c1.real () == c2.real ()) && (c1.imag () == c2.imag ()));
}

template <class T> 
inline 
bool operator== (T re, const complex<T>& cx)
{
    return ((re == cx.real ()) && (!cx.imag ()));
}

template <class T> 
inline 
bool operator== (const complex<T>& cx, T re)
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
       if (!is.fail() && ch == ',') { is >> im_t >> ch; }
       if (!is.fail() && ch != ')')            // no ')' : error
       {
           is.setstate (ios_base::failbit);
           return is;
       }
    } else if(!is.fail())                      // no '(' in the beginning: "re"
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
inline basic_ostream<charT, traits>&
operator<< (basic_ostream<charT, traits>& os, const complex<T>& cx)
{
    return os << '(' << cx.real() << "," << cx.imag() << ')';
}

#ifdef __MSL_NO_INSTANTIATE__
	template __dont_instantiate class complex<float>;
	template __dont_instantiate class complex<double>;
	template __dont_instantiate class complex<long double>;
	/*
	template __dont_instantiate bool  operator!=<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate bool  operator!=<float> (const complex<float>&, float);
	template __dont_instantiate bool  operator!=<float> (float, const complex<float>&);
	template __dont_instantiate complex<float>  operator+<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate complex<float>  operator+<float> (const complex<float>&);
	template __dont_instantiate complex<float>  operator+ <float> (const complex<float>&, float);
	template __dont_instantiate complex<float>  operator+ <float> (float, const complex<float>&);
	template __dont_instantiate complex<float>  operator-<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate complex<float>  operator-<float> (const complex<float>&, float);
	template __dont_instantiate complex<float>  operator-<float> (float, const complex<float>&);
	template __dont_instantiate complex<float>  operator-<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate complex<float>  operator*<float> (const complex<float>&, float);
	template __dont_instantiate complex<float>  operator*<float> (float, const complex<float>&);
	template __dont_instantiate complex<float>  operator*<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate bool  operator==<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate bool  operator==<float> (const complex<float>&, float);
	template __dont_instantiate bool  operator==<float> (float, const complex<float>&);
	template __dont_instantiate complex<float>  operator/<float> (const complex<float>&, const complex<float>&);
	template __dont_instantiate complex<float>  operator/<float> (const complex<float>&, float);
	template __dont_instantiate complex<float>  operator/<float> (float, const complex<float>&);
	template __dont_instantiate complex<float> sin<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> sinh<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> cos<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> cosh<float> (const complex<float>& cx);
//removed inv template 6/16/97  matt fassiotto
	template __dont_instantiate complex<float> exp<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> tan<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> tanh<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> sqrt<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> conj<float> (const complex<float>& cx);
	template __dont_instantiate float abs<float> (const complex<float>& cx);
	template __dont_instantiate float arg<float> (const complex<float>& cx);
	template __dont_instantiate float norm<float> (const complex<float>& cx);
	template __dont_instantiate float imag<float> (const complex<float>& cx);
	template __dont_instantiate float real<float> (const complex<float>& cx);
	template __dont_instantiate complex<float> polar<float> (float& ,float&);
	template __dont_instantiate complex<float> pow<float> (const complex<float>&,const complex<float>&);
	template __dont_instantiate complex<float> pow<float> (const complex<float>&,float);
	template __dont_instantiate complex<float> pow<float> (float,const complex<float>&);
	template __dont_instantiate complex<float> pow<float> (const complex<float>&,int);
	*/
	//template __dont_instantiate bool  operator!=<double> (const complex<double>&, const complex<double>&);
	//template __dont_instantiate bool  operator!=<long double> (const complex<long double>&, const complex<long double>&);
	//template __dont_instantiate complex<double> sin<double> (const complex<double>& cx);
	//template __dont_instantiate complex<double> sinh<double> (const complex<double>& cx);
	//template __dont_instantiate complex<long double> sin<long double> (const complex<long double>& cx);
	//template __dont_instantiate complex<long double> sinh<long double> (const complex<long double>& cx);

#endif

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
//970320 bkoz	line 385 changed abs to use hypot function
//970320 bkoz	line 959 sqrt fixed
//970320 bkoz	line 25 need hypot decls
//970320 bkoz	line 1169 remove ends
//970402 bkoz	use more accurate MSIPL_USE_EXTERNAL_MATHLIB
//970423 bkoz	line 1131 bkoz rewrote operator /
//970424 mm		line 834 template norm rewritten
//971107 Be   Correction to mutex name
*/
