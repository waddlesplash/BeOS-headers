/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_HASH_TABLE_H
#define MSIPL_HASH_TABLE_H

#include <mcompile.h>

#include MOD_C_INCLUDE(stdlib)
#include MOD_INCLUDE(hashfun)             /* mm 970905 */
#include MOD_INCLUDE(iosfwd)
#include MOD_INCLUDE(iterator)
#include MOD_INCLUDE(functional)
#include MOD_INCLUDE(algobase)
#include MOD_INCLUDE(vector)
#include MOD_INCLUDE(slist)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
class hash_table {
public:
    class iterator;
    class const_iterator;
    
    friend class iterator;
    friend class const_iterator;
    
    typedef long size_type;
    typedef Key key_type;
    typedef Value value_type;
    typedef HashFunction hash_function;
    typedef KeyOfValue key_value;

//protected:

    class bucket : public slist<value_type, allocator<value_type> >
    {
    friend class hash_table<Key,Value,KeyOfValue,HashFunction,KeyEqual>;

    public:
        typedef slist<value_type, allocator<value_type> >   slist_type;
        typedef typename slist_type::iterator               iterator;
        typedef typename slist_type::const_iterator         const_iterator;
        typedef typename slist_type::size_type              size_type; 
        typedef typename slist_type::reference              reference;
        typedef typename slist_type::const_reference        const_reference;
        typedef typename slist_type::difference_type        difference_type;
        
        long next_;  // Next non-empty bucket
        long prev_;  // Previous non-empty bucket
       
        bucket () : next_ (-1), prev_ (-1) {}
    };
    // end class bucket

    friend ostream& operator<< (ostream& o, const bucket& b);

public:

    typedef typename bucket::difference_type difference_type;
    typedef          value_type&             reference;
    typedef          const value_type&       const_reference;
    typedef          value_type*             pointer;
    typedef          const value_type*       const_pointer;
  
    class iterator 
#ifdef MSIPL_USING_NAMESPACE
    : public std::iterator <forward_iterator_tag, Value, difference_type>
#else
   // : public ::iterator <forward_iterator_tag, Value, difference_type>
    : public ::global_iterator <forward_iterator_tag, Value, difference_type>
#endif
    {
        friend class hash_table<Key, Value, KeyOfValue,
                                HashFunction, KeyEqual>;
        friend class const_iterator;
  
    protected:
        hash_table<Key, Value, KeyOfValue,HashFunction, KeyEqual>*  ht_; 
  	// hast table to which the iterator is pointing 
        bucket::iterator  ptr_;
        // Pointer to the current element in the bucket
  
    private:
        size_type currBucket () { return  (*ht_).S (key_value() (*ptr_)); }
   
        iterator (hash_table<Key, Value, KeyOfValue, HashFunction,
                             KeyEqual>*  ht, bucket::iterator ptr)
        :  ht_ (ht), ptr_ (ptr) { }
  
    public:
        iterator (const iterator& rhs)
        :  ht_ (rhs.ht_), ptr_ (rhs.ptr_) { }
    
        iterator () : ht_ (0),  ptr_ (0) { }
    
        iterator& operator= (const iterator& rhs) 
        {
            ptr_=rhs.ptr_;
            return *this;
        }
    
        ~iterator () {}
    
        friend bool
        operator== (const iterator& lhs, const iterator& rhs) 
        {
           return (lhs.ptr_ == rhs.ptr_); 
        }
    
        bool operator== (const iterator& rhs) 
        {
           return (ptr_ == rhs.ptr_);   
        }
  
    /*
        friend bool operator!= (const iterator& lhs, const iterator& rhs) 
        {
           return ! (lhs == rhs);
        }
    */
  
        reference operator*() { return *ptr_; }

        // Waiting for clarifications on this
        // pointer operator-> () const { return & (operator* ()); }
 
        iterator& operator++ () 
        {
            typename bucket::iterator tmp = ptr_;
            ++tmp;
            bucket& cb =  (*ht_).buckets_[currBucket ()];
            if  (tmp == cb.end () && cb.next_ != -1)
                ptr_ =  (*ht_).buckets_[cb.next_].begin ();
            else
                ptr_ = tmp;
            return *this;
        }
    
        iterator operator++ (int) 
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
    };   // end class iterator
  
