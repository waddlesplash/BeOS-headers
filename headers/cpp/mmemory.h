/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_DEFMEMORY_H
#define MSIPL_DEFMEMORY_H

#include <mcompile.h>

#include MOD_C_INCLUDE(stddef)
#include MOD_C_INCLUDE(stdio)
#include MOD_C_INCLUDE(stdlib)

#include MOD_INCLUDE(iterator)
#include MOD_INCLUDE(utility)

#include MOD_INCLUDE(new)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifndef DefAllocator
#define DefAllocator allocator
#endif

// Subclause 20.4.3 -- Memory handling primitives

// Section 20.4.3.3 -- construct 

template <class T1, class T2>
inline void construct (T1* p, const T2& value)
{
    new (p) T1 (value);
}

// Section 20.4.3.4 -- destroy

template <class T>
inline void destroy (T* pointer)
{
    pointer->~T ();
}

template <class ForwardIterator>
inline void destroy (ForwardIterator first, ForwardIterator last)
{
    while (first != last)
    {
       destroy (&*first);
       ++first;
    }
}

// Specializations required due to Borland's Bug

null_template
inline void destroy (char*)           {}
null_template
inline void destroy (signed char*)    {}
null_template
inline void destroy (unsigned char*)  {}
null_template
inline void destroy (short*)          {}
null_template
inline void destroy (unsigned short*) {}
null_template
inline void destroy (int*)            {}
null_template
inline void destroy (unsigned int*)   {}
null_template
inline void destroy (long*)           {}
null_template
inline void destroy (unsigned long*)  {}
null_template
inline void destroy (float*)          {}
null_template
inline void destroy (double*)         {}
null_template
inline void destroy (long double*)    {}

#ifdef MSIPL_BOOL_BUILTIN
null_template
inline void destroy (bool*)           {}
#endif

null_template
inline void destroy (char*, char*)                       {}
null_template
inline void destroy (signed char*, signed char*)         {}
null_template
inline void destroy (unsigned char*, unsigned char*)     {}
null_template
inline void destroy (short*, short*)                     {}
null_template
inline void destroy (unsigned short*, unsigned short*)   {}
null_template
inline void destroy (int*, int*)                         {}
null_template
inline void destroy (unsigned int*, unsigned int*)       {}
null_template
inline void destroy (long*, long*)                       {}
null_template
inline void destroy (unsigned long*, unsigned long*)     {}
null_template
inline void destroy (float*, float*)                     {}
null_template
inline void destroy (double*, double*)                   {}
null_template
inline void destroy (long double*, long double*)         {}
#ifdef MSIPL_BOOL_BUILTIN
null_template
inline void destroy (bool*, bool*)                       {}
#endif

#ifdef MSIPL_WCHART
null_template
inline void destroy (wchar_t*)         {}
null_template
inline void destroy (wchar_t*, wchar_t*)                 {}
#endif

// destroy (TYPE**) versions deleted.

// Section 20.4.3 -- get_temporary_buffer

#ifndef MSIPL_STL_BUFFER_SIZE
#define MSIPL_STL_BUFFER_SIZE 16384 // 16k
#endif

extern double __stl_temp_buffer[(MSIPL_STL_BUFFER_SIZE + 
                               sizeof(double) - 1)/sizeof(double)];

template <class T>
inline
pair<T*, ptrdiff_t> 
get_temporary_buffer (ptrdiff_t len, T*)
{
    while (len > MSIPL_STL_BUFFER_SIZE / sizeof (T))
    {
        // new_handler newhand = set_new_handler (0);
        T* tmp = (T*)
        (::operator new ((size_t) (len * sizeof (T))));
        // set_new_handler (newhand);
        if (tmp)
           return pair<T*, ptrdiff_t> (tmp, len);
        len = len / 2;
    }
    return pair<T*, ptrdiff_t>
           ((T*)(void *)__stl_temp_buffer, 
           (ptrdiff_t) (MSIPL_STL_BUFFER_SIZE / sizeof (T)));
}

template <class T>
inline
void return_temporary_buffer (T* p)
{
    if ((void*) (p) != __stl_temp_buffer) delete (p);
}

// Section 20.4.4 -- Specialised Algorithms
// Subclause 20.4.4.1 -- uninitialized_copy

template <class InputIterator, class ForwardIterator>
inline
ForwardIterator
uninitialized_copy (InputIterator first, InputIterator last,
                    ForwardIterator result)
{
    while (first != last) construct (&*result++, *first++);
    return result;
}

// Subclause 20.4.4.2 -- uninitialized_fill
 
template <class ForwardIterator, class T>
inline
void
uninitialized_fill (ForwardIterator first, ForwardIterator last,
                    const T& x)
{
    while (first != last) construct (&*first++, x);
}

