
#ifndef _SUPPORT_SAFE_ATOM_H
#define _SUPPORT_SAFE_ATOM_H

#include <support/BAtom.h>
#include <support/BLightLocker.h>

namespace B {
namespace Support {

template <class TYPE> class safe_ref;

template <class TYPE>
class safe_ptr {
public:
		safe_ptr();
		safe_ptr(const safe_ptr<TYPE>& p);
		safe_ptr(const atom_ptr<TYPE>& p);
		safe_ptr(TYPE* p);
		~safe_ptr();

		safe_ptr<TYPE> &operator =(const safe_ptr<TYPE>& p);
		safe_ptr<TYPE> &operator =(const atom_ptr<TYPE>& p);
		safe_ptr<TYPE> &operator =(TYPE* p);

		operator atom_ptr<TYPE>() const;
		operator safe_ref<TYPE>() const;

		atom_ptr<TYPE>& get_atom(atom_ptr<TYPE>* into) const;
		atom_ref<TYPE>& get_atom(atom_ref<TYPE>* into) const;
		
		// These perform raw reference counting; be very careful if
		// you use them.
		TYPE* raw_acquire() const;
		TYPE* raw_increfs() const;
		
		// Various flavors of the comparison operators.
		// Be careful!  The result is out-of-date as soon as you get it!
		#define COMPARE(op)											\
			inline bool operator op(const TYPE* p) const			\
				{ return ptr op p; }								\
			inline bool operator op(const atom_ref<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
			inline bool operator op(const safe_ptr<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
			inline bool operator op(const safe_ref<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
		
		COMPARE(==);
		COMPARE(!=);
		COMPARE(<=);
		COMPARE(<);
		COMPARE(>);
		COMPARE(>=);
		
		#undef COMPARE
		
private:
		friend safe_ref<TYPE>;
		
		TYPE *ptr;
mutable	BLightLocker lock;
};

template <class TYPE>
class safe_ref {
public:
		safe_ref();
		safe_ref(const safe_ref<TYPE>& p);
		safe_ref(const atom_ptr<TYPE>& p);
		safe_ref(const atom_ref<TYPE>& p);
		safe_ref(TYPE* p);
		~safe_ref();

		safe_ref<TYPE> &operator =(const safe_ptr<TYPE>& p);
		safe_ref<TYPE> &operator =(const safe_ref<TYPE>& p);
		safe_ref<TYPE> &operator =(const atom_ptr<TYPE>& p);
		safe_ref<TYPE> &operator =(const atom_ref<TYPE>& p);
		safe_ref<TYPE> &operator =(TYPE* p);

		operator atom_ref<TYPE>() const;
		
		atom_ref<TYPE>& get_atom(atom_ref<TYPE>* into) const;
		
		// Up-cast to a primary reference.  if the change
		// fails, the result is NULL.
		operator atom_ptr<TYPE>() const;
		atom_ptr<TYPE>& get_atom(atom_ptr<TYPE>* into) const;
		
		// These perform raw reference counting; be very careful if
		// you use them.  Again, the acquire performs an up-cast and
		// returns NULL if it fails.
		TYPE* raw_acquire() const;
		TYPE* raw_increfs() const;
		
		// Various flavors of the comparison operators.
		// Be careful!  The result is out-of-date as soon as you get it!
		#define COMPARE(op)											\
			inline bool operator op(const TYPE* p) const			\
				{ return ptr op p; }								\
			inline bool operator op(const atom_ref<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
			inline bool operator op(const safe_ptr<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
			inline bool operator op(const safe_ref<TYPE>& p) const	\
				{ return ptr op p.ptr; }							\
		
		COMPARE(==);
		COMPARE(!=);
		COMPARE(<=);
		COMPARE(<);
		COMPARE(>);
		COMPARE(>=);
		
		#undef COMPARE
		
private:
		friend safe_ptr<TYPE>;
		
		TYPE *ptr;
mutable	BLightLocker lock;
};

// --------------- safe_ptr Implementation ---------------

template<class TYPE> inline
safe_ptr<TYPE>::safe_ptr()							{ ptr = NULL; }
template<class TYPE> inline
safe_ptr<TYPE>::safe_ptr(const atom_ptr<TYPE>& p)	{ ptr = p.ptr(); if(ptr) ptr->Acquire(this); }
template<class TYPE> inline
safe_ptr<TYPE>::safe_ptr(TYPE* p)					{ ptr = p; if(ptr) ptr->Acquire(this); }
template<class TYPE> inline
safe_ptr<TYPE>::~safe_ptr()							{ if (ptr) if(ptr) ptr->Release(this); }

template<class TYPE> inline
safe_ptr<TYPE>::safe_ptr(const safe_ptr<TYPE>& p)
{
	p.lock();
	ptr = p.ptr;
	if(ptr) ptr->Acquire(this);
	p.unlock();
}

template<class TYPE> inline
safe_ptr<TYPE> & safe_ptr<TYPE>::operator =(const safe_ptr<TYPE> &p)
{
	p.lock.Lock();
	TYPE *t = p.ptr;
	if (t) t->Acquire(this);
	p.lock.Unlock();
	lock.Lock();
	if (ptr!=t) {
		if (ptr) ptr->Release(this);
		ptr = t;
	} else if (t) t->Release(this);
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ptr<TYPE> & safe_ptr<TYPE>::operator =(const atom_ptr<TYPE>& p)
{
	lock.Lock();
	if (ptr!=p.ptr()) {
		if (ptr) ptr->Release(this);
		ptr = p.ptr();
		if (ptr) ptr->Acquire(this);
	};
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ptr<TYPE> & safe_ptr<TYPE>::operator =(TYPE *p)
{
	lock.Lock();
	if (ptr!=p) {
		if (ptr) ptr->Release(this);
		ptr = p;
		if (ptr) ptr->Acquire(this);
	};
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ptr<TYPE>::operator atom_ptr<TYPE>() const
{
	atom_ptr<TYPE> ret;
	get_atom(&ret);
	return ret;
}

template<class TYPE> inline
safe_ptr<TYPE>::operator safe_ref<TYPE>() const
{
	safe_ref<TYPE> ret;
	get_atom(&ret);
	return ret;
}

template<class TYPE> inline
atom_ptr<TYPE>& safe_ptr<TYPE>::get_atom(atom_ptr<TYPE>* into) const
{
	lock.Lock();
	*into = ptr;
	lock.Unlock();
	return *into;
}

template<class TYPE> inline
atom_ref<TYPE>& safe_ptr<TYPE>::get_atom(atom_ref<TYPE>* into) const
{
	lock.Lock();
	*into = ptr;
	lock.Unlock();
	return *into;
}

template<class TYPE> inline
TYPE* safe_ptr<TYPE>::raw_acquire() const
{
	lock.Lock();
	TYPE* result = ptr;
	if (result) result->Acquire();
	lock.Unlock();
	return result;
}

template<class TYPE> inline
TYPE* safe_ptr<TYPE>::raw_increfs() const
{
	lock.Lock();
	TYPE* result = ptr;
	if (result) result->IncRefs();
	lock.Unlock();
	return result;
}

// --------------- safe_ref Implementation ---------------

template<class TYPE> inline
safe_ref<TYPE>::safe_ref()							{ ptr = NULL; }
template<class TYPE> inline
safe_ref<TYPE>::safe_ref(const atom_ptr<TYPE>& p)	{ ptr = p.ptr(); if(ptr) ptr->IncRefs(this); }
template<class TYPE> inline
safe_ref<TYPE>::safe_ref(const atom_ref<TYPE>& p)	{ ptr = p.ptr(); if(ptr) ptr->IncRefs(this); }
template<class TYPE> inline
safe_ref<TYPE>::safe_ref(TYPE* p)					{ ptr = p; if(ptr) ptr->IncRefs(this); }
template<class TYPE> inline
safe_ref<TYPE>::~safe_ref()							{ if (ptr) ptr->DecRefs(this); }

template<class TYPE> inline
safe_ref<TYPE>::safe_ref(const safe_ref<TYPE>& p)
{
	p.lock();
	ptr = p.ptr;
	if(ptr) ptr->IncRefs(this);
	p.unlock();
}

template<class TYPE> inline
safe_ref<TYPE> & safe_ref<TYPE>::operator =(const safe_ptr<TYPE> &p)
{
	p.lock.Lock();
	TYPE *t = p.ptr;
	if (t) t->IncRefs(this);
	p.lock.Unlock();
	lock.Lock();
	if (ptr!=t) {
		if (ptr) ptr->DecRefs(this);
		ptr = t;
	} else if (t) t->DecRefs(this);
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ref<TYPE> & safe_ref<TYPE>::operator =(const safe_ref<TYPE> &p)
{
	p.lock.Lock();
	TYPE *t = p.ptr;
	if (t) t->IncRefs(this);
	p.lock.Unlock();
	lock.Lock();
	if (ptr!=t) {
		if (ptr) ptr->DecRefs(this);
		ptr = t;
	} else if (t) t->DecRefs(this);
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ref<TYPE> & safe_ref<TYPE>::operator =(const atom_ptr<TYPE>& p)
{
	lock.Lock();
	if (ptr!=p.ptr()) {
		if (ptr) ptr->DecRefs(this);
		ptr = p.ptr();
		if (ptr) ptr->IncRefs(this);
	};
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ref<TYPE> & safe_ref<TYPE>::operator =(const atom_ref<TYPE>& p)
{
	lock.Lock();
	if (ptr!=p.ptr()) {
		if (ptr) ptr->DecRefs(this);
		ptr = p.ptr();
		if (ptr) ptr->IncRefs(this);
	};
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ref<TYPE> & safe_ref<TYPE>::operator =(TYPE *p)
{
	lock.Lock();
	if (ptr!=p) {
		if (ptr) ptr->DecRefs(this);
		ptr = p;
		if (ptr) ptr->IncRefs(this);
	};
	lock.Unlock();
	return *this;
}

template<class TYPE> inline
safe_ref<TYPE>::operator atom_ptr<TYPE>() const
{
	atom_ptr<TYPE> ret;
	get_atom(&ret);
	return ret;
}

template<class TYPE> inline
safe_ref<TYPE>::operator atom_ref<TYPE>() const
{
	safe_ref<TYPE> ret;
	get_atom(&ret);
	return ret;
}

template<class TYPE> inline
atom_ptr<TYPE>& safe_ref<TYPE>::get_atom(atom_ptr<TYPE>* into) const
{
	lock.Lock();
	if (ptr && ptr->AttemptAcquire(&lock)) {
		*into = ptr;
		ptr->Release(&lock);
	} else {
		*into = NULL;
	}
	lock.Unlock();
	return *into;
}

template<class TYPE> inline
atom_ref<TYPE>& safe_ref<TYPE>::get_atom(atom_ref<TYPE>* into) const
{
	lock.Lock();
	*into = ptr;
	lock.Unlock();
	return *into;
}
		
template<class TYPE> inline
TYPE* safe_ref<TYPE>::raw_acquire() const
{
	lock.Lock();
	TYPE* result = ptr;
	if (result && !result->AttemptAcquire()) result = NULL;
	lock.Unlock();
	return result;
}

template<class TYPE> inline
TYPE* safe_ref<TYPE>::raw_increfs() const
{
	lock.Lock();
	TYPE* result = ptr;
	if (result) result->IncRefs();
	lock.Unlock();
	return result;
}

} }	// namespace B::Support

#endif
