/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_VALARRAY_H
#define MSIPL_VALARRAY_H

#include <mcompile.h>

#include MOD_INCLUDE(algobase)
#include MOD_INCLUDE(algorithm)
#include MOD_INCLUDE(extfunc)
#include MOD_INCLUDE(numeric)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Section 26.2 -- Numeric Arrays

class slice;
template <class T> class slice_array;    // a BLAS-like slice out of
                                         // an array
template <class T> class mask_array;     // a masked array
template <class T> class gslice_array;   // a generalized slice out of
                                         // an array
template <class T> class indirect_array; // an indirect array
template <class T> class valarray;       // an array of type T
class gslice;

//
// class slice
//
class slice {
public :
//
// Constructors
//

    slice () : _len (0), _step (0), _offset (0) {}

    slice (size_t offset, size_t len, size_t step)
    : _len (len), _step (step), _offset (offset) {}

    slice (const slice& s)
    : _len (s._len), _step (s._step), _offset (s._offset) {}

    size_t start () const { return _offset; }
    size_t length () const { return _len; }
    size_t stride () const { return _step; }

private :

//
// private data members
//
    size_t _len;
    size_t _step;
    size_t _offset;
};

//
// class slice_array
//
template <class T> class slice_array {
public :

    typedef T  value_type;

    void operator= (const valarray<T>&) const;
    void operator*= (const valarray<T>&) const;
    void operator/= (const valarray<T>&) const;
    void operator%= (const valarray<T>&) const;
    void operator+= (const valarray<T>&) const;
    void operator-= (const valarray<T>&) const;
    void operator^= (const valarray<T>&) const;
    void operator&= (const valarray<T>&) const;
    void operator|= (const valarray<T>&) const;
    void operator<<= (const valarray<T>&) const;
    void operator>>= (const valarray<T>&) const;

    void fill (const T&);

private:

//
// Constructors
//  
//
//  slice_array ();                              // need not be defined
    slice_array (const slice_array&);
    slice_array (const valarray<T>&, slice);

//
// Assignment operator
//
//  slice_array& operator= (const slice_array&); // need not be defined

//
// private data members
//
    size_t     _len;
    T**        _ptr_ptr;

//
// friend declarations
//

    friend class valarray<T>;

public:

    ~slice_array () { if (_len) delete[] _ptr_ptr; }


};

//
//class mask_array
//
template <class T> class mask_array {
public :

    typedef T  value_type;

    void operator= (const valarray<T>&) const;
    void operator*= (const valarray<T>&) const;
    void operator/= (const valarray<T>&) const;
    void operator%= (const valarray<T>&) const;
    void operator+= (const valarray<T>&) const;
    void operator-= (const valarray<T>&) const;
    void operator^= (const valarray<T>&) const;
    void operator&= (const valarray<T>&) const;
    void operator|= (const valarray<T>&) const;
    void operator<<= (const valarray<T>&) const;
    void operator>>= (const valarray<T>&) const;

    void fill (const T&);

private:

//
// Constructors
//
//  mask_array ();
    mask_array (const mask_array&);
    mask_array (const valarray<T>&, const valarray<bool>&);

//
// Assignment operator
//
//  mask_array& operator= (const mask_array&);

//
// private data members
//
    size_t   _len;
    T**      _ptr_ptr;

//
// friend declarations
//

    friend class valarray<T>;

public:

    ~mask_array () { if (_len) delete[] _ptr_ptr; }
 
};

//
//class indirect_array
//
template <class T> class indirect_array {
public :

    typedef T  value_type;

    void operator= (const valarray<T>&) const;
    void operator*= (const valarray<T>&) const;
    void operator/= (const valarray<T>&) const;
    void operator%= (const valarray<T>&) const;
    void operator+= (const valarray<T>&) const;
    void operator-= (const valarray<T>&) const;
    void operator^= (const valarray<T>&) const;
    void operator&= (const valarray<T>&) const;
    void operator|= (const valarray<T>&) const;
    void operator<<= (const valarray<T>&) const;
    void operator>>= (const valarray<T>&) const;

    void fill (const T&);

private:

//
// Constructors
//
//  indirect_array ();
    indirect_array (const indirect_array&);
    indirect_array (const valarray<T>&, const valarray<size_t>&);

//
// Assignment operator
//
//  indirect_array& operator= (const indirect_array&);

//
// private data members
//
    size_t   _len;
    T**      _ptr_ptr;

//
// friend declarations
//

    friend class valarray<T>;

public:

    ~indirect_array () { if (_len) delete[] _ptr_ptr; }
};

//
// class gslice_array
//
template <class T> class gslice_array {
public :

    typedef T  value_type;

    void operator= (const valarray<T>&) const;
    void operator*= (const valarray<T>&) const;
    void operator/= (const valarray<T>&) const;
    void operator%= (const valarray<T>&) const;
    void operator+= (const valarray<T>&) const;
    void operator-= (const valarray<T>&) const;
    void operator^= (const valarray<T>&) const;
    void operator&= (const valarray<T>&) const;
    void operator|= (const valarray<T>&) const;
    void operator<<= (const valarray<T>&) const;
    void operator>>= (const valarray<T>&) const;

    void fill (const T&);

private:

//
// Constructors
//
//  gslice_array ();
    gslice_array (const gslice_array&);
    gslice_array (const valarray<T>&, const gslice&);

//
// Assignment operator
//
//  gslice_array& operator= (const gslice_array&);

//
// private data members
//
    size_t   _len;
    T**      _ptr_ptr;

//
// nested class 
//

   class store_pointer {
      size_t*  _ptr;
      store_pointer (size_t* ptr) : _ptr (ptr) {}
      ~store_pointer () { if (_ptr) delete[] _ptr; }
      friend class gslice_array<T>;
   };

   
//
// friend declarations
//

    friend class valarray<T>;

public:

    ~gslice_array () { if (_len) delete[] _ptr_ptr; }
 
};

