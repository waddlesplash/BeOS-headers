/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_MAP_H
#define MSIPL_MAP_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(tree)
#include MOD_INCLUDE(mexcept)
 
#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

// Subclause 23.3.1 -- class map
 
#ifdef MSIPL_DEF_TEMPARG
template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<T> >
#else
template <class Key, class T, class Compare, class Allocator>
#endif
class map {
public:
    //
    // typedefs:
    //
    typedef Key                            key_type;
    typedef pair<M_CONST Key, T>           value_type;
    typedef Compare                        key_compare;
    typedef T                              mapped_type;

private:

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<value_type>::other  allocator_type;
#else
    typedef          DefAllocator<value_type>              allocator_type;
#endif

    typedef rb_tree<key_type, value_type, select1st<value_type, key_type>,
                    key_compare, allocator_type>   rep_type;

    rep_type t;  // red-black tree representing map

public:

    typedef typename rep_type::pointer                 pointer;
    typedef typename rep_type::reference               reference;
    typedef typename rep_type::const_reference         const_reference;
    typedef typename rep_type::iterator                iterator;
    typedef typename rep_type::const_iterator          const_iterator;
    typedef typename rep_type::reverse_iterator        reverse_iterator;
    typedef typename rep_type::const_reverse_iterator  const_reverse_iterator;
    typedef typename rep_type::size_type               size_type;
    typedef typename rep_type::difference_type         difference_type;
    
    class value_compare
        : public binary_function<value_type, value_type, bool> {

        friend class map<Key, T, Compare, Allocator>;
    protected :

        Compare comp;
        value_compare (Compare c) : comp (c) {}

    public:

        bool operator () (const value_type& x, const value_type& y) const
        {
            return comp (x.first, y.first);
        }
    };


public:

    //
    // 23.3.1.2  construct/copy/destroy:
    //
    explicit
    map (const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
         const Allocator& alloc = Allocator ())
#else
         const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, false, alloc) { }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    map (InputIterator first, InputIterator last,
         const Compare& comp = Compare (),
         const Allocator& alloc = Allocator ())
    : t (comp, false, alloc) { while (first != last)  insert (*first++); }
#else
    map (const value_type* first, const value_type* last, 
         const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
         const Allocator& alloc = Allocator ())
#else
         const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, false, alloc) { while (first != last)  insert (*first++); }
    map (iterator first, iterator last, 
         const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
         const Allocator& alloc = Allocator ())
#else
         const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, false, alloc) { while (first != last)  insert (*first++); }
    map (const_iterator first, const_iterator last, 
         const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
         const Allocator& alloc = Allocator ())
#else
         const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, false, alloc) { while (first != last)  insert (*first++); }
#endif

    map (const map<Key, T, Compare, Allocator>& x)
    : t (x.t, false) {}

    map<Key, T, Compare, Allocator>& 
    operator= (const map<Key, T, Compare, Allocator>& x)
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
    // 23.3.1.3  iterators:
    //
    iterator               begin ()          { return t.begin ();    }
    const_iterator         begin ()    const { return t.begin ();    }
    iterator               end ()            { return t.end ();      }
    const_iterator         end ()      const { return t.end ();      }
    reverse_iterator       rbegin ()         { return t.rbegin ();   }
    const_reverse_iterator rbegin ()   const { return t.rbegin ();   }
    reverse_iterator       rend ()           { return t.rend ();     }
    const_reverse_iterator rend ()     const { return t.rend ();     }

    //
    // 23.3.1.4  capacity:
    //
    bool                   empty ()    const { return t.empty ();    }
    size_type              size ()     const { return t.size ();     }
    size_type              max_size () const { return t.max_size (); }

    // 
    // 23.3.1.5  element access:
    // 
    mapped_type& operator[] (const key_type& k)
    {
        return (*((insert (value_type (k, T ()))).first)).second;
    }

#pragma extended_errorcheck off
    const mapped_type& operator[] (const key_type& k) const
    {
        // return (*((insert (value_type (k, T ()))).first)).second;
        const_iterator iter = find (k);
        if (iter == end ())
        {
#ifdef  MSIPL_EXCEPT
            throw   out_of_range ("Out of range exception occurred");
#else
            fprintf (stderr, "Out of range exception occurred\n");
            exit (1);
#endif
        }
        else	
        {
            return (*iter).second;
         }
    }
