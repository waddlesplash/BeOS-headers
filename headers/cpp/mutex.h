/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_MUTEX_H
#define MSIPL_MUTEX_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

class null_mutex {

public:

    inline null_mutex () {}
    inline ~null_mutex () {}
    inline int remove () const { return 0; }
    inline int acquire (int = 0) const { return 0; }
    inline int release () const { return 0; }

};

#ifdef MSIPL_USING_NAMESPACE
}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#ifdef MSIPL_MULTITHREAD
//
// Macros to be checked. These may have to be corrected.
//
#if defined (_Windows)
#    include MOD_INCLUDE(windows)
//
// Is the winbase.h file really required to be included.
// #  include <winbase.h>
//
#elif defined (sun)
#  include MOD_INCLUDE(synch)
#  include MOD_INCLUDE(thread)
#  include MOD_INCLUDE(sys/errno)

#elif defined(__BEOS__)	// MW-h+ 960731
#  include <OS.h>
#  include <be_rw_lock.h>
 
#elif !defined (MSIPL_MULTITHREAD)
#  error Mutex classes require multi-threaded operating system.
#else
#  error Mutex classes not implemented for this operating system
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif
//
// Class mutex implementation for WINDOWS using
// CRITICAL_SECTION does not work. So commented
// out and used HANDLE instead.
//
class mutex {
//
// Non-recursive mutex
//
#if defined (sun)              // Solaris 2.1
    typedef  mutex_t          mutex_type;
//
// Check for MACRO __WIN32__ henceforth. It may need
// need to be changed. CRITICAL_SECTION part of the 
// code, that has been commented out, should also work.
// Windows NT is required to check this code.
//
#elif defined (__WIN32__)
//
//    typedef  CRITICAL_SECTION mutex_type;
//
    typedef  HANDLE           mutex_type;

#elif defined(__BEOS__)	//	MW-h+ 960731
	typedef long			mutex_type;

#else
#   error Mutex classes not supported in this environment
#endif

private:

    mutex_type  _lock;

public:

    // Initialize the mutex.
    inline mutex ();

    // Implict mutex destruction.
    inline ~mutex ();

    // Explicit mutex destruction.
    inline int remove () const;

    // Acquire the _lock. (Wait if necessary).
    inline int acquire (int = 0) const;

    // Release the _lock.
    inline int release () const;

    // Attempt to lock the mutex, but don't wait. Return true if 
    // successful.
    bool try_lock ();

};

inline mutex::mutex ()
{
#if defined (sun)
    ::mutex_init ((mutex_t*)&this->_lock, USYNC_THREAD, 0);
#elif defined (__WIN32__)
//
//    ::InitializeCriticalSection (&this->_lock);
//
    _lock = ::CreateMutex (NULL, FALSE, NULL);

#elif defined(__BEOS__)	//	MW-h+ 960731
	_lock = 0;
#endif
}

inline int mutex::remove () const
{
#if defined (sun)
    return ::mutex_destroy ((mutex_t*)&this->_lock);
#elif defined (__WIN32__)
//
//    ::DeleteCriticalSection (&this->_lock);
//
    ::CloseHandle (_lock);
    return 0;

#elif defined(__BEOS__) // MW-h+ 960731
	mutex *self = const_cast<mutex *>(this);
//	self->_lock = -1; /* DON'T DO THIS */
 	self->_lock = 0;
   return (B_NO_ERROR);
#endif
}

inline mutex::~mutex ()
{
    remove ();
}

inline int mutex::acquire (int) const
{
#if defined (sun)
    return ::mutex_lock ((mutex_t*)&this->_lock);
#elif defined (__WIN32__)
//
//    ::EnterCriticalSection (&this->_lock);
//
    ::WaitForSingleObject (_lock, INFINITE);
    return 0;
#elif defined(__BEOS__)
	mutex *self = const_cast<mutex *>(this);
	acquire_spinlock(&self->_lock);
	return B_NO_ERROR;
#endif
}

inline int mutex::release () const
{
#if defined (sun)
    return ::mutex_unlock ((mutex_t*)&this->_lock);
#elif defined (__WIN32__)
//
//    ::LeaveCriticalSection (&this->_lock);
//
    ::ReleaseMutex (_lock);
    return 0;

#elif defined(__BEOS__) // MW-h+ 960731
	mutex *self = const_cast<mutex *>(this);
	release_spinlock(&self->_lock);
    return (B_NO_ERROR);
#endif
}

