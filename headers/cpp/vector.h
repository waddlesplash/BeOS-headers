/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_VECTOR_H
#define MSIPL_VECTOR_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(algobase)

//
// <limits> for MSIPL_WORD_BIT
//
#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(limits)
#else
#include MOD_INCLUDE(mlimits)
#endif

#ifdef MSIPL_ANSI_HEADER
#include MOD_INCLUDE(stdexcept)
#else
#include MOD_INCLUDE(mexcept)
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifndef vector
#define vector vector
#endif

// Subclause 23.2.8 -- class vector

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Allocator = allocator<T> >
#else
template <class T, class Allocator>
#endif
class vector {
public:
    
    // 23.2.5.1  types:
    // 
    typedef          Allocator                        allocator_type;
    typedef          T                                value_type;
    typedef typename allocator_type::pointer          pointer;
    typedef typename allocator_type::const_pointer    const_pointer;
    typedef typename allocator_type::pointer          iterator;
    typedef typename allocator_type::const_pointer    const_iterator;
    typedef typename allocator_type::reference        reference;
    typedef typename allocator_type::const_reference  const_reference;
    typedef typename allocator_type::size_type        size_type;
    typedef typename allocator_type::difference_type  difference_type;

    typedef reverse_iterator<const_iterator, value_type, const_reference, 
            const_pointer, difference_type>        const_reverse_iterator;

    typedef reverse_iterator<iterator, value_type, reference,
            pointer, difference_type>                    reverse_iterator;

protected:

    allocator_type            allocator_;
    iterator                  start;
    iterator                  finish;
    iterator                  end_of_storage;

    DEC_OBJ_LOCK(_mutex)

    void insert_aux (iterator position, const T& x);

public:

    //
    // 23.2.5.2  construct/copy/destroy:
    //
    inline
    explicit
    vector (const Allocator& alloc = Allocator()) ;

    explicit
    vector (size_type n, const T& value = T (), const Allocator& alloc = Allocator());

    vector (const vector<T, Allocator>& x);

    vector (const_iterator first, const_iterator last, const Allocator& alloc = Allocator());
    
    ~vector ();

    inline
    void assign (const_iterator first, const_iterator last);
    
    inline
    void assign (size_type n, const T& t = T ());

    inline
    allocator_type 
    get_allocator () const ;
 
    vector<T, Allocator>& 
    operator= (const vector<T, Allocator>& x);

    //
    // 23.2.5.3  iterators:
    //
    inline
    iterator                 begin ()    { READ_LOCK(_mutex); return start;  }
    
    inline
    const_iterator           begin () const  { READ_LOCK(_mutex); return start;  }
    
    inline
    iterator                 end ()   { READ_LOCK(_mutex); return finish; }
    
    inline
    const_iterator           end ()   const {  READ_LOCK(_mutex); return finish; }

    inline
    reverse_iterator       rbegin ()  { return reverse_iterator (end ()); }
    
    inline
    const_reverse_iterator rbegin () const { return const_reverse_iterator (end ()); }
    
    inline
    reverse_iterator       rend ()  { return reverse_iterator (begin ()); }
    
    inline
    const_reverse_iterator rend () const  { return const_reverse_iterator (begin ()); }

    //
    // 23.2.5.4  capacity:
    // 
    size_type 
    size ()     const { return size_type (end () - begin ());  }
    
    size_type 
    max_size () const { return allocator_.max_size (); }

    void resize (size_type sz, T v = T ());

    size_type capacity () const
    { READ_LOCK(_mutex); return size_type (end_of_storage - begin ()); }

    bool empty () const { return begin () == end (); }

    void reserve (size_type n);

    //
    // 23.2.5.5 element access:
    //
    reference operator[] (size_type n)
    {
        return *(begin () + n); 
    }

    const_reference operator[] (size_type n) const
    {
        return *(begin () + n); 
    }

    const_reference at (size_type n) const
    {
        if ( n >= (end() - begin()))      // mm 970729
        {
#ifdef  MSIPL_EXCEPT
            throw   out_of_range ("Out of range exception occurred");
#else
            fprintf (stderr, "Out of range exception occurred\n");
            exit (1);
#endif
        }
        return *(begin () + n);
    }

    reference at (size_type n) 
    {
        if ( n >= (end() - begin()) )      // mm 970729
        {
#ifdef  MSIPL_EXCEPT
            throw   out_of_range ("Out of range exception occurred");
#else
            fprintf (stderr, "Out of range exception occurred\n");
            exit (1);
#endif
        }

        return *(begin () + n);
    }

    reference         front ()        { return *begin ();     }
    const_reference   front () const  { return *begin ();     }
    reference         back ()         { return * (end () - 1); }
    const_reference   back ()  const  { return * (end () - 1); }