//
// class valarray
//
template <class T> class valarray {
public:
    typedef T  value_type;
//
// Constructors & Destructor
//
    valarray () : _len (0), _ptr (0) {}

    explicit
    valarray (size_t n) 
    : _len (n), _ptr (_len ? new T[_len] : 0) {
        fill_n (_ptr, _len, T());
    }

    valarray (const T& t, size_t n)
    : _len (n), _ptr (_len ? new T[_len] : 0) 
    { 
        fill_n (_ptr, _len, t);
    }

    valarray (const T* t, size_t n)
    : _len (n), _ptr (_len ? new T[_len] : 0) 
    {
#ifdef MSIPL_USING_NAMESPACE
        std::copy (t, t+n, _ptr);
#else
        ::copy (t, t+n, _ptr);
#endif
    }

    valarray (const valarray& v)
    : _len (v.length ()), _ptr (_len ? new T[_len] : 0) 
    {
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    }

    valarray (const mask_array<T>& m)
    : _len (m._len), _ptr (_len ? new T[_len] : 0) 
    {
        __msipl_copy_iter (m._ptr_ptr, m._ptr_ptr+_len, _ptr);
    }

    valarray (const slice_array<T>& s)
    : _len (s._len), _ptr (_len ? new T[_len] : 0) 
    {
        __msipl_copy_iter (s._ptr_ptr, s._ptr_ptr+_len, _ptr);
    }

    valarray (const gslice_array<T>& g)
    : _len (g._len), _ptr (_len ? new T[_len] : 0)
    {
        __msipl_copy_iter (g._ptr_ptr, g._ptr_ptr+_len, _ptr);
    }

    valarray (const indirect_array<T>& i)
    : _len (i._len), _ptr (_len ? new T[_len] : 0)
    {
        __msipl_copy_iter (i._ptr_ptr, i._ptr_ptr+_len, _ptr);
    }

    ~valarray () {  delete_alloc (); REMOVE(va_mutex); }

//
// Conversion operators
//

    operator T* () { READ_LOCK(va_mutex); return _ptr; }

    operator const T* () const { READ_LOCK(va_mutex); return _ptr; }

//
// Length of the array
//

    size_t length () const { READ_LOCK(va_mutex); return _len; }

//
// operator []
//

    T    operator[] (size_t pos) const 
      { READ_LOCK(va_mutex); return *(_ptr+pos); }

    T&   operator[] (size_t pos) 
      { READ_LOCK(va_mutex); return *(_ptr+pos); }

    valarray   operator[] (slice  s) const
    {
        READ_LOCK(va_mutex);
        slice_array<T>      sarray (*this, s);
        return valarray<T> (sarray);
    }

    valarray   operator[] (const gslice& g) const
    {
        READ_LOCK(va_mutex);
        gslice_array<T>     garray (*this,g);
        return valarray<T> (garray);
    }

    valarray   operator[] (const valarray<bool>& vb) const
    {
        READ_LOCK(va_mutex);
        mask_array<T>       marray (*this, vb);
        return valarray<T> (marray);
    }

    valarray   operator[] (const valarray<size_t>&  vi) const
    {
        READ_LOCK(va_mutex);
        indirect_array<T>   iarray (*this, vi);
        return valarray<T> (iarray);
    }

    slice_array<T>     operator[] (slice  s)
    {
        READ_LOCK(va_mutex);
        return slice_array<T> (*this, s);
    }

    gslice_array<T>    operator[] (const gslice& g)
    {
        READ_LOCK(va_mutex);
        return gslice_array<T> (*this, g);
    }

    mask_array<T>      operator[] (const valarray<bool>&  vb)
    {
        READ_LOCK(va_mutex);
        return mask_array<T> (*this, vb);
    }

    indirect_array<T>  operator[] (const valarray<size_t>&  vi)
    {
        READ_LOCK(va_mutex);
        return indirect_array<T> (*this, vi);
    } 

//
// Assignment operator
//

    valarray& operator= (const valarray&);
    valarray& operator= (const T&);
    valarray& operator= (const mask_array<T>&);
    valarray& operator= (const slice_array<T>&);
    valarray& operator= (const gslice_array<T>&);
    valarray& operator= (const indirect_array<T>&);

//
// Unary operators +, -, ~, !
//

    valarray operator+ () const { READ_LOCK(va_mutex); return *this; }

	#if !__MWERKS__
	//961120 bkoz orig src
    valarray operator- () const 
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, negate<T> ());
#else
       return val_array (*this, negate<T> ());
#endif
    }

    valarray operator~ () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, __msipl_complement<T> ());
#else
       return val_array (*this, __msipl_complement<T> ());
#endif
    }

    valarray operator! () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, __msipl_not<T> ());
#else
       return val_array (*this, __msipl_not<T> ());
#endif
    }
	#else
		valarray operator- () const;
		valarray operator~ () const;
		valarray operator! () const;
	#endif
		
//
// Operators *=, /=, +=, -=, %=, ^=, &=, |=, <<=, >>=
//

    valarray& operator*= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, multiplies<T> ());
        return *this;
    }

    valarray& operator/= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, divides<T> ());
        return *this;
    }

    valarray& operator%= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, modulus<T> ());
        return *this;
    }

    valarray& operator+= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, plus<T> ());
        return *this;
    }

    valarray& operator-= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, minus<T> ());
        return *this;
    }

    valarray& operator^= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, __msipl_caret<T> ());
        return *this;
    }

    valarray& operator&= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, __msipl_bitwise_and<T> ());
        return *this;
    }

    valarray& operator|= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, __msipl_bitwise_or<T> ());
        return *this;
    }

    valarray& operator<<= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, __msipl_shift_left<T> ());
        return *this;
    }

    valarray& operator>>= (const T& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, __msipl_shift_right<T> ());
        return *this;
    }

    valarray& operator*= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (),
                              _ptr, multiplies<T> ());
        return *this;
    }

    valarray& operator/= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (),
                              _ptr, divides<T> ());
        return *this;
    }

    valarray& operator%= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (),
                              _ptr, modulus<T> ());
        return *this;
    }

    valarray& operator+= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (),
                              _ptr, plus<T> ());
        return *this;
    }

    valarray& operator-= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, minus<T> ());
        return *this;
    }

    valarray& operator^= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen =  std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, __msipl_caret<T> ());
        return *this;
    }

    valarray& operator&= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, __msipl_bitwise_and<T> ());
        return *this;
    }

    valarray& operator|= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, __msipl_bitwise_or<T> ());
        return *this;
    }

    valarray& operator<<= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, __msipl_shift_left<T> ());
        return *this;
    }

    valarray& operator>>= (const valarray& v)
    {
        WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        size_t rlen = std::min (length (), v.length ());
#else
        size_t rlen = ::min (length (), v.length ());
#endif
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const T* (), 
                              _ptr, __msipl_shift_right<T> ());
        return *this;
    }

