//961214 bkoz
/*NB
valarray contains some member functions that cannot be instantiated for non-integer types.
Due to the lack of template member function specialization and template function specialization,
complete specializations of valarray for all floating-point types were provided.
(ie valarray<float>, valarray<double>, valarray<long double>

All problematic member functions have been deleted, as I could not determine a "general" way to
specialize these templates (ie, what will most people assume happens when operator-() is
applied to a fp type?). It is hoped that the absence (and subsequent compile errors) will 
prevent the pain of trying to debug the runtime results of someone else's assumptions. 
Suggestions other than return *this are welcome.

In the meantime, this is the list of deleted members:

// Conversion operators
    operator T* () { READ_LOCK(va_mutex); return _ptr; }  //not?

// Assignment operator
    valarray<double>& operator= (const valarray<double>&); //want more than double? bkoz

// Unary operators  -, ~

// Operators %=, ^=, &=, |=, <<=, >>=

// friend declarations for arithmetic & relational operators & global functions
   friend valarray operator% (const valarray&, const T&);
   friend valarray operator% (const T&, const valarray&);
   friend valarray operator% (const valarray&, const valarray&);

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

*/

//
// class valarray<long double>
//
class valarray<long double> {
public:
    typedef long double  value_type;
//
// Constructors & Destructor
//
    valarray () : _len (0), _ptr (0) {}

    explicit
    valarray (size_t n) 
    : _len (n), _ptr (_len ? new long double[_len] : 0) {
        fill_n (_ptr, _len, long double());
    }

    valarray (const long double& t, size_t n)
    : _len (n), _ptr (_len ? new long double[_len] : 0) 
    { 
        fill_n (_ptr, _len, t);
    }

    valarray (const long double* t, size_t n)
    : _len (n), _ptr (_len ? new long double[_len] : 0) 
    {
#ifdef MSIPL_USING_NAMESPACE
        std::copy (t, t+n, _ptr);
#else
        ::copy (t, t+n, _ptr);
#endif
    }

    valarray (const valarray& v)
    : _len (v.length ()), _ptr (_len ? new long double[_len] : 0) 
    {
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    }

    valarray (const mask_array<long double>& m)
    : _len (m._len), _ptr (_len ? new long double[_len] : 0) 
    {
        __msipl_copy_iter (m._ptr_ptr, m._ptr_ptr+_len, _ptr);
    }

    valarray (const slice_array<long double>& s)
    : _len (s._len), _ptr (_len ? new long double[_len] : 0) 
    {
        __msipl_copy_iter (s._ptr_ptr, s._ptr_ptr+_len, _ptr);
    }

    valarray (const gslice_array<long double>& g)
    : _len (g._len), _ptr (_len ? new long double[_len] : 0)
    {
        __msipl_copy_iter (g._ptr_ptr, g._ptr_ptr+_len, _ptr);
    }

    valarray (const indirect_array<long double>& i)
    : _len (i._len), _ptr (_len ? new long double[_len] : 0)
    {
        __msipl_copy_iter (i._ptr_ptr, i._ptr_ptr+_len, _ptr);
    }

    ~valarray () {  delete_alloc (); REMOVE(va_mutex); }

//
// Conversion operators
//

    //operator long double* () { READ_LOCK(va_mutex); return _ptr; }  //not?

    operator const long double* () const { READ_LOCK(va_mutex); return _ptr; }

//
// Length of the array
//

    size_t length () const { READ_LOCK(va_mutex); return _len; }

//
// operator []
//

    long double    operator[] (size_t pos) const 
      { READ_LOCK(va_mutex); return *(_ptr+pos); }

    long double&   operator[] (size_t pos) 
      { READ_LOCK(va_mutex); return *(_ptr+pos); }

    valarray   operator[] (slice  s) const
    {
        READ_LOCK(va_mutex);
        slice_array<long double>      sarray (*this, s);
        return valarray<long double> (sarray);
    }

    valarray   operator[] (const gslice& g) const
    {
        READ_LOCK(va_mutex);
        gslice_array<long double>     garray (*this,g);
        return valarray<long double> (garray);
    }

    valarray   operator[] (const valarray<bool>& vb) const
    {
        READ_LOCK(va_mutex);
        mask_array<long double>       marray (*this, vb);
        return valarray<long double> (marray);
    }

    valarray   operator[] (const valarray<size_t>&  vi) const
    {
        READ_LOCK(va_mutex);
        indirect_array<long double>   iarray (*this, vi);
        return valarray<long double> (iarray);
    }