    //
    // 23.2.5.6 modifiers:
    //
    void push_back (const T& x);

    inline
    void pop_back ();

    iterator insert (iterator position, const T& x = T ());

    void insert (iterator position, const_iterator first, const_iterator last);

    void insert (iterator position, size_type n, const T& x = T());
	
    iterator erase (iterator position) ;

    iterator erase (iterator first, iterator last);

    inline
    void swap (vector<T, Allocator>& x);

    void clear ()  { erase (begin (), end ()); }
};

template <class T, class Allocator>
inline bool operator== (const vector<T, Allocator>& x,
                        const vector<T, Allocator>& y)
{
    return x.size () == y.size () &&
	   equal (x.begin (), x.end (), y.begin ());
}

template <class T, class Allocator>
inline bool operator< (const vector<T, Allocator>& x,
                       const vector<T, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (),
	   y.begin (), y.end ());
}

template <class T, class Allocator>
vector<T, Allocator>::vector (const Allocator& alloc) 
: allocator_(alloc), start (0), finish (0), end_of_storage (0) {}

//#pragma dont_inline on
template <class T, class Allocator>
vector<T, Allocator>::vector (size_type n, const T& value, const Allocator& alloc)
: allocator_(alloc)
{
    start = allocator_.allocate (n);
    uninitialized_fill_n (start, n, value);
    finish = start + n;
    end_of_storage = finish;
}

template <class T, class Allocator>
vector<T, Allocator>::vector (const vector<T, Allocator>& x)
: allocator_(x.allocator_)
{
    start = allocator_.allocate (x.end () - x.begin ());
    finish = uninitialized_copy (x.begin (), x.end (), start);
    end_of_storage = finish;
}

template <class T, class Allocator>
vector<T, Allocator>::vector (const_iterator first, const_iterator last, const Allocator& alloc)
: allocator_(alloc)
{
    size_type n = 0;
    n = distance (first, last);
    start = allocator_.allocate (n);
    finish = uninitialized_copy (first, last, start);
    end_of_storage = finish;
}

template <class T, class Allocator>
vector<T, Allocator>::~vector ()
{
    destroy (start, finish);
    allocator_.deallocate (start);
    REMOVE(_mutex);
}
// mf 101597 #pragma dont_inline reset

template <class T, class Allocator>
void 
vector<T, Allocator>::assign (const_iterator first, const_iterator last)
{
   erase (begin (), end ());
   insert (begin (), first, last);
}

template <class T, class Allocator>
void 
vector<T, Allocator>::assign (size_type n, const T& t)
{
   erase (begin (), end ());
   insert (begin (), n, t);
}

template <class T, class Allocator>
vector<T, Allocator>::allocator_type
vector<T, Allocator>::get_allocator () const 
{
    return allocator_;
}

template <class T, class Allocator>
void 
vector<T, Allocator>::resize (size_type sz, T v)
    {
        if (sz > size ())
           insert (end (), sz-size (), v);
        else if (sz < size ())
           erase (begin ()+sz, end ());
    }

template <class T, class Allocator>
void 
vector<T, Allocator>::reserve (size_type n)
{
    if (capacity () < n)
    {
        WRITE_LOCK(_mutex);
        iterator tmp = allocator_.allocate (n);
        uninitialized_copy (begin (), end (), tmp);
        destroy (start, finish);
        allocator_.deallocate (start);
        finish = tmp + size ();
        start = tmp;
        end_of_storage = begin () + n;
    }
}

template <class T, class Allocator>
void 
vector<T, Allocator>::push_back (const T& x)
{
    WRITE_LOCK(_mutex);
    if (finish != end_of_storage)
    {
        construct (finish, x);
            finish++;
    } else
        insert_aux (end (), x);
}

template <class T, class Allocator>
void 
vector<T, Allocator>::pop_back ()
{
    WRITE_LOCK(_mutex);
    --finish;
    destroy (finish); 
}

template <class T, class Allocator>
vector<T, Allocator>::iterator 
vector<T, Allocator>::insert (iterator position, const T& x)
{
    WRITE_LOCK(_mutex);
    size_type n = position - begin ();
    if (finish != end_of_storage && position == end ())
    {
        construct (finish, x);
            finish++;
    } else
        insert_aux (position, x);
    return begin () + n;
}

template <class T, class Allocator>
vector<T, Allocator>::iterator 
vector<T, Allocator>::erase (iterator position) 
{
    WRITE_LOCK(_mutex);
    difference_type len = 0;
    iterator ret_iter = begin ();
    while (ret_iter != position) { len++; ret_iter++; }
    if (position + 1 != end ())
        copy (position + 1, end (), position);
    --finish;
    destroy (finish);
    ret_iter = begin ();
    for (int i=0; i < len; ++i) ++ret_iter;
    return ret_iter;
}