#pragma extended_errorcheck reset

    //
    // 23.3.1.6  modifiers
    //

    // typedef done to get around compiler bug
    typedef pair<iterator, bool> pair_iterator_bool; 

    pair_iterator_bool
    insert (const value_type& x) { return t.insert (x); }

    iterator insert (iterator position, const value_type& x)
    {
        return t.insert (position, x);
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        t.insert (first, last);
    }
#else
    void insert (const value_type* first, const value_type* last)
    {
        t.insert (first, last);
    }
    void insert (const_iterator first, const_iterator last)
    {
        t.insert (first, last);
    }
#endif

    void  erase (iterator position) 
    {
        t.erase (position);
     }
    size_type erase (const key_type& x) { return t.erase (x); }
    void  erase (iterator first, iterator last)
    { t.erase (first, last); }

    void swap (map<Key, T, Compare, Allocator>& x) { t.swap (x.t); }

    void clear () { erase (begin (), end ()); }

    //
    // 23.3.1.7  Observers
    //
    key_compare key_comp ()     const { return t.key_comp (); }
    value_compare value_comp () const
    { return value_compare (t.key_comp ()); }

    //
    // 23.3.1.8  Map operations:
    //
    iterator       find (const key_type& x)       { return t.find (x); }
    const_iterator find (const key_type& x) const { return t.find (x); }

    size_type count (const key_type& x) const { return t.count (x); }

    iterator lower_bound (const key_type& x) { return t.lower_bound (x); }
    const_iterator lower_bound (const key_type& x) const
    {
        return t.lower_bound (x); 
    }

    iterator upper_bound (const key_type& x) { return t.upper_bound (x); }
    const_iterator upper_bound (const key_type& x) const
    {
        return t.upper_bound (x); 
    }

    // typedef done to get around compiler bug
    typedef pair<iterator, iterator> pair_iterator_iterator; 

    pair_iterator_iterator equal_range (const key_type& x)
    {
        return t.equal_range (x);
    }

    // typedef done to get around compiler bug
    typedef pair<const_iterator, const_iterator> pair_citerator_citerator; 

    pair_citerator_citerator equal_range (const key_type& x) const
    {
        return t.equal_range (x);
    }
};

template <class Key, class T, class Compare, class Allocator>
inline bool operator== (const map<Key, T, Compare, Allocator>& x, 
                        const map<Key, T, Compare, Allocator>& y)
{
    return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ());
}

template <class Key, class T, class Compare, class Allocator>
inline bool operator< (const map<Key, T, Compare, Allocator>& x, 
                       const map<Key, T, Compare, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

// Subclause 23.3.2 -- class multimap

#ifdef MSIPL_DEF_TEMPARG
template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<T> >
#else
template <class Key, class T, class Compare, class Allocator>
#endif
class multimap {
public:

    //
    // typedefs:
    //
    typedef Key                          key_type;
    typedef pair<M_CONST Key, T>         value_type;
    typedef Compare                      key_compare;
    typedef T                            mapped_type;

    class value_compare
        : public binary_function<value_type, value_type, bool> {

        friend class multimap<Key, T, Compare, Allocator>;

    protected:

        Compare comp;
        value_compare (Compare c) : comp (c) {}

    public:

        bool operator () (const value_type& x, const value_type& y) const
        {
            return comp (x.first, y.first);
        }
    };

private:

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename  Allocator::rebind<value_type>::other  allocator_type;
#else
    typedef           DefAllocator<value_type>              allocator_type;
#endif
    typedef rb_tree<key_type, value_type, 
                    select1st<value_type, key_type>,
                    key_compare, allocator_type> rep_type;

    rep_type t;  // red-black tree representing multimap

public:

    typedef typename rep_type::reference                reference;
    typedef typename rep_type::const_reference          const_reference;
    typedef typename rep_type::iterator                 iterator;
    typedef typename rep_type::const_iterator           const_iterator; 
    typedef typename rep_type::reverse_iterator         reverse_iterator;
    typedef typename rep_type::const_reverse_iterator   const_reverse_iterator;
    typedef typename rep_type::size_type                size_type;
    typedef typename rep_type::difference_type          difference_type;

public:

    //
    // construct/copy/destroy
    //
    explicit
    multimap (const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
              const Allocator& alloc = Allocator ())
#else
              const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, true, alloc) { }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    multimap (InputIterator first, InputIterator last,
              const Compare& comp = Compare (),
              const Allocator& alloc = Allocator ())
    : t (comp, true, alloc) { while (first != last)  insert (*first++); }
#else
    multimap (const_iterator first, const_iterator last, 
              const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
              const Allocator& alloc = Allocator ())
#else
              const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, true, alloc) { while (first != last)  insert (*first++); }

    multimap (const value_type* first, const value_type* last, 
              const Compare& comp = Compare (),
#ifdef MSIPL_MEMBER_TEMPLATE
              const Allocator& alloc = Allocator ())
