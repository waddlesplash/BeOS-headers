/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_SET_H
#define MSIPL_SET_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(tree)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 23.3.3 -- class set

#ifdef MSIPL_DEF_TEMPARG
template <class Key, class Compare = less<Key>,
          class Allocator = allocator<Key> >
#else
template <class Key, class Compare, class Allocator>
#endif
class set {
public:
    //
    // typedefs:
    //
    typedef Key     key_type;
    typedef Key     value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;

private:

    typedef rb_tree<key_type, value_type, 
                    ident<value_type, key_type>,
                    key_compare, Allocator>         rep_type;
    rep_type t;  // red-black tree representing set

public:
    typedef          Allocator                          allocator_type;
    typedef typename rep_type::const_reference          reference;
    typedef typename rep_type::const_reference          const_reference;
    typedef typename rep_type::const_iterator           iterator;
    typedef typename rep_type::const_iterator           const_iterator;
    typedef typename rep_type::const_reverse_iterator   reverse_iterator;
    typedef typename rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename rep_type::size_type                size_type;
    typedef typename rep_type::difference_type          difference_type;

public:

    //
    // 23.3.3.2 construct/copy/destroy
    //
    explicit
    set (const Compare& comp = Compare (),
         const Allocator& alloc = Allocator())
    : t (comp, false, alloc) {}

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    set (InputIterator first, InputIterator last,
         const Compare& comp = Compare (),
         const Allocator& alloc = Allocator())
    : t (comp, false, alloc)
    {
        for (InputIterator i = first; i != last; ++i)
           t.insert (*i);
    }
#else
    set (const value_type* first, const value_type* last, 
         const Compare& comp = Compare (),
         const Allocator& alloc = Allocator())
    : t (comp, false, alloc)
    {
        for (const value_type* i = first; i != last; ++i)
           t.insert (*i);
    }
    set (const_iterator first, const_iterator last, 
         const Compare& comp = Compare (),
         const Allocator& alloc = Allocator())
    : t (comp, false, alloc)
    {
        for (const_iterator i = first; i != last; ++i)
           t.insert (*i);
    }
#endif /* MSIPL_MEMBER_TEMPLATE */

    set (const set<Key, Compare, Allocator>& x)
    : t (x.t, false) {}

    set<Key, Compare, Allocator>& 
    operator= (const set<Key, Compare, Allocator>& x)
    { 
        t = x.t; 
        return *this;
    }

    allocator_type
    get_allocator () const
    {
        return t.get_allocator ();
    }
 
    //
    // 23.3.3.3  Iterators:
    //
    iterator          begin ()      const { return t.begin ();    }
    iterator          end ()        const { return t.end ();      }
    reverse_iterator  rbegin ()     const { return t.rbegin ();   } 
    reverse_iterator  rend ()       const { return t.rend ();     }

    //
    // 23.3.3.4  capacity:
    //
    bool              empty ()      const { return t.empty ();    }
    size_type         size ()       const { return t.size ();     }
    size_type         max_size ()   const { return t.max_size (); }

    //
    // 23.3.3.5  modifiers:
    //
    typedef  pair<iterator, bool> pair_iterator_bool; 
    // typedef done to get around compiler bug

    pair_iterator_bool insert (const value_type& x)
    {
        pair<typename rep_type::iterator, bool> p = t.insert (x); 
        return pair<iterator, bool> (p.first, p.second);
    }
    iterator insert (iterator position, const value_type& x)
    {
        return t.insert ((typename rep_type::iterator&)position, x);
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        for (InputIterator i = first; i != last; ++i)
            t.insert (*i);
    }
#else
    void insert (const value_type* first, const value_type* last)
    {
        for (const value_type* i = first; i != last; ++i)
            t.insert (*i);
    }
    void insert (const_iterator first, const iterator last)
    {
        t.insert (first, last);
    }
#endif /* MSIPL_MEMBER_TEMPLATE */

    void erase (iterator position)
    {
        t.erase ((typename rep_type::iterator&)position); 
    }
    size_type erase (const key_type& x)
    {
        return t.erase (x); 
    }
    void erase (iterator first, iterator last)
    {
        t.erase ((typename rep_type::iterator&)first, 
               (typename rep_type::iterator&)last); 
    }

    void swap (set<Key, Compare, Allocator>& x) { t.swap (x.t); }

    void clear () { erase (begin (), end ()); }


    //
    // 23.3.3.6  Observers:
    //
    key_compare       key_comp ()   const { return t.key_comp (); }
    value_compare     value_comp () const { return t.key_comp (); }

    //
    // 23.3.3.7  set operations:
    //
    iterator   find (const key_type& x)  const { return t.find (x);  }
    size_type  count (const key_type& x) const { return t.count (x); }

    iterator   lower_bound (const key_type& x) const
    {
        return t.lower_bound (x);
    }
    iterator upper_bound (const key_type& x) const
    {
        return t.upper_bound (x); 
    }

    // typedef done to get around compiler bug
    typedef  pair<iterator, iterator> pair_iterator_iterator; 

    pair_iterator_iterator equal_range (const key_type& x) const
    {
        return t.equal_range (x);
    }
};

template <class Key, class Compare, class Allocator>
inline bool operator== (const set<Key, Compare, Allocator>& x, 
                        const set<Key, Compare, Allocator>& y)
{
    return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ());
}

