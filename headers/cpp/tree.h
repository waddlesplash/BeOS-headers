/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_TREE_H
#define MSIPL_TREE_H

/*

Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen,
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990),
except that

(1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin (), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union,
etc.);

(2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.

*/

#include <mcompile.h>

#include MOD_INCLUDE(algobase)
#include MOD_INCLUDE(functional)

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifndef rb_tree 
#define rb_tree rb_tree
#endif

#ifdef MSIPL_DEF_TEMPARG
template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator = allocator<Value> >
#else
template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator>
#endif
class rb_tree {

protected:

    enum color_type {red, black};

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<void>::other::pointer void_pointer;
#else
    typedef typename DefAllocator<void>::pointer             void_pointer;
#endif

    struct rb_tree_node;
    friend struct rb_tree_node;

    struct rb_tree_node {
        color_type color_field; 
        void_pointer parent_link;
        void_pointer left_link;
        void_pointer right_link;
        Value value_field;
    };

#ifdef MSIPL_MEMBER_TEMPLATE
    typename Allocator::rebind<rb_tree_node>::other rb_tree_node_allocator;
#else
             DefAllocator<rb_tree_node>             rb_tree_node_allocator;
#endif

    Allocator                                       value_allocator;

public:
    typedef          Key                            key_type;
    typedef          Value                          value_type;
    typedef          Allocator                      allocator_type;
    typedef typename Allocator::pointer             pointer;
    typedef typename Allocator::const_pointer       const_pointer;
    typedef typename Allocator::reference           reference;
    typedef typename Allocator::const_reference     const_reference;

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<rb_tree_node>::other  
                                                rb_tree_node_allocator_type;
#else
    typedef          DefAllocator<rb_tree_node> rb_tree_node_allocator_type;
#endif

    typedef typename rb_tree_node_allocator_type::pointer      link_type;
    typedef typename rb_tree_node_allocator_type::size_type    size_type;
    typedef typename rb_tree_node_allocator_type::difference_type 
                                                         difference_type;

protected:
    /*
    static size_type buffer_size ()
    {
        return  max (size_type (1),
                     size_type (4096/sizeof (rb_tree_node)));
    }
	*/
	
	//961210 for Efrem J. Sternbach, removed hard-wired buffer size
    static size_type buffer_size ()
    {
        DefAllocator<rb_tree_node> buffer_size_allocator;
        return  buffer_size_allocator.init_page_size();
    }

    struct rb_tree_node_buffer;
    friend struct rb_tree_node_buffer;

    struct rb_tree_node_buffer {
        void_pointer next_buffer;
        link_type buffer;
    };

public:

#ifdef MSIPL_MEMBER_TEMPLATE
    typedef typename Allocator::rebind<rb_tree_node_buffer>::other 
                                                       buffer_allocator_type;
#else
    typedef          DefAllocator<rb_tree_node_buffer> buffer_allocator_type;
#endif

    typedef typename buffer_allocator_type::pointer    buffer_pointer;

protected:

    buffer_allocator_type                 buffer_allocator;
    buffer_pointer                        buffer_list;
    link_type                             free_list;
    link_type                             next_avail;
    link_type                             last;

    DEC_OBJ_LOCK(_mutex)

    void add_new_buffer ()
    {
        buffer_pointer tmp = buffer_allocator.allocate ((size_type)1);
        tmp->buffer = rb_tree_node_allocator.allocate (buffer_size ());
        tmp->next_buffer = buffer_list;
        buffer_list = tmp;
        next_avail = buffer_list->buffer;
        last = next_avail + buffer_size ();
    }
    void deallocate_buffers ();
    link_type get_node ()
    {
        link_type tmp = free_list;
        return free_list ? 
                (free_list = (link_type) (free_list->right_link), tmp) 
                : (next_avail == last ? (add_new_buffer (), next_avail++) 
                   : next_avail++);
        // ugly code for inlining - avoids multiple returns
    }
    void put_node (link_type p)
    {
        p->right_link = free_list;
        free_list = p;
    }

protected:

    link_type       header;  

    link_type&      root ()            { return parent (header); }
    link_type&      root ()      const { return parent (header); }

    link_type&      leftmost ()        { return left (header);   }
    link_type&      leftmost ()  const { return left (header);   }

    link_type&      rightmost ()       { return right (header);  }
    link_type&      rightmost () const { return right (header);  }

    size_type       node_count;     // keeps track of size of tree
    bool            insert_always;  // controls whether an element
                                    // already in the tree is 
                                    // inserted again
    Compare             key_compare;

    static link_type    NIL;
#ifdef MSIPL_MULTITHREAD
    static mutex_arith<size_t, mutex>    number_of_trees;
#else
    static size_type                        number_of_trees;
#endif

    static link_type& left (link_type x)
    { 
        return (link_type&) ((*x).left_link);
    }
    static link_type& right (link_type x)
    {
        return (link_type&) ((*x).right_link); 
    }
    static link_type& parent (link_type x)
    {
        return (link_type&) ((*x).parent_link);
    }
    static reference value (link_type x) { return (*x).value_field; }
#ifdef MSIPL_MEMBER_TEMPLATE
    static typename Allocator::rebind<Key>::other::const_reference
#else
    static typename DefAllocator<Key>::const_reference
#endif 
    key (link_type x)
    {
        return KeyOfValue () (value (x));
    }
    static color_type& color (link_type x)
    {
        return (color_type&) (*x).color_field;
    }
    static link_type minimum (link_type x)
    {
        while (left (x) != NIL)
            x = left (x);
        return x;
    }
    static link_type maximum (link_type x)
    {
        while (right (x) != NIL)
            x = right (x);
        return x;
    }

public:

    class iterator;
    friend class iterator;
    class const_iterator;
    friend class const_iterator;
    class iterator
#ifdef MSIPL_USING_NAMESPACE
      : public std::iterator<bidirectional_iterator_tag,
                             Value, difference_type> 
#else
      //: public ::iterator<bidirectional_iterator_tag, Value, difference_type>
      : public ::global_iterator<bidirectional_iterator_tag, Value, difference_type>
#endif
    {
        friend class rb_tree<Key, Value, KeyOfValue,
                             Compare, Allocator>;
        friend class const_iterator;

    protected:

        link_type node;
        DEC_OBJ_LOCK(iter_mutex)
        iterator (link_type x) : node (x) {}

    public:

        iterator () {}
        ~iterator () { REMOVE(iter_mutex); }

        bool operator== (const iterator& y) const
	    { READ_LOCK(iter_mutex); return node == y.node; }

        bool operator== (const const_iterator& y) const
	    { READ_LOCK(iter_mutex); return node == y.node; }

        bool operator!= (const iterator& y) const
        { READ_LOCK(iter_mutex); return node != y.node; }

        bool operator!= (const const_iterator& y) const
        { READ_LOCK(iter_mutex); return node != y.node; }

        reference operator* () const 
          { READ_LOCK(iter_mutex); return value (node); }

        // Waiting for clarifications on this
        // pointer operator-> () const { return &(operator* ()); }
 
        iterator& operator++ ()
        {
            WRITE_LOCK(iter_mutex);
            if (right (node) != NIL)
            {
                node = right (node);
                while (left (node) != NIL)
                    node = left (node);
            } else
            {
                link_type y = parent (node);
                while (node == right (y))
                {
                    node = y;
                    y = parent (y);
                }
                if (right (node) != y) // necessary because of rightmost 
                    node = y;
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
            if (color (node) == red && parent (parent (node)) == node)  
                // check for header
                node = right (node);   // return rightmost
            else if (left (node) != NIL)
            {
                link_type y = left (node);
                while (right (y) != NIL)
                    y = right (y);
                node = y;
            } else
            {
                link_type y = parent (node);
                while (node == left (y))
                {
                    node = y;
                    y = parent (y);
                }
                node = y;
            }
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
      : public std::iterator<bidirectional_iterator_tag,
                             Value, difference_type> 
#else
      //: public ::iterator<bidirectional_iterator_tag, Value, difference_type>
      : public ::global_iterator<bidirectional_iterator_tag, Value, difference_type>
#endif
    {
        friend class rb_tree<Key, Value, KeyOfValue,
                             Compare, Allocator>;
        friend class iterator;

    protected:

        link_type node;
        DEC_OBJ_LOCK(citer_mutex)

        const_iterator (link_type x) : node (x) {}

    public:
        const_iterator () {}
        const_iterator (const iterator& x) : node (x.node) {}
        ~const_iterator () { REMOVE(citer_mutex); }

        bool operator== (const const_iterator& y) const
        { 
            READ_LOCK(citer_mutex);
            return node == y.node; 
        }
        bool operator!= (const const_iterator& y) const
        {
            READ_LOCK(citer_mutex);
            return node != y.node; 
        }
        const_reference operator* () const 
          { READ_LOCK(citer_mutex); return value (node); }
        // Waiting for clarifications on this
        // const_pointer operator-> () const { return &(operator* ()); }
        const_iterator& operator++ ()
        {
            WRITE_LOCK(citer_mutex);
            if (right (node) != NIL)
            {
                node = right (node);
                while (left (node) != NIL)
                    node = left (node);
            } else
            {
                link_type y = parent (node);
                while (node == right (y))
                {
                    node = y;
                    y = parent (y);
                }
                if (right (node) != y) // necessary because of rightmost 
                    node = y;
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
            if (color (node) == red && parent (parent (node)) == node)  
                // check for header
                node = right (node);   // return rightmost
            else if (left (node) != NIL)
            {
                link_type y = left (node);
                while (right (y) != NIL)
                    y = right (y);
                node = y;
            } else
            {
                link_type y = parent (node);
                while (node == left (y))
                {
                    node = y;
                    y = parent (y);
                }
                node = y;
            }
            return *this;
        }
        const_iterator operator-- (int)
        {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }
    };

    typedef reverse_bidirectional_iterator<iterator, value_type,
            reference, pointer, difference_type>         reverse_iterator; 

    typedef reverse_bidirectional_iterator<const_iterator, value_type,
            const_reference, const_pointer, difference_type>
                                                   const_reverse_iterator;

private:

    iterator    __insert (link_type x, link_type y, const value_type& v);
    link_type   __copy (link_type x, link_type p);
    void        __erase (link_type x);

    void init ()
    {
        ++number_of_trees;
        if (NIL == 0)
        {
            // NIL = get_node ();
            NIL = rb_tree_node_allocator.allocate((size_type)1);
            color (NIL) = black;
            parent (NIL) = 0;
            left (NIL) = 0;
            right (NIL) = 0;
        }
        header = get_node ();
        color (header) = red;  // used to distinguish header from root,
                              // in iterator.operator++
        root () = NIL;
        leftmost () = header;
        rightmost () = header;
    }
public:
 
    //
    // allocation/deallocation
    //
    rb_tree (const Compare& comp = Compare (), bool always = true, 
             const Allocator& alloc = Allocator ())
    : node_count (0), key_compare (comp), insert_always (always),
      free_list (0), buffer_list (0), next_avail (0), last (0),
      value_allocator(alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
      , rb_tree_node_allocator(alloc), buffer_allocator(alloc)
#endif
    {
        init ();
    }

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    rb_tree (InputIterator first, InputIterator last,
             const Compare& comp = Compare (), bool always = true,
             const Allocator& alloc = Allocator ())
    : node_count (0), key_compare (comp), insert_always (always),
      free_list (0), buffer_list (0), next_avail (0), last (0),
      value_allocator(alloc), rb_tree_node_allocator(alloc),
      buffer_allocator(alloc)
    { 
        init ();
        insert (first, last);
    }
#else
    rb_tree (const_iterator first, const_iterator last, 
             const Compare& comp = Compare (), bool always = true,
             const Allocator& alloc = Allocator ())
    : node_count (0), key_compare (comp), insert_always (always),
      free_list (0), buffer_list (0), next_avail (0), last (0),
      value_allocator(alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
      , rb_tree_node_allocator(alloc), buffer_allocator(alloc)
#endif
    { 
        init ();
        insert (first, last);
    }
    rb_tree (const value_type* first, const value_type* last, 
             const Compare& comp = Compare (), bool always = true,
             const Allocator& alloc = Allocator ())
    : node_count (0), key_compare (comp), insert_always (always),
      free_list (0), buffer_list (0), next_avail (0), last (0),
      value_allocator(alloc)
#ifdef MSIPL_MEMBER_TEMPLATE
      , rb_tree_node_allocator(alloc), buffer_allocator(alloc)
#endif
    { 
        init ();
        insert (first, last);
    }
#endif

    rb_tree (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, 
             bool always = true)
    : node_count (x.node_count), 
      key_compare (x.key_compare), insert_always (always),
      free_list (0), buffer_list (0), next_avail (0), last (0),
      value_allocator (x.value_allocator)
#ifdef MSIPL_MEMBER_TEMPLATE
      , rb_tree_node_allocator(x.rb_tree_node_allocator),
        buffer_allocator(x.buffer_allocator)
#endif
    { 
        ++number_of_trees;
        header = get_node ();
        color (header) = red;
        root () = __copy (x.root (), header);
        if (root () == NIL)
        {
            leftmost () = header;
            rightmost () = header;
        } else
        {
            leftmost () = minimum (root ());
            rightmost () = maximum (root ());
        }
    }
    ~rb_tree ()
    {
        erase (begin (), end ());
        put_node (header);
        if (--number_of_trees == 0)
        {
            // put_node (NIL);
            rb_tree_node_allocator.deallocate(NIL);
            NIL = 0;
        }
        deallocate_buffers ();
        free_list = 0;    
        next_avail = 0;
        last = 0;
        REMOVE(_mutex);
    }

    rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& 
    operator= (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x);

    allocator_type
    get_allocator () const
      { return value_allocator; }
    //
    // accessors:
    //
    Compare                key_comp () const 
      { READ_LOCK(_mutex); return key_compare; }
    iterator               begin    ()       
      { READ_LOCK(_mutex); return leftmost (); }
    const_iterator         begin    () const 
      { READ_LOCK(_mutex); return leftmost (); }
    iterator               end      ()       
      { READ_LOCK(_mutex); return header;      }
    const_iterator         end      () const 
      { READ_LOCK(_mutex); return header;      }

    reverse_iterator       rbegin ()
       { return reverse_iterator (end ());         }
    const_reverse_iterator rbegin () const
       { return const_reverse_iterator (end ());   }
    reverse_iterator       rend ()
       { return reverse_iterator (begin ());       }
    const_reverse_iterator rend () const
       { return const_reverse_iterator (begin ()); } 

    bool                   empty () const 
      { READ_LOCK(_mutex); return node_count == 0; }
    size_type              size () const 
     { READ_LOCK(_mutex); return node_count;      }
    size_type max_size () const
    {
        return rb_tree_node_allocator.max_size (); 
    }
    void swap (rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& t)
    {
        WRITE_LOCK(_mutex);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (header, t.header);
        std::swap (node_count, t.node_count);
        std::swap (insert_always, t.insert_always);
        std::swap (key_compare, t.key_compare);

        std::swap (rb_tree_node_allocator, t.rb_tree_node_allocator);
        std::swap (value_allocator, t.value_allocator);
        std::swap (buffer_allocator, t.buffer_allocator);
        std::swap (buffer_list, t.buffer_list);
        std::swap (free_list, t.free_list);
        std::swap (next_avail, t.next_avail);
        std::swap (last, t.last);
#else
        ::swap (header, t.header);
        ::swap (node_count, t.node_count);
        ::swap (insert_always, t.insert_always);
        ::swap (key_compare, t.key_compare);
        ::swap (rb_tree_node_allocator, t.rb_tree_node_allocator);
        ::swap (value_allocator, t.value_allocator);
        ::swap (buffer_allocator, t.buffer_allocator);
        ::swap (buffer_list, t.buffer_list);
        ::swap (free_list, t.free_list);
        ::swap (next_avail, t.next_avail);
        ::swap (last, t.last);
#endif
    }
    
    //
    // insert/erase
    //
    typedef  pair<iterator, bool> pair_iterator_bool; 
    // typedef done to get around compiler bug

    pair_iterator_bool insert (const value_type& x);

    iterator   insert (iterator position, const value_type& x);
#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void       insert (InputIterator first, InputIterator last);
#else
    void       insert (iterator first, iterator last);
    void       insert (const_iterator first, const_iterator last);
    void       insert (const value_type* first, const value_type* last);
#endif
    void       erase (iterator position);
    size_type  erase (const key_type& x);
    void       erase (iterator first, iterator last);
    void       erase (const key_type* first, const key_type* last);

    //
    // set operations:
    //
    iterator         find       (const key_type& x);
    const_iterator   find       (const key_type& x) const;
    size_type        count      (const key_type& x) const;

    iterator         lower_bound (const key_type& x);
    const_iterator   lower_bound (const key_type& x) const;
    iterator         upper_bound (const key_type& x);
    const_iterator   upper_bound (const key_type& x) const;

    typedef  pair<iterator, iterator> pair_iterator_iterator; 
    typedef  pair<const_iterator, const_iterator> pair_citerator_citerator; 

    pair_iterator_iterator   equal_range (const key_type& x);
    pair_citerator_citerator equal_range (const key_type& x) const;

    inline void rotate_left (link_type x);
    inline void rotate_right (link_type x);
};

#ifdef MSIPL_MULTITHREAD
template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator>
mutex_arith<size_t, mutex>
  rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::number_of_trees = 0;
#else
template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type 
  rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::number_of_trees = 0;
#endif

template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type 
        rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::NIL = 0;

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
inline
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
deallocate_buffers ()
{
    while (buffer_list)
    {
        buffer_pointer tmp = buffer_list;
        buffer_list = (buffer_pointer) (buffer_list->next_buffer);
        rb_tree_node_allocator.deallocate (tmp->buffer);
        buffer_allocator.deallocate (tmp);
    }
}

template <class Key, class Value, class KeyOfValue,
          class Compare, class Allocator>
inline bool 
operator== (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, 
            const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& y)
{
    return x.size () == y.size () &&
	   equal (x.begin (), x.end (), y.begin ());
}

template <class Key, class Value, class KeyOfValue, 
          class Compare, class Allocator>
inline bool 
operator< (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, 
           const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& y)
{
    return lexicographical_compare (x.begin (), x.end (),
				    y.begin (), y.end ());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
operator= (const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x)
{
    if (this != &x)
    {
        WRITE_LOCK(_mutex);
        // can't be done as in list because Key may be a constant type
        erase (begin (), end ());
        root () = __copy (x.root (), header);
        if (root () == NIL)
        {
            leftmost () = header;
            rightmost () = header;
        } else
        {
            leftmost () = minimum (root ());
            rightmost () = maximum (root ());
        }
        node_count = x.node_count;
    }
    return *this;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
__insert (link_type x, link_type y, const Value& v)
{
    ++node_count;
    link_type z = get_node ();
    construct (value_allocator.address (value (z)), v);
    if (y == header || x != NIL ||
         key_compare (KeyOfValue () (v), key (y)))
    {
        left (y) = z;      // also makes leftmost () = z when y == header
        if (y == header)
        {
            root () = z;
            rightmost () = z;
        } else if (y == leftmost ())
            leftmost () = z;   // maintain leftmost () pointing
                               // to minimum node
    } else
    {
        right (y) = z;
        if (y == rightmost ())
            rightmost () = z;  // maintain rightmost () pointing
                               // to maximum node
    }
    parent (z) = y;
    left (z) = NIL;
    right (z) = NIL;
    x = z;                    // recolor and rebalance the tree
    color (x) = red;
    while (x != root () && color (parent (x)) == red) 
        if (parent (x) == left (parent (parent (x))))
        {
            y = right (parent (parent (x)));
            if (color (y) == red)
            {
                color (parent (x)) = black;
                color (y) = black;
                color (parent (parent (x))) = red;
                x = parent (parent (x));
            } else
            {
                if (x == right (parent (x)))
                {
                    x = parent (x);
                    rotate_left (x);
                }
                color (parent (x)) = black;
                color (parent (parent (x))) = red;
                rotate_right (parent (parent (x)));
            }
        } else
        {
            y = left (parent (parent (x)));
            if (color (y) == red)
            {
                color (parent (x)) = black;
                color (y) = black;
                color (parent (parent (x))) = red;
                x = parent (parent (x));
            } else
            {
                if (x == left (parent (x)))
                {
                    x = parent (x);
                    rotate_right (x);
                }
                color (parent (x)) = black;
                color (parent (parent (x))) = red;
                rotate_left (parent (parent (x)));
            }
        }
    color (root ()) = black;
    return iterator (z);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::pair_iterator_bool
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert (const Value& v)
{
    WRITE_LOCK(_mutex);
    link_type y = header;
    link_type x = root ();
    bool comp = true;
    while (x != NIL)
    {
        y = x;
        comp = key_compare (KeyOfValue () (v), key (x));
        x = comp ? left (x) : right (x);
    }
    if (insert_always)
        return pair_iterator_bool (__insert (x, y, v), true);
    iterator j = iterator (y);   
    if (comp)
        if (j == begin ())     
            return pair_iterator_bool (__insert (x, y, v), true);
        else
            --j;
    if (key_compare (key (j.node), KeyOfValue () (v)))
        return pair_iterator_bool (__insert (x, y, v), true);
    return pair_iterator_bool (j, false);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>:: insert (iterator position, const Value& v)
{
    WRITE_LOCK(_mutex);
    if (position == iterator (begin ()))
        if (size () > 0 && 
            key_compare (KeyOfValue () (v), key (position.node)))
            return __insert (position.node, position.node, v);
            // first argument just needs to be non-NIL 
        else
            return insert (v).first;
    else if (position == iterator (end ()))
        if (key_compare (key (rightmost ()), KeyOfValue () (v)))
        {
            return __insert (NIL, rightmost (), v);
        }
        else
            return insert (v).first;
    else
    {
        iterator before = --position;
        if (key_compare (key (before.node), KeyOfValue () (v))
            && key_compare (KeyOfValue () (v), key (position.node)))
            if (right (before.node) == NIL)
                return __insert (NIL, before.node, v); 
            else
                return __insert (position.node, position.node, v);
                // first argument just needs to be non-NIL 
        else
            return insert (v).first;
    }
}

#ifdef MSIPL_MEMBER_TEMPLATE

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
template <class InputIterator>
void
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
insert (InputIterator first, InputIterator last)
{
    while (first != last) insert (*first++);
}

#else

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
insert (const_iterator first, const_iterator last)
{
    while (first != last) insert (*first++);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
insert (iterator first, iterator last)
{
    while (first != last) insert (*first++);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
insert (const Value* first, const Value* last)
{
    while (first != last) insert (*first++);
}

#endif /* MSIPL_MEMBER_TEMPLATE */
        
template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
erase (iterator position)
{
    link_type z = position.node;
    link_type y = z;
    link_type x;
    WRITE_LOCK(_mutex);
    if (left (y) == NIL)
        x = right (y);
    else
    {
        if (right (y) == NIL) 
            x = left (y);
        else
        {
            y = right (y);
            while (left (y) != NIL)
                y = left (y);
            x = right (y);
        }
    }
    if (y != z)          // relink y in place of z
    {
        parent (left (z)) = y; 
        left (y) = left (z);
        if (y != right (z))
        {
            parent (x) = parent (y); // possibly x == NIL
            left (parent (y)) = x;   // y must be a left child
            right (y) = right (z);
            parent (right (z)) = y;
        } else
            parent (x) = y;  // needed in case x == NIL
        if (root () == z)
            root () = y;
        else if (left (parent (z)) == z)
            left (parent (z)) = y;
        else 
            right (parent (z)) = y;
        parent (y) = parent (z);
#ifdef MSIPL_USING_NAMESPACE
        std::swap (color (y), color (z));
#else
        ::swap (color (y), color (z));
#endif
        y = z;
                       // y points to node to be actually deleted,
                       // ::swap (y, z);  
                       // z points to old z's former successor
    } 
    else             // y == z
    {
        parent (x) = parent (y);   // possibly x == NIL
        if (root () == z)
            root () = x;
        else 
            if (left (parent (z)) == z)
                left (parent (z)) = x;
            else
                right (parent (z)) = x;
        if (leftmost () == z) 
            if (right (z) == NIL)  // left (z) must be NIL also
                leftmost () = parent (z);
                // makes leftmost () == header if z == root ()
        else
            leftmost () = minimum (x);
        if (rightmost () == z)  
            if (left (z) == NIL) // right (z) must be NIL also
                rightmost () = parent (z);  
                // makes rightmost () == header if z == root ()
        else  // x == left (z)
            rightmost () = maximum (x);
    }
    if (color (y) != red)
    { 
        while (x != root () && color (x) == black)
            if (x == left (parent (x)))
            {
                link_type w = right (parent (x));
                if (color (w) == red)
                {
                    color (w) = black;
                    color (parent (x)) = red;
                    rotate_left (parent (x));
                    w = right (parent (x));
                }
                if (color (left (w)) == black && color (right (w)) == black)
                {
                    color (w) = red;
                    x = parent (x);
                } else
                {
                    if (color (right (w)) == black)
                    {
                        color (left (w)) = black;
                        color (w) = red;
                        rotate_right (w);
                        w = right (parent (x));
                    }
                    color (w) = color (parent (x));
                    color (parent (x)) = black;
                    color (right (w)) = black;
                    rotate_left (parent (x));
                    break;
                }
            } else // same as then clause with "right" and "left" exchanged
            {
                link_type w = left (parent (x));
                if (color (w) == red)
                {
                    color (w) = black;
                    color (parent (x)) = red;
                    rotate_right (parent (x));
                    w = left (parent (x));
                }
                if (color (right (w)) == black && color (left (w)) == black)
                {
                    color (w) = red;
                    x = parent (x);
                } else
                {
                    if (color (left (w)) == black)
                    {
                        color (right (w)) = black;
                        color (w) = red;
                        rotate_left (w);
                        w = left (parent (x));
                    }
                    color (w) = color (parent (x));
                    color (parent (x)) = black;
                    color (left (w)) = black;
                    rotate_right (parent (x));
                    break;
                }
            }
        color (x) = black;
    }
    destroy (value_allocator.address (value (y)));
    put_node (y);
    --node_count;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue,
        Compare, Allocator>::size_type 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
erase (const Key& x)
{
    pair_iterator_iterator p = equal_range (x);
    size_type n = distance (p.first, p.second);
    erase (p.first, p.second);
    return n;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
__copy (link_type x, link_type p)
{
   // structural copy
   link_type r = x;
   while (x != NIL)
   {
      link_type y = get_node ();
      if (r == x) r = y;  // save for return value
      construct (value_allocator.address (value (y)), value (x));
      left (p) = y;
      parent (y) = p;
      color (y) = color (x);
      right (y) = __copy (right (x), y);
      p = y;
      x = left (x);
   }
   left (p) = NIL;
   return r;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
__erase (link_type x)
{
    // erase without rebalancing
    while (x != NIL)
    {
       __erase (right (x));
       link_type y = left (x);
       destroy (value_allocator.address (value (x)));
       put_node (x);
       x = y;
    }
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
erase (iterator first, iterator last)
{
    WRITE_LOCK(_mutex);
    if (first == begin () && last == end () && node_count != 0)
    {
        __erase (root ());
        leftmost () = header;
        root () = NIL;
        rightmost () = header;
        node_count = 0;
    } else
        while (first != last) erase (first++);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
erase (const Key* first, const Key* last)
{
    while (first != last) erase (*first++);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
find (const Key& k)
{
   READ_LOCK(_mutex);
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root (); /* Current node. */

   while (x != NIL)
     if (!key_compare (key (x), k))
       y = x, x = left (x);
   else
       x = right (x);
 
   iterator j = iterator (y);
   return (j == end () || key_compare (k, key (j.node))) ? end () : j;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
find (const Key& k) const
{
   READ_LOCK(_mutex);
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root (); /* Current node. */
  
   while (x != NIL)
   {
     if (!key_compare (key (x), k))
       y = x, x = left (x);
   else
       x = right (x);
   }
   const_iterator j = const_iterator (y);
   return (j == end () || key_compare (k, key (j.node))) ? end () : j;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
count (const Key& k) const
{
    pair<const_iterator, const_iterator> p = equal_range (k);
    size_type n = distance (p.first, p.second);
    return n;
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
lower_bound (const Key& k)
{
   READ_LOCK(_mutex);
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root (); /* Current node. */
 
   while (x != NIL)
     if (!key_compare (key (x), k))
       y = x, x = left (x);
     else
       x = right (x);
 
   return iterator (y);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
lower_bound (const Key& k) const
{
   READ_LOCK(_mutex);
   link_type y = header; /* Last node which is not less than k. */
   link_type x = root (); /* Current node. */
 
   while (x != NIL)
     if (!key_compare (key (x), k))
       y = x, x = left (x);
     else
       x = right (x);
 
   return const_iterator (y);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
upper_bound (const Key& k)
{
  READ_LOCK(_mutex);
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root (); /* Current node. */
 
   while (x != NIL)
     if (key_compare (k, key (x)))
       y = x, x = left (x);
     else
       x = right (x);
 
   return iterator (y);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
upper_bound (const Key& k) const
{
  READ_LOCK(_mutex);
  link_type y = header; /* Last node which is greater than k. */
  link_type x = root (); /* Current node. */
 
   while (x != NIL)
     if (key_compare (k, key (x)))
       y = x, x = left (x);
     else
       x = right (x);
 
   return const_iterator (y);
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue,Compare, Allocator>::pair_iterator_iterator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range (const Key& k)
{
    return pair_iterator_iterator (lower_bound (k), upper_bound (k));
}

template <class Key, class Value, class KeyOfValue,class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::pair_citerator_citerator 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range (const Key& k) const
{
    return pair_citerator_citerator (lower_bound (k), upper_bound (k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
rotate_left (link_type x)
{
    WRITE_LOCK(_mutex);
    link_type y = right (x);
    right (x) = left (y);
    if (left (y) != NIL)
        parent (left (y)) = x;
    parent (y) = parent (x);
    if (x == root ())
        root () = y;
    else if (x == left (parent (x)))
        left (parent (x)) = y;
    else
        right (parent (x)) = y;
    left (y) = x;
    parent (x) = y;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void 
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rotate_right (link_type x)
{
    WRITE_LOCK(_mutex);
    link_type y = left (x);
    left (x) = right (y);
    if (right (y) != NIL)
        parent (right (y)) = x;
    parent (y) = parent (x);
    if (x == root ())
        root () = y;
    else if (x == right (parent (x)))
        right (parent (x)) = y;
    else
        left (parent (x)) = y;
    right (y) = x;
    parent (x) = y;
}

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_TREE_H */

//961120 bkoz line 240, 340 changed iterator to global_iterator
//961210 bkoz added alignment wrapper
//970214 bkoz line 114 added non-hardwared buffer_size() implementation