    slice_array<long double>     operator[] (slice  s)
    {
        READ_LOCK(va_mutex);
        return slice_array<long double> (*this, s);
    }

    gslice_array<long double>    operator[] (const gslice& g)
    {
        READ_LOCK(va_mutex);
        return gslice_array<long double> (*this, g);
    }

    mask_array<long double>      operator[] (const valarray<bool>&  vb)
    {
        READ_LOCK(va_mutex);
        return mask_array<long double> (*this, vb);
    }

    indirect_array<long double>  operator[] (const valarray<size_t>&  vi)
    {
        READ_LOCK(va_mutex);
        return indirect_array<long double> (*this, vi);
    } 

//
// Assignment operator
//

    valarray<long double>& operator= (const valarray<long double>&); //want more than long double? bkoz
    valarray<long double>& operator= (const long double&);
    valarray<long double>& operator= (const mask_array<long double>&);
    valarray<long double>& operator= (const slice_array<long double>&);
    valarray<long double>& operator= (const gslice_array<long double>&);
    valarray<long double>& operator= (const indirect_array<long double>&);

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
       return valarray<long double> (*this, negate<long double> ());
#else
       return val_array (*this, negate<long double> ());
#endif
    }

    valarray operator! () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<long double> (*this, __msipl_not<long double> ());
#else
       return val_array (*this, __msipl_not<long double> ());
#endif
    }
	#else
		valarray operator! () const;
	#endif
		
//
// Operators *=, /=, +=, -=, %=, ^=, &=, |=, <<=, >>=
//

    valarray& operator*= (const long double& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t,
                              _ptr, multiplies<long double> ());
        return *this;
    }

    valarray& operator/= (const long double& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, divides<long double> ());
        return *this;
    }

    valarray& operator+= (const long double& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, plus<long double> ());
        return *this;
    }

    valarray& operator-= (const long double& t)
    {
        WRITE_LOCK(va_mutex);
        __msipl_copy_value (_ptr, _ptr+length (), t, _ptr, minus<long double> ());
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
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const long double* (),
                              _ptr, multiplies<long double> ());
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
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const long double* (),
                              _ptr, divides<long double> ());
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
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const long double* (),
                              _ptr, plus<long double> ());
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
        __msipl_copy_array (_ptr, _ptr+rlen, v.operator const long double* (), 
                              _ptr, minus<long double> ());
        return *this;
    }


//
// Other member functions
//
    //
    // provided for gslice_array
    // code may be shifted from here.
    //    
    long double mult (size_t) const;
    long double min () const;
    long double max () const;

    valarray shift (int) const;
    valarray cshift (int) const;
    valarray apply (long double func (long double)) const;
    valarray apply (long double func (const long double&)) const;

    long double sum () const 
    {
       long double  total;
       READ_LOCK(va_mutex);
       if (length ()) total = *_ptr;
#ifdef MSIPL_USING_NAMESPACE
       return std::accumulate (_ptr+1, _ptr+length (), total);
#else
       return ::accumulate (_ptr+1, _ptr+length (), total);
#endif
    }

    void  fill (const long double& t) 
      { WRITE_LOCK(va_mutex); ::fill_n (_ptr, length (), t); }

    void  free () { WRITE_LOCK(va_mutex); delete_alloc (); }

    void  resize (size_t sz, const long double& c = long double ());

private :

//
// private data members
//
    size_t   _len;
    long double*       _ptr;

    DEC_OBJ_LOCK(va_mutex)

public:

#ifdef MSIPL_MEMBER_TEMPLATE

   template <class X, class Function>
   valarray (const valarray<X>& v, Function func)
   : _len (v.length ()), _ptr (_len ? new long double[_len] : 0)
   {
    __msipl_copy_value (v.operator const X* (),
                          v.operator const X* ()+_len, _ptr, func);
   }

   template <class X, class Function>
   valarray (const valarray<X>& v1, const valarray<X>& v2, Function func)
   : _len (::min (v1.length (), v2.length ())), _ptr (_len ? new long double[_len] : 0)
   {
    __msipl_copy_array (v1.operator const X* (),
                          v1.operator const X* ()+_len,
                          v2.operator const X* (), _ptr, func);
   }

   template <class X, class Function>
   valarray (const valarray<X>& v, const X& t, Function func)
   : _len (v.length ()), _ptr (_len ? new long double[_len] : 0)
   {
    __msipl_copy_value (v.operator const X* (),
                          v.operator const X* ()+_len, t, _ptr, func);
   }

   template <class X, class Function>
   valarray (const X& t, const valarray<X>& v, Function func)
   : _len (v.length ()), _ptr (_len ? new long double[_len] : 0)
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

   valarray (size_t len, long double* ptr)
   : _len (len), _ptr (ptr) {}