    class const_iterator 
#ifdef MSIPL_USING_NAMESPACE
    : public std::iterator <forward_iterator_tag, Value, difference_type>
#else
    //: public ::iterator <forward_iterator_tag, Value, difference_type>
    : public ::global_iterator <forward_iterator_tag, Value, difference_type>
#endif
    { 

        friend class hash_table<Key, Value, KeyOfValue,
                                HashFunction, KeyEqual>;
        friend class iterator;
  
    protected:

        const hash_table<Key, Value, KeyOfValue,
                         HashFunction, KeyEqual>*  ht_; 
  	// HT to which the const_iterator is pointing 

        bucket::const_iterator ptr_;
        // Pointer to current element in the bucket

    private:

        size_type currBucket () { return  (*ht_).S (key_value () (*ptr_)); }
  
    public:

        const_iterator (const hash_table<Key, Value, KeyOfValue,
                        HashFunction, KeyEqual>*  ht, 
                        bucket::const_iterator ptr)
        : ht_ (ht), ptr_ (ptr) { }
  
        const_iterator (const const_iterator& rhs) 
        :  ht_ (rhs.ht_), ptr_ (rhs.ptr_) { }
    
        const_iterator (const iterator& rhs) 
        :  ht_ (rhs.ht_), ptr_ (rhs.ptr_) { }
    
        const_iterator () : ht_ (0),  ptr_ (0) { }
    
        const_iterator& operator= (const const_iterator& rhs) 
        {
            ptr_=rhs.ptr_;
            return (*this);
        }
    
        ~const_iterator () {}
    
        friend bool operator== (const const_iterator& lhs, 
                                const const_iterator& rhs)
        { 
    	    return (lhs.ptr_ == rhs.ptr_); 
        }
    
        bool operator== (const const_iterator& rhs)
        {
            return (ptr_ == rhs.ptr_);   
        }
    
    /*    friend bool operator!= (const const_iterator& lhs, 
                                  const const_iterator& rhs)
          {
              return ! (lhs == rhs);
          }
    */

        const_reference operator*() { return *ptr_; }

        // Waiting for clarifications on this
        // const_pointer operator-> () const { return & (operator* ()); }
 
        const_iterator& operator++ ()
        {
            bucket::const_iterator tmp = ptr_;
            ++tmp;
            const bucket& cb =  (*ht_).buckets_[currBucket ()];
            if  (tmp == cb.end () && cb.next_ != -1)
               ptr_ =  (*ht_).buckets_[cb.next_].begin ();
            else
               ptr_ = tmp;
            return *this;
        }
    
        const_iterator operator++ (int) 
        {
             const_iterator tmp = *this;
             ++*this;
             return tmp;
        }
  
    };  // end class const_iterator
  
    typedef pair<iterator, bool>                 pair_iterator_bool;
    typedef pair<iterator, iterator>             pair_iterator_iterator;
    typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
  
private:

    long S (const key_type& k) const;
    void expand ();
    void contract ();
    void merge (size_type bucketNumber); 
    void split (size_type bucketNumber);
 
    void eraseNeb (bucket& b, size_type bNumber); 
    void insertNeb (bucket& b, size_type bNumber); 
 
protected:

    HashFunction  hf_;        // Actual hash function being used
 
    KeyEqual      eql_;       // Function object used to compare keys
    bool          insertAlways_; 
 	                      // True if duplicates should be inserted,
                              // false otherwise
    size_type  elementCount_; // Keeps track of the # of elements
    size_type  totBuckets_;   // # of buckets allocated
    size_type  usedBuckets_;  // # of buckets actually being used 
    float      maxLF_;        // LF that triggers expansion
    float      minLF_;        // LF that triggers contraction    
    long  firstNeb_;          // First non-empty bucket, -1 if empty ()
    long lastNebIns_;         // last bucket that became a non-empty
                              //  bucket, -1 if empty ()
    vector<bucket, allocator<bucket> > buckets_;  // Where the elements 
                                                  // are actually stored

public:
    //
    // allocation - deallocation    
    //
    hash_table (size_type initSize,
                float maxLF                    = 1.5,   
                const HashFunction& hf         = HashFunction (),
                const KeyEqual& equal          = KeyEqual (),
                bool always                    = true);
    