template <class T, class Allocator>
vector<T, Allocator>::iterator 
vector<T, Allocator>::erase (iterator first, iterator last)
{
    WRITE_LOCK(_mutex);
    iterator ret_iter = begin ();
    difference_type len = 0;
    while (ret_iter != last) { len++; ++ret_iter; }
    vector<T, Allocator>::iterator i = copy (last, end (), first);
    destroy (i, finish);
    // work around for destroy (copy (last, end (), first), finish);
    finish = finish - (last - first); 
    ret_iter = begin ();
    for (int k = 0; k < len-(last - first); ++k) ++ret_iter;
    return ret_iter;
}

template <class T, class Allocator>
void
vector<T, Allocator>::swap (vector<T, Allocator>& x)
{
    WRITE_LOCK(_mutex);
#ifdef MSIPL_USING_NAMESPACE
    std::swap (start, x.start);
    std::swap (finish, x.finish);
    std::swap (end_of_storage, x.end_of_storage);
#else
    ::swap (start, x.start);
    ::swap (finish, x.finish);
    ::swap (end_of_storage, x.end_of_storage);
#endif
}

template <class T, class Allocator>
vector<T, Allocator>& 
vector<T, Allocator>::operator= (const vector<T, Allocator>& x)
{
    WRITE_LOCK(_mutex);
    if (&x == this) return *this;
    if (x.size () > capacity ())
    {
        destroy (start, finish);
        allocator_.deallocate (start);
        start = allocator_.allocate (x.end () - x.begin ());
        end_of_storage = uninitialized_copy (x.begin (), x.end (), start);
    } else if (size () >= x.size ())
    {
       vector<T, Allocator>::iterator i = copy (x.begin (), x.end (), begin ());
        destroy (i, finish);
        // work around for destroy (copy (x.begin (), x.end (),
        // begin ()), finish);
    } else
    {
        copy (x.begin (), x.begin () + size (), begin ());
        uninitialized_copy (x.begin () + size (), x.end (), begin () + size ());
    }
    finish = begin () + x.size ();
    return *this;
}

template <class T, class Allocator>
void vector<T, Allocator>::insert_aux (iterator position, const T& x)
{
    if (finish != end_of_storage) {
        construct (finish, *(finish - 1));
        copy_backward (position, finish - 1, finish);
        *position = x;
        ++finish;
    } 
    else {
        size_type len = size () ? 2 * size () : allocator_.init_page_size ();
        iterator tmp = allocator_.allocate (len);
        uninitialized_copy (begin (), position, tmp);
        construct (tmp + (position - begin ()), x);
        uninitialized_copy (position, end (), tmp + (position - begin ()) + 1); 
        destroy (begin (), end ());
        allocator_.deallocate (begin ());
        end_of_storage = tmp + len;
        finish = tmp + size () + 1;
        start = tmp;
    }
}

template <class T, class Allocator>
void vector<T, Allocator>::insert (iterator position, size_type n, const T& x)
{
    if (n == 0) return;
    WRITE_LOCK(_mutex);
    if (end_of_storage - finish >= n)
    {
        if (end () - position > n)
        {
            uninitialized_copy (end () - n, end (), end ());
            copy_backward (position, end () - n, end ());
            fill (position, position + n, x);
        } else
        {
            uninitialized_copy (position, end (), position + n);
            fill (position, end (), x);
            uninitialized_fill_n (end (), n - (end () - position), x);
        }
        finish += n;
    } else
    {
        size_type len = size () + max (size (), n);
        iterator tmp = allocator_.allocate (len);
        uninitialized_copy (begin (), position, tmp);
        uninitialized_fill_n (tmp + (position - begin ()), n, x);
        uninitialized_copy (position, end (), tmp + (position - begin () + n));
        destroy (begin (), end ());
        allocator_.deallocate (begin ());
        end_of_storage = tmp + len;
        finish = tmp + size () + n;
        start = tmp;
    }
}

template <class T, class Allocator>
void vector<T, Allocator>::insert (iterator position, const_iterator first, const_iterator last)
{
    if (first == last) return;
    size_type n = 0;
    n = distance (first, last);
    WRITE_LOCK(_mutex);
    if (end_of_storage - finish >= n)
    {
        if (end () - position > n)
        {
            uninitialized_copy (end () - n, end (), end ());
            copy_backward (position, end () - n, end ());
            copy (first, last, position);
        } else
        {
            uninitialized_copy (position, end (), position + n);
            copy (first, first + (end () - position), position);
            uninitialized_copy (first + (end () - position), last, end ());
        }
        finish += n;
    } 
    else
    {
        size_type len = size () + max (size (), n);
        iterator tmp = allocator_.allocate (len);
        uninitialized_copy (begin (), position, tmp);
        uninitialized_copy (first, last, tmp + (position - begin ()));
        uninitialized_copy (position, end (), tmp + (position - begin () + n));
        destroy (begin (), end ());
        allocator_.deallocate (begin ());
        end_of_storage = tmp + len;
        finish = tmp + size () + n;
        start = tmp;
    }
}