// Subclause 20.4.4.3 -- uninitialized_fill_n
 
template <class ForwardIterator, class Size, class T>
inline
ForwardIterator
uninitialized_fill_n (ForwardIterator first, Size n, const T& x)
{
    while (n--) construct (&*first++, x);
    return first;
}
 
// Section 20.4.1 -- The default allocator
// Subclause 20.4.1.1 -- allocator member functions.

template <class T>   class allocator; // forward declaration

null_template
class allocator<void> {
public:
    typedef size_t           size_type;
    typedef ptrdiff_t        difference_type;
    typedef void*            pointer;
    typedef const void*      const_pointer;
    typedef void             value_type;

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class U>
    struct rebind { 
        typedef allocator<U>  other;
    };
#endif

    allocator () MSIPL_THROW {}

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class U>
    allocator (const allocator<U>&) MSIPL_THROW {}
    template <class U>
    allocator& operator=(const allocator<U>&) MSIPL_THROW { return *this; }
#else
    allocator (const allocator&) MSIPL_THROW {}
    allocator& operator=(const allocator&) MSIPL_THROW { return *this; }
#endif

    ~allocator () MSIPL_THROW {}

    //pointer allocate (size_type, const void* hint) { return (pointer)0; }
    pointer allocate (size_type, const void*) { return (pointer)0; }
    //void    deallocate (pointer p) {};
    void    deallocate (pointer) {};
    size_type max_size () const MSIPL_THROW { return 0; }
};

template <class T>
class allocator {
public:
    typedef T                             value_type;
    typedef T*                            pointer;
    typedef const T*                      const_pointer;
    typedef T&                            reference;
    typedef const T&                      const_reference;
    typedef size_t                        size_type;
    typedef ptrdiff_t                     difference_type;

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class U>
    struct rebind {
        typedef allocator<U>  other; 
    };
#endif

    inline
    pointer allocate (size_type n,typename allocator<void>::const_pointer hint = 0)
    { 
        hint; 				//961205 bkoz this is just to get rid of strict compiler warnings
        // new_handler newhand = set_new_handler (0);
        T* tmp = (T*)(::operator new ((size_t) (n * sizeof (T))));
        if (tmp == 0)
        {
#ifdef MSIPL_EXCEPT
            throw bad_alloc ();
#else
            fprintf (stderr, "STL++ : Could not allocate  memory ...\n");
            exit (1);
#endif
        }
        // set_new_handler (newhand); 
        return tmp;
    }
    
    inline
    void deallocate (pointer p)
    { 
        ::operator delete (p);
    }
    
    inline
    pointer address (reference x) const
    { 
        return (pointer)&x; 
    }
    
    //970216 bkoz
    /*
    inline
    const_pointer address (const_reference x) const
    {
        return (const_pointer)&x; 
    }
    */
    
    //  This function is not there in Draft.    
    inline
    size_type init_page_size ()
    { 
        return max (size_type (1), size_type (4096/sizeof (T))); 
    }
    
	//970214 bkoz
	inline
    size_type init_page_size_small ()
    { 
        return max (size_type (1), size_type (1024/sizeof (T))); 
    }

    inline
    size_type max_size () const MSIPL_THROW
    { 
        return max (size_type (1), size_type (size_type (-1)/sizeof (T))); 
    }
    
    inline
    void construct (pointer p, const T& val)
    {
        new ((void*)p) T(val);
    }
    
    //961113 bkoz
    //illegal access to protected/private member?
	/*
	void destroy (pointer p) 
    {
        ((T*)p)->~T();
    }
	*/
	
    inline
    allocator () MSIPL_THROW {}
#ifdef MSIPL_MEMBER_TEMPLATE
    template<class U>
    allocator (const allocator<U>&) MSIPL_THROW {}

    template<class U>
    allocator& 
    operator= (const allocator<U>&) MSIPL_THROW { return *this; }
#else
    inline
    allocator (const allocator&) MSIPL_THROW {}

    inline
    allocator& 
    operator= (const allocator&) MSIPL_THROW { return *this; }
#endif
    inline
    ~allocator () MSIPL_THROW {}
};

template <class T1, class T2>
inline
bool
operator== (const allocator<T1>& , const allocator<T2>&) MSIPL_THROW
{
    return true;
}
 
template <class T1, class T2>
inline
bool
operator!= (const allocator<T1>& , const allocator<T2>&) MSIPL_THROW
{
    return false;
}

// Subclause 20.4.1.2 -- allocator placement new
//
// Not implemented as this depends on allocator to be
// a template class with a nested template  class.
//
// void* operator new (size_t n, allocator& a) {
//     return a.allocate<char, void> (n, 0);
// }
//