inline bool mutex::try_lock () 
{

#if defined (sun)

    long result = ::mutex_trylock ((mutex_t*)&this->_lock);
    bool busy   = (result == EBUSY);
    if (result && !busy)
    {
        return false;
    }
    else
    {
        return !busy;
    }

#elif defined (__WIN32__)

    long result = ::WaitForSingleObject (_lock, 0);
 
    if (result == WAIT_FAILED)
    {
        return false;
     }
     else
     {
         return result != WAIT_TIMEOUT;
     }

#elif defined(__BEOS__) // MW-h+ 960731
	mutex *self = const_cast<mutex *>(this);
	long current = test_and_set (&self->_lock, 1);
	return (current == 0);

#endif

}

template <class MUTEX>
class mutex_block {

public:
    // Implicit lock acquisition
    inline mutex_block (const MUTEX& m, int type = 0)
    : _lock (m) { _lock.acquire (type); }

    // Implicit lock release
    inline ~mutex_block () { _lock.release (); }

    // Explicit lock release
    inline int remove () const { return _lock.remove (); }

    // Explicit lock release
    inline int release () const { return _lock.release (); }

    // Explicit lock acquisition
    inline int acquire (int type = 0) const { return _lock.acquire (type); }

private:

    const MUTEX&  _lock;

};

template <class TYPE, class MUTEX>
class mutex_arith {

private:

    TYPE   _count;
    MUTEX  _lock;

public:

    // Initialize _count to 0.
    inline mutex_arith ()
    {
       _count = 0;
    }

    // Initialize _count to i.
    inline mutex_arith (TYPE i)
    {
        _count = i;
    }

    // Increment _count by unit.
    inline TYPE operator++ ()
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  ++_count;
    }

    inline TYPE operator++ (int)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count++;
    }


    // Increment _count by i.
    inline TYPE operator+= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count += i;
    }

    // Decrement _count by unit.
    inline TYPE operator-- ()
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  --_count;		
    }

    inline TYPE operator-- (int)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count--;		
   }

    // Decrement _count by i.
    inline TYPE operator-= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count -= i;
    }

    // Compare _count with i.
    inline bool operator== (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count == i;
    }
    inline bool operator!= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count != i;
    }

    // Check if _count >= i.
    inline bool operator>= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count >= i;
    }

    // Check if _count > i.
    inline bool operator> (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count > i;
    }

    // Check if _count <= i.
    inline bool operator<= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count <= i;
    }

    // Check if _count < i.
    inline bool operator< (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count < i;
    }

    // Assign i to count_.
    inline void operator= (const TYPE i)
    {
        mutex_block<MUTEX>   _mutex (_lock);
        _count = i;
    }

    // Return count_.
    inline operator TYPE ()
    {
        mutex_block<MUTEX>   _mutex (_lock);
        return  _count;
    }

};

class rw_mutex {
#if defined (sun)              // Solaris 2.1
    typedef  rwlock_t          mutex_type;
#elif defined(__BEOS__) // MW-h+ 960731
	typedef rw_lock_id         mutex_type;
#else
#   error Readers/Writer Mutex classes not supported in this environment
#endif

private:

    mutex_type  _lock;

public:

    // Initialize the readers/writer mutex.
    inline rw_mutex ();

    // Implict mutex destruction.
    inline ~rw_mutex ();

    // Explicit mutex destruction.
    inline int remove () const;

    // Acquire the _lock. (Wait if necessary).
    inline int acquire (int) const;

    // Release the _lock.
    inline int release () const;

    // Attempt to lock the mutex for reading, but don't wait. Return true if 
    // successful.
    bool try_rdlock ();

    // Attempt to lock the mutex for writing, but don't wait. Return true if 
    // successful.
    bool try_wrlock ();

};



#if 0			/* jcm 11/14/97 uncommented to try and get it to compile */


inline rw_mutex::rw_mutex ()
{
#if defined (sun)
    ::rwlock_init ((rwlock_t*)&this->_lock, USYNC_THREAD, 0);
#elif defined(__BEOS__) // MW-h+ 960731
	_lock = create_rwlock("C++ R/W lock");
#endif
}

