/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/
 
#ifndef MSIPL_LIST_H
#define MSIPL_LIST_H
 
#include <mcompile.h>
 
#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(algobase)
 

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#else 
#define std
#endif

#ifdef MSIPL_DEF_TEMPARG
template <class T, class Allocator = allocator<T> >
#else
template <class T, class Allocator>
#endif
class list {
protected:

#ifdef MSIPL_MEMBER_TEMPLATE
   typedef typename Allocator::rebind<void>::other::pointer void_pointer;
#else
   typedef          DefAllocator<void>::pointer             void_pointer;
#endif

   struct list_node {
      void_pointer next;
      void_pointer prev;
      T data;
   };

#ifdef MSIPL_MEMBER_TEMPLATE
   typename Allocator::rebind<list_node>::other  list_node_allocator;
#else
             DefAllocator<list_node>              list_node_allocator;
#endif
 
   Allocator                 value_allocator;

public:

   typedef          T                            value_type;
   typedef          Allocator                    allocator_type;
   typedef typename Allocator::pointer           pointer;
   typedef typename Allocator::const_pointer     const_pointer;
   typedef typename Allocator::reference         reference;
   typedef typename Allocator::const_reference   const_reference;
 
#ifdef MSIPL_MEMBER_TEMPLATE
   typedef typename Allocator::rebind<list_node>::other
                                                    list_node_allocator_type;
#else
   typedef          DefAllocator<list_node>        list_node_allocator_type;
#endif


   typedef typename list_node_allocator_type::pointer         link_type;
   typedef typename list_node_allocator_type::size_type       size_type;
   typedef typename list_node_allocator_type::difference_type difference_type;

protected:

   link_type head;
   size_type length;
   link_type cache;

   DEC_OBJ_LOCK(lst_mutex)

   link_type get_node ()
   {
      WRITE_LOCK(lst_mutex);
      link_type tmp = cache;
      if (cache)  
         cache = (link_type)cache->next;
      else
         tmp =  list_node_allocator.allocate ((size_type)1);
      tmp->next = tmp->prev = tmp;
      return tmp;
   }

public:

    class const_iterator;
    class iterator
		#ifdef MSIPL_USING_NAMESPACE
		    : public std::iterator<bidirectional_iterator_tag, T, difference_type> 
		#else
		    : public ::global_iterator<bidirectional_iterator_tag, T, difference_type>
		#endif