    hash_table (const value_type* first,
                const value_type* last, 
                size_type initSize,
                float maxLF            = 1.5, 
                const HashFunction& hf = HashFunction (), 
                const KeyEqual& equal  = KeyEqual (),
                bool always            = true);
    //
    // copying, assignment, swap
    //
    hash_table (const hash_table<Key, value_type, KeyOfValue, 
                                 HashFunction, KeyEqual>& other, 
                bool always = true);
    
    hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>& 
    operator= (const hash_table<Key, value_type, KeyOfValue, 
                                HashFunction, KeyEqual>& other);
    
    void swap (hash_table<Key, Value, KeyOfValue, 
                         HashFunction, KeyEqual>& other);
    
    //
    // accessors
    //
    // Not in the HP-Implementation
    KeyEqual           key_comp ()    const { return eql_;             }
    hash_function      hash_funct ()  const { return hf_;              }
    size_type          bucketCount () const { return  (usedBuckets_);  }
    size_type          size ()        const { return  (elementCount_); }

    size_type          max_size ()    const
    { 
        return slist<value_type, allocator<value_type> > ().max_size ();
    }

    bool               empty ()       const { return  (size () == 0); }

    float              loadFactor ()  const
    { 
        return  (size () == 0 ? 0 :  (float)size () / bucketCount ()); 
    }

    size_type count (const key_type& k) const;
    
    //
    // insert - erase
    //
    pair_iterator_bool insert (const value_type& v)
    {
        size_type hash_value = S (KeyOfValue () (v));
        bucket&   b          = buckets_[hash_value];
        bucket::iterator p;

        for  (p = b.begin (); p != b.end (); ++p)
             // if  (eql_ (KeyOfValue () (*p), v))
             if (eql_ (KeyOfValue () (*p), KeyOfValue () (v)))
      	break;
      
        bucket::iterator where = p;
        bool inserted = false;

        if  (b.empty ())
            insertNeb (b, hash_value);

        if  (p == b.end () || insertAlways_) {
            if  (p == b.end ()) {
      	 b.push_front (v);
      	 where = b.begin ();
            }
            else {
      	 bucket::iterator previous = p++;
      	 where = b.insert (previous, p, v);
            }      
            inserted = true;
            elementCount_++;
            if  (loadFactor () > maxLF_)
      	  expand (); 
        }
        return pair<iterator, bool> (iterator (this, where), inserted);
    }
	
#ifdef MSIPL_MEMBER_TEMPLATE

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last);

#else

    void insert (const_iterator first, const_iterator last);
    void insert (const value_type* first,  const value_type* last);

#endif

    void      erase (iterator position);
    size_type erase (const key_type& k);
    void      erase (iterator first, iterator last);
    
    //
    // set operations
    //
    iterator       find (const key_type& k);
    const_iterator find (const key_type& k) const;
    
    //
    // iterators
    //
    iterator       begin ();
    const_iterator begin () const;
    iterator       end ();
    const_iterator end () const;

    pair_iterator_iterator   equal_range (const key_type& k);
    pair_citerator_citerator equal_range (const key_type& k) const;

    iterator       lower_bound (const key_type& k);
    const_iterator lower_bound (const key_type& k) const;

    iterator       upper_bound (const key_type& k);
    const_iterator upper_bound (const key_type& k) const;

};  // end class hash_table;

//961217 bkoz
#ifndef MSIPL_PARTIAL_TEMPL
//1
typedef pair<const int, int> pair_cii;
typedef select1st< pair_cii, int> select1st_pi;
typedef hash_table<int, pair_cii, select1st_pi, hash_fun0, equal_to<int> > hash_table_splz1;

null_template
struct iterator_trait <const hash_table_splz1::bucket*> {
    typedef ptrdiff_t                    	distance_type;
    typedef hash_table_splz1::bucket         value_type;
    typedef random_access_iterator_tag   	iterator_category;
};

//2
typedef pair<const int, char> pair_cic;
typedef select1st<pair_cic, int> select1st_pc;
typedef hash_table<int, pair_cic, select1st_pc, hash_fun0, equal_to<int> > hash_table_splz2;

null_template
struct iterator_trait <const hash_table_splz2::bucket*> {
    typedef ptrdiff_t                    	distance_type;
    typedef hash_table_splz2::bucket         value_type;
    typedef random_access_iterator_tag   	iterator_category;
};