inline int rw_mutex::remove () const
{
#if defined (sun)
    return ::rwlock_destroy ((rwlock_t*)&this->_lock);
#endif
}

inline rw_mutex::~rw_mutex ()
{
    remove ();
}

inline int rw_mutex::acquire (int type) const
{
#if defined (sun)
    if (type == RD_LOCK)
        return ::rw_rdlock ((rwlock_t*)&this->_lock);
    else
    if (type == WR_LOCK)
        return ::rw_wrlock ((rwlock_t*)&this->_lock);
#elif defined(__BEOS__) // MW-h+ 960731
	if (type == RD_LOCK)
		return acquire_read(_lock);
	else
	if (type == WR_LOCK)
		return acquire_write(_lock);
#endif
    return 0;
}

inline int rw_mutex::release () const
{
#if defined (sun)
    return ::rw_unlock ((rwlock_t*)&this->_lock);
#elif defined(__BEOS__) // MW-h+ 960731
	return release_rwlock(_lock);
#endif
}

inline bool rw_mutex::try_rdlock () 
{

#if defined (sun)

    long result = ::rw_tryrdlock ((rwlock_t*)&this->_lock);
    bool busy   = (result == EBUSY);
    if (result && !busy)
    {
        return false;
    }
    else
    {
        return !busy;
    }
#elif defined(__BEOS__) // MW-h+ 960731
	long result = acquire_read_etc(_lock, B_TIMEOUT, 0);
	return result == B_NO_ERROR;
#endif

}

inline bool rw_mutex::try_wrlock () 
{

#if defined (sun)

    long result = ::rw_trywrlock ((rwlock_t*)&this->_lock);
    bool busy   = (result == EBUSY);
    if (result && !busy)
    {
        return false;
    }
    else
    {
        return !busy;
    }
#elif defined(__BEOS__) // MW-h+ 960731
	long result = acquire_write_etc(_lock, B_TIMEOUT, 0);
	return result == B_NO_ERROR;
#endif

}

#endif /* 0 */			/* jcm 11/14/97 uncommented in order to try to get it to compile */

//
// Recursive Mutex
//
#ifdef MSIPL_DEF_TEMPARG
template <class MUTEX = mutex>
#else
template <class MUTEX>
#endif
class mutex_rec {

#if defined (sun)              // Solaris 2.1 & above
    typedef  thread_t    thread_id;    
#elif defined (__WIN32__)
    typedef  HANDLE      thread_id;  
#elif defined(__BEOS__) // MW-h+ 960731
	//	thread_id is the right name!!!
#else
#   error Mutex classes not supported in this environment
#endif

public:

   mutex_rec():nest_count(0),thr_id(0){ }
   
   int acquire(int type = 0) const
   {
       thread_id  t_id = get_tid ();
       
       if (t_id == thr_id)
       { 
           ++((mutex_rec*)this)->nest_count;
           return 0;
       }
       else
       {
           int lock_fail = lock.acquire (type);
           if (!lock_fail)
           {
               ((mutex_rec*)this)->thr_id = t_id;
               ((mutex_rec*)this)->nest_count = 0;
           }
           return lock_fail;
       }
    }

    int release() const
    {
        if (((mutex_arith<unsigned int, mutex>)((mutex_rec*)this)->nest_count).operator >(0)) 
        {
            --((mutex_rec*)this)->nest_count;
            return 0;
        }
        else
        {
            ((mutex_rec*)this)->thr_id = 0;
            return lock.release();
        }
    }

    int remove () const
    {
        return lock.remove ();
    }

private:

    thread_id get_tid () const 
    { 
#if defined (sun)
             return (thr_self ());
#elif defined (__WIN32__)
             return (GetCurrentThread ());
#elif defined(__BEOS__) // MW-h+ 960731
             return find_thread(NULL);
#endif
     }

    MUTEX                             lock;
    thread_id                         thr_id;
    mutex_arith<unsigned int,mutex>   nest_count;     // count for locks. 
};

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_MULTITHREAD */


#endif /* MSIPL_MUTEX_H */

//961210 bkoz added alignment wrapper
//970417 Be-mani readded BEOS code (originally by h+)