//
// Other member functions
//
    //
    // provided for gslice_array
    // code may be shifted from here.
    //    
    T mult (size_t) const;
    T min () const;
    T max () const;

    valarray shift (int) const;
    valarray cshift (int) const;
    valarray apply (T func (T)) const;
    valarray apply (T func (const T&)) const;

    T sum () const 
    {
       T  total;
       READ_LOCK(va_mutex);
       if (length ()) total = *_ptr;
#ifdef MSIPL_USING_NAMESPACE
       return std::accumulate (_ptr+1, _ptr+length (), total);
#else
       return ::accumulate (_ptr+1, _ptr+length (), total);
#endif
    }

    void  fill (const T& t) 
      { WRITE_LOCK(va_mutex); ::fill_n (_ptr, length (), t); }

    void  free () { WRITE_LOCK(va_mutex); delete_alloc (); }

    void  resize (size_t sz, const T& c = T ());

private :

//
// private data members
//
    size_t   _len;
    T*       _ptr;

    DEC_OBJ_LOCK(va_mutex)

public:

#ifdef MSIPL_MEMBER_TEMPLATE

   template <class X, class Function>
   valarray (const valarray<X>& v, Function func)
   : _len (v.length ()), _ptr (_len ? new T[_len] : 0)
   {
    __msipl_copy_value (v.operator const X* (),
                          v.operator const X* ()+_len, _ptr, func);
   }

   template <class X, class Function>
   valarray (const valarray<X>& v1, const valarray<X>& v2, Function func)
   : _len (::min (v1.length (), v2.length ())), _ptr (_len ? new T[_len] : 0)
   {
    __msipl_copy_array (v1.operator const X* (),
                          v1.operator const X* ()+_len,
                          v2.operator const X* (), _ptr, func);
   }

   template <class X, class Function>
   valarray (const valarray<X>& v, const X& t, Function func)
   : _len (v.length ()), _ptr (_len ? new T[_len] : 0)
   {
    __msipl_copy_value (v.operator const X* (),
                          v.operator const X* ()+_len, t, _ptr, func);
   }

   template <class X, class Function>
   valarray (const X& t, const valarray<X>& v, Function func)
   : _len (v.length ()), _ptr (_len ? new T[_len] : 0)
   {
    __msipl_copy_value (t, v.operator const X* (),
                          v.operator const X* ()+_len, _ptr, func);
   }

#endif

   void
   delete_alloc () 
   {
      if (_len) delete[] _ptr;
      _ptr = 0;
      _len = 0;
   }


#ifndef MSIPL_MEMBER_TEMPLATE
public:
#endif

   valarray (size_t len, T* ptr)
   : _len (len), _ptr (ptr) {}

//
// friend declarations for arithmetic & relational operators & global functions
//

   friend valarray operator* (const valarray&, const T&);
   friend valarray operator* (const T&, const valarray&);
   friend valarray operator* (const valarray&, const valarray&);

   friend valarray operator/ (const valarray&, const T&);
   friend valarray operator/ (const T&, const valarray&);
   friend valarray operator/ (const valarray&, const valarray&);

   friend valarray operator% (const valarray&, const T&);
   friend valarray operator% (const T&, const valarray&);
   friend valarray operator% (const valarray&, const valarray&);

   friend valarray operator+ (const valarray&, const T&);
   friend valarray operator+ (const T&, const valarray&);
   friend valarray operator+ (const valarray&, const valarray&);

   friend valarray operator- (const valarray&, const T&);
   friend valarray operator- (const T&, const valarray&);
   friend valarray operator- (const valarray&, const valarray&);

   friend valarray operator^ (const valarray&, const T&);
   friend valarray operator^ (const T&, const valarray&);
   friend valarray operator^ (const valarray&, const valarray&);

   friend valarray operator& (const valarray&, const T&);
   friend valarray operator& (const T&, const valarray&);
   friend valarray operator& (const valarray&, const valarray&);

   friend valarray operator| (const valarray&, const T&);
   friend valarray operator| (const T&, const valarray&);
   friend valarray operator| (const valarray&, const valarray&);

   friend valarray operator<< (const valarray&, const T&);
   friend valarray operator<< (const T&, const valarray&);
   friend valarray operator<< (const valarray&, const valarray&);

   friend valarray operator>> (const valarray&, const T&);
   friend valarray operator>> (const T&, const valarray&);
   friend valarray operator>> (const valarray&, const valarray&);

   friend valarray operator&& (const valarray&, const T&);
   friend valarray operator&& (const T&, const valarray&);
   friend valarray operator&& (const valarray&, const valarray&);

   friend valarray operator|| (const valarray&, const T&);
   friend valarray operator|| (const T&, const valarray&);
   friend valarray operator|| (const valarray&, const valarray&);

   friend valarray<bool> operator== (const valarray&, const T&);
   friend valarray<bool> operator== (const T&, const valarray&);
   friend valarray<bool>
   operator== (const valarray<T>&, const valarray<T>&);

   friend valarray<bool> operator!= (const valarray&, const T&);
   friend valarray<bool> operator!= (const T&, const valarray&);
   friend valarray<bool>
   operator!= (const valarray<T>&, const valarray<T>&);

   friend valarray<bool> operator> (const valarray&, const T&);
   friend valarray<bool> operator> (const T&, const valarray&);
   friend valarray<bool>
   operator> (const valarray<T>&, const valarray<T>&);

   friend valarray<bool> operator< (const valarray&, const T&);
   friend valarray<bool> operator< (const T&, const valarray&);
   friend valarray<bool>
   operator< (const valarray<T>&, const valarray<T>&);

   friend valarray<bool> operator>= (const valarray&, const T&);
   friend valarray<bool> operator>= (const T&, const valarray&);
   friend valarray<bool>
   operator>= (const valarray<T>&, const valarray<T>&);

   friend valarray<bool> operator<= (const valarray&, const T&);
   friend valarray<bool> operator<= (const T&, const valarray&);
   friend valarray<bool>
   operator<= (const valarray<T>&, const valarray<T>&);

   friend valarray abs (const valarray&);
   friend valarray acos (const valarray&);
   friend valarray asin (const valarray&);
   friend valarray atan (const valarray&);
   friend valarray cos (const valarray&);
   friend valarray cosh (const valarray&);
   friend valarray exp (const valarray&);
   friend valarray log (const valarray&);
   friend valarray log10 (const valarray&);
   friend valarray sin (const valarray&);
   friend valarray sinh (const valarray&);
   friend valarray sqrt (const valarray&);
   friend valarray tan (const valarray&);
   friend valarray tanh (const valarray&);

   friend valarray atan2 (const valarray&, const T&);
   friend valarray atan2 (const T&, const valarray&);
   friend valarray atan2 (const valarray&, const valarray&);

   friend valarray pow (const valarray&, const T&);
   friend valarray pow (const T&, const valarray&);
   friend valarray pow (const valarray&, const valarray&);
   friend T        min (const valarray&);
   friend T        max (const valarray&);

};