// Subclause 20.4.2.1 -- raw storage iterator

template <class OutputIterator, class T>
class raw_storage_iterator 
    //: public iterator<output_iterator_tag, void, void> {
    : public global_iterator<output_iterator_tag, void, void> {
protected:
    OutputIterator iter;
public:
    explicit
    raw_storage_iterator (OutputIterator x) : iter (x) {}
    raw_storage_iterator<OutputIterator, T>& operator*() { return *this; }
    raw_storage_iterator<OutputIterator, T>& operator= (const T& element) {
        construct (iter, element);
        return *this;
    }
    raw_storage_iterator<OutputIterator, T>& operator++ ()
    {
        ++iter;
        return *this;
    }
    raw_storage_iterator<OutputIterator, T> operator++ (int)
    {
        raw_storage_iterator<OutputIterator, T> tmp = *this;
        ++iter;
        return tmp;
    }
};

// Section 20.4.5 -- Pointers
// Subclause 20.4.5.1 -- Class auto_ptr
/*
template <class X>
class auto_ptr {
public :

   typedef X   element_type;

   explicit
   auto_ptr (X* p = 0) : ptr_ (p) { owns = (p) ? true : false; }

#ifdef MSIPL_MEMBER_TEMPLATE
   template <class Y>
   auto_ptr (const auto_ptr<Y>& a)
   {
       owns = a.owns;
       ptr_ = (X*)a.release ();
   }

   auto_ptr (const auto_ptr& a)
   {
       //printf (" copy c'tor\n");
       owns = a.owns;
       ptr_ = a.release ();
   }

   template <class Y>
   auto_ptr& operator=(const auto_ptr<Y>& a)
   {
       if (ptr_ != a.ptr_) { delete get (); ptr_ = 0; }
       owns = a.owns;
       ptr_ = (X*)a.release ();
       return *this;
   }

   auto_ptr& operator=(const auto_ptr& a)
   {
       if (ptr_ != a.ptr_) { delete get (); ptr_ = 0; }
       owns = a.owns;
       ptr_ = a.release ();
       return *this;
   }
#else
   auto_ptr (auto_ptr& a)
   {
       //printf ("22 - Copy C'tor\n");
       // owns = false;
       // if (a.owns) { owns = true; } 
       owns = a.owns;  
       ptr_ = a.release ();
   }
   auto_ptr& operator=(auto_ptr& a)
   {
       //printf ("22 - operator==\n");
       if (ptr_ != a.ptr_) { delete get (); ptr_ = 0; }
       owns = a.owns;  
       ptr_ = a.release ();
       return *this;
   }
#endif

   ~auto_ptr () { if (owns){ delete get (); ptr_ = 0; } owns = false; }
   X& operator* () const { return *get (); }
   X* operator-> () const { return get (); }
   X* get () const { return ptr_; }
   X* release () const {
      // ptr_ = 0;
      ((auto_ptr*)this)->owns = false;
      return ptr_;
   }

protected :
   X* ptr_;
   bool owns;
};
*/

template<class T>
class auto_ptr
{
	public:
		auto_ptr(T* p = 0) : owner(p != 0), p_(p) { }
		
		auto_ptr(const auto_ptr& r) : owner(r.owner), p_(r.release())	{ }
		
		~auto_ptr() { if (owner) delete p_; owner = 0; }
		
		auto_ptr&		operator = (const auto_ptr& r)		{
			if ((void *)&r != (void *)this) {
				if (owner)
					delete p_;
				owner = r.owner;
				p_ = r.release();
			}
			return *this;
		}

		T&	operator * (void) const{ return *p_; }
		
		T*	operator -> (void) const { return p_; }
		
		T*	get(void) const { return p_; }
		
		T*	release(void) const{ 
			const_cast<auto_ptr *>(this)->owner = 0;
			return p_; 
		}

	private:
		T*		p_;
		bool	owner;
};

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_DEFMEMORY_H */

//961113 bkoz line 300, commented out destroy member function, mw compiler has problem with
//		 this when destructor private. . .as syntax checks all member functions when
//		 instantiates this bug surfaces (ie flags instance that user wouldn't code for)
//961121 bkoz line 401, 425, 433 commented out the printf's
//961121 bkoz line 356 changed inherited iterator to global_iterator
//961121 bkoz line 235, 234 took out unused variables
//961205 bkoz line 261 added hint; for default argument and remove strict compiler warning
//961210 bkoz added alignment wrapper
//961223 bkoz lines 487-521 added auto_ptr via Zart Colwing
//970214 bkoz line 306 added allocator::init_page_size_small() for smaller buffer setups, see
//		 Efrem J. Sternbach in tree.h .ine 114
//970216 bkoz line 292, commented out const_pointer address (const_reference x) const for list*