//3
typedef hash_table<char, char, ident<char, char>, hash_fun0, greater<char> > hash_table_splz3;

null_template
struct iterator_trait <const hash_table_splz3::bucket*> {
    typedef ptrdiff_t                    	distance_type;
    typedef hash_table_splz3::bucket         value_type;
    typedef random_access_iterator_tag   	iterator_category;
};

//4
typedef hash_table<int, int, ident<int, int>, hash_fun0, equal_to<int> > hash_table_splz4;

null_template
struct iterator_trait <const hash_table_splz4::bucket*> {
    typedef ptrdiff_t                    	distance_type;
    typedef hash_table_splz4::bucket         value_type;
    typedef random_access_iterator_tag   	iterator_category;
};

//5
typedef pair<const int, basic_string<char, char_traits<char>, allocator<char> > > pair_is;
typedef select1st<pair_is, int> select1st_pisi;
typedef hash_table<int, pair_is, select1st_pisi, hash_fun0, equal_to<int> > hash_table_splz5;

null_template
struct iterator_trait <const hash_table_splz5::bucket*> {
    typedef ptrdiff_t                    	distance_type;
    typedef hash_table_splz5::bucket         value_type;
    typedef random_access_iterator_tag   	iterator_category;
};

#endif
//end bkoz

//
// allocation - deallocation
//
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
hash_table (size_type initSize,
            float maxLF,
            const HashFunction& hf,
            const KeyEqual& equal,
            bool always) 
:   hf_ (hf), 
//  eql_ (KeyEqual ()), 
    eql_ (equal), 
    insertAlways_ (always), 
    elementCount_ (0), 
    totBuckets_ (initSize), 
    usedBuckets_ (initSize), 
    maxLF_ (maxLF), 
    minLF_ (0.0), 
    buckets_ (initSize), 
    firstNeb_ (-1), 
    lastNebIns_ (-1) { hf_ = hf; }

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
hash_table (const value_type* first, const value_type* last,
            size_type initSize, float maxLF, const HashFunction& hf,
            const KeyEqual& equal, bool always) 
:   hf_ (hf), 
//  eql_ (KeyEqual ()), 
    eql_ (equal),
    insertAlways_ (always), 
    elementCount_ (0), 
    totBuckets_ (initSize), 
    usedBuckets_ (initSize), 
    maxLF_ (maxLF), 
    minLF_ (0.0), 
    buckets_ (initSize), 
    firstNeb_ (-1), 
    lastNebIns_ (-1) { insert (first, last); }

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
hash_table (const hash_table<Key, Value, KeyOfValue, HashFunction,
                             KeyEqual>& other, bool always)