//
//class gslice
//
class gslice {

public :

//
// Constructors
//

    gslice () : _offset (0) {}

    gslice (size_t offset, const valarray<size_t>& len,
                    const valarray<size_t>& step)
    :_offset (offset), _len (len), _step (step) {}
 
    gslice (const gslice& g)
    :_offset (g._offset), _len (g._len), _step (g._step) {}

    size_t   start () const { return _offset; }

    valarray<size_t>  length () const { return _len; }

    valarray<size_t>  stride () const { return _step; }


private :

//
// private data members
//

    valarray<size_t>  _len; // min value for any element in _len is 1.
                            // otherwise behaviour is undefined.
    valarray<size_t>  _step;
    size_t            _offset;

};



#ifndef MSIPL_MEMBER_TEMPLATE

template <class T, class Function>
inline
valarray<T>
val_array (const valarray<T>& v, Function func)
{
    size_t len  = v.length ();
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_value (v.operator const T* (),
                          v.operator const T* ()+len, ptr, func);
    return valarray<T> (len, ptr);
}

template <class T, class Function>
inline
valarray<T>
val_array (const valarray<T>& v1, const valarray<T>& v2, Function func)
{
#ifdef MSIPL_USING_NAMESPACE
    size_t len  = std::min (v1.length (), v2.length ());
#else
    size_t len  = ::min (v1.length (), v2.length ());
#endif
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_array (v1.operator const T* (),
                          v1.operator const T* ()+len,
                          v2.operator const T* (), ptr, func);
    return valarray<T> (len, ptr);
}

template <class T, class Function>
inline
valarray<T>
val_array (const valarray<T>& v, const T& t, Function func)
{
    size_t len  = v.length ();
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_value (v.operator const T* (),
                          v.operator const T* ()+len,
                          t, ptr, func);
    return valarray<T> (len, ptr);
}

template <class T, class Function>
inline
valarray<T>
val_array (const T& t, const valarray<T>& v, Function func)
{
    size_t len  = v.length ();
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_value (t, v.operator const T* (),
                          v.operator const T* ()+len, ptr, func);
    return valarray<T> (len, ptr);
}

template <class T, class Function>
inline
valarray<bool>
val_array_bool (const valarray<T>& v, Function func)
{
    size_t len  = v.length ();
    bool*  ptr  = len ? new bool[len] : 0;
    __msipl_copy_value (v.operator const T* (),
                          v.operator const T* ()+len,
                          ptr, func);
    return valarray<bool> (len, ptr);
}

template <class T, class Function>
inline
valarray<bool>
val_array_bool (const valarray<T>& v1, const valarray<T>& v2,
                Function func)
{
#ifdef MSIPL_USING_NAMESPACE
    size_t len  = std::min (v1.length (), v2.length ());
#else
    size_t len  = ::min (v1.length (), v2.length ());
#endif
    bool*  ptr  = len ? new bool[len] : 0;
    __msipl_copy_array (v1.operator const T* (),
                          v1.operator const T* ()+len,
                          v2.operator const T* (), ptr, func);
    return valarray<bool> (len, ptr);
}

template <class T, class Function>
inline
valarray<bool>
val_array_bool (const valarray<T>& v, const T& t, Function func)
{
    size_t len  = v.length ();
    bool*  ptr  = len ? new bool[len] : 0;
    __msipl_copy_value (v.operator const T* (),
                          v.operator const T* ()+len,
                          t, ptr, func);
    return valarray<bool> (len, ptr);
}

template <class T, class Function>
inline
valarray<bool>
val_array_bool (const T& t, const valarray<T>& v, Function func)
{
    size_t len  = v.length ();
    bool*  ptr  = len ? new bool[len] : 0;
    __msipl_copy_value (t, v.operator const T* (),
                          v.operator const T* ()+len, ptr, func);
    return valarray<bool> (len, ptr);
}

#endif //ndef msipl_membertemplates

//valarray member definitions
//961120 bkoz
	#if __MWERKS__
	template <class T>
    valarray<T> 
    valarray<T>::operator- () const 
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, negate<T> ());
#else
       return val_array (*this, negate<T> ());
#endif
    }

	template <class T>
    valarray<T> 	
    valarray<T>:: operator~ () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, __msipl_complement<T> ());
#else
       return val_array (*this, __msipl_complement<T> ());
#endif
    }

	template <class T>
    valarray<T> 
    valarray<T>:: operator! () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<T> (*this, __msipl_not<T> ());
#else
       return val_array (*this, __msipl_not<T> ());