template <class Key, class Compare, class Allocator>
inline bool operator< (const set<Key, Compare, Allocator>& x, 
                       const set<Key, Compare, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

// Subclause 23.3.4 -- class multiset
 
#ifdef MSIPL_DEF_TEMPARG
template <class Key, class Compare = less<Key>,
          class Allocator = allocator<Key> >
#else
template <class Key, class Compare, class Allocator>
#endif
class multiset {
public:
    //
    // typedefs:
    //
    typedef Key           key_type;
    typedef Key           value_type;
    typedef Compare       key_compare;
    typedef Compare       value_compare;
    typedef Allocator     allocator_type;

private:

    typedef rb_tree<key_type, value_type, 
                    ident<value_type, key_type>,
                    key_compare, Allocator> rep_type;

    rep_type t;  // red-black tree representing multiset

public:

    typedef typename rep_type::const_reference          reference;
    typedef typename rep_type::const_reference          const_reference;
    typedef typename rep_type::const_iterator           iterator;
    typedef typename rep_type::const_iterator           const_iterator;
    typedef typename rep_type::const_reverse_iterator   reverse_iterator;
    typedef typename rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename rep_type::size_type                size_type;
    typedef typename rep_type::difference_type          difference_type;

public:

    //
    // construct/copy/destroy
    //
    explicit
    multiset (const Compare& comp = Compare (), 
              const Allocator& alloc = Allocator())
    : t (comp, true, alloc) {}

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    multiset (InputIterator first, InputIterator last,
              const Compare& comp = Compare (),
              const Allocator& alloc = Allocator())
    : t (comp, true, alloc)
    {
        for (InputIterator i = first; i != last; ++i)
           t.insert (*i);
    }
#else
    multiset (const value_type* first, const value_type* last, 
              const Compare& comp = Compare (),
              const Allocator& alloc = Allocator())
    : t (comp, true, alloc)
    {
        for (const value_type* i = first; i != last; ++i)
           t.insert (*i);
    }
    multiset (iterator first, iterator last,
              const Compare& comp = Compare (),
              const Allocator& alloc = Allocator())
    : t (comp, true, alloc)
    {
        for (iterator i = first; i != last; ++i)
           t.insert (*i);
    }
#endif

    multiset (const multiset<Key, Compare, Allocator>& x) 
    : t (x.t, true) {}

    multiset<Key, Compare, Allocator>& 
    operator= (const multiset<Key, Compare, Allocator>& x)
    { 
        t = x.t; 
        return *this;
    }

    allocator_type 
    get_allocator () const 
    {
        return t.get_allocator ();
    }

    //
    // iterators:
    //
    iterator         begin ()      const { return t.begin ();    }
    iterator         end ()        const { return t.end ();      }
    reverse_iterator rbegin ()     const { return t.rbegin ();   } 
    reverse_iterator rend ()       const { return t.rend ();     }

    // 
    // capacity:
    //
    bool             empty ()      const { return t.empty ();    }
    size_type        size ()       const { return t.size ();     }
    size_type        max_size ()   const { return t.max_size (); }

    //
    // modifiers:
    //
    iterator insert (const value_type& x)
    {
        return t.insert (x).first;
    }
    iterator insert (iterator position, const value_type& x)
    {
        return t.insert ((typename rep_type::iterator&)position, x);
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        for (InputIterator i = first; i != last; ++i)
            t.insert (*i);
    }
#else
    void insert (const value_type* first, const value_type* last)
    {
        for (const value_type* i = first; i != last; ++i)
            t.insert (*i);
    }
    void insert (const_iterator first, const_iterator last)
    {
        t.insert (first, last);
    }
#endif

    void erase (iterator position)
    {
        t.erase ((typename rep_type::iterator&)position); 
    }
    size_type erase (const key_type& x)
    {
        return t.erase (x); 
    }
    void erase (iterator first, iterator last)
    {
        t.erase ((typename rep_type::iterator&)first, 
              (typename rep_type::iterator&)last); 
    }

    void swap (multiset<Key, Compare, Allocator>& x) { t.swap (x.t); }

    void clear () { erase (begin (), end ()); }

    //
    // observers:
    //
    key_compare      key_comp ()   const { return t.key_comp (); }
    value_compare    value_comp () const { return t.key_comp (); }

    //
    // set operations:
    //
    iterator     find (const key_type& x)  const { return t.find (x);  }
    size_type    count (const key_type& x) const { return t.count (x); }

    iterator lower_bound (const key_type& x) const
    {
        return t.lower_bound (x);
    }
    iterator upper_bound (const key_type& x) const
    {
        return t.upper_bound (x); 
    }

    // typedef done to get around compiler bug
    typedef  pair<iterator, iterator> pair_iterator_iterator; 

    pair_iterator_iterator equal_range (const key_type& x) const
    {
        return t.equal_range (x);
    }
};

template <class Key, class Compare, class Allocator>
inline bool operator== (const multiset<Key, Compare, Allocator>& x, 
                        const multiset<Key, Compare, Allocator>& y)
{
    return x.size () == y.size () &&
           equal (x.begin (), x.end (), y.begin ());
}

template <class Key, class Compare, class Allocator>
inline bool operator< (const multiset<Key, Compare, Allocator>& x, 
                       const multiset<Key, Compare, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (),
                                    y.begin (), y.end ());
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_SET_H */

//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory
