
/*
 *   complex.h
 *
 *   C++ Complex mathematics.
 *
 *           Copyright (c) 1991-1992, MetaWare Incorporated
 */

#ifndef __COMPLEX_H
#define __COMPLEX_H
#pragma push_align_members(64);

#include <math.h>

#pragma on(nodebug)
class complex {

private:
	double _real;
	double _imaginary;


public:

	complex(double __real_part, double __imag_part=0) {
		_real=__real_part;
		_imaginary=__imag_part;
		}
	complex() {
		_real = _imaginary = 0.0;
		}

	// complex manipulations
	friend double real(complex&);	// Inspect real part
	friend double imag(complex&);	// Inspect imaginary part
	friend complex conj(complex&);	// Complex conjugate
	friend double norm(complex&);	// Magnitude^2
	friend double arg(complex&);	// Angle in the plane

	// Create a complex from polar coordinates
	friend complex polar(double __mag, double __angle=0);

	// ANSI C math functions for complex numbers.
	friend complex pow(complex& __base, double __expon);
	friend complex pow(double __base, complex& __expon);
	friend complex pow(complex& __base, complex& __expon);

	friend complex cos(complex&);
	friend complex cosh(complex&);

	friend complex sin(complex&);
	friend complex sinh(complex&);

	friend complex tan(complex&);
	friend complex tanh(complex&);

	friend complex acos(complex&);
	friend complex asin(complex&);
	friend complex atan(complex&);

	friend double  abs(complex&);
	friend complex exp(complex&);
	friend complex sqrt(complex&);

	friend complex log(complex&);
	friend complex log10(complex&);

	// Binary operators
	friend complex operator*(complex&, complex&);
	friend complex operator*(complex&, double);
	friend complex operator*(double, complex&);

	friend complex operator/(complex&, complex&);
	friend complex operator/(complex&, double);
	friend complex operator/(double, complex&);

	friend complex operator+(complex&, complex&);
	friend complex operator+(double, complex&);
	friend complex operator+(complex&, double);

	friend complex operator-(complex&, complex&);
	friend complex operator-(double, complex&);
	friend complex operator-(complex&, double);

	friend int operator==(complex&, complex&);
	friend int operator!=(complex&, complex&);

	// Compound assignment
	complex& operator*=(complex& __z);
	complex& operator*=(double __d) {
		_real *= __d;
		_imaginary *= __d;
		return *this;
		}

	complex& operator/=(complex& __z);
	complex& operator/=(double __d) {
		_real /= __d;
		_imaginary /= __d;
		return *this;
		}

	complex& operator+=(complex& __z) {
		_real += __z._real;
		_imaginary += __z._imaginary;
		return *this;
		}
	complex& operator+=(double __d) {
		_real+= __d;
		return *this;
		}

	complex& operator-=(complex& __z) {
		_real -= __z._real;
		_imaginary -= __z._imaginary;
		return *this;
		}
	complex& operator-=(double __d) {
		_real -= __d;
		return *this;
		}

	// Unary operators
	complex operator+() { return *this; }
	complex operator-() { return (complex(-_real,-_imaginary)); }
	};
#pragma pop(nodebug)


inline double real(complex& __z) {
	return __z._real;
	}

inline double imag(complex& __z) {
	return __z._imaginary;
	}

inline complex conj(complex& __z) {
	return complex(__z._real, -__z._imaginary);
	}

inline complex polar(double __mag, double __angle) {
	return complex(__mag*cos(__angle), __mag*sin(__angle));
	}

inline double abs(complex& __z) {
        return sqrt((__z._real * __z._real)+(__z._imaginary * __z._imaginary));
	}


inline complex operator*(complex& __z, double __d) {
	return complex(__z._real * __d, __z._imaginary * __d);
	}

inline complex operator*(double __d, complex& __z) {
	return complex(__z._real * __d, __z._imaginary * __d);
	}

inline complex operator/(complex& __z, double __d) {
	return complex(__z._real / __d, __z._imaginary / __d);
	}

inline complex operator+(complex& __za, complex& __zb) {
	return complex(__za._real+__zb._real, __za._imaginary+__zb._imaginary);
	}

inline complex operator+(double __d, complex& __z) {
	return complex(__d + __z._real, __z._imaginary);
	}

inline complex operator+(complex& __z, double __d) {
	return complex(__z._real + __d, __z._imaginary);
	}

inline complex operator-(complex& __za, complex& __zb) {
	return complex(__za._real-__zb._real, __za._imaginary-__zb._imaginary);
	}

inline complex operator-(double __d, complex& __z) {
	return complex(__d - __z._real, -__z._imaginary);
	}

inline complex operator-(complex& __z, double __d) {
	return complex(__z._real - __d, __z._imaginary);
	}

inline int operator==(complex& __za, complex& __zb) {
	return	(  (__za._real == __zb._real)
		&& (__za._imaginary == __zb._imaginary)
		);
	}

inline int operator!=(complex& __za, complex& __zb) {
	return	(  (__za._real != __zb._real)
		|| (__za._imaginary != __zb._imaginary)
		);
	}

#c_include <iostream.h>

ostream& operator<<(ostream& __os, complex& __z);
istream& operator>>(istream& __is, complex& __z);


#pragma pop_align_members();
#endif  // __COMPLEX_H

/**          Copyright (c) 1991-1992, MetaWare Incorporated             **/