#endif
    }
	#endif /*__MWERKS__*/

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const valarray& v)
{
    WRITE_LOCK(va_mutex);
    if (this != &v)
    {
        if (length () != v.length ())
        {
            delete_alloc ();
            _len = v.length ();
            _ptr = _len ? new T[_len] : 0;
        }
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    }
    return *this;
}

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const T& t)
{
    valarray<T> v (t, length ());
    WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    return *this;
}

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const slice_array<T>& s)
{
    size_t  len = s._len;
    WRITE_LOCK(va_mutex);
    T*      ptr = (len ? ((length () != len) ?  new T[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (s._ptr_ptr, s._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const gslice_array<T>& g)
{
    size_t  len = g._len;
    WRITE_LOCK(va_mutex);
    T*      ptr = (len ? ((length () != len) ?  new T[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (g._ptr_ptr, g._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const mask_array<T>& m)
{
    size_t  len = m._len;
    WRITE_LOCK(va_mutex);
    T*      ptr = (len ? ((length () != len) ?  new T[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (m._ptr_ptr, m._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

template <class T>
inline
valarray<T>&
valarray<T>::operator= (const indirect_array<T>& i)
{
    size_t  len = i._len;
    WRITE_LOCK(va_mutex);
    T*      ptr = (len ? ((length () != len) ?  new T[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (i._ptr_ptr, i._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

//
// To be used for gslice_array. valarray<size_t> .
// May be moved later to some other place
//
template <class T>
inline
T
valarray<T>::mult (size_t len) const
{
    T  prod = 1;
    READ_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (len, length ());
#else
    size_t rlen = ::min (len, length ());
#endif
    for (size_t count = 0; count < rlen; ++count)
        prod *= (*(_ptr+count));
    return prod;
}

template <class T>
inline
T
valarray<T>::min () const
{
    T   min_val = T ();
    READ_LOCK(va_mutex);
    if (length ()) min_val = *_ptr;
    for (size_t count = 1; count < length (); ++count)
    {
        if (min_val > (*(_ptr+count)))
            min_val = (*(_ptr+count));
    }
    return min_val;
}

template <class T>
inline
T
valarray<T>::max () const
{
    T   max_val = T ();
    READ_LOCK(va_mutex);
    if (length ()) max_val = *_ptr;
    for (size_t count = 1; count < length (); ++count)
    {
        if (max_val < (*(_ptr+count)))
            max_val = (*(_ptr+count));
    }
    return max_val;
}

template <class T>
inline
valarray<T>
valarray<T>::shift (int i) const
{
    // Take the absolute value of i in j.
    int j = (i > 0) ? i : -i;

    READ_LOCK(va_mutex);
    size_t len  = length ();
    valarray<T> ret (T (), len);

#ifdef MSIPL_USING_NAMESPACE
    if ( i < 0 )
        std::copy (_ptr, _ptr+len-j, ret._ptr+j);
    if ( i >= 0 )
        std::copy (_ptr+j, _ptr+len, ret._ptr);
#else
    if ( i < 0 )
        ::copy (_ptr, _ptr+len-j, ret._ptr+j);
    if ( i >= 0 )
        ::copy (_ptr+j, _ptr+len, ret._ptr);
#endif
    return ret;
}

template <class T>
inline
valarray<T>
valarray<T>::cshift (int i) const
{
    READ_LOCK(va_mutex);
    // Take the absolute value of i in j.
    int j = (i > 0) ? i : -i;

    if (j >= length ()) j = j % length ();

    size_t len  = length ();
    valarray<T> ret (T (), len);

    if ( i < 0 )
    {
#ifdef MSIPL_USING_NAMESPACE
         std::copy (_ptr+len-j, _ptr+len, ret._ptr);
         std::copy (_ptr, _ptr+len-j, ret._ptr+j);
#else
         ::copy (_ptr+len-j, _ptr+len, ret._ptr);
         ::copy (_ptr, _ptr+len-j, ret._ptr+j);
#endif
    }
    else if ( i > 0 )
    {
#ifdef MSIPL_USING_NAMESPACE
         std::copy (_ptr+j, _ptr+len, ret._ptr);
         std::copy (_ptr, _ptr+j, ret._ptr+len-j);
#else
         ::copy (_ptr+j, _ptr+len, ret._ptr);
         ::copy (_ptr, _ptr+j, ret._ptr+len-j);
#endif
    }
    else
    {
#ifdef MSIPL_USING_NAMESPACE
         std::copy (_ptr, _ptr+len, ret._ptr);
#else
         ::copy (_ptr, _ptr+len, ret._ptr);
#endif
    }

    return ret;
}

template <class T>
inline
valarray<T>
valarray<T>::apply (T func (T)) const
{
    READ_LOCK(va_mutex);
    size_t len  = length ();
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_value (_ptr, _ptr+len, ptr, func);
    return valarray<T> (len, ptr);
}

template <class T>
inline
valarray<T>
valarray<T>::apply (T func (const T&)) const
{
    READ_LOCK(va_mutex);
    size_t len  = length ();
    T*     ptr  = len ? new T[len] : 0;
    __msipl_copy_value (_ptr, _ptr+len, ptr, func);
    return valarray<T> (len, ptr);
}

template <class T>
inline
void
valarray<T>::resize (size_t sz, const T& c)  //961113 bkoz
{
    WRITE_LOCK(va_mutex);
    valarray<T>  v1(*this);

    if (sz < _len)
    {
        delete_alloc ();
        _ptr = new T[sz+1];
        _len = sz;
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v1._ptr, v1._ptr+sz, _ptr);
#else
        ::copy (v1._ptr, v1._ptr+sz, _ptr);
#endif
    }
    else if (sz > _len)
    {
        delete_alloc ();
        _ptr = new T[sz+1];
        _len = sz;
        valarray<T>  v2(c, (sz-v1.length ()));

#ifdef MSIPL_USING_NAMESPACE
        std::copy (v1._ptr, v1._ptr+v1._len, _ptr);
        std::copy (v2._ptr, v2._ptr+v2._len, _ptr+v1._len);
#else
        ::copy (v1._ptr, v1._ptr+v1._len, _ptr);
        ::copy (v2._ptr, v2._ptr+v2._len, _ptr+v1._len);
#endif
    }
}

//961214 bkoz
//have to specialize valarray for float, double, long double so that bit ops not performed
#include <valarray_float.h>
#include <valarray_double.h>
#if !__MOTO__
#include <valarray_longdouble.h>
#endif

//valarray unary templates
template <class T>
inline
valarray<T>
operator* (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, multiplies<T> ());
#else
    return val_array (v, t, multiplies<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator* (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, multiplies<T> ());
#else
    return val_array (t, v, multiplies<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator* (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, multiplies<T> ());
#else
    return val_array (v1, v2, multiplies<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator/ (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, divides<T> ());
#else
    return val_array (v, t, divides<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator/ (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, divides<T> ());
#else
    return val_array (t, v, divides<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator/ (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, divides<T> ());
#else
    return val_array (v1, v2, divides<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator% (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, modulus<T> ());
#else
    return val_array (v, t, modulus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator% (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, modulus<T> ());
#else
    return val_array (t, v, modulus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator% (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, modulus<T> ());
#else
    return val_array (v1, v2, modulus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator+ (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, plus<T> ());
#else
    return val_array (v, t, plus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator+ (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, plus<T> ());
#else
    return val_array (t, v, plus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator+ (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, plus<T> ());
#else
    return val_array (v1, v2, plus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator- (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, minus<T> ());
#else
    return val_array (v, t, minus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator- (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, minus<T> ());
#else
    return val_array (t, v, minus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator- (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, minus<T> ());
#else
    return val_array (v1, v2, minus<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator^ (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_caret<T> ());
#else
    return val_array (v, t, __msipl_caret<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator^ (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_caret<T> ());
#else
    return val_array (t, v, __msipl_caret<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator^ (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_caret<T> ());
#else
    return val_array (v1, v2, __msipl_caret<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator& (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_bitwise_and<T> ());
#else
    return val_array (v, t, __msipl_bitwise_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator& (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_bitwise_and<T> ());
#else
    return val_array (t, v, __msipl_bitwise_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator& (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_bitwise_and<T> ());
#else
    return val_array (v1, v2, __msipl_bitwise_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator| (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_bitwise_or<T> ());
#else
    return val_array (v, t, __msipl_bitwise_or<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator| (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_bitwise_or<T> ());
#else
    return val_array (t, v, __msipl_bitwise_or<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator| (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_bitwise_or<T> ());
#else
    return val_array (v1, v2, __msipl_bitwise_or<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator<< (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_shift_left<T> ());
#else
    return val_array (v, t, __msipl_shift_left<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator<< (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_shift_left<T> ());
#else
    return val_array (t, v, __msipl_shift_left<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator<< (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_shift_left<T> ());
#else
    return val_array (v1, v2, __msipl_shift_left<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator>> (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_shift_right<T> ());
#else
    return val_array (v, t, __msipl_shift_right<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator>> (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_shift_right<T> ());
#else
    return val_array (t, v, __msipl_shift_right<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator>> (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_shift_right<T> ());
#else
    return val_array (v1, v2, __msipl_shift_right<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator&& (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_and<T> ());
#else
    return val_array (v, t, __msipl_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator&& (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_and<T> ());
#else
    return val_array (t, v, __msipl_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator&& (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_and<T> ());
#else
    return val_array (v1, v2, __msipl_and<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator|| (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_or<T> ());
#else
    return val_array (v, t, __msipl_or<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator|| (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_or<T> ());
#else
    return val_array (t, v, __msipl_or<T> ());
#endif
}

template <class T>
inline
valarray<T>
operator|| (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_or<T> ());
#else
    return val_array (v1, v2, __msipl_or<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator== (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, equal_to<T> ());
#else
    return val_array_bool (v, t, equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator== (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, equal_to<T> ());
#else
    return val_array_bool (t, v, equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator== (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, equal_to<T> ());
#else
    return val_array_bool (v1, v2, equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator!= (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, not_equal_to<T> ());
#else
    return val_array_bool (v, t, not_equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator!= (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, not_equal_to<T> ());
#else
    return val_array_bool (t, v, not_equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator!= (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, not_equal_to<T> ());
#else
    return val_array_bool (v1, v2, not_equal_to<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator< (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, less<T> ());
#else
    return val_array_bool (v, t, less<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator< (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, less<T> ());
#else
    return val_array_bool (t, v, less<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator< (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, less<T> ());
#else
    return val_array_bool (v1, v2, less<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator> (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, greater<T> ());
#else
    return val_array_bool (v, t, greater<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator> (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, greater<T> ());
#else
    return val_array_bool (t, v, greater<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator> (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, greater<T> ());
#else
    return val_array_bool (v1, v2, greater<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator<= (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, less_equal<T> ());
#else
    return val_array_bool (v, t, less_equal<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator<= (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, less_equal<T> ());
#else
    return val_array_bool (t, v, less_equal<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator<= (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, less_equal<T> ());
#else
    return val_array_bool (v1, v2, less_equal<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator>= (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v, t, greater_equal<T> ());
#else
    return val_array_bool (v, t, greater_equal<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator>= (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (t, v, greater_equal<T> ());
#else
    return val_array_bool (t, v, greater_equal<T> ());
#endif
}

template <class T>
inline
valarray<bool>
operator>= (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<bool> (v1, v2, greater_equal<T> ());
#else
    return val_array_bool (v1, v2, greater_equal<T> ());
#endif
}

template <class T>
inline
valarray<T>
abs (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_absolute<T> ());
#else
    return val_array (v, __msipl_absolute<T> ());
#endif
}

template <class T>
inline
valarray<T>
acos (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_arccos<T> ());
#else
    return val_array (v, __msipl_arccos<T> ());
#endif
}

template <class T>
inline
valarray<T>
asin (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_arcsin<T> ());
#else
    return val_array (v, __msipl_arcsin<T> ());
#endif
}

template <class T>
inline
valarray<T>
atan (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_arctan<T> ());
#else
    return val_array (v, __msipl_arctan<T> ());
#endif
}

template <class T>
inline
valarray<T>
cos (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_cosine<T> ());
#else
    return val_array (v, __msipl_cosine<T> ());
#endif
}

template <class T>
inline
valarray<T>
cosh (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_cosineh<T> ());
#else
    return val_array (v, __msipl_cosineh<T> ());
#endif
}

template <class T>
inline
valarray<T>
exp (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_exponential<T> ());
#else
    return val_array (v, __msipl_exponential<T> ());
#endif
}

template <class T>
inline
valarray<T>
log (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v,__msipl_logarithm<T> ());
#else
    return val_array (v,__msipl_logarithm<T> ());
#endif
}

template <class T>
inline
valarray<T>
log10 (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v,__msipl_logarithm10<T> ());
#else
    return val_array (v,__msipl_logarithm10<T> ());
#endif
}

template <class T>
inline
valarray<T>
sin (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_sine<T> ());
#else
    return val_array (v, __msipl_sine<T> ());
#endif
}

template <class T>
inline
valarray<T>
sinh (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_sineh<T> ());
#else
    return val_array (v, __msipl_sineh<T> ());
#endif
}

template <class T>
inline
valarray<T>
sqrt (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_sqroot<T> ());
#else
    return val_array (v, __msipl_sqroot<T> ());
#endif
}

template <class T>
inline
valarray<T>
tan (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_tangent<T> ());
#else
    return val_array (v, __msipl_tangent<T> ());
#endif
}

template <class T>
inline
valarray<T>
tanh (const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, __msipl_tangenth<T> ());
#else
    return val_array (v, __msipl_tangenth<T> ());
#endif
}

template <class T>
inline
valarray<T>
atan2 (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_arctan2<T> ());
#else
    return val_array (v, t, __msipl_arctan2<T> ());
#endif
}

template <class T>
inline
valarray<T>
atan2 (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_arctan2<T> ());
#else
    return val_array (t, v, __msipl_arctan2<T> ());
#endif
}

template <class T>
inline
valarray<T>
atan2 (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_arctan2<T> ());
#else
    return val_array (v1, v2, __msipl_arctan2<T> ());
#endif
}

template <class T>
inline
valarray<T>
pow (const valarray<T>& v, const T& t)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v, t, __msipl_power<T> ());
#else
    return val_array (v, t, __msipl_power<T> ());
#endif
}

template <class T>
inline
valarray<T>
pow (const T& t, const valarray<T>& v)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (t, v, __msipl_power<T> ());
#else
    return val_array (t, v, __msipl_power<T> ());
#endif
}

template <class T>
inline
valarray<T>
pow (const valarray<T>& v1, const valarray<T>& v2)
{
#ifdef MSIPL_MEMBER_TEMPLATE
    return valarray<T> (v1, v2, __msipl_power<T> ());
#else
    return val_array (v1, v2, __msipl_power<T> ());
#endif
}

template <class T>
inline
T
min (const valarray<T>& v)
{
    T   min_val = T ();
    if (v.length ()) min_val = *v._ptr;
    for (size_t count = 1; count < v.length (); ++count)
    {
        if (min_val > (*(v._ptr+count)))
            min_val = (*(v._ptr+count));
    }
    return min_val;
}

template <class T>
inline
T
max (const valarray<T>& v)
{
    T   max_val = T ();
    if (length ()) max_val = *v._ptr;
    for (size_t count = 1; count < length (); ++count)
    {
        if (max_val < (*(v._ptr+count)))
            max_val = (*(v._ptr+count));
    }
    return max_val;
}

template <class T>
inline
slice_array<T>::slice_array (const slice_array& s)
:_len (s._len), _ptr_ptr (_len ? new T*[_len] : 0)
{
#ifdef MSIPL_USING_NAMESPACE
    std::copy (s._ptr_ptr, s._ptr_ptr+_len, _ptr_ptr);
#else
    ::copy (s._ptr_ptr, s._ptr_ptr+_len, _ptr_ptr);
#endif
}

template <class T>
inline
void
slice_array<T>::operator= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (), 
                             v.operator const T* ()+rlen, _ptr_ptr+rlen);
}

template <class T>
inline
void
slice_array<T>::operator*= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                            v.operator const T* ()+rlen, _ptr_ptr+rlen,
                            _ptr_ptr+rlen, multiplies<T> ());
}

template <class T>
inline
void
slice_array<T>::operator/= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, divides<T> ());
}

template <class T>
inline
void
slice_array<T>::operator%= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                            v.operator const T* ()+rlen, _ptr_ptr+rlen,
                            _ptr_ptr+rlen, modulus<T> ());
}

template <class T>
inline
void
slice_array<T>::operator+= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, plus<T> ());
}

template <class T>
inline
void
slice_array<T>::operator-= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, minus<T> ());
}

template <class T>
inline
void
slice_array<T>::operator^= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_caret<T> ());
}

template <class T>
inline
void
slice_array<T>::operator&= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_bitwise_and<T> ());
}

template <class T>
inline
void
slice_array<T>::operator|= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_bitwise_or<T> ());
}

template <class T>
inline
void
slice_array<T>::operator<<= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_shift_left<T> ());
}

template <class T>
inline
void
slice_array<T>::operator>>= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_shift_right<T> ());
}

template <class T>
inline
void
slice_array<T>::fill (const T& t)
{
    __msipl_fill_iter_n (_ptr_ptr, _len, t);
}

template <class T>
inline
gslice_array<T>::gslice_array (const gslice_array& g)
:_len (g._len), _ptr_ptr (_len ? new T*[_len] : 0)
{
#ifdef MSIPL_USING_NAMESPACE
    std::copy (g._ptr_ptr, g._ptr_ptr+_len, _ptr_ptr);
#else
    ::copy (g._ptr_ptr, g._ptr_ptr+_len, _ptr_ptr);
#endif
}

template <class T>
inline
void
gslice_array<T>::operator= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (), 
                              v.operator const T* ()+rlen, _ptr_ptr+rlen);
}

template <class T>
inline
void
gslice_array<T>::operator*= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                            v.operator const T* ()+rlen, _ptr_ptr+rlen,
                            _ptr_ptr+rlen, multiplies<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator/= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                            v.operator const T* ()+rlen, _ptr_ptr+rlen,
                            _ptr_ptr+rlen, divides<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator%= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                            v.operator const T* ()+rlen, _ptr_ptr+rlen,
                            _ptr_ptr+rlen, modulus<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator+= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, plus<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator-= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = ::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, minus<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator^= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, __msipl_caret<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator&= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_bitwise_and<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator|= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_bitwise_or<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator<<= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_shift_left<T> ());
}

template <class T>
inline
void
gslice_array<T>::operator>>= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_shift_right<T> ());
}

template <class T>
inline
void
gslice_array<T>::fill (const T& t)
{
    __msipl_fill_iter_n (_ptr_ptr, _len, t);
}

template <class T>
inline
mask_array<T>::mask_array (const mask_array& m)
:_len (m._len), _ptr_ptr (_len ? new T*[_len] : 0)
{
#ifdef MSIPL_USING_NAMESPACE
    std::copy (m._ptr_ptr, m._ptr_ptr+_len, _ptr_ptr);
#else
    ::copy (m._ptr_ptr, m._ptr_ptr+_len, _ptr_ptr);
#endif
}

template <class T>
inline
void
mask_array<T>::operator= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (), 
                             v.operator const T* ()+rlen, _ptr_ptr+rlen);
}

template <class T>
inline
void
mask_array<T>::operator*= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, multiplies<T> ());
}

template <class T>
inline
void
mask_array<T>::operator/= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                             v.operator const T* ()+rlen, _ptr_ptr+rlen,
                             _ptr_ptr+rlen, divides<T> ());
}

template <class T>
inline
void
mask_array<T>::operator%= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, modulus<T> ());
}

template <class T>
inline
void
mask_array<T>::operator+= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, plus<T> ());
}

template <class T>
inline
void
mask_array<T>::operator-= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, minus<T> ());
}

template <class T>
inline
void
mask_array<T>::operator^= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_caret<T> ());
}

template <class T>
inline
void
mask_array<T>::operator&= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_bitwise_and<T> ());
}

template <class T>
inline
void
mask_array<T>::operator|= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_bitwise_or<T> ());
}

template <class T>
inline
void
mask_array<T>::operator<<= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, __msipl_shift_left<T> ());
}

template <class T>
inline
void
mask_array<T>::operator>>= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, __msipl_shift_right<T> ());
}

template <class T>
inline
void
mask_array<T>::fill (const T& t)
{
    __msipl_fill_iter_n (_ptr_ptr, _len, t);
}

template <class T>
inline
indirect_array<T>::indirect_array (const indirect_array& i)
:_len (i._len), _ptr_ptr (_len ? new T*[_len] : 0)
{
#ifdef MSIPL_USING_NAMESPACE
    std::copy (i._ptr_ptr, i._ptr_ptr+_len, _ptr_ptr);
#else
    ::copy (i._ptr_ptr, i._ptr_ptr+_len, _ptr_ptr);
#endif
}

template <class T>
inline
void
indirect_array<T>::operator= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (), 
                                  v.operator const T* ()+rlen, _ptr_ptr+rlen);
}

template <class T>
inline
void
indirect_array<T>::operator*= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, multiplies<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator/= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, divides<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator%= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, modulus<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator+= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, plus<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator-= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, minus<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator^= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_caret<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator&= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_bitwise_and<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator|= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                               v.operator const T* ()+rlen, _ptr_ptr+rlen,
                               _ptr_ptr+rlen, __msipl_bitwise_or<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator<<= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_shift_left<T> ());
}