:   hf_ (other.hf_), 
    eql_ (other.eql_), 
    insertAlways_ (always), 
    elementCount_ (other.elementCount_), 
    totBuckets_ (other.totBuckets_), 
    usedBuckets_ (other.usedBuckets_), 
    maxLF_ (other.maxLF_), 
    minLF_ (other.minLF_), 
    buckets_ (other.buckets_), 
    firstNeb_ (other.firstNeb_), 
    lastNebIns_ (other.lastNebIns_)
{
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline operator== (
   const hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>& lhs,
   const hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>& rhs
                  )
{
    return (lhs.buckets_ == rhs.buckets_);
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
	  class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>&
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
operator= (const hash_table<Key, Value, KeyOfValue, 
                            HashFunction, KeyEqual>& other)
{
    hf_            = other.hf_;
    eql_           = other.eql_;
    elementCount_  = other.elementCount_;
    totBuckets_    = other.totBuckets_;
    usedBuckets_   = other.usedBuckets_;
    maxLF_         = other.maxLF_;
    minLF_         = other.minLF_;
    buckets_       = other.buckets_;
    firstNeb_      = other.firstNeb_;
    lastNebIns_    = other.lastNebIns_;

    return *this;
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
swap (hash_table<Key, Value, KeyOfValue,
                 HashFunction, KeyEqual>& other)
{
#ifdef MSIPL_USING_NAMESPACE
    std::swap (hf_, other.hf_);
    std::swap (eql_, other.eql_);
    std::swap (insertAlways_, other.insertAlways_);
    std::swap (elementCount_, other.elementCount_);
    std::swap (totBuckets_, other.totBuckets_);
    std::swap (usedBuckets_, other.usedBuckets_);
    std::swap (maxLF_, other.maxLF_);
    std::swap (minLF_, other.minLF_);
    std::swap (firstNeb_, other.firstNeb_);
    std::swap (lastNebIns_, other.lastNebIns_);
#else
    ::swap (hf_, other.hf_);
    ::swap (eql_, other.eql_);
    ::swap (insertAlways_, other.insertAlways_);
    ::swap (elementCount_, other.elementCount_);
    ::swap (totBuckets_, other.totBuckets_);
    ::swap (usedBuckets_, other.usedBuckets_);
    ::swap (maxLF_, other.maxLF_);
    ::swap (minLF_, other.minLF_);
    ::swap (firstNeb_, other.firstNeb_);
    ::swap (lastNebIns_, other.lastNebIns_);
#endif
    buckets_.swap (other.buckets_);
}

//
// Accessors
//
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::size_type
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
count (const key_type& k) const 
{
    pair_citerator_citerator pii = equal_range (k);
    size_type n = 0;

    for (const_iterator p = pii.first; p != pii.second; ++p) 
        n++;

    return n;
}


//
// insert - erase
//
#ifdef MSIPL_MEMBER_TEMPLATE
 
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
template <class InputIterator>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
insert (InputIterator first, InputIterator last)
{ 
    while (first != last) 
        insert (*first++);
}
 
#else

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
void 
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
insert (const_iterator first, const_iterator last)
{
    for (const_iterator p = first; p != last; ++p)
        insert (*p);
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
insert (const value_type* first, const value_type* last)
{
    while (first != last)
        insert (*(first++));
}

#endif

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
erase (iterator position)
{
    long hash_value = S (KeyOfValue () ((*position.ptr_)));
    bucket& b = buckets_[hash_value];
    b.erase (position.ptr_);
    --elementCount_;
    if  (loadFactor () < minLF_)
        contract ();
    else if  (b.empty ())
        eraseNeb (b, hash_value);
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::size_type
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
erase (const key_type& k)
{
    pair_iterator_iterator pii = equal_range (k);
    size_type n = 0;

    for (iterator p = pii.first; p != pii.second; ++n) 
        erase (p++);

    return n;
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
erase (iterator first, iterator last)
{
    while  (first != last) erase (first++);
}

// Search Operations

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
find (const key_type& k) 
{
    size_type hash_value = S (k);
    bucket& b = buckets_[hash_value];

    for (bucket::iterator p = b.begin (); p != b.end (); ++p)
       if  (eql_ (KeyOfValue () (*p), k))
	   return iterator (this, p);

    return end ();
}


template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::const_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
find (const key_type& k) const
{
    size_type hash_value = S (k);
    const bucket& b = buckets_[hash_value];

    for  (bucket::const_iterator p = b.begin (); p != b.end (); ++p)
       if  (eql_ (KeyOfValue () (*p), k))
	   return const_iterator (this, p);

    return end ();
}

//
// accessors
//
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
begin ()
{
    if  (!empty ())
        return iterator (this, buckets_[firstNeb_].begin ());
    else
        return end ();
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::const_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
begin () const
{
    if  (!empty ())
        return const_iterator (this, buckets_[firstNeb_].begin ());
    else
        return end ();
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
end ()
{
    return iterator (this, bucket::iterator (NULL));
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::const_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
end () const
{
    return const_iterator (this, bucket::const_iterator (NULL));
}

template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue,
           HashFunction, KeyEqual>::pair_iterator_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
equal_range (const key_type& k)
{
    return pair_iterator_iterator (lower_bound (k), upper_bound (k));
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue,
           HashFunction, KeyEqual>::pair_citerator_citerator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
equal_range (const key_type& k) const
{
    return pair_citerator_citerator (lower_bound (k), upper_bound (k));
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
lower_bound (const key_type& k)
{
    return find (k);
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::const_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
lower_bound (const key_type& k) const
{
    return find (k);
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
upper_bound (const key_type& k)
{
    iterator p = find (k);

    while  (p != end () && eql_ (KeyOfValue () (*p), k))
        ++p;

    return p;
}

template <class Key, class Value, class KeyOfValue, class HashFunction,
          class KeyEqual>
inline
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::const_iterator 
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
upper_bound (const key_type& k) const
{
    const_iterator p = find (k);

    while  (p != end () && eql_ (KeyOfValue () (*p), k))
        ++p;

    return p;
}

//
// Private methods
//

// Function that maps the hash function into the size of the table
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
long  
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
S (const key_type& k) const
{
    long hv = hf_ (k) % totBuckets_;
  
    if (hv >= usedBuckets_)
        return hv - (totBuckets_ >> 1);
    else
        return hv;
}


template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
contract () 
{
    --usedBuckets_;
    merge (usedBuckets_);
    if (usedBuckets_ < (totBuckets_ >> 1)) {
        totBuckets_ /= 2;
    }
}

// If maxLoadFactor > 1, just by adding one slot the new load
// factor will be within the limits
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
expand () 
{
    usedBuckets_++;
    if (usedBuckets_ > totBuckets_)
        totBuckets_ *= 2;
    if  (usedBuckets_ > buckets_.size ()) {
        bucket::separate_copy (false); 
          // if push_back causes relocation, 
          // lists in buckets will not be copied
        { 
  	buckets_.push_back (bucket ()); 
        } // these braces limit extent of temporary bucket (), 
          // causing it not to be erased, as would happen if its
          // extent included next statement
        bucket::separate_copy (true);  // restore normal copying of lists
    }
    split (usedBuckets_-1);
}

// Merge entries from bucket btm to bucket (btm - totBuckets/2)
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
merge (long btm) 
{
    long     target = btm - (totBuckets_ >> 1);
    bucket&  bBtm = buckets_[btm];
    bucket&  bTarget = buckets_[target];
  
    if  (!bBtm.empty ()) {
        bTarget.splice (bBtm);
        eraseNeb (bBtm, btm); 
    } 
}

// Move some elements from bucket (target - totBuckets_/2) 
// to bucket target
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
split (long target) 
{
    long             bts     = target - (totBuckets_ >> 1);
    bucket&          bBts    = buckets_[bts];
    bucket&          bTarget = buckets_[target];

    bucket::iterator p (bBts.begin ());
  
    if  (!bBts.empty ()) {
        // Note placement of p++ in following code; this allows p to
        // be properly advanced before node referred to by p is moved
        while  (p != bBts.end ())
  	  if  (S (KeyOfValue () (*p)) != bts)
  	       // ++ must be done here while p is still valid
  	       bTarget.splice (bBts, p++);
  	  else
  	       ++p;
  
        // Update list of non-empty buckets
        if (bBts.empty ())
  	  eraseNeb (bBts, bts);
        if  (!bTarget.empty ())
  	  insertNeb (bTarget, target);
    }
}

// Functions for maintaining list of non-empty buckets

// Eliminate bucket b from the list of non-empty buckets
// Precondition: b is a non-empty bucket (i.e b.next_ != -1)
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
eraseNeb (bucket& b, size_type bNumber) 
{
    if (b.prev_ != -1)
        buckets_[b.prev_].next_ = b.next_;
    if (b.next_ != -1)
        buckets_[b.next_].prev_ = b.prev_;
    if (bNumber == firstNeb_) 
        firstNeb_ = b.next_;
    if (bNumber == lastNebIns_)
        lastNebIns_ = (b.prev_ != -1 ? b.prev_ : b.next_);
    b.next_ = b.prev_ = -1;  
}

// Insert bucket b in the list of non-empty buckets
// Precondition: b doesn't belong to the list of non-empty buckets, 
//               i.e. b.next_ == -1
template <class Key, class Value, class KeyOfValue, class HashFunction, 
          class KeyEqual>
inline
void
hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual>::
insertNeb (bucket& b, size_type bNumber) 
{
    if (firstNeb_ != -1)   // The hash_table is not empty
    {
        buckets_[lastNebIns_].next_ = bNumber;
        b.prev_ = lastNebIns_;
    } else 
        firstNeb_ = bNumber;
    lastNebIns_ = bNumber;
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_HASH_TABLE_H */

/* Change record
 * 961210 bkoz added alignment wrapper
 * 961120 bkoz line 77, 158 changed iterator to global_iterator
 * 961217 bkoz line 416-460 added iterator_traits specialization
 * mm 970905  Added include of hashfun to declare hash_fun0
 */
