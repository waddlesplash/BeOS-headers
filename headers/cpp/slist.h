/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_SLIST_H
#define MSIPL_SLIST_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(algobase)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifndef slist
#define slist slist
#endif

// Singly-linked lists -- For Implementation Of Hash Tables

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Allocator = allocator<T> >
#else
template <class T, class Allocator>
#endif
class slist {
protected:

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<void>::other::pointer void_pointer;
#else
    typedef          DefAllocator<void>::pointer             void_pointer;
#endif

    struct slist_node;
    friend struct slist_node;

    struct slist_node {
        void_pointer next;
        T data;
    };

#ifdef MSIPL_MEMBER_TEMPLATE
    typename Allocator::rebind<slist_node>::other    slist_node_allocator;
#else
             DefAllocator<slist_node>                slist_node_allocator;
#endif

    Allocator                           value_allocator;

#ifdef MSIPL_MULTITHREAD
    static mutex_arith<bool, mutex>  separate_copying;
#else
    static bool                      separate_copying;
#endif

    DEC_OBJ_LOCK(_mutex)

public:      

    typedef          T                             value_type;
    typedef          Allocator                     allocator_type;
    typedef typename Allocator::pointer            pointer;
    typedef typename Allocator::reference          reference;
    typedef typename Allocator::const_reference    const_reference;

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<slist_node>::other  
                                                   slist_node_allocator_type;
#else
    typedef          DefAllocator<slist_node>      slist_node_allocator_type;
#endif

    typedef typename slist_node_allocator_type::pointer         link_type;
    typedef typename slist_node_allocator_type::size_type       size_type;
    typedef typename slist_node_allocator_type::difference_type difference_type;

protected:

    size_type buffer_size ()
    {
        return slist_node_allocator.init_page_size ();
    }

    struct slist_node_buffer;
    friend struct slist_node_buffer;

    struct slist_node_buffer {
        void_pointer next_buffer;
        link_type buffer;
    };

public:

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<slist_node_buffer>::other	buffer_allocator_type;
#else
    typedef          DefAllocator<slist_node_buffer>     buffer_allocator_type;
#endif

    typedef typename buffer_allocator_type::pointer buffer_pointer;     

protected:

    buffer_allocator_type           buffer_allocator;
    buffer_pointer                  buffer_slist;
    link_type                       free_slist;
    link_type                       next_avail;
    link_type                       last;

    void add_new_buffer ()
    {
        buffer_pointer tmp = buffer_allocator.allocate ((size_type)1);
        tmp->buffer = slist_node_allocator.allocate (buffer_size ());
        tmp->next_buffer = buffer_slist;
        buffer_slist = tmp;
        next_avail = buffer_slist->buffer;
        last = next_avail + buffer_size ();
    }

    void deallocate_buffers ();

    link_type get_node ()
    {
        link_type tmp = free_slist;
        return free_slist ? (free_slist = (link_type) (free_slist->next), tmp) 
            : (next_avail == last ? (add_new_buffer (), next_avail++) 
                : next_avail++);
        // ugly code for inlining - avoids multiple returns
    }

    void put_node (link_type p)
    {
        p->next = free_slist;
        free_slist = p;
    }

protected:

    link_type node;

public:

    class iterator;
    class const_iterator;