template <class T>
inline
void
indirect_array<T>::operator>>= (const valarray<T>& v) const
{
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (_len, v.length ());
#else
    size_t rlen = ::min (_len, v.length ());
#endif
    __msipl_iter_copy_backward (v.operator const T* (),
                              v.operator const T* ()+rlen, _ptr_ptr+rlen,
                              _ptr_ptr+rlen, __msipl_shift_right<T> ());
}

template <class T>
inline
void
indirect_array<T>::fill (const T& t)
{
    __msipl_fill_iter_n (_ptr_ptr, _len, t);
}

template <class T>
inline
slice_array<T>::slice_array (const valarray<T>& v, slice s)
{
#ifdef MSIPL_USING_NAMESPACE
    _len = std::min (s.length (), ((v.length ()-s.start ())/s.stride ())+1);
#else
    _len = ::min (s.length (), ((v.length ()-s.start ())/s.stride ())+1);
#endif
    _ptr_ptr = _len ? new T*[_len] : 0;
    for (size_t count = 0; count < _len; ++count)
    {
        * (_ptr_ptr+count) = (T*)((v.operator const T* ())+
                                  s.start ()+ (count*s.stride ()));
    }
}

template <class T>
inline
gslice_array<T>::gslice_array (const valarray<T>& v, const gslice& g)
{
    const valarray<size_t>  slen (g.length ());
    const valarray<size_t>  sstp (g.stride ());

#ifdef MSIPL_USING_NAMESPACE
    size_t mlen =  std::min (slen.length (), sstp.length ());
#else
    size_t mlen =  ::min (slen.length (), sstp.length ());
#endif
    _len        =  slen.mult (mlen);

    size_t*   ptr  = _len ? new size_t[_len] : 0;
    store_pointer _sptr (ptr);
    size_t*   muli = mlen ? new size_t[mlen] : 0;
    store_pointer _smuli (muli);
    size_t*   mulc = mlen ? new size_t[mlen] : 0;
    store_pointer _smulc (mulc);

    size_t count;
    for (count = 0; count < mlen; ++count)
    {
        *(muli+count) = 0;
        * (mulc+mlen-count-1) = slen.mult (mlen-count-1);
    }

    for (count = 0; count < _len; ++count)
    {
        * (ptr+count) = g.start ();
        size_t  len; 
        for (len = 0; len < mlen; ++len)
        {
             *(ptr+count) += (*(muli+len))*(sstp[len]);
        }
        for (len = 0; len < mlen; ++len)
        {
             if (! ((count+1) % (* (mulc+len))))
             {
                 ++ (* (muli+len));
                 *(muli+len) %= slen[len];
             }
        }
        
    }

    sort (ptr, ptr+_len);
    size_t*  bptr = lower_bound (ptr, ptr+_len, v.length ());

    _len = 0;

    _len = distance (ptr, bptr);
    _ptr_ptr = _len ? new T*[_len] : 0;
    for (count = 0; count < _len; ++count)
        * (_ptr_ptr+count) = (T*)((v.operator const T* ())+ (* (ptr+count)));
}