    {
        friend class list<T, Allocator>;
        friend class const_iterator;
 
    protected:
 
        link_type node;

        DEC_OBJ_LOCK(iter_mutex)
 
        iterator (link_type x) : node (x) {}
    public:
        iterator () {}
 
        ~iterator () { REMOVE(iter_mutex); }
 
        bool operator== (const iterator& x) const
        { READ_LOCK(iter_mutex); return node == x.node; }
 
        bool operator== (const const_iterator& x) const
        { READ_LOCK(iter_mutex); return node == x.node; }
 
        bool operator!= (const iterator& x) const
        { READ_LOCK(iter_mutex); return node != x.node; }
 
        bool operator!= (const const_iterator& x) const
        { READ_LOCK(iter_mutex); return node != x.node; }
 
        reference operator*() const
        {
            READ_LOCK(iter_mutex);
            return (*node).data;
        }

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
        iterator& operator-- ()
        {
            WRITE_LOCK(iter_mutex);
            node = (link_type) ((*node).prev);
            return *this;
        }
        iterator operator-- (int)
        {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
    };
    class const_iterator
    #ifdef MSIPL_USING_NAMESPACE
      : public std::iterator<bidirectional_iterator_tag, T, difference_type> 
		#else
		      : public ::global_iterator<bidirectional_iterator_tag, T, difference_type>
		#endif
		{
    friend class list<T, Allocator>;
    friend class iterator;
 
    protected:
 
        link_type node;
        DEC_OBJ_LOCK(citer_mutex)
 
        const_iterator (link_type x) : node (x) {}
 
    public:
 
        const_iterator () {}
        const_iterator (const iterator& x) : node (x.node) {}
 
        ~const_iterator () { REMOVE(citer_mutex); }
 
        bool operator== (const const_iterator& x) const
        { READ_LOCK(citer_mutex); return node == x.node; }
 
        bool operator!= (const const_iterator& x) const
        { READ_LOCK(citer_mutex); return node != x.node; }
 
        const_reference operator*() const
        {
            READ_LOCK(citer_mutex);
            return (*node).data;
        }
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
        const_iterator& operator-- ()
        {
            WRITE_LOCK(citer_mutex);
            node = (link_type) ((*node).prev);
            return *this;
        }
        const_iterator operator-- (int)
        {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }
    };
 
    typedef reverse_bidirectional_iterator<const_iterator, value_type,
                                           const_reference, const_pointer,
                                           difference_type>
                                           const_reverse_iterator;
    typedef reverse_bidirectional_iterator<iterator, value_type, reference,
                                           pointer, difference_type>
                                           reverse_iterator;
 
    //  23.2.2.1  construct/copy/destroy:
    //
   explicit list (const Allocator& alloc = Allocator ())
   : value_allocator(alloc), length (0)
#ifdef MSIPL_MEMBER_TEMPLATE
      , list_node_allocator(alloc)
#endif
    , cache ((link_type)0)
    {
     head = get_node();
    }      

   explicit list (size_type n, const T& value = T(), 
                  const Allocator& alloc = Allocator ())
   : value_allocator(alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
      , list_node_allocator(alloc)
#endif
     , length (0), cache ((link_type)0)
   {
      head = get_node();
      insert(begin(), n, value); 
   }

#ifdef MSIPL_MEMBER_TEMPLATE
   template <class InputIterator>
   list (InputIterator first, InputIterator last,
         const Allocator& alloc = Allocator ())
   : value_allocator(alloc)
     , list_node_allocator(alloc), length (0), cache(0)
   {
      head = get_node();
      insert (begin (), first, last);
    }
#else
    list (const T* first, const T* last,
          const Allocator& alloc = Allocator ())
    : value_allocator(alloc), cache(0), length (0)
    {
       head = get_node();
       insert (begin (), first, last);
    }
    list (const_iterator first, const_iterator last,
          const Allocator& alloc = Allocator ())
    : value_allocator(alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
      , list_node_allocator(alloc)
#endif
      , cache(0), length (0)
    {
        head = get_node();
        insert (begin (), first, last);
    }
#endif 

    ~list ()
    {
        link_type i= (link_type)head->next;
        while ( i != head)
        {
           link_type j = (link_type)i->next;
           destroy(i);                    // ¥¥¥Êadded JDJ  
           list_node_allocator.deallocate (i); i=j;
        }
        list_node_allocator.deallocate (head); 
        while(cache)
        {
           i = (link_type)cache->next;
           //destroy(cache);                    // ¥¥¥Êadded JDJ // mm 970916
           list_node_allocator.deallocate (cache); cache=i;
        }
        REMOVE(lst_mutex);
    }

    list (const list<T, Allocator>& x)
    : value_allocator(x.value_allocator)
#ifdef MSIPL_MEMBER_TEMPLATE
      , list_node_allocator(x.list_node_allocator)
#endif
      ,cache (0),length (0)
    {
        head = get_node();
        insert (begin (), x.begin (), x.end ());
    }

   list<T, Allocator>& operator= (const list<T, Allocator>& x)
   {
       WRITE_LOCK(lst_mutex);
       if (this != &x)
       {
           iterator first1 = begin ();
           iterator last1 = end ();
           const_iterator first2 = x.begin ();
           const_iterator last2 = x.end ();
           while (first1 != last1 && first2 != last2) *first1++ = *first2++;
           if (first2 == last2)
               erase (first1, last1);
           else
               insert (last1, first2, last2);
       }
       return *this;
   }

#ifdef MSIPL_MEMBER_TEMPLATE
    template<class InputIterator>
    void assign (InputIterator first2, InputIterator last2)
    {
       erase (begin (), end ());
       insert (begin (), n, t);
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
    void assign (const T* first, const T* last)
    {
       erase (begin (), end ());
       insert (begin (), first, last);
    }
    void assign (iterator first, iterator last)
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

    allocator_type
    get_allocator () const { return value_allocator; }

// 
// Iterators:
//

    iterator             begin ()
    {
        READ_LOCK(lst_mutex);
        return (link_type) ((*head).next);
    }
    const_iterator       begin () const
    {
        READ_LOCK(lst_mutex);
        return (link_type) ((*head).next);
    }
    iterator             end   ()
    {
        READ_LOCK(lst_mutex);
        return head;
    }
    const_iterator       end   () const
    {
        READ_LOCK(lst_mutex);
        return head;
    }
 
    reverse_iterator       rbegin ()
    { return reverse_iterator (end ()); }
 
    const_reverse_iterator       rbegin () const
    { return const_reverse_iterator (end ()); }
 
    reverse_iterator       rend ()
    { return reverse_iterator (begin ()); }
    const_reverse_iterator rend () const
    { return const_reverse_iterator (begin ()); }

//
// 23.2.2.2
//

    bool      empty ()    const
    {
        READ_LOCK(lst_mutex);
        return (length==0);
    }
  
    size_type size  ()    const { READ_LOCK(lst_mutex); return length; }
    size_type max_size () const { return list_node_allocator.max_size (); }

   void resize (size_type sz, T v = T ())
   {
       WRITE_LOCK(lst_mutex);
       if (sz >= size ())
          insert (end (), sz-size (), v);
       else 
       {
          iterator iter = begin ();
          for (size_type i = 0; i < sz; i++)
              ++iter;
          erase (iter, end ());
       }
   }

    //
    //   element access:
    //
    reference         front ()       { return *begin ();   }
    const_reference   front () const { return *begin ();   }
    reference         back ()        { return *(--end ()); }
    const_reference   back () const  { return *(--end ()); }

    //
    //   23.2.2.3  modifiers
 
    iterator insert (iterator position, const T& x = T ())
    {
        WRITE_LOCK(lst_mutex);
        link_type tmp = get_node ();
        tmp->prev = (*position.node).prev;
        tmp->next = position.node;
        construct (value_allocator.address ((*tmp).data), x);
        (*(link_type ((*position.node).prev))).next = tmp;
        (*position.node).prev = tmp;
        ++length;
        return tmp;
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (iterator position,
                 InputIterator first, InputIterator last)
    {
        while (first != last) insert (position, *first++);
    }
 
#else
    void insert (iterator position, const T* first, const T* last)
    {
        while (first != last) insert (position, *first++);
    }
 
    void insert (iterator position,
                 const_iterator first, const_iterator last)
    {
        while (first != last) insert (position, *first++);
    }
#endif

   void insert (iterator position, size_type n, const T& x)
   {
       while (n--) insert (position, x);
   }

   void push_front (const T& x) { insert (begin (), x); }
   void push_back (const T& x)  { insert (end (), x);   }
   void pop_front ()            { erase (begin ()); }
   void pop_back ()
   {
       WRITE_LOCK(lst_mutex);
       erase (--end());
   }

   iterator erase (iterator position)
   {
        WRITE_LOCK(lst_mutex);
        (*(link_type((*position.node).prev))).next = (*position.node).next;
        (*(link_type((*position.node).next))).prev = (*position.node).prev;
        iterator ret = link_type((*position.node).next);
        (*position.node).next = cache;
        cache = (link_type)position.node;
        destroy(cache); // Added JCV for cache destroy() leak  // mm 970916
        --length;
        return ret;
    }

    iterator erase (iterator first, iterator last)
    {
        while (first != last) erase (first++);
        return last;
    }

   void swap (list<T, Allocator>& x)
    {
        WRITE_LOCK(lst_mutex);
        std::swap (length, x.length);
        std::swap (value_allocator, x.value_allocator);
        std::swap (list_node_allocator, x.list_node_allocator);
        std::swap (cache, x.cache);
        std::swap (head, x.head);
    }
 
   void clear() { erase(begin(), end()); }

//
// 23.2.2.4 list operations
//

   void splice (iterator position, list<T, Allocator>& x)
   {
        WRITE_LOCK(lst_mutex);
        if (!x.empty () && &x != this)
        {
            transfer (position, x.begin (), x.end ());
            length += x.length;
            x.length = 0;
        }
   }

   void splice (iterator position, list<T, Allocator>& x, iterator i)
   {
        WRITE_LOCK(lst_mutex);
        iterator j = i;
        if (position == i || position == ++j) return;
        transfer (position, i, j);       
        ++length;
        --x.length;
   }
   void splice (iterator position,
                 list<T, Allocator>& x, iterator first, iterator last)
   {
        if (first != last)
        {
            WRITE_LOCK(lst_mutex);
            if (&x != this)
            {
                difference_type n = distance (first, last);
                x.length -= n;
                length += n;
            }
            transfer (position, first, last);
        }
   }
#ifdef MSIPL_MEMBER_TEMPLATE
 
    template <class Predicate>
    void remove_if (Predicate pred);
 
    template <class BinaryPredicate>
    void unique (BinaryPredicate binary_pred);
 
    template <class Compare>
    void sort (Compare comp);
 
    template <class Compare>
    void merge (list<T, Allocator>& x, Compare comp);
 
#endif
    void remove (const T& value);
    void unique ();
    void merge  (list<T, Allocator>& x);
    void reverse ();
    void sort   ();
protected:

   void transfer (iterator position, iterator first, iterator last)
   {
       WRITE_LOCK(lst_mutex);
       (*(link_type ((*last.node).prev))).next = position.node;
       (*(link_type ((*first.node).prev))).next = last.node;
       (*(link_type ((*position.node).prev))).next = first.node;
       link_type tmp = link_type ((*position.node).prev);
       (*position.node).prev = (*last.node).prev;
       (*last.node).prev = (*first.node).prev;
       (*first.node).prev = tmp;
   }
};

template <class T, class Allocator>
inline bool
operator== (const list<T, Allocator>& x, const list<T, Allocator>& y)
{
    return x.size () == y.size () &&
           equal (x.begin (), x.end (), y.begin ());
}
 
template <class T, class Allocator>
inline bool
operator< (const list<T, Allocator>& x, const list<T, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (),
           y.begin (), y.end ());
}
 
template <class T, class Allocator>
void list<T, Allocator>::remove (const T& value)
{
    WRITE_LOCK(lst_mutex);
    iterator first = begin ();
    iterator last = end ();
    while (first != last)
        if (*first == value) erase (first++);
        else ++first;
}
 
template <class T, class Allocator>
void list<T, Allocator>::unique ()
{
    iterator first = begin();
    iterator last = end();
    if (first != last) 
    {  
       WRITE_LOCK(lst_mutex);
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
}
 
template <class T, class Allocator>
void list<T, Allocator>::merge (list<T, Allocator>& x)
{
    if (&x == this || x.empty()) return;
    WRITE_LOCK(lst_mutex);
    if(empty()) 
    {
        transfer(begin(),x.begin(),x.end());
        length=x.length;x.length=0;
        return;
    }
    iterator first1 = begin ();
    iterator last1 = end ();
    iterator first2 = x.begin ();
    iterator last2 = x.end ();
    iterator next;
    while (first1 != last1 && first2 != last2)
        if (*first2 < *first1)
        {
            next = first2;
            transfer (first1, first2, ++next);
            first2 = next;
        } 
        else
            ++first1;
    if (first2 != last2) 
        transfer (last1, first2, last2);
    length += x.length;
    x.length= 0;
}
 
template <class T, class Allocator>
void list<T, Allocator>::reverse ()
{
    if (size () < 2) return;
    WRITE_LOCK(lst_mutex);
    link_type tmp = head;
    void_pointer t; 
    do
    {
        t = tmp->next;
        tmp->next = tmp->prev;
        tmp->prev = t;
        tmp = (link_type)tmp->prev;
    }
    while(tmp !=head);
}   
 
template <class T, class Allocator> 
void list<T, Allocator>::sort ()
{
    if (size () < 2) return;
    WRITE_LOCK(lst_mutex);
    list<T, Allocator> carry;
    list<T, Allocator> counter[64];
    int sfill = 0;
    while (!empty ())
    {
        carry.splice (carry.begin (), *this, begin ());
        int i = 0;
        while (i < sfill && !counter[i].empty ())
        {
            counter[i].merge (carry);
            carry.swap (counter[i++]);
        }
        carry.swap (counter[i]);
        if (i == sfill) ++sfill;
    }
    while (sfill--) merge(counter[sfill]);
}
 
#ifdef MSIPL_MEMBER_TEMPLATE
template <class T, class Allocator>
template <class Predicate>
void list<T, Allocator>::remove_if (Predicate pred)
{
    WRITE_LOCK(lst_mutex);
    iterator first = begin ();
    iterator last = end ();
    while (first != last)
        if (pred (*first)) erase (first++);
        else first++;
}
 
template <class T, class Allocator>
template <class BinaryPredicate>
void list<T, Allocator>::unique (BinaryPredicate binary_pred)
{
    WRITE_LOCK(lst_mutex);
    iterator first = begin ();
    iterator last = end ();
    if (first == last) return;
    iterator next = first;
    while (++next != last)
        if (binary_pred (*first, *next))
            { erase (next); next =first;}
        else
            first = next;
}
 
template <class T, class Allocator>
template <class Compare>
void list<T, Allocator>::merge (list<T, Allocator>& x, Compare comp)
{
    if (&x != this) {
    WRITE_LOCK(lst_mutex);
    iterator first1 = begin ();
    iterator last1 = end ();
    iterator first2 = x.begin ();
    iterator last2 = x.end ();
    while (first1 != last1 && first2 != last2)
        if (comp (*first2, *first1))
        {
            iterator next = first2;
            transfer (first1, first2, ++next);
            first2 = next;
        } else
            ++first1;
    if (first2 != last2) transfer (last1, first2, last2);
    length += x.length;
    x.length= 0;}
}
 
template <class T, class Allocator>
template <class Compare>
void list<T, Allocator>::sort (Compare comp)
{
    if (size () < 2) return;
    WRITE_LOCK(lst_mutex);
    list<T, Allocator> carry;
    list<T, Allocator> counter[64];
    int sfill = 0;
    while (!empty ())
    {
        carry.splice (carry.begin (), *this, begin ());
        int i = 0;
        while (i < sfill && !counter[i].empty ())
        {
            counter[i].merge (carry, comp);
            carry.swap (counter[i++]);
        }
        carry.swap (counter[i]);
        if (i == sfill) ++sfill;
    }
    while (sfill--) merge(counter[sfill]);
}
 
#endif /* MSIPL_MEMBER_TEMPLATE */

#ifdef __MSL_NO_INSTANTIATE__
	template __dont_instantiate class list<int, allocator<int> >;
	template __dont_instantiate class list<char, allocator<char> >;
#endif

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#else  
#undef std
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif

/* Change record
 * 961206 received from atul
 * 961206 bkoz line 99, 192 change iterator to global_iterator
 * 961210 bkoz added alignment wrapper
 * 961216 ah changed memory to mmemory
 * 961218 bkoz lines 782-792, 706-719  changed fill to sfill
 * 970216 bkoz lines 293,300 added cleanup code to ~list() via Jesse Jones  MW00478
 * 970916 mm further corrections to ~list and erase via Justin Vallon
 */