//
// friend declarations for arithmetic & relational operators & global functions
//
   friend valarray operator* (const valarray&, const long double&);
   friend valarray operator* (const long double&, const valarray&);
   friend valarray operator* (const valarray&, const valarray&);

   friend valarray operator/ (const valarray&, const long double&);
   friend valarray operator/ (const long double&, const valarray&);
   friend valarray operator/ (const valarray&, const valarray&);

   friend valarray operator+ (const valarray&, const long double&);
   friend valarray operator+ (const long double&, const valarray&);
   friend valarray operator+ (const valarray&, const valarray&);

   friend valarray operator- (const valarray&, const long double&);
   friend valarray operator- (const long double&, const valarray&);
   friend valarray operator- (const valarray&, const valarray&);


   friend valarray operator&& (const valarray&, const long double&);
   friend valarray operator&& (const long double&, const valarray&);
   friend valarray operator&& (const valarray&, const valarray&);

   friend valarray operator|| (const valarray&, const long double&);
   friend valarray operator|| (const long double&, const valarray&);
   friend valarray operator|| (const valarray&, const valarray&);

   friend valarray<bool> operator== (const valarray&, const long double&);
   friend valarray<bool> operator== (const long double&, const valarray&);
   friend valarray<bool>
   operator== (const valarray<long double>&, const valarray<long double>&);

   friend valarray<bool> operator!= (const valarray&, const long double&);
   friend valarray<bool> operator!= (const long double&, const valarray&);
   friend valarray<bool>
   operator!= (const valarray<long double>&, const valarray<long double>&);

   friend valarray<bool> operator> (const valarray&, const long double&);
   friend valarray<bool> operator> (const long double&, const valarray&);
   friend valarray<bool>
   operator> (const valarray<long double>&, const valarray<long double>&);

   friend valarray<bool> operator< (const valarray&, const long double&);
   friend valarray<bool> operator< (const long double&, const valarray&);
   friend valarray<bool>
   operator< (const valarray<long double>&, const valarray<long double>&);

   friend valarray<bool> operator>= (const valarray&, const long double&);
   friend valarray<bool> operator>= (const long double&, const valarray&);
   friend valarray<bool>
   operator>= (const valarray<long double>&, const valarray<long double>&);

   friend valarray<bool> operator<= (const valarray&, const long double&);
   friend valarray<bool> operator<= (const long double&, const valarray&);
   friend valarray<bool>
   operator<= (const valarray<long double>&, const valarray<long double>&);

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

   friend valarray atan2 (const valarray&, const long double&);
   friend valarray atan2 (const long double&, const valarray&);
   friend valarray atan2 (const valarray&, const valarray&);

   friend valarray pow (const valarray&, const long double&);
   friend valarray pow (const long double&, const valarray&);
   friend valarray pow (const valarray&, const valarray&);
   friend long double        min (const valarray&);
   friend long double        max (const valarray&);
};

//961120 bkoz
	#if __MWERKS__

    valarray<long double> 
    valarray<long double>:: operator! () const
    {
       READ_LOCK(va_mutex);
#ifdef MSIPL_MEMBER_TEMPLATE
       return valarray<long double> (*this, __msipl_not<long double> ());
#else
       return val_array (*this, __msipl_not<long double> ());
#endif
    }
	#endif /*__MWERKS__*/

inline
valarray<long double>&
valarray<long double>::operator= (const valarray<long double>& v)  //bkoz specialize for more than just long double?
{
    WRITE_LOCK(va_mutex);
    if (this != &v)
    {
        if (length () != v.length ())
        {
            delete_alloc ();
            _len = v.length ();
            _ptr = _len ? new long double[_len] : 0;
        }
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    }
    return *this;
}

