/*
	
	ClassInfo.h
	
	Copyright 1994 Be, Inc. All Rights Reserved.

*/


#ifndef _CLASS_INFO_H
#define _CLASS_INFO_H

/*
This header file defines the runtime type information system used by Be software.
There are 2 parts to this system:

1) A private typedef of "inherited" is created that represents the base class.
This, in effect, creates an "inherited" keyword that can be used to call
inherited functions. For example:
	SomeClass::SomeFunc()
	{
		...
		inherited::SomeFunc();
	}

2) Runtype type information is available to any class defined in a specific
fashion. If you want a class to have runtime type information, declare the
class like so:

	class B : public A
	{
		...
		DECLARE_CLASS_INFO(A);	// use DECLARE_ROOT_CLASS_INFO() if class B
					// has no base class.
	};

And in the implementation file do the following at the global scope (###):

	DEFINE_CLASS_INFO(B, A);	// use DEFINE_ROOT_CLASS_INFO(B) if class B
					// has no base class

That's all. Now class B will contain runtime type information.

The runtime info can be used in the following ways (in the following examples 
assume that class A also has the runtime type information):

	- Safe casting: Can determine if a A* object is really an B*:
		func(A *a) {
			B *b;
			b = cast_as(a, B);
			if (b) {
				// "a" was a pointer to a B object
			}
			else {
				// it wasn't!
			}
		}
	
	- is_kind_of macro - determine if object pointed to by a is of class B
		or derived from class B:
		
		func(A *a) {
			if (is_kind_of(a, B)) {...}
		}
	
	- is_instance_of macro - determine if object pointed to by "a" is exactly
		class B:
		
		func(A *a) {
			if (is_instance_of(a, B)) {...}
		}
	
	- class_name macro
		func(A *a) {
			printf("real class of A *a = %s", class_name(a));
		}
		
	- (More stuff to come like handling reference objects, etc)
*/

#ifndef _SUPPORT_DEFS_H
#include <support/SupportDefs.h>
#endif

#define DECLARE_CLASS_INFO(BASE)							\
	public:													\
	  virtual const	BClassInfo	*DynamicClassInfo()	const;	\
	  static const	BClassInfo	*ClassInfo();				\
	private:												\
	  static const	BClassInfo	classInfo;					\
	  typedef BASE	inherited;

#define DECLARE_ROOT_CLASS_INFO()							\
	public:													\
	  virtual const	BClassInfo	*DynamicClassInfo()	const;	\
	  static const	BClassInfo	*ClassInfo();				\
	private:												\
	  static const	BClassInfo	classInfo;

#define DEFINE_CLASS_INFO(class, base)									\
	const	BClassInfo	*class::DynamicClassInfo() const				\
								{ return &classInfo; }					\
	const	BClassInfo	*class::ClassInfo()								\
								{ return &classInfo; }					\
	const	BClassInfo	class::classInfo(#class, base::ClassInfo());

#define DEFINE_ROOT_CLASS_INFO(class)									\
	const	BClassInfo	*class::DynamicClassInfo() const				\
								{ return &classInfo; }					\
	const	BClassInfo	*class::ClassInfo()								\
								{ return &classInfo; }					\
	const	BClassInfo	class::classInfo(#class, 0);

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
	DECLARE_ROOT_CLASS_INFO();

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
