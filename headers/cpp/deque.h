/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_DEQUE_H
#define MSIPL_DEQUE_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(algobase)

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

#ifndef deque 
#define deque deque
#endif

//
// Subclause 23.2.2
//
#ifdef MSIPL_DEF_TEMPARG
template <class T, class Allocator = allocator<T> > 
#else
template <class T, class Allocator> 
#endif
class deque {
public:
    class        iterator;
    class        const_iterator;
    friend class iterator;
    friend class const_iterator;

    typedef          T                             value_type;
    typedef          Allocator                     allocator_type;
    typedef typename Allocator::pointer            pointer;
    typedef typename Allocator::const_pointer      const_pointer;
    typedef typename Allocator::reference          reference;
    typedef typename Allocator::const_reference    const_reference;
    typedef typename Allocator::size_type          size_type;
    typedef typename Allocator::difference_type    difference_type;

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<pointer>::other  map_allocator_type;   
#else
    typedef          DefAllocator<pointer>              map_allocator_type;   
#endif

protected:

    allocator_type                        data_allocator;
    static size_type                      buffer_size;
    map_allocator_type                    map_allocator;

    typedef typename map_allocator_type::pointer   map_pointer;

public:

    class iterator 
#ifdef MSIPL_USING_NAMESPACE
     : public std::iterator<random_access_iterator_tag, T, difference_type>
#else
     : public ::global_iterator<random_access_iterator_tag, T, difference_type>
#endif
    {
        friend class deque<T, Allocator>;
        friend class const_iterator;
        friend iterator operator+ (difference_type n, iterator iter) 
        {
            // deque<T, Allocator>::iterator tmp = iter;	//  971015 vss
            iterator tmp = iter;							//  971015 vss
            return tmp += n;
        }

    protected:

        pointer current;
        pointer first;
        pointer last;
        map_pointer node;

        DEC_OBJ_LOCK(iter_mutex)

        iterator (pointer x, map_pointer y) 
            : current (x), first (*y), last (*y + buffer_size), node (y) {}

    public:

        iterator ()
        : current (0), first (0), last (0), node (0) {}

        reference operator*() const { READ_LOCK(iter_mutex); return *current; }

        // Waiting for clarifications on this
        // pointer operator-> () const { return &(operator* ()); }
 
        difference_type operator- (const iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return node == x.node 
                ? current - x.current 
                : difference_type (buffer_size * (node - x.node - 1) +
                    (current - first) + (x.last - x.current));
        }
        difference_type operator- (const const_iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return node == x.node 
                ? current - x.current 
                : difference_type (buffer_size * (node - x.node - 1) +
                    (current - first) + (x.last - x.current));
        }
        iterator& operator++ ()
        {
            WRITE_LOCK(iter_mutex);
            if (++current == last)
            {
                first = *(++node);
                current = first;
                last = first + buffer_size;
            }
            return *this; 
        }
        iterator operator++ (int) 
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        iterator& operator-- ()
        {
            WRITE_LOCK(iter_mutex);
            if (current == first)
            {
                first = *(--node);
                last = first + buffer_size;
                current = last;
            }
            --current;
            return *this;
        }
        iterator operator-- (int)
        {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
        iterator& operator+= (difference_type n)
        {
            WRITE_LOCK(iter_mutex);
            difference_type offset = n + (current - first);
            difference_type num_node_to_jump = offset >= 0
                ? offset / buffer_size
                : - ((-offset + buffer_size - 1) / buffer_size);
            if (num_node_to_jump == 0)
                current += n;
            else
            {
                node = node + num_node_to_jump;
                first = *node;
                last = first + buffer_size;
                current = first + (offset - num_node_to_jump * buffer_size);
            }
            return *this;
        }
        iterator& operator-= (difference_type n) { return *this += -n; }
        iterator operator+ (difference_type n) const
        {
            iterator tmp = *this;
            return tmp += n;
        }
        iterator operator- (difference_type n) const
        {
            iterator tmp = *this;
            return tmp -= n;
        }
        reference operator[] (difference_type n) { return * (*this + n); }
        bool operator== (const iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return current == x.current || 
                ((current == first || x.current == x.first) && 
                 *this - x == 0);
        }
        bool operator== (const const_iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return current == x.current || 
                ((current == first || x.current == x.first) && 
                 *this - x == 0);
        }
        bool operator!= (const iterator& x) const
        {
            return !(*this == x);
        }
        bool operator!= (const const_iterator& x) const
        {
            return !(*this == x);
        }
        bool operator< (const iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return (node == x.node) ? (current < x.current) 
                                    : (node < x.node);
        }
        bool operator< (const const_iterator& x) const
        {
            READ_LOCK(iter_mutex);
            return (node == x.node) ? (current < x.current) 
                                    : (node < x.node);
        }
    };
    class const_iterator 
#ifdef MSIPL_USING_NAMESPACE
     : public std::iterator<random_access_iterator_tag, T, difference_type>
#else
     : public ::global_iterator<random_access_iterator_tag, T, difference_type>
#endif
    {

    friend class deque<T, Allocator>;
    friend class iterator;

    friend const_iterator operator+ (difference_type n,
                                     const_iterator iter) 
    {
        //  deque<T, Allocator>::const_iterator tmp = iter;		//  971015 vss
        const_iterator tmp = iter;								//  971015 vss
        return tmp += n;
    }

    protected:
        pointer current;
        pointer first;
        pointer last;
        map_pointer node;

        DEC_OBJ_LOCK(citer_mutex)

        const_iterator (pointer x, map_pointer y) 
        : current (x), first (*y), last (*y + buffer_size), node (y) {}
    public:
        const_iterator ()
        : current (0), first (0), last (0), node (0) {}

        const_iterator (const iterator& x) 
        : current (x.current), first (x.first), last (x.last), node (x.node) {}     
        const_reference operator*() const 
        { 
            READ_LOCK(citer_mutex);
            return *current;
         }

        // Waiting for clarifications on this
        // const_pointer operator-> () const { return &(operator* ()); }

        difference_type operator- (const const_iterator& x) const
        {
            READ_LOCK(citer_mutex);
            return node == x.node 
                ? current - x.current 
                : difference_type (buffer_size * (node - x.node - 1) +
                           (current - first) + (x.last - x.current));
        }
        const_iterator& operator++ ()
        {
            WRITE_LOCK(citer_mutex);
            if (++current == last)
            {
                first = *(++node);
                current = first;
                last = first + buffer_size;
            }
            return *this; 
        }
        const_iterator operator++ (int)
        {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
        const_iterator& operator-- ()
        {
            WRITE_LOCK(citer_mutex);
            if (current == first)
            {
                first = *(--node);
                last = first + buffer_size;
                current = last;
            }
            --current;
            return *this;
        }
        const_iterator operator-- (int)
        {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }
        const_iterator& operator+= (difference_type n)
        {
            WRITE_LOCK(citer_mutex);
            difference_type offset = n + (current - first);
            difference_type num_node_to_jump = offset >= 0
                ? offset / buffer_size
                : - ((-offset + buffer_size - 1) / buffer_size);
            if (num_node_to_jump == 0)
                current += n;
            else
            {
                node = node + num_node_to_jump;
                first = *node;
                last = first + buffer_size;
                current = first + (offset - num_node_to_jump * buffer_size);
            }
            return *this;
        }
        const_iterator&
        operator-= (difference_type n) { return *this += -n; }

        const_iterator operator+ (difference_type n) const
        {
            const_iterator tmp = *this;
            return tmp += n;
        }
        const_iterator operator- (difference_type n) const
        {
            const_iterator tmp = *this;
            return tmp -= n;
        }
        const_reference operator[] (difference_type n) const
        {
            return *(*this + n); 
        }
        bool operator== (const const_iterator& x) const
        {
            READ_LOCK(citer_mutex);
            return current == x.current || 
                ((current == first || x.current == x.first) && 
                 *this - x == 0);
        }
        bool operator!= (const const_iterator& x) const
        {
            return !(*this == x);
        }
        bool operator< (const const_iterator& x) const
        {
            READ_LOCK(citer_mutex);
            return (node == x.node) ? (current < x.current) 
                                    : (node < x.node);
        }
    };

    typedef reverse_iterator<const_iterator, value_type, const_reference, 
                             const_pointer, difference_type> 
    const_reverse_iterator;

    typedef reverse_iterator<iterator, value_type, reference,
                             pointer, difference_type>
    reverse_iterator; 

protected:    

    iterator        start;
    iterator        finish;
    size_type       length;
    map_pointer     map;
    size_type       map_size;

    DEC_OBJ_LOCK(dq_mutex)

    void allocate_at_begin  ();
    void allocate_at_end    ();
    void deallocate_at_begin ();
    void deallocate_at_end  ();

public:

    //
    // 23.2.2.2   construct/copy/destroy
    //
    explicit
    deque (const Allocator& alloc = Allocator()) 
    : data_allocator(alloc), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(alloc)
#endif
    {
        buffer_size = data_allocator.init_page_size ();
    }

    explicit
    deque (size_type n, const T& value = T (),
           const Allocator& alloc = Allocator ())
    : data_allocator(alloc), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(alloc)
#endif
    {
        buffer_size = data_allocator.init_page_size ();  
        insert (begin (), n, value);
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class Iterator>
    deque (Iterator first, Iterator last,
           const Allocator& alloc = Allocator())
    : data_allocator(alloc), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(alloc)
#endif
    {
        buffer_size = data_allocator.init_page_size ();  
        copy (first, last, back_inserter (*this));
    }
#else
    deque (const_iterator first, const_iterator last,
           const Allocator& alloc = Allocator())
    : data_allocator(alloc), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(alloc)
#endif
    {
        buffer_size = data_allocator.init_page_size ();  
        copy (first, last, back_inserter (*this));
    }
    deque (const T* first, const T* last,
           const Allocator& alloc = Allocator())
    : data_allocator(alloc), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(alloc)
#endif
    {
        buffer_size = data_allocator.init_page_size ();  
        copy (first, last, back_inserter (*this));
    }
#endif

    deque (const deque<T, Allocator>& x)
    : data_allocator(x.data_allocator), start (), finish (),
      length (0), map (0), map_size (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , map_allocator(x.map_allocator)
#endif
    {
        buffer_size = data_allocator.init_page_size ();  
        copy (x.begin (), x.end (), back_inserter (*this));
    }

    deque<T, Allocator>& operator= (const deque<T, Allocator>& x)
    {
        if (this != &x)
        {
            WRITE_LOCK(dq_mutex);
            if (size () >= x.size ()) 
                erase (copy (x.begin (), x.end (), begin ()), end ());
            else 
                copy (x.begin () + size (), x.end (),
                     inserter (*this, copy (x.begin (), x.begin () + size (),
                                          begin ())));
        }
        return *this;
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template<class InputIterator>
    void assign (InputIterator first, InputIterator last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }

    template <class Size, class Type>
#ifdef MSIPL_TFN_DEFARG
    void assign (Size n, const Type& t = Type())
#else
    void assign (Size n, const Type& t)
#endif
    {
       erase (begin (), end ());
       insert (begin (), n, t);
    }

#else
    void assign (const_iterator first, const_iterator last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }
    void assign (const T* first, const T* last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }
    void assign (size_type n, const T& t = T ())
    {
       erase (begin (), end ());
       insert (begin (), n, t);
    }
#endif

    allocator_type get_allocator () const
    {
        return data_allocator;
    }

    ~deque ();

    //
    // 23.2.2.3   iterators:
    //
    iterator begin ()       
    { 
        READ_LOCK(dq_mutex);
        return start;
    }
    const_iterator begin () const 
    { 
        READ_LOCK(dq_mutex);
        return start;
    }
    iterator end ()         
    { 
        READ_LOCK(dq_mutex);
        return finish;
    }
    const_iterator end () const  
    { 
        READ_LOCK(dq_mutex);
        return finish;
    }

    reverse_iterator         rbegin () { return reverse_iterator (end ()); }
    const_reverse_iterator   rbegin () const
    { 
        return const_reverse_iterator (end ()); 
    }
    reverse_iterator         rend () { return reverse_iterator (begin ()); }
    const_reverse_iterator   rend () const
    { 
        return const_reverse_iterator (begin ()); 
    } 

    //
    // 23.2.2.4  capacity:
    //
    size_type   size ()      const { READ_LOCK(dq_mutex); return length; }
    size_type   max_size ()  const 
    { 
        return data_allocator.max_size (); 
    }

    void resize (size_type sz, T v = T ())
    {
        if (sz > size ())
           insert (end (), sz-size (), v);
        else if (sz < size ())
           erase (begin ()+sz, end ());
    }

    bool        empty ()     const 
    { 
        READ_LOCK(dq_mutex);
        return length == 0; 
    }

    //
    // 23.2.2.5 element access:
    //
    reference operator[] (size_type n)
    { 
        return * (begin () + n); 
    }

    const_reference operator[] (size_type n) const 
    {
        return * (begin () + n); 
    }

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

    reference          front ()       { return *begin ();      }
    const_reference    front () const { return *begin ();      }
    reference          back ()        { return * (end () - 1); }
    const_reference    back () const  { return * (end () - 1); }

    //
    // 23.2.2.6  modifiers:
    //
    void push_front (const T& x) 
    {
        WRITE_LOCK(dq_mutex);
        if (empty () || begin ().current == begin ().first)
            allocate_at_begin ();
        --start.current;
        construct (start.current, x);
        ++length;
        if (end ().current == end ().last) allocate_at_end ();
    }

    void push_back (const T& x)
    {
        WRITE_LOCK(dq_mutex);
        if (empty ()) allocate_at_end ();
        construct (finish.current, x);
        ++finish.current;
        ++length;
        if (end ().current == end ().last) allocate_at_end ();
    }

    iterator insert (iterator position, const T& x = T ());
    void     insert (iterator position, size_type n, const T& x);

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (iterator position,
                 InputIterator first, InputIterator last);
#else
    void insert (iterator position,
                const T* first, const T* last);

    void insert (iterator position,
                const_iterator first, const_iterator last);
#endif

    void pop_front ()
    {
        WRITE_LOCK(dq_mutex);
        destroy (start.current);
        ++start.current;
        --length; 
        if (empty () || begin ().current == begin ().last)
            deallocate_at_begin ();
    }

    void pop_back ()
    {
        WRITE_LOCK(dq_mutex);
        if (end ().current == end ().first) deallocate_at_end ();
        --finish.current;
        destroy (finish.current);
        --length; 
        if (empty ()) deallocate_at_end ();
    }

    iterator erase (iterator position);
    iterator erase (iterator first, iterator last);    

    void swap (deque<T, Allocator>& x)
    {
        WRITE_LOCK(dq_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (start, x.start);
        std::swap (finish, x.finish);
        std::swap (length, x.length);
        std::swap (map, x.map);
        std::swap (map_size, x.map_size);
        std::swap (data_allocator, x.data_allocator);
        std::swap (map_allocator, x.map_allocator);
#else
        ::swap (start, x.start);
        ::swap (finish, x.finish);
        ::swap (length, x.length);
        ::swap (map, x.map);
        ::swap (map_size, x.map_size);
        ::swap (data_allocator, x.data_allocator);
        ::swap (map_allocator, x.map_allocator);
#endif
    }

     void clear () { erase (begin (), end ()); }

};

template <class T, class Allocator>
deque<T, Allocator>::size_type deque<T, Allocator>::buffer_size =
       max (size_type (1), size_type (4096/sizeof (T)));
// const deque<T>::size_type deque<T>::buffer_size = 0; 
// should be data_allocator.init_page_size (); // Borland bug

template <class T, class Allocator>
inline
bool
operator== (const deque<T, Allocator>& x, const deque<T, Allocator>& y)
{
    return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ());
}

template <class T, class Allocator>
inline
bool
operator< (const deque<T, Allocator>& x, const deque<T, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

template <class T, class Allocator>
inline
deque<T, Allocator>::~deque () 
{ 
    while (!empty ()) pop_front (); 
    REMOVE(dq_mutex);
}     

template <class T, class Allocator>
inline
void deque<T, Allocator>::allocate_at_begin ()
{
    WRITE_LOCK(dq_mutex);
    pointer p = data_allocator.allocate (buffer_size);
    if (!empty ())
    {
        if (start.node == map)
        {
            difference_type i = finish.node - start.node;
            map_size = (i + 1) * 2;
            map_pointer tmp = map_allocator.allocate (map_size);
            copy (start.node, finish.node + 1, tmp + map_size / 4 + 1);
            map_allocator.deallocate (map);
            map = tmp;
            map[map_size / 4] = p;
            start = iterator (p + buffer_size, map + map_size / 4);
            finish = iterator (finish.current, map + map_size / 4 + i + 1);
        } else
        {
            *--start.node = p;
            start = iterator (p + buffer_size, start.node);
        }
    } else
    {
        map_size = map_allocator.init_page_size ();
        map = map_allocator.allocate (map_size);
        map[map_size / 2] = p;
        start = iterator (p + buffer_size / 2 + 1, map + map_size / 2);
        finish = start;
    }
}

template <class T, class Allocator>
inline
void deque<T, Allocator>::allocate_at_end ()
{
    WRITE_LOCK(dq_mutex);
    pointer p = data_allocator.allocate (buffer_size);
    if (!empty ())
    {
        if (finish.node == map + map_size - 1)
        {
            difference_type i = finish.node - start.node;
                 map_size = (i + 1) * 2;
            map_pointer tmp = map_allocator.allocate (map_size);
            copy (start.node, finish.node + 1, tmp + map_size / 4);
            map_allocator.deallocate (map);
            map = tmp;
                 map[map_size / 4 + i + 1] = p;
            start = iterator (start.current, map + map_size / 4);
            finish = iterator (p, map + map_size / 4 + i + 1);
        } else
       {
            *++finish.node = p;
            finish = iterator (p, finish.node);
        }
    } else
   {
        map_size = map_allocator.init_page_size ();
        map = map_allocator.allocate (map_size);
        map[map_size / 2] = p;
        start = iterator (p + buffer_size / 2, map + map_size / 2);
        finish = start;
    }
}

template <class T, class Allocator>
inline
void deque<T, Allocator>::deallocate_at_begin ()
{
    WRITE_LOCK(dq_mutex);
    data_allocator.deallocate (*start.node++);
    if (empty ())
    {
        if (finish.current == finish.first)
            data_allocator.deallocate (*start.node);
        start = iterator ();
        finish = start;
        map_allocator.deallocate (map);
    } else
        start = iterator (*start.node, start.node);
}

template <class T, class Allocator>
inline
void deque<T, Allocator>::deallocate_at_end ()
{
    WRITE_LOCK(dq_mutex);
    data_allocator.deallocate (*finish.node--);
    if (empty ())
    {
        start = iterator ();
        finish = start;
        map_allocator.deallocate (map);
    } else
        finish = iterator (*finish.node + buffer_size, finish.node);
}

template <class T, class Allocator>
inline
deque<T, Allocator>::iterator 
deque<T, Allocator>::insert (iterator position, const T& x)
{
    WRITE_LOCK(dq_mutex);
    if (position == begin ())
    {
        push_front (x);
        return begin ();
    } else if (position == end ())
    {
        push_back (x);
        return end () - 1;
    } else
    {
        difference_type index = position - begin ();
        if (index < length)
        {
            push_front (*begin ());
            copy (begin () + 2, begin () + index + 1, begin () + 1);
        } else
        {
            push_back (* (end () - 1));
            copy_backward (begin () + index, end () - 2, end () - 1);
        }
        * (begin () + index) = x;
        return begin () + index;
    }
}

template <class T, class Allocator>
inline
void deque<T, Allocator>::insert (iterator position, size_type n, const T& x)
{
    WRITE_LOCK(dq_mutex);
    difference_type index = position - begin ();
    difference_type remainder = length - index;
    if (remainder > index)
    {
        if (n > index)
        {
            difference_type m = n - index;
            while (m-- > 0) push_front (x);
            difference_type i = index;
            while (i--) push_front (* (begin () + n - 1));
            fill (begin () + n, begin () + n + index, x);
        } else
        {
            difference_type i = n;
            while (i--) push_front (* (begin () + n - 1));
            copy (begin () + n + n, begin () + n + index, begin () + n);
            fill (begin () + index, begin () + n + index, x);
        }
    } else
    {
        difference_type orig_len = index + remainder;
        if (n > remainder)
        {
            difference_type m = n - remainder;
            while (m-- > 0) push_back (x);
            difference_type i = 0;
            while (i < remainder) push_back (* (begin () + index + i++));
            fill (begin () + index, begin () + orig_len, x);
        } else
        {
            difference_type i = 0;
            while (i < n) push_back (* (begin () + orig_len - n + i++));
            copy_backward (begin () + index, begin () + orig_len - n,
                          begin () + orig_len);
            fill (begin () + index, begin () + index + n, x);
        }
    }
}

#ifdef MSIPL_MEMBER_TEMPLATE
template <class T, class Allocator>
template <class InputIterator>
inline
void deque<T, Allocator>::insert (iterator position,
                       InputIterator first, InputIterator last)
{
    WRITE_LOCK(dq_mutex);
    difference_type index = position - begin ();
    difference_type remainder = length - index;
    size_type n = distance (first, last);
    if (remainder > index)
    {
        if (n > index)
        {
            InputIterator m = last - index;
            while (m != first) push_front (*--m);
            difference_type i = index;
            while (i--) push_front (* (begin () + n - 1));
            copy (last - index, last, begin () + n);
        } else
        {
            difference_type i = n;
            while (i--) push_front (* (begin () + n - 1));
            copy (begin () + n + n, begin () + n + index, begin () + n);
            copy (first, last, begin () + index);
        }
    } else
    {
        difference_type orig_len = index + remainder;
        if (n > remainder)
        {
            InputIterator m = first + remainder;
            while (m != last) push_back (*m++);
            difference_type i = 0;
            while (i < remainder) push_back (* (begin () + index + i++));
            copy (first, first + remainder, begin () + index);
        } else
        {
            difference_type i = 0;
            while (i < n) push_back (* (begin () + orig_len - n + i++));
            copy_backward (begin () + index, begin () + orig_len - n,
                          begin () + orig_len);
            copy (first, last, begin () + index);
        }
    }
}
#else
template <class T, class Allocator>
inline
void deque<T, Allocator>::insert (iterator position,
                                  const T* first, const T* last)
{
    WRITE_LOCK(dq_mutex);
    difference_type index = position - begin ();
    difference_type remainder = length - index;
    size_type n = distance (first, last);
    if (remainder > index)
    {
        if (n > index)
        {
            const T* m = last - index;
            while (m != first) push_front (*--m);
            difference_type i = index;
            while (i--) push_front (* (begin () + n - 1));
            copy (last - index, last, begin () + n);
        } else
        {
            difference_type i = n;
            while (i--) push_front (* (begin () + n - 1));
            copy (begin () + n + n, begin () + n + index, begin () + n);
            copy (first, last, begin () + index);
        }
    } else
    {
        difference_type orig_len = index + remainder;
        if (n > remainder)
        {
            const T* m = first + remainder;
            while (m != last) push_back (*m++);
            difference_type i = 0;
            while (i < remainder) push_back (* (begin () + index + i++));
            copy (first, first + remainder, begin () + index);
        } else
        {
            difference_type i = 0;
            while (i < n) push_back (* (begin () + orig_len - n + i++));
            copy_backward (begin () + index, begin () + orig_len - n,
                          begin () + orig_len);
            copy (first, last, begin () + index);
        }
    }
}

template <class T, class Allocator>
inline
void
deque<T, Allocator>::insert (iterator position,
                  const_iterator first, const_iterator last)
{
    WRITE_LOCK(dq_mutex);
    difference_type index = position - begin ();
    difference_type remainder = length - index;
    size_type n = distance (first, last);
    if (remainder > index)
    {
        if (n > index)
        {
            const_iterator  m = last - index;
            while (m != first) push_front (*--m);
            difference_type i = index;
            while (i--) push_front (* (begin () + n - 1));
            copy (last - index, last, begin () + n);
        } else
        {
            difference_type i = n;
            while (i--) push_front (* (begin () + n - 1));
            copy (begin () + n + n, begin () + n + index, begin () + n);
            copy (first, last, begin () + index);
        }
    } else
    {
        difference_type orig_len = index + remainder;
        if (n > remainder)
        {
            const_iterator m = first + remainder;
            while (m != last) push_back (*m++);
            difference_type i = 0;
            while (i < remainder) push_back (* (begin () + index + i++));
            copy (first, first + remainder, begin () + index);
        } else
        {
            difference_type i = 0;
            while (i < n) push_back (* (begin () + orig_len - n + i++));
            copy_backward (begin () + index, begin () + orig_len - n,
                          begin () + orig_len);
            copy (first, last, begin () + index);
        }
    }
}
#endif

template <class T, class Allocator>
inline
deque<T, Allocator>::iterator 
deque<T, Allocator>::erase (iterator position)
{
    WRITE_LOCK(dq_mutex);
    deque<T, Allocator>::iterator iter;
    if ( position != end() )
        iter = position + 1;
    else
        iter = end ();

    if (end () - position > position - begin ())
    {
        copy_backward (begin (), position, position + 1);
        pop_front ();
    } else
    {
        copy (position + 1, end (), position);
        pop_back ();
    }
    return iter;
}
 
template <class T, class Allocator>
inline
deque<T, Allocator>::iterator 
deque<T, Allocator>::erase (iterator first, iterator last)
{
    deque<T, Allocator>::iterator iter = last;

    difference_type n = last - first;
    WRITE_LOCK(dq_mutex);
    if (end () - last > first - begin ())
    {
        copy_backward (begin (), first, last);
        while (n-- > 0) pop_front ();
    } else
    {
        copy (last, end (), first);
        while (n-- > 0) pop_back ();
    }
    return iter;
}

#undef deque

#ifdef __MSL_NO_INSTANTIATE__
	template __dont_instantiate class deque<int, allocator<int> >;
	template __dont_instantiate class deque<char, allocator<char> >;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_DEQUE_H */

//961120 bkoz line 74, 227 iterator to global_iterator change
//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory
//971015 vss don't need to scope inside nested template