//
//  provide vector<bool> specialization only if "bool" is a
//  builtin data type
//

//970406 bkoz this implementation doesn't work, use 2.2 or general template
/*
#ifdef MSIPL_BOOL_BUILTIN

#define MSIPL_WORD_BIT (numeric_limits<unsigned int>::digits)

// Subclause 23.2.9 -- class vector<bool>

#ifdef MSIPL_PARTIAL_TEMPL
#ifdef MSIPL_DEF_TEMPARG
template vector<class Allocator = allocator<unsigned int> >
#else
template vector<class Allocator>
#endif
class vector<bool, Allocator> {
#else   
null_template
class vector<bool, DefAllocator<unsigned int> > {
#endif
public:

#ifdef MSIPL_PARTIAL_TEMPL
    typedef Allocator                        allocator_type;
#else
    typedef DefAllocator<unsigned int>       allocator_type;
#endif
    typedef bool                             value_type;
    typedef bool                             const_reference;
    typedef allocator_type::size_type        size_type;
    typedef allocator_type::difference_type  difference_type; 
    typedef allocator_type::pointer          pointer; 
    typedef allocator_type::const_pointer    const_pointer; 

    class iterator;
    class const_iterator;

    class reference {
        friend class iterator;
        friend class const_iterator;
    protected:
        unsigned int* p;
        unsigned int mask;
        DEC_OBJ_LOCK(ref_mutex)

        reference (unsigned int* x, unsigned int y) : p (x), mask (y) {}
    public:
        reference () : p (0), mask (0) {}
        ~reference (){ REMOVE(ref_mutex); }
        operator bool () const { return ! (! (*p & mask)); }
        reference& operator= (const bool x)
        {
            WRITE_LOCK(ref_mutex);
            if (x)      
                *p |= mask;
            else 
                *p &= ~mask;
            return *this;
        }
        reference& operator= (const reference& x)
        { WRITE_LOCK(ref_mutex); return *this = bool (x); }
        bool operator== (const reference& x) const
        {
            READ_LOCK(ref_mutex);
            return bool (*this) == bool (x);
        }
        bool operator< (const reference& x) const
        {
            READ_LOCK(ref_mutex);
            return bool (*this) < bool (x);
        }
        void flip () { WRITE_LOCK(ref_mutex); *p ^= mask; }
    };

    class iterator 
#ifdef MSIPL_USING_NAMESPACE
      : public std::iterator <random_access_iterator_tag, bool, difference_type>
#else
      : public ::global_iterator <random_access_iterator_tag, bool, difference_type>
#endif
    {
#ifdef MSIPL_PARTIAL_TEMPL
        friend class vector<bool, Allocator>;
#else
        friend class vector<bool, DefAllocator<unsigned int> >;
#endif
        friend class const_iterator;

    protected:
        unsigned int* p;
        unsigned int offset;
        DEC_OBJ_LOCK(iter_mutex)

        void bump_up ()
        {
            if (offset++ == MSIPL_WORD_BIT - 1)
            {
                offset = 0;
                ++p;
            }
        }
        void bump_down ()
        {
            if (offset-- == 0)
            {
                offset = MSIPL_WORD_BIT - 1;
                --p;
            }
        }

    public:
        iterator ()
        : p (0), offset (0) {}

        iterator (unsigned int* x, unsigned int y)
        : p (x), offset (y) {}

        ~iterator () { REMOVE(iter_mutex); }

        reference operator* () const
          { READ_LOCK(iter_mutex); return reference (p, 1U << offset); }

        iterator& operator++ ()
        {
            WRITE_LOCK(iter_mutex);
            bump_up ();
            return *this;
        }
        iterator operator++ (int)
        {
            WRITE_LOCK(iter_mutex);
            iterator tmp = *this;
            bump_up ();
            return tmp;
        }
        iterator& operator-- ()
        {
            WRITE_LOCK(iter_mutex);
            bump_down ();
            return *this;
        }
        iterator operator-- (int)
        {
            WRITE_LOCK(iter_mutex);
            iterator tmp = *this;
            bump_down ();
            return tmp;
        }
        iterator& operator+= (difference_type i)
        {
            WRITE_LOCK(iter_mutex);
            difference_type n = i + offset;
            p += n / MSIPL_WORD_BIT;
            n = n % MSIPL_WORD_BIT;
            if (n < 0)
            {
                offset = n + MSIPL_WORD_BIT;
                --p;
            } else
                offset = n;
            return *this;
        }
        iterator& operator-= (difference_type i)
        {
            *this += -i;
            return *this;
        }
        iterator operator+ (difference_type i) const
        {
            iterator tmp = *this;
            return tmp += i;
        }
        iterator operator- (difference_type i) const
        {
            iterator tmp = *this;
            return tmp -= i;
        }
        difference_type operator- (iterator x) const
        {
            READ_LOCK(iter_mutex);
            return MSIPL_WORD_BIT * (p - x.p) + offset - x.offset;
        }
        reference operator[] (difference_type i)
        { return *(*this + i); }
        bool operator== (const iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return p == x.p && offset == x.offset;
        }
        bool operator!= (const iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return !(*this == x);
        }
        bool operator< (iterator x) const
        {
            READ_LOCK(iter_mutex);
            return p < x.p || (p == x.p && offset < x.offset);
        }
    };

    class const_iterator 
#ifdef MSIPL_USING_NAMESPACE
      : public std::iterator <random_access_iterator_tag, bool, difference_type> {
#else
      : public ::global_iterator <random_access_iterator_tag, bool, difference_type> {
#endif

#ifdef MSIPL_PARTIAL_TEMPL
        friend class vector<bool, Allocator>;
#else
        friend class vector<bool, DefAllocator<unsigned int> >;
#endif

    protected:

        unsigned int*   p;
        unsigned int    offset;
        DEC_OBJ_LOCK(citer_mutex)

        void bump_up ()
        {
            if (offset++ == MSIPL_WORD_BIT - 1)
            {
                offset = 0;
                ++p;
            }
        }
        void bump_down ()
        {
            if (offset-- == 0)
            {
                offset = MSIPL_WORD_BIT - 1;
                --p;
            }
        }
    public:
        const_iterator () : p (0), offset (0) {}

        const_iterator (unsigned int* x, unsigned int y)
        : p (x), offset (y) {}

        const_iterator (const iterator& x)
        : p (x.p), offset (x.offset) {}

        ~const_iterator () { REMOVE (citer_mutex); }

        const_reference operator*() const
        {
            return reference (p, 1U << offset);
        }
        const_iterator& operator++ ()
        {
            bump_up ();
            return *this;
        }
        const_iterator operator++ (int)
        {
            WRITE_LOCK(citer_mutex);
            const_iterator tmp = *this;
            bump_up ();
            return tmp;
        }
        const_iterator& operator-- ()
        {
            WRITE_LOCK(citer_mutex);
            bump_down ();
            return *this;
        }
        const_iterator operator-- (int)
        {
            WRITE_LOCK(citer_mutex);
            const_iterator tmp = *this;
            bump_down ();
            return tmp;
        }
        const_iterator& operator+= (difference_type i)
        {
            WRITE_LOCK(citer_mutex);
            difference_type n = i + offset;
            p += n / MSIPL_WORD_BIT;
            n = n % MSIPL_WORD_BIT;
            if (n < 0)
            {
                offset = n + MSIPL_WORD_BIT;
                --p;
            } else
                offset = n;
            return *this;
        }
        const_iterator& operator-= (difference_type i)
        {
            *this += -i;
            return *this;
        }
        const_iterator operator+ (difference_type i) const
        {
            const_iterator tmp = *this;
            return tmp += i;
        }
        const_iterator operator- (difference_type i) const
        {
            const_iterator tmp = *this;
            return tmp -= i;
        }
        difference_type operator- (const_iterator x) const
        {
            READ_LOCK(citer_mutex);
            return MSIPL_WORD_BIT * (p - x.p) + offset - x.offset;
        }
        const_reference operator[] (difference_type i) const
        { 
            return *(*this + i); 
        }
        bool operator== (const const_iterator& x) const
        {
            READ_LOCK(citer_mutex);
            return p == x.p && offset == x.offset;
        }
        bool operator!= (const const_iterator& x) const
        {
            READ_LOCK(citer_mutex);
            return !(*this == x);
        }
        bool operator< (const_iterator x) const
        {
            READ_LOCK(citer_mutex);
            return p < x.p || (p == x.p && offset < x.offset);
        }
    };

    typedef reverse_iterator<const_iterator, value_type, const_reference, 
                             const_pointer, difference_type>
                             const_reverse_iterator;
    typedef reverse_iterator<iterator, value_type, reference,
                             reference*, difference_type>
                             reverse_iterator;

protected:

    allocator_type                 allocator_;
    iterator                       start;
    iterator                       finish;
    unsigned int*                  end_of_storage;

    DEC_OBJ_LOCK(bv_mutex)

    unsigned int* bit_alloc (size_type n)
    {
        return allocator_.allocate ((n + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT);
    }
    void initialize (size_type n)
    {
        unsigned int* q = bit_alloc (n);
        end_of_storage = q + (n + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        start = iterator (q, 0);
        finish = start + n;
    }

    inline void
    insert_aux (iterator position, bool x);

#ifdef MSIPL_PARTIAL_TEMPL
    typedef vector<bool, Allocator> self;
#else
    typedef vector<bool, DefAllocator<unsigned int> > self;
#endif

public:

    iterator          begin ()       { READ_LOCK(bv_mutex); return start;  }
    const_iterator    begin () const { READ_LOCK(bv_mutex); return start;  }

    iterator          end ()         { READ_LOCK(bv_mutex); return finish; }
    const_iterator    end ()   const { READ_LOCK(bv_mutex); return finish; }

    reverse_iterator  rbegin ()      { return reverse_iterator (end ()); }
    const_reverse_iterator rbegin () const
    { 
        return const_reverse_iterator (end ()); 
    }
    reverse_iterator rend () { return reverse_iterator (begin ()); }
    const_reverse_iterator rend () const
    { 
        return const_reverse_iterator (begin ()); 
    }

    size_type size ()     const { return size_type (end () - begin ());  }
    size_type max_size () const { return allocator_.max_size ();       }

    void resize (size_type sz, bool v = false)
    {
        if (sz > size ())
           insert (end (), sz-size (), v);
        else if (sz < size ())
           erase (begin ()+sz, end ());
    }

    size_type capacity () const
    {
        READ_LOCK(bv_mutex); 
        return size_type (const_iterator (end_of_storage, 0) - begin ());
    }

    bool empty () const { return begin () == end (); }

    reference       operator[] (size_type n) { return * (begin () + n); }
    const_reference operator[] (size_type n) const
    { return * (begin () + n); }

    const_reference at (size_type n) const
    {
        if ( n > size() )
        {
#ifdef  MSIPL_EXCEPT
            throw   out_of_range ("Out of range exception occurred");
#else
            fprintf (stderr, "Out of range exception occurred\n");
            exit (1);
#endif
        }
        return *(begin () + n);
    }

    reference at (size_type n) 
    {
        if ( n > size() )
        {
#ifdef  MSIPL_EXCEPT
            throw   out_of_range ("Out of range exception occurred");
#else
            fprintf (stderr, "Out of range exception occurred\n");
            exit (1);
#endif
        }

        return *(begin () + n);
    }

    explicit
#ifdef MSIPL_PARTIAL_TEMPL
    vector (const Allocator& alloc = Allocator())
#else
    vector (const DefAllocator<unsigned int>& alloc 
              = DefAllocator<unsigned int>())
#endif
    : allocator_(alloc), start (iterator ()), finish (iterator ()),
      end_of_storage (0)                              {}

    explicit
#ifdef MSIPL_PARTIAL_TEMPL
    vector (size_type n, const bool& value = bool (),
            const Allocator& alloc = Allocator())
#else
    vector (size_type n, const bool& value = bool (),
            const DefAllocator<unsigned int>& alloc 
              = DefAllocator<unsigned int>())
#endif
    : allocator_(alloc)
    {
        initialize (n);
        fill(start.p, end_of_storage, value ? ~0 : 0);
    }

    vector (const self& x)
    : allocator_(x.allocator_)
    {
        initialize (x.size ());
        copy(x.begin (), x.end (), start);
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template<class InputIterator>
#ifdef MSIPL_PARTIAL_TEMPLATE
    vector (InputIterator first, InputIterator last,
            const Allocator& alloc = Allocator())
#else
    vector (InputIterator first, InputIterator last,
            const DefAllocator<unsigned int>& alloc 
              = DefAllocator<unsigned int>())
#endif
    : allocator_(alloc)
    {
        size_type n = 0;
        n = distance (first, last);
        initialize (n);
        copy (first, last, start);
    }
#else
#ifdef MSIPL_PARTIAL_TEMPLATE
    vector (const_iterator first, const_iterator last,
            const Allocator& alloc = Allocator())
#else
    vector (const_iterator first, const_iterator last,
            const DefAllocator<unsigned int>& alloc 
              = DefAllocator<unsigned int>())
#endif
    : allocator_(alloc)
    {
        size_type n = 0;
        n = distance (first, last);
        initialize (n);
        copy (first, last, start);
    }
#ifdef MSIPL_PARTIAL_TEMPLATE
    vector (const bool* first, const bool* last,
            const Allocator& alloc = Allocator())
#else
    vector (const bool* first, const bool* last,
            const DefAllocator<unsigned int>& alloc 
              = DefAllocator<unsigned int>())
#endif
    : allocator_(alloc)
    {
        size_type n = 0;
        n = distance (first, last);
        initialize (n);
        copy (first, last, start);
    }
#endif

#ifdef MSIPL_MEMBER_TEMPLATE
    template<class InputIterator>
    void assign (InputIterator first, InputIterator last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }
    template <class Size>
    void assign (Size n, const bool& t = bool ())
    {
       erase (begin (), end ());
       insert (begin (), n, t);
    }
    allocator_type
    get_allocator () const 
    {
        return allocator_;
    }
    template<class InputIterator>
    inline
    void insert (iterator pos,
                 InputIterator first, InputIterator last);
#else
    void assign (const_iterator first, const_iterator last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }
    void assign (size_type n, const bool& t = bool ())
    {
       erase (begin (), end ());
       insert (begin (), n, t);
    }
    inline
    void insert (iterator pos,
                 const_iterator first, const_iterator last);
#endif

    ~vector () { allocator_.deallocate (start.p); REMOVE(bv_mutex); }

    self& operator= (const self& x)
    {
        WRITE_LOCK(bv_mutex); 
        if (&x == this) return *this;
        if (x.size () > capacity ())
        {
            allocator_.deallocate (start.p); 
            initialize (x.size ());
        }
        copy (x.begin (), x.end (), begin ());
        finish = begin () + x.size ();
        return *this;
    }

    void reserve (size_type n)
    {
        if (capacity () < n)
        {
            WRITE_LOCK(bv_mutex);
            unsigned int* q = bit_alloc (n);
            finish = copy (begin (), end (), iterator (q, 0));
            allocator_.deallocate (start.p);
            start = iterator (q, 0);
            end_of_storage = q + (n + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        }
    }

    reference       front ()       { return *begin ();     }
    const_reference front () const { return *begin ();     }
    reference       back ()        { return * (end () - 1); }
    const_reference back ()  const { return * (end () - 1); }

    void push_back (const bool& x)
    {
        WRITE_LOCK(bv_mutex);
        if (finish.p != end_of_storage)
            *finish++ = x;
        else
            insert_aux (end (), x);
    }

#ifdef MSIPL_PARTIAL_TEMPL
    void swap (vector<bool, Allocator>& x)
#else
    void swap (vector<bool, DefAllocator<unsigned int> >& x)
#endif
    {
        WRITE_LOCK(bv_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (start, x.start);
        std::swap (finish, x.finish);
        std::swap (allocator_, x.allocator_);
        std::swap (end_of_storage, x.end_of_storage);
#else
        ::swap (start, x.start);
        ::swap (finish, x.finish);
        ::swap (allocator_, x.allocator_);
        ::swap (end_of_storage, x.end_of_storage);
#endif
    }

    iterator insert (iterator position, const bool& x = bool ())
    {
        WRITE_LOCK(bv_mutex);
        size_type n = position - begin ();
        if (finish.p != end_of_storage && position == end ())
            *finish++ = x;
        else
            insert_aux (position, x);
        return begin () + n;
    }
    inline
    void insert (iterator position, size_type n,
                 const bool& x);

    void pop_back () { WRITE_LOCK(bv_mutex); --finish; }
    iterator erase (iterator position)
    {
        WRITE_LOCK(bv_mutex);
        iterator ret_iter = begin ();
        difference_type len = 0;
        while (ret_iter != position) { ++len; ++ret_iter; }
        if (position + 1 != end ())
            copy (position + 1, end (), position);
        --finish;
        ret_iter = begin ();
        for (int i=0; i< len; ++i)  ++ret_iter;
        return ret_iter;
    }
    iterator erase (iterator first, iterator last)
    {
        WRITE_LOCK(bv_mutex);
        iterator ret_iter = begin ();
        difference_type len = 0;
        while (ret_iter != last) { ++len; ++ret_iter; }
        finish = copy (last, end (), first);
        ret_iter = begin ();
        for (int i = 0; i < len - (last-first); ++i) ++ret_iter;
        return ret_iter;

    }
    void clear () { erase (begin (), end ()); }
#ifdef MSIPL_PARTIAL_TEMPL
    static void swap (vector<bool, Allocator>::reference x,
                      vector<bool, Allocator>::reference y)
#else
    static void swap (vector<bool, DefAllocator<unsigned int> >::reference x,
                      vector<bool, DefAllocator<unsigned int> >::reference y)
#endif
    {
        bool tmp = x;
        x = y;
        y = tmp;
    }
    void flip()
    {
        WRITE_LOCK(bv_mutex);
        for (iterator i = begin(); i != end(); i++)
            (*i).flip();
    }
};

null_template
inline bool
#ifdef MSIPL_PARTIAL_TEMPL
operator== (const vector<bool, Allocator>& x,
            const vector<bool, Allocator>& y)
#else
operator== (const vector<bool, DefAllocator<unsigned int> >& x,
            const vector<bool, DefAllocator<unsigned int> >& y)
#endif
{
    return x.size () == y.size () &&
	   equal (x.begin (), x.end (), y.begin ());
}

null_template
inline bool
#ifdef MSIPL_PARTIAL_TEMPL
operator< (const vector<bool, Allocator>& x,
           const vector<bool, Allocator>& y)
#else
operator< (const vector<bool, DefAllocator<unsigned int> >& x,
           const vector<bool, DefAllocator<unsigned int> >& y)
#endif
{
    return lexicographical_compare (x.begin (), x.end (),
	   y.begin (), y.end ());
}

#ifdef MSIPL_PARTIAL_TEMPL
template <class Allocator>
inline void 
vector<bool, Allocator>::
#else
inline void 
vector<bool, DefAllocator<unsigned int> >::
#endif
insert_aux (iterator position, bool x)
{
    if (finish.p != end_of_storage)
    {
        copy_backward (position, finish - 1, finish);
        *position = x;
        ++finish;
    } else
    {
        size_type len = size () ? 2 * size () : MSIPL_WORD_BIT;
        unsigned int* q = bit_alloc (len);
        iterator i = copy (begin (), position, iterator (q, 0));
        *i++ = x;
        finish = copy (position, end (), i);
        allocator_.deallocate (start.p);
        end_of_storage = q + (len + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        start = iterator (q, 0);
    }
}

#ifdef MSIPL_PARTIAL_TEMPL
template <class Allocator>
inline void 
vector<bool, Allocator>::
#else
inline void 
vector<bool, DefAllocator<unsigned int> >::
#endif
insert (iterator position, size_type n, const bool& x)
{
    if (n == 0) return;
    WRITE_LOCK(bv_mutex);
    if (capacity () - size () >= n)
    {
        copy_backward (position, end (), finish + n);
        fill (position, position + n, x);
        finish += n;
    } else
    {
        size_type len = size () + max (size (), n);
        unsigned int* q = bit_alloc (len);
        iterator i = copy (begin (), position, iterator (q, 0));
        fill_n (i, n, x);
        finish = copy (position, end (), i + n);
        allocator_.deallocate (start.p);
        end_of_storage = q + (n + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        start = iterator (q, 0);
    }
}

#ifdef MSIPL_MEMBER_TEMPLATE
template <class InputIterator>
#ifdef MSIPL_PARTIAL_TEMPL
template <class Allocator>
inline void 
vector<bool, Allocator>::
#else
inline void 
vector<bool, DefAllocator<unsigned int> >::
#endif
insert (iterator position, InputIterator first, InputIterator last)
{
    if (first == last) return;
    size_type n = 0;
    n = distance (first, last);
    WRITE_LOCK(bv_mutex);
    if (capacity () - size () >= n)
    {
        copy_backward (position, end (), finish + n);
        copy (first, last, position);
        finish += n;
    } else
    {
        size_type len = size () + max (size (), n);
        unsigned int* q = bit_alloc (len);
        iterator i = copy (begin (), position, iterator (q, 0));
        i = copy (first, last, i);
        finish = copy (position, end (), i);
        allocator_.deallocate (start.p);
        end_of_storage = q + (len + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        start = iterator (q, 0);
    }
}
#else

#ifdef MSIPL_PARTIAL_TEMPL
template <class Allocator>
inline void
vector<bool, Allocator>::
#else
inline void
vector<bool, DefAllocator<unsigned int> >::
#endif
insert (iterator position, const_iterator first, const_iterator last)
{
    if (first == last) return;
    size_type n = 0;
    n = distance (first, last);
    WRITE_LOCK(bv_mutex);
    if (capacity () - size () >= n)
    {
        copy_backward (position, end (), finish + n);
        copy (first, last, position);
        finish += n;
    } else
    {
        size_type len = size () + max (size (), n);
        unsigned int* q = bit_alloc (len);
        iterator i = copy (begin (), position, iterator (q, 0));
        i = copy (first, last, i);
        finish = copy (position, end (), i);
        allocator_.deallocate (start.p);
        end_of_storage = q + (len + MSIPL_WORD_BIT - 1)/MSIPL_WORD_BIT;
        start = iterator (q, 0);
    }
}

#endif 

#undef MSIPL_WORD_BIT

#endif 
*/

#undef vector

#ifdef __MSL_NO_INSTANTIATE__
	template __dont_instantiate class vector<void*, allocator<void*> >;
	template __dont_instantiate class vector<long, allocator<long> >;
	template __dont_instantiate class vector<char, allocator<char> >;
#endif


#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_VECTOR_H */

//961205 bkoz line 634, 761 changed to global_iterator
//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory
//961223 bkoz line 323 added default argument to vector::insert();
// mm 970729   Corrected at function to throw out of range exception properly. [23.1.1] BW00200