#else
              const allocator_type& alloc = allocator_type ())
#endif
    : t (comp, true, alloc) { while (first != last)  insert (*first++); }
#endif

    multimap (const multimap<Key, T, Compare, Allocator>& x)
    : t (x.t, true) { }

    multimap<Key, T, Compare, Allocator>&
    operator= (const multimap<Key, T, Compare, Allocator>& x)
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
    iterator               begin ()           { return t.begin ();    }
    const_iterator         begin ()     const { return t.begin ();    }
    iterator               end ()             { return t.end ();      }
    const_iterator         end ()       const { return t.end ();      }

    reverse_iterator       rbegin ()          { return t.rbegin ();   }
    const_reverse_iterator rbegin ()    const { return t.rbegin ();   }
    reverse_iterator       rend ()            { return t.rend ();     }
    const_reverse_iterator rend ()      const { return t.rend ();     }

    //
    //  capacity:
    //
    bool                   empty ()     const { return t.empty ();    }
    size_type              size ()      const { return t.size ();     }
    size_type              max_size ()  const { return t.max_size (); }

    //
    // modifiers
    //
    iterator insert (const value_type& x) { return t.insert (x).first; }
    iterator insert (iterator position, const value_type& x)
    {
        return t.insert (position, x);
    }
#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        t.insert (first, last);
    }
#else
    void insert (const value_type* first, const value_type* last)
    {
        t.insert (first, last);
    }
    void insert (iterator first, iterator last)
    {
        t.insert (first, last);
    }
    void insert (const_iterator first, const_iterator last)
    {
        t.insert (first, last);
    }
#endif

    void  erase (iterator position)
    { 
        t.erase (position);
     }
    size_type erase (const key_type& x) { return t.erase (x); }
    void  erase (iterator first, iterator last)
    { 
        t.erase (first, last);
     }

    void swap (multimap<Key, T, Compare, Allocator>& x) { t.swap (x.t); }

    void clear () { erase (begin (), end ()); }

    //
    // accessors:
    //
    key_compare   key_comp ()   const { return t.key_comp (); }
    value_compare value_comp () const
    { return value_compare (t.key_comp ()); }

    //
    // map operations:
    //
    iterator       find (const key_type& x)        { return t.find (x); }
    const_iterator find (const key_type& x)  const { return t.find (x); }

    size_type      count (const key_type& x) const { return t.count (x); }

    iterator       lower_bound (const key_type& x)
    { return t.lower_bound (x); }

    const_iterator lower_bound (const key_type& x) const
    {
        return t.lower_bound (x); 
    }

    iterator upper_bound (const key_type& x)
    { return t.upper_bound (x); }

    const_iterator upper_bound (const key_type& x) const
    {
        return t.upper_bound (x); 
    }

    // typedefs done to get around compiler bug
    typedef  pair<iterator, iterator>             pair_iterator_iterator;
    typedef  pair<const_iterator, const_iterator> pair_citerator_citerator;

    pair_iterator_iterator equal_range (const key_type& x)
    {
        return t.equal_range (x);
    }
    pair_citerator_citerator equal_range (const key_type& x) const
    {
        return t.equal_range (x);
    }
};

template <class Key, class T, class Compare, class Allocator>
inline bool operator== (const multimap<Key, T, Compare, Allocator>& x, 
                       const multimap<Key, T, Compare, Allocator>& y)
{
    return x.size () == y.size () &&
           equal (x.begin (), x.end (), y.begin ());
}

template <class Key, class T, class Compare, class Allocator>
inline bool operator< (const multimap<Key, T, Compare, Allocator>& x, 
                      const multimap<Key, T, Compare, Allocator>& y)
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

#endif /* MSIPL_MAP_H */

//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory
//961213 bkoz line 189 wrapped with pragma extended_errorcheck off