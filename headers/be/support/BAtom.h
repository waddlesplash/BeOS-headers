/***************************************************************************
//
//	File:			support/BAtom.h
//
//	Description:	BAtom is a reference counted base class.
//					atom_ptr<> is a template class that looks like a
//					pointer to an atom and holds a primary reference on it.
//					atom_ref<> is a template class that looks like a
//					pointer to an atom and holds a secondary reference on it.
//
//	Copyright 2001, Be Incorporated, All Rights Reserved.
//
***************************************************************************/

// NOTE: This is the new IK2 BAtom class.  For the version that is
// currently used by Wagner see support/Atom.h.

#ifndef _SUPPORT_ATOM_H
#define _SUPPORT_ATOM_H

#include <support/SupportDefs.h>

#include <typeinfo>

namespace std {
	struct nothrow_t;
}

class BDataIO;

namespace B {
namespace Support {

class AtomTracker;

// Flags for BAtom debugging reports
enum {
	B_FORCE_LONG_REPORT		= 0x0001,
	B_FORCE_SHORT_REPORT	= 0x0002,
	B_FORCE_SUMMARY_REPORT	= 0x0003,
	B_FORCE_REPORT_MASK		= 0x000f,
	
	B_REMOVE_HEADER			= 0x0010
};

class BAtom
{
public:
		void*			operator new(size_t size);
		void*			operator new(size_t size, const std::nothrow_t&);
		void			operator delete(void* ptr, size_t size);

		// Acquire and release the primary reference.  This is
		// the standard reference count -- once it transitions
		// to zero, the atom will become invalid.
		// An atom starts with a reference count of zero, and
		// gets invalidated the first time it transitions from one
		// to zero.
		int32			Acquire(const void* id = NULL) const;
		int32			Release(const void* id = NULL) const;
		
		// Increment and decrement the secondary reference count.
		// This keeps an atom from actually being freed after its
		// last primary reference is removed.  If you are only
		// holding a secondary reference on the object, you know
		// that the memory it points to still exists, but don't
		// know what state the object is in.
		int32		 	IncRefs(const void* id = NULL) const;
		int32		 	DecRefs(const void* id = NULL) const;

		// Try to acquire this atom if you only have a reference
		// on it.  Returns true on success, false on failure.
		// Failure only after the atom has already been acquired
		// and then completely released.
		bool			AttemptAcquire(const void* id = NULL) const;
		
		void			Report(BDataIO& io, const char* prefix="  ", uint32 flags=0) const;
		
static	int32			MarkLeakReport();
static	void			LeakReport(BDataIO& io, int32 mark=0, uint32 flags=0);
static	void			LeakReport(int32 mark=0, uint32 flags=0);
		
static	void			StartWatching(const type_info* type);
static	void			StopWatching(const type_info* type);

protected:

						BAtom();
virtual					~BAtom();

		// This function is called the first time an atom is
		// acquired.  You can override it and do any setup you
		// need.  Note that you do not need to call the BAtom
		// implementation.  (So you can derive from two different
		// BAtom implementations and safely call down to both
		// of their Acquire() methods.)
virtual	void			Acquired();

		// This function is called the last time an atom is
		// released.  The default implementation deletes the
		// object.  You can override it to do something else,
		// but note that when inheriting from multiple BAtom base
		// classes, only ONE of their Released() methods can be
		// called.
virtual	void			Released();

		// If you override Released() to not call into BAtom
		// (and thus extend the life of your object), then this
		// method will be called when its last reference goes
		// away.  The default implementation deletes the object.
virtual	void			DeleteAtom();

private:
		friend class	AtomTracker;
		
		void			destructor_impl();
		void			delete_impl(size_t size);
		
		// ----- Debugging Support -----
		
		void			init_atom();
		void			term_atom();
		
		void			lock_atom() const;
		void			unlock_atom() const;
		
		int32*			primary_addr() const;
		int32*			secondary_addr() const;
		
		int32			primary_count() const;
		int32			secondary_count() const;
		
		void			watch_action(const char* description) const;
		void			do_report(BDataIO& io, const char* prefix, uint32 flags) const;
		
		void			add_acquire(const void* id) const;
		void			add_release(const void* id) const;
		void			add_increfs(const void* id) const;
		void			add_decrefs(const void* id) const;
		
mutable	int32			fPrimary;
mutable	int32			fSecondary;
		void*			fBase;
		int32			fSize;
};

// -----------------------------------------------------------------------

// forward reference
template <class TYPE> class atom_ref;
template <class TYPE> class safe_ptr;
template <class TYPE> class safe_ref;

template <class TYPE>
class atom_ptr {
public:
		atom_ptr();
		atom_ptr(const atom_ptr<TYPE>& p);
		atom_ptr(TYPE* p);
		~atom_ptr();

