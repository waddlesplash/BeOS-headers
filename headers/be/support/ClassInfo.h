/*
	
	ClassInfo.h
	
	Copyright 1994-96 Be, Inc. All Rights Reserved.

*/


#ifndef _CLASS_INFO_H
#define _CLASS_INFO_H

#ifndef _SUPPORT_DEFS_H
#include <SupportDefs.h>
#endif

#define B_DECLARE_CLASS_INFO(BASE)							\
	public:													\
	  virtual const	BClassInfo	*DynamicClassInfo()	const;	\
	  static const	BClassInfo	*ClassInfo();				\
	private:												\
	  static const	BClassInfo	classInfo;					\
	  typedef BASE	inherited

#define B_DECLARE_ROOT_CLASS_INFO()							\
	public:													\
	  virtual const	BClassInfo	*DynamicClassInfo()	const;	\
	  static const	BClassInfo	*ClassInfo();				\
	private:												\
	  static const	BClassInfo	classInfo

#define B_DEFINE_CLASS_INFO(class, base)									\
	const	BClassInfo	*class::DynamicClassInfo() const				\
								{ return &classInfo; }					\
	const	BClassInfo	*class::ClassInfo()								\
								{ return &classInfo; }					\
	const	BClassInfo	class::classInfo(#class, base::ClassInfo())

#define B_DEFINE_ROOT_CLASS_INFO(class)									\
	const	BClassInfo	*class::DynamicClassInfo() const				\
								{ return &classInfo; }					\
	const	BClassInfo	*class::ClassInfo()								\
								{ return &classInfo; }					\
	const	BClassInfo	class::classInfo(#class, 0)

// returns pointer to class name.
#define class_name(ptr)				\
	(((ptr)->DynamicClassInfo())->Name())

// Is the object pointed to by ptr an object of class "class"?
#define is_kind_of(ptr, class)			\
	((ptr)->DynamicClassInfo())->CanCast(class::ClassInfo())
	
// Is the object pointed to by ptr EXACTLY class "class"
#define is_instance_of(ptr, class)		\
	((ptr)->DynamicClassInfo())->IsSameAs(class::ClassInfo())
	
// Must check for NIL after the cast to see if it was legal.
#define cast_as(ptr, class)			\
	(is_kind_of(ptr, class) ? (class *) (ptr) : 0)

/* -----------------------------------------------------------------------------
	Class BClassInfo
*/
class BClassInfo
{
	B_DECLARE_ROOT_CLASS_INFO();

public:
		BClassInfo(const char *name, const BClassInfo *base);
		
		const char	*Name()											const;
		bool		IsSameAs(const BClassInfo *p)					const;
		bool		DerivesFrom(const BClassInfo *p,
								bool DirectOnly = FALSE)			const;
		bool		CanCast(const BClassInfo *p)					const;
	
private:
		const char			*fClassName;
		const BClassInfo	*fBaseClass;
};


#endif