inline
valarray<long double>&
valarray<long double>::operator= (const long double& t)
{
    valarray<long double> v (t, length ());
    WRITE_LOCK(va_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::copy (v._ptr, v._ptr+_len, _ptr);
#else
        ::copy (v._ptr, v._ptr+_len, _ptr);
#endif
    return *this;
}

inline
valarray<long double>&
valarray<long double>::operator= (const slice_array<long double>& s)
{
    size_t  len = s._len;
    WRITE_LOCK(va_mutex);
    long double*      ptr = (len ? ((length () != len) ?  new long double[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (s._ptr_ptr, s._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

inline
valarray<long double>&
valarray<long double>::operator= (const gslice_array<long double>& g)
{
    size_t  len = g._len;
    WRITE_LOCK(va_mutex);
    long double*      ptr = (len ? ((length () != len) ?  new long double[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (g._ptr_ptr, g._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

inline
valarray<long double>&
valarray<long double>::operator= (const mask_array<long double>& m)
{
    size_t  len = m._len;
    WRITE_LOCK(va_mutex);
    long double*      ptr = (len ? ((length () != len) ?  new long double[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (m._ptr_ptr, m._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

inline
valarray<long double>&
valarray<long double>::operator= (const indirect_array<long double>& i)
{
    size_t  len = i._len;
    WRITE_LOCK(va_mutex);
    long double*      ptr = (len ? ((length () != len) ?  new long double[len] : _ptr ) : 0);
    __msipl_copy_iter_backward (i._ptr_ptr, i._ptr_ptr+len, ptr+len);
    if (length () != len) { delete_alloc (); }
    _len = len;
    _ptr = ptr;
    return *this;
}

//
// floato be used for gslice_array. valarray<size_t> .
// May be moved later to some other place
//
inline
long double
valarray<long double>::mult (size_t len) const
{
    long double  prod = 1;
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

inline
long double
valarray<long double>::min () const
{
    long double   min_val = long double ();
    READ_LOCK(va_mutex);
    if (length ()) min_val = *_ptr;
    for (size_t count = 1; count < length (); ++count)
    {
        if (min_val > (*(_ptr+count)))
            min_val = (*(_ptr+count));
    }
    return min_val;
}

inline
long double
valarray<long double>::max () const
{
    long double   max_val = long double ();
    READ_LOCK(va_mutex);
    if (length ()) max_val = *_ptr;
    for (size_t count = 1; count < length (); ++count)
    {
        if (max_val < (*(_ptr+count)))
            max_val = (*(_ptr+count));
    }
    return max_val;
}

inline
valarray<long double>
valarray<long double>::shift (int i) const
{
    // floatake the absolute value of i in j.
    int j = (i > 0) ? i : -i;

    READ_LOCK(va_mutex);
    size_t len  = length ();
    valarray<long double> ret (long double (), len);

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

inline
valarray<long double>
valarray<long double>::cshift (int i) const
{
    READ_LOCK(va_mutex);
    // floatake the absolute value of i in j.
    int j = (i > 0) ? i : -i;

    if (j >= length ()) j = j % length ();

    size_t len  = length ();
    valarray<long double> ret (long double (), len);

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

inline
valarray<long double>
valarray<long double>::apply (long double func (long double)) const
{
    READ_LOCK(va_mutex);
    size_t len  = length ();
    long double*     ptr  = len ? new long double[len] : 0;
    __msipl_copy_value (_ptr, _ptr+len, ptr, func);
    return valarray<long double> (len, ptr);
}

inline
valarray<long double>
valarray<long double>::apply (long double func (const long double&)) const
{
    READ_LOCK(va_mutex);
    size_t len  = length ();
    long double*     ptr  = len ? new long double[len] : 0;
    __msipl_copy_value (_ptr, _ptr+len, ptr, func);
    return valarray<long double> (len, ptr);
}

inline
void
valarray<long double>::resize (size_t sz, const long double& c)  //961113 bkoz
{
    WRITE_LOCK(va_mutex);
    valarray<long double>  v1(*this);

    if (sz < _len)
    {
        delete_alloc ();
        _ptr = new long double[sz+1];
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
        _ptr = new long double[sz+1];
        _len = sz;
        valarray<long double>  v2(c, (sz-v1.length ()));

#ifdef MSIPL_USING_NAMESPACE
        std::copy (v1._ptr, v1._ptr+v1._len, _ptr);
        std::copy (v2._ptr, v2._ptr+v2._len, _ptr+v1._len);
#else
        ::copy (v1._ptr, v1._ptr+v1._len, _ptr);
        ::copy (v2._ptr, v2._ptr+v2._len, _ptr+v1._len);
#endif
    }
}