		// Conversion to other atom types.
		template <class NEWTYPE> operator atom_ptr<NEWTYPE>() const;
		template <class NEWTYPE> operator atom_ref<NEWTYPE>() const;
		
		// Access to raw pointer.
		TYPE& operator *() const;
		TYPE* operator ->() const;
		
		TYPE* ptr() const;
		TYPE* detach() const;
		
		// Assignment.
		const atom_ptr<TYPE> &operator =(TYPE* p);
		const atom_ptr<TYPE> &operator =(const atom_ptr<TYPE>& p);

		// Give comparison operators access to our pointer.
		#define COMPARE_FRIEND(op)									\
			friend bool operator op <>(	const atom_ptr<TYPE>& p,	\
										const atom_ptr<TYPE>& p);	\
			bool operator op (const TYPE* p2) const					\
				{ return fPtr op p2; }								\
			friend bool operator op <>(	const atom_ref<TYPE>& p,	\
										const atom_ptr<TYPE>& p);	\
			friend bool operator op <>(	const atom_ptr<TYPE>& p,	\
										const atom_ref<TYPE>& p);	\
		
		COMPARE_FRIEND(==);
		COMPARE_FRIEND(!=);
		COMPARE_FRIEND(<=);
		COMPARE_FRIEND(<);
		COMPARE_FRIEND(>);
		COMPARE_FRIEND(>=);
		
		#undef COMPARE_FRIEND

private:
		friend atom_ref<TYPE>;
		friend safe_ptr<TYPE>;
		friend safe_ref<TYPE>;
		
		TYPE *fPtr;
};

// -----------------------------------------------------------------------

template <class TYPE>
class atom_ref {
public:
		atom_ref();
		atom_ref(const atom_ptr<TYPE>& p);
		atom_ref(const atom_ref<TYPE>& p);
		atom_ref(TYPE* p);
		~atom_ref();
		
		// Conversion to other atom types.
		template <class NEWTYPE> operator atom_ref<NEWTYPE>() const;
		
		// Assignment.
		const atom_ref<TYPE> &operator =(TYPE* p);
		const atom_ref<TYPE> &operator =(const atom_ptr<TYPE>& p);
		const atom_ref<TYPE> &operator =(const atom_ref<TYPE>& p);

		// Attempt to promote this reference to an acquire.
		// The returned atom_ptr<> will be NULL if it failed.
		const atom_ptr<TYPE> acquire() const;
		
		// Give comparison operators access to our pointer.
		#define COMPARE_FRIEND(op)									\
			friend bool operator op <>(	const atom_ref<TYPE>& p,	\
										const atom_ref<TYPE>& p);	\
			bool operator op (const TYPE* p2) const					\
				{ return fPtr op p2; }								\
			friend bool operator op <>(	const atom_ref<TYPE>& p,	\
										const atom_ptr<TYPE>& p);	\
			friend bool operator op <>(	const atom_ptr<TYPE>& p,	\
										const atom_ref<TYPE>& p);	\
		
		COMPARE_FRIEND(==);
		COMPARE_FRIEND(!=);
		COMPARE_FRIEND(<=);
		COMPARE_FRIEND(<);
		COMPARE_FRIEND(>);
		COMPARE_FRIEND(>=);
		
		#undef COMPARE_FRIEND
		
private:
		friend atom_ptr<TYPE>;
		friend safe_ptr<TYPE>;
		friend safe_ref<TYPE>;
		
