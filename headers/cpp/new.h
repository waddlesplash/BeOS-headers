/*  Metrowerks Standard Library  Version 2.1  1996 December 29  */
/*
 *	new
 *	
 *		Copyright © 1996 Metrowerks, Inc.
 *		All rights reserved.
 */
 
#ifndef __new__
#define __new__

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#include <mcompile.h>

#ifdef MSIPL_USING_NAMESPACE  // MW-mm 960213b
namespace std {
#endif

#include <size_t.h>     //MW-mm 960723
#include <exception>		//960902 bkoz

class bad_alloc : public exception {
	public :
	    bad_alloc () MSIPL_THROW : exception () { }
	    bad_alloc (const bad_alloc& ) MSIPL_THROW : exception () { }
	    bad_alloc& operator= (const bad_alloc& exarg) MSIPL_THROW;
	    virtual ~bad_alloc () MSIPL_THROW;
	    virtual const char* what () const MSIPL_THROW;
/* XXX Be-mani 
 *    Having static objects of complex types as members of
 *    classes is BAD programming practice and triggered a bug
 *    on one particular Mac configuration running the BeOS.
 *    This has correspondingly been changed in mexcept.cpp
 */
#ifdef WRONG
	private :
	    static  const string  alloc_msg;
#endif
};
	
	//old
	//struct nothrow {};
	
	//new
	struct nothrow_t {};
	const nothrow_t nothrow = {};

	//old 		
	//void (*set_new_handler (void (*) () )) ();

	//new 960813 bkoz
	typedef void (*new_handler)(); 
	
	#if __dest_os == __win32_os
		new_handler set_new_handler(new_handler); 
	#else
		new_handler set_new_handler(new_handler) throw(); 
	#endif

#ifdef MSIPL_USING_NAMESPACE // MW-mm 960213b
} /* namespace std */
#endif

#define __nothrow		/*std::*/nothrow
#define __bad_alloc	/*std::*/bad_alloc

#if !__MOTO__	//moto can't have two declarations, one with exception spec and one w/o
	void * 	operator new(size_t size);  // MW-mm 960213c
#endif
	void * 	operator new(size_t size) throw (__bad_alloc); // MW-mm 960213c //bkoz 960813
	void * 	operator new(size_t size, const nothrow_t&)		throw();	//9608013 bkoz
	
	//void	operator delete		(void * ptr);  //MW-mm 960307a
	void	operator delete		(void * ptr) throw(); //MW-mm 960307a

//				void * 	operator new[]		(size_t size)											throw(__bad_alloc);
//				void * 	operator new[]		(size_t size, const __nothrow& t)	throw();
//				void		operator delete[]	(void * ptr)											throw();

inline		void *	operator new(size_t, void * ptr)throw()	{ return(ptr); }
//inline	void * 	operator new[]		(size_t, void * ptr) throw()	{ return(ptr); }
//inline	void		operator delete		(void * , void *) throw()	{}
//inline	void		operator delete[]	(void * , void *) throw()	{}

//	non-standard functions
extern char	__throws_bad_alloc;
extern void __throw_bad_alloc();
extern void _set_newpoolsize(size_t);		//	default: 0x00010000L
extern void _set_newnonptrmax(size_t);		//	default: 0x00001000L
extern char _prealloc_newpool(size_t);		//	preallocte a new buffer

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif

/* Change record
MW-mm 960213a  Deleted the definition of the bad_except class
MW-mm 960213b  Put Modena wrappers around namespace
MW-mm 960213c  Changed declaration to avoid syntax error in line with <new>
MW-mm 960307a  Changed declaration to avoid syntax error in line with delete
MW-mm 960723   Added include of size_t.h so that new.h can be compiled independently
mw-bk 960813   added andreas's changes for new throw bad_alloc()
mw-bk 960902   moved class exception into exception header, including excpt instead of stdexcept
mw-bk 961210 	added alignment wrapper
mw-bk 961221	line 65 added moto wrapper (mmoss)
*/
