/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_HASH_SET_H
#define MSIPL_HASH_SET_H

#include <mcompile.h>

#include MOD_INCLUDE(mmemory)
#include MOD_INCLUDE(hashtbl)
#include MOD_INCLUDE(functional)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

template <class Key, class HashFunction, class KeyEqual>
class hash_set {
public:
    //
    // typedefs:
    //
    typedef Key           key_type;
    typedef Key           value_type;
    typedef HashFunction  hash_function;
    typedef KeyEqual      key_equal;
    typedef KeyEqual      value_compare;

private:
    typedef hash_table <key_type, value_type, 
                        ident<value_type, key_type>, 
                        hash_function, key_equal>       rep_type;

    rep_type ht;        // hash_table representing hash_set

public:

    typedef typename rep_type::reference        reference;
    typedef typename rep_type::const_reference  const_reference;

    typedef typename rep_type::const_iterator           iterator;
    typedef typename rep_type::const_iterator           const_iterator;

    typedef typename rep_type::size_type        size_type;
    typedef typename rep_type::difference_type  difference_type;

    //
    // allocation/deallocation
    //
    hash_set (size_type initSize     = 10007,
              float maxLF            = 1.1, 
              const HashFunction& hf = HashFunction (),
              const KeyEqual& equal  = KeyEqual ()) 
    : ht (initSize, maxLF, hf, equal, false) {}

    hash_set (const value_type* first,
              const value_type* last,
              size_type initSize      = 10007,
              float maxLF             = 1.1, 
              const HashFunction& hf  = HashFunction (),
              const KeyEqual& equal   = KeyEqual ())
    : ht (first, last, initSize, maxLF, hf, equal, false) {}

    //
    // copying, assignment, swap
    //
    hash_set (const hash_set<Key, HashFunction, KeyEqual>& x) 
    : ht (x.ht, false) {}

    hash_set<Key, HashFunction, KeyEqual>& 
    operator= (const hash_set<Key, HashFunction, KeyEqual>& x) 
    {
        ht = x.ht;
        return *this; 
    }

    void
    swap (hash_set<Key, HashFunction, KeyEqual>& x) { ht.swap (x.ht); }

    //
    // accessors:
    //
    key_equal        key_comp ()   const { return ht.key_comp (); }
    value_compare    value_comp () const { return ht.key_comp (); }
    
    hash_function    hash_funct () const { return ht.hash_funct (); }

    iterator         begin ()      const { return ht.begin ();      }
    iterator         end ()        const { return ht.end ();        }

    bool             empty ()      const { return ht.empty ();      }
    size_type        size ()       const { return ht.size ();       }
    size_type        max_size ()   const { return ht.max_size ();   }

    //
    // insert/erase
    //

    // typedef done to get around compiler bug
    typedef pair<iterator, bool> pair_iterator_bool; 

    pair_iterator_bool insert (const value_type& x) 
    {
        pair<typename rep_type::iterator, bool> p = ht.insert (x); 
        return pair<iterator, bool> (p.first, p.second);
    }
    
#ifdef MSIPL_MEMBER_TEMPLATE
   
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        for (InputIterator i = first; i != last; ++i)
            ht.insert (*i);
    }

#else

    void insert (iterator first, iterator last) 
    {
        ht.insert (first, last); 
    }

    void insert (const value_type* first, const value_type* last) 
    {
        ht.insert (first, last); 
    }

#endif

    void erase (iterator position)
    { ht.erase ((typename rep_type::iterator&)position); }

    size_type erase (const key_type& x) { return ht.erase (x);  }

    void erase (iterator first, iterator last)
    { 
	ht.erase ((typename rep_type::iterator&)first,
                  (typename rep_type::iterator&)last);
    }
   
    void clear  () { erase (begin (), end ()); }
 
    //
    // search operations:
    //
    iterator     find  (const key_type& x) const { return (ht.find (x));  }
    size_type    count (const key_type& x) const { return (ht.count (x)); }

    // typedef done to get around compiler bug
    typedef pair<iterator, iterator>  pair_iterator_iterator; 

    pair_iterator_iterator
    equal_range (const key_type& x) const { return ht.equal_range (x); }

    iterator   lower_bound (const key_type& x) const
    {
        return ht.lower_bound (x);
    }

    iterator upper_bound (const key_type& x) const
    {
        return ht.upper_bound (x);
    }

};

template <class Key, class HashFunction, class KeyEqual>
inline bool
operator== (const hash_set<Key, HashFunction, KeyEqual>& x, 
            const hash_set<Key, HashFunction, KeyEqual>& y) 
{
    return (x.size () == y.size () && equal (x.begin (), x.end (), y.begin ()));
}

template <class Key, class HashFunction, class KeyEqual>
inline bool
operator< (const hash_set<Key, HashFunction, KeyEqual>& x, 
            const hash_set<Key, HashFunction, KeyEqual>& y) 
{
    return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ());
}

#undef Allocator

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_HASH_SET_H */

//961210 bkoz added alignment wrapper
//961216 ah changed memory to mmemory