		TYPE *fPtr;
};

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------

// A zillion kinds of comparison operators.
#define COMPARE(op)														\
template<class TYPE> inline												\
bool operator op(const atom_ptr<TYPE>& p1, const atom_ptr<TYPE>& p2)	\
	{ return p1.fPtr op p2.fPtr; }										\
template<class TYPE> inline												\
bool operator op(const atom_ref<TYPE>& p1, const atom_ref<TYPE>& p2)	\
	{ return p1.fPtr op p2.fPtr; }										\
template<class TYPE> inline												\
bool operator op(const atom_ptr<TYPE>& p1, const atom_ref<TYPE>& p2)	\
	{ return p1.fPtr op p2.fPtr; }										\
template<class TYPE> inline												\
bool operator op(const atom_ref<TYPE>& p1, const atom_ptr<TYPE>& p2)	\
	{ return p1.fPtr op p2.fPtr; }										\

COMPARE(==);
COMPARE(!=);
COMPARE(<=);
COMPARE(<);
COMPARE(>);
COMPARE(>=);

#undef COMPARE

// ----------------------- atom_ptr Implementation -----------------------

template<class TYPE> inline
atom_ptr<TYPE>::atom_ptr()								{ fPtr = NULL; }
template<class TYPE> inline
atom_ptr<TYPE>::atom_ptr(const atom_ptr<TYPE>& p)		{ fPtr = p.fPtr; if (fPtr) fPtr->Acquire(this); }
template<class TYPE> inline
atom_ptr<TYPE>::atom_ptr(TYPE* p)						{ fPtr = p; if (fPtr) fPtr->Acquire(this); }
template<class TYPE> inline
atom_ptr<TYPE>::~atom_ptr()								{ if (fPtr) fPtr->Release(this); }

template<class TYPE> template<class NEWTYPE> inline
atom_ptr<TYPE>::operator atom_ptr<NEWTYPE>() const		{ return atom_ptr<NEWTYPE>(fPtr); }
template<class TYPE> template<class NEWTYPE> inline
atom_ptr<TYPE>::operator atom_ref<NEWTYPE>() const		{ return atom_ref<NEWTYPE>(fPtr); }
template<class TYPE> inline
TYPE & atom_ptr<TYPE>::operator *() const				{ return *fPtr; }
template<class TYPE> inline
TYPE * atom_ptr<TYPE>::operator ->() const				{ return fPtr; }
template<class TYPE> inline
TYPE * atom_ptr<TYPE>::ptr() const						{ return fPtr; }
template<class TYPE> inline
TYPE * atom_ptr<TYPE>::detach() const					{ return fPtr; fPtr = NULL; }

template<class TYPE> inline
const atom_ptr<TYPE> & atom_ptr<TYPE>::operator =(TYPE* p)
{
	if (fPtr!=p) {
		if (fPtr) fPtr->Release(this);
		fPtr = p;
		if (fPtr) fPtr->Acquire(this);
	};
	return *this;
}

template<class TYPE> inline
const atom_ptr<TYPE> & atom_ptr<TYPE>::operator =(const atom_ptr<TYPE>& p)
{
	return ((*this) = p.fPtr);
}

// ----------------------- atom_ref Implementation -----------------------

template<class TYPE> inline
atom_ref<TYPE>::atom_ref()								{ fPtr = NULL; }
template<class TYPE> inline
atom_ref<TYPE>::atom_ref(const atom_ptr<TYPE>& p)		{ fPtr = p.fPtr; if (fPtr) fPtr->IncRefs(this); }
template<class TYPE> inline
atom_ref<TYPE>::atom_ref(const atom_ref<TYPE>& p)		{ fPtr = p.fPtr; if (fPtr) fPtr->IncRefs(this); }
template<class TYPE> inline
atom_ref<TYPE>::atom_ref(TYPE* p)						{ fPtr = p; if (fPtr) fPtr->IncRefs(this); }
template<class TYPE> inline
atom_ref<TYPE>::~atom_ref()								{ if (fPtr) fPtr->DecRefs(this); }

template<class TYPE> template<class NEWTYPE> inline
atom_ref<TYPE>::operator atom_ref<NEWTYPE>() const		{ return atom_ref<NEWTYPE>(fPtr); }

template<class TYPE> inline
const atom_ref<TYPE> & atom_ref<TYPE>::operator =(TYPE *p)
{
	if (fPtr!=p) {
		if (fPtr) fPtr->DecRefs(this);
		fPtr = p;
		if (fPtr) fPtr->IncRefs(this);
	};
	return *this;
}

template<class TYPE> inline
const atom_ref<TYPE> & atom_ref<TYPE>::operator =(const atom_ptr<TYPE> &p)
{
	return ((*this) = p.fPtr);
}

template<class TYPE> inline
const atom_ref<TYPE> & atom_ref<TYPE>::operator =(const atom_ref<TYPE> &p)
{
	return ((*this) = p.fPtr);
}

template<class TYPE> inline
const atom_ptr<TYPE> atom_ref<TYPE>::acquire() const
{
	atom_ptr<TYPE> a;
	if (!fPtr) return a;
	if (fPtr->AttemptAcquire(this)) {
		a = fPtr;
		a->Release(this);
	}
	return a;
}

} }	// namespace B::Support

#endif