    class iterator 
#ifdef MSIPL_USING_NAMESPACE
        : public std::iterator<forward_iterator_tag, T, difference_type> {
#else
       // : public ::iterator<forward_iterator_tag, T, difference_type>    {
        : public ::global_iterator<forward_iterator_tag, T, difference_type>    {
#endif

        friend class slist<T, Allocator>;
        friend class const_iterator;

    protected:

        link_type node;
        DEC_OBJ_LOCK(iter_mutex)

    public:
        iterator (link_type x) : node (x) {}
        iterator () {}

        ~iterator () { REMOVE(iter_mutex); }

        bool operator== (const iterator& x) const
          { READ_LOCK(iter_mutex); return node == x.node; }

        reference operator*() const 
          { READ_LOCK(iter_mutex); return (*node).data; }

        // Waiting for clarifications on this
        // pointer operator-> () const { return & (operator* ()); }
 
        iterator& operator++ ()
        { 
            WRITE_LOCK(iter_mutex);
            node = (link_type) ((*node).next);
            return *this;
        }
        iterator operator++ (int)
        { 
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
    };
    class const_iterator 
#ifdef MSIPL_USING_NAMESPACE
        : public std::iterator<forward_iterator_tag, T, difference_type> {
#else
        //: public ::iterator<forward_iterator_tag, T, difference_type>    {
        : public ::global_iterator<forward_iterator_tag, T, difference_type>    {
#endif

        friend class slist<T, Allocator>;

    protected:

        link_type node;
        DEC_OBJ_LOCK(citer_mutex)

    public:     

        const_iterator (link_type x) : node (x) {}
        const_iterator () {}
        const_iterator (const iterator& x) : node (x.node) {}

        ~const_iterator () { REMOVE(citer_mutex); }


        bool operator== (const const_iterator& x) const
          { READ_LOCK(citer_mutex); return node == x.node; } 

        const_reference operator*() const 
          { READ_LOCK(citer_mutex); return (*node).data; }

        // Waiting for clarifications on this
        // const_pointer operator-> () const { return & (operator* ()); }
 
        const_iterator& operator++ ()
        { 
            WRITE_LOCK(citer_mutex);
            node = (link_type) ((*node).next);
            return *this;
        }
        const_iterator operator++ (int)
        { 
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
    };

    //
    // Copy control
    //
    static void separate_copy (bool option = true)
    {
        separate_copying = option;
    }

    //
    // Constructors and destructor
    //
    slist (const Allocator& alloc = Allocator ())
    : value_allocator(alloc), free_slist (0), buffer_slist (0),
      next_avail (0), last (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , slist_node_allocator(alloc), buffer_allocator(alloc)
#endif
    {
        node = get_node ();
        (*node).next = NULL;
    }
    slist (size_type n, const T& value = T (),
           const Allocator& alloc = Allocator ())
    : value_allocator(alloc), free_slist (0), buffer_slist (0),
      next_avail (0), last (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , slist_node_allocator(alloc), buffer_allocator(alloc)
#endif
    {
        node = get_node ();
        (*node).next = NULL;
        insert (iterator (node), begin (), n, value);
    }
    slist (const T* first, const T* last,
           const Allocator& alloc = Allocator ())
    : value_allocator(alloc), free_slist (0), buffer_slist (0),
      next_avail (0), last (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , slist_node_allocator(alloc), buffer_allocator(alloc)
#endif
    {
        node = get_node ();
        (*node).next = NULL;
        insert (iterator (node), begin (), first, last);
    }
    slist (const slist<T, Allocator>& x)
    : value_allocator(x.value_allocator), free_slist (0),
      buffer_slist (0), next_avail (0), last (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , slist_node_allocator(x.slist_node_allocator),
        buffer_allocator(x.buffer_allocator)
#endif
    {
        if (separate_copying)
        {
           node = get_node ();
          (*node).next = NULL;
           insert (iterator (node), begin (), x.begin (), x.end ());
        } else 
           node = x.node;
    }
    ~slist ()
    {
        if (separate_copying)
        {
            erase (begin (), end ());
            put_node (node);
            deallocate_buffers ();
        }
        REMOVE(_mutex);
    }

    friend void destroy (slist<T, Allocator>* p); /* { p->~slist (); } */

    //
    // Assignment operator
    //
    slist<T, Allocator>& operator= (const slist<T, Allocator>& x);

    //
    // Accessors
    //
    iterator       begin ()       
      { READ_LOCK(_mutex); return (link_type) ((*node).next); }
    const_iterator begin () const 
      { READ_LOCK(_mutex); return (link_type) ((*node).next); }
    iterator       end ()         { return NULL; }
    const_iterator end ()   const { return NULL; }
    bool           empty () const { return begin () == end (); }

    size_type size () const
    {
        size_type n = 0;
        for (const_iterator p = begin (); p != end (); ++p) ++n;
        return n;
    }

    size_type max_size () const
    { return slist_node_allocator.max_size (); }

    reference       front ()       { return *begin (); }
    const_reference front () const { return *begin (); }

    //
    // Modifiers
    //
    void swap (slist<T, Allocator>& x)
    {
        WRITE_LOCK(_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (node, x.node);
        std::swap (value_allocator, x.value_allocator);
        std::swap (buffer_allocator, x.buffer_allocator);
        std::swap (buffer_slist, x.buffer_slist);
        std::swap (free_slist, x.free_slist);
        std::swap (next_avail, x.next_avail);
        std::swap (last, x.last);
#else
        ::swap (node, x.node);
        ::swap (value_allocator, x.value_allocator);
        ::swap (buffer_allocator, x.buffer_allocator);
        ::swap (buffer_slist, x.buffer_slist);
        ::swap (free_slist, x.free_slist);
        ::swap (next_avail, x.next_avail);
        ::swap (last, x.last);
#endif
    }
    iterator
    insert (iterator previous, iterator position, const T& x)
    {
        WRITE_LOCK(_mutex);
        link_type tmp = get_node ();
        construct (value_allocator.address ((*tmp).data), x);
       (*tmp).next = position.node;
        (* (link_type (previous.node))).next = tmp;
        return tmp;
    }
    void insert (iterator previous, iterator position,
                size_type n, const T& x = T ());
    void insert (iterator previous, iterator position, 
                const T* first, const T* last);
    void insert (iterator previous, iterator position, 
                const_iterator first, const_iterator last);

    void push_front (const T& x)
    { insert (iterator (node), begin (), x); }

    iterator erase (iterator position)
    {
        WRITE_LOCK(_mutex);
        iterator iter;
        if (position != end ())
            iter = (link_type)(*position.node).next;
        else
            iter = end ();
        iterator previous (node);
        for (iterator p = begin (); p != position; ++p)
            previous = p;
       (*previous.node).next = (*position.node).next;
        destroy (value_allocator.address ((*position.node).data));
        put_node (position.node);
        return iter;
    }
    iterator erase (iterator first, iterator last);

    void pop_front () { erase (begin ()); }

    void splice (iterator previous, iterator position, slist<T, Allocator>& x, 
                iterator first, iterator last)
    {
        if (first != last)
        {
            WRITE_LOCK(_mutex);
            iterator prev1 (x.node);
            iterator p = x.begin ();
            for (; p != first; ++p)
               prev1 = p;
            iterator prev2 = prev1;
            for ( ; p != last; ++p)
               prev2 = p;
           (*previous.node).next = first.node;
           (*prev1.node).next = (*prev2.node).next;
           (*prev2.node).next = position.node;
        }
    }
    void splice (iterator previous, iterator position, slist<T, Allocator>& x)
    {
        if (!x.empty ())
        {
            splice (previous, position, x, x.begin (), x.end ());
        }
    }
    void splice (iterator previous, iterator position, 
                slist<T, Allocator>& x, iterator i)
    {
        iterator j = i;
        splice (previous, position, x, i, ++j);
    }
    void splice (slist<T, Allocator>& x)
    {
        splice (iterator (node), begin (), x, x.begin (), x.end ());
    }
    void splice (slist<T, Allocator>& x, iterator i)
    {
        iterator j = i;
        splice (iterator (node), begin (), x, i, ++j);
    }

/*
    void remove (const T& value);
    void unique ();
    void merge (slist<T, Allocator>& x);
    void reverse ();
    void sort ();
*/
};

#ifdef MSIPL_MULTITHREAD
template <class T, class Allocator>
mutex_arith<bool, mutex> slist<T, Allocator>::separate_copying = false;
#else
template <class T, class Allocator>
bool slist<T, Allocator>::separate_copying = false;
#endif

template <class T, class Allocator>
inline bool 
operator== (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{
    return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ());
}

template <class T, class Allocator>
inline bool 
operator< (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::deallocate_buffers ()
{
    while (buffer_slist)
    {
        buffer_pointer tmp = buffer_slist;
        buffer_slist = (buffer_pointer) (buffer_slist->next_buffer);
        slist_node_allocator.deallocate (tmp->buffer);
        buffer_allocator.deallocate (tmp);
    }
    free_slist = 0;
    next_avail = 0;
    last = 0;
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::insert (iterator previous, iterator position, 
                       const T* first, const T* last)
{
    while (first != last)
    {
        insert (previous, position, *first++);
        ++previous;
    }
}
         
template <class T, class Allocator>
inline
void slist<T, Allocator>::insert (iterator previous, iterator position, 
                       const_iterator first, const_iterator last)
{
    while (first != last)
    {
        insert (previous, position, *first++);
        ++previous;
    }
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::insert (iterator previous, iterator position, 
                       size_type n, const T& x)
{
    while (n--)
    {
        insert (previous, position, x);
        ++previous;
    }
}

template <class T, class Allocator>
inline
slist<T, Allocator>::iterator 
slist<T, Allocator>::erase (iterator first, iterator last)
{
    while (first != last) erase (first++);
    return last;
}

template <class T, class Allocator>
inline
slist<T, Allocator>& 
slist<T, Allocator>::operator= (const slist<T, Allocator>& x)
{
    if (this != &x)
    {
        erase (begin (), end ());
        insert (iterator (node), begin (), x.begin (), x.end ());
    }
    return *this;
}

/*
template <class T, class Allocator>
inline
void slist<T, Allocator>::remove (const T& value)
{
    iterator first = begin ();
    iterator last = end ();
    while (first != last)
    {
        iterator next = first;
        ++next;
        if (*first == value) erase (first);
        first = next;
    }
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::unique ()
{
    iterator first = begin ();
    iterator last = end ();
    if (first == last) return;
    iterator next = first;
    while (++next != last)
    {
        if (*first == *next)
            erase (next);
        else
            first = next;
        next = first;
    }
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::merge (slist<T, Allocator>& x)
{
    iterator first1 = begin ();
    iterator last1 = end ();
    iterator first2 = x.begin ();
    iterator last2 = x.end ();
    while (first1 != last1 && first2 != last2)
        if (*first2 < *first1)
        {
            iterator next = first2;
            transfer (first1, first2, ++next);
            first2 = next;
        } else
            first1++;
    if (first2 != last2) transfer (last1, first2, last2);
    length += x.length;
    x.length= 0;
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::reverse ()
{
    if (size () < 2) return;
    for (iterator first = ++begin (); first != end ();)
    {
        iterator old = first++;
        transfer (begin (), old, first);
    }
}    

template <class T, class Allocator>
inline
void slist<T, Allocator>::sort ()
{
    if (size () < 2) return;
    slist<T, Allocator> carry;
    slist<T, Allocator> counter[64];
    int fill = 0;
    while (!empty ())
    {
        carry.splice (carry.begin (), *this, begin ());
        int i = 0;
        while (i < fill && !counter[i].empty ())
        {
            counter[i].merge (carry);
            carry.swap (counter[i++]);
        }
        carry.swap (counter[i]);         
        if (i == fill) ++fill;
    } 
    while (fill--) merge (counter[fill]);
}
*/

#undef slist

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_SLIST_H */

//961120 bkoz line 158 202 changed iterator to global_iterator
//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory