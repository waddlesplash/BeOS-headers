/*  Metrowerks Standard Library  Version 2.2  1997 October 17  */
/**
 ** Lib++     : The Modena C++ Standard Library,
 **             Version 2.1, November 1996
 **
 ** Copyright (c) 1994-1996 Modena Software Inc.
 **/

#ifndef MSIPL_STDEXCEPT_H 
#define MSIPL_STDEXCEPT_H

#include <mcompile.h>

#if __MWERKS__				// 960828 bkoz to cut the exception->string dependencies
	#include <exception>
#else
	#ifdef MSIPL_ANSI_HEADER
	#include MOD_INCLUDE(string)
	#else
	#include MOD_INCLUDE(bstring)
	#endif
#endif

#ifdef   MSIPL_EXCEPT
#ifdef  __EDG_EXCEPT_CLASSES
#include MOD_INCLUDE(typeinfo)
#endif
#endif

#ifndef MSIPL_EXCEPTION_SEEN

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
namespace std {
#endif

#ifdef   MSIPL_EXCEPT
#ifndef  __EDG_EXCEPT_CLASSES

// Section 19.1 -- Exception classes
//960802 bkoz moved into <exception> to comform with draft
/*
class exception {
public :
    exception () MSIPL_THROW : desc (0), alloced (false) { }
    exception (const exception& exarg) MSIPL_THROW;
    exception& operator= (const exception& exarg) MSIPL_THROW;
    virtual ~exception () MSIPL_THROW;
    virtual const char* what () const MSIPL_THROW;
protected :
    exception (const string& what_arg) MSIPL_THROW;
private :
    const string* desc;
    bool  alloced;
};
*/
class logic_error : public exception {
public :
    logic_error (const char* what_arg) : exception (what_arg) { } //961122 bkoz
    logic_error (const string& what_arg) : exception (what_arg) { }
    virtual ~logic_error () MSIPL_THROW;
};

class domain_error : public logic_error {
public :
    domain_error (const char *what_arg) : logic_error (what_arg) { } // 980107 mani
    domain_error (const string& what_arg) : logic_error (what_arg) { }
    virtual ~domain_error () MSIPL_THROW;
};

class invalid_argument : public logic_error {
public :
    invalid_argument (const char *what_arg) : logic_error (what_arg) { } // 980107 mani
    invalid_argument (const string& what_arg) : logic_error (what_arg) { }
    virtual ~invalid_argument () MSIPL_THROW;
};

class length_error : public logic_error {
public :
    length_error (const char* what_arg) : logic_error (what_arg) { }  //961122 bkoz
    length_error (const string& what_arg) : logic_error (what_arg) { }
    virtual ~length_error () MSIPL_THROW;
};

class out_of_range : public logic_error {
public :
    out_of_range (const char* what_arg) : logic_error (what_arg) { }  //961122 bkoz
    out_of_range (const string& what_arg) : logic_error (what_arg) { }
    virtual ~out_of_range () MSIPL_THROW;
};

class runtime_error : public exception {
public :
    runtime_error (const char *what_arg) : exception (what_arg) { } // 980107 mani
    runtime_error (const string& what_arg) : exception (what_arg) { }
    virtual ~runtime_error () MSIPL_THROW;
protected :
    runtime_error () : exception () { }
};

class range_error : public runtime_error {
public :
    range_error (const char *what_arg) : runtime_error (what_arg) { } // 980107 mani
    range_error (const string& what_arg) : runtime_error (what_arg) { }
    virtual ~range_error () MSIPL_THROW;
};

class overflow_error : public runtime_error {
public :
    overflow_error (const char *what_arg) : runtime_error (what_arg) { } // 980107 mani
    overflow_error (const string& what_arg) : runtime_error (what_arg) { }
    virtual ~overflow_error () MSIPL_THROW;
};

//
// To be moved later to new.h
//
//960828 bkoz moved to new.h
/*
class bad_alloc : public exception {
public :
    bad_alloc () MSIPL_THROW : exception () { }
    bad_alloc (const bad_alloc& ) MSIPL_THROW : exception () { }
    bad_alloc& operator= (const bad_alloc& exarg) MSIPL_THROW ;
    virtual ~bad_alloc () MSIPL_THROW;
    virtual const char* what () const MSIPL_THROW;
private :
    static  const string  alloc_msg;
};
*/
//
// To be moved later to typeinfo.h
//
//960828 bkoz moved to typeinfo
/*

class bad_cast : public exception {
public :
    bad_cast (const string& what_arg) MSIPL_THROW
    : exception (what_arg) { }
    virtual ~bad_cast () MSIPL_THROW;
};

class bad_typeid : public exception {
public :
    bad_typeid () MSIPL_THROW;
    virtual ~bad_typeid () MSIPL_THROW;
};
*/
#else

//
// Section 19.1 -- Exception classes
// class exception, bad_cast, bad_typeid 
// ---- from files stdexcept.h & typeinfo.h
//

class msipl_exception : public exception {
public :
    msipl_exception (const char* what_arg) MSIPL_THROW;
    msipl_exception (const msipl_exception& exarg) MSIPL_THROW;
    msipl_exception& operator= (const msipl_exception& exarg) MSIPL_THROW;
    virtual const char* what () const MSIPL_THROW;
    virtual ~msipl_exception () MSIPL_THROW;
private:
    char* ptr;
};

class logic_error : public msipl_exception {
public :
    logic_error (const char* what_arg)
    : msipl_exception (what_arg) { }
    virtual ~logic_error () MSIPL_THROW;
};

class domain_error : public logic_error {
public :
    domain_error (const char* what_arg)
    : logic_error (what_arg) { }
    virtual ~domain_error () MSIPL_THROW;
};

class invalid_argument : public logic_error {
public :
    invalid_argument (const char* what_arg)
    : logic_error (what_arg) { }
    virtual ~invalid_argument () MSIPL_THROW;
};

class length_error : public logic_error {
public :
    length_error (const char* what_arg)
    : logic_error (what_arg) { }
    virtual ~length_error () MSIPL_THROW;
};

class out_of_range : public logic_error {
public :
    out_of_range (const char* what_arg)
    : logic_error (what_arg) { }
    virtual ~out_of_range () MSIPL_THROW;
};

class runtime_error : public msipl_exception {
public :
    runtime_error (const char* what_arg)
    : msipl_exception (what_arg) { }
    virtual ~runtime_error () MSIPL_THROW;
protected :
    runtime_error () : msipl_exception (0) { }
};

class range_error : public runtime_error {
public :
    range_error (const char* what_arg)
    : runtime_error (what_arg) { }
    virtual ~range_error () MSIPL_THROW;
};

class overflow_error : public runtime_error {
public :
    overflow_error (const char* what_arg)
    : runtime_error (what_arg) { }
    virtual ~overflow_error () MSIPL_THROW;
};

/*
//
// To be moved later to new.h
//
class bad_alloc : public runtime_error {
public :
    bad_alloc () MSIPL_THROW
    : runtime_error () { }
    bad_alloc (const bad_alloc& exarg) MSIPL_THROW
    : runtime_error () { }
    bad_alloc& operator= (const bad_alloc& exarg) MSIPL_THROW;
    virtual ~bad_alloc () MSIPL_THROW;
    virtual const char* what () const MSIPL_THROW;
private :
    static  const char   alloc_msg[];
};
*/

#endif /* __EDG_EXCEPT_CLASSES */

#endif /* MSIPL_EXCEPT */

#define MSIPL_EXCEPTION_SEEN

#ifdef MSIPL_USING_NAMESPACE
} /* namespace std */
#endif

#endif /* MSIPL_EXCEPTION_SEEN */

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset


#endif /* MSIPL_STDEXCEPT_H */

//960828 bkoz line 15 to cut the exception->string dependencies, move exception into own header
//960828 bkoz line 39 move exeption class definition into its own header. . .
//960828 bkoz line 108 moved bad_alloc to new.h
//960828 bkoz line 122 moved bad_cast, bad_typeid to typeinfo.h
//961122 bkoz added const char * ctors for 3 classes for inlining...
//961210 bkoz added alignment wrapper
//980107 Be-mani Complete the 961122 for all classes. Why didn't bkoz
//               do this in the first place?