template <class T>
inline
mask_array<T>::mask_array (const valarray<T>& v, const valarray<bool>& vb)
{
    _len = 0;
    size_t count;
#ifdef MSIPL_USING_NAMESPACE
    size_t rlen = std::min (vb.length (), v.length ());
#else
    size_t rlen = ::min (vb.length (), v.length ());
#endif

    for (count = 0; count < rlen; ++count)
         if (vb[count]) _len++;

    _ptr_ptr = _len ? new T*[_len] : 0;
    _len     = 0;

    for (count = 0; count < rlen; ++count)
    {
         if (vb[count])
         {
             * (_ptr_ptr+_len) = (T*)((v.operator const T* ())+count);
             _len++;
         }
    }
}

template <class T>
inline
indirect_array<T>::indirect_array (const valarray<T>& v, 
                                   const valarray<size_t>& vi)
{
//
// elements of vi should be less than v.length ()
// otherwise behaviour is undefined.
//
    _len = vi.length ();
    _ptr_ptr = _len ? new T*[_len] : 0;

    for (size_t count = 0; count < _len; ++count)
        *(_ptr_ptr+count) = (T*)((v.operator const T* ())+vi[count]);
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_VALARRAY_H */

//961114 bkoz changed the order in which the arrays are declared/defined to
//		slice, slice_array, indirect_array, mask_array, gslice_array, valarray, gslice
// 		this is important as valarray uses indirect_array constructors. . .
//961114 bkoz line 1361 changed valarray::resize definition, took out default arg (in decl)
//961210 bkoz added alignment wrapper
//961214 bkoz line 1394 included specializations for float, double, long double
//961221 bkoz line 1398 moto changes via mmoss